```mermaid

classDiagram

    class User {
        -string id
        -string name
        +User(string userId, string userName)
        +string getUserId()
        +string getUserName()
        +void setUserName(string name)
    }

    class Group {
        -string id
        -string name
        -vector~User*~ users
        -vector~Expense*~ expenses
        +Group(string id, string name, vector~User*~ users, vector~Expense*~ expenses)
        +string getId()
        +string getName()
        +vector~User*~ getUsers()
        +vector~Expense*~ getExpenses()
        +void addUser(User* user)
        +void addExpense(Expense* expense)
    }

    class Expense {
        -string id
        -string description
        -User* paidBy
        -vector~Split*~ splits
        -double totalAmount
        +Expense(string id, string description, User* paidBy, double totalAmount)
        +string getId()
        +string getDescription()
        +User* getPaidBy()
        +double getTotalAmount()
        +vector~Split*~ getSplits()
        +void addSplit(Split* split)
    }

    class Split {
        -double amount
        -User* user
        +Split(User* user, double amount)
        +User* getUser()
        +double getAmount()
    }

    class Balance {
        -User* fromUser
        -User* toUser
        -double amount
        +Balance(User* fromUser, User* toUser, double amount)
        +User* getFromUser()
        +User* getToUser()
        +double getAmount()
        +void settleBalance(double paidAmount)
        +void updateBalance(double newAmount)
    }

    class SplitStrategy {
        <<abstract>>
        +calculateSplits(double totalAmount, vector~User*~ users, vector~double~ values)* vector~Split*~
    }

    class EqualSplitStrategy {
        +calculateSplits(double totalAmount, vector~User*~ users, vector~double~ values) vector~Split*~
    }

    class ExactSplitStrategy {
        +calculateSplits(double totalAmount, vector~User*~ users, vector~double~ values) vector~Split*~
    }

    class PercentageSplitStrategy {
        +calculateSplits(double totalAmount, vector~User*~ users, vector~double~ values) vector~Split*~
    }

    class SplitFactory {
        +createSplitStrategy(SplitType type) SplitStrategy*
    }

    class ExpenseService {
        -BalanceService* balanceService
        +ExpenseService(BalanceService* balanceService)
        +Expense* createExpense(SplitType type, string id, double totalAmount, User* paidBy, string description, vector~User*~ users, vector~double~ values)
    }

    class BalanceService {
        -vector~Balance*~ balances
        +void addOrUpdateBalance(User* fromUser, User* toUser, double amount)
    }

    class SplitwiseService {
        -vector~User*~ users
        -vector~Group*~ groups
        -ExpenseService* expenseService
        +SplitwiseService(ExpenseService* expenseService)
        +void addUser(User* user)
        +Group* createGroup(string id, string name)
        +void addUserToGroup(Group* group, User* user)
        +Expense* addExpense(Group* group, SplitType type, string id, double amount, User* paidBy, string description, vector~User*~ users, vector~double~ values)
        +void showBalances()
        +void settleUp(User* fromUser, User* toUser, double amount)
    }

    class SplitType {
        <<enumeration>>
        EQUAL
        PERCENT
        EXACT
    }


    SplitStrategy <|-- EqualSplitStrategy
    SplitStrategy <|-- ExactSplitStrategy
    SplitStrategy <|-- PercentageSplitStrategy

    SplitFactory ..> SplitStrategy : creates

    ExpenseService --> SplitFactory : uses
    ExpenseService --> BalanceService : uses

    Expense --> User : paidBy
    Expense "1" *-- "many" Split : contains

    Split --> User : belongs to

    Group "1" o-- "many" User : members
    Group "1" o-- "many" Expense : contains

    Balance --> User : fromUser
    Balance --> User : toUser

    SplitwiseService --> User : manages
    SplitwiseService --> Group : manages
    SplitwiseService --> ExpenseService : uses