#ifndef TYPST_CONVERTER_H
#define TYPST_CONVERTER_H

#include <QString>
#include <map>

/**
 * Converts mathematical expressions to Typst format
 *
 * Easy to extend:
 * - Add new conversions via registerConversion()
 * - Override convert() for custom formatting
 * - Can be used alongside LaTeXConverter
 */
class TypstConverter {
public:
    TypstConverter();
    virtual ~TypstConverter() = default;

    // Main conversion method
    virtual QString convert(const QString &expression, const QString &result = "");

    // Register custom conversions
    void registerConversion(const QString &from, const QString &to);

    // Configuration
    void setDisplayMode(bool block_mode) { blockMode = block_mode; }
    bool isBlockMode() const { return blockMode; }

protected:
    virtual QString convertOperators(const QString &expr);
    virtual QString convertFunctions(const QString &expr);
    virtual QString convertNumbers(const QString &expr);
    virtual QString wrapExpression(const QString &expr);

private:
    std::map<QString, QString> conversions;
    bool blockMode;

    void setupDefaultConversions();
};

#endif // TYPST_CONVERTER_H