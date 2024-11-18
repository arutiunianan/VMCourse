#ifndef LABEL_H_
#define LABEL_H_

#include <string>
#include <vector>

class Label {
public:
    std::string name;
    int         address;

    Label(std::string n, int a):
          name(n), address(a) {};
};

#endif // #define LABEL_H_