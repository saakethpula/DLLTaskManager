
// Saaketh Pula Section 10

#include <cstdlib>
#include <iostream>
#include "DNode.hpp"
using namespace std;

/* write your constructors here! */
DNode::DNode() {
    task = nullptr;
    prev = nullptr;
    next = nullptr;
}
DNode::DNode(string t, int p, int h, int m){
    task = new Task(t, p, h, m);
    prev = nullptr;
    next = nullptr;
}

DNode::DNode(Task *task, DNode *prev, DNode *next) {
    this->task = task;
    this->prev = prev;
    this->next = next;
}

