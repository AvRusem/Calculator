#include <gtest/gtest.h>
#include "calculator.hpp"

using namespace calculator;

TEST(CalculatorTest, Variablse) {
	Calculator calculator;

	auto result = calculator.DeclareVariable("x");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.GetValueById("x");
	EXPECT_EQ(Status::kOk, result->status);
	EXPECT_TRUE(std::isnan(std::get<double>(result->return_value)));
	result.reset();

	result = calculator.SetVariable("x", "42");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));

	result = calculator.GetValueById("x");
	EXPECT_EQ(Status::kOk, result->status);
	EXPECT_EQ(42.0, std::get<double>(result->return_value));
	result.reset();

	result = calculator.SetVariable("x", "1.234");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.GetValueById("x");
	EXPECT_EQ(Status::kOk, result->status);
	EXPECT_EQ(1.23, std::get<double>(result->return_value));
	result.reset();

	result = calculator.SetVariable("y", "x");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.SetVariable("x", "99");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.GetVariablesValues();
	EXPECT_EQ(Status::kOk, result->status);
	EXPECT_EQ("x", std::get<ReturnPairType>(result->return_value)[0].first);
	EXPECT_EQ(99, std::get<ReturnPairType>(result->return_value)[0].second);
	EXPECT_EQ("y", std::get<ReturnPairType>(result->return_value)[1].first);
	EXPECT_EQ(1.23, std::get<ReturnPairType>(result->return_value)[1].second);
	result.reset();
}

TEST(CalculatorTest, Functions) {
	Calculator calculator;

	auto result = calculator.DeclareVariable("x");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.DeclareVariable("y");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.DeclareFunction("XPlusY", "x", GetOperatorFromString("+"), "y");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.GetValueById("XPlusY");
	EXPECT_EQ(Status::kOk, result->status);
	EXPECT_TRUE(std::isnan(std::get<double>(result->return_value)));
	result.reset();

	result = calculator.SetVariable("x", "3");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.SetVariable("y", "4");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.GetValueById("XPlusY");
	EXPECT_EQ(Status::kOk, result->status);
	EXPECT_EQ(7.0, std::get<double>(result->return_value));
	result.reset();

	result = calculator.SetVariable("x", "10");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.GetValueById("XPlusY");
	EXPECT_EQ(Status::kOk, result->status);
	EXPECT_EQ(14.0, std::get<double>(result->return_value));
	result.reset();

	result = calculator.SetVariable("z", "3.5");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.DeclareFunction("XPlusYDivZ", "XPlusY", GetOperatorFromString("/"), "z");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.GetFunctionsValues();
	EXPECT_EQ(Status::kOk, result->status);
	EXPECT_EQ("XPlusY", std::get<ReturnPairType>(result->return_value)[0].first);
	EXPECT_EQ(14.0, std::get<ReturnPairType>(result->return_value)[0].second);
	EXPECT_EQ("XPlusYDivZ", std::get<ReturnPairType>(result->return_value)[1].first);
	EXPECT_EQ(4.0, std::get<ReturnPairType>(result->return_value)[1].second);
	result.reset();
}

TEST(CalculatorTest, FnAndLetDiff) {
	Calculator calculator;

	auto result = calculator.SetVariable("v", "42");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.SetVariable("variable", "v");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.DeclareFunction("function", "v");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.SetVariable("v", "43");
	EXPECT_EQ(Status::kOk, result->status);
	ASSERT_TRUE(std::holds_alternative<std::monostate>(result->return_value));
	result.reset();

	result = calculator.GetValueById("variable");
	EXPECT_EQ(Status::kOk, result->status);
	EXPECT_EQ(42.0, std::get<double>(result->return_value));
	result.reset();

	result = calculator.GetValueById("function");
	EXPECT_EQ(Status::kOk, result->status);
	EXPECT_EQ(43.0, std::get<double>(result->return_value));
	result.reset();
}
