Develop a C++ console program "Calculator" that allows you to declare variables and functions and perform arithmetic operations on them.

# Code Requirements
The solution should use an object-oriented approach and contain appropriate classes and structures that model the entities of the domain. Use suitable STL containers for solving the task.

Having automated tests for the program as a whole or for its classes and functions is welcome. You can use your preferred testing framework or use the standard assert macro.

Use your preferred naming style for classes, variables, methods, and functions.

# Input and Output Format
The input data is read from stdin line by line. The output is displayed on stdout. Each input line contains one of the commands shown below. Each command is executed immediately after it is read.

The program terminates when the end of the input file is reached.

List of commands:

* **var <identifier\>**

Declares a double variable with the name <identifier\>. The <identifier\> must not match any previously declared variable or function names. The value of the variable after its declaration is undefined (you can use the value NAN for this purpose). No output is produced on stdout in case of success. If there is an error, the command is ignored and an error message is displayed on stdout.

* **let <identifier1\>=<floating-point number\>** or **let <identifier1\>=<identifier2\>**

Assigns a numeric value to the variable with the name <identifier1\>, or assigns the current value of the previously declared identifier <identifier2\> to <identifier1\>. If the variable with the name <identifier1\> has not been previously declared, a new variable is declared. No output is produced on stdout in case of success. If there is an error, the command is ignored and an error message is displayed on stdout.

* **fn <identifier1\>=<identifier2\>** or **fn <identifier1\>=<identifier2\><operation\><identifier3\>**

Declares a new function with a previously undeclared name <identifier1\>, whose value will be either the value of the identifier <identifier2\> or the result of applying one of the following binary operations to the values of the previously declared identifiers <identifier2\> and <identifier3\> at the time of function evaluation:

- **\+** Addition. The result is the sum of the values of <identifier2\> and <identifier3\>.
- **\-** Subtraction. The result is the difference between the values of <identifier2\> and <identifier3\>.
- **\*** Multiplication. The result is the product of the values of <identifier2\> and <identifier3\>.
- **/** Division. The result is the quotient of the values of <identifier2\> and <identifier3\>.
- If the value of at least one of the operands is undefined, the result of the operation should be NaN. No output is produced on stdout in case of success. If there is an error, the command is ignored and an error message is displayed on stdout.
* **print <identifier\>**

Outputs the value of the previously declared identifier to stdout. If the identifier is a variable, its value is displayed; if it is a function, its computed value is displayed. The value is displayed with a precision of 2 decimal places. For example, the number 0.33333 should be displayed as 0.33. If the value of the identifier is undefined, nan should be displayed. If there is an error (e.g., trying to print the value of an undeclared identifier), the command is ignored, and an error message is displayed on stdout.

* **printvars**

Outputs the names and values of all previously declared variables, sorted alphabetically, with each name and value displayed on a separate line in the following format: <identifier\>:<value\>. The value of the variable is displayed with a precision of 2 decimal places. If the value of the variable is undefined, nan should be displayed. If no variables have been declared before the execution of the printvars command, nothing should be displayed on stdout.

* **printfns**

Outputs the names and values of all previously declared functions, sorted alphabetically, with each name and value displayed on a separate line in the following format: <identifier\>:<value\>. The value of the function is displayed with a precision of 2 decimal places. If the value of the function is undefined, nan should be displayed. If no functions have been declared before the execution of the printfns command, nothing should be displayed on stdout.

An identifier is a non-empty string that can use English letters, digits, and underscores. An identifier cannot start with a digit. Identifiers are used as variable and function names.

# Examples
## Declaring, Assigning, and Printing Variable Values
| stdin       | stdout | Explanation                                                        |
|-------------|--------|--------------------------------------------------------------------|
| var x       |        | Declaring a variable x                                             |
| print x     | nan    | The value of variable x is not defined yet                         |
| let x = 42  |        | Assigning the value 42 to variable x                               |
| print x     | 42.00  | Variable x now holds the value 42                                  |
| let x = 1.234 |      | Changing the value of variable x to 1.234                          |
| print x     | 1.23   | The value is displayed with a precision of 2 decimal places         |
| let y = x   |        | Automatically declaring variable y and assigning it the current value of x |
| let x = 99  |        | Assigning the value 99 to variable x                               |
| printvars   | x:99.00 y:1.23 | Variable y holds the assigned value of x. Subsequent changes to x do not affect y. Variables are displayed in alphabetical order |
## Declaring Functions
| stdin              | stdout            | Explanation                                                                                     |
|--------------------|-------------------|-------------------------------------------------------------------------------------------------|
| var x              |                   | Declaring variable x                                                                           |
| var y              |                   | Declaring variable y                                                                           |
| fn XPlusY = x + y  |                   | Declaring the function XPlusY, which adds the values of x and y                                |
| print XPlusY       | nan               | The value of the function is undefined as the values of its arguments x and y are not defined   |
| let x = 3          |                   | Assigning the value 3 to variable x                                                            |
| let y = 4          |                   | Assigning the value 4 to variable y                                                            |
| print XPlusY       | 7.00              | The value of the function XPlusY is now defined and equals 7.00                                 |
| let x = 10         |                   | Changing the value of variable x to 10                                                          |
| print XPlusY       | 14.00             | The value of the function XPlusY depends on the values of its arguments x and y and equals 14.00 |
| let z = 3.5        |                   | Declaring variable z with a value of 3.5                                                        |
| fn XPlusYDivZ = XPlusY / z |           | Declaring the function XPlusYDivZ, which divides the value of the function XPlusY by the value of variable z |
| printfns           | XPlusY:14.00<br>XPlusYDivZ:4.00 | The values of functions XPlusY and XPlusYDivZ are displayed in alphabetical order: XPlusY:14.00, XPlusYDivZ:4.00 |
## Differences Between fn and let
| stdin                  | stdout    | Explanation                                                                                                                                                                 |
|------------------------|-----------|-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| let v=42               |           | Declaring variable v and assigning it the value 42                                                                                                                         |
| let variable=v         |           | The variable variable holds the value of v (42)                                                                                                                            |
| fn function=v          |           | The function function holds the action that will be computed when the function value is obtained                                                                           |
| let v=43               |           | Changing the value of variable v to 43                                                                                                                                     |
| print variable         | 42.00     | The variable variable holds the previously assigned value of 42                                                                                                            |
| print function         | 43.00     | The value of the function function is the value of variable v (43), computed at the time of function call (not at its declaration)                                          |
## Example: Calculating the Area of a Circle
| stdin                            | stdout      | Explanation                                                                                                                      |
|----------------------------------|-------------|----------------------------------------------------------------------------------------------------------------------------------|
| var radius                       |             | Declaring variable radius                                                                                                        |
| let pi=3.14159265                |             | Assigning the value 3.14159265 to variable pi                                                                                    |
| fn radiusSquared=radius\*radius    |             | Declaring the function radiusSquared, which calculates the square of the radius                                                  |
| fn circleArea=pi\*radiusSquared    |             | Declaring the function circleArea, which calculates the area of the circle                                                       |
| let radius=10                    |             | Assigning the value 10 to variable radius                                                                                        |
| print circleArea                 | 314.16      | Displaying the value of the circleArea function for a radius of 10                                                               |
| let circle10Area=circleArea       |             | Assigning the value of the circleArea function for a radius of 10 to variable circle10Area                                      |
| let radius=20                    |             | Changing the value of variable radius to 20                                                                                      |
| let circle20Area=circleArea       |             | Assigning the value of the circleArea function for a radius of 20 to variable circle20Area                                      |
| printfns | circleArea:1256.64 radiusSquared:400.00 | Displaying the values of the circleArea and radiusSquared functions                                                             |
| printvars | circle10Area:314.16 circle20Area:1256.64<br>pi:3.14<br>radius:20.00  | Displaying the values of the variables circle10Area, circle20Area, pi, and radius                                              |
## Example: Calculating the Fibonacci Sequence
| stdin                                      | stdout                          | Explanation                                                                                        |
|--------------------------------------------|---------------------------------|----------------------------------------------------------------------------------------------------|
| let v0=0                                    |                                 | Declaring variable v0 and assigning it the value 0                                                 |
| let v1=1                                    |                                 | Declaring variable v1 and assigning it the value 1                                                 |
| fn fib0=v0                                 |                                 | Declaring the function fib0 equal to the value of v0                                                |
| fn fib1=v1                                 |                                 | Declaring the function fib1 equal to the value of v1                                                |
| fn fib2=fib1+fib0                          |                                 | Declaring the function fib2 equal to the sum of fib1 and fib0                                       |
| fn fib3=fib2+fib1                          |                                 | Declaring the function fib3 equal to the sum of fib2 and fib1                                       |
| fn fib4=fib3+fib2                          |                                 | Declaring the function fib4 equal to the sum of fib3 and fib2                                       |
| fn fib5=fib4+fib3                          |                                 | Declaring the function fib5 equal to the sum of fib4 and fib3                                       |
| fn fib6=fib5+fib4                          |                                 | Declaring the function fib6 equal to the sum of fib5 and fib4                                       |
| printfns | fib0:0.00<br>fib1:1.00<br>fib2:1.00<br>fib3:2.00<br>fib4:3.00<br>fib5:5.00<br>fib6:8.00 | Displaying the values of the functions fib0, fib1, fib2, fib3, fib4, fib5, and fib6                 |
| let v0=1                                    |                                 | Changing the value of variable v0 to 1                                                             |
| let v1=1                                    |                                 | Changing the value of variable v1 to 1                                                             |
| printfns | fib0:1.00<br>fib1:1.00<br>fib2:2.00<br>fib3:3.00<br>fib4:5.00<br>fib5:8.00<br>fib6:13.00 | Displaying the updated values of the functions fib0, fib1, fib2, fib3, fib4, fib5, and fib6       |
# Optional Task Enhancement
The naive approach to calculating function values in some situations can lead to long computation times. For example, computing the value of the 50th Fibonacci number using functions fib0, fib1, fib2, ..., fib50 can take several seconds or even minutes. If your solution suffers from this problem, enhance the program to address the cause of the slow performance.
