#include <iostream>
using namespace std;

/* ===== PERSON & USER ===== */
class Person {
public:
    string email;
    string password;
};

class User : public Person {};

/* ===== BOOKING ===== */
class Booking {
public:
    string guestName;
    string roomType, acType;

    int inDay, inMonth, inYear;
    int outDay, outMonth, outYear;

    int days;
    int roomBill, foodBill, serviceBill, totalBill;
    int roomNo;
    bool active;

    Booking() {
        days = roomBill = foodBill = serviceBill = totalBill = 0;
        roomNo = 0;
        active = false;
    }
};

/* ===== HOTEL ===== */
class Hotel {
private:
    User users[10];
    int userCount = 0;
    bool loggedIn = false;

    Booking bookings[100];
    int bookingCount = 0;
    int nextRoomNo = 1;

    /* EMAIL VALIDATION */
    bool validEmail(string email) {
        string d = "@gmail.com";
        return email.length() > d.length() &&
               email.substr(email.length() - d.length()) == d;
    }

    /* CALCULATE STAY DAYS */
    int calcDays(Booking b) {
        return (b.outDay - b.inDay); // Simple calculation
    }

    int roomPrice(string r, string ac) {
        if (r == "Family")
            return (ac == "AC") ? 4500 : 3500;
        else
            return (ac == "AC") ? 3000 : 2000;
    }

    int findRoom(int r) {
        for (int i = 0; i < bookingCount; i++)
            if (bookings[i].roomNo == r && bookings[i].active)
                return i;
        return -1;
    }

public:
    /* SIGN UP */
    void signUp() {
        User u;
        cout << "Enter Email: ";
        cin >> u.email;

        if (!validEmail(u.email)) {
            cout << "Invalid Email! Only @gmail.com allowed\n";
            return;
        }

        cout << "Enter Password: ";
        cin >> u.password;
        users[userCount++] = u;

        cout << "Signup Successful!\n";
    }

    /* LOGIN */
    void login() {
        string e, p;
        cout << "Email: "; cin >> e;
        cout << "Password: "; cin >> p;

        for (int i = 0; i < userCount; i++) {
            if (users[i].email == e && users[i].password == p) {
                loggedIn = true;
                cout << "Login Successful!\n";
                userMenu();
                return;
            }
        }
        cout << "Invalid Login!\n";
    }

    /* ROOM BOOKING */
    void bookRoom() {
        Booking b;
        cin.ignore();

        cout << "Guest Name: ";
        getline(cin, b.guestName);

        cout << "Check-in Date (DD MM YYYY): ";
        cin >> b.inDay >> b.inMonth >> b.inYear;

        cout << "Check-out Date (DD MM YYYY): ";
        cin >> b.outDay >> b.outMonth >> b.outYear;

        b.days = calcDays(b);

        int r, ac;
        cout << "1. Family  2. Single: ";
        cin >> r;
        b.roomType = (r == 1) ? "Family" : "Single";

        cout << "1. AC  2. Non-AC: ";
        cin >> ac;
        b.acType = (ac == 1) ? "AC" : "Non-AC";

        b.roomBill = b.days * roomPrice(b.roomType, b.acType);
        b.totalBill = b.roomBill;

        b.roomNo = nextRoomNo++;
        b.active = true;

        bookings[bookingCount++] = b;

        cout << "\nRoom Booked Successfully!";
        cout << "\nRoom No: " << b.roomNo;
        cout << "\nStay Days: " << b.days;
        cout << "\nRoom Bill: Rs." << b.roomBill << endl;
    }

    /* FOOD ORDER (7 ITEMS) */
    void foodOrder() {
        int r, ch, qty, bill = 0;
        cout << "Room No: ";
        cin >> r;

        int i = findRoom(r);
        if (i == -1) {
            cout << "Invalid Room!\n";
            return;
        }

        cout << "\n--- FOOD MENU ---";
        cout << "\n1. Biryani (250)";
        cout << "\n2. Karahi (1200)";
        cout << "\n3. Pizza (800)";
        cout << "\n4. Burger (300)";
        cout << "\n5. Fries (200)";
        cout << "\n6. BBQ (900)";
        cout << "\n7. Cold Drink (120)";
        cout << "\nChoice: ";
        cin >> ch;

        cout << "Quantity: ";
        cin >> qty;

        switch (ch) {
        case 1: bill = 250 * qty; break;
        case 2: bill = 1200 * qty; break;
        case 3: bill = 800 * qty; break;
        case 4: bill = 300 * qty; break;
        case 5: bill = 200 * qty; break;
        case 6: bill = 900 * qty; break;
        case 7: bill = 120 * qty; break;
        default: cout << "Invalid Item!\n"; return;
        }

        bookings[i].foodBill += bill;
        bookings[i].totalBill += bill;

        cout << "Food Order Added Successfully!\n";
    }

    /* ROOM SERVICE */
    void roomService() {
        int r, ch, bill = 0;
        cout << "Room No: ";
        cin >> r;

        int i = findRoom(r);
        if (i == -1) {
            cout << "Invalid Room!\n";
            return;
        }

        cout << "\n--- ROOM SERVICE ---";
        cout << "\n1. Laundry (500)";
        cout << "\n2. Cleaning (300)";
        cout << "\n3. Extra Bed (1000)";
        cout << "\nChoice: ";
        cin >> ch;

        if (ch == 1) bill = 500;
        else if (ch == 2) bill = 300;
        else if (ch == 3) bill = 1000;
        else { cout << "Invalid Service!\n"; return; }

        bookings[i].serviceBill += bill;
        bookings[i].totalBill += bill;

        cout << "Room Service Added Successfully!\n";
    }

    /* SHOW TOTAL BILL */
    void showBill() {
        int r;
        cout << "Room No: ";
        cin >> r;

        int i = findRoom(r);
        if (i == -1) {
            cout << "Invalid Room!\n";
            return;
        }

        cout << "\n===== BILL DETAILS =====";
        cout << "\nRoom Bill: Rs." << bookings[i].roomBill;
        cout << "\nFood Bill: Rs." << bookings[i].foodBill;
        cout << "\nService Bill: Rs." << bookings[i].serviceBill;
        cout << "\n------------------------";
        cout << "\nTOTAL BILL: Rs." << bookings[i].totalBill << endl;
    }

    /* CHECK OUT */
    void checkOut() {
        int r;
        cout << "Room No: ";
        cin >> r;

        int i = findRoom(r);
        if (i == -1) { cout << "Room Not Found!\n"; return; }

        bookings[i].active = false;

        cout << "Checkout Successful!\n";
    }

    /* TODAY SUMMARY */
    void todaySummary() {
        int totalCheckIn = 0;
        int totalCheckOut = 0;
        int totalCollection = 0;

        for (int i = 0; i < bookingCount; i++) {
            if (bookings[i].active) totalCheckIn++;
            else totalCheckOut++;

            totalCollection += bookings[i].roomBill + bookings[i].foodBill + bookings[i].serviceBill;
        }

        cout << "\n===== TODAY SUMMARY =====";
        cout << "\nTotal Check-in: " << totalCheckIn;
        cout << "\nTotal Check-out: " << totalCheckOut;
        cout << "\nTotal Collection: Rs." << totalCollection << endl;
    }

    /* USER MENU */
    void userMenu() {
        int ch;
        while (loggedIn) {
            cout << "\n===== USER MENU =====";
            cout << "\n1. Room Booking";
            cout << "\n2. Food Order";
            cout << "\n3. Room Service";
            cout << "\n4. Show Bill";
            cout << "\n5. Check Out";
            cout << "\n6. Today Summary";
            cout << "\n7. Logout";
            cout << "\nChoice: ";
            cin >> ch;

            switch (ch) {
            case 1: bookRoom(); break;
            case 2: foodOrder(); break;
            case 3: roomService(); break;
            case 4: showBill(); break;
            case 5: checkOut(); break;
            case 6: todaySummary(); break;
            case 7: loggedIn = false; break;
            default: cout << "Invalid Choice!\n";
            }
        }
    }
};

/* ===== MAIN ===== */
int main() {
    Hotel h;
    int ch;
    while (true) {
        cout << "\n==== ZAM ZAM HOTEL ====";
        cout << "\n1. Sign Up";
        cout << "\n2. Login";
        cout << "\n3. Exit";
        cout << "\nChoice: ";
        cin >> ch;

        if (ch == 1) h.signUp();
        else if (ch == 2) h.login();
        else break;
    }
    return 0;
}