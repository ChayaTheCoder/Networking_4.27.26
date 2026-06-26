# Networking_4.27.26

### Overview
This folder contains C++ programs demonstrating **TCP client–server communication** using Linux sockets. The examples show how processes exchange data over a network using system calls such as `socket()`, `connect()`, `bind()`, `listen()`, `accept()`, `send()`, and `recv()`.

---

## File Breakdown

### **1. client‑tcp‑4.27.26.cpp**
**Concept:** TCP client implementation  
**What it demonstrates:**
- Creates a socket using `socket(PF_INET, SOCK_STREAM, 0)`
- Connects to a server using `connect()`
- Sends user input to the server with `send()`
- Receives and prints the server’s response using `recv()`
- Gracefully closes the connection with `shutdown()` and `close()`


---

### **2. server‑tcp‑4.27.26.cpp**
**Concept:** TCP server implementation  
**What it demonstrates:**
- Creates a listening socket using `socket()` and `bind()`
- Waits for incoming connections with `listen()` and `accept()`
- Receives client messages using `recv()`
- Processes requests and sends responses with `send()`
- Handles multiple connections sequentially or iteratively


---

### **3. Linux_Processes_Assignment‑1.31.26.cpp**
**Concept:** Process creation and management  
**What it demonstrates:**
- Uses `fork()` to create child processes
- Employs `execvp()` to replace process images
- Synchronizes parent and child execution with `waitpid()`


---

## Compilation
Compile each file using:
```bash
g++ filename.cpp -o filename
