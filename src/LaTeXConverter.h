#ifndef LATEX_CONVERTER_H
#define LATEX_CONVERTER_H

#include <QString>
#include <map>

/**
 * Converts mathematical expressions to LaTeX format
 *
 * Easy to extend:
 * - Add new conversions via registerConversion()
 * - Override convert() for custom formatting
 * - Support for multiple output formats
 * - Can be replaced entirely in Calculator class
 */
class LaTeXConverter {
public:
    LaTeXConverter();
    virtual ~LaTeXConverter() = default;

    // Main conversion method
    virtual QString convert(const QString &expression, const QString &result = "");

    // Register custom conversions
    void registerConversion(const QString &from, const QString &to);

    // Configuration
    void setDisplayMode(bool inline_mode) { inlineMode = inline_mode; }
    bool isInlineMode() const { return inlineMode; }

protected:
    virtual QString convertOperators(const QString &expr);
    virtual QString convertFunctions(const QString &expr);
    virtual QString convertNumbers(const QString &expr);
    virtual QString wrapExpression(const QString &expr);

private:
    std::map<QString, QString> conversions;
    bool inlineMode;

    void setupDefaultConversions();
};

#endif // LATEX_CONVERTER_H