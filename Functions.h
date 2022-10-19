/*
Functions for final project
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctime>
#include <conio.h>
#include <cmath>
#include "Movie.cpp"
#include "Rental.cpp"

using namespace std;

#define AVAILABILITY 3 

//Function to read the info of the actors from actors.txt
vector <Actor> readActors () {
	vector <Actor> actors;
	
	ifstream file;
	file.open("actors.txt");
	
	if (!file) {
		cout << "Error: File does not exist" << endl;
	} else {
		while (!file.eof()) {
			//Read name
			string name;
			getline (file, name);
			
			//Read birthdate
			int bd;
			file >> bd;
			file.ignore(1, '\n'); //Clear buffer before taking a new line
			
			//Read nationality
			string nation;
			getline (file, nation);
			
			//Creating an Actor with the read data and appending it to the end of the vector
			Actor cActor (name, bd, nation);
			actors.push_back (cActor);
		}
	}
	
	file.close();
	
	return actors;
}

//Function to read movies from movie.txt
vector <Movie> readMovies () {
	vector <Movie> movies;
	
	ifstream file;
	file.open ("movies.txt");
	
	if (!file) {
		cout << "Error: file does not exist" << endl;
	} else {
		while (!file.eof()) {
			//Read title
			string title;
			getline (file, title);
			
			//Read genre
			string genre;
			getline (file, genre);
			
			//Read director
			string director;
			getline (file, director);
			
			//Read year
			int year;
			file >> year;
			file.ignore(1, '\n'); //Clears the buffer before taking next line
			
			//Read actors
			string firstActor, secondActor, thirdActor;
			getline(file, firstActor);
			getline(file, secondActor);
			getline(file, thirdActor);
			
			//Read description
			string desc;
			getline (file, desc);
			
			//Read price
			double price;
			file >> price;
			file.ignore(1, '\n'); //Clears the buffer before taking next line
			
			//Creating a Movie with the read data and appending it to the end of the vector 
			Movie cMovie (title, genre, director, year, firstActor, desc, price);
			movies.push_back (cMovie);
		}
	}
	
	file.close ();
	
	return movies;
}

//Function to display the menu
int menu () {
	string s; //Even though the expected input is a number, we store it in a string to prevent the program from crashing due to an unexpected input
	cout << "Main menu" << endl;
	cout << "<< Movies Club >>" << endl;
	cout << "1. Watch online movies" << endl;
	cout << "2. Rent a movie DVD" << endl;
	cout << "3. Show DVD rentals" << endl;
	cout << "4. Show DVD availability" << endl;
	cout << "5. Exit" << endl;
	cout << "\nSelect an option: ";
	cin >> s;
	char c = s[0]; //We only get the first character because the expected input is only one character long
	int ascii = int(c); //We get the ASCII value of the first character the user inputs...
	int op;
	switch (ascii) { //...and, if it is a number, 'op' will match it
		case 49: { //49 is the ASCII value of character '1', and so on
			op = 1;
			break;
		}
		case 50: {
			op = 2;
			break;
		}
		case 51: {
			op = 3;
			break;
		}
		case 52: {
			op = 4;
			break;
		}
		case 53: {
			op = 5;
			break;
		}
		default: { //When it is not a valid option (not a number 1-5), 'op' defaults to -1
			op = -1;
			break;
		}
	}
	cout << endl;
	
	return op;
}

//Function to return the current date as int
int getCurrentDate(){
	time_t t = time(0);   // get time now
	tm* now = localtime(&t);
	
	int year = now->tm_year + 1900;
	int month = now->tm_mon + 1;
	int day = now->tm_mday;
	
	int currentDateAsInt = (year * 10000 ) + (month * 100) + day;
	
	return currentDateAsInt;
}

//Turn 18/03/2021 to int 20210318
int dateSplitter (string dateAsString) {
	vector <int> v;
	stringstream ss(dateAsString);
	for (int i; ss >> i;) {
		v.push_back(i); //Includes int 'i' in the vector 'v'.
		if (ss.peek() == '/') { //Searches for instances of the character '/'
			ss.ignore(); //Clears buffer
		}
	}
	
	int intDate;
	intDate = v[2] * 10000 + v[1] * 100 + v[0]; //Formats the date in ISO
	return intDate;
}

//Turn 31/04/2021 into 01/05/2021
int dateCorrector(int intDate) {
	/* First let us get the day, month and year from our date in YYYYMMDD format by using
	the % operator and taking advantage of int variables not storing decimal places */
	int d = intDate % 100;
	int m = (intDate % 10000 - d) / 100;
	int y = (intDate - 100 * m - d) / 10000;
	
	int a; //"a" (for "adjustments") counts how many adjustments were necessary to legalize the date

	// Now we check for illegal dates and repeat this until the date is legal
	do {	
		a = 0; // Resetting the adjustment counter
		
		// Converting illegal February dates into March dates:
		if ((d > 28) && (m == 2)) {
			m++; // We go to the next month, March
			d = d - 28; // The days exceeding 28 are the days passed in March
			a++;
			if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) { // If we are in a leap year:
				if (intDate % 100 == 229) // a) If the date happens to be a legal February 29th, no adjustment was needed
					a--;
				} else {
				d--; // b) We take the extra day February 29th into account by going back one day
			}
		}
		
		// Converting dates that surpass the 30 or 31 day limit
		if (d > 30) {
			switch (m) {
				case 1: case 3: case 5: case 7: case 8: case 10: case 12: // Months with 31 days
					if (d > 31) { // We exclude the case where the day is the 31st
						d = d - 31;
						m++;	// Similar to the algorithm we used to legalize February dates
						a++;	
					}
					break;
				case 4: case 6: case 9: case 11: // Months with 30 days
					d = d - 30;
					m++;
					a++;
					break;
			}
		}
		
		// Converting dates in Month 13
		if (m > 12) {
			y++;
			m = m - 12;
			a++;
		}
		
		intDate = y*10000 + m*100 + d;
		
	} while (a > 0);	// When the counter is zero, it means no adjustments were necessary, so no more checking is needed -- this date is now legal
	
	return intDate;
}

//Check if the date exists (is legal)
bool isLegalDate(int intDate) {
	// We repurpose part of the algorithm in the function "dateCorrector"
	
	int d = intDate % 100;
	int m = (intDate % 10000 - d) / 100;
	int y = (intDate - 100 * m - d) / 10000;
	
	if ((d < 1 || d > 31) || (m < 1 || m > 12) || (y < 1000 || y > 2021)) {
		return false;
	}
	
	if ((d > 28) && (m == 2)) {
			if (((y % 4 == 0) && (y % 100 != 0)) || (y % 400 == 0)) { 
				if (intDate % 100 == 229) {
					return true;
				}
			}
		return false;
	}
		
	if (d > 30) {
		switch (m) {
			case 1: case 3: case 5: case 7: case 8: case 10: case 12: 
				if (d > 31) {
					return false;
				}
				break;
			case 4: case 6: case 9: case 11:
				return false;
				break;
		}
	}
	
	if (m > 12) {
		return false;
	}
	
	return true;
}

//Function to get the current month
int getCurrentMonth(){
	time_t t = time(0);   // get time now
	tm* now = localtime(&t);
	
	int currentMonthAsInt = now->tm_mon + 1;

	return currentMonthAsInt;
}

//Function to turn the month as an integer to the name of the month
void numberToMonth (int m) {
	string month;
	switch (m) {
		case 1:{
			month = "January";
			break;
		}
		case 2: {
			month = "February";
			break;
		}
		case 3: {
			month = "March";
			break;
		}
		case 4: {
			month = "April";
			break;
		}
		case 5: {
			month = "May";
			break;
		}
		case 6: {
			month = "June";
			break;
		}
		case 7: {
			month = "July";
			break;
		}
		case 8: {
			month = "August";
			break;
		}
		case 9: {
			month = "September";
			break;
		}
		case 10: {
			month = "October";
			break;
		}
		case 11: {
			month = "November";
			break;
		}
		case 12: {
			month = "December";
			break;
		}
		default: {
			month = "Unknown Month";
			break;
		}
	}
	
	cout << month;
}

/* 
Main functions
*/

//1. Watch online movies
void watch (vector<Movie> movies) {
	string query;
	cout << "Introduce the title of the movie:\n";
	cin.ignore();
	getline (cin, query);
	
	double p = 0;
	for (int i = 0; i < movies.size(); i++) {
		if (query.compare(movies[i].getTitle()) == 0) {
			p = movies[i].getPrice();
		}
	}
	if (p == 0) { // As to not create a rental for a movie that does not exist, we use "p" to check if the movie the user asks for is in the catalog
	// When the movie is not it the catalog ("movies.txt"), its price is 0 by default
		cout << "No listings for '" << query << "' were found in our catalog.\n" << endl;
	} else { // If the movie is in the catalog, it will have a price
		cout << "Total price: EUR " << p << endl;
		char cont;
		cout << "Do you want to continue (Y/N)? " << endl;
		cin >> cont;
		
		while ((cont != 'Y') && (cont != 'y') && (cont != 'N') && (cont != 'n')) { // Case-insensitive
			cout << "Not a valid option." << endl << "Do you want to continue (Y/N)? " << endl;
			cin >> cont;
		}
		
		switch (cont) {
			case 'Y': case 'y': {
				string user, exp, card;
				cout << "Introduce complete name:\n";
				cin.ignore();
				getline (cin, user);
				do {
					cout << "Introduce your credit card number:\n";
					cin >> card;
					if (card.size() != 16) {
						cout << "Not a valid credit card number." << endl;
					}
				} while(card.size() != 16); //Checks if the card number is long enough (16 digits)
				cout << "Introduce the expiration month:\n";
				cin >> exp;
				cout << "The payment has been made.\n" << endl;
				cout << "Thank you for using our www.moviesclubagency.net\n" << endl;
				cout << "To watch the movie, please follow the following link with the password: " << rand() % 89999 + 100000 << "\n"; //The password is a randomly generated six-digit number
				cout << "www.moviesclubagency.net/login/\n" << endl;
				cout << "Press any key to return to the main menu...\n" << endl;
				system ("pause > nul"); //Calls system to stop the program until any key is pressed. nul hides the default text (it is in Spanish)
				break;
			} case 'N': case 'n': {
				cout << "Purchase cancelled." << endl;
				break;
			}
		}
	}
}

//2. Rent a movie DVD
Rental rent (vector <Movie> movies, vector <Rental> rentals) {
	Rental rent;
	bool movieExists = false;
	string query;
	cout << "Introduce the title of the movie:\n";
	cin.ignore();
	getline (cin, query);
	for (int i = 0; i < movies.size(); i++) {
		if (query.compare(movies[i].getTitle()) == 0) {
			movieExists = true;
		}
	}
	if (!movieExists) {
		cout << "No listings for '" << query << "' were found in our catalog.\n" << endl;
	} else {
		string stDate;
		cout << "Introduce start date:\n";
		cin >> stDate;
		int intDate;
		intDate = dateSplitter(stDate);
		while (!isLegalDate(intDate) || intDate < getCurrentDate()) { // Movie rentals for past dates are not allowed
			cout << "Not a valid date." << endl;
			cout << "Introduce start date:\n";
			cin >> stDate;
			intDate = dateSplitter(stDate);
		}
		
		string s;
		int days;
		do {
			cout << "Introduce how many days:\n";
			cin >> s;
			if (!isdigit(s[0])) { //Check that the first element of the string is a digit
				cout << "Not a number.\n";
			}
		} while (!isdigit(s[0]));
		
		days = stoi(s); //Turn the first elements that are digits into integers
		int intEndDate;
		intEndDate = dateCorrector(intDate + days);
		
		int c; //'c' for 'current'
		for (int i = 0; i < movies.size(); i++) {
			if (query.compare(movies[i].getTitle()) == 0) {
				c = i;
			}
		}
		
		int isAvailable = AVAILABILITY;
		for (int i = 0; i < rentals.size(); i++) {
			if (((rentals[i].getStartDate() >= intDate) && (rentals[i].getStartDate() <= intEndDate)) || ((rentals[i].getEndDate() >= intDate) && (rentals[i].getEndDate() <= intEndDate)) || ((intDate >= rentals[i].getStartDate()) && (intEndDate <= rentals[i].getEndDate()))) {
				//This very long condition checks if the start or end date are contained in the timespan of a preexisting rental or if the preexisting rental is contained in the timespan between the start and end dates
				isAvailable--;
			}
		}
		
		if (isAvailable < 1) {
			cout << "There is no available DVD for " << query << " for the specified dates.\nPress any key to return to the main menu...\n" << endl;
			system ("pause > nul");
		} else {
			double p;
			p = movies[c].getPrice() * days;
			cout << "Total price: EUR " << p << endl;
			
			char cont;
			cout << "Do you want to continue (Y/N)? " << endl;
			cin >> cont;
			
			while ((cont != 'N') && (cont != 'Y') && (cont != 'n') && (cont != 'y')) {
				cout << "Not a valid option." << endl << "Do you want to continue (Y/N)? " << endl;
				cin >> cont;
			}
			
			switch (cont) {
				case 'Y': case 'y': {
					string user, card, exp;
					cout << "Introduce complete name:\n";
					cin.ignore();
					getline (cin, user);
					do {
						cout << "Introduce your credit card number:\n";
						cin >> card;
						if (card.size() != 16) {
							cout << "Not a valid credit card number." << endl;
						}
					} while(card.size() != 16); //Checks if the card number is long enough (16 digits)
					cout << "Introduce the expiration month:\n";
					cin >> exp;
					cout << "The payment has been made.\n" << endl;
					
					//Set the values for the rental in the Rental class' object
					rent.setTitle(query);
					rent.setStartDate(intDate);
					rent.setEndDate(intEndDate);
					rent.setPrice(p);
					rent.setUser(user);
					
					cout << "Thank you for using our www.moviesclubagency.net\n" << endl;
					
					cout << "The movie        : " << query << endl;
					cout << "Rental start date: " << Date::showDate (intDate) << endl;
					cout << "Rental end time  : " << Date::showDate (intEndDate) << endl;
					cout << "Total price      : EUR " << p << endl;
					cout << "Client's name    : " << user << endl;
					
					cout << "\nPress any key to return to the main menu...\n" << endl;
					system ("pause > nul");
					break;
				} case 'N': case 'n': {
					cout << "Purchase cancelled." << endl;
					break;
				}
			}
		}
		return rent;
	}
}

//3. Show DVD rentals
void showRentals (vector <Rental> rent, vector <Movie> movies) {
	string query;
	bool movieExists;
	cout << "Introduce the title of the movie:\n";
	cin.ignore();
	getline(cin, query);
	
	for (int i = 0; i < movies.size(); i++) {
		if (query.compare(movies[i].getTitle()) == 0) {
			movieExists = true;
		}
	}
	if (!movieExists) {
		cout << "No listings for '" << query << "' were found in our catalog.\n" << endl;
	} else {
		int currentMonth = getCurrentMonth();
		cout << "\nList of rents of the movie " << query << " in ";
		numberToMonth (currentMonth);
		cout << " is:" << endl;
		cout << "Client's name                 Start date    End date      Total price" << endl;
		cout << "---------------------------------------------------------------------" << endl;
		
		for (int i = 0; i < rent.size(); i++) {
			/* We only print the elements in the vector whose title matches
			the query and whose start or end date is in the current month */		
			if ((query.compare(rent[i].getTitle()) == 0) && (((rent[i].getStartDate() % 10000 >= currentMonth*100 + 1) && ((rent[i].getStartDate()) % 10000 <= currentMonth*100 + 31)) || ((((rent[i].getEndDate()) % 10000 >= currentMonth*100 + 1) && ((rent[i].getEndDate()) % 10000 <= currentMonth*100 + 31))))) {
				// In order to keep the formatting of the list tidy, we will check the length of the user's name
				if (rent[i].getUser().size() <= 26) {
					cout << rent[i].getUser();
					for (int j = 0; j < 30 - rent[i].getUser().size(); j++) { // 30 = 26 + 4, the 4 extra spaces are the space between each column
						cout << " ";
					}
				} else {
					cout << rent[i].getUser().substr(0,23) << "...    ";
				}
				cout << Date::showDate(rent[i].getStartDate()) << "    ";
				cout << Date::showDate(rent[i].getEndDate()) << "    ";
				cout << "EUR " << rent[i].getPrice() << endl;
			}
		}
		
		cout << endl;
	}
}

//4. Show DVD availability
void showAvailability (vector <Rental> rent, vector <Movie> movies) {
	int currentMonth = getCurrentMonth();
	
	cout << "\nList of availability of movies in ";
	numberToMonth (currentMonth);
	cout << " is:" << endl;
	cout << "Movie title                   Director             Year    1st actor                Description              " << endl;
	cout << "-------------------------------------------------------------------------------------------------------------" << endl;
	int currentYear = getCurrentDate() / 10000;
	
	int daysInMonth;
	switch (currentMonth) {
		case 1: case 3: case 5: case 7: case 8: case 10: case 12: {
			daysInMonth = 31;
			break;
		}
		case 2: {
			if (((currentYear % 4 == 0) && (currentYear % 100 != 0)) || (currentYear % 400 == 0)){
				daysInMonth = 29;
			} else {
				daysInMonth = 28;
			}
			break;
		}
		case 4:	case 6:	case 9:	case 11: {
			daysInMonth = 30;
			break;
		}
	}
	
	for (int i = 0; i < movies.size(); i++) {
		bool everyDay = true;		
		for (int j = getCurrentDate(); j < daysInMonth + (currentYear * 10000) + (currentMonth * 100); j++) {
			int isAvailable = AVAILABILITY;
			
			for (int k = 0; k < rent.size(); k++) {
				if (rent[k].getStartDate() <= j && rent[k].getEndDate() >= j && movies[i].getTitle().compare(rent[k].getTitle()) == 0) {
					isAvailable--;
				}
			}
			if (isAvailable < 1) {
				everyDay = false;
			}
		}
		if (everyDay) { 
			cout << movies[i].getTitle(); // The longest title of a movie in our database is 26 characters long
			for (int l = 0; l < 30 - movies[i].getTitle().size(); l++) {
				cout << " ";
			}
			cout << movies[i].getDirector(); // The longest name of a director in our database is 17 characters long
			for (int l = 0; l < 21 - movies[i].getDirector().size(); l++) {
				cout << " ";
			}
			cout << movies[i].getYear() << "    ";
			cout << movies[i].getActor(); // The longest name of an actor in our database is 21 characters long
			for (int l = 0; l < 25 - movies[i].getActor().size(); l++) {
				cout << " ";
			}
			// Each line of the description will be 25 characters long
			for (int l = 0; l*25 < movies[i].getDesc().size(); l++) {
				if (l != 0) {
					for (int m = 0; m < 81; m++) {
						cout << " ";
					}
				}
				cout << movies[i].getDesc().substr(l*25,25) << endl;
			} 
		};
	};
	cout << endl;
}
