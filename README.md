<div align="center">

```
███████╗███╗   ██╗ █████╗ ██╗  ██╗███████╗
██╔════╝████╗  ██║██╔══██╗██║ ██╔╝██╔════╝
███████╗██╔██╗ ██║███████║█████╔╝ █████╗  
╚════██║██║╚██╗██║██╔══██║██╔═██╗ ██╔══╝  
███████║██║ ╚████║██║  ██║██║  ██╗███████╗
╚══════╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝

 ██████╗  █████╗ ███╗   ███╗███████╗
██╔════╝ ██╔══██╗████╗ ████║██╔════╝
██║  ███╗███████║██╔████╔██║█████╗  
██║   ██║██╔══██║██║╚██╔╝██║██╔══╝  
╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗
 ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝
```

<br>

<img src="https://img.shields.io/badge/Language-C++-blue?style=for-the-badge">
<img src="https://img.shields.io/badge/Platform-Windows%20Console-green?style=for-the-badge">
<img src="https://img.shields.io/badge/Architecture-Procedural-orange?style=for-the-badge">
<img src="https://img.shields.io/badge/Rendering-Real--Time-success?style=for-the-badge">

# 🐍 Console Based Snake Game in C++

### ⚡ A classic arcade Snake Game built in terminal using arrays, loops, collision detection, and real-time keyboard controls.

<img src="https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=24&pause=1000&color=36BCF7&center=true&vCenter=true&width=700&lines=Real-Time+Console+Game+Engine;Array-Based+Snake+Logic;Smooth+Rendering+Loop;Collision+Detection+System" />

</div>

---

## 📖 About The Project

This project is a **console-based implementation of the classic Snake Arcade Game** developed in **C++** using procedural programming fundamentals.

The game executes entirely inside the terminal and demonstrates:

* ⚡ Real-time keyboard event handling
* 🎮 Frame-based rendering loop
* 🐍 Snake body movement using arrays
* 🍎 Random food generation
* 💥 Collision detection (wall + self)
* 📊 Score tracking and HUD display
* 🔁 Restart and exit controls

> No external libraries — pure system-level programming.

---

## 🎮 Live Gameplay Preview

<p align="center">
  <picture>
    <source media="(prefers-color-scheme: dark)" srcset="https://raw.githubusercontent.com/arya-dev2005/Snake-Game/output/github-snake-dark.svg" />
    <source media="(prefers-color-scheme: light)" srcset="https://raw.githubusercontent.com/arya-dev2005/Snake-Game/output/github-snake.svg" />
    <img alt="github-snake" src="https://raw.githubusercontent.com/arya-dev2005/Snake-Game/output/github-snake.svg" />
  </picture>
</p>

---

## ✨ Key Features

| Feature | Description |
|---------|-------------|
| 🎯 Real-Time Input | Uses `_kbhit()` and `_getch()` for non-blocking keyboard capture |
| 🐍 Dynamic Snake Growth | Snake length increases after consuming food |
| 🍎 Random Food Logic | Food spawns randomly within board boundaries |
| 💥 Collision Engine | Detects self-hit and wall-hit conditions |
| 📊 HUD Display | Live score, length, controls, objective shown on top |
| 🔁 Restart Option | Allows replay after Game Over |
| 🎨 Console Styling | Colored borders and terminal UI enhancement |

---

## 🧠 Core Concepts

### Snake Representation

```cpp
int snakeX[MAX_LENGTH], snakeY[MAX_LENGTH];
```

### Game Loop

```cpp
while (!gameOver)
{
    handleInput();
    update();
    draw();
    Sleep(SPEED_MS);
}
```

### Collision Detection

* Boundary checks
* Self overlap detection
* Food consumption → growth

---

## ⚙️ Installation & Execution

### Clone Repository

```bash
git clone https://github.com/arya-dev2005/Snake-Game.git
```

### Enter Folder

```bash
cd Snake-Game
```

### Compile

```bash
g++ snake_game.cpp -o snake_game
```

### Run

```bash
snake_game.exe
```

---

## 🎮 Controls

| Key   | Action     |
| ----- | ---------- |
| W / ↑ | Move Up    |
| S / ↓ | Move Down  |
| A / ← | Move Left  |
| D / → | Move Right |
| Q     | Quit       |
| R     | Restart    |

---

## 🧱 Project Structure

```
Snake-Game/
│── snake_game.cpp
│── README.md
│── snake_preview.png
│── .github/
│   └── workflows/
│       └── snake.yml
```

---

## ⚡ Technical Highlights

* Efficient array-based snake movement
* Non-blocking input handling
* Flicker-free rendering using cursor control
* Clean procedural design architecture

---

## 🚀 Future Improvements

* 🎨 Themes / color modes
* 🔊 Sound effects
* 🧠 AI Snake mode
* 🌐 Cross-platform support
* 🧩 OOP-based refactor

---

## 🤝 Contributing

Pull requests are welcome.
For major changes, please open an issue first.

---

## 📜 License

This project is open-source under the **MIT License**.

---

<div align="center">

### ⭐ If you like this project, give it a star!

</div>
