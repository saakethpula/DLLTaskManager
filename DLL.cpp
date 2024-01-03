// Saaketh Pula Section 10
#include "DNode.hpp"
#include "DLL.hpp"
#include <iostream>
#include <cstdlib>
#include <math.h>
using namespace std;


DLL::DLL() {
    first = NULL;
    last = NULL;
    numTasks = 0;
    tothrs = 0;
    totmin = 0;
}


DLL::DLL(string t, int p, int h, int m){
    first = new DNode(t, p, h, m);
    last = first;
    numTasks = 1;
    tothrs = h;
    totmin = m;
}

DLL::~DLL() {
    DNode* current = first;
    while (current != NULL) {
        DNode* next = current->next;
        delete current;
        current = next;
    }
    first = NULL;
    last = NULL;
}


void DLL::push(string t, int p, int h, int m) {
    DNode* newNode = new DNode(t, p, h, m);
    if (first == nullptr) {
        first = newNode;
        last = newNode;
    } else {
        DNode* current = first;
        while (current != nullptr && current->task->priority <= p) {
            current = current->next;
        }
        if (current == first) {
            newNode->next = first;
            first->prev = newNode;
            first = newNode;
        } else if (current == nullptr) {
            last->next = newNode;
            newNode->prev = last;
            last = newNode;
        } else {
            newNode->next = current;
            newNode->prev = current->prev;
            current->prev->next = newNode;
            current->prev = newNode;
        }
    }
    addTime(h, m);
    numTasks++;
}


Task *DLL::pop() {
    DNode *temp = first;
    Task* tempTask = temp->task; // want to return the data
    removeTime(temp->task->hr,temp->task->min);
    numTasks--;
    first = first->next;
    delete temp;
    last->next = NULL;
    numTasks--;
    return tempTask;
}
int DLL::remove(int tn) {
    DNode *curr = first;
    if (numTasks == 0) {
        return -1;
    } else if (numTasks == 1 && tn == first->task->tasknum) {
        delete first;
        first = nullptr;
        last = nullptr;
        numTasks = 0;
        tothrs = 0;
        totmin = 0;
        return tn;
    }
    while (curr->next != nullptr) {
        if (curr->task->tasknum == tn) {
            if (curr == first) {
                first = curr->next;
                first->prev = nullptr;
            } else {
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
            }
            numTasks--;
            removeTime(curr->task->hr, curr->task->min);
            delete curr;
            return tn;
        }
        curr = curr->next;
    }
    if (tn == last->task->tasknum) {
        removeTime(last->task->hr, last->task->min);
        last->prev->next = nullptr;
        last = last->prev;
        numTasks--;
        return tn;
    }
    return -1;
}
void DLL::addTime(int h, int m) {
    tothrs += h;
    tothrs += m/60;
    totmin += m%60;

}

void DLL::removeTime(int h, int m) {
    if (totmin - m < 0) {
        tothrs -= h;
        tothrs -= 1;
        totmin = totmin-(60 - m);
    } else {
        tothrs -= h;
        totmin -= m;
    }

}
void DLL::moveDown(int tn) {
    if (numTasks == 1 || numTasks == 0) {
        return;
    } else if (numTasks == 2) {
        if (first->task->tasknum == tn || last->task->tasknum == tn) {
            DNode *temp = first;
            first = last;
            last = temp;
            first->next = last;
            first->prev = nullptr;
            last->next = nullptr;
            last->prev = first;
            if (first->task->tasknum == tn) {
                first->task->priority = last->task->priority;
            } else {
                last->task->priority = first->task->priority;
            }
        }
        return;
    } else if (numTasks == 3 && first->next->task->tasknum == tn) {
        DNode *temp = first->next;
        first->next = last;
        last->prev = first;
        last->next = temp;
        temp->prev = last;
        temp->next = nullptr;
        temp->task->priority = last->task->priority;
        last = temp;
        return;
    }
    if (first->task->tasknum == tn) {
        DNode *one = first->next;
        DNode *two = one->next;
        one->prev = nullptr;
        one->next = first;
        first->prev = one;
        first->next = two;
        two->prev = first;
        first->task->priority = one->task->priority;
        first = first->prev;
        return;
    } else if (first->next->task->tasknum == tn) {
        DNode *one = first->next;
        DNode *two = one->next;
        DNode *three = two->next;
        two->prev = first;
        first->next = two;
        one->prev = two;
        two->next = one;
        three->prev = one;
        one->next = three;
        one->task->priority = two->task->priority;
        return;
    } else if (last->prev->task->tasknum == tn) {
        DNode *one = last->prev;
        DNode *two = one->prev;
        two->next = last;
        last->prev = two;
        last->next = one;
        one->prev = last;
        one->next = nullptr;
        one->task->priority = last->task->priority;
        last = one;
        return;
    } else if (last->task->tasknum == tn) {
        DNode *one = last->prev;
        first->prev = last;
        last->next = first;
        one->next = nullptr;
        last->prev = nullptr;
        last->task->priority = first->task->priority;
        first = last;

        last = one;
        return;
    } else {
        DNode *curr = first;
        while (curr != nullptr) {
            if (curr->task->tasknum == tn) {
                DNode *one = curr->prev;
                DNode *two = curr->next;
                DNode *three = two->next;
                two->prev = one;
                one->next = two;
                curr->prev = two;
                two->next = curr;
                three->prev = curr;
                curr->next = three;
                curr->task->priority = two->task->priority;
                return;
            }
            curr = curr->next;
        }
    }
}
void DLL::moveUp(int tn) {
    DNode *current = first;
    while (current != NULL) {
        if (current->task->tasknum == tn) {
            if (numTasks == 1) {
                return;
            } else if (numTasks == 2){
                DNode* one = first;
                DNode* two = last;
                two->prev = one;
                one->prev = NULL;
                one->next = two;
                two->next = NULL;
                if (current == first) {
                    current->task->priority = current->prev->task->priority;
                } else {
                    current->task->priority = current->next->task->priority;
                }
                first = two;
                last = one;
                return;
            } else if (numTasks == 3) {
                DNode* one = first;
                DNode* two = current;
                DNode* three = last;
                if (current->prev == first) {
                    two->prev = NULL;
                    one->prev = two;
                    three->prev = one;
                    three->next = NULL;
                    one->next = three;
                    two->next = one;
                    first = two;
                    return;
                }
            }
            if (current->prev == first) {
                DNode* one = first;
                DNode* two = current;
                DNode* three = current->next;
                DNode* four = current->next->next;
                two->next = one;
                two->prev = nullptr;
                one->prev = two;
                one->next = three;
                three->next = four;
                three->prev = one;
                first = two;
            } else if (current == first) {
                DNode* one = first;
                DNode* two = current->next;
                DNode* three = current->next->next;
                DNode* four = last;
                one->prev = four;
                one->next = nullptr;
                four->next = one;
                two->prev = nullptr;
                first = two;
                last = one;
                last->task->priority = 3;
            } else if (current->next == last) {
                DNode* one = current->prev->prev;
                DNode* two = current->prev;
                DNode* three = current;
                DNode* four = current->next;
                one->next = three;
                three->next = two;
                two->next = four;
                four->prev = two;
                two->prev = three;
                three->prev = one;
                current->task->priority = current->next->task->priority;
            } else if (current == last) {
                DNode* one = current->prev->prev;
                DNode* two = current->prev;
                DNode* three = last;
                one->next = three;
                three->next = two;
                two->next = nullptr;
                two->prev = three;
                three->prev = one;
                last = two;
                current->task->priority = current->next->task->priority;
            } else {
                DNode* one = current->prev->prev;
                DNode* two = current->prev;
                DNode* three = current;
                DNode* four = current->next;
                one->next = three;
                three->next = two;
                two->next = four;
                four->prev = two;
                two->prev = three;
                three->prev = one;
                current->task->priority = current->next->task->priority;
            }
        }
        current = current->next;
    }
}


void DLL::changePriority(int tn, int newp) {
    if (numTasks == 0) {
        return;
    } else if (numTasks == 1 && first->task->tasknum == tn) {
        first->task->priority = newp;
        return;
    }
    DNode *curr = first;
    while (curr != nullptr) {
        if (curr->task->tasknum == tn) {
            if (newp == 1) {
                while (curr != first) {
                    moveUp(tn);
                }
                while (curr->task->priority == 1) {
                    moveDown(curr->task->tasknum);
                }
                if (curr != first) {
                    moveUp(tn);
                }
                curr->task->priority = newp;
            } else if (newp == 2) {
                changePriority(tn, 3);
                while (curr->task->priority == 3) {
                    moveUp(tn);
                }
                moveDown(tn);
                curr->task->priority = newp;
            } else if (newp == 3) {
                while (curr != last) {
                    moveDown(tn);
                }
                curr->task->priority = newp;
            }
        }
        curr = curr->next;
    }
}

void DLL::listDuration(int *th, int *tm, int tp) {
    DNode *tmp = last;
    *th = 0;
    *tm = 0;
    while (tmp != NULL) {
        if (tmp->task->priority == tp) {
            *th += tmp->task->hr;
            *tm += tmp->task->min ;
        }
        *th = *th+*tm/60;
        *tm = *tm%60;
        tmp = tmp->prev;
    }
}


void DLL::printList() {
    cout << "Total Time Required: " << tothrs+totmin/60 << ":" << totmin%60<< endl;
    DNode *tmp = first;
    while (tmp != NULL) {
        tmp->task->printTask();
        tmp = tmp->next;
    }
    cout<<endl;
}

void DLL::printList(int p) {
    DNode *tmp = first;
    int phrs = 0;
    int pmin = 0;
    listDuration(&phrs,&pmin,p);
    cout << p <<": Total Time Required: "<< phrs << ":"<< pmin <<endl;
    while (tmp != NULL) {
        if (tmp->task->priority == p) {
            tmp->task->printTask();
        }
        tmp = tmp->next;
    }
    cout<<endl;
}
