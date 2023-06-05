#include "pch.hpp"
#include "operator.hpp"

double AddFunctor::operator()(double a, double b) const {
	if (std::isnan(a) || std::isnan(b))
		return NAN;

	return a + b;
}

double SubtractFunctor::operator()(double a, double b) const {
	if (std::isnan(a) || std::isnan(b))
		return NAN;

	return a - b;
}

double MultiplyFunctor::operator()(double a, double b) const {
	if (std::isnan(a) || std::isnan(b))
		return NAN;
	
	return a * b;
}

double DivideFunctor::operator()(double a, double b) const {
	if (std::isnan(a) || std::isnan(b))
		return NAN;
	
	return a / b;
}

std::unique_ptr<Operator> GetOperatorFromString(const std::string& op) {
	if (op == "+") {
		return std::make_unique<AddFunctor>();
	}
	else if (op == "-") {
		return std::make_unique<SubtractFunctor>();
	}
	else if (op == "*") {
		return std::make_unique<MultiplyFunctor>();
	}
	else if (op == "/") {
		return std::make_unique<DivideFunctor>();
	}

	return std::unique_ptr<Operator>();
}
