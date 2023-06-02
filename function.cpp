#include "pch.h"
#include "function.h"

Function::Function(const std::shared_ptr<IEntity>& first, std::unique_ptr<Operator>&& op,
	const std::shared_ptr<IEntity>& second) : first_(first), operator_(std::move(op)), second_(second) {}

double Function::Extract() const {
	double first = first_->Extract();
	double second = second_->Extract();

	return (*operator_)(first, second);
}
