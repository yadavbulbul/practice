/*
Design a food delivery application like Zomato. Customers should be able to browse restaurants, select food items, place orders and make payments. Restaurants should be able to accept and prepare orders, and delivery partners should deliver them.

Customer
- id
- name
- address
- phoneNumber
- isPrimeMember


Restaurant
- id
- name
- menu
- address
- openingTime
- closingTime


Menu
- foodItems


FoodItem
- id
- name
- price
- quantityAvailable


Cart
- cartItems


CartItem
- foodItem
- quantity


Order
- id
- customer
- restaurant
- orderItems
- bill
- deliveryPartner
- status
- orderDateTime


OrderItem
- foodItem
- quantity
- price


Bill
- orderDetails
- priceToPay


DeliveryPartner
- id
- name
- phoneNumber
- availability
- currentLocation


┌──────────────────┐
│    Customer      │
├──────────────────┤
│ id               │
│ name             │
│ address          │
│ phoneNumber      │
│ isPrimeMember    │
└────────┬─────────┘
         │
         │ places
         ▼
┌──────────────────┐
│      Order       │
├──────────────────┤
│ id               │
│ customer         │
│ restaurant       │
│ orderItems       │
│ bill             │
│ deliveryPartner  │
│ status           │
│ orderDateTime    │
└──────┬─────┬─────┘
       │     │
       │     └─────────────────────┐
       │                           │
       ▼                           ▼
┌──────────────┐          ┌──────────────────┐
│  OrderItem   │          │      Bill        │
├──────────────┤          ├──────────────────┤
│ foodItem     │          │ orderDetails     │
│ quantity     │          │ priceToPay       │
│ price        │          └──────────────────┘
└──────┬───────┘
       │
       ▼
┌──────────────────┐
│    FoodItem      │
├──────────────────┤
│ id               │
│ name             │
│ price            │
│ quantityAvailable│
└──────────────────┘


┌──────────────────┐
│    Restaurant    │
├──────────────────┤
│ id               │
│ name             │
│ menu             │
│ address          │
│ openingTime      │
│ closingTime      │
└────────┬─────────┘
         │
         ▼
┌──────────────────┐
│      Menu        │
├──────────────────┤
│ foodItems        │
└────────┬─────────┘
         │
         ▼
     FoodItem


┌──────────────────┐
│       Cart       │
├──────────────────┤
│ cartItems        │
└────────┬─────────┘
         │
         ▼
┌──────────────────┐
│    CartItem      │
├──────────────────┤
│ foodItem         │
│ quantity         │
└──────────────────┘


┌──────────────────┐
│ DeliveryPartner  │
├──────────────────┤
│ id               │
│ name             │
│ phoneNumber      │
│ availability     │
│ currentLocation  │
└──────────────────┘

Customer
    → selects restaurant
    → adds items to cart

Restaurant
    → manages menu
    → accepts/rejects order

Cart
    → addItem()
    → removeItem()
    → checkout()

Order
    → contains OrderItems
    → calculateTotal()
    → tracks status

Bill
    → represents payment amount/details

DeliveryPartner
    → accepts delivery
    → picks up order
    → delivers order
________________________

methods i'd keep in these classes

Restaurant
+ addFoodItem()
+ removeFoodItem()
+ updateFoodItem()
+ displayMenu()
+ acceptOrder()
+ rejectOrder()


Cart
+ addItem()
+ removeItem()
+ displayItems()
+ checkout()


Order
+ calculateTotal()
+ updateStatus()
*/

#include<iostream>
using namespace std;

enum class PaymentType{
    UPI,
    CARD,
    COD
};

class PaymentStrategy{
public:
    virtual bool pay(double amount) = 0;
    virtual ~PaymentStrategy() = default;
};

class UPIPaymentStrategy:public PaymentStrategy{
public:
    bool pay(double amount)override{
        cout<<"Payment of Rs "<<amount<<" successful via UPI."<<endl;
        return true;
    }
};

class CardPaymentStrategy:public PaymentStrategy{
public:
    bool pay(double amount)override{
        cout<<"Payment of Rs "<<amount<<" successful via Card."<<endl;
        return true;
    }
};

class CODPaymentStrategy:public PaymentStrategy{
public:
    bool pay(double amount)override{
        cout<<"Pay Rs "<<amount<<" upon receiving the order."<<endl;
        return true;
    }
};

class PaymentFactory{
public:
    static PaymentStrategy* createPayment(PaymentType type){
        if(type==PaymentType::UPI){
            return new UPIPaymentStrategy();
        }else if(type==PaymentType::CARD){
            return new CardPaymentStrategy();
        }else if(type==PaymentType::COD){
            return new CODPaymentStrategy();
        }else{
            return nullptr;
        }
    }
};

int main() {
    // create payment using factory
    PaymentStrategy* payment = PaymentFactory::createPayment(PaymentType::CARD);

    // call pay()
    payment->pay(1234);
    // delete payment
    delete payment;
}