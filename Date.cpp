/*
Class Date
*/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;

class Date {
	
	private:
		int day, month, year;
		
	public:
		
		//Default constructor 
		Date(){
			day = 0;
			month = 0;
			year = 0;
		}
		
		//Parameterized construtor
		Date(int d, int m, int y){
			
			if (d < 1 || d > 31) throw "Invalid day";
			if (m < 1 || m > 12) throw "Invalid month";
			if (y < 1000 || y > 2021) throw "Invalid year";
			day = d;	
			month = m;
			year = y;
		}
		
		//Setters
		void setDay(int d){
			if (d < 1 || d > 31) throw "Invalid day";
			day = d;
		}
		
		void setMonth(int m){
			if (m < 1 || m > 12) throw "Invalid month";
			month = m;
		}
		
		void setYear(int y){
			if (y < 1000 || y > 2021) throw "Invalid year";
			year = y;
		}
		
		//Getters
		int getDay(){
			return day;
		}
		
		int getMonth(){
			return month;
		}
		
		int getYear(){
			return year;
		}
		
		//Functions
		int compare(Date date){
			int myDateAsNumber = convert();
			int otherDateASNumber = date.convert();
			int result = -2;
			
			if (myDateAsNumber < otherDateASNumber ) result = -1;
			else if (myDateAsNumber > otherDateASNumber ) result = 1;
			else result = 0;
			
			return result;
		}
		
		int convert(){
			int dateAsNumber;
			dateAsNumber = (year * 10000) + (month * 100) + day;
			return dateAsNumber;
		}
		
		//20210318
		// year = 20210318 / 10000 = 2021
		// month = (20210318 % 2021) / 100 = 3
		// day = (20210318 % 2021) % 100 = 18
		//18/03/2021
		
		static string showDate(int numberDate){
			int yearFromNumber = numberDate / 10000;
			int monthFromNumber = (numberDate % yearFromNumber) / 100;
			int dayFromNumber = (numberDate % yearFromNumber) % 100;
			
			
			string dateAsString; 
			string d = to_string(dayFromNumber);
			string m = to_string(monthFromNumber);
			string y = to_string(yearFromNumber);
			if (dayFromNumber<10) d = '0' + d;
			if (monthFromNumber<10) m = '0' + m;
			dateAsString = d + "/" + m + "/" + y;
			
			return dateAsString;
		}
		
		bool operator < (Date date){
			bool thisIsLowerThanDate;
			
			if (convert() < date.convert()){
				thisIsLowerThanDate = true;
			}else{
				thisIsLowerThanDate = false;
			}
			
			return thisIsLowerThanDate;
		}
		
		bool operator > (Date date){
			bool thisIsGreaterThanDate;
			
			if (convert() > date.convert()){
				thisIsGreaterThanDate = true;
			}else{
				thisIsGreaterThanDate = false;
			}
			
			return thisIsGreaterThanDate;
		}
		
		bool operator == (Date date){
			bool thisIsEqualToDate;
			
			if (convert() == date.convert()){
				thisIsEqualToDate = true;
			}else{
				thisIsEqualToDate = false;
			}
			
			return thisIsEqualToDate;
		}
		
		bool isLeapYear(){
			bool leapYear;
			
			if (((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0)){
				leapYear = true;
			}else{
				leapYear = false;
			}
			
			return leapYear;
		}
		
		static void sort(vector<int> &v){
			int temp = 0;
			
			for (int i = 0; i < v.size(); i++){
				for(int j = i; j > 0; j--){
					if (v[j] < v[j-1]){
						temp = v[j];
						v[j] = v[j-1];
						v[j-1] = temp;
					}
				}
			}
			
			for(int i = 0; i < v.size(); i++){
				cout << Date::showDate(v[i]) << endl;
			}
		}
};
