# 🎰 Console Slot Machine Simulator

A fully functional console-based slot machine simulator written in C++.

This project was developed during my first month at Euro Games Technology (EGT) 
as a practical exploration of slot game mechanics, payout evaluation, and bonus systems.

---

## 📌 Features

### 🎲 Core Game Logic
- Configurable payout table
- Multiple paylines evaluation
- Win calculation based on symbol combinations
- Scatter symbol detection across reels

### 🎁 Bonus System
- Triggered when 3 or more scatter symbols appear
- Separate bonus game mode

### 🎯 Gamble Feature
- Red/Black double-or-nothing mechanic
- Risk/reward decision flow
- Random outcome generation

### 📊 Information Panel
- Display of game rules
- Payout explanation

### 🛠 Developer Mode
- Demo mode for deterministic testing
- Hardcoded reel outcomes
- Controlled scenarios for verifying:
  - Line evaluation
  - Scatter triggers
  - Bonus activation
  - Gamble mechanics

---

## 🏗 Architecture Overview

The project follows a structured design separating:

- Game state management
- Reel generation logic
- Payline evaluation
- Payout calculation
- Random number generation
- Testing override mechanisms

This separation allows:
- Easier debugging
- Deterministic testing
- Extensibility for new features

---

## 🧠 Concepts Implemented

- 2D matrix symbol evaluation
- Payline mapping algorithms
- Scatter-based bonus triggering
- Randomized event handling
- Deterministic test injection
- Basic casino game mathematics

---

## ▶ How To Run

1. Clone the repository:
   git clone https://github.com/AlexanderSpiridonovv/Console-Slot-Machine
2. Complie:
   g++ main.cpp -o slot
3. Run:
   ./slot

---

## 👨‍💻 Author

Alexander Spiridonov
