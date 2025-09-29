#include "MathEngine.h"
#include <cmath>
#include <limits>
#include <QRegularExpression>

MathEngine::MathEngine() {
    setupDefaultOperators();
    setupDefaultFunctions();
}

void MathEngine::setupDefaultOperators() {
    registerOperator("+", 1, [](double a, double b) { return a + b; });
    registerOperator("-", 1, [](double a, double b) { return a - b; });
    registerOperator("*", 2, [](double a, double b) { return a * b; });
    registerOperator("/", 2, [](double a, double b) { return a / b; });
    registerOperator("^", 3, [](double a, double b) { return std::pow(a, b); });
}

void MathEngine::setupDefaultFunctions() {
    registerFunction("sin", [](double x) { return std::sin(x); });
    registerFunction("cos", [](double x) { return std::cos(x); });
    registerFunction("tan", [](double x) { return std::tan(x); });
    registerFunction("sqrt", [](double x) { return std::sqrt(x); });
    registerFunction("log", [](double x) { return std::log10(x); });
    registerFunction("ln", [](double x) { return std::log(x); });
    registerFunction("!", [](double x) {
        if (x < 0 || x != std::floor(x)) return std::nan("");
        if (x > 170) return std::numeric_limits<double>::infinity();
        double result = 1;
        for (int i = 2; i <= static_cast<int>(x); ++i) {
            result *= i;
        }
        return result;
    });
}

void MathEngine::registerOperator(const QString &op, int precedence,
                                   std::function<double(double, double)> func) {
    operators[op] = {precedence, func};
}

void MathEngine::registerFunction(const QString &name,
                                  std::function<double(double)> func) {
    functions[name] = func;
}

QString MathEngine::evaluate(const QString &expression) {
    lastError.clear();

    if (expression.isEmpty()) {
        return "";
    }

    try {
        QStringList tokens = tokenize(expression);
        QStringList rpn = infixToRPN(tokens);
        double result = evaluateRPN(rpn);

        // Format result
        QString resultStr = QString::number(result, 'g', 10);
        return resultStr;
    } catch (const std::exception &e) {
        lastError = QString("Error: %1").arg(e.what());
        return lastError;
    } catch (...) {
        lastError = "Unknown error occurred";
        return lastError;
    }
}

QStringList MathEngine::tokenize(const QString &expression) {
    QStringList tokens;
    QString current;
    QString expr = expression.simplified().replace(" ", "");

    for (int i = 0; i < expr.length(); ++i) {
        QChar c = expr[i];

        if (c.isDigit() || c == '.') {
            current += c;
        } else {
            if (!current.isEmpty()) {
                tokens.append(current);
                current.clear();
            }

            if (c.isLetter()) {
                // Function name
                current += c;
                while (i + 1 < expr.length() && expr[i + 1].isLetter()) {
                    current += expr[++i];
                }
                tokens.append(current);
                current.clear();
            } else {
                tokens.append(QString(c));
            }
        }
    }

    if (!current.isEmpty()) {
        tokens.append(current);
    }

    return tokens;
}

QStringList MathEngine::infixToRPN(const QStringList &tokens) {
    QStringList output;
    QStack<QString> stack;

    for (const QString &token : tokens) {
        if (isNumber(token) || token == "pi" || token == "e") {
            output.append(token);
        } else if (token == "!") {
            // Factorial is postfix, apply immediately
            output.append(token);
        } else if (isFunction(token)) {
            stack.push(token);
        } else if (isOperator(token)) {
            while (!stack.isEmpty() && stack.top() != "(" &&
                   (isFunction(stack.top()) ||
                    operatorPrecedence(stack.top()) >= operatorPrecedence(token))) {
                output.append(stack.pop());
            }
            stack.push(token);
        } else if (token == "(") {
            stack.push(token);
        } else if (token == ")") {
            while (!stack.isEmpty() && stack.top() != "(") {
                output.append(stack.pop());
            }
            if (!stack.isEmpty()) {
                stack.pop(); // Remove '('
            }
            if (!stack.isEmpty() && isFunction(stack.top())) {
                output.append(stack.pop());
            }
        }
    }

    while (!stack.isEmpty()) {
        output.append(stack.pop());
    }

    return output;
}

double MathEngine::evaluateRPN(const QStringList &tokens) {
    QStack<double> stack;

    for (const QString &token : tokens) {
        if (token == "pi") {
            stack.push(M_PI);
        } else if (token == "e") {
            stack.push(M_E);
        } else if (isNumber(token)) {
            stack.push(token.toDouble());
        } else if (token == "!") {
            // Factorial - postfix operator
            if (stack.isEmpty()) {
                throw std::runtime_error("Invalid expression");
            }
            double a = stack.pop();
            double result = functions["!"](a);
            stack.push(result);
        } else if (isOperator(token)) {
            if (stack.size() < 2) {
                throw std::runtime_error("Invalid expression");
            }
            double b = stack.pop();
            double a = stack.pop();
            double result = operators[token].function(a, b);
            stack.push(result);
        } else if (isFunction(token)) {
            if (stack.isEmpty()) {
                throw std::runtime_error("Invalid expression");
            }
            double a = stack.pop();
            double result = functions[token](a);
            stack.push(result);
        }
    }

    if (stack.size() != 1) {
        throw std::runtime_error("Invalid expression");
    }

    return stack.top();
}

bool MathEngine::isValidExpression(const QString &expression) const {
    // Basic validation
    return !expression.isEmpty();
}

int MathEngine::operatorPrecedence(const QString &op) const {
    auto it = operators.find(op);
    return (it != operators.end()) ? it->second.precedence : 0;
}

bool MathEngine::isOperator(const QString &token) const {
    return operators.find(token) != operators.end();
}

bool MathEngine::isFunction(const QString &token) const {
    return functions.find(token) != functions.end();
}

bool MathEngine::isNumber(const QString &token) const {
    bool ok;
    token.toDouble(&ok);
    return ok;
}