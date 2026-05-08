# Snake Game — STM32F407VG Discovery Kit

A fully playable Snake game running on bare-metal STM32F407VG, 
written in C. Built as an embedded systems assignment and 
completed in a single session to return borrowed hardware 
on time.

## Hardware
- Board: STM32F407VG Discovery Kit
- Display: 128x64 GLCD (KS0108 controller via GPIOE)
- Input: 5 directional buttons (UP/DOWN/LEFT/RIGHT/MID)
- Audio: Buzzer on PA8 for food collection and game over jingle

## Button Pin Mapping
| Direction | Port | Pin |
|-----------|------|-----|
| UP        | PC   | 4   |
| DOWN      | PA   | 14  |
| LEFT      | PA   | 13  |
| RIGHT     | PB   | 1   |
| MID       | PC   | 5   |

## Features
- Smooth snake movement at ~30fps (33ms loop delay)
- Collision detection for walls and self
- Random food spawning within bounds
- Score tracking (+10 per food)
- Audio feedback on food collection and game over
- HEX file included for direct flashing via STM32CubeProgrammer

## Technical Notes
- Input handled via polling — interrupt-based input was 
  scoped out intentionally to meet the submission deadline
- Main menu and score display were planned but deprioritized 
  in favor of core gameplay

## Getting Started
Flash `snake.hex` directly using STM32CubeProgrammer, 
or build from source using MikroC for ARM.
