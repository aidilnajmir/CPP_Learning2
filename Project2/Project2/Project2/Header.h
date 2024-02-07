#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <fstream>

char* gettime() {
#pragma warning(disable : 4996)
	time_t ttime = time(0);

	char* dt = ctime(&ttime);

	return dt;
}


//classes
#include "order.h"
#include "item.h"
#include "inventory.h"
#include "Customer.h"


using namespace std;

void menu();
void customerInterface();
void adminInterface();

void menu() {
	int op = 0;
		cout << "-------------------The Store-------------------" << endl;
		cout << "\tPlease select who you are." << endl;
		cout << "\t 1) Customer" << endl << "\t 2) Admin" << endl << "\t 3) Exit" << endl;
		cout << "\tEnter your choice: ";
		cin >> op;

		switch (op)
		{
		case 1:
			customerInterface();
			break;
		case 2:
			adminInterface();
			break;
		case 3:
			exit(0);
			break;

		}

}

void customerInterface() {
	int choice;
	string name;
	customer curCust;
	

	cout << "-------------------Customer-------------------" << endl;
	cout << "Please enter your name: ";
	cin >> name;
	curCust.setName(name);

	m:

	
	item curItem;
	order curOrder;
	inventory invent;
	invent.readFromFile();

	cout << "\t Options:" << endl;
	cout << "\t 1) Buy products \n";
	cout << "\t 2) Return products \n";
	cout << "\t 3) View products \n";
	cout << "\t 4) Search products \n";
	cout << "\t 5) Menu \n\n";
	cout << "\tEnter your choice: ";
	cin >> choice;


	string itemName;
	string yn;
	switch (choice) {
	case 1:
		s:
		cout << "-------------------Cart-------------------" << endl;
		cout << "Search for item by name: "; cin >> itemName;
		curItem = invent.getItemFromString(itemName);
		if (curItem.getName() != "") {
			curOrder.addItem(curItem);
			invent.itemList.at(invent.getItemIndex(curItem)).setStock(invent.itemList.at(invent.getItemIndex(curItem)).getStock() - 1);
			cout << "Item: " << curItem.getName() << " Price: " << curItem.getPrice() << " Added to cart ..." << endl;
			cout << "Continue shopping? (y/n): "; cin >> yn;
			cout << endl;
			if (yn == "y") {
				goto s;
			}
		}
		else {
			cout << "item not in inventory ..." << endl;
		}

		invent.saveToFile();
		invent.readFromFile();
		
		curCust.orders.push_back(curOrder);
		curCust.saveRecordToFile();
	
		_sleep(3);
		cout << endl << endl;
		goto m;
		break;

	case 2:

		t:
		cout << "Returning items: " << endl;
		cout << "what item are you returning? "; cin >> itemName;
		curItem = invent.getItemFromString(itemName);
		if (curItem.getName() != "") {
			invent.itemList.at(invent.getItemIndex(curItem)).setStock(curItem.getStock()+1);
			cout << "Item: " << curItem.getName() << " Price: " << curItem.getPrice() << " Returning to inventory ..." << endl;
			cout << "Returning more? (y/n): "; cin >> yn;
			cout << endl;
			if (yn == "y") {
				goto t;
			}
		}
		else {
			cout << "We do not acceptance " << itemName << " anymore. Sorry" << endl;
		}

		invent.saveToFile();
		invent.readFromFile();

		_sleep(3);
		cout << endl << endl;
		goto m;
		break;

	case 3:
		invent.DisplayInventory();
		_sleep(3);
		cout << endl << endl; 
		goto m;
		break;

	case 4:
		cout << "Inventory Search:" << endl;
		cout << "Search item's name: "; cin >> itemName;
		if (invent.checkItemAvailable(itemName)) {
			cout << "Item is available for purchase/return" << endl;
		}
		else {
			cout << "Item is no longer supported by The Store" << endl;
		}
		_sleep(3);
		cout << endl << endl;
		goto m;
		break;

	case 5:
		menu();
		break;

	default:
		cout << "Invalid input." << endl;
		menu();
	}
}

void adminInterface() {

	int choice, modC;
	string user, pass;

	inventory invent;
	invent.readFromFile();

	item curItem, tmpItem;
	string tmpN, tmpNN;
	int tmpId, itemIndex;
	double tmpP;
	int tmpS;

	cout << "Please enter login credentials: " << endl;
	cout << "username: "; cin >> user;
	cout << "password: "; cin >> pass; cout << endl;

	if (user == "admin" && pass == "password") {

	m:
		
		
		cout << "-------------------Administrator menu-------------------" << endl;
		cout << "\t 1) Add product" << endl;
		cout << "\t 2) Modify product" << endl;
		cout << "\t 3) Delete product" << endl;
		cout << "\t 4) Display Inventory" << endl;
		cout << "\t 5) Exit to main menu" << endl;
		cout << " Enter your choice:";
		cin >> choice;

		switch (choice) {
		case 1:
			cout << "Add item to Inventory:" << endl;
			cout << "What is the name of this item? "; cin >> tmpN;
			cout << "What is the id number of this item? "; cin >> tmpId;
			cout << "What is the price of this item? "; cin >> tmpP;
			cout << "What is the stock of this item? "; cin >> tmpS;

			curItem = item(tmpN, tmpId, tmpP, tmpS);
			invent.addItem(curItem);

			invent.saveToFile();
			

			_sleep(3);
			cout << endl << endl;
			goto m;
			break;

		case 2:
			cout << "Change Product Info: " << endl;
			cout << "What is the name of the item? "; cin >> tmpN;
			curItem = invent.getItemFromString(tmpN);
			itemIndex = invent.getItemIndex(curItem);
			cout << "What do you want to modify?" << endl
				<< " 1) Name" << endl
				<< " 2) ID" << endl
				<< " 3) Price" << endl
				<< " 4) Stock" << endl;
			cout << "Choice: "; cin >> modC;
			switch (modC) {
			case 1:
				cout << "What is the new name? "; cin >> tmpNN;
				invent.itemList.at(itemIndex).setName(tmpNN);

				break;
				
			case 2:
				cout << "What is the new id? "; cin >> tmpId;
				invent.itemList.at(itemIndex).setID(tmpId);
				
				break;

			case 3:
				cout << "What is the new price? "; cin >> tmpP;
				invent.itemList.at(itemIndex).setPrice(tmpP);
				
				break;

			case 4:
				cout << "What is the new stock? "; cin >> tmpS;
				invent.itemList.at(itemIndex).setStock(tmpS);
				
				break;

			}

			invent.saveToFile();

			_sleep(3);
			cout << endl << endl;
			goto m;
			break;

		case 3:
			cout << "Remove Product: " << endl;
			cout << "What is the name of the item? "; cin >> tmpN;
			curItem = invent.getItemFromString(tmpN);
			invent.rmItem(curItem);

			invent.saveToFile();

			_sleep(3);
			cout << endl << endl;
			goto m;
			break;

		case 4:
			cout << "Products: " << endl;
			invent.DisplayInventory();

			_sleep(3);
			cout << endl << endl;
			goto m;
			break;

		case 5:
			cout << endl << endl;
			menu();
			break;

		default:
			cout << "Invalid input. Try again (1-4).\n";
			menu();
			
		}
		
	}
	else {
		cout << "invalid credentials ..." << endl;
		_sleep(3);
		cout << endl << endl;
		menu();
	}

}
