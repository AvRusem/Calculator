/*
* The class that is responsible for the operation of the calculator
*/

#pragma once

#include <map>
#include <string>
#include <memory>

#include "operator.hpp"
#include "variable.hpp"
#include "function.hpp"
#include "handler.hpp"

namespace calculator {
	enum class Commands {
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

	double GetValue(std::string identidier) const;
	std::shared_ptr<Entity> GetEntity(std::string identidier) const;

	bool IsVariableExist(const std::string& identifier) const noexcept;
	bool IsFunctionExist(const std::string& identifier) const noexcept;
	bool IsExist(const std::string& identifier) const noexcept;

	std::string ExecuteCommand(const calculator::Commands command, const std::vector<std::string>& match);
	std::string ExecuteVar(const std::vector<std::string>& match);
	std::string ExecuteLet(const std::vector<std::string>& match);
	std::string ExecuteFn(const std::vector<std::string>& match);
	std::string ExecutePrint(const std::vector<std::string>& match);
	std::string ExecutePrintvars() const;
	std::string ExecutePrintfns() const;
	std::string ExecuteError() const;

public:
	Calculator() = default;

	void Calculator::Start();
	std::string Execute(const std::string& response);

};
