#include <iostream>

#include "handler.hpp"
#include "calculator.hpp"

// The identifier is a non-empty string that can contain letters of the English
// alphabet, numbers, and the underscore character. An identifier cannot start
// with a number. Identifiers are used as variable and function names.
Handler::Handler() :
	// var <identifier>
	var_regex_(R"(^var\s+([a-zA-Z_][a-zA-Z0-9_]*)$)"),

	// let <identifier1>=<float> or let <identifier1>=<identifier2>
	let_regex_(R"(^let\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*((\d+(\.\d+)?)|([a-zA-Z_][a-zA-Z0-9_]*))$)"),
	
	// fn <identifier1>=<identifier2> or fn <identifier1>=<identifier2><operation><identifier3>
	fn_regex_(R"(^fn\s+([a-zA-Z_][a-zA-Z0-9_]*)\s*=\s*([a-zA-Z_][a-zA-Z0-9_]*)(?:([+\-*/])\s*([a-zA-Z_][a-zA-Z0-9_]*))?$)"),
	
	// print <identifier>
	print_regex_(R"(^print\s+([a-zA-Z_][a-zA-Z0-9_]*)$)"),
	
	// printvars
	printvars_regex_(R"(^printvars$)"),
	
	// printfns
	printfns_regex_(R"(^printfns$)") {}

std::pair<calculator::Commands, std::vector<std::string>> Handler::Handle(const std::string& request) const {
	std::smatch match;
	std::pair<calculator::Commands, std::vector<std::string>> result(calculator::Commands::kError, std::vector<std::string>(match.begin(), match.end()));

	if (std::regex_match(request, match, var_regex_)) {
		result.first = calculator::Commands::kVar;
	}
	else if (std::regex_match(request, match, let_regex_)) {
		result.first = calculator::Commands::kLet;
	}
	else if (std::regex_match(request, match, fn_regex_)) {
		result.first = calculator::Commands::kFn;
	}
	else if (std::regex_match(request, match, print_regex_)) {
		result.first = calculator::Commands::kPrint;
	}
	else if (std::regex_match(request, match, printvars_regex_)) {
		result.first = calculator::Commands::kPrintvars;
	}
	else if (std::regex_match(request, match, printfns_regex_)) {
		result.first = calculator::Commands::kPrintfns;
	}

	result.second = std::vector<std::string>(match.begin(), match.end());
	return result;
}

std::pair<calculator::Commands, std::vector<std::string>> Handler::GetInput() const {
	std::string request;
	std::getline(std::cin, request);

	return Handle(request);
}
