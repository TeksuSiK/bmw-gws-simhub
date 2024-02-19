## BMW F-Series Gear Lever

## Supported games
- Euro Truck Simulator 2

## Installation
- Clone this repository
- Open project as PlatformIO project
- Upload code to board
- Select board in SimHub as custom serial device (You must enable this plugin in settings first), set baudrate to 115200 and paste custom protocol

## Configuration
- Upload code to board with CONFIGURATION_MODE set to true in include/configuration.h
- Select board in SimHub as custom serial device (You must enable this plugin in settings first), set baudrate to 115200 and paste custom protocol
- Run Euro Truck Simulator 2 and set following settings:
- Gameplay:
  - Tranmission: Real Automatic
- Gamepads:
  - Controls: (Your setup) + Arduino
  - Automatic gearbox Drive: Push selector down from N
  - Automatic gearbox Reverse: Push selector up from N
- Return to game and engage D on selector
- Keybinds:
  - Shift to neutral: Shift up from D
  - Gearbox switch Automatic/Sequential: Push sideways from D
  - Shift up: Push down selector
  - Shift down: Push up selector
- Set CONFIGURATION_MODE to false in include/configuration.h and upload code to board

## Video
[![Video](https://img.youtube.com/vi/_xLUNnK0lww/maxresdefault.jpg)](https://www.youtube.com/watch?v=_xLUNnK0lww)

## Credits
- [OpenInverter.org Wiki](https://openinverter.org/wiki/BMW_F-Series_Gear_Lever) for CAN messages

## Check out my other projects
- [BMW E87 Cluster](https://github.com/TeksuSiK/e87-cluster-simhub)
- [BMW E46 Cluster](https://github.com/TeksuSiK/e46-cluster-simhub)