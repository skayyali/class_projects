//
// Implement the List class
//

#include <stdio.h>
#include "Stack.h"

int Stack::pop ( )
{
	ListNode *current = _head;
	while(current->_next != NULL)
	{
		current = current->_next;
	}
	int value = current->_value;
	if(remove(current->_value) == 0)
		return value;
	else
		return -1;
}

void Stack::push ( int val )
{
	append(val);
}


//
// List constructor
//
Stack::Stack()
{
  // Complete procedure 
	_head = new ListNode;
	_head->_value = (int)NULL;
	_head->_next = NULL;
}

//
// List destructor: delete all list elements, if any.
//
Stack::~Stack()
{
  // Complete procedure 
	 
	ListNode *current = _head;
	while(current != NULL && current->_next != NULL)
	{
		delete(current);
		current = current->_next;
	}
	if(current != NULL)
		delete(current);
}

