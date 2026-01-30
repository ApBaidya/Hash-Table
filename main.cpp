/*
Aparajita Baidya
1.30.2026

To do:
Add
Print
Delete
Quit
Store students in hash table:
 use chaining
 if more than 3 collisions occur when chaining, double array size and rehash
Rand student generator:
 make a file of first and last names
 grab random first and last names from the file
 add id number (increment it)
 add rand GPA
 Be able to specify # of students to generate and add
*/
#include <iostream>
#include <cstring>
#include <iomanip>
#include "Node.h"
#include "Student.h"
//#include file of names

using namespace std;

//function definitions
Student* randMkStud();//take names from file, randomly make students
void randAdd();//ask for stud amounts --> do randMkStud that many times & add to table 
void reHash();//remake hash Table --> make new table --> call hashFunc for all nodes --> set old func to new
int hashFunc();//does the hash function stuff, returns index for node*
Student* mkStud();//makes the student 
void Add();//adds student to node*, adds student to hash table
//when adding, probably check if it has to go through a chain, and then count how many times it loops to get to end. if there are three nodes in the chain already, add new node to end, then call reHash()

void Print();//probably have to just look through array for what person wants
void Delete();//delete specified value --> probably ask for details that can get hash functioned 
void Quit();//have to delete each value in the table

//main
int main()
{
  //just some very boring normal variables
  int tbLen = 101;//starting length 
  char input;
  int running = 1;
  //hash table  
  Node** hashtb = new Node*[tbLen];
  while(running == 1)
  {
    return 0;
    cout<<"what do you want to do? [a-add][r-rand add][p-print][d-delete][q-quit]:"<<endl;//ask what to do
    cin >> input;
    cin.ignore(10, '\n');
    cin.clear();
    if(input == 'q')
      {
	Quit();
	running = 0;//end the while
      }
    else if(input == 'a')
      {
	Add();
      }
    else if(input == 'r')
      {
	randAdd();
      }
    else if(input == 'p')
      {
	Print();
      }
    else if(input == 'd')
      {
	Delete();
      }
  }
  cout << "Farewell. Fare thee well."<<endl;
}

//hash related dudes
void reHash(){}
int hashFunc(){}

//add normal
Student* mkStud()
{
  Student* s = new Student;
  //vars
  char* fname[16];
  char* lname[16];
  int id;
  float gpa;
  //first name
  cout<< "First name:"<<endl;
  cin>>fname;
  cin.ignore(20, '\n');
  cin.clear();
  s->setF(fname);
  //last name
  cout<<"Last name:"<<endl;
  cin>>lname;
  cin.ignore(20,'\n');
  cin.clear();
  s->setL(lname);
  //id
  cout<<"ID:"<<endl;
  cin >> id;
  cin.ignore(20, '\n');//you never know. 
  cin.clear();
  s->setI(id);
  //gpa
  cout << "GPA:"<<endl;
  cin>>gpa;
  cin.ignore(20, '\n');//someone might enter something weird.
  cin.clear();
  s->setG(gpa);
  //return
  return s;
}
void Add(){}

//add random
Student* randMkStud(){}
void randAdd(){}

//print
void Print(){}

//delete
void Delete(){}

//quit
void Quit(){}


