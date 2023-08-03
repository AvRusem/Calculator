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

std::string DoubleToString(double value) {
	std::ostringstream oss;
	oss << std::fixed << std::setprecision(2) << value;
	return oss.str();
}

bool IsStringDouble(const std::string& str) {
	try {
		size_t pos = 0;
		std::ignore = std::stod(str, &pos);
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

std::shared_ptr<Entity> Calculator::GetEntity(std::string identidier) const {
	if (IsVariableExist(identidier)) {
		return variables_.at(identidier);
	}
	else {
		return functions_.at(identidier);
	}
}

double Calculator::GetValue(std::string identidier) const {
	if (IsVariableExist(identidier)) {
		return variables_.at(identidier)->Extract();
	}
	else {
		return functions_.at(identidier)->Extract();
	}
}

bool Calculator::IsVariableExist(const std::string& identifier) const noexcept {
	return variables_.count(identifier) > 0;
}

bool Calculator::IsFunctionExist(const std::string& identifier) const noexcept {
	return functions_.count(identifier) > 0;
}

bool Calculator::IsExist(const std::string& identifier) const noexcept {
	return IsVariableExist(identifier) || IsFunctionExist(identifier);
}

std::string Calculator::ExecuteCommand(const calculator::Commands command, const std::vector<std::string>& match) {
	switch (command) {
	case calculator::Commands::kVar:
		return ExecuteVar(match);

	case calculator::Commands::kLet:
		return ExecuteLet(match);

	case calculator::Commands::kFn:
		return ExecuteFn(match);

	case calculator::Commands::kPrint:
		return ExecutePrint(match);

	case calculator::Commands::kPrintvars:
		return ExecutePrintvars();

	case calculator::Commands::kPrintfns:
		return ExecutePrintfns();

	case calculator::Commands::kError:
	default:
		return ExecuteError();
	}
}

std::string Calculator::ExecuteVar(const std::vector<std::string>& match) {
	std::string identifier = match[1];
	const std::string kErrorMessage("Error: This identifier is already in use\n");

	if (IsExist(identifier)) {
		return kErrorMessage;
	}

	variables_[identifier] = std::make_shared<Variable>(NAN);
	return "";
}

std::string Calculator::ExecuteLet(const std::vector<std::string>& match) {
	std::string identifier1 = match[1];
	const std::string kErrorMessage("Error: This identifier is already used by the function\n");

	if (IsFunctionExist(identifier1)) {
		return kErrorMessage;
	}

	std::string identidier2 = match[2];
	double value;
	if (!IsStringDouble(identidier2)) {
		const std::string kErrorId2Message("Error: Variable or Function named \"" + identidier2 + "\" does not exist\n");
		if (!IsExist(identidier2)) {
			return kErrorId2Message;
		}
		value = GetValue(identidier2);
	}
	else {
		value = std::stod(identidier2);
	}

	if (!IsVariableExist(identifier1)) {
		variables_[identifier1] = std::make_shared<Variable>(NAN);
	}
	*(variables_[identifier1]) = value;
	return "";
}

std::string Calculator::ExecuteFn(const std::vector<std::string>& match) {
	std::string identifier1 = match[1];
	const std::string kErrorMessage("Error: This identifier is already in use\n");

	if (IsExist(identifier1)) {
		return kErrorMessage;
	}

	std::string identifier2 = match[2];
	const std::string kErrorId2Message("Error: Variable or Function named \"" + identifier2 + "\" does not exist\n");

	if (!IsExist(identifier2)) {
		return kErrorId2Message;
	}

	if (match[3].empty()) {
		functions_[identifier1] = std::make_shared<Function>(GetEntity(identifier2));
	}
	else {
		std::string op_str = match[3];
		std::string identifier3 = match[4];

		const std::string kErrorOperatorMessage("Error: Wrong operator: " + op_str + '\n');
		std::unique_ptr<Operator> op(GetOperatorFromString(op_str));
		if (!op) {
			return kErrorOperatorMessage;
		}

		const std::string kErrorId3Message("Error: Variable or Function named \"" + identifier3 + "\" does not exist\n");
		if (!IsExist(identifier3)) {
			return kErrorId3Message;
		}

		functions_[identifier1] = std::make_shared<Function>(GetEntity(identifier2), std::move(op), GetEntity(identifier3));
	}

	return "";
}

std::string Calculator::ExecutePrint(const std::vector<std::string>& match) {
	std::string identifier = match[1];
	const std::string kErrorMessage("Error: Variable or Function named \"" + identifier + "\" does not exist\n");
	if (!IsExist(identifier)) {
		return kErrorMessage;
	}

	const std::string kResponse(DoubleToString(RoundToTwoDecimalPlaces(GetEntity(identifier)->Extract())) + '\n');
	return kResponse;
}

std::string Calculator::ExecutePrintvars() const {
	std::string response = "";
	for (const auto& el : variables_) {
		response += el.first + ':' + DoubleToString(RoundToTwoDecimalPlaces(el.second->Extract())) + '\n';
	}

	return response;
}

std::string Calculator::ExecutePrintfns() const {
	std::string response = "";
	for (const auto& el : functions_) {
		response += el.first + ':' + DoubleToString(RoundToTwoDecimalPlaces(el.second->Extract())) + '\n';
	}

	return response;
}

std::string Calculator::ExecuteError() const {
	const std::string kErrorMessage("Error: Wrong request\n");
	return kErrorMessage;
}

void Calculator::Start() {
	while (!feof(stdin)) {
		auto result = handler_.GetInput();
		std::cout << ExecuteCommand(result.first, result.second);
	}
}

std::string Calculator::Execute(const std::string& response) {
	auto result = handler_.Handle(response);
	return ExecuteCommand(result.first, result.second);
}
