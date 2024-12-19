# StateMachine_CAN
### README: CAN-Based Multi-ECU System with State Machine Control

---

#### **Project Overview**
This project demonstrates a two-ECU system using a CAN (Controller Area Network) communication protocol, where:
- **ECU1** acts as the controller for the state machines.
- **ECU2** executes the output of the state machine based on commands received from ECU1.

The application adheres to a layered architecture and configurable OS design to ensure modularity, scalability, and maintainability. It includes robust error handling and functionality for switch debouncing.

---

#### **Functional Description**
1. **ECU1 Features**:
   - **State Machine Control**:
     - Reads onboard switches SW1 and SW2.
     - Sends CAN messages every 50 ms to ECU2, specifying the desired state.
     - Controls the state transitions of ECU2:
       - SW1: Move to the next state (clockwise) every 1000 ms.
       - SW2: Move to the next state (anticlockwise) every 1000 ms.
       - Both pressed: Reset state to the initial state (RED).
       - No switch activity for 10 seconds: Command ECU2 to enter IDLE state (WHITE).
   - **UART Communication**:
     - Sends state change messages to a PC, indicating:
       - Current state of ECU2.
       - Any error messages received from ECU2.

2. **ECU2 Features**:
   - **CAN Command Execution**:
     - Processes commands from ECU1 every 10 ms.
     - Executes state transitions and controls outputs (LEDs, LCD) based on the received state.
   - **State Display**:
     - Displays "IDLE" on an LCD for 2 seconds when commanded to IDLE by ECU1.

3. **System Timing**:
   - No delays are used; all timing is managed by the OS.
   - Configurable timing intervals:
     - CAN message sending: 50 ms.
     - State transitions: 1000 ms.
     - Timeout to IDLE: 10 seconds.

4. **Error Handling**:
   - Handles communication errors (e.g., missing CAN messages).
   - Reports errors to ECU1 and displays appropriate messages on the PC via UART.

5. **Architecture**:
   - **Layered Design**:
     - Drivers, OS, services, and application layers are modular and follow a configuration-based approach.
   - **Configuration Concept**:
     - Each module has its own `cfg.h` and `cfg.c` files.
   - State machines reside strictly in the application layer to avoid architectural violations.

---

#### **State Machine Overview**
The state machine consists of the following states:
- **RED** (Initial State)
- **GREEN**
- **BLUE**
- **WHITE** (IDLE)

**State Transitions**:
- **Clockwise**: SW1 pressed → Next state every 1000 ms.
- **Anticlockwise**: SW2 pressed → Previous state every 1000 ms.
- **Reset**: Both SW1 and SW2 pressed → Return to RED.
- **Timeout**: No switch activity for 10 seconds → Go to IDLE (WHITE).

---

#### **Project Structure**
```
Project Root
├── ECU1/
│   ├── main.c                 # Main application logic for ECU1
│   ├── can_driver.c/.h        # CAN driver for ECU1
│   ├── uart_driver.c/.h       # UART driver for ECU1
│   ├── app_state_machine.c/.h # State machine logic for ECU1
│   ├── cfg/                   # Configuration files for ECU1
│   │   ├── can_cfg.c/.h
│   │   ├── uart_cfg.c/.h
│   │   └── os_cfg.c/.h
│   └── os/                    # OS layer for ECU1
│       ├── os.c/.h
│       └── timer.c/.h
├── ECU2/
│   ├── main.c                 # Main application logic for ECU2
│   ├── can_driver.c/.h        # CAN driver for ECU2
│   ├── lcd_driver.c/.h        # LCD driver for ECU2
│   ├── app_state_machine.c/.h # State machine logic for ECU2
│   ├── cfg/                   # Configuration files for ECU2
│   │   ├── can_cfg.c/.h
│   │   ├── lcd_cfg.c/.h
│   │   └── os_cfg.c/.h
│   └── os/                    # OS layer for ECU2
│       ├── os.c/.h
│       └── timer.c/.h
├── shared/
│   ├── can_protocol.c/.h      # Shared CAN protocol definitions
│   └── common_utils.c/.h      # Shared utility functions
├── README.md                  # Project documentation
└── LICENSE                    # License information
```

---

#### **Build and Run**
1. **Dependencies**:
   - A compiler supporting C99 or later.
   - CAN communication tools (e.g., Vector CANoe or USB-to-CAN interfaces).
   - An LCD module connected to ECU2.

2. **Build Instructions**:
   - Use a compatible IDE (e.g., Keil, IAR, or STM32CubeIDE) or CLI tools (e.g., `gcc`, `make`).
   - Configure `cfg.h` files for specific hardware and timing requirements.

3. **Run Instructions**:
   - Flash the compiled binaries to the respective ECUs.
   - Connect ECU1 to a PC via UART for status monitoring.
   - Connect both ECUs via a CAN bus.

4. **Testing**:
   - Press SW1 or SW2 on ECU1 and observe the LED states on ECU2.
   - Check the UART messages on the PC for real-time updates and error reports.

---

#### **Key Notes**
- Ensure **switch debouncing** is correctly implemented to avoid false triggers.
- Error handling is integrated across all layers for reliability.
- Follow the **configuration concept** strictly to maintain modularity and scalability.

---

#### **License**
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

---

Feel free to adapt and extend this project for additional functionalities or use in other CAN-based systems.
