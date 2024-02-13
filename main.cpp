#include <iostream>
#include <cstring>
#include <iomanip>
#include <time.h>
#include <fstream>

using namespace std;

struct student{
  char first[51];
  char last[51];
  float gpa;
  int ID;
  student* next;
};
//Prototypes
void getStudentInfo(student* ns);
int ADD(student** &list, student* ns, int size);
int reHash(student** &list, int size);
void PRINT(student** list, int size);
void printStudent(student* s);
void DELETE(student** list, int size, int delID);

int main() {
  //Intialize Variables
  bool running = true;
  char command[8];
  int randomID = 100;
  srand(time(NULL));
  randomID = 1; //creates the slot where ADDRAND will add all the students for testing
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
      size = ADD(list, ns, size);
      cout << "Student Added" << endl << endl;
    }
    else if (strcmp(command, "ADDRAND") ==0) { //Add an amount, amount determined by user, of randomly generated students with randomly generated names, ID's, and GPA
            int num;
            char** nameFirst = new char* [20];
            char** nameLast = new char* [20];
            for (int i = 0; i < 20; i++) {
                nameFirst[i] = new char[81];
                nameLast[i] = new char[81];
            }
	    //number of students
            cout << endl << "Number of students to add: ";
            cin >> num;
            cin.clear();
            cin.ignore(10000, '\n');
	    //assigns all the first names into an array
            ifstream myfile("firstNames.txt");
            int lineNum = 0;
            char first[81];
            while (lineNum < 20) {
                myfile.getline(first, 81);
                strcpy(nameFirst[lineNum], first);
                lineNum++;
            }
	    //assigns all the last names into an array
            ifstream myfile1("lastNames.txt");
            char last[81];
            lineNum = 0; //restart count
            while (lineNum < 20) {
                myfile1.getline(last, 81);
                strcpy(nameLast[lineNum], last);
                lineNum++;
            }
	    //DEBUG
	    //for(int i = 0; i<20; i++) {
	    //cout << nameFirst[i] << ", " << nameLast[i] << endl;
	    //}
	    while (num > 0) {
                student* newStudent = new student();
                //make random numbers between 0 and 19
                int randomFirst = rand() % 19;
                int randomLast = rand() % 19;
                //assign random data to new studen
                strcpy(newStudent->first, nameFirst[randomFirst]);
                strcpy(newStudent->last, nameLast[randomLast]);
                newStudent->ID = randomID;
                newStudent->gpa = (float)rand() / (RAND_MAX) * 5;
                randomID++;
                //add new student genrated
                size = ADD(list, newStudent, size);
                num--;
	    }
    }
    else if(strcmp(command, "PRINT") == 0) {//PRINT
      PRINT(list, size);
    }
    else if(strcmp(command, "DELETE") == 0) {//Delete
      //Get ID
      cout  << "What is the ID of the student you want to delete" << endl;
      int delID;
      cin >>delID;
      cout << "Deleting Student" << endl;
      DELETE(list, size, delID);
    }
    else if (strcmp(command, "QUIT") == 0) {//QUIT
      running = false;
    }
  }
}
void getStudentInfo(student* ns) {//get student stuff
  ns->next = NULL;
  cout << "Enter first name: ";
  cin >> ns->first;
  cin.clear();
  cin.ignore(81, '\n');
  cout << "Enter last name: ";
  cin >> ns->last;
  cin.clear();
  cin.ignore(81, '\n');
  cout << "Enter ID: ";
  cin >> ns->ID;
  cin.clear();
  cin.ignore(81, '\n');
  cout << "Enter GPA: ";
  cin >> ns->gpa;
  cin.clear();
  cin.ignore(81, '\n');
  return;
}
int ADD(student** &list, student* ns, int size) {//ADD function
  bool adding = true;
  while(adding == true) {
    int key = (ns->ID) % size;//Hash Function the key is the remainder of the ID divided by size
    if(list[key] == NULL) {//if the key is empty
      list[key] = ns;
      adding = false;
    }
    else if((list[key])->next == NULL) {//if the next one is empty
      (list[key])->next = ns;
      adding = false;
    }
    else if(((list[key])->next)->next == NULL) {//if the next one is empty
      ((list[key])->next)->next = ns;
      adding = false;
    }
    else {//else the key where the new student is meant to go is full and the list need to be rehashed 
      size = reHash(list, size);
    }
  }
  return size;
}
int reHash(student** &list, int size) {//Double the length of the list and copy all the students to the new list
  cout << "ReHashing" << endl;
  int newSize = 2*size;//double size
  student** temp = new student* [newSize];
  for (int i=0; i < newSize; i++) {//clear the temp list
    temp[i] = NULL;
  }
  for(int y = 0; y < size; y++) {//Go through every slot in the original list
    if (list[y]!=NULL) {//node there
      student* move = list[y];
      if(move->next != NULL) {//is it linked to another
	student* newNext = move->next;
	move->next = NULL;
	if (newNext->next != NULL) {//is it linked to another
	  student* newNext2 = newNext->next;
	  newNext->next = NULL;
	  ADD(temp, newNext2, newSize);//Add the nodes to the temp list
	}
	ADD(temp, newNext, newSize);
      }
      ADD(temp, move, newSize);
    }
  }
  //replace the list
  delete[] list;
  list = temp;
  return newSize;//return newSize so it can be passed back to main
}
void PRINT(student** list, int size) {//Go through list and find each student
  for(int y = 0; y < size; y++) {
    if(list[y] != NULL) {
      student* print = list[y];
      printStudent(print);
      if(print->next != NULL) {
	student* Next = print->next;
	printStudent(Next);
	if (Next->next != NULL) {
	  student* Next2 = Next->next;
	  printStudent(Next2);
	}
      }
    }
  }
}
void printStudent(student* s) {//Print Student and set GPA to a 100ths place
  cout << s->first << " " << s->last << ", " << s->ID << ", " << fixed << setprecision(2) << s->gpa << endl;
}
void DELETE(student** list, int size, int delID) {//Delete student
  int key = delID % size;//find the slot the supposed student is in
  if (list[key] == NULL) {//Wrong ID
    cout << "No Student with that ID in the list" << endl;
  }
  else {
    if (list[key]->ID == delID) {//is the first the right student
      if(list[key]->next == NULL) {//is it not linked to any other ones
	delete list[key];
	list[key] = NULL;
      }
      else {//if it is shift the list down
	student* replace = list[key]->next;
	delete list[key];
	list[key] = replace;
      }
    }
    else {
      if(list[key]->next == NULL) {//the second one isn't there
	cout << "No student with that ID in the list" << endl;
      }
      else {
	if(list[key]->next->ID == delID) {//second is the right student
	  if(list[key]->next->next == NULL) {//not linked to anything
	    delete list[key]->next;
	    list[key]->next = NULL;
	  }
	  else {//is linked so move it down
	    student* replace = list[key]->next->next;
	    delete list[key]->next;
	    list[key]->next = replace;
	  }
	}
	else {
	  if(list[key]->next->next == NULL) {//the third isn't there
	    cout << "No such student with that ID" << endl;
	  }
	  else {
	    if(list[key]->next->next->ID == delID) {//Delete the third one 
	      delete list[key]->next->next;
	      list[key]->next->next = NULL;
	    }
	    else {//the third isn't rght
	      cout << "No such student with that ID" << endl;
	    }
	  }
	}
      }
    }
  }
}
