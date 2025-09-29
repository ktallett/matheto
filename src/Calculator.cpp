#include "Calculator.h"
#include "CalculatorButton.h"
#include "MathEngine.h"
#include "LaTeXConverter.h"
#include "TypstConverter.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent),
      mathEngine(std::make_unique<MathEngine>()),
      latexConverter(std::make_unique<LaTeXConverter>()),
      typstConverter(std::make_unique<TypstConverter>()),
      currentFormat(OutputFormat::LaTeX) {

    setupUI();
    setupButtons();
    setupConnections();
    styleWidget();
}

Calculator::~Calculator() = default;

void Calculator::setupUI() {
    setWindowTitle("Matheto");
    setMinimumSize(400, 600);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(10, 10, 10, 10);

    // Input display
    QLabel *inputLabel = new QLabel("Input:", this);
    inputLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    mainLayout->addWidget(inputLabel);

    inputDisplay = new QLineEdit(this);
    inputDisplay->setReadOnly(true);
    inputDisplay->setAlignment(Qt::AlignRight);
    inputDisplay->setMinimumHeight(50);
    inputDisplay->setStyleSheet(
        "QLineEdit {"
        "    font-size: 20px;"
        "    padding: 10px;"
        "    border: 2px solid #ccc;"
        "    border-radius: 5px;"
        "    background-color: white;"
        "}"
    );
    mainLayout->addWidget(inputDisplay);

    // Format label and toggle button
    QHBoxLayout *formatLayout = new QHBoxLayout();
    QLabel *latexLabel = new QLabel("LaTeX Preview:", this);
    latexLabel->setObjectName("formatLabel");
    latexLabel->setStyleSheet("font-weight: bold; font-size: 14px;");
    formatLayout->addWidget(latexLabel);

    formatToggle = new QPushButton("Switch to Typst", this);
    formatToggle->setMaximumWidth(150);
    connect(formatToggle, &QPushButton::clicked, this, &Calculator::toggleFormat);
    formatLayout->addWidget(formatToggle);
    formatLayout->addStretch();

    mainLayout->addLayout(formatLayout);

    latexDisplay = new QTextEdit(this);
    latexDisplay->setReadOnly(true);
    latexDisplay->setMinimumHeight(100);
    latexDisplay->setMaximumHeight(150);
    latexDisplay->setStyleSheet(
        "QTextEdit {"
        "    font-size: 16px;"
        "    font-family: 'Courier New', monospace;"
        "    padding: 10px;"
        "    border: 2px solid #ccc;"
        "    border-radius: 5px;"
        "    background-color: #f9f9f9;"
        "}"
    );
    mainLayout->addWidget(latexDisplay);

    // Button layout
    buttonLayout = new QGridLayout();
    buttonLayout->setSpacing(5);
    mainLayout->addLayout(buttonLayout);
}

void Calculator::setupButtons() {
    // Row 0: Functions and Clear
    addButton("sin", 0, 0);
    addButton("cos", 0, 1);
    addButton("tan", 0, 2);
    addButton("π", 0, 3);
    addButton("e", 0, 4);
    addButton("C", 0, 5);

    // Row 1: More functions
    addButton("ln", 1, 0);
    addButton("log", 1, 1);
    addButton("sqrt", 1, 2);
    addButton("x²", 1, 3);
    addButton("xʸ", 1, 4);
    addButton("!", 1, 5);

    // Row 2: (, ), 7, 8, 9, ⌫
    addButton("(", 2, 0);
    addButton(")", 2, 1);
    addNumberButton("7", 2, 2);
    addNumberButton("8", 2, 3);
    addNumberButton("9", 2, 4);
    addButton("⌫", 2, 5);

    // Row 3: /, *, 4, 5, 6, =
    addOperatorButton("/", 3, 0);
    addOperatorButton("*", 3, 1);
    addNumberButton("4", 3, 2);
    addNumberButton("5", 3, 3);
    addNumberButton("6", 3, 4);
    addButton("=", 3, 5, 2, 1);

    // Row 4: -, +, 1, 2, 3
    addOperatorButton("-", 4, 0);
    addOperatorButton("+", 4, 1);
    addNumberButton("1", 4, 2);
    addNumberButton("2", 4, 3);
    addNumberButton("3", 4, 4);

    // Row 5: %, ., 0
    addButton("%", 5, 0);
    addButton(".", 5, 1);
    addNumberButton("0", 5, 2, 1, 3);
}

void Calculator::setupConnections() {
    // Connections are set up in addButton methods
}

void Calculator::styleWidget() {
    setStyleSheet(
        "QWidget {"
        "    background-color: #f0f0f0;"
        "}"
    );
}

void Calculator::addButton(const QString &text, int row, int col,
                           int rowSpan, int colSpan) {
    CalculatorButton *button = new CalculatorButton(text, this);

    // Set button type based on text
    if (text == "C") {
        button->setButtonType(CalculatorButton::Special);
    } else if (text == "=" || text == "⌫") {
        button->setButtonType(CalculatorButton::Function);
    } else if (text == "sin" || text == "cos" || text == "tan" ||
               text == "sqrt" || text == "^" || text == "(" || text == ")") {
        button->setButtonType(CalculatorButton::Function);
    }

    connect(button, &QPushButton::clicked, this, [this, text]() {
        handleButtonClick(text);
    });

    buttonLayout->addWidget(button, row, col, rowSpan, colSpan);
}

void Calculator::addOperatorButton(const QString &text, int row, int col) {
    CalculatorButton *button = new CalculatorButton(text, this);
    button->setButtonType(CalculatorButton::Operator);

    connect(button, &QPushButton::clicked, this, [this, text]() {
        handleButtonClick(text);
    });

    buttonLayout->addWidget(button, row, col);
}

void Calculator::addNumberButton(const QString &text, int row, int col,
                                 int rowSpan, int colSpan) {
    CalculatorButton *button = new CalculatorButton(text, this);
    button->setButtonType(CalculatorButton::Number);

    connect(button, &QPushButton::clicked, this, [this, text]() {
        handleButtonClick(text);
    });

    buttonLayout->addWidget(button, row, col, rowSpan, colSpan);
}

void Calculator::handleButtonClick(const QString &text) {
    if (text == "C") {
        handleClear();
    } else if (text == "⌫") {
        handleBackspace();
    } else if (text == "=") {
        handleEquals();
    } else if (text == "x²") {
        currentInput += "^2";
        updateDisplays();
    } else if (text == "xʸ") {
        currentInput += "^";
        updateDisplays();
    } else if (text == "π") {
        currentInput += "pi";
        updateDisplays();
    } else if (text == "e") {
        currentInput += "e";
        updateDisplays();
    } else if (text == "ln") {
        currentInput += "ln(";
        updateDisplays();
    } else if (text == "log") {
        currentInput += "log(";
        updateDisplays();
    } else if (text == "sin" || text == "cos" || text == "tan" || text == "sqrt") {
        currentInput += text + "(";
        updateDisplays();
    } else if (text == "%") {
        currentInput += "/100";
        updateDisplays();
    } else {
        currentInput += text;
        updateDisplays();
    }
}

void Calculator::handleClear() {
    currentInput.clear();
    updateDisplays();
}

void Calculator::handleBackspace() {
    if (!currentInput.isEmpty()) {
        currentInput.chop(1);
        updateDisplays();
    }
}

void Calculator::handleEquals() {
    if (currentInput.isEmpty()) {
        return;
    }

    QString result = mathEngine->evaluate(currentInput);
    QString formatted;

    if (currentFormat == OutputFormat::LaTeX) {
        formatted = latexConverter->convert(currentInput, result);
    } else {
        formatted = typstConverter->convert(currentInput, result);
    }

    inputDisplay->setText(currentInput + " = " + result);
    latexDisplay->setText(formatted);

    // Optionally, set currentInput to result for continued calculation
    // currentInput = result;
}

void Calculator::toggleFormat() {
    if (currentFormat == OutputFormat::LaTeX) {
        currentFormat = OutputFormat::Typst;
        formatToggle->setText("Switch to LaTeX");

        // Update label
        QLabel *label = findChild<QLabel*>("formatLabel");
        if (label) {
            label->setText("Typst Preview:");
        }
    } else {
        currentFormat = OutputFormat::LaTeX;
        formatToggle->setText("Switch to Typst");

        // Update label
        QLabel *label = findChild<QLabel*>("formatLabel");
        if (label) {
            label->setText("LaTeX Preview:");
        }
    }

    updateDisplays();
}

void Calculator::updateDisplays() {
    inputDisplay->setText(currentInput);

    if (!currentInput.isEmpty()) {
        QString formatted;
        if (currentFormat == OutputFormat::LaTeX) {
            formatted = latexConverter->convert(currentInput);
        } else {
            formatted = typstConverter->convert(currentInput);
        }
        latexDisplay->setText(formatted);
    } else {
        latexDisplay->clear();
    }
}