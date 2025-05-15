#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// Base class
class User {
public:
    string name;
    double totalIncome;
    double totalExpenses;
    string pass;
    long int phone_no;

    User(string name) : name(name), totalIncome(0), totalExpenses(0) {}

    virtual void addIncome(double amount) {
        totalIncome += amount;
    }

    virtual void addExpense(double amount) {
        totalExpenses += amount;
    }
};

// Derived class for Students
class Student : public User {
public:
    Student(string name) : User(name) {}
};

// Derived class for Working Professionals
class Professional : public User {
public:
    Professional(string name) : User(name) {}
};

// Derived class for Retired Persons
class Retired : public User {
public:
    Retired(string name) : User(name) {}
};

// Function to create a user
void createUser(User* U) {
    cout << "Enter username: ";
    cin >> U->name;
    cout << "Enter Phone number: ";
    cin >> U->phone_no;
    cout << "Enter password: ";
    cin >> U->pass;
}

// Function to calculate expenses based on user category
float calculate(int category) {
    float emi = 0, exp, rent, food, travel, oth = 0, total = 0;
    char a, b;

    switch (category) {
        case 1: // Student
            cout << "Have you taken an education loan? (Enter Y/y for Yes): ";
            cin >> a;
            if (a == 'Y' || a == 'y') {
                float p, r, n;
                cout << "Enter Principal amount: ";
                cin >> p;
                cout << "Enter rate of interest: ";
                cin >> r;
                cout << "Enter tenure (in months): ";
                cin >> n;

                // EMI Calculation
                if (r != 0) {
                    emi = (p * r * pow(1 + r, n)) / ((powf(1 + r, n) - 1));
                } else {
                    emi = p / n; // If interest rate is 0
                }

                cout << "Enter Accommodation cost: ";
                cin >> rent;

                cout << "Enter Mess/Canteen charges: ";
                cin >> food;

                cout << "Enter travel charges: ";
                cin >> travel;

                cout << "Any other expenses? (Enter Y/y for Yes): ";
                cin >> b;
                if (b == 'Y' || b == 'y') {
                    cout << "Enter miscellaneous expenses: ";
                    cin >> oth;
                }
                total = emi + rent + food + travel + oth;
                cout << "Total Expenses: Rs" << total << endl; // Show total
            }
            break;

        case 2: // Professional
            // Placeholder for future implementation
            cout << "Professional category selected. No implementation yet." << endl;
            break;

        case 3: // Retired
            // Placeholder for future implementation
            cout << "Retired category selected. No implementation yet." << endl;
            break;

        default:
            cout << "Invalid category! Creating a Student by default.\n";
            break;
    }
    return total;
}

// Function to handle user login
void login(const vector<User*>& users) {
    string username, password;
    cout << "Enter Username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // Check if the user exists
    for (User* user : users) {
        if (user->name == username && user->pass == password) {
            cout << "Login Successful! Go to tracker:\n";
            int category;
            cout << "Select category (1: Student, 2: Professional, 3: Retired): ";
            cin >> category;
            calculate(category);
            return; // Exit after successful login
        }
    }
    cout << "Login failed. Check your credentials." << endl;
}

int main() {
    vector<User*> users; // Vector to store user objects
    int choice;

    do {
        cout << "\n--- Personal Finance Tracker ---\n";
        cout << "1. Create User\n";
        cout << "2. Add Income\n";
        cout << "3. Add Expense\n";
        cout << "4. Login\n"; // Removed Display Reports option
        cout << "5. Exit\n";
        cout << "Select an option: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string userType;
                cout << "Enter user type (student/professional/retired): ";
                cin >> userType;
                User* user = nullptr;

                if (userType == "student") {
                    user = new Student("New Student"); // Default name, will be updated in createUser
                } else if (userType == "professional") {
                    user = new Professional("New Professional");
                } else if (userType == "retired") {
                    user = new Retired("New Retired");
                } else {
                    cout << "Invalid user type! Defaulting to Student.\n";
                    user = new Student("New Student");
                }

                createUser(user); // Pass by pointer
                users.push_back(user); // Store user in vector
                break;
            }
            case 2: {
                string name;
                double amount;
                cout << "Enter user name: ";
                cin >> name;
                cout << "Enter income amount: ";
                cin >> amount;

                for (User* user : users) {
                    if (user->name == name) {
                        user->addIncome(amount);
                        cout << "Income added for " << name << endl;
                        break;
                    }
                }
                break;
            }
            case 3: {
                string name;
                double amount;
                cout << "Enter user name: ";
                cin >> name;
                cout << "Enter expense amount: ";
                cin >> amount;

                for (User* user : users) {
                    if (user->name == name) {
                        user->addExpense(amount);
                        cout << "Expense added for " << name << endl;
                        break;
                    }
                }
                break;
            }
            case 4: {
                login(users); // Call login function
                break;
            }
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid option! Please try again.\n";
        }
    } while (choice != 5);

    // Cleanup
    for (User* user : users) {
        delete user;
    }

    return 0;
}
