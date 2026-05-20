# 📚 CSE 222 / BİL 505 — Data Structures and Algorithms

**Gebze Technical University — Computer Engineering Department**  
**Spring 2025**

---

## 🧑‍💻 About

This repository contains my homework assignments for the **CSE 222 / BİL 505 — Data Structures and Algorithms** course at Gebze Technical University. All implementations are written in **Java** and focus on core data structure concepts including OOP design, algorithm analysis, trees, hash maps, and more.

---

## 🛠️ Technologies & Tools

| Tool | Details |
|------|---------|
| Language | Java (OpenJDK 11) |
| IDE | Any Java-compatible IDE (IntelliJ, Eclipse, VS Code) |
| Build | Makefile |
| OS | Linux (Ubuntu recommended) |
| Docs | JavaDoc |

---

## 📂 Repository Structure

```
CSE222-Homeworks/
├── HW1/   → Embedded System Device Framework (OOP)
├── HW2/   → Algorithm Analysis & Complexity (Written)
├── HW3/   → Device Framework Extension + Logging
├── HW4/   → Planetary System Tree Analysis
├── HW6/   → Custom HashMap, HashSet & Spell Checker
└── README.md
```

---

## 📝 Homeworks

### HW1 — Embedded System Device Framework
**Topic:** Object-Oriented Programming, Inheritance, Interfaces, Polymorphism

Designed and implemented a framework for controlling communication ports of an embedded system using OOP principles in Java.

**Key concepts:**
- Protocol interface with `I2C`, `SPI`, `UART`, `OneWire` implementations
- Abstract device hierarchy: `Sensor`, `Display`, `WirelessIO`, `MotorDriver`
- Concrete device classes: `DHT11`, `BME280`, `MPU6050`, `GY951`, `LCD`, `OLED`, `Bluetooth`, `Wifi`, `PCA9685`, `SparkFunMD`
- Terminal-based runtime commands: `addDev`, `rmDev`, `turnON/OFF`, `readSensor`, `list ports`, etc.
- Error handling without program termination

**Allowed Libraries:** `java.io.File`, `java.util.ArrayList`, `java.util.Scanner`

---

### HW2 — Algorithm Analysis & Complexity
**Topic:** Big-O Notation, Asymptotic Analysis, Growth Rates

A written (pencil & paper) assignment covering:

- True/False proofs using limit derivation for Big-O, Omega, and Theta
- Ordering functions by growth rate with step-by-step derivations
- Worst-case complexity analysis of given Java code snippets
- The "toy drop" problem: finding the lowest breaking floor in a 100-floor building using binary search and complexity analysis

**Submission format:** Handwritten, scanned PDF

---

### HW3 — Device Framework Extension: Logging & Output Handling
**Topic:** Data Structures (ArrayList, LinkedList, Queue, Stack), Iterators, JavaDoc

Extended the HW1 device framework with:

- Command buffering: all terminal commands are stored in a `List` and executed after `exit`
- Protocol-level log files: `<protocolName>_<portID>.log` written in descending order
- Strict stdout/stderr separation for outputs and errors
- Full JavaDoc documentation for all classes and methods
- All operations in `O(1)` time complexity

**Allowed Libraries:** `java.util.ArrayList`, `java.util.LinkedList`, `java.util.Queue`, `java.util.Stack`, `java.util.Iterator`, `java.io.File`, `java.util.Scanner`

---

### HW4 — Deep Space Planetary System Analysis
**Topic:** Trees, Recursion, Stacks

Implemented a tree-based data structure to model a planetary system discovered by a space probe.

**Key features:**
- Multi-child tree where the root is a Star, children are Planets, and their children are Moons
- Each node stores `SensorData` (temperature, pressure, humidity, radiation)
- Terminal commands:
  - `create planetSystem` — builds the tree with a root star
  - `addPlanet` / `addSatellite` — adds nodes to the tree
  - `findRadiationAnomalies <threshold>` — recursive traversal to find anomalies
  - `getPathTo <planetName>` — returns path from root using a `Stack<String>`
  - `printMissionReport` / `printMissionReport <nodeName>` — prints full or node-specific data
- Recursive tree traversal throughout

---

### HW6 — High-Performance Spell Checker with Custom HashMap & HashSet
**Topic:** Hashing, Open Addressing, Edit Distance, Custom Data Structures

Implemented from scratch a fully custom `GTUHashMap<K,V>` and `GTUHashSet<E>`, then used them to build a real-world spell checker.

**Key features:**
- `GTUHashMap<K,V>` with open addressing (linear probing), tombstone deletion, and optional rehashing to next prime capacity
- `GTUHashSet<E>` built on top of `GTUHashMap`
- `SpellChecker` that loads a 50,000+ word dictionary and suggests corrections within **edit distance ≤ 2** (insert, delete, substitute)
- Performance requirement: suggestion lookup under **100ms**
- No Java collection libraries used — fully custom implementations

**Bonus tasks:** Quadratic probing, collision/memory tracking, custom JUnit-style test framework, rehashing

**Submitted files:** `GTUHashMap.java`, `GTUHashSet.java`, `SpellChecker.java`, `Entry.java`, `dictionary.txt`

---

## ⚠️ Academic Integrity

All code in this repository is my own original work submitted for academic evaluation at Gebze Technical University.

> Cheating and unauthorized use of others' code is strictly prohibited and results in **NA** from the course.

---

## 📬 Contact

**Course Instructor:** Burak Dikmen  
**Contact:** a.dikmen2022@gtu.edu.tr  
**University:** Gebze Technical University — Department of Computer Engineering
