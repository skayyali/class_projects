//
// Implement the Queue class
//

#include <stdio.h>
#include "Queue.h"

int 
Queue::Dequeue ( )
{
	int value = _head->_value;
	if(remove(_head->_value) == 0)
	{
		return value;
	}
	else
	{
		return -1;	
	}
}

void Queue::Enqueue ( int val )
{
	append(val);
}


//
// List constructor
//
Queue::Queue()
{
  // Complete procedure 
	_head = new ListNode;
	_head->_value = (int)NULL;
	_head->_next = NULL;
}

//
// List destructor: delete all list elements, if any.
//
Queue::~Queue()
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

