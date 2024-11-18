#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>

typedef double Elem_t;

class Stack {
private:
	size_t size;
	std::vector<Elem_t> data;

public:
    Stack(): size(0) {};

    void   StackPush(Elem_t elem);
    Elem_t StackPop();
};

#endif // STACK_H