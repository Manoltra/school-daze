#include "ItemLoan.h"
#include <chrono>
#include <ctime>

string getCurrentTime() {
	char buffer[100];
	auto time = chrono::system_clock::to_time_t(chrono::system_clock::now());
	ctime_s(buffer, 100, &time);
	return string(buffer);
}

ItemLoan::ItemLoan(MyItem* newItem, string newName, int newID)
{
	LoanItem = newItem;
	LoanerName = newName;
	LoanDate = getCurrentTime();
	LoanID = newID;
};
ItemLoan::ItemLoan(MyItem* newItem, string newName, int newID, string newDate) 
{
	LoanItem = newItem;
	LoanerName = newName;
	LoanDate = newDate;
	LoanID = newID;
}
void ItemLoan::setID(int id) {
	LoanID = id;
}
void ItemLoan::setName(string newName) {
	LoanerName = newName;
};
void ItemLoan::setItem(MyItem* newItem) {
	LoanItem = newItem;
};
int ItemLoan::getID() {
	return LoanID;
}
MyItem* ItemLoan::getItem() {
	return LoanItem;
};
string ItemLoan::getName() {
	return LoanerName;
};

string ItemLoan::getDate() {
	return LoanDate;
}