#include "pch.hpp"
#include "calculator.hpp"

using namespace std;

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	Calculator calculator;
	calculator.Start();

	return 0;
}
