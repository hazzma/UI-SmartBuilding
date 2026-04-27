# SmartBuildingUI Library

A driver-agnostic UI library for Smart Building HMI applications. Built on top of a `DisplayEngine` Hardware Abstraction Layer (HAL).

## Features
- **Driver-Agnostic**: Easily switch between `TFT_eSPI`, `LovyanGFX`, or any other driver by implementing a simple adapter.
- **Modern Aesthetics**: Premium dark-mode design with rounded cards, smooth gradients, and clean typography.
- **Virtual Keyboard**: Built-in interactive QWERTY keyboard for data entry.
- **Decoupled Logic**: Uses event callbacks to separate UI interaction from application logic (WiFi, LAN, etc.).

## Installation (PlatformIO)
Add the following to your `platformio.ini`:
```ini
lib_deps =
    hazzma/SmartBuildingUI
```

## Usage
1. Initialize the `DisplayEngine` adapter.
2. Define `UIEventCallbacks`.
3. Call `screens_init(callbacks)`.
4. Run `screens_render(state, fps)` in your UI task.

## License
MIT
