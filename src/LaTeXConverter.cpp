#include "LaTeXConverter.h"
#include <QStringList>

LaTeXConverter::LaTeXConverter() : inlineMode(false) {
    setupDefaultConversions();
}

void LaTeXConverter::setupDefaultConversions() {
    // Mathematical operators
    registerConversion("*", "\\times");
    registerConversion("/", "\\div");
    registerConversion("^", "^");

    // Functions
    registerConversion("sqrt", "\\sqrt");
    registerConversion("sin", "\\sin");
    registerConversion("cos", "\\cos");
    registerConversion("tan", "\\tan");
    registerConversion("log", "\\log");
    registerConversion("ln", "\\ln");
}

void LaTeXConverter::registerConversion(const QString &from, const QString &to) {
    conversions[from] = to;
}

QString LaTeXConverter::convert(const QString &expression, const QString &result) {
    if (expression.isEmpty()) {
        return "";
    }

    QString latex = expression;

    // Convert functions and operators
    latex = convertFunctions(latex);
    latex = convertOperators(latex);

    // Add result if provided
    if (!result.isEmpty()) {
        latex += " = " + result;
    }

    // Wrap in LaTeX delimiters
    return wrapExpression(latex);
}

QString LaTeXConverter::convertOperators(const QString &expr) {
    QString result = expr;

    // Replace pi and e with proper symbols
    result.replace("pi", "\\pi");
    result.replace("e", "e");

    // Factorial already uses ! which is correct in LaTeX

    // Percent - convert /100 to %
    result.replace("/100", "\\%");

    // Replace multiplication
    result.replace("*", " \\times ");

    // Replace division with fraction notation
    // Simple case: a/b -> \frac{a}{b}
    // For now, keep simple division symbol
    result.replace("/", " \\div ");

    // Handle exponentiation
    // Convert a^b to a^{b} for proper LaTeX
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
            result.replace(pos, end - pos, "^{" + exponent + "}");
            pos = pos + exponent.length() + 3;
        } else {
            pos++;
        }
    }

    return result;
}

QString LaTeXConverter::convertFunctions(const QString &expr) {
    QString result = expr;

    // Convert sqrt(x) to \sqrt{x}
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
        result.replace(pos, end - pos, "\\sqrt{" + argument + "}");
        pos += argument.length() + 7;
    }

    // Convert trigonometric and other functions (sin, cos, tan, log, ln)
    QStringList functions = {"sin", "cos", "tan", "log", "ln"};

    for (const QString &func : functions) {
        if (conversions.find(func) == conversions.end()) continue;

        QString latexFunc = conversions[func];
        pos = 0;
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
            // Format as \sin(x) or \sin{x} - using parentheses for readability
            result.replace(pos, end - pos, latexFunc + "\\left(" + argument + "\\right)");
            pos += latexFunc.length() + argument.length() + 13; // length of \left( and \right)
        }
    }

    return result;
}

QString LaTeXConverter::convertNumbers(const QString &expr) {
    // Future: handle scientific notation, complex numbers, etc.
    return expr;
}

QString LaTeXConverter::wrapExpression(const QString &expr) {
    if (inlineMode) {
        return "$" + expr + "$";
    } else {
        return "$$" + expr + "$$";
    }
}