/*
* Class that represents function
*/

#pragma once

#include "entity.h"
#include "operator.h"
#include "variable.h"

#include <memory>

class Function final :
    public IEntity {
private:
    std::shared_ptr<IEntity> first_;
    std::shared_ptr<IEntity> second_;
    std::unique_ptr<Operator> operator_;

public:
    Function() = default;
    Function(const std::shared_ptr<IEntity>& first, std::unique_ptr<Operator>&& op = std::make_unique<AddFunctor>(), 
        const std::shared_ptr<IEntity>& second = std::make_shared<Variable>(0));

    double Extract() const override;

};
