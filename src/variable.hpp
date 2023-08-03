/*
* Class that represents variable
*/

#pragma once

#include "entity.hpp"

class Variable final :
    public Entity {
public:
    Variable();
    Variable(double value);

    void MakeNonActual() override;

    Variable& operator=(double value);

};
