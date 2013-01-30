#include "stack.h"

Stack::Stack() {
//constructor without arguments
    head = 0;
    length = 0;
}

Stack::Stack(int num) {
//constructor wherein argument becomes first element
    head = 0;
    length = 0;
    push(num);
}

Stack::~Stack() {
//destructor
    while (get_length())
        pop();
}

int Stack::get_length() {
//accessor for length
    return length;
}


int* Stack::array() {
//returns the contents of the stack in an array format
//this is useful for various purposes
    NODE *node = head;
    
    int *array = new int[length];
    //creates the array
    
    for(int i = 0; i < length; i++) {
        array[i] = node->value;
        //populates the array
        node = node->next;
    }
    return array;
}


void Stack::push(int num) {
//push num into head
    NODE *first = new NODE;
    first -> value = num;
    first -> next = head;
    head = first;
    length++;
    
}

int Stack::top() {
//what's in head?
    if (!head)
        throw "can't top: list is empty";
        
    return head->value;
}

void Stack::pop() {
//pop off the head
    if (!head)
        throw "can't pop: list is empty";
    
    NODE *first = head;
    head = head->next;
    delete first;
    length--;
} 

