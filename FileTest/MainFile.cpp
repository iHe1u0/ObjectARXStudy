#include "MainFile.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


void writeDataToFile(double data) {

	ofstream of("out.txt");
	if (of.is_open())
	{
		of << noskipws;
		of.showpoint;
		//of.precision(8);
		of << data;
		of.close();
	}
}

void readFromFile(char *ch) {
	ifstream fin("out.txt");
	string s;
	while (fin >> s)
	{
		cout << "Read from file: " << s << endl;

	}
	cout << s << endl;

}


int main() {

	double data = 1232.435060007;
	writeDataToFile(data);

	char* result = new char;
	readFromFile(result);
	//cout << result;
	return 0;
}