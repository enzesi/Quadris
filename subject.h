#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
#include "observer.h"
#include <memory>
struct Info;

class Subject {
    std::vector<std::shared_ptr<Observer>> observers;
public:
    void attach(std::shared_ptr<Observer> o);
    void notifyObservers();
    virtual Info getInfo() const = 0;
};


#endif
