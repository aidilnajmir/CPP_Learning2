#pragma once
#include "Header.h"
#include "item.h"
#pragma warning(disable : 4996)



using namespace std;

class inventory{
protected:
	
public:
	vector<item> itemList;
	void addItem(item);
	void rmItem(item);
	int getItemIndex(item);
	void saveToFile();
	void readFromFile();
	void DisplayInventory();
	bool checkItemAvailable(string);
	item getItemFromString(string);
};


item inventory::getItemFromString(string s) {
	if (checkItemAvailable(s)) {
		for (int i = 0; i < itemList.size(); i++) {
			if (itemList.at(i).getName() == s) {
				return itemList.at(i);
			}
		}
	}
	else {
		return item("", 0, 0, 0);
	}
}

bool inventory::checkItemAvailable(string s) {
	bool found = false;
	for (int i = 0; i < itemList.size(); i++) {
		if (itemList.at(i).getName() == s && itemList.at(i).getStock() > 0) {
			found = true;
			itemList.at(i).setStock(itemList.at(i).getStock());
		}
	}
	return found;
}

void inventory::addItem(item i) {
	itemList.push_back(i);
}

void inventory::rmItem(item rmi) {
	for (int i = 0; i < itemList.size(); i++) {
		if (itemList.at(i).getName() == rmi.getName()) {
			itemList.erase(itemList.begin()+i);
		}	
	}
}

int inventory::getItemIndex(item tmp) {
	bool found = false;
	for (int i = 0; i < itemList.size(); i++) {
		if (itemList.at(i).getName() == tmp.getName()) {
			return i;
			found = true;
		}
	}
	if (found == false) {
		cout << "Item not found in Inventory" << endl;
		return -1;
	}
}

void inventory::saveToFile() {
	fstream file;

	file.open("inventory.txt");

	if (!file.is_open()) {
		cout << "Failed to open file" << endl;
	}
	else {

		for (int i = 0; i < itemList.size(); i++) {
			file << itemList.at(i).getName() << " " << itemList.at(i).getID() << " " << itemList.at(i).getPrice() << " " << itemList.at(i).getStock() << "\n";
		}
	}

	
	file.close();

}

void inventory::readFromFile() {
	fstream file;
	string tmpLine;
	string tmpN, tmpI, tmpP, tmpS;

	file.open("inventory.txt");

	if (!file.is_open()) {
		cout << "Failed to open file" << endl;
	}
	else {
		while (file >> tmpN >> tmpI >> tmpP >> tmpS) {
			item tmpItem(tmpN, stoi(tmpI), stod(tmpP), stoi(tmpS));
			itemList.push_back(tmpItem);
		}
	}

	

	file.close();

}

void inventory::DisplayInventory() {

	cout << "-----------------------------Inventory----------------------------- As of " << gettime() << endl << endl;
	cout << " name: \t\t id: \t\t price: \t\t stock: " << endl;
	for (int i = 0; i < itemList.size(); i++) {
		cout << "     " << itemList.at(i).getName() << "\t\t" << itemList.at(i).getID() << "\t\t" << itemList.at(i).getPrice() << "\t\t    " << itemList.at(i).getStock() << endl;
	}
}