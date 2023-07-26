// #ifndef PHONEBOOK_FUNCTIONS
// #define PHONEBOOK_FUNCTIONS
#include <iostream>
#include <vector>
using namespace std;

void add_contact(vector<phonebook>& contact_array, int MAX_STRUCTURES, phonebook& ph);
void delete_contact(vector<phonebook>& contact_array, int MAX_STRUCTURES, phonebook& ph);
void modify_contact(vector<phonebook>& contact_array, int MAX_STRUCTURES, phonebook& ph);
void search_contact(vector<phonebook>& contact_array, int MAX_STRUCTURES, phonebook& ph);
void displayAll(vector<phonebook>& contact_array, int MAX_STRUCTURES, phonebook& ph);

// #endif 