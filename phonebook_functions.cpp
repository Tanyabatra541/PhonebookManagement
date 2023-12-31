#include "phonebook_functions.h"
#include <iostream>
#include <algorithm>
#include <bits/stdc++.h>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <sqlite3.h>
#define DB_NAME "contacts.sqlite"

using namespace std;

struct phonebook{
    string name;
    string number;
};

struct phonebook ph;
const int MAX_CONTACTS = 100;
vector<phonebook> contacts_array;
char phonebook_file[] = "phonebook.txt";
sqlite3* db;

bool read_contacts() {
    ifstream fin(phonebook_file);
    string line;
    while(getline(fin, line)) {
        stringstream ss(line);
        struct phonebook tmp_contact;
        if (getline(ss, tmp_contact.name, ',') && getline(ss, tmp_contact.number, ',')){
            contacts_array.push_back({tmp_contact.name, tmp_contact.number});
        } else {
            return false;
        }
    }
    return true;
}

void add_contact() {
    if(contacts_array.size() <= MAX_CONTACTS) {
        cout<<"Enter the name to be added: ";
        getline(cin, ph.name);
        cout<<"Enter the number: ";
        getline(cin,ph.number);

        // For an array
        contacts_array.push_back({ph.name, ph.number});
        
        // For a file
        ofstream fout(phonebook_file, ios::app); //ios is for input output stream, can use ofstream here too
        // ofstream fout(phonebook_file, ios::out | ios::trunc); This is to clear the file contents
        fout<<ph.name<<","<<ph.number<<"\n";
        fout.close();

        // For a database
        sqlite3* db;
        string insertRecordQuery = "INSERT INTO contacts (name, number) VALUES (' "+ ph.name +"', '"+ ph.number +"');";
        char* errorMsg;
        // Save the connection result
        int rc = sqlite3_open(DB_NAME, &db); 

        // Run commands on DB
        rc = sqlite3_exec(db, insertRecordQuery.c_str(), 0, 0, &errorMsg);
        if (rc != SQLITE_OK) {
            cerr<<"\033[31mSQL error: "<< errorMsg<<"\033[0m"<<endl;
            sqlite3_free(errorMsg);
        }

        // Close the connection
        sqlite3_close(db);
        cout<<"\n\033[32mContact added!!\033[0m\n";
    }
    else {
        cout<<"Not enough memory. Delete some contacts";
    }
}

void delete_contact() {
    string toBeDeleted;
    cout<<"Enter the number to be deleted: ";
    getline(cin, toBeDeleted);
    for(auto i = contacts_array.begin(); i != contacts_array.end(); i++){
        if(i -> number == toBeDeleted){
            contacts_array.erase(i);
            break;
        }
    }

    // for a file
    ifstream fin(phonebook_file);
    ofstream fout("temp.txt");
    string line;
    while(getline(fin, line)) {
        if(line.find(toBeDeleted)) { //0 if found and 1 if not found
            fout<<line<<"\n";
        }
    }
    fout.close();
    fin.close();
    remove(phonebook_file);
    rename("temp.txt", phonebook_file);

    // For a database
    sqlite3* db;
    string delRecordQuery = "DELETE FROM contacts WHERE number='"+ toBeDeleted +"';";
    char* errorMsg;
    // Save the connection result
    int rc = sqlite3_open(DB_NAME, &db);
    // Run commands on DB
    rc = sqlite3_exec(db, delRecordQuery.c_str(), 0, 0, &errorMsg);
    if (rc != SQLITE_OK) {
        cerr<<"\033[31mSQL error: "<< errorMsg<<"\033[0m"<<endl;
        sqlite3_free(errorMsg);
    } else {
        cout<<"\n\033[31mContact Deleted!!\033[0m\n";
    }
    // Close the connection
    sqlite3_close(db);
}

void modify_contact() {
    string toBeModified;
    cout<<"Enter the name or number to be deleted: ";
    getline(cin, toBeModified);
    string modifiedNumber;
    cout<<"Enter the modified number: ";
    getline(cin, modifiedNumber);
    for(auto i=contacts_array.begin(); i!=contacts_array.end(); i++) {
        if(i -> number == toBeModified || i -> name == toBeModified) {
            i -> number = modifiedNumber;
        }
    }

    // for a file
    ifstream fin(phonebook_file);
    ofstream fout("temp.txt");
    string line;
    while (getline(fin, line)){
        stringstream ss(line);
        string str1, str2;
        if (getline(ss, str1, ',') && getline(ss, str2, ',')) {
            if(str1 == toBeModified || str2 == toBeModified) {
                str2 = modifiedNumber;
                fout<<str1<<","<<str2<<"\n";
            }
            else{
                fout<<str1<<","<<str2<<"\n";
            }
        }
    }
    fout.close();
    fin.close();
    remove(phonebook_file);
    rename("temp.txt", phonebook_file);

    // For a database
    sqlite3* db;
    string modRecordQuery = "UPDATE contacts SET number='"+ modifiedNumber +"' WHERE name='" + toBeModified + "';";
    char* errorMsg;
    // Save the connection result
    int rc = sqlite3_open(DB_NAME, &db);
    // Run commands on DB
    rc = sqlite3_exec(db, modRecordQuery.c_str(), 0, 0, &errorMsg);
    if (rc != SQLITE_OK) {
        cerr<<"\033[31mSQL error: "<< errorMsg<<"\033[0m"<<endl;
        sqlite3_free(errorMsg);
    } else {
        cout<<"\n\033[33mContact Modified!!\033[0m\n";
    }
    // Close the connection
    sqlite3_close(db);
}

void search_contact() {
    string toBeFound; int flag = 0;
    cout<<"Enter the name or number to be searched: "<<endl;
    getline(cin, toBeFound);
    cout<<"\nSearch results are: "<<endl;
    cout<<"| Name"<<"\t|\t"<<"Number |"<<endl;
    for(auto i=contacts_array.begin();i!=contacts_array.end();i++){
        if(i -> number == toBeFound || i -> name == toBeFound){
            cout<<i -> name<<"\t\t"<<i -> number<<endl;
        }
    }

    //for a file
    ifstream fin(phonebook_file);
    string line;
    while (getline(fin, line)){
        stringstream ss(line);
        // cout<<ss(line);
        string str1, str2;
        if (getline(ss, str1, ',') && getline(ss, str2, ',')){
            if(str1 == toBeFound || str2 == toBeFound){
                cout<<str1<<","<<str2<<"\n";
            }
        }
    }
    fin.close();
}

void displayAll(){
    cout<<"\nAll Contacts"<<endl;
    cout<<"------------"<<endl;
    cout<<"Name"<<"\t|\t"<<"Number"<<endl;
    for(int i=0; i < contacts_array.size(); i++)
        cout<<contacts_array[i].name<<"\t|\t"<<contacts_array[i].number<<endl;
}