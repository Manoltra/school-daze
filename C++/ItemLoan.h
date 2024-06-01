#pragma once

#include "MyItem.h"
#include <string>

using namespace std;

class ItemLoan
{
	int LoanID;
	string LoanerName;
	MyItem* LoanItem;
	string LoanDate;
public:
	ItemLoan() { };
	ItemLoan(MyItem* newItem, string newName, int newID);
	ItemLoan(MyItem* newItem, string newName, int newID, string newDate);
	void setID(int newID);
	void setName(string newName);
	void setItem(MyItem* newItem);
	int getID();
	MyItem* getItem();
	string getName();
	string getDate();
};