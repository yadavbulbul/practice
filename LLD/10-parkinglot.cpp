#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Vehicle;
class ParkingSpot;
class ParkingLot;
class ParkingFloor;
class Ticket;

class ParkingLotService;
class TicketService;

class PricingStrategy;
class PricingStrategyFactory;

enum class VehicleType{
    CAR,
    BIKE,
    TRUCK
};

enum class SpotType{
    CAR,
    BIKE,
    TRUCK
};

enum class TicketStatus{
    ACTIVE,
    CLOSED
};

class Vehicle{
private:
    string number;
    VehicleType type;
public:
    Vehicle(string number,VehicleType type){
        this->number=number;
        this->type=type;
    }
    string getVehicleNumber(){
        return number;
    }
    VehicleType getVehicleType(){
        return type;
    }
};

class ParkingSpot{
private:
    string id;
    SpotType type;
    Vehicle* vehicle;
public:
    ParkingSpot(string id,SpotType type){
        this->type=type;
        this->id=id;
        this->vehicle=nullptr;
    }
    string getSpotId(){
        return id;
    }
    SpotType getSpotType(){
        return type;
    }
    Vehicle* getParkedVehicle(){
        return vehicle;
    }  
    bool isOccupied(){
        return vehicle != nullptr;
    }
    bool parkVehicle(Vehicle* vehicle){
        if(isOccupied()){
            return false;
        }
        this->vehicle=vehicle;
        return true;
    }
    void removeVehicle(){
        this->vehicle=nullptr;
    }
};

class ParkingFloor{
private:
    string number;
    vector<ParkingSpot*>parkingSpots;
public:
    ParkingFloor(string number){
        this->number=number;
    }
    string getFloorNumber(){
        return number;
    }
    void addParkingSpot(ParkingSpot* spot){
        parkingSpots.push_back(spot);
    }
    vector<ParkingSpot*> viewParkingSpots(){
        return parkingSpots;
    }
};

class ParkingLot{
private:
    string id;
    vector<ParkingFloor*>floors;
public:
    ParkingLot(string id){
        this->id=id;
    }
    void addFloor(ParkingFloor* floor){
        floors.push_back(floor);
    }
    vector<ParkingFloor*> viewFloors(){
        return floors;
    }
    string getParkingLotId(){
        return id;
    }
};

class Ticket{
private:
    string id;
    string entryTime;
    string exitTime;
    Vehicle* vehicle;
    ParkingSpot* spot;
    double amount;
    TicketStatus status;
public:
    Ticket(string id,string entryTime,Vehicle* vehicle,ParkingSpot* spot){
        this->id=id;
        this->entryTime=entryTime;
        this->vehicle=vehicle;
        this->spot=spot;
        this->amount=0;
        this->status=TicketStatus::ACTIVE;
    }
    string getId(){
        return id;
    }
    string getEntryTime(){
        return entryTime;
    }
    Vehicle* getVehicle(){
        return vehicle;
    }
    ParkingSpot* getSpot(){
        return spot;
    }
    void setExitTime(string exitTime){
        this->exitTime=exitTime;
    }
    void setAmount(double amount){
        this->amount=amount;
    }
    string getExitTime(){
        return exitTime;
    }
    double getAmount(){
        return amount;
    }
    TicketStatus getTicketStatus(){
        return status;
    }
    void closeTicket(){
        this->status=TicketStatus::CLOSED;
    }
};



class PricingStrategy{
public:
    virtual double calculatePrice(string entryTime, string exitTime) = 0;
    virtual ~PricingStrategy(){}
};
class BikePricingStrategy:public PricingStrategy{
public:
    double calculatePrice(string entryTime, string exitTime)override{
        //temporary logic
        return 120;
    }
};
class CarPricingStrategy:public PricingStrategy{
public:
    double calculatePrice(string entryTime, string exitTime)override{
        return 150;
    }
};
class TruckPricingStrategy:public PricingStrategy{
public:
    double calculatePrice(string entryTime, string exitTime)override{
        return 200;
    }
};

class PricingStrategyFactory{
public:
    PricingStrategy* getPricingStrategy(VehicleType type){
        if(type==VehicleType::BIKE){
            return new BikePricingStrategy();
        }
        else if(type==VehicleType::CAR){
            return new CarPricingStrategy();
        }
        else if(type==VehicleType::TRUCK){
            return new TruckPricingStrategy();
        }else{
            return nullptr;
        }
    }
};
class TicketService{
private:
    PricingStrategyFactory* factory;
public:
    TicketService(){
        factory = new PricingStrategyFactory();
    }
    Ticket* createTicket(Vehicle* vehicle,ParkingSpot* spot){
        Ticket* ticket = new Ticket("t1","20:00",vehicle,spot); 
        return ticket;
    }
    double calculateAmount(Ticket* ticket){
        PricingStrategy* strategy = factory->getPricingStrategy(ticket->getVehicle()->getVehicleType());
        double amount = strategy->calculatePrice(ticket->getEntryTime(),ticket->getExitTime());
        ticket->setAmount(amount);
        return amount;
    }
    
    
};
class ParkingLotService{
private:
    ParkingLot* parkingLot;
    TicketService* ticketService;
public:
    ParkingLotService(ParkingLot* parkingLot,TicketService* ticketService){
        this->parkingLot=parkingLot;
        this->ticketService=ticketService;
    }

    ParkingSpot* findAvailableSpot(VehicleType type){
        vector<ParkingFloor*>floors = parkingLot->viewFloors();
        for(auto floor:floors){
            vector<ParkingSpot*>spots=floor->viewParkingSpots();
            for(auto spot:spots){
                if(!spot->isOccupied()){
                    if(type==VehicleType::BIKE && spot->getSpotType()==SpotType::BIKE){
                        return spot;
                    }
                    else if(type==VehicleType::CAR && spot->getSpotType()==SpotType::CAR){
                        return spot;
                    }
                    else if(type==VehicleType::TRUCK && spot->getSpotType()==SpotType::TRUCK){
                        return spot;
                    }
                }
            }
        }
        return nullptr;

    }
    Ticket* parkVehicle(Vehicle* vehicle){
        ParkingSpot* spot = findAvailableSpot(vehicle->getVehicleType());

        if(spot == nullptr){
            return nullptr;
        }

        spot->parkVehicle(vehicle);

        Ticket* ticket = ticketService->createTicket(vehicle, spot);

        return ticket;
    }
    double removeVehicle(Ticket* ticket){
        ticket->setExitTime("22:00");

        double amount = ticketService->calculateAmount(ticket);
        ParkingSpot* spot = ticket->getSpot();

        spot->removeVehicle();

        ticket->closeTicket();

        return amount;
    }
};

int main(){

    ParkingLot* parkingLot = new ParkingLot("P1");

    ParkingFloor* floor1 = new ParkingFloor("F1");

    ParkingSpot* carSpot1 =
        new ParkingSpot("S1", SpotType::CAR);

    ParkingSpot* bikeSpot1 =
        new ParkingSpot("S2", SpotType::BIKE);

    floor1->addParkingSpot(carSpot1);
    floor1->addParkingSpot(bikeSpot1);

    parkingLot->addFloor(floor1);

    TicketService* ticketService =
        new TicketService();

    ParkingLotService* parkingLotService =
        new ParkingLotService(
            parkingLot,
            ticketService
        );

    Vehicle* car =
        new Vehicle("DL01AB1234", VehicleType::CAR);

    Ticket* ticket =
        parkingLotService->parkVehicle(car);

    if(ticket != nullptr){
        cout << "Vehicle parked successfully\n";
        cout << "Ticket ID: " << ticket->getId() << endl;
    }

    double amount =
        parkingLotService->removeVehicle(ticket);

    cout << "Amount: " << amount << endl;

    Vehicle* car1 = new Vehicle("NL01AB1234", VehicleType::CAR);

    Ticket* ticket1 = parkingLotService->parkVehicle(car1);

    if(ticket1 != nullptr){
        cout << "Vehicle parked successfully\n";
        cout << "Ticket ID: " << ticket1->getId() << endl;
    }

    double amount1 =parkingLotService->removeVehicle(ticket1);

    cout << "Amount: " << amount1 << endl;

    return 0;
}