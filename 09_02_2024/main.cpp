#include <iostream>
#include <limits>
#include <cctype>
#include "drink.h"

// lecture activity comment lines 25 - 30, 32, 46, 50, 59, 61, 74 - 80
void resetStream();
sizeType inputDrinkSize();
baseType inputDrinkBase();
tempType inputDrinkTemperature();
std::string inputDrinkFlavor();
std::string inputDrinkDairy();
int *newArray();

bool numInRange(int num, int lower, int upper);
bool numGT0(int num, int = 0, int = 0);
bool negNum(int num, int = 0, int = 0);

int inputInt(std::string prompt, bool (*func)(int, int, int), int lower = 0, int upper = 0); // the function pointer returns a true if the data is valid

int main()
{
    int x = 79;
    int *p = nullptr;
    p = &x;
    std::cout << &x << std::endl;
    std::cout << *p << std::endl;
    p = newArray();
    delete[] p;
    
    drink **drinks;

    sizeType drinkSize;
    baseType drinkBase;
    tempType drinkTemp;
    std::string dairy;
    std::string flavor;
    char yN = 'Y';
    drink *myDrink;
    drinkSize = inputDrinkSize();
    drinkBase = inputDrinkBase();
    drinkTemp = inputDrinkTemperature();
    flavor = inputDrinkFlavor();
    dairy = inputDrinkDairy();
    myDrink = new drink(drinkBase, drinkTemp, drinkSize, dairy, flavor);

    // int numDrinks = inputInt("How many drinks do you want? ", numGT0);
    int numDrinks = 1;
    drinks = new drink *[numDrinks];

    while (yN == 'Y')
    {
        drinkSize = inputDrinkSize();
        drinkBase = inputDrinkBase();
        drinkTemp = inputDrinkTemperature();
        flavor = inputDrinkFlavor();
        dairy = inputDrinkDairy();
        drinks[numDrinks - 1] = new drink(drinkBase, drinkTemp, drinkSize, dairy, flavor);
        // drink d(bases[drinkBase - 1], temps[drinkTemp - 1], sizes[drinkSize - 1], dairy, flavor);
        std::cout << drinks[numDrinks - 1]->tostring() << std::endl;
        std::cout << "Would you like another drink? ";
        std::cin >> yN;
        yN = toupper(yN);
        while (yN != 'Y' && yN != 'N')
        {
            std::cout << "You did not enter y or n." << std::endl;
            std::cout << "Would you like another drink? ";
            std::cin >> yN;
            yN = toupper(yN);
        }
        if (yN == 'Y')
        {
            drink **d = drinks;
            drinks = new drink *[++numDrinks];
            for (int i = 0; i < numDrinks - 1; i++)
            {
                drinks[i] = d[i];
            }
            delete[] d;
        }
    }

    std::cout << "The list of drinks is:" << std::endl;
    std::cout << myDrink->tostring() << std::endl;

    delete myDrink;
    for (int i = 0; i < numDrinks; i++)
    {
        std::cout << drinks[i]->tostring() << std::endl;
        delete drinks[i];
    }
    delete[] drinks;
    return 0;
}

void resetStream()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

sizeType inputDrinkSize()
{
    std::ostringstream out;

    out << "Please choose the drink size:" << std::endl;
    for (int i = 0; i < ENUM_NUM; i++)
    {
        out << i + 1 << ": " << sizeStr[i] << std::endl;
    }
    int drinkSize = inputInt(out.str(), numInRange, 1, 3);

    return sizes[drinkSize - 1];
}

baseType inputDrinkBase()
{
    std::ostringstream out;
    out << "Please choose the drink base:" << std::endl;
    for (int i = 0; i < ENUM_NUM; i++)
    {
        out << i + 1 << ": " << baseStr[i] << std::endl;
    }
    int drinkBase = inputInt(out.str(), numInRange, 1, 3);

    return bases[drinkBase - 1];
}

tempType inputDrinkTemperature()
{
    std::ostringstream out;
    int drinkTemp;
    out << "Please choose the drink temperature:" << std::endl;
    for (int i = 0; i < ENUM_NUM; i++)
    {
        out << i + 1 << ": " << tempStr[i] << std::endl;
    }
    drinkTemp = inputInt(out.str(), numInRange, 1, 3);

    return temps[drinkTemp - 1];
}

std::string inputDrinkFlavor()
{
    std::string flavor;
    std::cout << "Please enter a flavor for your drink: ";
    std::cin >> std::ws;
    std::getline(std::cin, flavor);
    return flavor;
}

std::string inputDrinkDairy()
{
    std::string dairy;
    std::cout << "What kind of dairy would you like? ";
    std::cin >> std::ws;
    std::getline(std::cin, dairy);
    return dairy;
}

int *newArray()
{
    int *list = new int[15];
    return list;
}

bool numInRange(int num, int lower, int upper)
{
    return lower <= num && num <= upper;
}

bool numGT0(int num, int, int)
{

    return num > 0;
}

bool negNum(int num, int, int)
{
    return num < 0;
}

int inputInt(std::string prompt, bool (*func)(int, int, int), int lower, int upper)
{
    int theNum;
    std::cout << prompt;
    std::cin >> theNum;

    while (!std::cin || !func(theNum, lower, upper))
    {
        if (!std::cin)
        {
            std::cout << "You entered something that is not a number!" << std::endl;
            resetStream();
        }
        std::cout << "You have entered invalid data." << std::endl;
        std::cout << prompt;
        std::cin >> theNum;
    }

    return theNum;
}
