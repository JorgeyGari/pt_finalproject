/*
Class Movie
*/

#include <iostream>
#include <vector>
#include "Actor.cpp"

using namespace std;

class Movie {
	private:
		string title;
		string genre;
		string director;
		int year;
		string actor;
		string desc;
		int price;
	
	public:
		//Default constructor
		Movie () {}
		
		//Parameterized constructor
		Movie (string t, string g, string dir, int y, string a, string des, int p) {
			title = t;
			genre = g;
			director = dir;
			year = y;
			actor = a;
			desc = des;
			price = p;
		}
		
		//Getters (Setters are not necessary for this exercise)
		string getTitle () {
			return title;
		}
		
		string getGenre () {
			return genre;
		}
		
		string getDirector () {
			return director;
		}
		
		int getYear () {
			return year;
		}
		
		string getActor () {
			return actor;
		}
		
		string getDesc () {
			return desc;
		}
		
		int getPrice () {
			return price;
		}
		
};
