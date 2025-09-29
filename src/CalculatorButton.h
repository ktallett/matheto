#ifndef CALCULATOR_BUTTON_H
#define CALCULATOR_BUTTON_H

#include <QPushButton>

/**
 * Custom calculator button with enhanced styling
 *
 * Easy to extend with:
 * - Custom colors via setButtonType()
 * - Custom sizes
 * - Custom animations
 * - Sound effects
 */
class CalculatorButton : public QPushButton {
    Q_OBJECT

public:
    enum ButtonType {
        Number,
        Operator,
        Function,
        Special
    };

    explicit CalculatorButton(const QString &text, QWidget *parent = nullptr);

    void setButtonType(ButtonType type);
    ButtonType buttonType() const { return m_type; }

protected:
    virtual void applyStyle();

private:
    ButtonType m_type;
};

#endif // CALCULATOR_BUTTON_H