#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

string getMonthString(int day);

struct dateOfBirth {
    string month;
    int day;
    int year;
};

struct presidentialInfo {
    string firstName;
    string middleName;
    string lastName;
    int ageElected;
    string stateOfBirth;
    dateOfBirth *DOB;
};

int main() {
    ifstream in;
    string fileName;

    cout << "Enter filename to process\n> ";
    getline(cin, fileName, '\n');

    while (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nPlease try again:\n> ";
        getline(cin, fileName, '\n');
    }

    in.open(fileName);

    while (!in) {
        cout << "\nFailed to open file, please try again or type 'q' to exit\n> ";
        getline(cin, fileName, '\n');

        if (fileName == "q" || fileName == "Q")
            exit(0);

        in.open(fileName);
    }

    vector<presidentialInfo*> presidentialStats;

    while (!in.eof()) {
        presidentialInfo *info = new presidentialInfo();
        getline(in, info->firstName, ':');
        getline(in, info->middleName, ':');
        getline(in, info->lastName, ':');

        in >> info->ageElected;

        // Extraction operator does not consume newlines
        // so we must account for that

        in.ignore(numeric_limits<streamsize>::max(), '\n');

        getline(in, info->stateOfBirth, '\n');
        info->DOB = new dateOfBirth();

        // If we're out of memory, end it now
        if (!info || !info->DOB)
            break;

        int month;

        // Ignore until reach int or newline
        while (!(in >> month)) {
            in.clear();
            in.ignore(1, '\n');
        }

        string monthStr = getMonthString(month);
        info->DOB->month = monthStr;

        while (!(in >> info->DOB->day)) {
            in.clear();
            in.ignore(1, '\n');
        }

        while (!(in >> info->DOB->year)) {
            in.clear();
            in.ignore(1, '\n');
        }

        in.ignore(numeric_limits<streamsize>::max(), '\n');

        presidentialStats.push_back(info);
    }

    cout << "===============================" << endl;

    for (int j = 0; j < presidentialStats.size(); j++) {
        cout << "President Name: " << presidentialStats[j]->firstName << " ";
        if (presidentialStats[j]->middleName.size() > 0)
            cout << presidentialStats[j]->middleName << " ";
        cout << presidentialStats[j]->lastName << endl;
        cout << "Age Elected: " << presidentialStats[j]->ageElected << endl;
        cout << "State of Birth: " << presidentialStats[j]->stateOfBirth << endl;
        cout << "Date of Birth: " << presidentialStats[j]->DOB->month << " " << presidentialStats[j]->DOB->day << ", " << presidentialStats[j]->DOB->year << endl;
        cout << "----------------------------" << endl;

        delete presidentialStats[j]->DOB;
        delete presidentialStats[j];
    }

    in.close();

#ifdef _WIN32
    system("pause");
#endif
    return 0;
}

string getMonthString(int day) {
    switch (day) {
        case 1:
            return "January";
        case 2:
            return "February";
        case 3:
            return "March";
        case 4:
            return "April";
        case 5:
            return "May";
        case 6:
            return "June";
        case 7:
            return "July";
        case 8:
            return "August";
        case 9:
            return "September";
        case 10:
            return "October";
        case 11:
            return "November";
        case 12:
            return "December";
        default:
            return "NULL";
    }
}