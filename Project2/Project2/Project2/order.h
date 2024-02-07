#pragma once
#include "Header.h"
#include "item.h"

using namespace std;

class order {
protected:
	char* date;
	double total = 0;
	int numItems;
public:
	vector<item> itemsBought;
	order();
	order(item, char*, double, int);
	void addItem(item);
	char* getDate();
	double getTotal();
	void addToTotal(double);

};

order::order() {
	//just need this to make computer happy
}

order::order(item i, char* dt, double t, int s) {
	itemsBought.push_back(i);
	date = dt;
	total = t;
	numItems = s;
}

void order::addItem(item i) {
	itemsBought.push_back(i);
	numItems++;
	date = gettime();
	total += i.getPrice();
}

char* order::getDate() {
	return date;
}

double order::getTotal() {
	return total;
}

void order::addToTotal(double d) {
	total += d;
}