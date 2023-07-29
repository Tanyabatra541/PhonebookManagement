#include "phonebook_functions.h"
#include<iostream>
#include<algorithm>
#include <bits/stdc++.h>
#include<string>
#include<vector>
#include<fstream>
#include<cstdio>
using namespace std;

struct phonebook{
    string name;
    string number;
};

struct phonebook ph;
const int MAX_STRUCTURES = 100;
vector<phonebook> contact_array;

void add_contact(){
    if(contact_array.size()<=MAX_STRUCTURES){
        cout<<"Enter the name to be added: ";
        getline(cin, ph.name);
        cout<<"Enter the number: ";
        getline(cin,ph.number);
        contact_array.push_back({ph.name, ph.number});
        
        //for a file
        ofstream fout("phonebook.txt", ios::app); //ios is for input output stream, can use ofstream here too
        // ofstream fout("phonebook.txt", ios::out | ios::trunc); This is to clear the file contents
        fout<<ph.name<<","<<ph.number<<"\n";
        fout.close();
    }
    else{
        cout<<"Not enough memory. Delete some contacts";
    }
}

void delete_contact(){
    string toBeDeleted;
    cout<<"Enter the name or number to be deleted: ";
    getline(cin, toBeDeleted);
    for(auto i=contact_array.begin();i!=contact_array.end();i++){
        if(i -> name == toBeDeleted || i -> number == toBeDeleted){
            contact_array.erase(i);
            break;
        }
        
    }

    // for a file
    ifstream fin("phonebook.txt");
    ofstream fout("temp.txt");
    string line;
    while (getline(fin, line)) {
        bool found = line.find(toBeDeleted); //0 if found and 1 if not found
        if (found == 1)
            fout<<line<<"\n";
    }
    fout.close();
    fin.close();
    remove("phonebook.txt");
    rename("temp.txt", "phonebook.txt");
 
    cout<<"\nContact Deleted!!!!\n";
}

void modify_contact(){
    string toBeModified;
    cout<<"Enter the name or number to be deleted: "<<endl;
    getline(cin, toBeModified);
    string modifiedNumber;
    cout<<"Enter the modified number: ";
    getline(cin, modifiedNumber);
    for(auto i=contact_array.begin();i!=contact_array.end();i++){
        if(i -> number == toBeModified || i -> name == toBeModified){
            i -> number = modifiedNumber;
        }
        
    }

    // for a file
    ifstream fin("phonebook.txt");
    ofstream fout("temp.txt");
    string line;
    while (getline(fin, line)){
        stringstream ss(line);
        string str1, str2;
        if (getline(ss, str1, ',') && getline(ss, str2, ',')){
            if(str1 == toBeModified || str2 == toBeModified){
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
    remove("phonebook.txt");
    rename("temp.txt", "phonebook.txt");

    cout<<"\nContact Modified!!!!\n";
}

void search_contact(){
    string toBeFound; int flag = 0;
    cout<<"Enter the name or number to be searched: "<<endl;
    getline(cin, toBeFound);
    cout<<"\nSearch results are: "<<endl;
    cout<<"Name"<<"\t\t"<<"Number"<<endl;
    for(auto i=contact_array.begin();i!=contact_array.end();i++){
        if(i -> number == toBeFound || i -> name == toBeFound){
            cout<<i -> name<<"\t\t"<<i -> number<<endl;
        }
    }

    //for a file
    ifstream fin("phonebook.txt");
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
    cout<<"\nAll Contacts"<<endl<<endl;
    cout<<"Name"<<"\t\t"<<"Number"<<endl;
    for(int i=0;i<contact_array.size();i++){
        cout<<contact_array[i].name<<"\t\t"<<contact_array[i].number<<endl;
    }
}