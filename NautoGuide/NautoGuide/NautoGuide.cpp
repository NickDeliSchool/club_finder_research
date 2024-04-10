//Starting the NautoGuide project

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <array>
using namespace std;

int UnmergedSelection(string line);
bool EventDetector(string);
bool FindClubKeyword(string);
void MergeClubs();
string ClubNameCollector(string line);
string* DivisionOfClubName(string line);

// Array holding the keywords for detecting events
string eventKeywords[] = { "tournament", "match", "competition", "game", "event", "championship", "league", "meetup", "race", "friendly", "practice", "session", "playoff"}; 



//Array holding the keywords for detecting clubs (remember to add 'ground')
string clubKeywords[] = { "association", "company", "group", "union", "society", "circle", "lodge", "guild", "club", "ground", "centre"};


int word_count; // General word count for how many words are in the name of the specified club 

int main() {

	ifstream file("locaria.all_items.csv");

	if (!file.is_open()) {
	
		cerr << "Error, file couldn't be opened" << endl;
		return 0;
	}

	string line;


	while (getline(file, line)) {

		UnmergedSelection(line);
	
	}

	file.close();

	MergeClubs();

	cout << "Process succesfful" << endl;

	return 1;
}

int UnmergedSelection(string line) { // Selector that checks if something is an event, then if its a club, and prints it into the unmerged file

	if (!EventDetector(line)) {
		
		if (FindClubKeyword(line)) {


			ofstream UnmergedResult("UnmergedResult.csv", ios::app);

			if (!UnmergedResult.is_open()) {

				cerr << "Error, file couldn't be opened" << endl;
				return 0;
			}

			UnmergedResult << line << endl;

			UnmergedResult.close();


		}
	}

	else return 0;

}




bool EventDetector(string line) { // Detector to check if something is an event or not

	string* DividedName = DivisionOfClubName(line);
	
	if (DividedName[0] == "") {
	
		return false;
	
	}

	for (int j = 0; j <= word_count; j++) {

		for (int i = 0; i < 13; i++) {

			if (eventKeywords[i].compare(DividedName[j]) == 0) {

				return true;

			}
		}
	}
	return false;

}

bool FindClubKeyword(string line) { // Function that detects keywords indicating if the provided element is a club or not 

	string* DividedName = DivisionOfClubName(line);

	if (DividedName[0] == "") {

		return true;

	}

	for (int j = 0; j <= word_count; j++) {

		for (int i = 0; i < 12; i++) {

			if (clubKeywords[i].compare(DividedName[j]) == 0) {

				return true;

			}
		}
	}

	return false;

}

void MergeClubs() { // Function that merges the clubs

	ifstream UnmergedResult("UnmergedResult.csv");

	ofstream MergedResult("MergedResult.csv", ios::app);


	string line; 

	string* DividedName2;


	while (getline(UnmergedResult, line)) {

		DividedName2 = DivisionOfClubName(line); 

	}





	UnmergedResult.close();

	MergedResult.close();

}

string* DivisionOfClubName(string line) { // Function that divides the collected name into a string array containing each word

	int i = 0;

	int j = 0;

	string collectedName = ClubNameCollector(line);


	int count_spaces = 0;

	for (i = 0; i < collectedName.size(); i++)
	{
		collectedName[i] = tolower(collectedName[i]);

		if (isspace(collectedName[i]) != 0) {

			count_spaces++;

		}
	}

	string* DividedName = new string[count_spaces + 1];

	word_count = 0;

	for (i = 0; i < collectedName.size(); i++) {

		if (isspace(collectedName[i]) != 0) {

			word_count++;
			continue;

		}

		DividedName[word_count] += collectedName[i];

	}

	return DividedName;


}

string ClubNameCollector(string line) { // Function that collects the name of the specified club 

	string storeName;

	bool storeFollowingElements = false;

	bool storedClubNameChecker = false;

	for (int i = 0; i <= line.length() - 1; i++) {


		if (storeName == "title") {

			return "";

		}

		if (storedClubNameChecker == true) {

			return storeName;


		}


		if ((line.at(i) == ',') && (storeFollowingElements)) {

			storeFollowingElements = false;
			storedClubNameChecker = true;
			continue;

		}

		if ((line.at(i) == ',') && (!storeFollowingElements)) {

			storeFollowingElements = true;


		}


		if ((storeFollowingElements) && (line.at(i) != ',')) {

			storeName += line.at(i);

		}

	}

	cout << storeName << endl;


	return "";

}