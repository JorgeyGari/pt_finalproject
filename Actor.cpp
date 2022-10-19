/*
Class Actor
*/

#include <iostream>
#include <vector>

using namespace std;

class Actor {
	private:
		string name;
		int birthday;
		string nation;
	
	public:
		//Default constructor
		Actor () {}
		
		//Parameterized constructor
		Actor (string nm, int b, string nt) {
			name = nm;
			birthday = b;
			nation = nt;
		}
		
		//Getters (Setters are not necessary for this exercise)
		string getName () {
			return name;
		}
		
		int getBirthday () {
			return birthday;
		}
		
		string getNation () {
			return nation;
		}
};
