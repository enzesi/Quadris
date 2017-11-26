#ifndef CELL_H
#define CELL_H
#include <cstddef>
#include <iostream>
#include <vector>
#include "info.h"
#include "subject.h"
#include "observer.h"

class Cell: public Subject {
    int x, y;
    int ith = -1;
    char type = ' ';
    bool empty = true;
public:
    Cell(int x, int y);
    bool getempty() const;
    Info getInfo() const;
    void settype(char type);
    void setempty(bool empty);
    void setith(int ith);
};

#endif
