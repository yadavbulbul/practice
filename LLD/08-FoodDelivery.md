```mermaid
classDiagram

    class Address {
        -string city
        -string street
    }

    class Customer {
        -string id
        -string name
        -Address* address
        -string phoneNumber
        -bool isPrimeMember
    }

    class Restaurant {
        -string id
        -string name
        -Address* address
        -Menu* menu
        -string openingTime
        -string closingTime
        +acceptOrder() bool
    }

    class Menu {
        -vector~FoodItem*~ menuItems
        +addFoodItem(FoodItem*)
        +getMenu()
        +displayMenu()
    }

    class FoodItem {
        -string id
        -string name
        -double price
        -int quantityAvailable
        +getId()
        +getName()
        +getPrice()
        +getQuantityAvailable()
        +reduceQuantity(int)
    }

    class Cart {
        -vector~CartItem*~ cartItems
        -Restaurant* restaurant
        +addItem(FoodItem*, Restaurant*, int)
        +getItems()
        +getRestaurant()
        +clear()
    }

    class CartItem {
        -FoodItem* foodItem
        -int quantity
        +getFoodItem()
        +getQuantity()
    }

    class Order {
        -string id
        -Customer* customer
        -Restaurant* restaurant
        -vector~OrderItem*~ orderItems
        -DeliveryPartner* deliveryPartner
        -Payment* payment
        -OrderStatus status
        +addOrderItem(OrderItem*)
        +calculateTotal()
        +confirmOrder()
        +startPreparing()
        +outForDelivery()
        +markDelivered()
        +cancelOrder()
        +assignDeliveryPartner(DeliveryPartner*)
        +setPayment(Payment*)
    }

    class OrderItem {
        -FoodItem* foodItem
        -int quantity
        -double price
        +getFoodItem()
        +getQuantity()
        +getPrice()
    }

    class DeliveryPartner {
        -string id
        -string name
        -string phoneNumber
        -bool availability
        -string currentLocation
        +checkAvailability()
        +setAvailability(bool)
    }

    class DeliveryService {
        -vector~DeliveryPartner*~ partners
        +addDeliveryPartner(DeliveryPartner*)
        +findAvailablePartner()
    }

    class Payment {
        -string id
        -Order* order
        -double amount
        -PaymentStatus status
        -string transactionId
        -PaymentStrategy* strategy
        +processPayment()
    }

    class PaymentStrategy {
        <<interface>>
        +pay(double) bool
    }

    class UPIPaymentStrategy {
        +pay(double) bool
    }

    class CardPaymentStrategy {
        +pay(double) bool
    }

    class CODPaymentStrategy {
        +pay(double) bool
    }

    class PaymentFactory {
        +createPayment(PaymentType) PaymentStrategy*
    }

    class OrderService {
        -DeliveryService* deliveryService
        +placeOrder(Customer*, Restaurant*, Cart*, PaymentType)
    }

    class OrderStatus {
        <<enumeration>>
        PLACED
        CONFIRMED
        PREPARING
        OUT_FOR_DELIVERY
        DELIVERED
        CANCELLED
    }

    class PaymentStatus {
        <<enumeration>>
        PENDING
        SUCCESS
        FAILED
    }

    class PaymentType {
        <<enumeration>>
        UPI
        CARD
        COD
    }

    Customer "1" --> "1" Address
    Customer "1" --> "1" Cart
    Customer "1" --> "0..*" Order

    Restaurant "1" --> "1" Address
    Restaurant "1" --> "1" Menu

    Menu "1" --> "0..*" FoodItem

    Cart "1" --> "0..*" CartItem
    Cart "1" --> "1" Restaurant
    CartItem "*" --> "1" FoodItem

    Order "1" --> "1" Customer
    Order "1" --> "1" Restaurant
    Order "1" --> "1..*" OrderItem
    OrderItem "*" --> "1" FoodItem

    Order "1" --> "0..1" Payment
    Order "1" --> "0..1" DeliveryPartner

    DeliveryService "1" --> "*" DeliveryPartner
    OrderService "1" --> "1" DeliveryService

    Payment "*" --> "1" PaymentStrategy

    PaymentStrategy <|.. UPIPaymentStrategy
    PaymentStrategy <|.. CardPaymentStrategy
    PaymentStrategy <|.. CODPaymentStrategy

    PaymentFactory ..> PaymentStrategy
    PaymentFactory ..> PaymentType

    Order --> OrderStatus
    Payment --> PaymentStatus

    OrderService ..> Order
    OrderService ..> Payment
    OrderService ..> PaymentFactory