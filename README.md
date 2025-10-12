# Matheto - Scientific Calculator

A lightweight, modular scientific calculator built with C++ and Qt5 for mathematicians, engineers, and students.

Designed with functional minimalism and precision, featuring dual mathematical notation support (LaTeX and Typst) for educational and professional use.

## Features

- 🧮 **Scientific functions** - Trigonometric, logarithmic, exponential, and factorial operations
- 📐 **Mathematical notation** - Real-time LaTeX and Typst output for documentation
- 🎨 **Modern design** - Clean interface following Universal Design System principles
- 📱 **Responsive layout** - Optimized for MNT Pocket Reform and desktop displays
- ⚡ **Lightweight** - Fast, minimal dependencies, efficient performance
- 🔢 **Expression evaluation** - Advanced math engine with proper operator precedence
- 🎯 **Modular architecture** - Easily extensible for custom functions and converters
- ⌨️ **Keyboard-friendly** - Full keyboard navigation support

## Installation

### Prerequisites

- Qt 5.12+ development libraries
- CMake 3.16+
- C++17 compatible compiler
- Git

### Linux (Fedora/CentOS)

```bash
sudo dnf install cmake gcc-c++ qt5-qtbase-devel git

git clone https://github.com/ktallett/matheto.git
cd matheto

mkdir build && cd build
cmake ..
make -j4

./matheto
```

### Linux (Debian/Ubuntu)

```bash
sudo apt update
sudo apt install cmake g++ qtbase5-dev git

git clone https://github.com/ktallett/matheto.git
cd matheto

mkdir build && cd build
cmake ..
make -j4

./matheto
```

### macOS

```bash
brew install qt@5 cmake

git clone https://github.com/ktallett/matheto.git
cd matheto

mkdir build && cd build
cmake -DCMAKE_PREFIX_PATH=/opt/homebrew/opt/qt@5 ..
make -j4

./matheto
```

### Windows

1. Install [Qt 5](https://www.qt.io/download)
2. Install [CMake](https://cmake.org/download/)
3. Clone the repository
4. Open Qt Creator and import the CMakeLists.txt file
5. Build and run

### System-wide Installation (Linux/macOS)

```bash
# After building, install to /usr/local/bin
cd build
sudo make install

# Now you can run from anywhere
matheto
```

## Usage

### Basic Operations

Click buttons or type directly to input expressions. The calculator supports:
- **Basic arithmetic**: +, -, *, /, %
- **Trigonometry**: sin(), cos(), tan()
- **Logarithms**: ln(), log()
- **Powers**: x², xʸ (^)
- **Constants**: π (pi), e
- **Functions**: sqrt(), ! (factorial)

### Mathematical Notation

Toggle between LaTeX and Typst output formats:
- **LaTeX Preview**: For use in LaTeX documents, academic papers
- **Typst Preview**: For modern typesetting with Typst

Click "Switch to Typst" or "Switch to LaTeX" button to change format.

### Platform Notes

Matheto is optimized for the **MNT Pocket Reform** handheld Linux computer with responsive sizing for split-screen tiling window managers. Works on any Linux desktop, macOS, or Windows system with Qt5.

## Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a new feature branch: `git checkout -b feature/your-feature`
3. Commit your changes with clear messages
4. Open a pull request for review

Please ensure your contributions follow the existing code style and include appropriate documentation and tests where applicable.

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

## References & Acknowledgements

- [GNU GPL v3 License](https://www.gnu.org/licenses/gpl-3.0.en.html)
- [MNT Pocket Reform](https://mntre.com/reform/)
- [Universal Design System](https://docs.elementary.io/hig)
- [NumWorks Calculator](https://www.numworks.com/)
- [Qt Framework](https://www.qt.io/)

---
