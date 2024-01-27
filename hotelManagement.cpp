#include <iostream>
#include <string>
#include <cstring> //cstring helped fix issues of vector original

#define max 100 //prevents exceeding

class Customer { //class customer with customer detail strings, float for adv, and int for id
public:
    std::string name;
    std::string address;
    std::string phone;
    std::string from_date;
    std::string to_date;
    float payment_advance;
    int booking_id;
};

class Room { //class room for room details, status, and creates array for rooms and keeps count
public:
    char type;
    char stype;
    char ac;
    int roomNumber;
    int rent;
    int status;
    static int count; //uses static count to keep track of # of rooms
    static Room rooms[max]; //array for rooms stored in system

    Room() : status(0) {} //constructor to initialize status for rooms

    Customer cust; //used for customer detail calls and displays

    //uses int for search with room #
    static Room addRoom(int);
    void searchRoom(int);
    void deleteRoom(int);
    static void displayRoom(const Room&);
};

int Room::count = 0; //initializes static count
Room Room::rooms[max]; //initializes static array

void manageRooms() {
    int opt, rno, i, flag = 0; //option, room #, flag for t/f
    do {
        std::cout << "\n### Manage Rooms ###";
        std::cout << "\n1. Add Room";
        std::cout << "\n2. Search Room";
        std::cout << "\n3. Delete Room";
        std::cout << "\n4. Back to Main Menu";
        std::cout << "\n\nEnter Option: ";
        std::cin >> opt; //takes in option for menu

        //switch case for room management menu
        switch (opt) {
            case 1:
                std::cout << "\nEnter Room Number: ";
                std::cin >> rno; //takes in room #
                i = 0;
                for (i = 0; i < Room::count; i++) {
                    if (Room::rooms[i].roomNumber == rno) { //room # to array
                        flag = 1; //flag to 1
                    }
                }
                if (flag == 1) {
                    std::cout << "\nRoom Number is Present.\nPlease enter a unique Number";
                    flag = 0; //if room already exists
                } else {
                    Room::rooms[Room::count] = Room::addRoom(rno); //adds room through function call
                }
                break;

            case 2:
                std::cout << "\nEnter room number: ";
                std::cin >> rno;
                Room::rooms[0].searchRoom(rno); //searches by room # through function call
                break;

            case 3:
                std::cout << "\nEnter room number to delete: ";
                std::cin >> rno;
                Room::rooms[0].deleteRoom(rno); //removes from array by room # through function call
                break;

            case 4:
                //used to go back to the main menu
                return;

            default:
                std::cout << "\nPlease Enter the correct option";
                break; //if incorrect input
        }
    } while (true);
}


Room Room::addRoom(int rno) { //addRoom function for room details
    Room room;
    room.roomNumber = rno;
    std::cout << "\nType AC/Non-AC (A/N) : ";
    std::cin >> room.ac;
    std::cout << "\nType Comfort (S/N) : ";
    std::cin >> room.type;
    std::cout << "\nType Size (B/S) : ";
    std::cin >> room.stype;
    std::cout << "\nDaily Rent : ";
    std::cin >> room.rent;
    ++Room::count; //updates static count
    Room::rooms[Room::count - 1] = room; //adds new room to array
    std::cout << "\n Room Added Successfully!";
    return room;
}

void Room::searchRoom(int rno) { //searches and displays room details if present
    int i, found = 0;
    for (i = 0; i < Room::count; i++) {
        if (Room::rooms[i].roomNumber == rno) {
            found = 1;
            break;
        }
    }

    if (found == 1) {
        std::cout << "Room Details\n";
        if (Room::rooms[i].status == 1) { //for reserved or open
            std::cout << "\nRoom is Reserved";
        } else {
            std::cout << "\nRoom is available";
        }
        displayRoom(Room::rooms[i]);
    } else {
        std::cout << "\nRoom not found"; //incorrect input
    }
}

void Room::deleteRoom(int rno) { //delets room from array if present through input rno
    int i, found = 0;
    for (i = 0; i < Room::count; i++) {
        if (Room::rooms[i].roomNumber == rno) {
            found = 1;
            break;
        }
    }
    if (found == 1) {
        //shifts remaining rooms to fill gap
        for (int j = i; j < Room::count - 1; j++) {
            Room::rooms[j] = Room::rooms[j + 1];
        }
        --Room::count; //updates static count
        std::cout << "\nRoom Deleted Successfully!";
    } else {
        std::cout << "\nRoom not found";
    }
}

void Room::displayRoom(const Room &tempRoom) { //displays room details using tempRoom
    std::cout << "\nRoom Number: \t" << tempRoom.roomNumber;
    std::cout << "\nType AC/Non-AC (A/N) " << tempRoom.ac;
    std::cout << "\nType Comfort (S/N) " << tempRoom.type;
    std::cout << "\nType Size (B/S) " << tempRoom.stype;
    std::cout << "\nRent: " << tempRoom.rent;
}

class HotelMgnt : protected Room { //hm class inheriting from room
private:

public: //public void functions for management system
    void checkIn();
    void getAvailRoom();
    void searchCustomer(const char *);
    void checkOut(int);
    void guestSummaryReport();
};

void HotelMgnt::guestSummaryReport() {
    if (Room::count == 0) { //for if none entered (first option choice)
        std::cout << "\n No Guest in Hotel !!";
    }
    for (int i = 0; i < Room::count; i++) { //if guest ecists, displays details entered from check-in
        if (Room::rooms[i].status == 1) {
            std::cout << "\n Customer First Name : " << Room::rooms[i].cust.name;
            std::cout << "\n Room Number : " << Room::rooms[i].roomNumber;
            std::cout << "\n Address (only city) : " << Room::rooms[i].cust.address;
            std::cout << "\n Phone : " << Room::rooms[i].cust.phone;
            std::cout << "\n---------------------------------------";
        }
    }
}

void HotelMgnt::checkIn() { //checks in guest to room
    int i, found = 0, rno;

    Room room;
    std::cout << "\nEnter Room number : ";
    std::cin >> rno;
    for (i = 0; i < Room::count; i++) {
        if (Room::rooms[i].roomNumber == rno) {
            found = 1;
            break;
        }
    }

    if (found == 1) {
        if (Room::rooms[i].status == 1) { //if room taken by another guest
            std::cout << "\nRoom is already Booked";
            return;
        }

        std::cout << "\nEnter booking id: "; //id assigned to customer
        std::cin >> Room::rooms[i].cust.booking_id;

        std::cout << "\nEnter Customer Name (First Name): ";
        std::cin >> Room::rooms[i].cust.name; //name assigned

        std::cout << "\nEnter Address (only city): ";
        std::cin >> Room::rooms[i].cust.address; //city assigned

        std::cout << "\nEnter Phone: ";
        std::cin >> Room::rooms[i].cust.phone; //phone assigned

        std::cout << "\nEnter From Date: ";
        std::cin >> Room::rooms[i].cust.from_date; 
        //dates staying (used in calcuating total bill at end)
        std::cout << "\nEnter to  Date: ";
        std::cin >> Room::rooms[i].cust.to_date;

        std::cout << "\nEnter Advance Payment: ";
        std::cin >> Room::rooms[i].cust.payment_advance; //takes in and deducts advance from total bill

        Room::rooms[i].status = 1; //updates roo status to occupied

        std::cout << "\n Customer Checked-in Successfully..";
    }
}

void HotelMgnt::getAvailRoom() { //used to display the rooms that have been entered and aren't taken
    int i, found = 0;
    for (i = 0; i < Room::count; i++) {
        if (Room::rooms[i].status == 0) { //relies on room status
            Room::displayRoom(Room::rooms[i]);
            std::cout << "\n\nPress enter for next room";
            found = 1;
        }
    }
    if (found == 0) { //if all taken
        std::cout << "\nAll rooms are reserved";
    }
}

void HotelMgnt::searchCustomer(const char *pname) { //searched customer using ptr
    int i, found = 0;
    for (i = 0; i < Room::count; i++) {
        if (Room::rooms[i].status == 1 && strcmp(Room::rooms[i].cust.name.c_str(), pname) == 0) {
            //string comparison to see if matches
            std::cout << "\nCustomer Name: " << Room::rooms[i].cust.name;
            std::cout << "\nRoom Number: " << Room::rooms[i].roomNumber;
            std::cout << "\nAddress: " << Room::rooms[i].cust.address;
            std::cout << "\nPhone Number: " << Room::rooms[i].cust.phone;
            std::cout << "\n\nPress enter for next record\n";
            //presents customer details entered from check-in prompt
            found = 1;
        }
    }
    if (found == 0) { //person not entered or incorrect name input
        std::cout << "\nPerson not found.\n";
    }
}

void HotelMgnt::checkOut(int roomNum) { //used to check out guest and displays $
    int i, found = 0, days;
    float billAmount = 0; //initializes bill
    for (i = 0; i < Room::count; i++) {
        if (Room::rooms[i].status == 1 && Room::rooms[i].roomNumber == roomNum) {
            found = 1;
            break;
        }
    }

    if (found == 1) {
        std::cout << "\nEnter Number of Days:\t";
        std::cin >> days;
        billAmount = days * Room::rooms[i].rent; //calcs bill based on days and rent

        std::cout << "\n\t######## CheckOut Details ########\n";
        std::cout << "\nCustomer Name : " << Room::rooms[i].cust.name;
        std::cout << "\nRoom Number : " << Room::rooms[i].roomNumber;
        std::cout << "\nAddress : " << Room::rooms[i].cust.address;
        std::cout << "\nPhone : " << Room::rooms[i].cust.phone;
        std::cout << "\nTotal Amount Due : " << billAmount << " /"; //displays total before adv added
        std::cout << "\nAdvance Paid: " << Room::rooms[i].cust.payment_advance << " /";
        //outputs the total payable bill after deducting the advance payment from total amount
        std::cout << "\n*** Total Payable: " << billAmount - Room::rooms[i].cust.payment_advance << "/ only";

        Room::rooms[i].status = 0; //updates room status to unoccupied
    }
}

int main() {
    int opt, rno;
    char pname[100]; //char name array
    HotelMgnt hm; //used to call in hm class functions

    do { //do while statement for main menu
        std::cout << "######## Hotel Management #########\n";
        std::cout << "\n1. Manage Rooms";
        std::cout << "\n2. Check-In Room";
        std::cout << "\n3. Available Rooms";
        std::cout << "\n4. Search Customer";
        std::cout << "\n5. Check-Out Room";
        std::cout << "\n6. Guest Summary Report";
        std::cout << "\n7. Exit";
        std::cout << "\n\nEnter Option: ";
        std::cin >> opt;

        switch (opt) {
            case 1:
                manageRooms(); //calls manage rooms menu and associated functions
                break;

            case 2:
                if (Room::count == 0) { //if no rooms added upon startup
                    std::cout << "\nRooms data is not available.\nPlease add the rooms first.";
                } else {
                    hm.checkIn(); //prompts check-in if rooms have been entered
                }
                break;

            case 3:
                if (Room::count == 0) {
                    std::cout << "\nRooms data is not available.\nPlease add the rooms first.";
                } else {
                    hm.getAvailRoom(); //displays avail rooms
                }
                break;

            case 4:
                if (Room::count == 0) { 
                    std::cout << "\nRooms are not available.\nPlease add the rooms first.";
                } else {
                    std::cout << "Enter Customer Name: ";
                    std::cin >> pname; //takes in customer name
                    hm.searchCustomer(pname); //for search opt
                }
                break;

            case 5:
                if (Room::count == 0) {
                    std::cout << "\nRooms are not available.\nPlease add the rooms first.";
                } else {
                    std::cout << "Enter Room Number : ";
                    std::cin >> rno; //takes in room #
                    hm.checkOut(rno); //used to see who is checking out and what room
                }
                break;

            case 6:
                hm.guestSummaryReport(); //displays guest details and report
                break;

            case 7: //exits hm system
                std::cout << "\nTHANK YOU! FOR USING SOFTWARE\n";
                break;

            default: //if proper input not provided
                std::cout << "\nPlease Enter correct option";
                break;
        }
    } while (opt != 7); //so long as 7 not entered, repeats

    return 0;
}
