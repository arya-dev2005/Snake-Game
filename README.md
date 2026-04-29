<div align="center">

# 🐍 Console Based Snake Game in C++

### A classic arcade Snake Game built in terminal using arrays, loops, collision detection, and real-time keyboard controls.

<img src="https://readme-typing-svg.herokuapp.com?font=Fira+Code&size=24&pause=1000&color=36BCF7&center=true&vCenter=true&width=700&lines=Classic+Snake+Game+in+CPP%2B%2B;Real-Time+Console+Rendering;Array+Based+Movement+Engine;Collision+Detection+%26+Food+Logic" />

<br>

<img src="https://img.shields.io/github/stars/arya-dev2005/Snake-Game?style=for-the-badge">
<img src="https://img.shields.io/github/forks/arya-dev2005/Snake-Game?style=for-the-badge">
<img src="https://img.shields.io/github/repo-size/arya-dev2005/Snake-Game?style=for-the-badge">
<img src="https://img.shields.io/github/last-commit/arya-dev2005/Snake-Game?style=for-the-badge">

<br><br>

<img src="https://img.shields.io/badge/Language-C++-blue?style=for-the-badge">
<img src="https://img.shields.io/badge/Platform-Windows%20Console-green?style=for-the-badge">
<img src="https://img.shields.io/badge/Type-Arcade%20Game-orange?style=for-the-badge">
<img src="https://img.shields.io/badge/Status-Completed-success?style=for-the-badge">

</div>

---

## 📖 About The Project

This project is a **console-based implementation of the classic Snake Arcade Game** developed in **C++** using procedural programming fundamentals.

The game executes entirely inside the terminal and demonstrates:

- real-time keyboard event handling,
- frame-based rendering,
- snake body movement using arrays,
- random food generation,
- score management,
- wall and self collision detection,
- restart and quit controls.

It is a strong beginner-to-intermediate systems programming project that builds confidence in low-level game logic without external graphics libraries.

---

## 🎮 Live Gameplay Preview

<p align="center">
  <img src="snake_preview.png" width="900">
</p>

---

## 🐍 GitHub Contribution Snake

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

## 🧠 Core Programming Concepts Used

### ✅ Arrays for Snake Body Coordinates

```cpp
int tailX[100], tailY[100];