#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void login();
void menu();
void enterRecord();
void searchRecord();
void deleteRecord();
void printRecords();
void clearScreen();

const string USERNAME = "useradmin";
const string PASSWORD = "password123";

int main() {
    login();
    return 0;
}

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void login() {
    string username, password;
    bool isAuthenticated = false;

    while (!isAuthenticated) {
        clearScreen();
        cout << "=============================================" << endl;
        cout << "       Login to Continue" << endl;
        cout << "=============================================" << endl;

        cout << "Enter username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> password;

        if (username == USERNAME && password == PASSWORD) {
            isAuthenticated = true;
            cout << "\nAccess Granted!" << endl;
            menu();
        } else {
            cout << "Incorrect username or password. Please try again." << endl;
        }
    }
}

void menu() {
    int choice;
    while (true) {
        clearScreen();
        cout << "=============================================" << endl;
        cout << "     Clinic Management System" << endl;
        cout << "=============================================" << endl;
        cout << "[1] Enter New Record" << endl;
        cout << "[2] Search for a Record" << endl;
        cout << "[3] View All Records" << endl;
        cout << "[4] Delete a Record" << endl;
        cout << "[5] Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                enterRecord();
                break;
            case 2:
                searchRecord();
                break;
            case 3:
                printRecords();
                break;
            case 4:
                deleteRecord();
                break;
            case 5:
                cout << "Exiting the program..." << endl;
                exit(0);
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    }
}

void enterRecord() {
    string name, section, concern, guardianContact, otherHealthIssue, nurseOnDuty, date, time, guardianName;
    int age;

    clearScreen();
    cout << "=============================================" << endl;
    cout << "        Enter New Record" << endl;
    cout << "=============================================" << endl;

    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Age: ";
    cin >> age;
    cout << "Enter Section: ";
    cin.ignore();
    getline(cin, section);
    cout << "Health Concern: ";
    getline(cin, concern);
    cout << "Guardian name: ";
    getline(cin, guardianName);
    cout << "Guardian Contact: ";
    getline(cin, guardianContact);
    cout << "Enter other health issue: ";
    getline(cin, otherHealthIssue);
    cout << "Enter date (MM-DD-YYYY): ";
    getline(cin, date);
    cout << "Enter time (HH:MM): ";
    getline(cin, time);
    cout << "Enter nurse on duty: ";
    getline(cin, nurseOnDuty);

    ofstream file("HealthRecords.txt", ios::app);
    if (file.is_open()) {
        file << name << "\n" << age << "\n" << section << "\n" << concern << "\n"
             << guardianName << "\n" << guardianContact << "\n" << otherHealthIssue << "\n"
             << date << "\n" << time << "\n" << nurseOnDuty << "\n";
        file.close();
        cout << "\nRecord added successfully!" << endl;
    } else {
        cout << "Error: Unable to open file." << endl;
    }
    system("pause");
}

void searchRecord() {
    string searchName, line;
    bool found = false;

    clearScreen();
    cout << "=============================================" << endl;
    cout << "        Search Record" << endl;
    cout << "=============================================" << endl;
    cout << "Enter name to search: ";
    cin.ignore();
    getline(cin, searchName);

    ifstream file("HealthRecords.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            if (line == searchName) {
                found = true;
                cout << "\nRecord Found:" << endl;
                cout << "Name: " << line << endl;
                getline(file, line);
                cout << "Age: " << line << endl;
                getline(file, line);
                cout << "Section: " << line << endl;
                getline(file, line);
                cout << "Health Concern: " << line << endl;
                getline(file, line);
                cout << "Guardian Name: " << line << endl;
                getline(file, line);
                cout << "Guardian Contact: " << line << endl;
                getline(file, line);
                cout << "Other Health Issue: " << line << endl;
                getline(file, line);
                cout << "Date: " << line << endl;
                getline(file, line);
                cout << "Time: " << line << endl;
                getline(file, line);
                cout << "Nurse on Duty: " << line << endl;
                break;
            }
        }
        file.close();

        if (!found) {
            cout << "\nNo record found for " << searchName << "." << endl;
        }
    } else {
        cout << "Error: Unable to open file." << endl;
    }
    system("pause");
}

void deleteRecord() {
    string searchName, line;
    bool found = false;

    clearScreen();
    cout << "=============================================" << endl;
    cout << "        Delete Record" << endl;
    cout << "=============================================" << endl;
    cout << "Enter name to delete: ";
    cin.ignore();
    getline(cin, searchName);

    ifstream file("HealthRecords.txt");
    ofstream tempFile("TempRecords.txt");

    if (file.is_open() && tempFile.is_open()) {
        while (getline(file, line)) {
            if (line == searchName) {
                found = true;
                for (int i = 0; i < 9; i++) {
                    getline(file, line);
                }
                cout << "\nRecord deleted successfully." << endl;
            } else {
                tempFile << line << "\n";
                for (int i = 0; i < 9; i++) {
                    getline(file, line);
                    tempFile << line << "\n";
                }
            }
        }
        file.close();
        tempFile.close();

        remove("HealthRecords.txt");
        rename("TempRecords.txt", "HealthRecords.txt");

        if (!found) {
            cout << "\nNo record found for " << searchName << "." << endl;
        }
    } else {
        cout << "Error: Unable to open file." << endl;
    }
    system("pause");
}

void printRecords() {
    string line;

    clearScreen();
    cout << "=============================================" << endl;
    cout << "        All Health Records" << endl;
    cout << "=============================================" << endl;

    ifstream file("HealthRecords.txt");
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << "Name: " << line << endl;
            getline(file, line);
            cout << "Age: " << line << endl;
            getline(file, line);
            cout << "Section: " << line << endl;
            getline(file, line);
            cout << "Health Concern: " << line << endl;
            getline(file, line);
            cout << "Guardian Name: " << line << endl;
            getline(file, line);
            cout << "Guardian Contact: " << line << endl;
            getline(file, line);
            cout << "Other Health Issue: " << line << endl;
            getline(file, line);
            cout << "Date: " << line << endl;
            getline(file, line);
            cout << "Time: " << line << endl;
            getline(file, line);
            cout << "Nurse on Duty: " << line << endl;
            cout << "=============================================" << endl;
        }
        file.close();
    } else {
        cout << "Error: Unable to open file." << endl;
    }
    system("pause");
}
