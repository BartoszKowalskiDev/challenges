/*Challenge 399*/
/*
 * Assign every lowercase letter a value, from 1 for a to 26 for z. Given a string of lowercase letters, find the sum of the values of the letters in the string.

	lettersum("") => 0
	lettersum("a") => 1
	lettersum("z") => 26
	lettersum("cab") => 6
	lettersum("excellent") => 100
	lettersum("microspectrophotometries") => 317
*/

#include <iostream>
#include <string>
//#include <algorithm>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

int lettersum(const string&);
vector<string> getDataFrom(string, size_t = 0);
void displayLettersum(const string&);
void searchForLettersum(const vector<string>&, size_t);
map<int, int> mapCommonLettersum(const vector<string>&);
//mostCommonLettersum


struct MostCommonLetterSum {
	int sum;
	int count;
};
ostream& operator << (ostream& os, MostCommonLetterSum& m) {
	os << "Letter sum: " << m.sum << " number of words: " << m.count;
	return os;
}
MostCommonLetterSum mostCommonLettersum(map<int, int>&);


int main() {

	vector<string> wordList;
	wordList = getDataFrom("enable1.txt");

	int breakPoint = 10;
	for (size_t i = 0; i < breakPoint; ++i) {
		displayLettersum(wordList[i]);
	}
	displayLettersum("excellent");
	
	/*1. microspectrophotometries is the only word with a letter sum of 317. Find the only word with a letter sum of 319.*/
	cout << "\n1. ";
	searchForLettersum(wordList, 319);

	/*2. How many words have an odd letter sum?*/
	size_t oddCounter = 0;
	for (string word : wordList)
		if (lettersum(word) % 2 == 1)
			++oddCounter;
	cout << "\n2. oddCounter => " << oddCounter << endl;

	
	/*3. There are 1921 words with a letter sum of 100, making it the second most common letter sum. What letter sum is most common, and how many words have it?*/
	//mostCommonLettersum(wordList);
	map<int, int> mapedCommonLettersum = mapCommonLettersum(wordList);
	MostCommonLetterSum mclt = mostCommonLettersum(mapedCommonLettersum);
	cout << "\n3." <<  mclt;
	//for (auto& m : mapedCommonLettersum)
		//cout << m.first << ", " << m.second << endl;

	/*4. zyzzyva and biodegradabilities have the same letter sum as each other (151), and their lengths differ by 11 letters. 
	Find the other pair of words with the same letter sum whose lengths differ by 11 letters.*/

	/*5. cytotoxicity and unreservedness have the same letter sum as each other (188), and they have no letters in common. 
	Find a pair of words that have no letters in common, and that have the same letter sum, which is larger than 188. 
	(There are two such pairs, and one word appears in both pairs.)*/

	/*The list of word { geographically, eavesdropper, woodworker, oxymorons } contains 4 words. 
	Each word in the list has both a different number of letters, and a different letter sum. 
	The list is sorted both in descending order of word length, and ascending order of letter sum. 
	What's the longest such list you can find?*/

	cout << endl;
	return 0;
}


MostCommonLetterSum mostCommonLettersum(map<int, int>& map) {
	MostCommonLetterSum mclt;
	mclt.sum = 0;
	mclt.count = 0;

	for (auto& m : map) {
		if (m.second > mclt.count) {
			mclt.sum = m.first;
			mclt.count = m.second;
		}
	}

	return mclt;
}

map<int, int> mapCommonLettersum(const vector<string>& vec) {
	map<int, int> data;
	for (string word : vec) {
		int sum = lettersum(word);
		auto search = data.find(sum);
		if (search != data.end()) {
			search->second++;
		}
		else {
			data.insert({ sum, 1});
		}
	}
	return data;
}

void searchForLettersum(const vector<string> &vec ,size_t sum) {
	for (string word : vec) {
		if (lettersum(word) == sum) {
			displayLettersum(word);
		}
			
	}
}

int lettersum(const string &word) {
	
	size_t length = word.size();
	if (length == 0)
		return 0;

	//transform(word.begin(), word.end(), word.begin(), tolower);
	unsigned short int offset = 96;
	int sum = 0;
	for (char c : word) {
		sum += (int)c-offset;
	}
	
	return sum;
}

void displayLettersum(const string &word) {
	cout << "lettersum(\"" << word << "\") => " << lettersum(word) << endl;
}


vector<string> getDataFrom(string filename, size_t amount) {
	fstream file;
	file.open(filename, ios::in);

	vector<string> data;
	int counter = 0;
	if (file.is_open()) {
		string s;

		while (file >> s)
		{
			data.push_back(s);

			counter++;
			if (amount != 0 && counter == amount)
				break;
		}
	}
	
	file.close();

	return data;
}