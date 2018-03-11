#ifndef TEXTDISPLAY_H
#define TEXTDISPLAY_H
#include <iostream>
#include <vector>
#include <memory>
#include "subject.h"
#include "info.h"


class Observer;

class Cell;

class TextDisplay: public Observer {
    std::vector<std::vector<char>> theDisplay;
public:
    TextDisplay();
    
    void notify(Subject &whoNotified) override;
    
    friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif
