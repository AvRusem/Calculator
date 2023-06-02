/*
* Class that represents variable
*/

#pragma once

#include "entity.h"

class Variable final :
    public IEntity {
private:
    double value_;

public:
    Variable();
    Variable(double value);

    double Extract() const override;

    Variable& operator=(double value);

};
