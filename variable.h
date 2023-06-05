/*
* Class that represents variable
*/

#pragma once

#include "entity.h"

class Variable final :
    public Entity {
private:
    void MakeNonActual() noexcept;

public:
    Variable();
    Variable(double value);

    Variable& operator=(double value);

};
