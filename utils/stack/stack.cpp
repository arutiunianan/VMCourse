#include "stack.hpp"

void Stack::Push(Elem_t elem) {
	data.push_back(elem);
	++size;
}

Elem_t Stack::Pop() {
    Elem_t del_elem = data.back();

    data.pop_back();
	--size;
	return del_elem;
}
