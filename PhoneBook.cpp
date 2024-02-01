// no struct approach
#include <iostream>
#include <fstream>
#include <string>
#include <limits>    //needed for input validation
#include <algorithm> //needed for alldigits function

using namespace std;

bool alldigits(string phoneNum)
{
    // returns true if all characters in a string(phoneNum) are digits
    return all_of(phoneNum.begin(), phoneNum.end(), ::isdigit);
}

void addContact()
{

    fstream file("test.txt", ios::app);
    if (file.is_open())
    {
        string firstName;
        string secondName;
        string phoneNumber;

        cout << "Enter the phone num: ";
        cin >> phoneNumber;
        // checks if phoneNumber length is less than 10 and that all digits are integers
        if (!alldigits(phoneNumber) || phoneNumber.size() > 10)
        {
            cout << "Enter a valid Phone Number!\n";
            addContact();
        }
        else
        {

            cout << "Enter the first name: ";
            cin >> firstName;
            cout << "Enter the Second name: ";
            cin >> secondName;

            file << phoneNumber << ' ' << firstName << ' ' << secondName << endl;
        }
    }
    else
    {
        cerr << "Error occured";
    }
    file.close();
}

void displayContact()
{
    ifstream inputFile("test.txt");

    if (inputFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cerr << "Error Occured";
    }
    inputFile.close();
}

void updateContact()
{
    ifstream inputFile("test.txt");
    ofstream tempFile("temp.txt");

    if (inputFile.is_open() && tempFile.is_open())
    {
        bool found = false;
        string line;
        string searchTerm;
        cout << "Input SearchTerm (Name,PhoneNumber): ";
        cin >> searchTerm;
        while (getline(inputFile, line))
        {
            auto pos = line.find(searchTerm);
            if (pos != string::npos)
            {
                cout << "Contact Info: " << line << endl;
                found = true;
                string newPhoneNum, newFirstName, newSecondName;
                cout << "Enter new phone number: ";
                cin >> newPhoneNum;
                if (alldigits(newPhoneNum) && newPhoneNum.size() <= 10)
                {
                    cout << "Enter the first name: ";
                    cin >> newFirstName;
                    cout << "Enter the second name: ";
                    cin >> newSecondName;
                    tempFile << newPhoneNum << ' ' << newFirstName << ' ' << newSecondName << endl;
                }
                else
                {
                    cout << "Enter a valid phone number\n";
                    updateContact();
                }
            }
            else
            {
                tempFile << line << endl;
            }
        }

        inputFile.close();
        tempFile.close();

        if (found)
        {
            remove("test.txt");
            rename("temp.txt", "test.txt");
        }
        else
        {
            cout << "Contact not found" << endl;
            remove("temp.txt"); // Delete the temp file
        }
    }
    else
    {
        cerr << "Error Occurred\n";
    }
}

void searchContact()
{
    ifstream inputFile("test.txt");

    if (inputFile.is_open())
    {
        bool found = false;
        string line;
        string searchTerm;
        cout << "Input SearchTerm (Name,PhoneNumber): ";
        cin >> searchTerm;
        while (getline(inputFile, line))
        {
            auto pos = line.find(searchTerm);
            if (pos != string::npos)
            {
                cout << "Contact Found!\n";
                cout << line << endl;
                found = true;
                break;
            }
        }

        if (!found)
        {
            cout << "Contact doesn't exist\n";
        }
    }
    else
    {
        cerr << "Error Occurred";
    }

    inputFile.close();
}

void deleteContact()
{
    ifstream file("test.txt");
    ofstream tempFile("temp.txt");

    if (file.is_open() && tempFile.is_open())
    {

        bool contactFound = false;
        string contactToBeDeleted;
        cout << "Enter Name or Phone number of the contact you want to remove: ";
        cin >> contactToBeDeleted;
        string line;
        while (getline(file, line))
        {
            auto pos = line.find(contactToBeDeleted);
            if (pos != string::npos)
            {
                contactFound = true;
                continue;
            }

            tempFile << line << endl;
            break;
        }

        tempFile.close();
        file.close();

        if (contactFound)
        {
            if (remove("test.txt") == 0 && rename("temp.txt", "test.txt") == 0)
            {
                cout << "Contact Deleted Successfully" << endl;
            }
            else
            {
                cerr << "Error deleting or renaming files." << endl;
            }
        }
        else
        {
            cout << "Contact Not Found" << endl;
            ;
        }
    }
    else
    {
        cerr << "Error opening files.";
    }
}

int main()
{
    int choice;
    cout << "MENU" << endl;
    do
    {
        cout << "1. Add Contact" << endl
             << "2. Display Contact" << endl
             << "3. Search Contact" << endl
             << "4. Update Contact" << endl
             << "5. Delete Contact" << endl
             << "6. Exit" << endl;
        cout << "Please enter your choice: ";

        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, Please enter numbers from 1 to 5\n";
            continue;
        }
        else if (choice > 6 || choice < 1)
        {
            cout << "Invalid input, Please enter integers in the range of [1,5].\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        else
        {
            switch (choice)
            {
            case 1:
                addContact();
                break;
            case 2:
                displayContact();
                break;
            case 3:
                searchContact();
                break;
            case 4:
                updateContact();
                break;
            case 5:
                deleteContact();
                break;
            }
        }
    } while (choice != 6);

    return 0;
}