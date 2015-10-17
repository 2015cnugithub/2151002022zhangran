#include <iostream>
using namespace std;

bool is_leap_year(int i){
	if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0) return true;
	else return false;
}

int day_of_month(int month,int year){
	if (month == 2){
		if (is_leap_year(year))return 29;
		else return 28;
	}
	else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) return 31;
	else return 30;
}

int main(){
	//Enter
	cout << "Please enter a year:";
	int year;
	cin >> year;
	cout << "Please enter a month chosen from(1,2,3,4,5,6,7,8,9,10,11,12):";
	int month;
	cin >> month;

	//count days
	int days=0;
	int i;
	for (i = 1800; i < year; i++){
		if (is_leap_year(i)) days += 366;
		else days += 365;
	}
	for (i = 1; i < month; i++)days += day_of_month(i,year);

	//Print
	int start_day =(days+3) % 7;
	cout << endl << "             " << year << "." << month << endl << "  ---------------------------------" << endl <<
		"  Sun  Mon  Tue  Wed  Thu  Fri  Sat" << endl;
	for (i = 0; i < start_day; i++)cout << "     ";
	for (i = 1; i <= day_of_month(month, year); i++){
		printf("%5d", i);
		if ((i + start_day) % 7 == 0)cout << endl;
	}
	cout << endl<<endl;

	system("pause");
	return 0;
}