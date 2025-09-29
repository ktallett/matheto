#include "TypstConverter.h"
#include <QStringList>

TypstConverter::TypstConverter() : blockMode(false) {
    setupDefaultConversions();
}

void TypstConverter::setupDefaultConversions() {
    // Mathematical operators
    registerConversion("*", "times");
    registerConversion("/", "div");
    registerConversion("^", "^");

    // Functions
    registerConversion("sqrt", "sqrt");
    registerConversion("sin", "sin");
    registerConversion("cos", "cos");
    registerConversion("tan", "tan");
    registerConversion("log", "log");
    registerConversion("ln", "ln");
}

void TypstConverter::registerConversion(const QString &from, const QString &to) {
    conversions[from] = to;
}

QString TypstConverter::convert(const QString &expression, const QString &result) {
    if (expression.isEmpty()) {
        return "";
    }

    QString typst = expression;

    // Convert functions and operators
    typst = convertFunctions(typst);
    typst = convertOperators(typst);

    // Add result if provided
    if (!result.isEmpty()) {
        typst += " = " + result;
    }

    // Wrap in Typst delimiters
    return wrapExpression(typst);
}

QString TypstConverter::convertOperators(const QString &expr) {
    QString result = expr;

    // Replace pi and e with proper symbols
    result.replace("pi", "pi");
    result.replace("e", "e");

    // Factorial already uses ! which is correct in Typst

    // Percent - convert /100 to %
    result.replace("/100", "%");

    // Replace multiplication with Typst notation
    result.replace("*", " times ");

    // Replace division with Typst notation
    result.replace("/", " / ");

    // Handle exponentiation - Typst uses ^ with superscript
    int pos = 0;
    while ((pos = result.indexOf("^", pos)) != -1) {
        int start = pos + 1;
        int end = start;

        // Find the extent of the exponent
        if (start < result.length()) {
            if (result[start] == '(') {
                // Find matching parenthesis
                int depth = 1;
                end = start + 1;
                while (end < result.length() && depth > 0) {
                    if (result[end] == '(') depth++;
                    if (result[end] == ')') depth--;
                    end++;
                }
            } else {
                // Single character or number
                while (end < result.length() &&
                       (result[end].isDigit() || result[end] == '.')) {
                    end++;
                }
            }

            QString exponent = result.mid(start, end - start);
            result.replace(pos, end - pos, "^" + exponent);
            pos = pos + exponent.length() + 1;
        } else {
            pos++;
        }
    }

    return result;
}

QString TypstConverter::convertFunctions(const QString &expr) {
    QString result = expr;

    // Convert sqrt(x) to sqrt(x) - Typst syntax is the same
    // But we should ensure proper formatting

    // Convert trigonometric and other functions
    QStringList functions = {"sin", "cos", "tan", "log", "ln"};

    for (const QString &func : functions) {
        if (conversions.find(func) == conversions.end()) continue;

        QString typstFunc = conversions[func];
        int pos = 0;
        QString pattern = func + "(";

        while ((pos = result.indexOf(pattern, pos)) != -1) {
            int start = pos + pattern.length(); // After "func("
            int depth = 1;
            int end = start;

            while (end < result.length() && depth > 0) {
                if (result[end] == '(') depth++;
                if (result[end] == ')') depth--;
                end++;
            }

            QString argument = result.mid(start, end - start - 1);
            // Format as function(x) for Typst
            result.replace(pos, end - pos, typstFunc + "(" + argument + ")");
            pos += typstFunc.length() + argument.length() + 2;
        }
    }

    // Handle sqrt specially
    int pos = 0;
    while ((pos = result.indexOf("sqrt(", pos)) != -1) {
        int start = pos + 5; // After "sqrt("
        int depth = 1;
        int end = start;

        while (end < result.length() && depth > 0) {
            if (result[end] == '(') depth++;
            if (result[end] == ')') depth--;
            end++;
        }

        QString argument = result.mid(start, end - start - 1);
        result.replace(pos, end - pos, "sqrt(" + argument + ")");
        pos += argument.length() + 6;
    }

    return result;
}

QString TypstConverter::convertNumbers(const QString &expr) {
    // Future: handle scientific notation, complex numbers, etc.
    return expr;
}

QString TypstConverter::wrapExpression(const QString &expr) {
    if (blockMode) {
        return "$ " + expr + " $";
    } else {
        return "$" + expr + "$";
    }
}