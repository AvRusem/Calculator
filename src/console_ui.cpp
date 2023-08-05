#include <iostream>
#include <variant>

#include "console_ui.hpp"
#include "calculator.hpp"

// The identifier is a non-empty string that can contain letters of the English
// alphabet, numbers, and the underscore character. An identifier cannot start
// with a number. Identifiers are used as variable and function names.
ConsoleUI::ConsoleUI(Calculator& calculator) :
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
	printfns_regex_(R"(^printfns$)"),

	kWrongInput("ConsoleUI Error: wrong input"),
	kErrorIdentifierTaken("This identifier is already in use"),
	kErrorIdentifierNotExist("This identifier is not exist"),
	kErrorWrongOperator("Wrong operator"),
	kUnknownError("Unknown error"),
	calculator_(calculator) {}

std::string ConsoleUI::CreateOutput(std::unique_ptr<calculator::Result> result) const {
	if (!result) {
		return kWrongInput + '\n';
	}

	std::string result_string;
	if (result->status == calculator::Status::kOk) {
		if (std::holds_alternative<double>(result->return_value)) {
			result_string = std::to_string(std::get<double>(result->return_value)) + '\n';
		}
		else if (std::holds_alternative<calculator::ReturnPairType>(result->return_value)) {
			for (const auto& el : std::get<calculator::ReturnPairType>(result->return_value)) {
				result_string += el.first + ':' + std::to_string(el.second) + '\n';
			}
		}
	}
	else {
		result_string += "Error: ";

		switch (std::get<calculator::Errors>(result->return_value)) {
		case calculator::Errors::kIdentifierTaken:
			result_string += kErrorIdentifierTaken;
			break;
		case calculator::Errors::kIdentifierNotExist:
			result_string += kErrorIdentifierNotExist;
			break;
		case calculator::Errors::kWrongOperator:
			result_string += kErrorWrongOperator;
			break;
		default:
			result_string += kUnknownError;
		}

		result_string += '\n';
	}

	return result_string;
}

std::string ConsoleUI::HandleRequest(const std::string& request) const {
	std::smatch match;
	std::unique_ptr<calculator::Result> result(nullptr);

	if (std::regex_match(request, match, var_regex_)) {
		result = calculator_.DeclareVariable(match[1]);
	}
	else if (std::regex_match(request, match, let_regex_)) {
		result = calculator_.SetVariable(match[1], match[2]);
	}
	else if (std::regex_match(request, match, fn_regex_)) {
		if (match.size() > 3)
			result = calculator_.DeclareFunction(match[1], match[2], GetOperatorFromString(match[3]), match[4]);
		else
			result = calculator_.DeclareFunction(match[1], match[2]);
	}
	else if (std::regex_match(request, match, print_regex_)) {
		result = calculator_.GetValueById(match[1]);
	}
	else if (std::regex_match(request, match, printvars_regex_)) {
		result = calculator_.GetVariablesValues();
	}
	else if (std::regex_match(request, match, printfns_regex_)) {
		result = calculator_.GetFunctionsValues();
	}

	return CreateOutput(std::move(result));
}

void ConsoleUI::HandleUserInput() const {
	std::string input;
	while (std::getline(std::cin, input)) {
		if (input.empty())
			continue;

		std::cout << HandleRequest(input);
	}
}
