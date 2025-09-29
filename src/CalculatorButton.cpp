#include "CalculatorButton.h"

CalculatorButton::CalculatorButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent), m_type(Number) {
    setMinimumSize(60, 50);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    applyStyle();
}

void CalculatorButton::setButtonType(ButtonType type) {
    m_type = type;
    applyStyle();
}

void CalculatorButton::applyStyle() {
    QString baseStyle =
        "QPushButton {"
        "    border: 1px solid #ccc;"
        "    border-radius: 4px;"
        "    font-size: 16px;"
        "    font-weight: bold;"
        "}"
        "QPushButton:hover {"
        "    border: 2px solid #999;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #ddd;"
        "}";

    QString colorStyle;
    switch (m_type) {
    case Number:
        colorStyle = "background-color: #f5f5f5; color: #333;";
        break;
    case Operator:
        colorStyle = "background-color: #ff9500; color: white;";
        break;
    case Function:
        colorStyle = "background-color: #4a90e2; color: white;";
        break;
    case Special:
        colorStyle = "background-color: #e74c3c; color: white;";
        break;
    }

    setStyleSheet(baseStyle + "QPushButton {" + colorStyle + "}");
}