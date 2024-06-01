#include "MyItem.h"
#include "ItemLoan.h"
#include <algorithm>
#include <fstream>
#include <sstream>

int currentHighestID = 0;
vector<unique_ptr<MyItem>> itemList;
vector<ItemLoan> loanList;
string inputFileName = "loans.csv";

//creates and appends an item to the itemList vector
void createItem() {
    string itemName, itemDesc;
    bool needsValidation = true;

    while(needsValidation){
        cout << "Enter a name: ";
        cin >> itemName;
        if (itemName.length() == 0 || all_of(itemName.begin(), itemName.end(), isspace)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Enter a name for your item." << endl;
        }
        else {
            needsValidation = false;
        }
    }
    needsValidation = true;
    cin.clear();
    while(needsValidation){
        cout << "Enter the item's description: ";
        cin >> itemDesc;
        if (itemDesc.length() == 0 || all_of(itemDesc.begin(), itemDesc.end(), isspace)) {
            cout << "Enter a description for your item." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
            needsValidation = false;
        }
    }

    itemList.emplace_back(make_unique<MyItem>(itemName, itemDesc));

    cout << "Item successfully added." << endl;

    return;
}

//finds an item
MyItem* findItem(const string& itemName) {
    auto iterator = find_if(itemList.begin(), itemList.end(),
        [itemName](unique_ptr<MyItem>& item) {return itemName == item->getName(); }
    );
    if (iterator == itemList.end()) {
        return nullptr;
    }
    return iterator->get();
}


//creates a loan and adds it to the loanList vector
void createLoan() {
    string loanerName;
    string searchedName;

    bool needsValidation = true;
        cout << "Enter the item that you are loaning out: ";

        cin >> searchedName;

    for (unique_ptr<MyItem>& curItem : itemList) {
        if (curItem->getName() == searchedName) {
            if (curItem->getStatus()) {
                cout << "Item already in use" << endl;
                return;
            }
            while (needsValidation) {
                cout << "Enter the name of the loaner: ";
                cin >> loanerName;
                if (loanerName.length() == 0 || all_of(loanerName.begin(), loanerName.end(), isspace)) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Enter a name for the loaner." << endl;

                }
                else {
                    needsValidation = false;
                }
            }
            loanList.emplace_back(curItem.get(), loanerName, ++currentHighestID);
            curItem->setStatus(true);
            cout << "Item successfully added." << endl;
            return;

        }

        cout << "Item not found, please try again." << endl;

    }
}

//loads all the loans and items when the program starts
void loadState() {
    string loanLine;
    string itemLine;
    {
        fstream itemFile("items.csv");

        //load items from file
        while (getline(itemFile, itemLine)) {
            stringstream ss(itemLine);
            string itemName, itemDesc, statusString;
            bool isLent;

            getline(ss, itemName, ',');
            getline(ss, itemDesc, ',');
            getline(ss, statusString, ',');

            itemDesc.erase(0, 1);

            isLent = stoi(statusString) == 1 ? true : false;

            itemList.emplace_back(make_unique<MyItem>(itemName, itemDesc, isLent));

        }
    }
    {
        fstream loanFile(inputFileName);
        //load loans from file
        while (getline(loanFile, loanLine)) {
            stringstream ss(loanLine);
            string loanerName, itemName;
            string loanID;
            string loanDate;

            getline(ss, loanerName, ',');
            getline(ss, itemName, ',');
            itemName.erase(0, 1);
            getline(ss, loanID, ',');
            getline(ss, loanDate, ',');
            loanDate.erase(0, 1);

            MyItem* item = findItem(itemName);

            if (item == nullptr) {
                // some error
                cout << "Unable to find item " << itemName << endl;
            }
            int loanIDint = stoi(loanID);
            if (loanIDint > currentHighestID) {
                currentHighestID = loanIDint;
            }
            loanList.emplace_back(item, loanerName, loanIDint, loanDate);
        }
    }
}

//deletes an item
void deleteItem() {
    string deletedItem;

    cout << "Enter the name of the item you wish to delete: ";

    cin >> deletedItem;

    loanList.erase(remove_if(loanList.begin(), loanList.end(),
        [deletedItem](ItemLoan& curLoan) {
            return curLoan.getItem()->getName() == deletedItem;
        }), loanList.end());

    int removeCount = 0;
    itemList.erase(remove_if(itemList.begin(), itemList.end(),
        [deletedItem, &removeCount](unique_ptr<MyItem>& curItem) {
            if (curItem->getName() == deletedItem) {
                removeCount++;
                cout << "Removed item " << curItem->getName() << endl;
                return true;
            }
            return false;
        }), itemList.end());
    if (removeCount == 0) {
        cout << "Unable to find item " << deletedItem << endl;
    }
}

//edits an item
void editItem() {
    string editedItem;

    cout << "Enter the name of the item you wish to edit: ";

    cin >> editedItem;

    MyItem* foundItem = findItem(editedItem);
    if (foundItem == nullptr) {
        cout << "Unable to find item " << editedItem << endl;
        return;
    }

    string newDesc;
    string newName;
    
    cout << "Enter the new name: ";
    cin >> newName;

    cout << "Enter the new description: ";
    cin >> newDesc;

    foundItem->setDescription(newDesc);
    foundItem->setName(newName);
}


//deletes a loan
void deleteLoan() {
    int deletedLoan;

    cout << "Enter the ID of the loan you wish to delete: ";

    cin >> deletedLoan;

    int removeCount = 0;
    loanList.erase(remove_if(loanList.begin(), loanList.end(),
        [deletedLoan, &removeCount](ItemLoan& curLoan) {
            if (curLoan.getID() == deletedLoan) {
                curLoan.getItem()->setStatus(false);
                removeCount++;
                return true;
            }
            return false;
        }), loanList.end());

    if (removeCount == 0) {
        cout << "Unable to find loan " << deletedLoan << endl;
    }
}

void saveFiles() {
    //saves the vector of the items to file
    {
        ofstream itemFileO("items.csv");
        for (unique_ptr<MyItem>& currItem : itemList) {
            itemFileO << currItem->getName() << ", " << currItem->getDescription() << ", "
                << [](bool a) -> int { return a ? 1 : 0; } (currItem->getStatus()) << "\n";
        }
    }
    //saves the vector of the loans to file
    {
        ofstream loanFileO("loans.csv");
        for (ItemLoan curLoan : loanList) {
            MyItem* loanItem = curLoan.getItem();
            loanFileO << curLoan.getName() << ", " << loanItem->getName() << ", "
                << curLoan.getID() << ", " << curLoan.getDate() << "\n";
        }
    }
    cout << "Successfully saved." << endl;
}

//displays the loans to the user
void displayLoans() {
    if (loanList.size() == 0) {
        cout << "There are no loans." << endl;
    } else {
        for (ItemLoan curLoan : loanList) {
            MyItem* loanItem = curLoan.getItem();
            cout << curLoan.getID() << " | " << curLoan.getName() 
                << " | " << loanItem->getName() <<
                " | " << loanItem->getDescription() << " | "
               << curLoan.getDate() << endl;
        }
    }
}

//displays the items to the user
void displayItems() {
    if (itemList.size() == 0) {
        cout << "There are no items." << endl;
    }
    else {
        for (unique_ptr<MyItem>& curItem : itemList) {
            cout << curItem->getName() << " | " << curItem->getDescription() << endl;
        }
    }
}

//displays the options to the user
void displayOptions() {
    cout << " 1) Add Item \n 2) Add Loan \n 3) Remove Item \n 4) Remove Loan \n"
        << " 5) List Items \n 6) List Loans \n 7) Save \n 8) Edit Item \n 9) Exit" << endl;
}

int main(int argc, char* argv[])
{
    //allows the program to be run through commandline via a filepath
    if (argc > 2 && argv[1] == "-f") {
        inputFileName = string(argv[2]);
    }

    loadState();

    cout << "Welcome to LoanIt!" << endl;

                

                int myChoice;
                bool isRunning = true;

                while (isRunning) {
                    displayOptions();
                    cout << "Pick an option: ";
                    cin >> myChoice;

                    switch (myChoice) {
                    case 1:
                        createItem();
                        break;
                    case 2:
                        createLoan();
                        break;
                    case 3:
                        deleteItem();
                        break;
                    case 4:
                        deleteLoan();
                        break;
                    case 5:
                        displayItems();
                        break;
                    case 6:
                        displayLoans();
                        break;
                    case 7:
                        //saves items and loans to files
                        saveFiles();
                        break;
                    case 8:
                        editItem();
                        break;
                    case 9:
                        isRunning = false;
                        break;
                    default:
                        cout << "Enter a valid digit." << endl;

                        displayOptions();

                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    };

                }


        }
