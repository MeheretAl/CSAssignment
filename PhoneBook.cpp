// V1.0.1 invalid input patch jan 18
// V1.0.2 changes in reading data from file jan 24
// V1.0.3 output formatting feb 11

#include <iostream>  // basic output and input header
#include <cstdlib>   //needed for system("CLS")
#include <iomanip>   //needed for setw
#include <sstream>   //needed to split strings at commas
#include <fstream>   // file manipulation
#include <string>    //needed for getline function
#include <limits>    //needed for input validation
#include <algorithm> //needed for alldigits function

#define CLEAR_SCREEN system("CLS")

using namespace std;

struct PhoneBook
{
    string phoneNumber;
    string firstName;
    string lastName;
    // add other data here
};

bool alldigits(string phoneNum)
{
    return all_of(phoneNum.begin(), phoneNum.end(), ::isdigit);
}

void formatData(string line, string phoneNumber, string firstName, string lastName)
{
    stringstream ss(line);
    getline(ss, phoneNumber, ',');
    getline(ss, firstName, ',');
    getline(ss, lastName, ',');
    cout << setw(10) << phoneNumber << setw(15) << firstName << setw(15) << lastName << endl;
}

void addContact(PhoneBook Book)
{
    fstream file("Book.txt", ios::app);
    if (file.is_open())
    {
        cout << "Enter the Phonenumber: ";
        cin >> Book.phoneNumber;

        if (!alldigits(Book.phoneNumber) || (Book.phoneNumber).size() > 10)
        {
            cout << "Enter a valid Phonenumber \n";
            addContact(Book);
        }
        else
        {
            cout << "Enter the first name: ";
            cin >> Book.firstName;
            cout << "Enter the last name: ";
            cin >> Book.lastName;

            file << Book.phoneNumber << ',' << Book.firstName << ',' << Book.lastName << ',' << endl;
        }
    }
    else
    {
        cerr << "Error occurred";
    }

    file.close();

    cout << "Contact added successfully." << endl;
}

void displayContact()
{
    CLEAR_SCREEN;
    ifstream file("Book.txt");

    if (file.is_open())
    {
        string line;
        cout << "--------------------------------------------------\n";
        cout << setw(10) << "Phone Number" << setw(15) << "First Name" << setw(15) << "Last Name" << endl;
        cout << "--------------------------------------------------\n";
        while (getline(file, line))
        {
            string phoneNumber, firstName, lastName;
            formatData(line, phoneNumber, firstName, lastName);
        }
    }
    else
    {
        cerr << "Error occurred while opening file." << endl;
    }

    file.close();
}

void searchContact(const PhoneBook &book)
{
    ifstream file("Book.txt");
    if (file.is_open())
    {
        string contactToBeSearched;
        cout << "Enter the search term (First Name,Last name or Phone number): ";
        cin >> contactToBeSearched;
        bool contactFound = false;
        string line;
        while (getline(file, line))
        {
            auto pos = line.find(contactToBeSearched);
            if (pos != string::npos)
            {
                string phoneNumber, firstName, lastName;
                cout << setw(10) << "Phone Number" << setw(15) << "First Name" << setw(15) << "Last Name" << endl;
                cout << "--------------------------------------------------\n";
                formatData(line, phoneNumber, firstName, lastName);
                contactFound = true;
                break;
            }
        }

        if (!contactFound)
        {
            int choice;
            cout << "Contact doesn't exist.\n";
            cout << "Would you like to search again?\n1 for yes & 2 for no: ";
            while (!(cin >> choice) || choice > 2 || choice < 1)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid Input, Please enter 1 or 2:  ";
            }
            if (choice == 1)
            {
                searchContact(book);
            }
        }
    }
    else
    {
        cerr << "Error ocurred" << endl;
    }

    file.close();
}

void updateContact(PhoneBook &book)
{
    ifstream inputFile("Book.txt");
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
                    tempFile << newPhoneNum << ',' << newFirstName << ',' << newSecondName << endl;
                }
                else
                {
                    cout << "Enter a valid phone number\n";
                    updateContact(book);
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
            remove("Book.txt");
            rename("temp.txt", "Book.txt");
        }
        else
        {
            cout << "Contact not found" << endl;
            remove("temp.txt"); // Deletes the temp file
        }
    }
    else
    {
        cerr << "Error Occurred\n";
    }
}

void deleteContact(PhoneBook &book)
{
    ifstream file("Book.txt");
    ofstream tempFile("temp.txt");

    if (file.is_open() && tempFile.is_open())
    {

        bool contactFound = false;
        string contactToBeDeleted;
        cout << "Enter Name or Phone number of the contact you want to remove: ";
        cin >> contactToBeDeleted;
        while (contactToBeDeleted.size() < 3)
        {
            cout << "Please provide a longer input (greater than 3) to ensure proper deletion.\n";
            cout << "Enter again: ";
            cin >> contactToBeDeleted;
        }

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
            continue;
        }

        tempFile.close();
        file.close();

        if (contactFound)
        {
            if (remove("Book.txt") == 0 && rename("temp.txt", "Book.txt") == 0)
            {
                cout << "Contact Deleted Successfully." << endl;
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
    PhoneBook Book;
    int choice;
    cout << "Menu" << endl;
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
            cout << "Invalid input, Please enter numbers from 1 to 5.\n";
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
                addContact(Book);
                break;
            case 2:
                displayContact();
                break;
            case 3:
                searchContact(Book);
                break;
            case 4:
                updateContact(Book);
                break;
            case 5:
                deleteContact(Book);
                break;
            }
        }
    } while (choice != 6);

    return 0;
}
