#ifdef RUN_MAIN_TEST

#include <gtest/gtest.h>
#include <iostream>

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	std::cin.get();

	return 0;
}

#endif // RUN_MAIN_TEST
