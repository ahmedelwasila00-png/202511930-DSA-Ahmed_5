#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Student structure (instead of class, easier for beginners)
struct Student {
    string rollNumber;
    string name;
    int age;
};

// Function to read all students from file into an array
// Returns number of students read
int readAllStudents(Student students[], string filename) {
    ifstream file(filename.c_str());
    int count = 0;
    string line;

    if (!file.is_open()) {
        return 0; // file doesn't exist yet
    }

    while (getline(file, line) && count < 100) {
        // parse CSV line: rollNumber,name,age
        int firstComma = line.find(',');
        int secondComma = line.find(',', firstComma + 1);

        students[count].rollNumber = line.substr(0, firstComma);
        students[count].name = line.substr(firstComma + 1, secondComma - firstComma - 1);
        string ageStr = line.substr(secondComma + 1);
        students[count].age = stoi(ageStr);
        count++;
    }
    file.close();
    return count;
}

// Function to write all students from array back to file
void writeAllStudents(Student students[], int count, string filename) {
    ofstream file(filename.c_str());
    for (int i = 0; i < count; i++) {
        file << students[i].rollNumber << "," << students[i].name << "," << students[i].age << endl;
    }
    file.close();
}

// 1. Display all students
void displayAllStudents(string filename) {
    Student students[100];
    int count = readAllStudents(students, filename);

    if (count == 0) {
        cout << "\nNo student records found.\n";
        return;
    }

    cout << "\n--- All Students ---\n";
    cout << "Roll Number     Name                Age\n";
    cout << "---------------------------------------\n";
    for (int i = 0; i < count; i++) {
        cout << students[i].rollNumber << "          "
             << students[i].name << "               "
             << students[i].age << endl;
    }
    cout << endl;
}

// 2. Search student by roll number
void searchStudent(string filename) {
    Student students[100];
    int count = readAllStudents(students, filename);
    string searchRoll;
    bool found = false;

    cout << "Enter Roll Number to search: ";
    cin >> searchRoll;

    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == searchRoll) {
            cout << "\nStudent found!\n";
            cout << "Roll Number: " << students[i].rollNumber << endl;
            cout << "Name: " << students[i].name << endl;
            cout << "Age: " << students[i].age << endl;
            found = true;
            break;
        }
    }
    if (!found) {
        cout << "Student not found.\n";
    }
    cout << endl;
}

// 3. Update student information
void updateStudent(string filename) {
    Student students[100];
    int count = readAllStudents(students, filename);
    string searchRoll;
    bool found = false;

    cout << "Enter Roll Number to update: ";
    cin >> searchRoll;

    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == searchRoll) {
            found = true;
            cout << "Current details:\n";
            cout << "Name: " << students[i].name << ", Age: " << students[i].age << endl;

            cout << "Enter new Name: ";
            cin.ignore(); // clear newline from previous input
            getline(cin, students[i].name);
            cout << "Enter new Age: ";
            cin >> students[i].age;

            // Save changes to file
            writeAllStudents(students, count, filename);
            cout << "Student record updated successfully!\n";
            break;
        }
    }
    if (!found) {
        cout << "Student not found.\n";
    }
    cout << endl;
}

// 4. Delete student record
void deleteStudent(string filename) {
    Student students[100];
    int count = readAllStudents(students, filename);
    string searchRoll;
    bool found = false;

    cout << "Enter Roll Number to delete: ";
    cin >> searchRoll;

    // Find index of student to delete
    int indexToDelete = -1;
    for (int i = 0; i < count; i++) {
        if (students[i].rollNumber == searchRoll) {
            indexToDelete = i;
            found = true;
            break;
        }
    }

    if (found) {
        // Shift all students after indexToDelete one position left
        for (int i = indexToDelete; i < count - 1; i++) {
            students[i] = students[i + 1];
        }
        count--; // reduce count
        writeAllStudents(students, count, filename);
        cout << "Student record deleted permanently!\n";
    } else {
        cout << "Student not found.\n";
    }
    cout << endl;
}

// Main menu
int main() {
    string filename = "student.txt";
    int choice;

    do {
        cout << "\n===== Student Record Menu =====\n";
        cout << "1. Display All Students\n";
        cout << "2. Search Student\n";
        cout << "3. Update Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                displayAllStudents(filename);
                break;
            case 2:
                searchStudent(filename);
                break;
            case 3:
                updateStudent(filename);
                break;
            case 4:
                deleteStudent(filename);
                break;
            case 5:
                cout << "Exiting program. Bye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}