// Victor Pueyo 
// This is my Lab 2
// I have neither given nor received unauthorized aid in completing this work, nor have I presented someone else's work as my own.

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using namespace std;

//Functions
int process_employees(string&, float&, int&, ifstream&);
void process_payroll(string[], int[], int, float[], int, ofstream&);
void print_results(string[], int[], int, float[], ofstream&);
int maximumPay(const float[], int);
int minimumPay(const float[], int);
double averagePay(const float[], int, int);

int main()
{
	const int SIZE = 15;
	int Hours[SIZE];
	float Wage[SIZE];
	string Name[SIZE];
	int count = 0;
	ifstream input;
	ofstream output;

	input.open("input.txt");
	output.open("output.txt");

	//It will check if the input file is able to open
	if (input.fail())
	{
		cout << "Input file failed to open\n" << endl;
		system("pause");
		exit(0);
	}

	//It will check if the output file opened or not, if it fails it will say that it failed to open
	if (output)
		;
	else
	{
		cout << "Output file failed to open" << endl;
		system("pause");
		exit(1);
	}

	//Checks if there are more than 10 names, if there are more a ERROR message will appear 
	while (process_employees(Name[count], Wage[count], Hours[count], input))
	{
		count++;
		if (count == 11)
		{
			cout << "ERROR: There are more than 10 names" << endl << endl;
			output << "ERROR: There are more than 10 names" << endl << endl;
		}
	}

	cout << fixed << setprecision(2);

	process_payroll(Name, Hours, count, Wage, count, output);

	//Displays the headers of the table October 2009 Payroll
	cout << "October 2009 Payroll:" << endl << endl;
	cout << setw(10) << left << "Name" << setw(14) << right << "Hours" << setw(12) << "Rate" << setw(9) << "Gross"
		<< setw(11) << "Bonus" << setw(19) << "Adjusted Gross" << endl << endl;
	output << "October 2009 Payroll:" << endl << endl;
	output << setw(10) << left << "Name" << setw(14) << right << "Hours" << setw(12) << "Rate" << setw(9) << "Gross"
		<< setw(11) << "Bonus" << setw(19) << "Adjusted Gross" << endl << endl;

	print_results(Name, Hours, count, Wage, output);

	system("pause");
	return 0;
}

//The function takes the information from the input text file. If the employee's information is read successfully it will return 1 or 0
//if it is not read correctly
int process_employees(string& Name, float& Wage, int& Hours, ifstream& input)
{
	int count = 0;

	while (input >> Name >> Wage >> Hours && count < 15)
		return 1;

	return 0;
}

//The function puts the returned value from the functions maximumPay, minimumPay and averagePay into the local variable max, min and avg. 
//Then, the program prints the number of employees, maximum pay rate, minimum pay rate and average pay 
void process_payroll(string Name[], int Hours[], int employee, float Wage[], int count, ofstream& output)
{
	int max, min;
	float avg;
	string maxPay, minPay;

	//Puts the returned value from the functions maximumPay, minimumPay and averagePay into the local variable max, min and avg
	max = maximumPay(Wage, count);
	min = minimumPay(Wage, count);
	avg = averagePay(Wage, count, employee);

	maxPay = Name[max];
	minPay = Name[min];

	cout << setprecision(2) << fixed;
	output << setprecision(2) << fixed;

	//Displays the number of employee, maximum pay rate, minimum pay rate and average pay 
	cout << "Number of Employees: " << employee << endl << endl;
	cout << "Maximum Pay Rate: " << maxPay << " @ $" << Wage[max] << endl << endl;
	cout << "Minimun Pay Rate: " << minPay << " @ $" << Wage[min] << endl << endl;
	cout << "Average Pay: $" << avg << endl << endl;
	output << "Number of Employees: " << employee << endl << endl;
	output << "Maximum Pay Rate: " << maxPay << " @ $" << Wage[max] << endl << endl;
	output << "Minimun Pay Rate: " << minPay << " @ $" << Wage[min] << endl << endl;
	output << "Average Pay: $" << avg << endl << endl;

	return;
}

// The function calculates the FINE and Bonus of the emplyees and displays the table of October 2009 Payroll
void print_results(string employeeName[15], int hour[15], int i, float wages[15], ofstream& output)
{
	const float FINE = .25;
	const int BONUS = 50;

	//This part displays the table of October 2009 Payroll
	for (int j = 0; j < i; j++)
	{
		cout << setw(10) << left << employeeName[j] << right << setw(14) << hour[j] << setw(12) << wages[j] << setw(10) << wages[j] * hour[j];
		output << setw(10) << left << employeeName[j] << right << setw(14) << hour[j] << setw(12) << wages[j] << setw(10) << wages[j] * hour[j];

		if (hour[j] > 45)
		{
			cout << setw(10) << "Y" << setw(20) << wages[j] * hour[j] + BONUS << endl;
			output << setw(10) << "Y" << setw(20) << wages[j] * hour[j] + BONUS << endl;
		}
		else if (hour[j] < 30)
		{
			cout << setw(10) << "N" << setw(20) << (wages[j] - FINE) * hour[j] << endl;
			output << setw(10) << "N" << setw(20) << (wages[j] - FINE) * hour[j] << endl;
		}
		else
		{
			cout << setw(10) << "N" << setw(20) << wages[j] * hour[j] << endl;
			output << setw(10) << "N" << setw(20) << wages[j] * hour[j] << endl;
		}
	}
	cout << endl;

	return;
}

// The function calculates the maximum Pay, once it is calculated it is returned to the function process_payroll
int maximumPay(const float Rate[], int count)
{
	int high = 0, highest = -999999;

	for (int i = 0; i < count; i++)
	{
		if (Rate[i] > highest)
		{
			high = i;
			highest = Rate[i];
		}
	}
	return high;
}

// The function calculates the minimum Pay, once it is calculated it is returned to the function process_payroll
int minimumPay(const float rate[], int count)
{
	int low = 0, lowest = 999999;

	for (int i = 0; i < count; i++)
	{
		if (rate[i] < lowest)
		{
			low = i;
			lowest = rate[i];
		}
	}
	return low;
}

// The function calculates the average Pay, once it is calculated it is returned to the function process_payroll
double averagePay(const float rate[], int count, int employeeNum)
{
	float avg = 0;
	float averagePay;

	for (int i = 0; i < count; i++)
	{
		avg += rate[i];
	}

	averagePay = avg / employeeNum;

	return averagePay;
}