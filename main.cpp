#include "pch.h"
#include "calculator.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();

	Calculator calculator;
	calculator.Start();

	return 0;
}
