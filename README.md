# CHIP-8 GUI with Nuklear

Port of chip8 emulator to use nuklear GUI.

## Improvements
1) Test games again (quirks and tests)
2) Update Nuklear and Framework to check if mouse missing problem is fixed
3) Create a way to show Emulator Information
4) Add a Pause popup on screen
5) Insert the name of game loaded in the status bar OR window
6) Reduce the number of global variables

## Problems

* INPUT: When the first key is pressed, freeze the emulation by a second
* Emulation -> Reset bagunça pause e cores
* Cycles per second locked to 60 when quirk_display_wait is ENABLED
* Unify the PAUSE function with all requirements
* Breakout Camelo Cortez quirk problem ingame

* ESC no load_rom está deixando o statusbar na tela até próximo draw - FIXED
* Problema no ESC -> LOAD ROM 2x, na segunda o fica com o tema do pause - FIXED


hide emulation reset menu before rom is loaded

button 0 (reset berak everything)

remove keyboard shortcuts?