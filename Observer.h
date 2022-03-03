#ifndef OBSERVER_H
#define OBSERVER_H
#include "Data.h"

class Observer
{
public:
    Observer() {}
    virtual void updateData(const QList<Data>& data) = 0;
    virtual ~Observer() {}
};


#endif // OBSERVER_H
