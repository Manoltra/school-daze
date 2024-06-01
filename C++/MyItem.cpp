#include "myItem.h"

MyItem::MyItem(string myName, string myDescription) {
	itemName = myName;
	itemDescription = myDescription;
	isLent = false;
}

MyItem::MyItem(string myName, string myDescription, bool myStatus) {
	itemName = myName;
	itemDescription = myDescription;
	isLent = myStatus;
}

void MyItem::setName(string newName)
{
	itemName = newName;
};
void MyItem::setDescription(string newDescription) {
	itemDescription = newDescription;
};
void MyItem::setStatus(bool newStatus) {
	isLent = newStatus;
};

string MyItem::getName() {
	return itemName;
};
string MyItem::getDescription() {
	return itemDescription;
};
bool MyItem::getStatus() {
	return isLent;
};