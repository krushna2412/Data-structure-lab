#include<iostream>
#include<string>
#include<limits>
using namespace std;

struct Course {
        string courseCode;
        Course* next;
};

struct Student {
        int rollNo;
        string name;
        string department;
        Course* courseHead;
        Student* next;
        Student* hashNext;
};

Student* head = NULL;
const int SIZE = 10;
Student* hashTable[SIZE] = {NULL};

int hashFunction(int rollNo)
{
        return rollNo % SIZE;
}

void registerStudent()
{
        Student* s = new Student;
        cout << "Enter student Roll Number: ";
        cin >> s->rollNo;

        int index = hashFunction(s->rollNo);
        Student* temp = hashTable[index];
        while (temp != NULL)
        {
                if (temp->rollNo == s->rollNo)
                {
                        cout << "Roll Number already exists!\n";
                        delete s;
                        return;
                }
                temp = temp->hashNext;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Enter Student Name: ";
        getline(cin, s->name);

        cout << "Enter Department: ";
        getline(cin, s->department);

        s->courseHead = NULL;

        s->next = head;
        head = s;

        s->hashNext = hashTable[index];
        hashTable[index] = s;

        cout << "Student registered successfully!\n";
}

void searchStudent()
{
        int rollNo;
        cout << "Enter Roll Number to search: ";
        cin >> rollNo;

        int index = hashFunction(rollNo);
        Student* temp = hashTable[index];
        while (temp != NULL)
        {
                if (temp->rollNo == rollNo)
                {
                        cout << "\nStudent Found!\n";
                        cout << "Roll Number: " << temp->rollNo << endl;
                        cout << "Name: " << temp->name << endl;
                        cout << "Department: " << temp->department << endl;
                        cout << "Enrolled Courses: ";

                        Course* c = temp->courseHead;
                        if (c == NULL)
                        {
                                cout << "None";
                        }
                        while (c != NULL)
                        {
                                cout << c->courseCode;
                                if (c->next != NULL) cout << ", ";
                                c = c->next;
                        }
                        cout << endl;
                        return;
                }
                temp = temp->hashNext;
        }
        cout << "Student not found!\n";
}

void updateStudent()
{
        int rollNo;
        cout << "Enter Roll Number to update: ";
        cin >> rollNo;

        int index = hashFunction(rollNo);
        Student* temp = hashTable[index];
        while (temp != NULL)
        {
                if (temp->rollNo == rollNo)
                {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "Enter New Student Name: ";
                        getline(cin, temp->name);

                        cout << "Enter New Department: ";
                        getline(cin, temp->department);

                        cout << "Student details updated successfully!\n";
                        return;
                }
                temp = temp->hashNext;
        }
        cout << "Student not found!\n";
}

void enrollCourse()
{
        int rollNo;
        cout << "Enter student Roll Number: ";
        cin >> rollNo;

        int index = hashFunction(rollNo);
        Student* temp = hashTable[index];
        while (temp != NULL)
        {
                if (temp->rollNo == rollNo)
                {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        string code;
                        cout << "Enter Course Code to enroll: ";
                        getline(cin, code);

                        // Check if already enrolled
                        Course* c = temp->courseHead;
                        while (c != NULL)
                        {
                                if (c->courseCode == code)
                                {
                                        cout << "Student is already enrolled in this course!\n";
                                        return;
                                }
                                c = c->next;
                        }

                        Course* newCourse = new Course;
                        newCourse->courseCode = code;
                        newCourse->next = temp->courseHead;
                        temp->courseHead = newCourse;

                        cout << "Course enrolled successfully!\n";
                        return;
                }
                temp = temp->hashNext;
        }
        cout << "Student not found!\n";
}

void withdrawCourse()
{
        int rollNo;
        cout << "Enter student Roll Number: ";
        cin >> rollNo;

        int index = hashFunction(rollNo);
        Student* temp = hashTable[index];
        while (temp != NULL)
        {
                if (temp->rollNo == rollNo)
                {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        string code;
                        cout << "Enter Course Code to withdraw: ";
                        getline(cin, code);

                        Course* curr = temp->courseHead;
                        Course* prev = NULL;

                        while (curr != NULL && curr->courseCode != code)
                        {
                                prev = curr;
                                curr = curr->next;
                        }

                        if (curr == NULL)
                        {
                                cout << "Course not found in student's enrollment list!\n";
                                return;
                        }

                        if (prev == NULL)
                                temp->courseHead = curr->next;
                        else
                                prev->next = curr->next;

                        delete curr;
                        cout << "Withdrawn from course successfully!\n";
                        return;
                }
                temp = temp->hashNext;
        }
        cout << "Student not found!\n";
}

void removeStudent()
{
        int rollNo;
        cout << "Enter Roll Number to remove: ";
        cin >> rollNo;

        int index = hashFunction(rollNo);
        Student* currHash = hashTable[index];
        Student* prevHash = NULL;

        while (currHash != NULL && currHash->rollNo != rollNo)
        {
                prevHash = currHash;
                currHash = currHash->hashNext;
        }

        if (currHash == NULL)
        {
                cout << "Student not found!\n";
                return;
        }

        if (prevHash == NULL)
                hashTable[index] = currHash->hashNext;
        else
                prevHash->hashNext = currHash->hashNext;

  
        Student* currList = head;
        Student* prevList = NULL;
        while (currList != NULL && currList != currHash)
        {
                prevList = currList;
                currList = currList->next;
        }

        if (currList != NULL)
        {
                if (prevList == NULL)
                        head = currList->next;
                else
                        prevList->next = currList->next;
        }

        Course* c = currHash->courseHead;
        while (c != NULL)
        {
                Course* nextCourse = c->next;
                delete c;
                c = nextCourse;
        }

        delete currHash;
        cout << "Student record removed successfully!\n";
}

void displayStudents()
{
        Student* temp = head;

        if (temp == NULL)
        {
                cout << "No student record is available.\n";
                return;
        }

        cout << "\n---All Registered Students---\n";
        while (temp != NULL)
        {
                cout << "\nRoll Number: " << temp->rollNo << endl;
                cout << "Name: " << temp->name << endl;
                cout << "Department: " << temp->department << endl;
                cout << "Enrolled Courses: ";

                Course* c = temp->courseHead;
                if (c == NULL)
                {
                        cout << "None";
                }
                while (c != NULL)
                {
                        cout << c->courseCode;
                        if (c->next != NULL) cout << ", ";
                        c = c->next;
                }
                cout << endl;
                temp = temp->next;
        }
}

int main()
{
        int choice;
        do
        {
                cout << "\n---University Student Registration & Course Enrollment System---\n";
                cout << "1. Register New Student\n";
                cout << "2. Search Student\n";
                cout << "3. Update Student Information\n";
                cout << "4. Enroll Student in Course\n";
                cout << "5. Withdraw Student from Course\n";
                cout << "6. Remove Student Record\n";
                cout << "7. Display All Students\n";
                cout << "8. Exit\n";
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                        case 1:
                                registerStudent();
                                break;
                        case 2:
                                searchStudent();
				break;

                        case 3:
                                updateStudent();
                                break;

                        case 4:
                                enrollCourse();
                                break;

                        case 5:
                                withdrawCourse();
                                break;

                        case 6:
                                removeStudent();
                                break;

                        case 7:
                                displayStudents();
                                break;

                        case 8:
                                cout << "Exiting the system. Thank you!\n";
                                break;

                        default:
                                cout << "Invalid choice! Please try again.\n";
                }

        } while (choice != 8);

        return 0;
}
