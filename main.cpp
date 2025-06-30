/*
Neema Taghipour 06/01/2025 08:30 PM
CS-210 Richard Foster
Chada clock Program
Displays user inputed time in 24 Hr and 12 HR clock
*/

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// Clock class definition to hold and manage time
class Clock {
private:
    int hour;
    int minute;
    int second;

public:
    // Default constructor
    Clock() {
        hour = 0;
        minute = 0;
        second = 0;
    }

    // Overloaded constructor to initialize custom time
    Clock(int h, int m, int s) {
        setTime(h, m, s);
    }

    // Set time with validation
    void setTime(int h, int m, int s) {
        hour = (h >= 0 && h < 24) ? h : 0;
        minute = (m >= 0 && m < 60) ? m : 0;
        second = (s >= 0 && s < 60) ? s : 0;
    }

    // Method to add one hour
    void addHour() {
        hour = (hour + 1) % 24;
    }

    // Method to add one minute and roll over if needed
    void addMinute() {
        minute++;
        if (minute >= 60) {
            minute = 0;
            addHour();
        }
    }

    // Method to add one second and roll over if needed
    void addSecond() {
        second++;
        if (second >= 60) {
            second = 0;
            addMinute();
        }
    }

    // Getters
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }
};

// Helper function to format time with leading zeros
string formatTwoDigits(int num) {
    ostringstream out;
    out << setw(2) << setfill('0') << num;
    return out.str();
}

// Function to display both 12-hour and 24-hour clocks
void displayClocks(const Clock& clock) {
    int hour24 = clock.getHour();
    int hour12 = hour24 % 12;
    if (hour12 == 0) hour12 = 12;
    string ampm = (hour24 >= 12) ? "PM" : "AM";

    string time12 = formatTwoDigits(hour12) + ":" + formatTwoDigits(clock.getMinute()) + ":" +
                    formatTwoDigits(clock.getSecond()) + " " + ampm;

    string time24 = formatTwoDigits(hour24) + ":" + formatTwoDigits(clock.getMinute()) + ":" +
                    formatTwoDigits(clock.getSecond());

    cout << "**************************    **************************" << endl;
    cout << "*     12-Hour Clock     *    *     24-Hour Clock     *" << endl;
    cout << "*      " << time12 << "      *    *       " << time24 << "         *" << endl;
    cout << "**************************    **************************" << endl;
}

// Function to show the user menu
void displayMenu() {
    cout << "\n**************************" << endl;
    cout << "* 1 - Add One Hour       *" << endl;
    cout << "* 2 - Add One Minute     *" << endl;
    cout << "* 3 - Add One Second     *" << endl;
    cout << "* 4 - Exit Program       *" << endl;
    cout << "**************************" << endl;
    cout << "Enter your choice: ";
}

// Function to get validated integer input within range
int getValidatedInput(const string& prompt, int min, int max) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail() && value >= min && value <= max) {
            break;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between " << min << " and " << max << "." << endl;
        }
    }
    return value;
}

// Main driver function
int main() {
    cout << "Welcome to Chada Tech Clock System!\nPlease enter the initial time:" << endl;

    int initHour = getValidatedInput("Enter hour (0-23): ", 0, 23);
    int initMinute = getValidatedInput("Enter minute (0-59): ", 0, 59);
    int initSecond = getValidatedInput("Enter second (0-59): ", 0, 59);

    Clock clock(initHour, initMinute, initSecond);

    int choice = 0;

    while (true) {
        displayClocks(clock);
        displayMenu();
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number from 1 to 4.\n";
            continue;
        }

        switch (choice) {
            case 1:
                clock.addHour();
                break;
            case 2:
                clock.addMinute();
                break;
            case 3:
                clock.addSecond();
                break;
            case 4:
                cout << "Exiting program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}