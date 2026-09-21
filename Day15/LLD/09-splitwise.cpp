#include<iostream>
#include<string>
#include<vector>
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
    Group(string id, string name, vector<User*>users, vector<Expense*>expenses){
        this->id=id;
        this->name=name;
        this->users=users;
        this->expenses=expenses;
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
        vector<Split*>splits;
        int totalUsers = users.size();
        for(int i=0;i<totalUsers;i++){
            Split* x = new Split(users[i],values[i]);
            splits.push_back(x);
        }
        return splits;
    }
};

class PercentageSplitStrategy: public SplitStrategy{
public:
    vector<Split*> calculateSplits(double totalAmount,const vector<User*>&users,const vector<double>&values) override{
        vector<Split*>splits;
        int totalUsers = users.size();
        for(int i=0;i<totalUsers;i++){
            double temp = (values[i]*totalAmount)/100;
            Split* x = new Split(users[i],temp);
            splits.push_back(x);
        }
        return splits;
    }
};

class ExpenseService{
private:
    SplitStrategy* splitStrategy;
    BalanceService* balanceService;

public:
    ExpenseService(SplitStrategy* splitStrategy, BalanceService* balanceService){
        this->splitStrategy=splitStrategy;
        this->balanceService=balanceService;
    }

    Expense* createExpense(string id,double totalAmount,User* paidBy,string description,vector<User*>&users,vector<double>&values){
        vector<Split*>splits = splitStrategy->calculateSplits(totalAmount,users,values);
        Expense* expense = new Expense(id,description,paidBy,totalAmount);
        for(Split* split:splits){
            expense->addSplit(split);
        }
        return expense;
    }
};

class BalanceService{
private:
    vector<Balance*> balances;

public:

    void addOrUpdateBalance(
        User* fromUser,
        User* toUser,
        double amount
    ){
        for(Balance* balance:balances){
            if(fromUser==balance->getFromUser() && toUser==balance->getToUser()){
                balance->updateBalance(amount);
                return;
            }
        }
        Balance* balance = new Balance(fromUser,toUser, amount);
        balances.push_back(balance);
    }
};