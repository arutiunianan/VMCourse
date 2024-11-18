#include "stack.hpp"

void Stack::StackPush(Elem_t elem) {
	data.push_back(elem);
	++size;
}

Elem_t Stack::StackPop() {
    Elem_t del_elem = data[size - 1];

    data.pop_back();
	--size;
	return del_elem;
}
