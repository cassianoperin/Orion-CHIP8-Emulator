# ORION CHIP-8 Emulator

CHIP-8 emulator written in C with Nuklear gui library.

**Main Emulator** | **CHIP-8 Pong 2 game**
:-------------------------:|:-------------------------:
<img width="380" alt="main" src="https://github.com/cassianoperin/Orion-CHIP8-Emulator/blob/main/images/Orion-Main.png">  |  <img width="380" alt="pong2" src="https://github.com/cassianoperin/Orion-CHIP8-Emulator/blob/main/images/Orion-Pong2.png">

**Debug Screen**|
:-------------------------:|
<img width="787" alt="debug" src="https://github.com/cassianoperin/Orion-CHIP8-Emulator/blob/main/images/Orion-Debug.png"> |

## CHIP8 Status
* ![100%](https://progress-bar.xyz/100) CPU Opcodes
* ![100%](https://progress-bar.xyz/100) Memory
* ![100%](https://progress-bar.xyz/100) Registers
* ![100%](https://progress-bar.xyz/100) Graphics
* ![100%](https://progress-bar.xyz/100) Qwirks
* ![100%](https://progress-bar.xyz/100) Sound
## CHIP8 HiRes
* ![0%](https://progress-bar.xyz/0) CPU Opcodes
* ![0%](https://progress-bar.xyz/0) Memory
* ![0%](https://progress-bar.xyz/0) Registers
* ![0%](https://progress-bar.xyz/0) Graphics
* ![0%](https://progress-bar.xyz/0) Qwirks
* ![0%](https://progress-bar.xyz/0) Sound
## SCHIP Status
* ![0%](https://progress-bar.xyz/0) CPU Opcodes
* ![0%](https://progress-bar.xyz/0) Memory
* ![0%](https://progress-bar.xyz/0) Registers
* ![0%](https://progress-bar.xyz/0) Graphics
* ![0%](https://progress-bar.xyz/0) Qwirks
* ![0%](https://progress-bar.xyz/0) Sound
## Emulator
* ![100%](https://progress-bar.xyz/100) Pause and resume emulation
* ![100%](https://progress-bar.xyz/100) Reset emulation
* ![100%](https://progress-bar.xyz/100) Color Themes
* ![100%](https://progress-bar.xyz/100) Binary rom format support
* ![100%](https://progress-bar.xyz/100) Hexadecimal rom format support
* ![100%](https://progress-bar.xyz/100) Step Forward CPU Cycles for Debug
* ![100%](https://progress-bar.xyz/100) Increase and Decrease CPU Clock Speed
* ![10%](https://progress-bar.xyz/10) Keyboard remaps
* ![0%](https://progress-bar.xyz/0) Step Back (Rewind) CPU Cycles for Debug
* ![0%](https://progress-bar.xyz/0) Save States
* ![50%](https://progress-bar.xyz/50) Fullscreen
* ![100%](https://progress-bar.xyz/100) Emulation Status from all games I have to test

## EMULATOR Usage

1. Run:

	`$./orion`

2. Keys
- Original COSMAC Keyboard Layout (CHIP-8):

	`1` `2` `3` `C`

	`4` `5` `6` `D`

	`7` `8` `9` `E`

	`A` `0` `B` `F`

- **Keys used in this emulator:**

	`1` `2` `3` `4`

	`Q` `W` `E` `R`

	`A` `S` `D` `F`

	`Z` `X` `C` `V`

	`P` and `ESC`: Pause and Resume emulation

	`5`: Decrease CPU Clock Speed

	`6`: Increase CPU Clock Speed
    
	`9`: Enable / Disable Debug Mode

	`0`: Reset

	`I`: Increase CPU Cycle (in paused mode))


## EMULATOR Build Instructions

### MAC
* Install C:

	`brew install gcc make sdl2 (MAP PACKAGES!!)`

* Compile:

	`make`

* Vscode Setup:

   Install these extensions:

   - C/C++ (Microsoft)

   - Code runner (Jun Han)

   Press F5 to compile and run code.


## Documentation

### Chip-8
[Cowgod's Chip-8 Technical Reference](http://devernay.free.fr/hacks/chip8/C8TECH10.HTM#0.0)

[How to write an emulator (CHIP-8 interpreter) — Multigesture.net](http://www.multigesture.net/articles/how-to-write-an-emulator-chip-8-interpreter/)

[Wikipedia - CHIP-8](https://en.wikipedia.org/wiki/CHIP-8)

[trapexit chip-8 documentation](https://github.com/trapexit/chip-8_documentation)

[Thomas Daley Wiki (Game Compatibility)](https://github.com/tomdaley92/kiwi-8/issues/9)

[David Winter Documentation](http://vanbeveren.byethost13.com/stuff/CHIP8.pdf?i=2)

[Chip-8 Database](https://chip-8.github.io/database/)

[Archive chip8.com](https://web.archive.org/web/20160401091945/http://www.chip8.com/)

[Columbia University - Columbia University](http://www.cs.columbia.edu/~sedwards/classes/2016/4840-spring/designs/Chip8.pdf)

[Tom Swan Documentation](https://github.com/TomSwan/pips-for-vips)

[Chip 8 Instruction Scheduling and Frequency](https://jackson-s.me/2019/07/13/Chip-8-Instruction-Scheduling-and-Frequency.html)


### Superchip (SCHIP)
[HP48 Superchip](https://github.com/Chromatophore/HP48-Superchip)

[SCHIP](http://devernay.free.fr/hacks/chip8/schip.txt)

[Chip-8 Reference Manual](http://chip8.sourceforge.net/chip8-1.1.pdf)


### Other Chip-8 Extensions
[CHIP‐8 Extensions Reference](https://github.com/mattmikolay/chip-8/wiki/CHIP%E2%80%908-Extensions-Reference)

[CHIP‐8 Extensions (Github)](https://chip-8.github.io/extensions/)

[Chip8 Hybrids](https://www.ngemu.com/threads/chip8-thread.114578/page-22/)

[MegaChip](https://github.com/gcsmith/gchip/blob/master/docs/megachip10.txt)


### Emulators

[Octo](https://johnearnest.github.io/Octo/)

[EMMA02 Opcodes Documentation](https://www.emma02.hobby-site.com/pseudo_chip8.html)

### Nuklear
[Nuklear GUI](https://github.com/Immediate-Mode-UI/Nuklear)


### Memory leak testing

Test memory leaks on binary:

`leaks --atExit --list -- main`


## TODO

### Compatibility Tests

1. Test more games (Need SCHIP):

    CHIP-8 Archive - A collection of public domain (CC0) games, all playable online.
    A collection of CHIP-8 programs and documentation - Matt Mikolay's games, programs and documentation.

    https://johnearnest.github.io/chip8Archive/
	https://www.revival-studios.com/other.php
	https://github.com/mattmikolay/chip-8


2. Add result status of known chip-8 test suites and roms

### Improvements

## Emulation

1. Add SCHIP and other extensions

2) Reduce the number of global variables and code cleaning

3) Improve DXYN function (replace the last part by a XOR)

4) Change graphics array to dynamic
	destroy and recreate window after?
	https://stackoverflow.com/questions/3827892/how-can-i-change-the-size-of-an-array-in-c

5) If a rom enter in invalid opcode, enable debug hang the emulator

6) Raus recommendations:

6.1. Replace signature by SHA1
6.2. your 8xy4 is weirdly complex, just calc sum as short or larger, then store the lower 8 bits in v[x] and shift down the 9th bit into vf
so it is NOT allowed to use the vx/vy directly in the draw loop itself, you must make a copy of the coordinates
(unless you only set vf to the amount of collisions at the very end by using another var to hold collision status in the meantime)
--- that commented alternate version's good, if only some work is done to tackle clipping vs wrapping which is basically non-existent right now

6.5 SCHIP -
-  with the exception of 2 or 3 known games that need that original behavior to look right (but not necessary to work right), everything else works fine following the behavior of "modern superchip"
- which is basically a step down from the functionality of xochip with a lot less rules to how it works
-- legacy superchip: always 128x64 resolution, lores coords/draws are doubled (thus why scrolls are half as effective too), dxy0 draws 8x16 sprites, vf will either be 0 or 1. In hires, collisions count per-row (so vf can be > 1), and dxy0 draws 16x16 sprites.
-- modern superchip: resolution is either 64x32 or 128x64 depending on lores/hires respectively. vf collision is only ever 0 or 1. both modes in dxy0 draw 16x16.

https://github.com/janitor-raus/CubeChip/tree/master/test_roms

7) Gulrak:
- Assembly: 
-- https://johnearnest.github.io/Octo/docs/Manual.html
-- https://chip8.gulrak.net/
-- https://groups.google.com/g/comp.sys.hp48/c/e7In51mOgHY
-- https://github.com/rkdud007/solchip8 ???
-- https://github.com/gulrak/chiplet
-  in legacy SCHIP, lores mode is using display wait, while hires is not

8) Disable old C Emulator

10) Upgrade to SDL3

11) Update Nuklear

## GUI

1. Build a "cycle accurate" cpu, with a 12bits address bus and 8 bit data bus for visual representations

2. PAUSE GAME WHEN MENU IS ACTIVE (will fix the draw problem)


## Display

1. Duplicate or triplicate frame buffer to reduce flickering
https://www.reddit.com/r/EmuDev/comments/n9dcli/comment/gxnnzdw/


## Input

1. Add mouse map to control some games like pong


### Problems

1) INPUT: When the first key is pressed, freeze the emulation by a second (with input_keyboard_remaps() enabled). Table and update value? Pointer?

2) display_draw strange in main, review and set @60hz when debug or every cycle
