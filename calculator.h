/*
* The class that is responsible for the operation of the calculator
*/

#pragma once

#include <map>
#include <string>
#include <memory>

#include "operator.h"
#include "variable.h"
#include "function.h"
#include "handler.h"

namespace calculator {
	enum Commands {
		kVar,
		kLet,
		kFn,
		kPrint,
		kPrintvars,
		kPrintfns,
		kError
	};

} // namespace calculator

class Calculator {
private:
	Handler handler_;
	std::map<std::string, std::shared_ptr<Variable>> variables_;
	std::map<std::string, std::shared_ptr<Function>> functions_;

	double GetValue(std::string identidier) const noexcept;
	std::shared_ptr<Entity> GetEntity(std::string identidier) noexcept;

	bool IsVariableExist(const std::string& identifier) const noexcept;
	bool IsFunctionExist(const std::string& identifier) const noexcept;
	bool IsExist(const std::string& identifier) const noexcept;
	bool IsStringDouble(const std::string& str) const;

	std::string ExecuteCommand(const calculator::Commands command, const std::vector<std::string>& match)  noexcept;
	std::string ExecuteVar(const std::vector<std::string>& match)  noexcept;
	std::string ExecuteLet(const std::vector<std::string>& match)  noexcept;
	std::string ExecuteFn(const std::vector<std::string>& match)  noexcept;
	std::string ExecutePrint(const std::vector<std::string>& match) noexcept;
	std::string ExecutePrintvars() const noexcept;
	std::string ExecutePrintfns() const noexcept;
	std::string ExecuteError() const noexcept;

public:
	Calculator() = default;

	void Calculator::Start() noexcept;
	std::string Execute(const std::string& response) noexcept;

};
