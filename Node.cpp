//Aparajita Baidya 1.28.2026
#include "Node.h"

Node::Node(Student* s)
{
  student = s;
  next = nullptr;
}
Node::~Node()
{
  delete student;
}
void Node::setNext(Node* n)
{
  next = n;
}
Node* Node::getNext()
{
  return next;
}
Student* Node::getStudent()
{
  return student;
}
