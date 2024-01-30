#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

struct student{
  char first[51];
  char last[51];
  float gpa;
  int ID;
  student* next;
};

int main() {
  bool running = true;
  char command[8];
  student** list = new student* [100];
  int size = 100;

  while (running == true) {
    cout << "Options: ADD, ADDRAND, PRINT, DELETE, QUIT" << endl;
    cin.get(command,8);
    cin.clear();
    cin.ignore(10000, '\n');
    if(strcmp(command, "ADD") == 0) {
      student* ns = new student();
      getStudentInfo(ns);
      ADD(list, ns, size);
      cout << "Student Added" << endl << endl;
    }
  }
}
//No need to pass in a pointer by reference can just pass in a pointer because it will be out of scope once done
void getStudentInfo(student* ns) {
  newStudent->next = NULL;
  newStudent->prev = NULL;
  cout << "Enter first name: ";
  cin >> newStudent->firstName;
  cin.clear();
  cin.ignore(81, '\n');
  cout << "Enter last name: ";
  cin >> newStudent->lastName;
  cin.clear();
  cin.ignore(81, '\n');
  cout << "Enter ID: ";
  cin >> newStudent->ID;
  cin.clear();
  cin.ignore(81, '\n');
  cout << "Enter GPA: ";
  cin >> newStudent->gpa;
  cin.clear();
  cin.ignore(81, '\n');
  return;
}
void ADD(student** list, student* ns, int size) {
  int key = (ns->ID) % size;//Hash Function the key is the remainder of the ID divided by size
  if(list[key] == NULL) {
    list[key] = ns;
  }
  else 
