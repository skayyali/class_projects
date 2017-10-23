#include "List.h"
class Queue : List {
public:
	ListNode * _head;
	void Enqueue(int val);
	int Dequeue();
	Queue();
	~Queue();
};


