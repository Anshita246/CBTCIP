#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
public:
    string rollNumber;
    string name;
    string department;
    int year;
    float marks;

    void getData() {
        cout << "Enter Roll Number: ";
        cin >> rollNumber;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Department: ";
        getline(cin, department);
        cout << "Enter Year: ";
        cin >> year;
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void displayData() {
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Department: " << department << endl;
        cout << "Year: " << year << endl;
        cout << "Marks: " << marks << endl;
    }
};

void addStudent() {
    Student student;
    student.getData();

    ofstream outFile("students.dat", ios::binary | ios::app);
    outFile.write(reinterpret_cast<char*>(&student), sizeof(Student));
    outFile.close();

    cout << "Student record added successfully!" << endl;
}

void displayStudents() {
    Student student;

    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "No records found!" << endl;
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        student.displayData();
        cout << "----------------------" << endl;
    }

    inFile.close();
}

void searchStudent() {
    string rollNumber;
    cout << "Enter Roll Number to search: ";
    cin >> rollNumber;

    Student student;
    bool found = false;

    ifstream inFile("students.dat", ios::binary);
    if (!inFile) {
        cout << "No records found!" << endl;
        return;
    }

    while (inFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
        if (student.rollNumber == rollNumber) {
            student.displayData();
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with Roll Number " << rollNumber << " not found!" << endl;
    }

    inFile.close();
}

int main() {
    int choice;
    do {
        cout << "1. Add Student\n2. Display All Students\n3. Search Student\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            addStudent();
            break;
        case 2:
            displayStudents();
            break;
        case 3:
            searchStudent();
            break;
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
