/*
Class Rental
*/

#include <iostream>
#include "Date.cpp"

using namespace std;

class Rental {
	private:
		string title;
		int startDate;
		int endDate;
		double price;
		string user;
		
	public:
		//Default constructor
		Rental(){
			title = "No title";
			startDate = 0;
			endDate = 0;
			price = 0;
			user = "No name";
		}
		
		//Parametrized constructor
		Rental(string t, int s, int e, double p, string u){
			title = t;
			startDate = s;
			endDate = e;
			price = p;
			user = u;
		}
		
		//Getters
		string getTitle() {
			return title;
		}
		
		int getStartDate() {
			return startDate;
		}
		
		int getEndDate() {
			return endDate;
		}
		
		double getPrice() {
			return price;
		}
		
		string getUser() {
			return user;
		}
		
		//Setters
		void setTitle (string t) {
			title = t;
		}
		
		void setStartDate (int st) {
			startDate = st;
		}
		
		void setEndDate (int ed) {
			endDate = ed;
		}
		
		void setPrice (double p) {
			price = p;
		}
		
		void setUser (string u) {
			user = u;
		}
};
