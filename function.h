/*
* Class that represents function
*/

#pragma once

#include "entity.h"
#include "operator.h"
#include "variable.h"

#include <memory>

class Function final :
    public Entity {
private:
    std::shared_ptr<Entity> first_;
    std::shared_ptr<Entity> second_;
    std::unique_ptr<Operator> operator_;
    bool is_actual_;

public:
    Function() = default;
    Function(const std::shared_ptr<Entity>& first, std::unique_ptr<Operator>&& op = std::make_unique<AddFunctor>(), 
        const std::shared_ptr<Entity>& second = std::make_shared<Variable>(0));

    double Extract() noexcept override;
    bool IsActual() const noexcept;
    void MakeNonActual() noexcept;

};
