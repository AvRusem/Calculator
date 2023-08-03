#include "function.hpp"

Function::Function(const std::shared_ptr<Entity>& first, std::unique_ptr<Operator>&& op,
	const std::shared_ptr<Entity>& second) : Entity((*op)(first->Extract(), second->Extract())),
	first_(first), operator_(std::move(op)), second_(second) {
	first->AddDependent(this);
	second->AddDependent(this);
}

double Function::Extract() {
	if (!IsActual()) {
		SetValue((*operator_)(first_->Extract(), second_->Extract()));
		MakeActual();
	}

	return Entity::Extract();
}
