# Matheto - Scientific Calculator

A lightweight scientific calculator built with C++ and Qt 5 for mathematicians, engineers, and students.

Designed with functional minimalism and precision, focusing on essential scientific calculations with dual mathematical notation output (LaTeX and Typst).

## Features

- **Scientific functions** - Trigonometric, logarithmic, exponential, and factorial operations
- **Mathematical notation** - Real-time LaTeX and Typst output for documentation
- **Expression evaluation** - Advanced math engine with proper operator precedence
- **Modular architecture** - Easily extensible for custom functions and converters
- **Responsive design** - Optimized for MNT Pocket Reform and desktop displays
- **Modern UI** - Clean design following Universal Design System principles
- **Lightweight** - Fast and efficient with minimal dependencies

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

The calculator supports:
- **Basic arithmetic**: +, -, *, /, %
- **Trigonometry**: sin(), cos(), tan()
- **Logarithms**: ln(), log()
- **Powers**: x² (square), xʸ (power)
- **Constants**: π (pi), e
- **Functions**: sqrt() (square root), ! (factorial)

### Mathematical Notation Output

Toggle between output formats using the button in the interface:
- **LaTeX** - For LaTeX documents and academic papers
- **Typst** - For modern typesetting with Typst

## License

This project is licensed under the GNU General Public License v3.0 - see the [LICENSE](LICENSE) file for details.

---
