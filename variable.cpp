#include "pch.h"
#include "variable.h"

Variable::Variable() : value_(NAN) {}
Variable::Variable(double value) : value_(value) {}

double Variable::Extract() const {
	return value_;
}

Variable& Variable::operator=(double value) {
	value_ = value;

	return *this;
}
