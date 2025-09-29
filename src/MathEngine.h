#ifndef MATH_ENGINE_H
#define MATH_ENGINE_H

#include <QString>
#include <QStack>
#include <functional>
#include <map>

/**
 * Mathematical computation engine
 *
 * Extensible design:
 * - Add new operators via registerOperator()
 * - Add new functions via registerFunction()
 * - Replace evaluation algorithm by overriding evaluate()
 * - Support for custom number formats
 * - Can be replaced entirely in Calculator class
 */
class MathEngine {
public:
    MathEngine();
    virtual ~MathEngine() = default;

    // Main evaluation method
    virtual QString evaluate(const QString &expression);

    // Operator registration for easy extension
    void registerOperator(const QString &op, int precedence,
                          std::function<double(double, double)> func);

    // Function registration for easy extension
    void registerFunction(const QString &name,
                          std::function<double(double)> func);

    // Validation
    bool isValidExpression(const QString &expression) const;
    QString getLastError() const { return lastError; }

protected:
    // Helper methods
    virtual double evaluateRPN(const QStringList &tokens);
    virtual QStringList infixToRPN(const QStringList &tokens);
    virtual QStringList tokenize(const QString &expression);

    int operatorPrecedence(const QString &op) const;
    bool isOperator(const QString &token) const;
    bool isFunction(const QString &token) const;
    bool isNumber(const QString &token) const;

private:
    struct OperatorInfo {
        int precedence;
        std::function<double(double, double)> function;
    };

    std::map<QString, OperatorInfo> operators;
    std::map<QString, std::function<double(double)>> functions;
    QString lastError;

    void setupDefaultOperators();
    void setupDefaultFunctions();
};

#endif // MATH_ENGINE_H