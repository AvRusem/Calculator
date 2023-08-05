#ifdef RUN_MAIN

#include "calculator.hpp"
#include "console_ui.hpp"

int main(int argc, char** argv) {
	Calculator calculator;
	ConsoleUI ui(calculator);
	
	ui.HandleUserInput();

	return 0;
}

#endif // RUN_MAIN
