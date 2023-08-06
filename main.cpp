#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>
#include <vector>

#include "phonebook_functions.h"
#include "sqlite3.h"
#define DB_NAME "contacts.sqlite"

using namespace std;

int main() {
    // Display menu
    cout<<"\033[32m";
    cout<<"+---------------------------+"<<endl;
    cout<<"| Welcome to your Phonebook |"<<endl;
    cout<<"+---------------------------+"<<endl;
    cout<<"\033[0m";

    cout<<"reading contacts..."<<endl;

    sqlite3* db;
    // Save the connection result
    int rc = 0;
    rc = sqlite3_open(DB_NAME, &db);
    // Test if there was an error
    if(rc)
        cerr<<"DB Open Error: "<<sqlite3_errmsg(db)<<endl;
    else
        cout<<"opened database..."<<endl;

    // Create table if not exists
    const char* createTableQuery = "CREATE TABLE IF NOT EXISTS contacts(name TEXT, number TEXT PRIMARY KEY);";
    char* errorMsg;
    rc = sqlite3_exec(db, createTableQuery, 0, 0, &errorMsg);
    if(rc != SQLITE_OK) {
        cerr<<"SQL error: "<<errorMsg<<endl;
        sqlite3_free(errorMsg);
    } else {
        cout<<"table for contacts exists..."<<endl;
    }

    // Close the connection
    sqlite3_close(db);
    
    if(read_contacts()) {
        cout<<"\033[32mSuccessful!\033[0m\n";
    } else {
        cout<<"\033[31mError!\033[0m\n";
        return 1;
    }

    int choice;
    do {
        cout<<"\nPlease select one of the options:"<<endl;
        cout<<"1. Add contact"<<endl;
        cout<<"2. Delete contact"<<endl;
        cout<<"3. Modify contact"<<endl;
        cout<<"4. Search"<<endl;
        cout<<"5. Display all contacts"<<endl;
        cout<<"6. Exit \n\n";

        cout<<"Enter your choice: ";
        cin>>choice;

        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch(choice) {
            case 1:
                add_contact();
                break;
            case 2:
                delete_contact();
                break;
            case 3:
                modify_contact();
                break;
            case 4: 
                search_contact();
                break;
            case 5:
                displayAll();
                break;
            case 6:
                return 0;
                break;
            default:
                cout<<"Read the options!!"<<endl;
                break;
        }
    } while(choice != 6);
}