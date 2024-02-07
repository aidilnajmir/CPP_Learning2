#pragma once
#include "Header.h"

using namespace std;

class item {
protected:
	string name;
	int id;
	double price;
	int stock;
public:
	item();
	item(string, int, double, int);
	void setName(string);
	string getName();
	void setID(int);
	int getID();
	void setPrice(double);
	double getPrice();
	void setStock(int);
	int getStock();
	void operator=(item);
};

void item::operator=(item i) {

	name = i.getName();
	id = i.getID();
	price = i.getPrice();
	stock = i.getStock();
}

item::item() {
	name = "";
	id = 0;
	price = 0;
	stock = 0;
}

item::item(string n, int i, double p, int s) {
	name = n;
	id = i;
	price = p;
	stock = s;
}

void item::setName(string n) {
	name = n;
}

string item::getName() {
	return name;
}

void item::setID(int i) {
	id = i;
}

int item::getID() {
	return id;
}

void item::setPrice(double p) {
	price = p;
}

double item::getPrice() {
	return price;
}

void item::setStock(int s) {
	stock = s;
}

int item::getStock() {
	return stock;
}