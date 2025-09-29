# Matheto

A lightweight, modular calculator for Linux with dual mathematical notation support (LaTeX and Typst).

## Features

- **Dual Display**: Input display and mathematical notation preview
- **Format Switching**: Toggle between LaTeX and Typst output formats
- **Basic Operations**: Addition, subtraction, multiplication, division, exponentiation
- **Advanced Functions**:
  - Trigonometric: sin, cos, tan
  - Logarithmic: ln (natural log), log (base 10)
  - Square root
  - Factorial (!)
- **Constants**: π (pi), e (Euler's number)
- **Special Operations**: Percentage (%), power functions (x², xʸ)
- **Clean UI**: Simple, color-coded buttons with modern styling

## Installation

### Fedora

```bash
# Install dependencies
sudo dnf install cmake gcc-c++ qt5-qtbase-devel

# Clone or navigate to the project directory
cd matheto

# Build
mkdir build && cd build
cmake ..
make

# Run
./matheto
```

### Debian/Ubuntu

```bash
# Install dependencies
sudo apt install cmake g++ qtbase5-dev

# Clone or navigate to the project directory
cd matheto

# Build
mkdir build && cd build
cmake ..
make

# Run
./matheto
```

### Optional: System-wide Installation

```bash
# After building, install to /usr/local/bin
sudo make install

# Now you can run from anywhere
matheto
```

## Usage

1. **Input**: Click buttons or type expressions
2. **Calculate**: Press `=` to evaluate
3. **Format Toggle**: Click "Switch to Typst" or "Switch to LaTeX" to change output format
4. **Functions**: Function buttons (sin, cos, tan, sqrt, ln, log) automatically add opening parenthesis
5. **Clear**: Press `C` to clear input
6. **Backspace**: Press `⌫` to delete last character

## Architecture

Matheto is designed with modularity in mind:

- **Calculator**: Main UI component with virtual methods for easy extension
- **CalculatorButton**: Custom button widget with type-based styling
- **MathEngine**: Pluggable calculation engine with operator/function registration
- **LaTeXConverter**: Extensible LaTeX formatting system
- **TypstConverter**: Extensible Typst formatting system

## Extending Matheto

### Adding New Operators

```cpp
mathEngine->registerOperator("operator", precedence,
    [](double a, double b) { return result; });
```

### Adding New Functions

```cpp
mathEngine->registerFunction("function_name",
    [](double x) { return result; });
```

### Adding New Buttons

Override `setupButtons()` in Calculator class and use:
- `addButton()` - Generic button
- `addNumberButton()` - Number button with number styling
- `addOperatorButton()` - Operator button with operator styling

## License

GPL-3.0

## Contributing

[Add contribution guidelines here]