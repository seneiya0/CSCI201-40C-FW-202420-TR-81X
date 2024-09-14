#include "person.h"
#include "employee.h"
#include <iostream>
#include <limits>
#include <cctype>
// lecture activity add prompts for the employee data (see line 64)
void printPerson(const person &);
employee *enterEmployee();
person *enterPerson();
void resetStream();

int main()
{
    // person myPerson("Ansegar", "Goodwort");
    employee myEmployee("Wichmann", "Hedgehopper", "2221112222", "2024-09-09");

    // printPerson(myPerson);
    printPerson(myEmployee);

    int numPeople;
    std::cout << "How many people do you want to enter? ";
    std::cin >> numPeople;
    while (!std::cin || numPeople <= 0)
    {
        if (!std::cin)
            resetStream();
        std::cout << "You entered an invalid number. Please enter a number greater than 0." << std::endl;
        std::cout << "How many people do you want to enter? ";
        std::cin >> numPeople;
    }
    person **people = new person *[numPeople];
    for (int i = 0; i < numPeople; i++)
    {
        char pOrE;
        std::cout << "Would you like to enter a (p)erson or (e)mployee? ";
        std::cin >> pOrE;
        pOrE = tolower(pOrE);
        while (pOrE != 'p' && pOrE != 'e')
        {
            std::cout << "Please enter p for person or e for employee: ";
            std::cin >> pOrE;
            pOrE = tolower(pOrE);
        }
        if (pOrE == 'p')
            people[i] = enterPerson();
        else
            people[i] = enterEmployee();
    }
    for (int i = 0; i < numPeople; i++)
    {
        printPerson(*people[i]);
    }

    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printPerson(const person &p)
{
    std::cout << p.tostring() << std::endl;
}

employee *enterEmployee()
{
    person *p = enterPerson();
    std::string ssn , hiredate;
    double salary;
    // add prompts for this data
    std::cout << "Enter your SSN: ";
    std::getline(std::cin, ssn);
    
    std::cout << "Enter your hire date (YYYY-MM-DD): ";
    std::getline(std::cin, hiredate);
    
    std::cout << "Enter your salary: ";
    std::cin >> salary;
    while (!std::cin || salary <= 0) {
        if (!std::cin){
            resetStream();
            std::cout << "You entered an invalid salary. Please enter a positive number." << std::endl;
            std::cout << "Enter the salary: ";
            std::cin >> salary;
        } else if (salary < 6000){
            salary = 6000;
        }

    }

    employee *e = new employee(p->getFname(), p->getLname(), ssn, hiredate, salary, p->getAddress(), p->getPhone(), p->getEmail());
    delete p;
    return e;
}

person *enterPerson()
{
    std::string fname, lname, address, phone, email;
    std::cout << "Enter the first name: ";
    std::getline(std::cin >> std::ws, fname);
    std::cout << "Enter the last name: ";
    std::getline(std::cin >> std::ws, lname);
    std::cout << "Enter the address on 1 line: ";
    std::getline(std::cin, address);
    std::cout << "Enter the phone number: ";
    std::getline(std::cin, phone);
    std::cout << "Enter the email address: ";
    std::getline(std::cin, email);
    return new person(fname, lname, address, phone, email);
}
