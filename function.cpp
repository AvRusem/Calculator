#include "pch.hpp"
#include "function.hpp"

Function::Function(const std::shared_ptr<Entity>& first, std::unique_ptr<Operator>&& op,
	const std::shared_ptr<Entity>& second) : Entity((*op)(first->Extract(), second->Extract())),
	first_(first), operator_(std::move(op)), second_(second), is_actual_(true) {
	first->AddDependent(this);
	second->AddDependent(this);
}

double Function::Extract() noexcept {
	if (!is_actual_) {
		SetValue((*operator_)(first_->Extract(), second_->Extract()));
		is_actual_ = true;
	}

	return Entity::Extract();
}

bool Function::IsActual() const noexcept {
	return is_actual_;
}

void Function::MakeNonActual() noexcept {
	is_actual_ = false;

	for (auto el : GetDependent()) {
		if (static_cast<Function*>(el)->IsActual()) {
			static_cast<Function*>(el)->MakeNonActual();
		}
	}
}
