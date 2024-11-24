#ifndef STACK_H
#define STACK_H

#include <iostream>
#include <list>

typedef double Elem_t;

class Stack {
private:
	size_t size;
	std::list<Elem_t> data;

public:
    Stack(): size(0) {};

    size_t get_size() {
        return size;
    }

    void   Push(Elem_t elem);
    Elem_t Pop();
};

#endif // STACK_H