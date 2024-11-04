#include "volemachine.h"


using namespace std;

int main() {
    Machine machine;  // Move machine initialization outside the loop to preserve state
    string input;
    int choice;
    string fname;

    while (true) {
        cout << endl << endl << endl;
        cout << "Welcome to our Vole Machine \n";
        cout << "Please choose from the following menu: \n";
        cout << "1) Read file and load program\n";
        cout << "2) Execute program\n";
        cout << "3) Display Data\n";
        cout << "4) Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        int index;

        if (choice == 1) {
            cout << "Please enter starting location of the Memory (starting from 0 to 256): ";
            cin >> index;
            cout << "Please enter Command File name with extension: ";
            cin >> fname;
            ifstream infile(fname);

            if (!infile) {
                cerr << "ERROR: Could not open input file!" << endl;
                continue;  // Skip to the next loop iteration if file opening fails
            }

            string line;
            input.clear();  // Clear any previous input data
            while (getline(infile, line)) {
                input += line + "\n";
            }
            infile.close();
            machine.setInput(input, index);  // Set the input for the machine
        }
        else if (choice == 2) {
            machine.execute(index);  // Execute the loaded program
        }
        else if (choice == 3) {
            machine.printState();  // Display the current state of the machine
        }
        else if (choice == 4) {
            cout << "Exiting...\n";
            break;  // Exit the loop and end the program
        }
        else {
            cerr << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
