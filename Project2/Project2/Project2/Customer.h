#pragma once
#include "Header.h"
#include "order.h"
#pragma warning(disable : 4996)

using namespace std;

class customer : public order{
protected:
	string name;
public:
	vector<order> orders;
	string getName();
	void setName(string);
	void displayCustomerRecord();
	void readInRecord();
	void saveRecordToFile();
};

void customer::setName(string n) {
	name = n;
}

string customer::getName() {
	return name;
}

void customer::displayCustomerRecord() {
	cout << "customer: " << name << endl;
	cout << "Dates visited with items they bought : " << endl;
	for (int i = 0; i < orders.size() ; i++) {
		cout << orders.at(i).getDate() << ":" << endl;
		for (int j = 0; j < orders.at(i).itemsBought.size(); j++) {
			cout << orders.at(i).itemsBought.at(j).getName() << endl;
			orders.at(i).addToTotal(orders.at(i).itemsBought.at(j).getPrice());
		}
		cout << "Total order price: " << orders.at(i).getTotal() << endl;
	}
}

void customer::readInRecord() {
	/*fstream file;
	string tmpDate, tmpNumItems, tmpTotal;
	vector<string> tmpItems;

	string standardPath = "C:/Users/ceesu/source/repos/Project2/Project2/customers/" + name +".txt";
	
	START:

	file.open(standardPath);

	if (!file.is_open()) {
		cout << "customer has no previous record, creating one now ..." << endl;
		file.open(standardPath, ios::out);
		if (!file) {
			cout << "Error creating file" << endl;
		}
		else {
			cout << "File created successfully ..." << endl;
			goto START;
		}
	}
	else {
		while (!file.eof()) {
			file >> tmpDate >> tmpNumItems >> tmpTotal;
			orders.
		}
	}*/
}

void customer::saveRecordToFile() {
	fstream file;
	
	string standardPath = "C:/Users/ceesu/source/repos/Project2/Project2/customers/" + name + ".txt";

START:

	file.open(standardPath);

	if (!file.is_open()) {
		cout << "customer has no previous record, creating one now ..." << endl;
		file.open(standardPath, ios::out);
		if (!file) {
			cout << "Error creating file" << endl;
		}
		else {
			cout << "File created successfully ..." << endl;
			goto START;
		}
	}
	else {
		file.close();
		file.open(standardPath, ios::app);

		for (int i = 0; i < orders.size(); i++) {
			file << orders.at(i).getDate();
			file << "# of items: " << orders.at(i).itemsBought.size() << endl;
			file << "total: $" << orders.at(i).getTotal() << endl;
			file << "items: " << endl;
			for (int j = 0; j < orders.at(i).itemsBought.size(); j++) {
				file << orders.at(i).itemsBought.at(j).getName() << endl;
			}
			
		}
		file << endl;
	}

}
