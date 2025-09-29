#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QWidget>
#include <QLineEdit>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <memory>

class CalculatorButton;
class MathEngine;
class LaTeXConverter;
class TypstConverter;

/**
 * Main Calculator window
 *
 * Modular design allows easy extension:
 * - Add new buttons via addButton()
 * - Replace MathEngine for different calculation logic
 * - Replace LaTeXConverter for different display formatting
 * - Override virtual methods for custom behavior
 */
class Calculator : public QWidget {
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = nullptr);
    virtual ~Calculator();

protected:
    // Virtual methods for easy extension
    virtual void setupUI();
    virtual void setupButtons();
    virtual void setupConnections();
    virtual void styleWidget();

    // Button creation helpers
    void addButton(const QString &text, int row, int col,
                   int rowSpan = 1, int colSpan = 1);
    void addOperatorButton(const QString &text, int row, int col);
    void addNumberButton(const QString &text, int row, int col,
                         int rowSpan = 1, int colSpan = 1);

private slots:
    void handleButtonClick(const QString &text);
    void handleClear();
    void handleBackspace();
    void handleEquals();
    void toggleFormat();

private:
    void updateDisplays();

    enum class OutputFormat {
        LaTeX,
        Typst
    };

    // UI Components
    QLineEdit *inputDisplay;
    QTextEdit *latexDisplay;
    QPushButton *formatToggle;
    QVBoxLayout *mainLayout;
    QGridLayout *buttonLayout;

    // Core logic components (easily replaceable)
    std::unique_ptr<MathEngine> mathEngine;
    std::unique_ptr<LaTeXConverter> latexConverter;
    std::unique_ptr<TypstConverter> typstConverter;

    // State
    QString currentInput;
    OutputFormat currentFormat;
};

#endif // CALCULATOR_H