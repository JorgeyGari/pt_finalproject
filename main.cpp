/*
Final project
*/

#include <iostream>
#include "Functions.h"

using namespace std;

int main () {
	int op = menu();
	
	vector <Actor> actors = readActors ();
	vector <Movie> movies = readMovies ();
	vector <Rental> rentals;
	
	cout << fixed; //Set how doubles are displayed
	cout.precision(2); //Set doubles to be displayed with two decimal places
	
	do {
		switch (op) {
			case 1: {
				watch (movies);
				break;
			}
			case 2: {
				Rental r;
				r = rent (movies, rentals);
				rentals.push_back(r);
				break;
			}
			case 3: {
				showRentals (rentals, movies);
				break;
			}
			case 4: {
				showAvailability (rentals, movies);
				break;
			}
			default: {
				cout << "Not a valid option.\n" << endl;
				break;
			}
		}
		op = menu();		
	} while (op != 5);
}
