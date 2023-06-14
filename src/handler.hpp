/*
* Class that handles input to stdin
*/

#pragma once

#include <regex>
#include <vector>

namespace calculator {
	enum Commands;
} // namespace calculator


class Handler {
private:
	std::regex var_regex_; // var <identifier>
	std::regex let_regex_; // let <identifier1>=<float> or let <identifier1>=<identifier2>
	std::regex fn_regex_; // fn <identifier1>=<identifier2> or fn <identifier1>=<identifier2><operation><identifier3>
	std::regex print_regex_; // print <identifier>
	std::regex printvars_regex_; // printvars
	std::regex printfns_regex_; // printfns

public:
	Handler();

	std::pair<calculator::Commands, std::vector<std::string>> Handle(const std::string& request) const;
	std::pair<calculator::Commands, std::vector<std::string>> GetInput() const;

};
