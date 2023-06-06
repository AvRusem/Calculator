#include <gtest/gtest.h>
#include "calculator.hpp"

TEST(CalculatorTest, Variablse) {
	Calculator calculator;

	std::string response = "var x";
	EXPECT_EQ("", calculator.Execute(response));

	response = "print x";
	EXPECT_EQ("nan\n", calculator.Execute(response));

	response = "let x=42";
	EXPECT_EQ("", calculator.Execute(response));

	response = "print x";
	EXPECT_EQ("42.00\n", calculator.Execute(response));

	response = "let x=1.234";
	EXPECT_EQ("", calculator.Execute(response));

	response = "print x";
	EXPECT_EQ("1.23\n", calculator.Execute(response));

	response = "let y=x";
	EXPECT_EQ("", calculator.Execute(response));

	response = "let x=99";
	EXPECT_EQ("", calculator.Execute(response));

	response = "printvars";
	EXPECT_EQ("x:99.00\ny:1.23\n", calculator.Execute(response));
}

TEST(CalculatorTest, Functions) {
	Calculator calculator;

	std::string response = "var x";
	EXPECT_EQ("", calculator.Execute(response));

	response = "var y";
	EXPECT_EQ("", calculator.Execute(response));

	response = "fn XPlusY=x+y";
	EXPECT_EQ("", calculator.Execute(response));

	response = "print XPlusY";
	EXPECT_EQ("nan\n", calculator.Execute(response));

	response = "let x=3";
	EXPECT_EQ("", calculator.Execute(response));

	response = "let y=4";
	EXPECT_EQ("", calculator.Execute(response));

	response = "print XPlusY";
	EXPECT_EQ("7.00\n", calculator.Execute(response));

	response = "let x=10";
	EXPECT_EQ("", calculator.Execute(response));

	response = "print XPlusY";
	EXPECT_EQ("14.00\n", calculator.Execute(response));

	response = "let z=3.5";
	EXPECT_EQ("", calculator.Execute(response));

	response = "fn XPlusYDivZ=XPlusY/z";
	EXPECT_EQ("", calculator.Execute(response));

	response = "printfns";
	EXPECT_EQ("XPlusY:14.00\nXPlusYDivZ:4.00\n", calculator.Execute(response));
}

TEST(CalculatorTest, FnAndLetDiff) {
	Calculator calculator;

	std::string response = "let v=42";
	EXPECT_EQ("", calculator.Execute(response));

	response = "let variable=v";
	EXPECT_EQ("", calculator.Execute(response));

	response = "fn function=v";
	EXPECT_EQ("", calculator.Execute(response));

	response = "let v=43";
	EXPECT_EQ("", calculator.Execute(response));

	response = "print variable";
	EXPECT_EQ("42.00\n", calculator.Execute(response));

	response = "print function";
	EXPECT_EQ("43.00\n", calculator.Execute(response));
}
