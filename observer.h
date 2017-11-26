#ifndef _OBSERVER_H_
#define _OBSERVER_H_

class Subject;

class Cell;

class Observer {
public:
    virtual void notify(Subject &who) = 0;
    virtual ~Observer();
};

#endif
