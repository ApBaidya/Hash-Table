/*
Aparajita Baidya
2.11.2026

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
void randAdd(Node**& htb, vector<string>* firstNs, vector<string>* lastNs, int& randID, int& tbLen);//ask for stud amounts --> do randMkStud that many times & add to table 
void reHash(Node**& htb, int& tbLen);//remake hash Table --> make new table --> call hashFunc for all nodes --> set old func to new
int hashFunc(int id, char* fname, int tbLen);//does the hash function stuff, returns index for node*
Student* mkStud();//makes the student 
void Add(Node**& htb, int& tbLen);//adds student to node*, adds student to hash table
//when adding, probably check if it has to go through a chain, and then count how many times it loops to get to end. if there are three nodes in the chain already, add new node to end, then call reHash()

void Print();//probably have to just look through array for what person wants
void Delete();//delete specified value --> probably ask for details that can get hash functioned 
void Quit();//have to delete each value in the table


//main
int main()
{
  int tbLen = 102;//starting length 
  char input;//user input
  int running = 1;
  int randID = 0;//lets start the random IDs at 0
  Node** hashtb = new Node*[tbLen];//hash table
  for(int i = 0; i<tbLen+1; i++)//there has to be a better way...right?
  {
    hashtb[i] = nullptr;
  }
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
      //cout << word<<endl;
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
	randAdd(hashtb, firstNs, lastNs, randID, tbLen);
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


//hash related dudes
void reHash(Node**& htb, int& tbLen) 
{
  int oldTbLen;
  oldTbLen = tbLen;
  cout<<"Time to redo that table"<<endl;
  Student* tempStud = new Student();
  Node* tempNode = new Node(tempStud);//store node that needs to get re hashed
  Student* tS2 = new Student();
  Node* tN2 = new Node(tS2);//for doing collision things with
  int tempIndex = 0;//hash func index
  cout<<"update table length"<<endl;
  tbLen = tbLen+tbLen;//get len of new table
  Node** newTb = new Node*[tbLen];//the new table, twice the size of the old
  for(int i = 0; i<tbLen; i++)
  {
    newTb[i] = nullptr;
  }
  int chained = 0;//do I...need to rehash again?
  cout<<"starting"<<endl;
  for(int i = 0; i<oldTbLen; i++)//rehash everything in htb
  {
    cout<<"looking"<<endl;
    cout<<"current index:"<<i<<":"<<htb[i]<<endl;
    if(htb[i] != nullptr)//if node 
    {
      cout<<"found one"<<endl;
      tempNode = htb[i];//set it to the current
      cout<<"a"<<tempNode->getStudent()->getF()<<endl;//print this student's name
      tempIndex = hashFunc(tempNode->getStudent()->getI(), tempNode->getStudent()->getF(), tbLen);
      cout<<"b"<<endl;
      if(newTb[tempIndex]!=nullptr)//collision
      {
	cout<<"c"<<endl;
	if(newTb[tempIndex]->getNext() == nullptr)//first collision
	{
	  newTb[tempIndex]->setNext(tempNode);//add it to end
	  cout<<"d"<<endl;
	}
	else//2nd collision...or more...seperate to make chained = 1
	{
	  cout<<"Oh geez, guess we gotta do this again"<<endl;
	  tN2 = newTb[tempIndex];
	  while(tN2 -> getNext() != nullptr)
	  {
	    cout<<"wait"<<endl;
	    tN2 = tN2->getNext();//while going through the list, lets set tN2 to the next pointer
	  }
	  cout<<"inserted"<<endl;
	  tN2->setNext(tempNode);//add it to end of chain
	  chained = 1;
	}//end collision checks      
      }
      else//if no chain
      {
	cout<<"nice"<<endl;
	newTb[tempIndex] = tempNode;
      }
      cout<<"is there a chain here?"<<endl;
      //check if chain is there at the htb position, lets use tN2
      if(htb[i]->getNext()!=nullptr)//if chain
      {
	tN2 = htb[i];//head
	cout<<"lets handle that chain"<<endl;
	Student* tS3 = new Student();
	Node* tN3 = new Node(tS3);//for some looping
	tN3 = htb[i];//head again
	while(tN2!=nullptr)//look through chain 
	{
	  tN2 = tN3;//reset tN2 to prev
	  cout<<"found one2"<<endl;
	  tN3 = tN2->getNext();//move up to look at next Node*
	  cout<<"got next"<<endl;
	  tN2->setNext(nullptr);//detach it from chain as already been sorted
	  cout<<tN3->getStudent();//SEG FAULT WHYYYYY
	  cout<<"detach old"<<endl;
	  tempIndex = hashFunc(tN3->getStudent()->getI(),tN3->getStudent()->getF(), tbLen);
	  cout<<"got new index"<<endl;
	  if(newTb[tempIndex]!=nullptr)//collision
	  {
	    cout<<"collision"<<endl;
	    if(newTb[tempIndex]->getNext()!=nullptr)//3rd in chain
	    {
	      cout<<"agaaaaain?!!!"<<endl;
	      tN2 = newTb[tempIndex];//head of the new table's chain 
	      while(tN2 -> getNext() != nullptr)//go through chain to get to end
	      {
		cout<<"wait"<<endl;
		tN2 = tN2->getNext();
	      }
	      cout<<"inserted"<<endl;
	      tN2->setNext(tempNode);
	      chained = 1;
	    }
	    else//only 2nd collision
	    {
	      cout<<"added"<<endl;
	      newTb[tempIndex]->setNext(tempNode);
	    }
	  }//end of collision check
	  tN2 = tN3->getNext();//progress
	}
      }//end of chain check, continue looping
    }//end rehash for htb[i]
  }
  //set it equal to original table
  for(int i = 0; i<oldTbLen; ++i)
  {
    htb[i] = nullptr;
  }
  htb = newTb;//set it equal to new table
  //rehash again?
  if(chained == 1)
  {
    reHash(htb, tbLen);
  }
  cout<<"done"<<endl;
  return;
}

int hashFunc(int id, char* fname, int tbLen)//we should, uh, make this better
{
  int index = 0;
  int nameVal = 0;
  int loops = 1;
  /*
  //maybe do some sort of % eq
  for(int i =0; i<strlen(fname); ++i)
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
  index = ((id + fname[0]) * nameVal) % tbLen;*/
  index = id % tbLen;
  cout<<"I probably shouldn't cout this but the index is "<<index<<endl;;
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
  int chain = 0; //check if chaining is true. 
  Student* s = new Student();
  s = mkStud();
  Node* node = new Node(s);
  int index;
  index = hashFunc(s->getI(), s->getF(), tbLen);
  if(htb[index]==nullptr)//no collision
  {
    htb[index] = node;
  }
  else//collision
  {
    if(htb[index]->getNext() == nullptr)
    {
      htb[index]->setNext(node);
    }
    else
    {
      htb[index]->getNext()->setNext(node);
      //set it as 3rd in chain, set chain to 1 to rehash
      chain = 1;
    }
  }
  cout<<index<<htb[index]->getStudent()->getF();
  if(chain == 1)
  {
    reHash(htb, tbLen);
  }
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
void randAdd(Node**& htb, vector<string>* firstNs, vector<string>* lastNs, int& randID, int& tbLen)
{
  Student* tempS = new Student();
  int numStuds;
  int index;
  int chained = 0;
  cout<<"How many students would you like to add?"<<endl;
  cin>>numStuds;
  cin.ignore(10, '\n');
  cin.clear();
  for(int i = 0; i < numStuds; ++i)
  {
    tempS = randMkStud(firstNs, lastNs, randID);
    index = hashFunc(tempS->getI(), tempS->getF(),tbLen);
    Node* tempNode = new Node(tempS);
    if(htb[index]==nullptr)
    {
      htb[index]=tempNode;
    }
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

