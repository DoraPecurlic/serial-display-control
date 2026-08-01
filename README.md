# serial-display-control

![MCU](https://img.shields.io/badge/MCU-STM32F401RE-0072C6)
![Display](https://img.shields.io/badge/Display-SSD1306%20OLED-00ACC1)
![C](https://img.shields.io/badge/Language-C-2EA44F)
![Python](https://img.shields.io/badge/Language-Python-3776AB)
![UART](https://img.shields.io/badge/Interface-UART-F97316)
![I2C](https://img.shields.io/badge/Interface-I2C-8B5CF6)
![Status](https://img.shields.io/badge/Status-Completed-brightgreen)

A modular desktop-to-embedded application for displaying text and controlling visual effects on an SSD1306 OLED through a Python terminal and UART communication.

The Python host application acts as the command and communication layer, while the STM32 firmware parses requests and executes display operations. 
This separation keeps user interaction, protocol handling and hardware control independent and easy to extend.

The project implements a custom application-layer serial protocol between the Python host application and the STM32 firmware. 
Python translates user input into structured text or command requests and sends them over UART. 
The STM32 parses each request, executes the corresponding display operation and returns an explicit success or error response.

---

## Features

### Display Control

- Display user-entered text in static mode
- Clear the OLED through a terminal command
- Scroll the currently displayed text to the left or right
- Blink the displayed text
- Stop the active effect and restore the static text
- Automatically stop the previous effect when new text is entered
- Exit and close serial connection through command

### Communication and Reliability

- Interactive Python terminal communicating with the STM32 over UART
- Custom application-layer protocol designed for communication between Python and STM32
- Explicit OK response for successfully executed requests
- Descriptive ERROR: responses for invalid requests

---

## Software Architecture

- Object-oriented Python host application
- Modular STM32 firmware written in C
- Clear separation between: user input, application logic, protocol handling, serial transport and hardware control

### Python host application

| Component | Responsibility |
| --- | --- |
| `ConsoleApp` | Runs the interactive terminal session and collects user input |
| `CommandParser` | Determines whether the user input is text to display or a command that begins with `:` |
| `ApplicationController` | Coordinates parsed input and display actions |
| `DisplayClient` | Exposes high-level operations such as showing text, blinking and stopping effects |
| `SerialProtocol` | Converts high-level operations into wire-protocol messages and validates responses |
| `SerialConnection` | Owns the serial-port connection through PySerial |

### STM32 firmware

| Module | Responsibility |
| --- | --- |
| `uart_input` | Receives messages over UART |
| `serial_protocol` | Parses text and command requests |
| `request_handler` | Maps valid protocol requests to display operations |
| `display_controller` | Manages text, active display mode and effect timing |
| Extended SSD1306 driver | Sends low-level commands and framebuffer data over I2C |

### Request Flow

- The user enters plain text or a command in the Python terminal
- ConsoleApp collects the input and forwards it to ApplicationController
- CommandParser parses the input as either text to display or a command prefixed with :
- ApplicationController selects the appropriate operation exposed by DisplayClient.
- Python SerialProtocol encodes the operation as a structured protocol request, such as TEXT:Hello World or CMD:SCROLL_LEFT
- SerialConnection sends the complete request to the STM32 over UART
- The firmware uart_input module receives and buffers incoming characters until the complete message is available
- The STM32 serial_protocol module parses the message and identifies the request type and payload
- If the request is valid, request_handler maps it to the appropriate DisplayController operation
- DisplayController updates the stored text or active display mode and calls the SSD1306 driver when the OLED content must change
- After processing the request, the firmware returns OK or a descriptive ERROR: response over UART



## User Commands

| Input | Behaviour |
| --- | --- |
| `Hello World` | Displays the entered text in static mode |
| `:clear` | Clears the OLED |
| `:scroll left` | Scrolls the currently displayed text to the left |
| `:scroll right` | Scrolls the currently displayed text to the right |
| `:blink` | Starts blinking the currently displayed text |
| `:stop` | Stops the active effect and restores the static text |
| `exit` | Closes the Python application and serial connection |

Entering new plain text always stops the previous effect and returns the display to static mode.

---

## Hardware

- STM32 NUCLEO-F401RE development board
- [Soldered OLED I2C Display 0.96-inch SSD1306](https://soldered.com/products/display-oled-i2c-white-0-96-ssd1306)
- Four jumper wires

### OLED Connections

| OLED pin | NUCLEO-F401RE connection |
| --- | --- |
| `VCC` | `3.3V` |
| `GND` | `GND` |
| `SCL` | I2C1 SCL (`PB8` / Arduino `D15`) |
| `SDA` | I2C1 SDA (`PB9` / Arduino `D14`) |

## Software Requirements

- STM32CubeIDE
- STM32Cube HAL for the STM32F4 family
- Python 3
- PySerial
- ST-LINK USB driver

The project uses [afiskon STM32 SSD1306 library](https://github.com/afiskon/stm32-ssd1306) and extends it using [SSD1306 controller datasheet](https://cdn-shop.adafruit.com/datasheets/SSD1306.pdf)

---

## Project Structure

```text
serial-display-control/
├── firmware/
│   ├── Core/
│   │   ├── Inc/
│   │   │   ├── display_controller.h
│   │   │   ├── request_handler.h
│   │   │   ├── serial_protocol.h
│   │   │   └── uart_input.h
│   │   └── Src/
│   │       ├── display_controller.c
│   │       ├── main.c
│   │       ├── request_handler.c
│   │       ├── serial_protocol.c
│   │       └── uart_input.c
│   ├── Drivers/
│   │   └── SSD1306/
│   │       ├── Inc/
│   │       └── Src/
│   └── firmware.ioc
├── host_app/
│   ├── application_controller.py
│   ├── command.py
│   ├── command_parser.py
│   ├── console_app.py
│   ├── display_client.py
│   ├── main.py
│   ├── serial_connection.py
│   └── serial_protocol.py
├── .gitignore
└── README.md
```

---

## Running the Project

1. Clone the repository.
2. Connect the OLED and the NUCLEO-F401RE board.
3. Open the firmware project in STM32CubeIDE.
4. Build and flash the firmware.

Prepare the Python environment:

``` bash 
cd host_app 
python -m venv .venv 
source .venv/Scripts/activate 
python -m pip install pyserial 
```
Set the correct COM port in main.py:

```bash python main.py ```

Close any other application using the same port, then run:

```bash python main.py ```

---

## Author

Developed by Dora Pečurlić