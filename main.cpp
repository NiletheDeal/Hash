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

int main() {
  bool running = true;
  char command[8];
  int randomID = 0;
  srand(time(NULL));
  randomID = rand() % 999999 +1; //creates the slot where ADDRAND will add all the students for testing
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
            cout << endl << "Number of students to add: ";
            cin >> num;
            cin.clear();
            cin.ignore(10000, '\n');
            ifstream myfile("firstNames.txt");
            int lineNum = 0;
            char first[81];
            while (lineNum < 20) {
                myfile.getline(first, 81);
                strcpy(nameFirst[lineNum], first);
                lineNum++;
            }
            ifstream myfile1("lastNames.txt");
            char last[81];
            lineNum = 0; //restart count
            while (lineNum < 20) {
                myfile1.getline(last, 81);
                strcpy(nameLast[lineNum], last);
                lineNum++;
            }
            while (num > 0) {
                student* newStudent = new student();
                //make random numbers between 0 and 19
                int randomFirst = rand() % 19;
                int randomLast = rand() % 19;
                //assign random data to new studen
                strcpy(newStudent->firstName, nameFirst[randomFirst]);
                strcpy(newStudent->lastName, nameLast[randomLast]);
                newStudent->ID = randomID;
                newStudent->gpa = (float)rand() / (RAND_MAX) * 5;
                randomID = randomID + 100;
                //add new student genrated
                ADD(list, newStudent, size);
                num--;
	    }
    }
    else if(strcmp(command, "PRINT")) {
      void PRINT(list, size);
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
int ADD(student** &list, student* ns, int size) {
  bool adding = true;
  while(adding == true) {
    int key = (ns->ID) % size;//Hash Function the key is the remainder of the ID divided by size
    if(list[key] == NULL) {
      list[key] = ns;
    }
    else if((list[key])->next == NULL) {
      (list[key])->next = ns;
    }
    else if(((list[key])->next)->next == NULL) {
      ((list[key])->next)->next = ns;
    }
    else {
      size = reHash(list, size);
    }
    return size;
  }
}
int reHash(student** &list, int size) {
  cout << "ReHashing" << endl;
  int newSize = 2*size;
  student** temp = new student* [newSize];
  for (int i=0; i < newSize; i++) {
    temp[i] = NULL;
  }
  for(int y = 0; y < size; y++) {
    if (list[y]!=NULL) {
      student* move = list[y];
      if(move->next != NULL) {
	student* newNext = move->next;
	move->next = NULL;
	ADD(temp, newNext, newSize);
	if (newNext->next != NULL) {
	  studnet* newNext2 = newNext->next;
	  newNext->next = NULL;
	  ADD(temp, newNext2, newSize);
	}
      }
      ADD(temp, move, newSize);
    }
  }
  list = temp;
  delete[] temp;
  return newSize;
}
void PRINT(student** list, int size) {
  for(int y = 0; y < size; y++) {
    if(list[y] != NULL) {
      student* print = list[y];
      printStudent(print);
      if(print->next != NULL) {
	student* Next = print->next;
	printStudent(Next);
	if (Next->next != NULL) {
	  studnet* Next2 = Next->next;
	  printStudent(Next2);
	}
      }
    }
  }
}
void printStudent(student* s) {
  cout << s->fist << " " << s->last << ", " << s->ID << ", " << s->gpa << endl;
}
void DELETE(student** list, int size, int delID) {
  int key = delID % size;
  if (list[key] == NULL) {
    cout << "No Student with that ID in the list" << endl;
  }
  else {
    if (list[key]->ID == delID) {
      if(list[key]->next == NULL) {
	delete list[key];
      }
      else {
	student* replace = list[key]->next;
	list[key] = replace;
      }
    }
    else {
      if(list[key]->next == NULL) {
	cout << "No student with that ID in the list" << endl;
      }
      else {
	if(list[key]->next->ID == delID) {
	  if(list[key]->next->next == NULL) {
	    delete list[key]->next;
	  }
	  else {
	    student* replace = list[key]->next->next;
	    list[key]->next = replace;
	  }
	}
	else {
	  if(list[key]->next->next == NULL) {
	    cout << "No such student with that ID" << endl;
	  }
	  else {
	    if(list[key]->next->next->ID == delID) {
	      delete list[key]->next->next;
	      list[key]->next = NULL;
	    }
	  }
	}
      }
    }
  }
}
	printStudent(Next);
	if (Next->next != NULL) {
	  studnet* third = second->next;
	  printStudent(Next2);
	}
      }
    }
  }
