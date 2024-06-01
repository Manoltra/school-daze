#pragma once

#include <vector>
#include <string>
#include <iostream>
#include <memory>

using std::string;
using std::vector;
using std::unique_ptr;
using std::cout;
using std::cin;
using std::endl;

class MyItem
{
private:
	string itemName;
	string itemDescription;
	bool isLent;

public:
	MyItem() {};
	MyItem(string myName, string myDescription);
	MyItem(string myName, string myDescription, bool myStatus);

	void setName(string newName);
	void setDescription(string newDescription);
	void setStatus(bool newStatus);

	string getName();
	string getDescription();
	bool getStatus();
};
