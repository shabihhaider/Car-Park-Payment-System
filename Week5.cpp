#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

int calculateCheckDigit(string frequentParkingNumber) 
{
    int weights[] = {8, 6, 4, 2, 3};
    int sum = 0;
    for (int i = 0; i < 4; i++) 
	{
        sum += (frequentParkingNumber[i] - '0') * weights[i];
    }
    int checkDigit = (11 - (sum % 11)) % 11;
    
    if(checkDigit == 10)
	{
    	checkDigit = 0;
	}
	
    return checkDigit;
}

double calculateParkingPrice(string dayOfWeek, int arrivalHour, int numHours, string frequentParkingNumber) 
{
    double pricePerHour;
    double totalPrice = 0.0;
    int discountPercent = (arrivalHour >= 16 && arrivalHour <= 23) ? 50 : 10;
    
    bool discountApplied = false;

    if (dayOfWeek == "Sunday")
        pricePerHour = (arrivalHour >= 8 && arrivalHour < 16) ? 2.00 : 2.00;
    else if (dayOfWeek == "Saturday")
        pricePerHour = (arrivalHour >= 8 && arrivalHour < 16) ? 3.00 : 2.00;
    else
        pricePerHour = (arrivalHour >= 8 && arrivalHour < 16) ? 10.00 : 2.00;

   if (!frequentParkingNumber.empty() && frequentParkingNumber.length() >= 5) 
   {
  int checkDigit = calculateCheckDigit(frequentParkingNumber.substr(0, 4));
  if (checkDigit == frequentParkingNumber[frequentParkingNumber.length() - 1] - '0') 
  {
    discountApplied = true;
  }
}
    totalPrice = numHours * pricePerHour;

    if (discountApplied) {
        totalPrice -= (totalPrice * discountPercent) / 100;
}
    return totalPrice;
}

int main() 
{
    // Task1
    string dayOfWeek;
    int arrivalHour;
    int numHours;
    string frequentParkingNumber;

    cout << "Enter the day of the week: ";
    cin >> dayOfWeek;
    cout << "Enter the hour of arrival (0-23): ";
    cin >> arrivalHour;
    cout << "Enter the number of hours to park: ";
    cin >> numHours;
    cout << "Enter frequent parking number (if available): ";
    cin >> frequentParkingNumber;

    double totalPrice = calculateParkingPrice(dayOfWeek, arrivalHour, numHours, frequentParkingNumber);
    cout << fixed << setprecision(2);
    cout << "Total price to park: $" << totalPrice << endl;

    // Task2
    double dailyTotal = totalPrice;

    // Task3
    if (arrivalHour < 16 && arrivalHour + numHours >= 16) 
	{
        double priceBeforeEveningCharge = calculateParkingPrice(dayOfWeek, arrivalHour, 16 - arrivalHour, frequentParkingNumber);
        double eveningCharge = calculateParkingPrice(dayOfWeek, 16, arrivalHour + numHours - 16, frequentParkingNumber);
        totalPrice = priceBeforeEveningCharge + eveningCharge;
        cout << "Price before 16:00: $" << priceBeforeEveningCharge << endl;
        cout << "Evening charge after 16:00: $" << eveningCharge << endl;
        cout << "Total price with fairer charging: $" << totalPrice << endl;
    }

    return 0;
}


