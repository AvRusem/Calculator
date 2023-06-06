#include <gtest/gtest.h>
#include "handler.hpp"
#include "calculator.hpp"

#include <string>

TEST(HandlerTest, Var) {
	std::string input = "var x";

	Handler handler;
	auto result = handler.Handle(input);

	EXPECT_EQ(calculator::kVar, result.first);
	EXPECT_EQ("x", result.second[1]);
}

TEST(HandlerTest, Let) {
	std::string input = "let x=10";

	Handler handler;
	auto result = handler.Handle(input);

	EXPECT_EQ(calculator::kLet, result.first);
	EXPECT_EQ("x", result.second[1]);
	EXPECT_EQ(10, std::stod(result.second[2]));

	input = "let z=10.12";

	result.swap(handler.Handle(input));

	EXPECT_EQ(calculator::kLet, result.first);
	EXPECT_EQ("z", result.second[1]);
	EXPECT_EQ(10.12, std::stod(result.second[2]));

	input = "let z=abc_1";

	result.swap(handler.Handle(input));

	EXPECT_EQ(calculator::kLet, result.first);
	EXPECT_EQ("z", result.second[1]);
	EXPECT_EQ("abc_1", result.second[2]);
}

TEST(HandlerTest, Fn) {
	std::string input = "fn y=x";

	Handler handler;
	auto result = handler.Handle(input);

	EXPECT_EQ(calculator::kFn, result.first);
	EXPECT_EQ("y", result.second[1]);
	EXPECT_EQ("x", result.second[2]);

	input = "fn x1_=y+z";

	result.swap(handler.Handle(input));

	EXPECT_EQ(calculator::kFn, result.first);
	EXPECT_EQ("x1_", result.second[1]);
	EXPECT_EQ("y", result.second[2]);
	EXPECT_EQ("+", result.second[3]);
	EXPECT_EQ("z", result.second[4]);
}

TEST(HandlerTest, Print) {
	std::string input = "print variable";

	Handler handler;
	auto result = handler.Handle(input);

	EXPECT_EQ(calculator::kPrint, result.first);
	EXPECT_EQ("variable", result.second[1]);

	input = "printvars";
	result.swap(handler.Handle(input));
	EXPECT_EQ(calculator::kPrintvars, result.first);

	input = "printfns";
	result.swap(handler.Handle(input));
	EXPECT_EQ(calculator::kPrintfns, result.first);
}

TEST(HandlerTest, Error) {
	std::string input = "var x=10";
	Handler handler;
	auto result = handler.Handle(input);
	EXPECT_EQ(calculator::kError, result.first);

	input = "var 1x";
	result.swap(handler.Handle(input));
	EXPECT_EQ(calculator::kError, result.first);

	input = "let 10=12";
	result.swap(handler.Handle(input));
	EXPECT_EQ(calculator::kError, result.first);

	input = "fn x=y^z";
	result.swap(handler.Handle(input));
	EXPECT_EQ(calculator::kError, result.first);

	input = "fn x=y+36";
	result.swap(handler.Handle(input));
	EXPECT_EQ(calculator::kError, result.first);
}
