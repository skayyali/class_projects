#include "List.h"

class Stack : List {
public:
	ListNode *_head;
	void push(int val);
	int pop();
	Stack();
	~Stack();
};

