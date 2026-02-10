/*
Aparajita Baidya
2.5.2026

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
#include <string>
//read files. ofstream creates and writes files.fstream does both
#include <fstream>
#include <vector>
//rounding
#include <iomanip>
//for rand numbers
#include <ctime>
#include <cstdlib>
//h files
#include "Node.h"
#include "Student.h"


using namespace std;


//function definitions
Student* randMkStud(vector<string>* firstNs, vector<string>* lastNs, int& randID);//take names from file, randomly make students
void randAdd(vector<string>* firstNs, vector<string>* lastNs, int& randID, int& tbLen);//ask for stud amounts --> do randMkStud that many times & add to table 
void reHash(Node**& htb, int& tbLen);//remake hash Table --> make new table --> call hashFunc for all nodes --> set old func to new
int hashFunc(int id, char* fname, int tbSize);//does the hash function stuff, returns index for node*
Student* mkStud();//makes the student 
void Add(Node**& htb, int& tbLen);//adds student to node*, adds student to hash table
//when adding, probably check if it has to go through a chain, and then count how many times it loops to get to end. if there are three nodes in the chain already, add new node to end, then call reHash()

void Print();//probably have to just look through array for what person wants
void Delete();//delete specified value --> probably ask for details that can get hash functioned 
void Quit();//have to delete each value in the table


//main
int main()
{
  int tbLen = 101;//starting length 
  char input;//user input
  int running = 1;
  int randID = 0;//lets start the random IDs at 0
  Node** hashtb = new Node*[tbLen];//hash table
  //set up name file stuff
  ifstream firstNames("C:/cygwin64/home/apara/projects/HashTable/fNames.txt");//read from fName when it comes to firstNames
  ifstream lastNames("C:/cygwin64/home/apara/projects/HashTable/lNames.txt");
  //amount of names in the files
  vector<string>* firstNs = new vector<string>();//make vector for firstnames
  vector<string>*lastNs = new vector<string>();//last names
  //make those vectors
  string word; //first time using a string wwww
  if(firstNames.is_open())
  {
    while(firstNames >> word)
    {
      cout << word<<endl;
      firstNs->push_back(word);
    }
  }
  if(lastNames.is_open())
  {
    while(lastNames >> word)
    {
      lastNs->push_back(word);
    }//for future note, you can use .size to find the size of the vector i think.
  }
  //set that random seeeeed
  srand(time(NULL));
  while(running == 1)
  {
    cout<<"what do you want to do? [a-add][r-rand add][p-print][d-delete][q-quit]:"<<endl;//ask what to do
    cin >> input;
    cin.ignore(10, '\n');
    cin.clear();
    if(input == 'q')
      {
	//Quit();
	running = 0;//end the while
      }
    else if(input == 'a')
      {
	Add(hashtb, tbLen);
      }
    else if(input == 'r')
      {
	randAdd(firstNs, lastNs, randID, tbLen);
      }
    else if(input == 'p')
      {
	//Print();
      }
    else if(input == 'd')
      {
	//Delete();
      }
  }
  cout << "Farewell. Fare thee well."<<endl;
  return 0;
}

/*
//hash related dudes
void reHash(Node**& htb, int& tbSize)
{
  //make table twice the size
  //rehash and stuff
  //set it equal to original table
  tbSize = 2 * tbSize;
}
*/
int hashFunc(int id, char* fname, int tbSize)
{
  int index = 0;
  int nameVal = 0;
  int loops = 1;
  //maybe do some sort of % eq
  for(int i =0; i<sizeof(fname); ++i)
  {
    if(loops == 1)
    {
      nameVal = nameVal + fname[i];
      loops = 0;
    }
    else
    {
      nameVal = nameVal * fname[i];
      loops = 1;
    }
  }
  index = ((id + fname[0]) * nameVal) % tbSize;
  return index;
}


//add normal
Student* mkStud()
{
  Student* s = new Student;
  //vars
  char* fname = new char[16];
  char* lname = new char[16];
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
void Add(Node**& htb, int& tbLen)
{
  Student* s = new Student();
  s = mkStud();
  Node* node = new Node(s);
  int index;
  index = hashFunc(s->getI(), s->getF(), tbLen);
}

//add random
Student* randMkStud(vector<string>* firstNs, vector<string>* lastNs, int& randID)
{
  Student* s = new Student;
  int random;
  //first name
  char* fname = new char[16];
  int flen = firstNs->size();
  random = rand() % flen;
  strcpy(fname,(*(firstNs->begin()+random)).c_str());//https://stackoverflow.com/questions/21589353/error-cannot-convert-stdbasic-stringchar-to-const-char-for-argument-1#:~:text=Comments,do%20it%20without%20a%20temporary:
  //note for future me, lets try not using cstring and string at the same time (just...pick one)
  s->setF(fname);
  //last name
  char* lname = new char[16];
  int llen = lastNs->size();
  random = rand() % llen;
  strcpy(lname, (*(lastNs->begin()+random)).c_str());//so, I essentially use an iterator to get the loc of the name, then dereference that fellow to get the actual value, but it appears you cant convert that to a const car* without c_str()
  s->setL(lname);
  //id
  s->setI(randID);
  //gpa
  int gpa = rand() % 4 + 1; //set gpa to some nice random number
  s->setG(gpa);
  ++ randID;//incrimend after this student has been added
  cout << s->getF()<<endl;
  return s;
}
void randAdd(vector<string>* firstNs, vector<string>* lastNs, int& randID, int& tbLen)
{
  Student* tempS = new Student();
  int numStuds;
  int index;
  cout<<"How many students would you like to add?"<<endl;
  cin>>numStuds;
  cin.ignore(10, '\n');
  cin.clear();
  for(int i = 0; i < numStuds; ++i)
  {
    tempS = randMkStud(firstNs, lastNs, randID);
    index = hashFunc(tempS->getI(), tempS->getF(),tbLen);
  }
}

/*
//print
void Print()
{
  //get index from hash function
  //print if only node in chain
  //check if student has name and id requested if in chain
  //simply return if non existant 
}


//delete
void Delete()
{
  //get index from hash function
  //delete if only node in chain
  //check if student has name and id requested if in chain
    //correct the chain & table
  //simply return if non existant 
}


//quit
void Quit(){}
*/

