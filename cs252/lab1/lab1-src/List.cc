//
// Implement the List class
//

#include <stdio.h>
#include "List.h"

//
// Inserts a new element with value "val" in
// ascending order.
//
void
List::insertSorted( int val )
{
  // Complete procedure
	ListNode *current = _head;
	ListNode *previous = _head;
	while(current->_value <= val && current->_next != NULL)
	{
		previous = current;
		current = current->_next;
	}
	if(current->_value >= val)
	{
		if(_head == current)
		{
			ListNode *newNode = new ListNode;
			newNode->_next = _head;
			newNode->_value = val;
			_head = newNode;	
		}
		else
		{
			ListNode *newNode = new ListNode;
			previous->_next = newNode;
			newNode->_value = val;
			newNode->_next = current;
		}
	}
	if(current->_value < val)
	{
		ListNode *newNode = new ListNode;
		newNode->_value = val;
		newNode->_next = current->_next;
		current->_next = newNode;
		
	}
}
//
// Inserts a new element with value "val" at
// the end of the list.
//
void
List::append( int val )
{
	ListNode *current = _head;
	while(current->_next != NULL){
		current = current->_next;
	}
	ListNode *next = new ListNode;
	next->_value = val;
	current->_next = next;
}

//
// Inserts a new element with value "val" at
// the beginning of the list.
//
void
List::prepend( int val )
{
  // Complete procedure
	ListNode *next = new ListNode;
	next->_value = val;
	next->_next = _head;
	_head = next;
}

// Removes an element with value "val" from List
// Returns 0 if succeeds or -1 if it fails
int 
List:: remove( int val )
{
  // Complete procedure
	ListNode *current = _head;
	ListNode *previous = _head;
	while(current->_value != val && current->_next != NULL)
	{
		previous = current;
		current = current->_next;
	}
	if(current->_value == val)
	{
		if(current == _head){
			_head = current->_next;
			delete(current);
			return 0;
		}
		else{
			previous->_next=current->_next;
			delete(current);
			return 0;
		}
	}
  return -1;
}

// Prints The elements in the list. 
void
List::print()
{
  // Complete procedure
	ListNode *current = _head;
	while(current->_next != NULL)
	{
		printf("%d ", current->_value);
		current = current->_next;
	}
	printf("%d ", current->_value);
}

//
// Returns 0 if "value" is in the list or -1 otherwise.
//
int
List::lookup(int val)
{
  // Complete procedure 
	ListNode *current = _head;
	while(current->_value != val && current->_next != NULL)
	{
		current = current->_next;
	}
	if(current->_value == val)
	{
		return 0;
	}
  return -1;
}

//
// List constructor
//
List::List()
{
  // Complete procedure 
	_head = new ListNode;
	_head->_value = (int)NULL;
	_head->_next = NULL;
}

//
// List destructor: delete all list elements, if any.
//
List::~List()
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

