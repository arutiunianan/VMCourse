#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <vector>

typedef double Elem_t;

const size_t INITIAL_CAPACITY = 2;

class Stack
{
private:
	size_t size;
	size_t capacity;

	std::vector<Elem_t> data;

public:
    Stack(): size(0), capacity(INITIAL_CAPACITY) {};
    Stack(size_t cap): size(0), capacity(cap) {};

    void   StackPush(Elem_t elem);
    Elem_t StackPop();
};

#endif // STACK_H