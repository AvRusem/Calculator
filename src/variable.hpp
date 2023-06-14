/*
* Class that represents variable
*/

#pragma once

#include "entity.hpp"

class Variable final :
    public Entity {
private:
    void MakeNonActual();

public:
    Variable();
    Variable(double value);

    Variable& operator=(double value);

};
