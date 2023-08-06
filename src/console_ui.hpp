/*
* Class that handles input to stdin
*/

#pragma once

#include <regex>
#include <vector>
#include <string>

#include "calculator.hpp"

class ConsoleUI {
private:
	const std::regex var_regex_; // var <identifier>
	const std::regex let_regex_; // let <identifier1>=<float> or let <identifier1>=<identifier2>
	const std::regex fn_regex_; // fn <identifier1>=<identifier2> or fn <identifier1>=<identifier2><operation><identifier3>
	const std::regex print_regex_; // print <identifier>
	const std::regex printvars_regex_; // printvars
	const std::regex printfns_regex_; // printfns

	const std::string kWrongInput;
	const std::string kErrorIdentifierTaken;
	const std::string kErrorIdentifierNotExist;
	const std::string kErrorWrongOperator;
	const std::string kUnknownError;

	const std::streamsize kPrecision;

	Calculator& calculator_;

	std::string CreateOutput(std::unique_ptr<calculator::Result> result) const;

public:
	explicit ConsoleUI(Calculator& calculator);

	std::string HandleRequest(const std::string& request) const;
	void HandleUserInput() const;

};
