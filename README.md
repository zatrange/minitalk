# minitalk

> A small client-server communication program using UNIX signals — 42 School Project.

---

## 📋 Table of Contents

- [About](#about)
- [How It Works](#how-it-works)
- [Getting Started](#getting-started)
- [Usage](#usage)
- [Bonus Features](#bonus-features)
- [Examples](#examples)
- [Allowed Functions](#allowed-functions)
- [Norm Compliance](#norm-compliance)

---

## About

`minitalk` is a 42 School project that implements a basic data exchange program between a **client** and a **server** using only **UNIX signals** — specifically `SIGUSR1` and `SIGUSR2`.

The server is launched first and prints its **PID**. The client then takes that PID and a string as arguments and sends the string to the server **bit by bit** using signals. The server reconstructs the message and prints it.

---

## How It Works

Since only two signals are available, each character is encoded **bit by bit**:

- `SIGUSR1` → bit `0`
- `SIGUSR2` → bit `1`

Each ASCII character is 8 bits, so sending one character requires **8 signals**. The server accumulates bits, reconstructs each byte, and prints the full string once a null terminator (`\0`) is received.

```
Client                        Server
  |                              |
  |--- SIGUSR1 (bit 0) -------->|
  |--- SIGUSR2 (bit 1) -------->|
  |--- SIGUSR2 (bit 1) -------->|  → reconstructs char by char
  |--- SIGUSR1 (bit 0) -------->|
  |           ...               |
  |--- null terminator -------->|  → prints full message
```

---

## Getting Started

### Prerequisites

- GCC or Clang compiler
- GNU Make
- A Unix-based system (Linux / macOS)

### Installation

**Clone the repository:**
```bash
git clone https://github.com/your_username/minitalk.git
cd minitalk
```

**Compile mandatory part:**
```bash
make
```

**Compile with bonus:**
```bash
make bonus
```

This generates two executables: `server` (or `server_bonus`) and `client` (or `client_bonus`).

**Clean object files:**
```bash
make clean
```

**Remove all compiled files:**
```bash
make fclean
```

**Recompile from scratch:**
```bash
make re
```

---

## Usage

### Step 1 — Launch the server

```bash
./server
```

The server will display its **PID** and wait for incoming signals:

```
Server PID: 12345
```

### Step 2 — Send a message from the client

```bash
./client <SERVER_PID> "<MESSAGE>"
```

**Example:**
```bash
./client 12345 "Hello, 42!"
```

The server will then print:
```
Hello, 42!
```

---

## Bonus Features

The bonus part extends the base project with two key additions:

### ✅ Acknowledgment Signal

After the server successfully receives and reconstructs each character, it sends back a **SIGUSR1** signal to the client as an acknowledgment (ACK). The client waits for this ACK before sending the next character, ensuring **reliable, synchronized communication** with no lost signals.

```
Client          Server
  |                |
  |-- 8 signals -->|   (sends one character)
  |<-- SIGUSR1 ----|   (server ACKs reception)
  |-- 8 signals -->|   (sends next character)
  |      ...       |
```

### ✅ Unicode Support

The bonus version supports **Unicode characters** (UTF-8 multibyte sequences), allowing the client to send strings containing emojis and non-ASCII characters.

```bash
./client_bonus 12345 "Hello 🌍"
./client_bonus 12345 "こんにちは"
./client_bonus 12345 "مرحبا"
```

---

## Examples

### Mandatory

```bash
# Terminal 1
./server
# → Server PID: 48271

# Terminal 2
./client 48271 "Minitalk works!"
# → Server prints: Minitalk works!
```

### Bonus

```bash
# Terminal 1
./server_bonus
# → Server PID: 48271

# Terminal 2
./client_bonus 48271 "Hello 🚀 from 42!"
# → Server prints: Hello 🚀 from 42!
# → Client prints: Message successfully delivered!
```

---

## Allowed Functions

| Function        | Description                                      |
|-----------------|--------------------------------------------------|
| `write`         | Write to file descriptor                         |
| `ft_printf`     | Your own printf (if allowed by your school)      |
| `signal`        | Set a signal handler (simple, not recommended)   |
| `sigaction`     | Set a signal handler (robust, recommended)       |
| `kill`          | Send a signal to a process                       |
| `getpid`        | Get the current process PID                      |
| `malloc`/`free` | Memory management                                |
| `pause`         | Suspend process until a signal is received       |
| `sleep`         | Sleep for a number of seconds                    |
| `usleep`        | Sleep for a number of microseconds               |
| `exit`          | Exit the program                                 |

> 💡 `sigaction` is strongly preferred over `signal` as it provides more control and is more portable.

---

## Norm Compliance

This project follows the **42 Norm** (v3):

- No `for` loops — only `while`
- Maximum **25 lines** per function
- Maximum **5 functions** per file
- No global variables except for signal handlers (one per program is tolerated)
- No forbidden functions outside the allowed list above


