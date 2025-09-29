# matheto

A lightweight, modular calculator for Linux with dual mathematical notation support (LaTeX and Typst) currently still being developed.


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
## License

GPL-3.0

---
