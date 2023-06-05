#include "pch.h"
#include "variable.h"
#include "function.h"

Variable::Variable() : Entity(NAN) {}
Variable::Variable(double value) : Entity(value) {}

void Variable::MakeNonActual() noexcept {
	for (auto el : GetDependent()) {
		if (static_cast<Function*>(el)->IsActual()) {
			static_cast<Function*>(el)->MakeNonActual();
		}
	}
}

Variable& Variable::operator=(double value) {
	SetValue(value);
	MakeNonActual();

	return *this;
}
