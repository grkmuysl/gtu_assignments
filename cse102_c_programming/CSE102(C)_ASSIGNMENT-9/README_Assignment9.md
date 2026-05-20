# CSE 102 – Ödev 9 / Assignment 9

> **Ders / Course:** CSE 102 – Computer Programming (Spring 2024)  
> **Öğrenci / Student:** Görkem Uysal  
> **Teslim Tarihi / Due Date:** May 8, 2024

---

## 🇹🇷 Türkçe

### 📌 Genel Açıklama

Bu ödevde `T`, `B` ve `X` karakterlerinden oluşan bir orman haritasında botanikçiyi hareket ettiren, nadir çiçekleri toplayan ve oyun durumunu dosyaya kaydeden bir C programı geliştirilmiştir. Program `struct` ve özyinelemeli fonksiyonlar kullanılarak yazılmıştır.

---

### 🎮 Oyun Mekaniği

Harita bir `.txt` dosyasından okunur. Botanikçi (`B`) boş alanlarda hareket edebilir, ağaçlara (`T`) giremez. Nadir çiçekler (`X`) bulunduğunda şişeye konulur ve haritadan kaldırılır. Tüm çiçekler toplandığında veya kullanıcı çıkış yaparsa oyun sona erer.

| Karakter | Anlamı |
|----------|--------|
| `T` | Ağaç (geçilemez) |
| `B` | Botanikçi |
| `X` | Nadir çiçek |
| ` ` (boşluk) | Geçilebilir alan |

#### Hareket Kontrolleri

| Tuş | Yön |
|-----|-----|
| `w` | Yukarı |
| `s` | Aşağı |
| `a` | Sol |
| `d` | Sağ |
| `e` | Çıkış |

---

### 🔧 Fonksiyonlar

**`init_game(Forest*, Botanist*)`** — `init.txt` dosyasını okur, orman ve botanikçi yapılarını oluşturur. Çiçeklerin koordinatlarını kaydeder.

**`display_forest(Forest*, Botanist*, int)`** — Haritayı, toplanan çiçek sayısını ve kalan şişe sayısını ekrana yazdırır.

**`search(Forest*, Botanist*, int, int)`** — Özyinelemeli hareket fonksiyonu. Kullanıcıdan yön alır, botanikçiyi hareket ettirir, çiçek varsa toplar. Her hamle sonunda oyun durumunu `last.txt` dosyasına yazar.

---

### Kullanılan Kavramlar

- `struct` ile veri modelleme (`Forest`, `Botanist`)
- Özyinelemeli fonksiyon (`search`)
- Dosya okuma ve yazma (`fscanf`, `fgetc`, `fprintf`)
- 2D karakter dizisi ile harita temsili
- İşaretçilerle struct geçişi

---

### Derleme ve Çalıştırma

```bash
gcc --ansi 230104004174.c -o 230104004174
./230104004174
```

> ⚠️ `init_game()` ve `search()` içindeki dosya yollarını kendi sisteminize göre güncelleyin.

---

### `init.txt` Formatı

```
10,10          ← genişlik, yükseklik
1,0,100        ← botanikçi başlangıç satırı, sütunu, şişe sayısı
T,T,T,...      ← harita (3. satırdan itibaren)
```

### `last.txt` Formatı

```
10 10          ← genişlik yükseklik
9 6 99         ← botanikçi son satırı, sütunu, kalan şişe
T,T,T,...      ← oyunun son harita durumu
```

---

### 📁 Dosya Yapısı

```
📦 Assignment_9/
├── 230104004174.c      # Kaynak kod
├── init.txt            # Başlangıç harita dosyası
├── last.txt            # Oyun sonu durum dosyası (otomatik oluşturulur)
├── 230104004174.pdf    # Program çıktıları
└── README.md
```

---

---

## 🇬🇧 English

### 📌 Overview

This assignment implements a terminal-based game in C where a botanist navigates a forest map made of `T`, `B`, and `X` characters to collect rare flowers. The program uses structs and recursive functions.

---

### 🎮 Game Mechanics

The map is loaded from a `.txt` file. The botanist (`B`) can only move through empty spaces; trees (`T`) are impassable. When a rare flower (`X`) is found, it is collected into a bottle and removed from the map. The game ends when all flowers are collected or the user exits.

| Character | Meaning |
|-----------|---------|
| `T` | Tree (impassable) |
| `B` | Botanist |
| `X` | Rare flower |
| ` ` (space) | Walkable area |

#### Movement Controls

| Key | Direction |
|-----|-----------|
| `w` | Up |
| `s` | Down |
| `a` | Left |
| `d` | Right |
| `e` | Exit |

---

### 🔧 Functions

**`init_game(Forest*, Botanist*)`** — Reads `init.txt`, initializes the forest and botanist structs, and records flower coordinates.

**`display_forest(Forest*, Botanist*, int)`** — Prints the current map along with collected flower count and remaining bottle count.

**`search(Forest*, Botanist*, int, int)`** — Recursive movement function. Reads direction input, moves the botanist, collects flowers when found, and writes the current game state to `last.txt` after every move.

---

### Concepts Used

- Struct-based data modeling (`Forest`, `Botanist`)
- Recursive function (`search`)
- File I/O (`fscanf`, `fgetc`, `fprintf`)
- 2D character array for map representation
- Passing structs via pointers

---

### Compile & Run

```bash
gcc --ansi 230104004174.c -o 230104004174
./230104004174
```

> ⚠️ Update the file paths for `init.txt` and `last.txt` inside `init_game()` and `search()` to match your system.

---

### `init.txt` Format

```
10,10          ← width, height
1,0,100        ← botanist starting row, column, bottle count
T,T,T,...      ← map rows (starting from line 3)
```

### `last.txt` Format

```
10 10          ← width height
9 6 99         ← botanist final row, column, remaining bottles
T,T,T,...      ← final state of the map
```

---

### 📁 File Structure

```
📦 Assignment_9/
├── 230104004174.c      # Source code
├── init.txt            # Initial map file
├── last.txt            # End-of-game state file (auto-generated)
├── 230104004174.pdf    # Program outputs
└── README.md
```
