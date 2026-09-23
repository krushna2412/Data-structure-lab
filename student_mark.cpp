include <iostream>
using namespace std;

int main() {
    int marks[5];

    // Input marks
    cout << "Enter marks of 5 students:\n";
    for (int i = 0; i < 5; i++) {
        cin >> marks[i];
    }

    // Sort marks in descending order
    for (int i = 0; i < 5; i++) {
        for (int j = i + 1; j < 5; j++) {
            if (marks[i] < marks[j]) {
                int temp = marks[i];
                marks[i] = marks[j];
                marks[j] = temp;
            }
        }
    }

    // Display marks from highest to lowest
    cout << "\nMarks in descending order:\n";
    for (int i = 0; i < 5; i++) {
        cout << marks[i] << endl;
    }

    return 0;
}
