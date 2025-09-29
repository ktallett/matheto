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
        "    border: none;"
        "    border-radius: 8px;"
        "    font-size: 18px;"
        "    font-weight: 500;"
        "    font-family: 'SF Pro Text', 'Segoe UI', sans-serif;"
        "}"
        "QPushButton:hover {"
        "    opacity: 0.9;"
        "}"
        "QPushButton:pressed {"
        "    opacity: 0.7;"
        "}";

    QString colorStyle;
    switch (m_type) {
    case Number:
        // White/light grey for numbers
        colorStyle = "background-color: #FFFFFF; color: #333333;";
        break;
    case Operator:
        // Orange for operators (NumWorks style)
        colorStyle = "background-color: #FF9500; color: #FFFFFF;";
        break;
    case Function:
        // Medium grey for functions
        colorStyle = "background-color: #A5A5A5; color: #FFFFFF;";
        break;
    case Special:
        // Dark grey for special buttons
        colorStyle = "background-color: #505050; color: #FFFFFF;";
        break;
    }

    setStyleSheet(baseStyle + "QPushButton {" + colorStyle + "}");
}