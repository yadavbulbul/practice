#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Forward declarations
class Restaurant;
class Customer;
class Order;
class Payment;
class PaymentStrategy;
class DeliveryPartner;


// ============================================================
// Address
// ============================================================

class Address {
private:
    string city;
    string street;

public:
    Address(string city, string street) {
        this->city = city;
        this->street = street;
    }

    string getCity() {
        return city;
    }

    string getStreet() {
        return street;
    }
};


// ============================================================
// FoodItem
// ============================================================

class FoodItem {
private:
    string id;
    string name;
    double price;
    int quantityAvailable;

public:
    FoodItem(string id, string name, double price, int quantityAvailable) {
        this->id = id;
        this->name = name;
        this->price = price;
        this->quantityAvailable = quantityAvailable;
    }

    string getId() {
        return id;
    }

    string getName() {
        return name;
    }

    double getPrice() {
        return price;
    }

    int getQuantityAvailable() {
        return quantityAvailable;
    }

    void reduceQuantity(int quantity) {
        if (quantity <= quantityAvailable) {
            quantityAvailable -= quantity;
        }
    }
};


// ============================================================
// Menu
// ============================================================

class Menu {
private:
    vector<FoodItem*> menuItems;

public:
    void addFoodItem(FoodItem* item) {
        menuItems.push_back(item);
    }

    vector<FoodItem*>& getMenu() {
        return menuItems;
    }

    void displayMenu() {
        for (FoodItem* item : menuItems) {
            cout << item->getName()
                 << " - Rs. "
                 << item->getPrice()
                 << endl;
        }
    }
};


// ============================================================
// Restaurant
// ============================================================

class Restaurant {
private:
    string id;
    string name;
    Address* address;
    Menu* menu;
    string openingTime;
    string closingTime;

public:
    Restaurant(
        string id,
        string name,
        Address* address,
        Menu* menu,
        string openingTime,
        string closingTime
    ) {
        this->id = id;
        this->name = name;
        this->address = address;
        this->menu = menu;
        this->openingTime = openingTime;
        this->closingTime = closingTime;
    }

    Menu* getMenu() {
        return menu;
    }

    string getName() {
        return name;
    }

    // Restaurant gets a chance to accept/reject the order
    bool acceptOrder() {
        // In real system:
        // check restaurant status, capacity, opening hours, etc.
        return true;
    }
};


// ============================================================
// CartItem
// ============================================================

class CartItem {
private:
    FoodItem* foodItem;
    int quantity;

public:
    CartItem(FoodItem* foodItem, int quantity) {
        this->foodItem = foodItem;
        this->quantity = quantity;
    }

    FoodItem* getFoodItem() {
        return foodItem;
    }

    int getQuantity() {
        return quantity;
    }
};


// ============================================================
// Cart
// ============================================================

class Cart {
private:
    vector<CartItem*> cartItems;

    // A cart can contain items from only ONE restaurant
    Restaurant* restaurant;

public:
    Cart() {
        restaurant = nullptr;
    }

    void addItem(
        FoodItem* foodItem,
        Restaurant* restaurant,
        int quantity
    ) {
        // First item decides the restaurant
        if (this->restaurant == nullptr) {
            this->restaurant = restaurant;
        }

        // Don't allow items from another restaurant
        if (this->restaurant != restaurant) {
            cout << "Cannot add item from another restaurant."
                 << endl;
            return;
        }

        cartItems.push_back(
            new CartItem(foodItem, quantity)
        );
    }

    vector<CartItem*>& getItems() {
        return cartItems;
    }

    Restaurant* getRestaurant() {
        return restaurant;
    }

    // Clear cart after successful checkout
    void clear() {
        cartItems.clear();
        restaurant = nullptr;
    }
};


// ============================================================
// Customer
// ============================================================

class Customer {
private:
    string id;
    string name;
    Address* address;
    string phoneNumber;
    bool isPrimeMember;

public:
    Customer(
        string id,
        string name,
        Address* address,
        string phoneNumber,
        bool isPrimeMember
    ) {
        this->id = id;
        this->name = name;
        this->address = address;
        this->phoneNumber = phoneNumber;
        this->isPrimeMember = isPrimeMember;
    }

    string getName() {
        return name;
    }
};


// ============================================================
// OrderItem
// ============================================================

class OrderItem {
private:
    FoodItem* foodItem;
    int quantity;

    // Important:
    // Store price at the time order is placed.
    double price;

public:
    OrderItem(
        FoodItem* foodItem,
        int quantity,
        double price
    ) {
        this->foodItem = foodItem;
        this->quantity = quantity;
        this->price = price;
    }

    FoodItem* getFoodItem() {
        return foodItem;
    }

    int getQuantity() {
        return quantity;
    }

    double getPrice() {
        return price;
    }
};


// ============================================================
// Delivery Partner
// ============================================================

class DeliveryPartner {
private:
    string id;
    string name;
    string phoneNumber;
    bool availability;
    string currentLocation;

public:
    DeliveryPartner(
        string id,
        string name,
        string phoneNumber,
        string currentLocation
    ) {
        this->id = id;
        this->name = name;
        this->phoneNumber = phoneNumber;
        this->currentLocation = currentLocation;
        this->availability = true;
    }

    bool checkAvailability() {
        return availability;
    }

    void setAvailability(bool availability) {
        this->availability = availability;
    }
};


// ============================================================
// Delivery Service
// ============================================================

class DeliveryService {
private:
    vector<DeliveryPartner*> partners;

public:
    void addDeliveryPartner(DeliveryPartner* partner) {
        partners.push_back(partner);
    }

    DeliveryPartner* findAvailablePartner() {

        // Current implementation:
        // return first available partner.
        //
        // Can later be improved to:
        // nearest partner / round robin / least busy etc.

        for (DeliveryPartner* partner : partners) {

            if (partner->checkAvailability()) {
                return partner;
            }
        }

        return nullptr;
    }
};


// ============================================================
// Order Status
// ============================================================

enum class OrderStatus {
    PLACED,
    CONFIRMED,
    PREPARING,
    OUT_FOR_DELIVERY,
    DELIVERED,
    CANCELLED
};


// ============================================================
// Payment Status
// ============================================================

enum class PaymentStatus {
    PENDING,
    SUCCESS,
    FAILED
};


// ============================================================
// Payment Type
// ============================================================

enum class PaymentType {
    UPI,
    CARD,
    COD
};


// ============================================================
// Payment Strategy
// ============================================================

class PaymentStrategy {
public:

    virtual bool pay(double amount) = 0;

    virtual ~PaymentStrategy() = default;
};


// ============================================================
// UPI Payment
// ============================================================

class UPIPaymentStrategy : public PaymentStrategy {
public:

    bool pay(double amount) override {

        cout << "Processing UPI payment: Rs. "
             << amount << endl;

        return true;
    }
};


// ============================================================
// Card Payment
// ============================================================

class CardPaymentStrategy : public PaymentStrategy {
public:

    bool pay(double amount) override {

        cout << "Processing Card payment: Rs. "
             << amount << endl;

        return true;
    }
};


// ============================================================
// COD Payment
// ============================================================

class CODPaymentStrategy : public PaymentStrategy {
public:

    bool pay(double amount) override {

        cout << "COD selected. Amount: Rs. "
             << amount << endl;

        return true;
    }
};


// ============================================================
// Payment Factory
// ============================================================

class PaymentFactory {
public:

    static PaymentStrategy* createPayment(
        PaymentType type
    ) {

        if (type == PaymentType::UPI) {
            return new UPIPaymentStrategy();
        }

        if (type == PaymentType::CARD) {
            return new CardPaymentStrategy();
        }

        if (type == PaymentType::COD) {
            return new CODPaymentStrategy();
        }

        return nullptr;
    }
};


// ============================================================
// Order
// ============================================================

class Order {
private:
    string id;

    Customer* customer;
    Restaurant* restaurant;

    vector<OrderItem*> orderItems;

    DeliveryPartner* deliveryPartner;

    Payment* payment;

    OrderStatus status;

public:

    Order(
        string id,
        Customer* customer,
        Restaurant* restaurant
    ) {
        this->id = id;
        this->customer = customer;
        this->restaurant = restaurant;

        this->deliveryPartner = nullptr;
        this->payment = nullptr;

        this->status = OrderStatus::PLACED;
    }

    void addOrderItem(OrderItem* item) {
        orderItems.push_back(item);
    }

    double calculateTotal() {

        double total = 0;

        for (OrderItem* item : orderItems) {

            total +=
                item->getPrice()
                * item->getQuantity();
        }

        return total;
    }

    // PLACED -> CONFIRMED
    bool confirmOrder() {

        if (status != OrderStatus::PLACED) {
            return false;
        }

        status = OrderStatus::CONFIRMED;

        cout << "Order confirmed." << endl;

        return true;
    }

    // CONFIRMED -> PREPARING
    bool startPreparing() {

        if (status != OrderStatus::CONFIRMED) {
            return false;
        }

        status = OrderStatus::PREPARING;

        cout << "Restaurant is preparing the order."
             << endl;

        return true;
    }

    // PREPARING -> OUT_FOR_DELIVERY
    bool outForDelivery() {

        if (status != OrderStatus::PREPARING) {
            return false;
        }

        status = OrderStatus::OUT_FOR_DELIVERY;

        cout << "Order is out for delivery."
             << endl;

        return true;
    }

    // OUT_FOR_DELIVERY -> DELIVERED
    bool markDelivered() {

        if (status != OrderStatus::OUT_FOR_DELIVERY) {
            return false;
        }

        status = OrderStatus::DELIVERED;

        cout << "Order delivered." << endl;

        return true;
    }

    bool cancelOrder() {

        if (
            status == OrderStatus::DELIVERED ||
            status == OrderStatus::CANCELLED
        ) {
            return false;
        }

        status = OrderStatus::CANCELLED;

        cout << "Order cancelled." << endl;

        return true;
    }

    void assignDeliveryPartner(
        DeliveryPartner* partner
    ) {
        this->deliveryPartner = partner;
    }

    void setPayment(Payment* payment) {
        this->payment = payment;
    }
};


// ============================================================
// Payment
// ============================================================

class Payment {
private:
    string id;

    Order* order;

    double amount;

    PaymentStatus status;

    string transactionId;

    PaymentStrategy* strategy;

public:

    Payment(
        string id,
        Order* order,
        double amount,
        PaymentStrategy* strategy
    ) {
        this->id = id;
        this->order = order;
        this->amount = amount;

        // Initial state
        this->status = PaymentStatus::PENDING;

        this->transactionId = "";

        this->strategy = strategy;
    }

    bool processPayment() {

        bool paymentSuccess =
            strategy->pay(amount);

        if (paymentSuccess) {

            status = PaymentStatus::SUCCESS;

            // Demo transaction ID
            transactionId = "TXN001";

            cout << "Payment successful."
                 << endl;

        } else {

            status = PaymentStatus::FAILED;

            cout << "Payment failed."
                 << endl;
        }

        return paymentSuccess;
    }
};


// ============================================================
// Order Service
// ============================================================

class OrderService {
private:
    DeliveryService* deliveryService;

public:

    OrderService(
        DeliveryService* deliveryService
    ) {
        this->deliveryService = deliveryService;
    }

    Order* placeOrder(
        Customer* customer,
        Restaurant* restaurant,
        Cart* cart,
        PaymentType paymentType
    ) {

        // ----------------------------------------------------
        // 1. Validate cart
        // ----------------------------------------------------

        if (cart->getRestaurant() != restaurant) {

            cout << "Cart belongs to another restaurant."
                 << endl;

            return nullptr;
        }

        if (cart->getItems().empty()) {

            cout << "Cart is empty." << endl;

            return nullptr;
        }


        // ----------------------------------------------------
        // 2. Check inventory
        // ----------------------------------------------------

        for (CartItem* cartItem : cart->getItems()) {

            FoodItem* foodItem =
                cartItem->getFoodItem();

            if (
                foodItem->getQuantityAvailable()
                < cartItem->getQuantity()
            ) {

                cout << "Insufficient quantity for "
                     << foodItem->getName()
                     << endl;

                return nullptr;
            }
        }


        // ----------------------------------------------------
        // 3. Create Order
        // ----------------------------------------------------

        Order* order =
            new Order(
                "ORD001",
                customer,
                restaurant
            );


        // ----------------------------------------------------
        // 4. Convert CartItems -> OrderItems
        // ----------------------------------------------------

        for (CartItem* cartItem : cart->getItems()) {

            FoodItem* foodItem =
                cartItem->getFoodItem();

            int quantity =
                cartItem->getQuantity();

            // Store current price in OrderItem
            // so future price changes don't affect
            // this order.

            OrderItem* orderItem =
                new OrderItem(
                    foodItem,
                    quantity,
                    foodItem->getPrice()
                );

            order->addOrderItem(orderItem);
        }


        // ----------------------------------------------------
        // 5. Calculate total
        // ----------------------------------------------------

        double total =
            order->calculateTotal();

        cout << "Order total: Rs. "
             << total
             << endl;


        // ----------------------------------------------------
        // 6. Restaurant accepts/rejects order
        // ----------------------------------------------------

        if (!restaurant->acceptOrder()) {

            cout << "Restaurant rejected the order."
                 << endl;

            delete order;

            return nullptr;
        }


        // ----------------------------------------------------
        // 7. Create Payment Strategy
        // ----------------------------------------------------

        PaymentStrategy* strategy =
            PaymentFactory::createPayment(
                paymentType
            );

        if (strategy == nullptr) {

            cout << "Invalid payment type."
                 << endl;

            delete order;

            return nullptr;
        }


        // ----------------------------------------------------
        // 8. Create Payment
        // ----------------------------------------------------

        Payment* payment =
            new Payment(
                "PAY001",
                order,
                total,
                strategy
            );

        order->setPayment(payment);


        // ----------------------------------------------------
        // 9. Process Payment
        // ----------------------------------------------------

        if (!payment->processPayment()) {

            cout << "Order cancelled because "
                 << "payment failed."
                 << endl;

            delete payment;
            delete order;

            return nullptr;
        }


        // ----------------------------------------------------
        // 10. Reduce inventory
        // ----------------------------------------------------

        for (CartItem* cartItem : cart->getItems()) {

            cartItem
                ->getFoodItem()
                ->reduceQuantity(
                    cartItem->getQuantity()
                );
        }


        // ----------------------------------------------------
        // 11. Confirm Order
        // ----------------------------------------------------

        order->confirmOrder();


        // ----------------------------------------------------
        // 12. Assign Delivery Partner
        // ----------------------------------------------------

        DeliveryPartner* partner =
            deliveryService
                ->findAvailablePartner();

        if (partner != nullptr) {

            order->assignDeliveryPartner(
                partner
            );

            partner->setAvailability(false);

            cout << "Delivery partner assigned."
                 << endl;

        } else {

            cout << "No delivery partner available."
                 << endl;
        }


        // ----------------------------------------------------
        // 13. Clear Cart
        // ----------------------------------------------------

        cart->clear();

        cout << "Cart cleared." << endl;


        return order;
    }
};


// ============================================================
// Main
// ============================================================

int main() {

    // --------------------------------------------------------
    // Address
    // --------------------------------------------------------

    Address* customerAddress =
        new Address(
            "Delhi",
            "Connaught Place"
        );

    Address* restaurantAddress =
        new Address(
            "Delhi",
            "Rajouri Garden"
        );


    // --------------------------------------------------------
    // Menu + Food Items
    // --------------------------------------------------------

    Menu* menu =
        new Menu();

    FoodItem* pizza =
        new FoodItem(
            "F1",
            "Pizza",
            300,
            10
        );

    FoodItem* pasta =
        new FoodItem(
            "F2",
            "Pasta",
            200,
            5
        );

    menu->addFoodItem(pizza);
    menu->addFoodItem(pasta);


    // --------------------------------------------------------
    // Restaurant
    // --------------------------------------------------------

    Restaurant* restaurant =
        new Restaurant(
            "R1",
            "Domino's",
            restaurantAddress,
            menu,
            "10:00",
            "23:00"
        );


    // --------------------------------------------------------
    // Customer
    // --------------------------------------------------------

    Customer* customer =
        new Customer(
            "C1",
            "Pihu",
            customerAddress,
            "9999999999",
            true
        );


    // --------------------------------------------------------
    // Cart
    // --------------------------------------------------------

    Cart* cart =
        new Cart();

    cart->addItem(
        pizza,
        restaurant,
        2
    );

    cart->addItem(
        pasta,
        restaurant,
        1
    );


    // --------------------------------------------------------
    // Delivery Service
    // --------------------------------------------------------

    DeliveryService* deliveryService =
        new DeliveryService();

    DeliveryPartner* partner =
        new DeliveryPartner(
            "D1",
            "Rahul",
            "8888888888",
            "Delhi"
        );

    deliveryService
        ->addDeliveryPartner(partner);


    // --------------------------------------------------------
    // Order Service
    // --------------------------------------------------------

    OrderService orderService(
        deliveryService
    );


    // --------------------------------------------------------
    // Place Order
    // --------------------------------------------------------

    Order* order =
        orderService.placeOrder(
            customer,
            restaurant,
            cart,
            PaymentType::CARD
        );


    if (order != nullptr) {

        cout << "Order placed successfully!"
             << endl;

        // Example lifecycle

        order->startPreparing();

        order->outForDelivery();

        order->markDelivered();
    }


    return 0;
}