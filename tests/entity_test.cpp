#include <gtest/gtest.h>
#include "variable.hpp"
#include "function.hpp"

TEST(VariableTest, Test) {
	Variable var(10);
	EXPECT_EQ(10, var.Extract());

	var = 20;
	EXPECT_EQ(20, var.Extract());

	var = NAN;
	EXPECT_TRUE(std::isnan(var.Extract()));
}

TEST(FunctionTest, Test) {
	std::shared_ptr<Variable> var1(new Variable(10));
	std::shared_ptr<Variable> var2(new Variable(20));

	Function f(var1);
	EXPECT_EQ(10, f.Extract());

	std::unique_ptr<Operator> op(new AddFunctor);
	std::shared_ptr<Function> f2(new Function(var1, std::move(op), var2));
	EXPECT_EQ(30, f2->Extract());

	std::unique_ptr<Operator> opm(new MultiplyFunctor());
	Function f3(f2, std::move(opm), var1);
	EXPECT_EQ(300, f3.Extract());
}
