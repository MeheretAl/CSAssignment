#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>

using namespace std;

struct PhoneBook
{
    string firstName;
    string lastName;
    string phoneNumber;
};

bool sizecheck(const string& str)
{
    return str.size() == 10;
}

bool aredigits(const string& number)
{
    return all_of(number.begin(), number.end(), ::isdigit);
}

void searchContact(const PhoneBook& p)
{
    ifstream inputFile("PhoneBook.txt");
    string phoneNumberToSearch;
    cout << "Enter the phone number to search: ";
    cin >> phoneNumberToSearch;

    if (inputFile.is_open())
    {
        string line;
        bool found = false;
        while (getline(inputFile, line))
        {
            if (line.find(phoneNumberToSearch) != string::npos)
            {
                found = true;
                cout << line << endl;
            }
        }

        if (!found)
        {
            cout << "Contact not found.\n";
        }

        inputFile.close();
    }
    else
    {
        cerr << "Error opening file\n";
    }
}

void deleteContact(const PhoneBook& p)
{
    string phoneToBeDeleted;
    cout << "Enter the phone number you want to delete: ";
    cin >> phoneToBeDeleted;

    if (sizecheck(phoneToBeDeleted) && aredigits(phoneToBeDeleted))
    {
        ifstream inputFile("PhoneBook.txt");
        ofstream temp("temp.txt");

        if (inputFile.is_open() && temp.is_open())
        {
            string line;
            bool contactFound = false;

            while (getline(inputFile, line))
            {
                if (line.find(phoneToBeDeleted) != string::npos &&
                    line.find(p.firstName) != string::npos &&
                    line.find(p.lastName) != string::npos)
                {
                    contactFound = true;
                    continue; // Skip the line to delete
                }

                temp << line << endl;
            }

            inputFile.close();
            temp.close();

            if (contactFound)
            {
                remove("PhoneBook.txt");
                rename("temp.txt", "PhoneBook.txt");
                cout << "Contact Deleted Successfully\n";
            }
            else
            {
                cout << "Contact not found.\n";
            }
        }
        else
        {
            cerr << "Error opening files\n";
        }
    }
    else
    {
        cout << "Invalid Phone Number\n";
    }
}

void displayContact(const PhoneBook& p)
{
    ifstream file("PhoneBook.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            cout << line << endl;
        }
        file.close();
    }
    else
    {
        cerr << "Error opening file\n";
    }
}

PhoneBook addContact(const PhoneBook& p)
{
    PhoneBook newContact;
    cout << "Enter Phone Number: ";
    cin >> newContact.phoneNumber;
    cout << "Enter First Name: ";
    cin >> newContact.firstName;
    cout << "Enter Last Name: ";
    cin >> newContact.lastName;

    if (sizecheck(newContact.phoneNumber) && aredigits(newContact.phoneNumber))
    {
        ofstream file("PhoneBook.txt");
        if (file.is_open())
        {
            file << newContact.phoneNumber << " " << newContact.lastName << " " << newContact.firstName << endl;
            file.close();
            cout << "Contact Saved Successfully\n";
        }
        else
        {
            cerr << "Error opening file\n";
        }
    }
    else
    {
        cout << "Error!\n"
             << "Check if the number of digits is 10\n";
    }

    return newContact;
}

int main()
{
    int choice;
    PhoneBook temp;

    do
    {
        cout << "MENU" << endl;
        cout << "1. Add Contact" << endl
             << "2. Display Contact" << endl
             << "3. Search Contact" << endl
             << "4. Delete Contact" << endl
             << "5. Exit" << endl;
        cout << "Please enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            temp = addContact(temp);
            break;
        case 2:
            displayContact(temp);
            break;
        case 3:
            searchContact(temp);
            break;
        case 4:
            deleteContact(temp);
            break;
        case 5:
            cout << "Exiting program.\n";
            break;
        default:
            cout << "Please choose from 1 to 5\n";
            break;
        }

    } while (choice != 5);

    return 0;
}