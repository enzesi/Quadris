#include "subject.h"
using namespace std;

void Subject::attach(shared_ptr<Observer> o) {
    observers.emplace_back(o);
}

void Subject::notifyObservers() {
    for (auto &ob : observers) ob->notify(*this);
}
