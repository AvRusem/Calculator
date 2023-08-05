/*
* The class that is responsible for the operation of the calculator
*/

#pragma once

#include <map>
#include <string>
#include <memory>
#include <vector>
#include <variant>

#include "operator.hpp"
#include "variable.hpp"
#include "function.hpp"

namespace calculator {
	enum class Status {
		kOk,
		kError
	};

	enum class Errors {
		kIdentifierTaken,
		kIdentifierNotExist,
		kWrongOperator
	};

	using ReturnPairType = std::vector<std::pair<std::string, double>>;
	using ReturnType = std::variant<std::monostate, Errors, ReturnPairType, double>;

	struct Result {
		Status status;
		ReturnType return_value;

		Result() : status(Status::kOk), return_value{} {}
		explicit Result(double value) : status(Status::kOk), return_value(value) {}
		explicit Result(const Errors& error) : status(Status::kError), return_value(error) {}
		explicit Result(size_t size) : status(Status::kOk), return_value(ReturnPairType(0)) {
			std::get<ReturnPairType>(return_value).reserve(size);
		}
	};

} // namespace calculator

class Calculator {
private:
	std::map<std::string, std::shared_ptr<Variable>> variables_;
	std::map<std::string, std::shared_ptr<Function>> functions_;

	double GetValue(const std::string& identifier) const;
	std::shared_ptr<Entity> GetEntity(const std::string& identifier) const;

	bool IsVariableExist(const std::string& identifier) const noexcept;
	bool IsFunctionExist(const std::string& identifier) const noexcept;
	bool IsExist(const std::string& identifier) const noexcept;

public:
	Calculator() = default;

	std::unique_ptr<calculator::Result> DeclareVariable(const std::string& identifier);
	std::unique_ptr<calculator::Result> SetVariable(const std::string& identifier1, const std::string& identifier2);
	std::unique_ptr<calculator::Result> DeclareFunction(const std::string& identifier, const std::string& identifier1,
		std::unique_ptr<Operator> bin_operator = nullptr, const std::string& identifier2 = "");
	std::unique_ptr<calculator::Result> GetValueById(const std::string& identifier);
	std::unique_ptr<calculator::Result> GetVariablesValues() const;
	std::unique_ptr<calculator::Result> GetFunctionsValues() const;

};
