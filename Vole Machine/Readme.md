# Vole Machine Simulation

## 📌 Overview  
This program simulates a **Vole Machine**, a basic computational model used to execute custom command files. It allows users to load a program, execute it, and display memory state.  
---
## 🔥 Features  
- Load a program from a text file  
- Execute commands sequentially  
- Display memory and execution state  
---
## 🛠️ Setup & Compilation  
### 1️⃣ **Clone the repository**  
```bash
git clone https://github.com/Mohannad141/My-Work/tree/main/Vole%20Machine
cd VoleMachine
```
2️⃣ Compile the program
```
g++ -o vole_machine main.cpp volemachine.cpp -std=c++11
```

3️⃣ Run the program
```
./vole_machine
```
---

### How to Use

1️⃣ Run the program and choose an option from the menu:

Welcome to our Vole Machine
1) Read file and load program
2) Execute program
3) Display Data
4) Exit
Enter your choice: 

2️⃣ To load a program, enter a valid text file name.
3️⃣ To execute the program, select option 2.
4️⃣ To view machine memory, choose option 3.

Example Program File (commands.txt):
```
2001
2102
2203
2304
A302
C000
```
