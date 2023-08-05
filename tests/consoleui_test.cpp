#include <gtest/gtest.h>
#include "console_ui.hpp"
#include "calculator.hpp"

#include <string>

TEST(HandlerTest, Var) {
	Calculator calculator;
	ConsoleUI ui(calculator);

	std::string input = "var x";
	std::string result = ui.HandleRequest(input);
	EXPECT_EQ(result, "");
}

TEST(HandlerTest, Let) {
	Calculator calculator;
	ConsoleUI ui(calculator);

	std::string input = "let x=10";
	std::string result = ui.HandleRequest(input);
	EXPECT_EQ(result, "");
}

TEST(HandlerTest, Fn) {
	Calculator calculator;
	ConsoleUI ui(calculator);

	ui.HandleRequest("let x = 10");

	std::string input = "fn y=x";
	std::string result = ui.HandleRequest(input);
	EXPECT_EQ(result, "");
}

TEST(HandlerTest, Print) {
	Calculator calculator;
	ConsoleUI ui(calculator);

	ui.HandleRequest("let x = 10");
	ui.HandleRequest("let y = x");
	ui.HandleRequest("fn plus = x+y");
	ui.HandleRequest("let x = 15");

	std::string input = "print x";
	std::string result = ui.HandleRequest(input);
	EXPECT_EQ(std::stoi(result), 15);

	input = "print y";
	result = ui.HandleRequest(input);
	EXPECT_EQ(std::stoi(result), 10);

	input = "print plus";
	result = ui.HandleRequest(input);
	EXPECT_EQ(std::stoi(result), 25);

	input = "printvars";
	result = ui.HandleRequest(input);
	int x = std::stoi(result.substr(result.find_first_of(':') + 1, 2));
	int y = std::stoi(result.substr(result.find_last_of(':') + 1, 2));
	EXPECT_EQ(x, 15);
	EXPECT_EQ(y, 10);

	input = "printfns";
	result = ui.HandleRequest(input);
	int plus = std::stoi(result.substr(result.find_first_of(':') + 1, 2));
	EXPECT_EQ(plus, 25);
}

TEST(HandlerTest, Errors) {
	Calculator calculator;
	ConsoleUI ui(calculator);

	std::string input = "var x=10";
	std::string result = ui.HandleRequest(input);
	EXPECT_EQ(result, "ConsoleUI Error: wrong input\n");

	input = "var 1x";
	result = ui.HandleRequest(input);
	EXPECT_EQ(result, "ConsoleUI Error: wrong input\n");

	input = "let 10=12";
	result = ui.HandleRequest(input);
	EXPECT_EQ(result, "ConsoleUI Error: wrong input\n");

	input = "fn x=y^z";
	result = ui.HandleRequest(input);
	EXPECT_EQ(result, "ConsoleUI Error: wrong input\n");

	input = "fn x=y+36";
	result = ui.HandleRequest(input);
	EXPECT_EQ(result, "ConsoleUI Error: wrong input\n");
}
