#include <iostream>
#include <fstream>
using namespace std;

struct PhoneBook
{
    string fN;
    string lN;
    string pN;
};
bool check_digits(string);
bool check_numbers(string);
PhoneBook AddContact(PhoneBook p);
void DisplayContact(PhoneBook p);
void updateContact(PhoneBook *p);
void SearchContact(PhoneBook p);
void DeleteContact(PhoneBook p);

int main()
{
    PhoneBook phone;
    PhoneBook B;
    cout << "MENU" << endl;
    int choice;
    do
    {
        cout << "1. Add Contact" << endl
             << "2. Display Contact" << endl
             << "3. search Contact" << endl
             << "4. delete Contact" << endl
             << "5. Update Contact" << endl;
        cout << "Please enter your choice" << endl;
        cin >> choice;
        switch (choice)
        {

        case 1:
        {
            B = AddContact(phone);

            break;
        }

        case 2:
            DisplayContact(B);

            break;
        case 3:
        {
            SearchContact(B);

            break;
        }

        case 4:
            DeleteContact(phone);

            break;
        case 5:
        {
            updateContact(&B);

            break;

        }
            
        default:
            break;
        }

    } while (choice != 6);
}
// Method 5
// Helper method
bool check_digits(string x)
{
    if (x.length() == 10)
        return true;
    else
        return false;
}

// Method 6
// Helper method
bool check_numbers(string x)
{
    bool check = true;

    for (int i = 0; i < x.length(); i++)
    {
        if (!(int(x[i]) >= 48 && int(x[i]) <= 57))
        {
            check = false;
            break;
        }
    }

    if (check == true)
    {
        return true;
    }

    else
    {
        return false;
    }
}

PhoneBook AddContact(PhoneBook p)
{
    cout << "Enter First name" << endl;
    cin >> p.fN;
    cout << "Enter Last name" << endl;
    cin >> p.lN;
    cout << "Enter Phone number" << endl;
    cin >> p.pN;
    // if (p.pN == 10)
    if (check_digits(p.pN) == true)
    {
        if (check_numbers(p.pN) == true)
        {
            cout << "phone is correct" << endl;
            cout << p.fN << endl;
            cout << p.lN << endl;
            cout << p.pN << endl;
            cout << "contact saved successfully" << endl;
        }

        else
        {
            cout << "check phone number again" << endl;
        }
    }
    return p;
}

void DisplayContact(PhoneBook p)
{
    cout << "Current Record(s)" << endl;
    cout << "========================" << endl;
    int counter = 0;
    int size;
    cout << "enter record size" << endl;
    cin >> size;
    cout << "No|   First Name  |  Last Name  |  Phone Number  " << endl
         << "---------------------------------------------------\n";

    for (int i = 0; i <= size; i++)
    {
        counter++;
        cout << " " << counter << "    " << p.fN << "            "
             << p.lN << "             "
             << p.pN << endl;
    }
    cout << "===================================================" << endl;
}

void updateContact(PhoneBook *p)
{
   bool found = false;

    string keyword;
    cout << "Enter Keyword" << endl;
    cin >> keyword;

    if (keyword == p->fN || keyword == p->lN || keyword == p->pN)
    {
        cout << "First Name: " << p->fN  << endl
             << "Last Name: " <<p->lN << endl
             << "Phone Number: " << p->pN << endl;
        found = true;
        p->fN="hanna";
    }

    if (found == false)
    {
        cout << "contact not found" << endl;
    } 
}
void SearchContact(PhoneBook p)
{
    bool found = false;

    string keyword;
    cout << "Enter Keyword" << endl;
    cin >> keyword;

    if (keyword == p.fN || keyword == p.lN || keyword == p.pN)
    {
        cout << "First Name: " << p.fN << endl
             << "Last Name: " << p.lN << endl
             << "Phone Number: " << p.pN << endl;
        found = true;
    }

    if (found == false)
    {
        cout << "contact not found" << endl;
    }
}
void DeleteContact(PhoneBook p)
{
}
