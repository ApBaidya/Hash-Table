/*
Aparajita Baidya
2.12.2026

To do:
Quit
Store students in hash table:
 use chaining
 if more than 3 collisions occur when chaining, double array size and rehash
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

void Print(Node** htb, int& tbLen);//probably have to just look through array for what person wants
void Delete(int tI, float tG, char* tF, char*tL, Node**& htb, int tbLen);//delete specified value --> probably ask for details that can get hash functioned 
void Quit(int tbLen, Node**& htb);//have to delete each value in the table


//main
int main()
{
  int tbLen = 101;//starting length 
  char input;//user input
  int running = 1;
  int randID = 0;//lets start the random IDs at 0
  //for delete
  int tI;
  float tG;
  char* tF = new char[16];
  char* tL = new char[16];
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
	Quit(tbLen, hashtb);
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
	Print(hashtb, tbLen);
      }
    else if(input == 'd')
      {
	cout<<"first name:"<<endl;
        cin>>tF;
        cin.ignore(10, '\n');
        cin.clear();
        cout<<"last name:"<<endl;
        cin>>tL;
        cin.ignore(10, '\n');
        cin.clear();
	cout<<"id:"<<endl;
	cin>>tI;
	cout<<"gpa;"<<endl;
	cin>>tG;
	Delete(tI, tG, tF, tL, hashtb, tbLen);
      }
  }
  cout << "Farewell. Fare thee well."<<endl;
  return 0;
}


//hash related dudes
void reHash(Node**& htb, int& tbLen) 
{
  int chained = 0;//has a chain occured in the rehashing 
  int countChain = 0;//yet again for chaining
  int index;//re hashed index
  int oldTbLen = tbLen;//keep old tbLen
  tbLen = 2*tbLen;//double it
  Node** newHtb = new Node*[tbLen];//make new htb
  Node* tempN = nullptr;//for chaining --> will act as current
  Node* tempN2 = nullptr;//will act as next
  Node* tempN3 = nullptr;//yet another Node* --> for going through newHtb when hashing chains
  for(int i = 0; i<tbLen; i++)//set up newHtb
  {
    newHtb[i]=nullptr;
  }//end newHtb setup
  for(int i = 0; i<oldTbLen; i++)//enter main loop: go through old htb
  {
    countChain = 0;//reset the count each time
    if(htb[i]!=nullptr)//check if Node* at htb[i]
    {
      index = hashFunc(htb[i]->getStudent()->getI(), htb[i]->getStudent()->getF(), tbLen);
      if(htb[i]->getNext()!=nullptr)//check if part of chain
      {
	//cout<<"gonna deal with a chain"<<endl;
	tempN = htb[i];
	while(tempN!=nullptr)//loop through the chain
	{
	  //cout<<"found one"<<endl;
	  tempN2 = tempN->getNext();//store next pointer
	  tempN->setNext(nullptr);//get it out of the chain
	  index = hashFunc(tempN->getStudent()->getI(), tempN->getStudent()->getF(), tbLen);//get new index
	  //add it to newHtb --> check for collisions
	  if(newHtb[index]!=nullptr)//if collision
	  {
	    tempN3 = newHtb[index];
	    while(tempN3->getNext()!=nullptr)
	    {
	      tempN3=tempN3->getNext();//move through chain
	      ++countChain;
	    }
	    tempN3->setNext(tempN);
	    if(countChain >= 2)
	    {
	      cout<<countChain<<endl;
	      cout<<"again..."<<endl;
	      chained = 1;
	    }
	  }//end collision check
	  else
	  {
	    newHtb[index]=tempN;
	  }
	  tempN=tempN2;//move up chain
	}
      }//end rehash of chain
      else//if not part of a chain
	{
	if(newHtb[index]!=nullptr)//check if collision
	{
	  tempN = newHtb[index];
	  while(tempN->getNext()!=nullptr)
	  {
	    tempN=tempN->getNext();
	    ++countChain;
	  }
	  tempN->setNext(htb[i]);
	  if(countChain>=2)//4th node added to linked list
	  {
	    cout<<countChain<<endl;
	    cout<<"aggaaaainn"<<endl;
	    chained = 1;//time to reHash again
	  }
	}//end of collision check
	else//no need to check if collision
	{
	  newHtb[index]=htb[i];
	}
      }//exit rehash of not chain
    }//exit rehash for htb[i]
  }//exit main loop
  for(int i=0; i<oldTbLen;i++)//clean out old htb
  {
    htb[i] = nullptr;
  }//end of resetting old htb
  htb = newHtb;//finally, change old htb
  if(chained==1){
    cout<<"AGAIN"<<endl;
    reHash(htb, tbLen);
  }
  cout<<"done"<<endl;
  return;
}

int hashFunc(int id, char* fname, int tbLen)//we should, uh, make this better
{
  int len = 0;
  int index = 0;
  int nameVal = 0;
  
  //maybe do some sort of % eq
  for(int i =0; i<strlen(fname); ++i)
  {
    ++len;
    nameVal = nameVal + fname[i] * id;
  }
  index = ((id + fname[0]) * nameVal); 
  if(index < 0){
    index = index * -1;
  }
  index = index/len;
  index = index % tbLen;
  //index = id % tbLen;
  //cout<<"I probably shouldn't cout this but the index is "<<index<<endl;;
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
  int chained = 0; //check if chaining is true. 
  Student* s = new Student();
  s = mkStud();
  Node* node = new Node(s);
  int index;
  Node* tempN = nullptr;//for chains
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
      cout<<"okay"<<endl;
      tempN = htb[index];
      while(tempN->getNext()!=nullptr)
      {
	cout<<"passing"<<endl;
	tempN = tempN->getNext();
	++chained;
      }
      tempN->setNext(node);
    }
  }
  cout<<index<<htb[index]->getStudent()->getF();
  if(chained >= 2)
  {
    cout<<"rehash time"<<endl;
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
  //cout << s->getF()<<endl;
  return s;
}
void randAdd(Node**& htb, vector<string>* firstNs, vector<string>* lastNs, int& randID, int& tbLen)
{
  Student* tempS = new Student();
  int numStuds;
  int index;
  int chained = 0;
  int rehash = 0;
  Node* tN = nullptr;//for chaining
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
    else//collision
    {
      if(htb[index]->getNext() == nullptr)
      {
	htb[index] -> setNext(tempNode);
      }
      else
      {
	cout<<"okay"<<endl;
	tN=htb[index];
	while(tN->getNext()!=nullptr)
	{
	  cout<<"passing"<<endl;
	  tN = tN->getNext();
	  ++chained;
	}
	cout<<chained;
	tN->setNext(tempNode);
	if(chained >= 2)
	{
	  cout<<"AAAAAAAAAAAAAA"<<endl;
	  rehash = 1;
	}
      }
    }
    chained = 0;
  }
  if(rehash == 1)
  {
    cout<<"rehash time"<<endl;
    reHash(htb, tbLen);
  }
}

//print
void Print(Node** htb, int& tbLen)
{
  int len = 0;
  Student* tempS = new Student();
  Node* tempN = new Node(tempS);
  for(int i = 0; i<tbLen; i++)//look through everything, print anything you can seeeeee
  {
    if(htb[i]!=nullptr)
    {      
      if(htb[i]->getNext()!=nullptr)//chain!!!!
      {
	tempN = htb[i];
	while(tempN!=nullptr)
	{
	  ++len;
	  tempS = tempN->getStudent();//lets set the student
	  cout<<"Name:"<<tempS->getF()<<" "<<tempS->getL()<<" ID:"<<tempS->getI()<<" GPA:"<<setprecision(3)<<tempS->getG()<<endl;
	  tempN = tempN->getNext();//progress through the while
	}
      }
      else//no chain
      {
	++len;
	tempS = htb[i]->getStudent();
	cout<<"Name:"<<tempS->getF()<<" "<<tempS->getL()<<" ID:"<<tempS->getI()<<" GPA:"<<setprecision(3)<<tempS->getG()<<endl;
      }
    }
  }
  cout<<len<<endl;
  return;
}

//delete
void Delete(int tI, float tG, char* tF, char*tL, Node**& htb, int tbLen)
{
  int index;
  cout<<tI<<tG<<tF<<tL<<endl;
  if(htb[3] != nullptr){
    cout<<"debug: "<<htb[3]<<endl;
  }
  Student* tempS = new Student();
  Node* tempN = nullptr;
  index=hashFunc(tI, tF, tbLen);//get index from hash function
  //delete if only node in chain
  cout<<"index is : "<<index<<endl;
  cout<<htb[index]<<endl;
  if(htb[index]!=nullptr)//node there?
  {
    cout<<"a"<<endl;
    tempS = htb[index]->getStudent();
    //first node
    if(tempS->getI()==tI && tempS->getG()==tG && strcmp(tF, tempS->getF())==0 && strcmp(tL, tempS->getL())==0)
    {
      cout<<"b"<<endl;
      //does that node have a chain?
      if(htb[index]->getNext()!=nullptr)
      {
	tempN = htb[index]->getNext();
	htb[index]->setNext(nullptr);
	delete htb[index];
	htb[index]=tempN;//set head of chain to what the next val in the chain was
	return;
      }
      else//only other thing is not in chain so...
      {
	cout<<"c"<<endl;
	delete htb[index];
	htb[index] = nullptr;//reset that fellow
	return;
      }
    }
    else//check if there is a chain: check chain
    {
      cout<<"d"<<endl;
      //Student* tS2 = new Student();
      //Node* prev = new Node(tS2);
      Node* prev = htb[index];
      tempN = htb[index];
      while(tempN!=nullptr)//not at end of chain
      {
	tempS = tempN->getStudent();
	if(tempS->getI()==tI && tempS->getG()==tG && strcmp(tF, tempS->getF())==0 && strcmp(tL, tempS->getL())==0)
	{
	  cout<<"e"<<endl;
	  prev->setNext(tempN->getNext());
	  tempN->setNext(nullptr);
	  delete tempN;
	  return;
	}
	prev = tempN;
	tempN = tempN -> getNext();
      }
    }
  }
  return;
}

//quit
void Quit(int tbLen, Node**& htb)
{
  int len = 0;
  Node* current = nullptr;//for chains
  Node* next = nullptr;
  for(int i = 0; i<tbLen; i++)
  {
    if(htb[i]!=nullptr)
    {
      //chain
      if(htb[i]->getNext()!=nullptr)
      {
	current = htb[i];//head
	next = htb[i];
	len = 0;
	while(next!=nullptr)
	{
	  ++len;
	  //cout<<"delete in chain"<<endl;
	  next = current->getNext();
	  current->setNext(nullptr);
	  delete current;
	  current = next;//set current to the next value
	}
	cout<<len<<endl;
      }
      //not chain
      else
      {
	//++len;
	//cout<<"delete"<<endl;
	delete htb[i];
	htb[i] = nullptr;
      }
    }
  }
  /*
  for(int i = 0; i<tbLen; i++){
    if(htb[i]!= nullptr)
    {
      cout<<htb[i]->getStudent()->getF()<<endl;
      cout<<"oops"<<endl;
    }
    }*/
  cout<<len<<endl;
  return;
}

