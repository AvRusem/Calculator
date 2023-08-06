#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <tuple>

#include "calculator.hpp"

namespace {
double RoundToTwoDecimalPlaces(double value) {
	double rounded = std::round(value * 100.0) / 100.0;
	return rounded;
}

bool IsStringDouble(const std::string& str) {
	try {
		size_t pos = 0;
		std::ignore = std::stod(std::string(str), &pos);
		return (pos == str.length());
	}
	catch (const std::invalid_argument&) {
		return false;
	}
	catch (const std::out_of_range&) {
		return false;
	}
}

} // namespace

using namespace calculator;

std::shared_ptr<Entity> Calculator::GetEntity(const std::string& identifier) const {
	if (IsVariableExist(identifier)) {
		return variables_.at(std::string(identifier));
	}
	else {
		return functions_.at(std::string(identifier));
	}
}

double Calculator::GetValue(const std::string& identifier) const {
	if (IsVariableExist(identifier)) {
		return variables_.at(std::string(identifier))->Extract();
	}
	else {
		return functions_.at(std::string(identifier))->Extract();
	}
}

bool Calculator::IsVariableExist(const std::string& identifier) const noexcept {
	return variables_.count(std::string(identifier)) > 0;
}

bool Calculator::IsFunctionExist(const std::string& identifier) const noexcept {
	return functions_.count(std::string(identifier)) > 0;
}

bool Calculator::IsExist(const std::string& identifier) const noexcept {
	return IsVariableExist(identifier) || IsFunctionExist(identifier);
}

std::unique_ptr<Result> Calculator::DeclareVariable(const std::string& identifier) {
	if (IsExist(identifier)) {
		return std::make_unique<Result>(Errors::kIdentifierTaken);
	}

	variables_[std::string(identifier)] = std::make_shared<Variable>(NAN);
	return std::make_unique<Result>();
}

std::unique_ptr<Result> Calculator::SetVariable(const std::string& identifier1, const std::string& identifier2) {
	if (IsFunctionExist(identifier1)) {
		return std::make_unique<Result>(Errors::kIdentifierTaken);
	}

	double value;
	if (!IsStringDouble(identifier2)) {
		if (!IsExist(identifier2)) {
			return std::make_unique<Result>(Errors::kIdentifierNotExist);
		}
		value = GetValue(identifier2);
	}
	else {
		value = std::stod(std::string(identifier2.begin(), identifier2.end()));
	}

	if (!IsVariableExist(identifier1)) {
		variables_[std::string(identifier1)] = std::make_shared<Variable>(NAN);
	}
	*(variables_[std::string(identifier1)]) = value;
	return std::make_unique<Result>();
}

std::unique_ptr<calculator::Result> Calculator::DeclareFunction(const std::string& identifier, const std::string& identifier1,
	std::unique_ptr<Operator> bin_operator, const std::string& identifier2) {
	if (IsExist(identifier)) {
		return std::make_unique<Result>(Errors::kIdentifierTaken);
	}

	if (!IsExist(identifier1)) {
		return std::make_unique<Result>(Errors::kIdentifierNotExist);
	}

	if (identifier2.empty()) {
		functions_[std::string(identifier)] = std::make_shared<Function>(GetEntity(identifier1));
	}
	else {
		if (!bin_operator) {
			return std::make_unique<Result>(Errors::kWrongOperator);
		}

		if (!IsExist(identifier2)) {
			return std::make_unique<Result>(Errors::kIdentifierNotExist);
		}

		functions_[std::string(identifier)] = std::make_shared<Function>(GetEntity(identifier1), std::move(bin_operator), GetEntity(identifier2));
	}

	return std::make_unique<Result>();
}

std::unique_ptr<Result> Calculator::GetValueById(const std::string& identifier) {
	if (!IsExist(identifier)) {
		return std::make_unique<Result>(Errors::kIdentifierNotExist);
	}

	return std::make_unique<Result>(RoundToTwoDecimalPlaces(GetEntity(identifier)->Extract()));
}

std::unique_ptr<Result> Calculator::GetVariablesValues() const {
	std::unique_ptr<Result> result = std::make_unique<Result>(variables_.size());
	for (const auto& el : variables_) {
		std::get<ReturnPairType>(result->return_value).push_back({ el.first, RoundToTwoDecimalPlaces(el.second->Extract()) });
	}

	return result;
}

std::unique_ptr<Result> Calculator::GetFunctionsValues() const {
	std::unique_ptr<Result> result = std::make_unique<Result>(functions_.size());
	for (const auto& el : functions_) {
		std::get<ReturnPairType>(result->return_value).push_back({ el.first, RoundToTwoDecimalPlaces(el.second->Extract()) });
	}

	return result;
}
