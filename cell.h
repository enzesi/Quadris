#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include <iostream>
#include <vector>
#include "info.h"
#include "subject.h"


class Observer;

class Cell: public Subject {
    int x, y;
    int ith = -1;
    char type = ' ';
    bool empty = true;
public:
    Cell(int x, int y);
    // getter method;
    bool getempty() const;
    Info getInfo() const;
    // setter method;
    void settype(char type);
    void setempty(bool empty);
    void setith(int ith);
    // clean the current cell temprorily;
    void cleartemp();
};

#endif
