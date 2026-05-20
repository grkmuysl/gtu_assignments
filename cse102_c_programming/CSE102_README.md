# 💻 CSE 102 — Computer Programming

**Gebze Technical University — Computer Engineering Department**  
**Spring 2024**

---

## 🧑‍💻 About

This repository contains my homework assignments for the **CSE 102 — Computer Programming** course at Gebze Technical University. All implementations are written in **C (ANSI C)** and cover a wide range of fundamental programming concepts, from basic I/O and file handling to recursion, structs, and 2D arrays.

---

## 🛠️ Technologies & Tools

| Tool | Details |
|------|---------|
| Language | C (ANSI C standard) |
| Compiler | GCC 11.4.0 |
| Compile Command | `gcc --ansi your_program.c -o your_program` |
| OS | Linux (Ubuntu recommended) |

---

## 📂 Repository Structure

```
CSE102-Homeworks/
├── PA1/    → Caesar Cipher — Encrypt & Decrypt C Code
├── PA2/    → Basic AI Classifier — 2D Separator Model
├── PA3/    → ECTS Board Game — Terminal Grid Game
├── PA4/    → Student & Instructor Query System (File I/O)
├── PA5/    → Space Mission News Reader & Key Decryptor
├── PA6/    → Histogram Drawer & Statistics Calculator
├── PA7/    → Mancala Board Game
├── PA8/    → Scientist Database + Pattern Matching
├── PA9/    → Botanist Forest Explorer (Recursive)
├── PA10/   → Assembly Language Simulator
├── PA11/   → Recursive Path Finder, Hospital Planner & Card Shuffler
└── README.md
```

---

## 📝 Assignments

### PA1 — Caesar Cipher: Encrypt & Decrypt C Code
**Due:** March 11, 2024 | **Topic:** File I/O, Characters, Caesar Cipher

Implemented two separate programs to encrypt and decrypt valid C source code using a Caesar cipher.

**Key features:**
- Encryption: reads C code, skips comments inside `/* */` and replaces them with a `@n` marker, encrypts all other characters using a custom 61-character alphabet
- Decryption: reverses the process, restoring encrypted text and reconstructing comment markers
- Key is derived from the student ID by repeatedly summing digits until a single digit remains
- Input/output via file redirection: `./hw < input.txt > encrypted.txt`

**Allowed libraries:** `stdio.h` only

---

### PA2 — Basic AI Classifier: 2D Separator Model
**Due:** March 13, 2024 | **Topic:** Loops, File I/O, Selection Statements, Basic ML concept

Implemented a simple 2D binary classifier that learns separator coordinates from a dataset.

**Key features:**
- Part 1: reads `data.txt`, finds min/max X and Y per class
- Part 2: brute-force searches all integer X/Y separator pairs to minimize classification error; divides 2D space into 4 regions (R1–R4)
- Part 3: tests trained model on `test.txt`, prints predictions and success rate
- Part 4: interactive menu (Explore / Train / Test / Exit)

**Restrictions:** No arrays, no user-defined functions

---

### PA3 — ECTS Board Game
**Due:** March 20, 2024 | **Topic:** 1D Arrays, Functions, Terminal Game

Built a terminal-based board game on a 16×16 grid simulating a student's academic journey.

**Key features:**
- Player `P` starts at center, navigates with W/A/S/D keys
- Two square walls represent Year 1 and Year 2 boundaries
- Collecting `1` objects grants ECTS; player needs ≥32 ECTS to pass Wall 1, ≥24 more for Wall 2
- Goal: reach `X` at bottom-right corner
- Functions: `initialize_game()`, `print_board()`, `move_player(char direction)`

**Restrictions:** Only 1D arrays allowed, no 2D arrays; `stdio.h`, `stdlib.h`, `time.h` only

---

### PA4 — Student & Instructor Query System
**Due:** March 27, 2024 | **Topic:** File I/O, Structs, Switch-Case, GPA Calculation

Built a query system over two text files containing student/instructor records.

**Key features:**
- Reads `first.txt` (grades, course info) and `second.txt` (names, roles, departments)
- Utility functions: `first_initial`, `last_initial`, `get_id_fi`, `get_id_li`, `average_grade`
- Menu with 8 options: sort by age, filter by initial, GPA lookup, course pass/fail, instructor class count, department by role, course list, quit
- GPA computed from midterm + final averages using a letter-grade table (F/D/C/B/A)

**Restrictions:** No arrays or strings; `switch-case` required for menu

---

### PA5 — Space Mission News Reader & Key Decryptor
**Due:** April 3, 2024 | **Topic:** File I/O, String Processing, Functions, Math

Themed around Turkey's first astronaut Alper Gezeravcı's ISS mission — built a news reader with a hidden key decryption system.

**Key features:**
- Part 1: lists news headlines from 4 daily text files, interactive menu (read / list / decrypt)
- Part 2: tracks previously read articles; persists reading history across program restarts via a file
- Part 3: extracts magic numbers marked with `#` from news texts and computes a secret experiment key using: `f(x) = x³ − x² + 2`, `g(x) = x²`, `secret = Σg(f(Xᵢ))`

---

### PA6 — Histogram Drawer & Statistics Calculator
**Due:** April 10, 2024 | **Topic:** Arrays, Functions, Terminal Visualization

Created an interactive terminal histogram with statistical analysis.

**Key features:**
- User defines interval [A, B] (A ≥ 50, B ≤ 200); numbers outside range are ignored
- `find_size_of_array()` detects array end via `-1` sentinel
- Draws ASCII `*` histogram on terminal
- Allows adding up to 5 new numbers and re-drawing
- Calculates **average**, **median**, and **mode** (handles multiple modes and even-length arrays)

**Allowed libraries:** `stdio.h` only

---

### PA7 — Mancala Board Game
**Due:** April 24, 2024 | **Topic:** 2D Arrays, Functions, Game Logic

Implemented the classic Mancala board game in the terminal against a computer opponent.

**Key features:**
- 12 small cups (6 per side) + 2 large scoring cups
- Player distributes stones counterclockwise; skips opponent's large cup
- Extra turn if last stone lands in own large cup
- Computer plays automatically following the same rules
- Game ends when one side is empty; highest large-cup score wins
- Functions: `initializeGame()`, `printBoard()`, `gamePlay()`, `move()`

**Allowed libraries:** `stdio.h` only; no pointers

---

### PA8 — Scientist Database + Pattern Matching
**Due:** April 29, 2024 | **Topic:** Multi-dimensional Arrays, Sorting, String Search

Two-part assignment combining a scientist database and 2D pattern matching.

**Part 1 — Scientist Database:**
- Reads `input1.txt` with name, surname, age, and fields of famous scientists
- Menu: sort by age, sort by branch+age, filter by keyword, filter computer scientists who aren't mathematicians

**Part 2 — Pattern Matching in 2D text:**
- Reads `input2.txt` of `*`/`+` patterns
- Finds occurrences of 3 specific patterns: row (`P1`), column (`P2`), diagonal (`P3`)
- Uses array-of-strings representation — no conversion to 2D char array allowed

**Allowed libraries:** `stdio.h`, `string.h` only

---

### PA9 — Botanist Forest Explorer
**Due:** May 8, 2024 | **Topic:** Structs, Recursion, File I/O, 2D Arrays

Implemented a recursive maze exploration game set in a forest.

**Key features:**
- Reads map from `init.txt`: forest layout with Trees (`T`), Botanist (`B`), Flowers (`X`)
- `init_game()` parses file and builds forest + botanist structs
- `search()` — **recursive** function that walks the forest (up/down/left/right) through whitespaces to find all rare flowers
- `display_forest()` shows real-time map, collected flower count, and botanist coordinates
- User controls direction with `r/l/u/d`; trees block movement
- Final state saved to `last.txt` on exit

---

### PA10 — Assembly Language Simulator
**Due:** May 17, 2024 | **Topic:** Structs, Binary Arithmetic, File I/O, Simulation

Built a full fetch-decode-execute cycle simulator for a custom 30-instruction assembly language.

**Key features:**
- Two 8-bit registers (A, B), 16-bit Program Counter (PC), 24-bit Instruction Register (IR)
- Memory modeled as a stack; program stored in upper memory, variables in lower memory
- `to_binary(int)` and `to_decimal(char[])` conversion functions (8-bit representation)
- Supports all 30 opcodes: arithmetic (ADD, SUB, AND, OR, NOR), shifts (SHL, SHR), branches (BRE, BRN, J), memory ops (LDA, STR, LDAI), print (PRI, PRII, PRIM), and EXIT
- Reads `.asm` files from user input; loops until user exits with `0`

**Allowed libraries:** `stdio.h`, `string.h` only

---

### PA11 — Recursive Path Finder, Hospital Planner & Card Shuffler
**Due:** May 22, 2024 | **Topic:** Recursion, Structs, Randomization

Three independent problems, all requiring recursive solutions.

**Part 1 — Smart City Navigation (20 pts):**
- Robot Scout moves only West or South on a grid
- `numPathsHome(int street, int avenue)` — recursive function counting all optimal paths back to dispatch centre

**Part 2 — Sustainable Health Services (50 pts):**
- Given a list of `Hospital` structs (each covering up to 3 cities), determine if all cities can be covered within a hospital budget `numHospital`
- Recursive backtracking with `struct Hospital { char* name; char citiesServed[3]; }`

**Part 3 — Virtual Card Game Mixer (30 pts):**
- Models a 52-card deck using `struct card { const char *face; const char *suit; }`
- Randomly shuffles the deck and prints in two-column format

---

## ⚙️ Build & Run

```bash
# Compile (replace with actual filename)
gcc --ansi your_program.c -o your_program

# Run
./your_program

# For PA1 (file redirection)
./homework1_1 < input.txt > encrypted.txt
./homework1_2 < encrypted.txt > decrypted.txt
```

---

## ⚠️ Academic Integrity

All code in this repository is my own original work submitted for academic evaluation at Gebze Technical University.

> Cheating and unauthorized AI-generated code submission is strictly prohibited and results in **NA** from the course.

---

## 📬 Contact

**University:** Gebze Technical University — Department of Computer Engineering  
**Course:** CSE 102 — Computer Programming, Spring 2024
