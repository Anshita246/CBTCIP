#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include <cmath>

class Calculator {
public:
    void run();

private:
    double getNumber();
    char getOperator();
    double calculate(double num1, char op, double num2);
    bool isOperatorValid(char op);
};

void Calculator::run() {
    double num1, num2, result;
    char op;
    std::string choice;

    do {
        try {
            std::cout << "Enter the first number: ";
            num1 = getNumber();
            std::cout << "Enter an operator (+, -, *, /, ^): ";
            op = getOperator();
            std::cout << "Enter the second number: ";
            num2 = getNumber();

            result = calculate(num1, op, num2);
            std::cout << "Result: " << num1 << " " << op << " " << num2 << " = " << result << std::endl;
        } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

        std::cout << "Do you want to perform another calculation? (yes/no): ";
        std::cin >> choice;
    } while (choice == "yes" || choice == "y");
}

double Calculator::getNumber() {
    double number;
    std::string input;

    while (true) {
        std::cin >> input;
        std::stringstream ss(input);

        if (ss >> number) {
            return number;
        } else {
            std::cout << "Invalid input. Please enter a valid number: ";
        }
    }
}

char Calculator::getOperator() {
    char op;
    std::cin >> op;

    while (!isOperatorValid(op)) {
        std::cout << "Invalid operator. Please enter a valid operator (+, -, *, /, ^): ";
        std::cin >> op;
    }

    return op;
}

double Calculator::calculate(double num1, char op, double num2) {
    switch (op) {
        case '+':
            return num1 + num2;
        case '-':
            return num1 - num2;
        case '*':
            return num1 * num2;
        case '/':
            if (num2 == 0) {
                throw std::invalid_argument("Division by zero");
            }
            return num1 / num2;
        case '^':
            return std::pow(num1, num2);
        default:
            throw std::invalid_argument("Invalid operator");
    }
}

bool Calculator::isOperatorValid(char op) {
    return op == '+' || op == '-' || op == '*' || op == '/' || op == '^';
}

int main() {
    Calculator calculator;
    calculator.run();
    return 0;
}
