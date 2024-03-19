#include <iostream>
#include <fstream>
#include <forward_list>
#include <string>
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
    Car(){}
    Car(string t, string b, string m, string d) : type(t), brand(b), model(m), date(d), occupied(false){}
    Car(string t, string b, string m) : type(t), brand(b), model(m), occupied(false) {}
    Car(string b, string m) : brand(b), model(m), occupied(false) {}
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
    forward_list <Car> pastRents;
    string name;
    string surname;
    string phone;
public:
    Customer(string n, string s, string p) : name(n), surname(s), phone(p) {}
    Customer(string n, string s) : name(n),  surname(s) {}
    void setName(string n) { name = n; }
    void setSurname(string s) { surname = s; }
    void setPhone(string p) { phone = p; }
    void setRents(Car &c) {pastRents.push_front(c);}
    string getName() { return name; }
    string getSurname() { return surname; }
    string getPhone() { return phone; }
    void getRents()
    {
        for(Car p: pastRents)
        {
            cout << "- " << p.getType() << ", " << p.getBrand() << ", " << p.getModel() << ", " << p.getDate() << endl;
        }
    }
    bool cancelRent(Car p)
    {
        for(Car &temp: pastRents)
        {
            if(p.getModel() == temp.getModel() && p.getBrand() == temp.getBrand())
            {
                return true;
            }
        }
        return false;
    }

    friend void operator<<(ostream& os, Customer& c)
    {
        os << c.name << " " << c.surname << " - " << c.phone << endl;
        os << "Past Rents: " << endl;
        c.getRents();
    }
};

void printAvailableCars(forward_list<Car>&cars)
{
    for(Car p:cars)
    {
        if(p.getOccupied())
        {
            cout << "RENTED: ";
        }
        else
        {
            cout << "NOT RENTED: ";
        }
        cout << p.getType() << ", " << p.getBrand() << ", " << p.getModel() << ", " << p.getDate() << endl;
    }
}

void printCustomers(forward_list<Customer> &customers)
{
    for(Customer c: customers)
    {
        cout << "\n";
        cout << c;
        cout << "\n";
    }
}

bool rentCar(forward_list<Car>&cars, Car car, Customer &customer)
{
    for(Car &p: cars)
    {
        if(p.getModel() == car.getModel() && p.getType() == car.getType() && p.getBrand() == car.getBrand())
        {
            p.setOccupied(true);
            customer.setRents(p);
            return true;
        }
    }
    return false;
}

bool cancelCar(forward_list<Car>&cars, Car car, Customer &customer)
{
    for(Car &p: cars)
    {
        if(p.getModel() == car.getModel() && p.getBrand() == car.getBrand())
        {
            return customer.cancelRent(p);
        }
    }
    return false;
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
    cout << "Choose: ";
    cin >> opChoice;
    return opChoice;
}

int main() {

    ifstream text;
    string line;

    forward_list <Car> cars;
    forward_list <Customer> customers;

    string model, brand, type, year;
    string name, surname, no;

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
    bool loop = true, rent, cancel;

    do
    {
        choice = printMenu();
        if (choice == 1)
        {
            printAvailableCars(cars);
        }
        else if (choice == 2)
        {
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your surname: ";
            cin >> surname;
            Customer c(name, surname);
            for(Customer &p: customers)
            {
                if(c.getName() == p.getName() && c.getSurname() == p.getSurname())
                {
                    cout << "Enter brand: ";
                    cin >> brand;
                    cout << "Enter type: ";
                    cin.ignore();
                    getline(cin, type);
                    cout << "Enter model: ";
                    getline(cin, model);
                    Car car(type, brand, model);
                    rent = rentCar(cars, car, p);
                    if(rent)
                    {
                        cout << "Car rented successfully" << endl;
                    }
                    else
                    {
                        cout << "Could not rent" << endl;
                    }
                }
                else
                {
                    cout << "Customer could not found" << endl;
                }
            }
        }
        else if (choice == 3)
        {
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your surname: ";
            cin >> surname;
            Customer c(name, surname);
            for(Customer p: customers)
            {
                if(c.getName() == p.getName() && c.getSurname() == p.getSurname())
                {
                    cout << "Enter brand: ";
                    cin >> brand;
                    cin.ignore();
                    cout << "Enter model: ";
                    getline(cin, model);
                    Car car(brand, model);
                    cancel = cancelCar(cars, car, p);
                    if(cancel)
                    {
                        cout << "Car canceled successfully" << endl;
                    }
                    else
                    {
                        cout << "Could not cancel" << endl;
                    }
                }
                else
                {
                    cout << "Customer could not found" << endl;
                }
            }
        }
        else if (choice == 4)
        {
            printCustomers(customers);
        }
        else if (choice == 5)
        {
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your surname: ";
            cin >> surname;
            cout << "Enter your phone number (with your calling codes): ";
            cin.ignore();
            getline(cin, no);
            Customer c(name, surname, no);
            customers.push_front(c);
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