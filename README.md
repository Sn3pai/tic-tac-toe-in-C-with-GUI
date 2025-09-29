# 🎮 Tic-Tac-Toe (C++ with SFML)

A simple Tic-Tac-Toe game built using **C++** and **SFML** with a clean graphical interface.  
Two players can play on the same machine, with win/draw detection and a restart option.

---

## ✨ Features
- 🟩 **GUI** with SFML (no console required)  
- 🎲 **Two-player mode** (X vs O)  
- ✅ **Win & draw detection**  
- 🔄 **Restart game with R key**  
- 🎨 Simple and minimal design  

---

## 📂 Project Structure
project/
│── tictactoe.cpp # Source code
│── resources/
│ └── arial.ttf # Font file (required)


---

## ⚙️ Requirements
- **C++17** or later  
- **SFML 2.5+** (graphics, window, system)  

### Windows
You can install SFML via [MSYS2](https://www.msys2.org/):
```sh
pacman -S mingw-w64-ucrt-x86_64-sfml

▶️ Build & Run
Compile
g++ -std=c++17 tictactoe.cpp -o tictactoe -lsfml-graphics -lsfml-window -lsfml-system

Run
./tictactoe

