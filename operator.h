/*
* Functional objects (functors) are used to implement operators.
* To ensure polymorphism, there is a base class from which operators are inherited.
*/

#pragma once

#include <memory>

// Base class
class Operator {
public:
	virtual double operator()(double, double) const = 0;

};

class AddFunctor final : public Operator {
public:
	double operator()(double, double) const override;

};

class SubtractFunctor final : public Operator {
public:
	double operator()(double, double) const override;

};

class MultiplyFunctor final : public Operator {
public:
	double operator()(double, double) const override;

};

class DivideFunctor final : public Operator {
public:
	double operator()(double, double) const override;

};

std::unique_ptr<Operator> GetOperatorFromString(const std::string& op);
