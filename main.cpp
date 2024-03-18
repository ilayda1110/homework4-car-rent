#include <iostream>
#include <fstream>
#include <forward_list>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Car
{
private:
    string type;
    string brand;
    string model;
    string date;
    bool occupied;
public:
    Car(string t, string b, string m, string d) : type(t), brand(b), model(m), date(d), occupied(false){}
    void setModel(string m) {model = m;}
    void setBrand(string b) {brand = b;}
    void setDate(string d) {date = d;}
    void setType(string t) {type = t;}
    void setOccupied(bool o) {occupied = o;}
    string getModel() {return model;}
    string getBrand() {return brand;}
    string getDate() {return date;}
    string getType() {return type;}
    bool getOccupied() {return occupied;}
};

class Customer
{
private:
    vector <Car> pastRents;
    string name;
    string surname;
    string phone;
public:
    void setName(string n) { name = n; }
    void setSurname(string s) { surname = s; }
    void setPhone(string p) { phone = p; }
    string getName() { return name; }
    string getSurname() { return surname; }
    string getPhone() { return phone; }
};

void printAvailableCars(forward_list<Car>cars)
{
    for(Car &p:cars)
    {
        if(!p.getOccupied())
        {
            cout << p.getType() << ", " << p.getBrand() << ", " << p.getModel() << ", " << p.getDate() << endl;
        }
    }
}

int printMenu()
{
    int opChoice;
    cout << "====== EliteDrive======" << endl;
    cout << "1. Display available cars" << endl;
    cout << "2. Rent a car" << endl;
    cout << "3. Return rented car" << endl;
    cout << "4. Display customer information" << endl; // (display name, contact info, rental history)
    cout << "5. Register new customers" << endl;  // (get name, contact info)
    cout << "6. View customer accounts" << endl; // (Booking history,make new reservations)
    cout << "7. Exit" << endl;
    cin >> opChoice;
    return opChoice;
}

int main() {

    ifstream text;
    string line;

    forward_list <Car> cars;

    string model;
    string brand;
    string type;
    string year;

    text.open("cars.txt");
    if (text.is_open())
    {
        while (getline(text, line))
        {
            stringstream s(line);
            getline(s, type, ',');
            getline(s, brand, ',');
            getline(s, model, ',');
            getline(s, year, ',');
            Car car1(type, brand, model, year);
            cars.push_front(car1);
        }
        text.close();
    }
    else
    {
        cout << "Couldn't open the file" << endl;
    }

    int choice;
    bool loop = true;

    do
    {
        choice = printMenu();
        if (choice == 1)
        {
            printAvailableCars(cars);
        }
        else if (choice == 2)
        {

        }
        else if (choice == 3)
        {

        }
        else if (choice == 4)
        {

        }
        else if (choice == 5)
        {

        }
        else if (choice == 6)
        {

        }
        else if (choice == 7)
        {
            cout << "Bye!" << endl;
            loop = false;
        }
    } while (loop);
    return 0;
}