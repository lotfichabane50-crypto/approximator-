# The one and only Approximator
## Coded by Lotfi Chabane, Pierre Paquet-Deom, Arthur Prost and Luna Dal Molin
## Project Overview

This project is a short group project based on an imaginary calculator made with space materials.

The calculator is built with an Arduino board and several electronic components. It can perform basic calculations, but it also contains several unexpected modes and animations inspired by movies, games and pop culture.

The goal of the project was to create a fun and interactive calculator while working with Arduino programming and electronic components.

## Features

The calculator can:

* Perform basic additions, subtractions, multiplications and divisions.
* Display information on a 16x2 LCD screen.
* Use a 4x4 keypad to enter calculations.
* Use LEDs to create visual effects.
* Use a buzzer for sounds and melodies.
* Include several hidden modes and Easter eggs.
* Simulate a bomb activation and defusing sequence.
* Display random messages and results.

## Hardware

The project uses:

* Arduino board
* 16x2 LCD screen
* 4x4 keypad
* 5 LEDs
* Buzzer
* Connecting wires

The LCD is connected using the I2C interface. The keypad is used to enter numbers and operators, while the LEDs and buzzer provide visual and audio feedback.

## Libraries

The project uses the following Arduino libraries:

* `BitBang_LiquidCrystal_I2C`
* `Keypad`

These libraries are required for the LCD screen and keypad to work correctly.

## How It Works

When the calculator starts, the LCD displays:

`Calcul [*=Envoi]:`

Numbers can be entered using the keypad.

The keypad uses the following operators:

* `A` → Addition (`+`)
* `B` → Subtraction (`-`)
* `C` → Multiplication (`*`)
* `D` → Division (`/`)
* `*` → Validate the calculation
* `#` → Reset the calculator

The calculator supports calculations using two numbers and one operator.

After validation, the calculator displays the result or activates one of its special behaviours.

## Special Modes and Easter Eggs

The calculator contains several hidden features.

### James Bond Mode

Entering `007` activates a James Bond themed mode and plays a melody using the buzzer.

### Hacker Mode

Entering a sequence ending with:

`+-*/`

activates the hacker animation.

The LCD displays random characters, the LEDs flash randomly and the buzzer plays random sounds for several seconds.

### CSGO Bomb Mode

Entering:

`7355608`

activates a bomb simulation.

A countdown appears on the LCD and the LEDs and buzzer are activated.

The bomb can be defused by holding the `#` key for several seconds.

If the bomb is not defused before the countdown ends, an explosion animation is displayed.

### Random Results

Some calculations can produce unexpected results or random messages. These messages include references to different characters, brands and pop culture elements.

## Installation

1. Install the Arduino IDE.
2. Connect the Arduino board to the computer.
3. Install the required libraries.
4. Open `Approximator.cpp` in the Arduino IDE.
5. Connect the LCD, keypad, LEDs and buzzer according to the pin configuration in the code.
6. Select the correct Arduino board and port.
7. Upload the program to the Arduino board.

## Usage

After uploading the program:

1. Turn on the Arduino.
2. Enter a calculation using the keypad.
3. Press `*` to validate it.
4. Press `#` to reset the calculator.
5. Try the special sequences to discover the hidden modes.

## Project Structure

```text
Project/
│
├── Approximator.cpp
├── boite_approximator.stl
├── couvercle_boitier.stl
└── README.md
```

* `Approximator.cpp` → Complete Arduino program.
* `boite_approximator.stl` → 3D model of the calculator case.
* `couvercle_boitier.stl` → 3D model of the case cover.
* `README.md` → Project documentation.

The main objective was to combine programming, electronics and creativity to create an interactive imaginary calculator.
