#include "CalculatorButton.h"

CalculatorButton::CalculatorButton(const QString &text, QWidget *parent)
    : QPushButton(text, parent), m_type(Number) {
    // Responsive sizing - no fixed minimum, let it scale down
    setMinimumSize(40, 36);  // Smaller minimum for compact screens
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
        "    border: 2px solid transparent;"
        "    border-radius: 6px;"
        "    font-size: 18px;"
        "    font-weight: 500;"
        "    font-family: 'Inter', 'Segoe UI', 'Roboto', sans-serif;"
        "    padding: 8px 16px;"
        "    min-height: 36px;"
        "}"
        "QPushButton:pressed {"
        "    transform: translateY(0);"
        "}";

    QString colorStyle;
    QString hoverStyle;
    switch (m_type) {
    case Number:
        // White background for numbers (design system)
        colorStyle = "background-color: #FFFFFF; color: #000000; border-color: #E0E0E0;";
        hoverStyle = "QPushButton:hover { background-color: #FAFAFA; border-color: #4482B4; }";
        break;
    case Operator:
        // Primary accent for operators
        colorStyle = "background-color: #4482B4; color: white;";
        hoverStyle = "QPushButton:hover { background-color: #3574A0; box-shadow: 0 2px 8px rgba(68, 130, 180, 0.3); }";
        break;
    case Function:
        // Secondary accent for functions
        colorStyle = "background-color: #FF9C5C; color: white;";
        hoverStyle = "QPushButton:hover { background-color: #FFB380; box-shadow: 0 2px 8px rgba(255, 156, 92, 0.3); }";
        break;
    case Special:
        // Error color for special buttons (clear, etc)
        colorStyle = "background-color: #EF5350; color: white;";
        hoverStyle = "QPushButton:hover { background-color: #E53935; }";
        break;
    }

    setStyleSheet(baseStyle + "QPushButton {" + colorStyle + "}" + hoverStyle);
}