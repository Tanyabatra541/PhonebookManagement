#include "phonebook_functions.h"
#include<iostream>
#include<algorithm>
#include <bits/stdc++.h>
#include<string>
#include<vector>

using namespace std;

int main(){
    // Display menu
    cout<<"\033[32m";
    cout<<"+---------------------------+"<<endl;
    cout<<"| Welcome to your Phonebook |"<<endl;
    cout<<"+---------------------------+"<<endl;
    cout<<"\033[0m";

    cout<<"Reading contacts..."<<endl;
    if(read_contacts()) {
        cout<<"\033[32mSuccessful!\033[0m\n";
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
                exit(0);
                break;
            default:
                cout<<"Read the options!!"<<endl;
                break;
        }
    } while(choice != 6);
}