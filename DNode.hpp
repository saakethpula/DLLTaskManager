// Saaketh Pula Section 10

#ifndef DNODE_HPP_
#define DNODE_HPP_
#include <cstdlib>
using namespace std;

#include "Task.hpp"

class DNode {
	friend class DLL;
	Task *task;
    DNode *next;
    DNode *prev;
public:
	DNode(); // empty constructor, sets all variables to default NULL value
	DNode(string t, int p, int lenhr, int lenmin);
    DNode(Task *task, DNode *prev, DNode *next);
    // node containing a task with the given parameters, sets variables to appropriate values
};



#endif /* DNODE_HPP_ */
