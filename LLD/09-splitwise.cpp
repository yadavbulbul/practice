#include<iostream>
#include<string>
#include<vector>
#include <cmath>
using namespace std;

class User;
class Group;
class Expense;
class ExpenseService;
class Split;
class SplitStrategy;
class EqualSplitStrategy;
class PercentageSplitStrategy;
class ExactSplitStrategy;
class Balance;
class BalanceService;



class User{
private:
    string id;
    string name;
public:
    User(string userId, string userName){
        this->id=userId;
        this->name=userName;
    }
    string getUserId() const{
        return id;
    }
    string getUserName() const{
        return name;
    }
    void setUserName(string name){
        this->name=name;
    }
};

class Split{
private:
    double amount;
    User* user;
public:
    Split(User* user,double amount){
        this->user=user;
        this->amount=amount;
    }

    User* getUser() const{
        return user;
    }

    double getAmount() const{
        return amount;
    }
};

class Expense{
private:
    string id;
    string description;
    User* paidBy;
    vector<Split*>splits;
    double totalAmount;
public:
    Expense(string id, string description, User* paidBy,double totalAmount){
        this->id=id;
        this->description=description;
        this->paidBy=paidBy;
        this->totalAmount=totalAmount;
    }
    string getId() const{
        return id;
    }
    User* getPaidBy() const{
        return paidBy;
    }
    string getDescription() const{
        return description;
    }
    double getTotalAmount() const{
        return totalAmount;
    }
    vector<Split*> getSplits() const{
        return splits;
    }
    void addSplit(Split* split){
        splits.push_back(split);
    }

};

class Group{
private:
    string id;
    string name;
    vector<User*>users;
    vector<Expense*>expenses;
public:
    Group(string id, string name, vector<User*>users){
        this->id=id;
        this->name=name;
        this->users=users;
    }
    string getId() const{
        return id;
    }
    string getName() const{
        return name;
    }
    vector<User*> getUsers() const{
        return users;
    }
    vector<Expense*> getExpenses() const{
        return expenses;
    }
    void addUser(User* user){
        users.push_back(user);
    }
    void addExpense(Expense* expense){
        expenses.push_back(expense);
    }

};


class Balance{
private:
    User* fromUser;
    User* toUser;
    double amount;
public:
    Balance(User* fromUser,User* toUser,double amount){
        this->fromUser=fromUser;
        this->toUser=toUser;
        this->amount=amount;
    }

    User* getFromUser() const{
        return fromUser;
    }

    User* getToUser() const{
        return toUser;
    }

    double getAmount() const{
        return amount;
    }

    void settleBalance(double paidAmount){
        amount-=paidAmount;
    }
    void updateBalance(double newAmount){
        amount+=newAmount;
    }
};

class SplitStrategy{
public:
    virtual vector<Split*> calculateSplits(double totalAmount,const vector<User*>&users,const vector<double>&values) = 0;
    virtual ~SplitStrategy() = default;

};

class EqualSplitStrategy: public SplitStrategy{
public:
    vector<Split*> calculateSplits(double totalAmount,const vector<User*>&users,const vector<double>&values) override{
        
        vector<Split*>splits;
        int totalUsers = users.size();
        if(totalUsers<1){
            return {};
        }
        if(totalAmount<0){
            return {};
        }
        for(User* user:users){
            Split* x = new Split(user,totalAmount/totalUsers);
            splits.push_back(x);
        }
        return splits;
    }
};

class ExactSplitStrategy: public SplitStrategy{
public:
    vector<Split*> calculateSplits(double totalAmount,const vector<User*>&users,const vector<double>&values) override{
        
        vector<Split*> splits;

        int totalUsers = users.size();

        // Number of users and values must match
        if(totalUsers != values.size()){
            return {};
        }

        double sum = 0;

        // Calculate total of exact amounts
        for(double value : values){
            sum += value;
        }

        // Total of splits must equal expense amount
        if(abs(sum - totalAmount) > 0.0001){
            return {};
        }

        // Create splits
        for(int i = 0; i < totalUsers; i++){
            Split* split = new Split(users[i], values[i]);
            splits.push_back(split);
        }

        return splits;
    }
};

class PercentageSplitStrategy: public SplitStrategy{
public:
    vector<Split*> calculateSplits(double totalAmount,const vector<User*>&users,const vector<double>&values) override{
        int totalUsers = users.size();

        // Number of users and values must match
        if(totalUsers != values.size()){
            return {};
        }

        double sum = 0;

        // Calculate total of exact amounts
        for(double value : values){
            sum += value;
        }
        if(abs(sum - 100.0) > 0.0001){
            return {};
        }
        vector<Split*>splits;
        for(int i=0;i<totalUsers;i++){
            double temp = (values[i]*totalAmount)/100;
            Split* x = new Split(users[i],temp);
            splits.push_back(x);
        }
        return splits;
    }
};

enum class SplitType{
    EQUAL,
    PERCENT,
    EXACT
};

class SplitFactory{
public:
    SplitStrategy* createSplitStrategy(SplitType type){
        if(type==SplitType::EQUAL){
            return new EqualSplitStrategy();
        }else if(type==SplitType::EXACT){
            return new ExactSplitStrategy();
        }else if(type==SplitType::PERCENT){
            return new PercentageSplitStrategy();
        }return nullptr;
    }
};

class BalanceService{
private:
    vector<Balance*> balances;

public:
    vector<Balance*> getBalances() const{
        return balances;
    }
    void addOrUpdateBalance(
        User* fromUser,
        User* toUser,
        double amount
    ){
        for(int i = 0; i < balances.size(); i++){

            Balance* balance = balances[i];

            // Case 1: Same direction
            // A -> B 100
            // A -> B 50
            // A -> B 150
            if(fromUser == balance->getFromUser() &&
               toUser == balance->getToUser()){

                balance->updateBalance(amount);
                return;
            }

            // Case 2: Reverse direction
            // Existing: A -> B
            // New:      B -> A
            if(fromUser == balance->getToUser() &&
               toUser == balance->getFromUser()){

                double existingAmount = balance->getAmount();

                // Existing balance is greater
                // A -> B 300
                // B -> A 100
                // Result: A -> B 200
                if(existingAmount > amount){
                    balance->settleBalance(amount);
                    return;
                }

                // Both completely cancel
                // A -> B 300
                // B -> A 300
                // Result: nothing
                else if(existingAmount == amount){
                    delete balance;
                    balances.erase(balances.begin() + i);
                    return;
                }

                // New reverse balance is greater
                // A -> B 300
                // B -> A 500
                // Result: B -> A 200
                else{
                    double remaining = amount - existingAmount;

                    delete balance;
                    balances.erase(balances.begin() + i);

                    Balance* newBalance =
                        new Balance(fromUser, toUser, remaining);

                    balances.push_back(newBalance);

                    return;
                }
            }
        }

        // No existing balance between these users
        Balance* balance = new Balance(fromUser, toUser, amount);
        balances.push_back(balance);
    }
};


class ExpenseService{
private:
    BalanceService* balanceService;

public:
    ExpenseService(BalanceService* balanceService){
        this->balanceService=balanceService;
    }

    Expense* createExpense(Group* group,SplitType type,string id,double totalAmount,User* paidBy,string description,vector<User*>&users,vector<double>&values){
        vector<User*> groupUsers = group->getUsers();
        bool paidByFound = false;

        for(User* groupUser : groupUsers){

            if(groupUser->getUserId() == paidBy->getUserId()){
                paidByFound = true;
                break;
            }
        }

        if(!paidByFound){
            cout << "Payer is not a member of this group" << endl;
            return nullptr;
        }
        // Check that every expense participant belongs to the group
        for(User* pUser : users){

            bool found = false;

            for(User* groupUser : groupUsers){

                if(groupUser->getUserId() == pUser->getUserId()){
                    found = true;
                    break;
                }
            }

            if(!found){
                cout << "User is not a member of this group" << endl;
                return nullptr;
            }
        }
        SplitFactory factory;
        SplitStrategy* strategy = factory.createSplitStrategy(type);
        if(strategy == nullptr){
            cout << "Invalid split type" << endl;
            return nullptr;
        }
        vector<Split*>splits = strategy->calculateSplits(totalAmount,users,values);
        delete strategy;
        if(splits.empty()){
            cout << "Invalid split details" << endl;
            return nullptr;
        }
        Expense* expense = new Expense(id,description,paidBy,totalAmount);
        for(Split* split:splits){
            expense->addSplit(split);
            
            User* user = split->getUser();
            if(user!=paidBy){
                balanceService->addOrUpdateBalance(user,paidBy,split->getAmount());
            }
            
            
        }
        group->addExpense(expense);
        return expense;
    }
};


int main(){

    User* A = new User("u1","A");
    User* B = new User("u2","B");
    User* C = new User("u3","C");
    
    vector<User*>users;
    users.push_back(A);
    users.push_back(B);
    users.push_back(C);
    
    Group* trip = new Group("g1","trip",users);

    BalanceService* bService = new BalanceService();
    ExpenseService* eService = new ExpenseService(bService);

    vector<double>values;
    eService->createExpense(trip,SplitType::EQUAL,"e1",20000,A,"flights",users,values);
    
    for(Balance* balance : bService->getBalances()){
        cout << balance->getFromUser()->getUserName()
            << " owes "
            << balance->getToUser()->getUserName()
            << " : "
            << balance->getAmount()
            << endl;
    }
    
    eService->createExpense(
        trip,
        SplitType::EQUAL,
        "e2",
        9000,
        B,
        "food",
        users,
        values
    );


    cout<<"updated balance sheet"<<endl;

    for(Balance* balance : bService->getBalances()){
        cout << balance->getFromUser()->getUserName()
            << " owes "
            << balance->getToUser()->getUserName()
            << " : "
            << balance->getAmount()
            << endl;
    }
    return 0;
}