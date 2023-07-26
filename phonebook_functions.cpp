#include "phonebook_functions.h"
#include<iostream>
#include<algorithm>
#include <bits/stdc++.h>
#include<string>
#include<vector>
using namespace std;


void add_contact(vector<phonebook>& contact_array, int MAX_STRUCTURES, phonebook& ph){
    if(contact_array.size()<=MAX_STRUCTURES){
        cout<<"Enter the name to be added: ";
        getline(cin, ph.name);
        cout<<"Enter the number: ";
        getline(cin,ph.number);
        contact_array.push_back({ph.name, ph.number});
    }
    else{
        cout<<"Not enough memory. Delete some contacts";
    }
}

void delete_contact(vector<phonebook>& contact_array, int MAX_STRUCTURES, phonebook& ph){
    string toBeDeleted;
    cout<<"Enter the name or number to be deleted: ";
    getline(cin, toBeDeleted);
    for(auto i=contact_array.begin();i!=contact_array.end();i++){
        if(i -> name == toBeDeleted || i -> number == toBeDeleted){
            contact_array.erase(i);
            break;
        }
        
    }
    cout<<"\nContact Deleted!!!!\n";
}

void modify_contact(vector<phonebook>& contact_array, int MAX_STRUCTURES, phonebook& ph){
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
    cout<<"\nContact Modified!!!!\n";
}

void search_contact(vector<phonebook>& contact_array, int MAX_STRUCTURES, phonebook& ph){
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
}

void displayAll(vector<phonebook>& contact_array, int MAX_STRUCTURES, phonebook& ph){
    cout<<"\nAll Contacts"<<endl<<endl;
    cout<<"Name"<<"\t\t"<<"Number"<<endl;
    for(int i=0;i<contact_array.size();i++){
        cout<<contact_array[i].name<<"\t\t"<<contact_array[i].number<<endl;
    }
}