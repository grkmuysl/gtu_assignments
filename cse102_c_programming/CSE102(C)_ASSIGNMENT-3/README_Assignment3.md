# CSE 102 – Ödev 3 / Assignment 3

## 🎮 ECTS Toplama Oyunu – Terminal Tabanlı / ECTS Collection Game – Terminal Based

---

## 📌 Açıklama / Description

**TR:**
Bu ödev, 16x16'lık bir tahta üzerinde oynanan terminal tabanlı bir oyundur. Oyuncu (`P`), iki kare duvarla çevrili başlangıç konumundan hareket ederek ders (`1` ve `2`) nesnelerini toplar ve ECTS puanı kazanır. Yeterli ECTS puanı toplanmadan duvarlar geçilemez. Amaç, tahtanın sağ alt köşesindeki `X` noktasına ulaşmaktır.

**EN:**
This assignment is a terminal-based game played on a 16x16 board. The player (`P`) starts at the center surrounded by two square walls, collects course objects (`1` and `2`) to earn ECTS credits, and cannot pass through walls without sufficient ECTS. The goal is to reach the `X` located at the bottom-right corner of the board.

---

## 📁 Dosya Yapısı / File Structure

```
└── gorkem_uysal.c    # Ana kaynak kodu / Main source code
```

---

## ⚙️ Oyun Mekanikleri / Game Mechanics

### Tahta Gösterimi / Board Display

| Sembol | Anlam (TR) | Meaning (EN) |
|:-:|---|---|
| `P` | Oyuncu | Player |
| `#` | Duvar | Wall |
| `1` | 1. Sınıf Dersi | 1st Year Course |
| `2` | 2. Sınıf Dersi | 2nd Year Course |
| `X` | Hedef | Goal |
| `.` | Boş Alan | Empty Space |

### ECTS Sistemi / ECTS System

**TR:**
- Her `1` veya `2` nesnesi toplanınca **+8 ECTS** kazanılır.
- 1. duvarı geçmek için gereken minimum ECTS: **32**
- 2. duvarı geçmek için gereken minimum ECTS: **56** (toplam)
- İç alanda **4 adet** `1` nesnesi rastgele konumlandırılır.
- İki duvar arasında **3 adet** `2` nesnesi rastgele konumlandırılır.

**EN:**
- Collecting each `1` or `2` object grants **+8 ECTS**.
- Minimum ECTS to pass Wall 1: **32**
- Minimum ECTS to pass Wall 2: **56** (total)
- **4** `1` objects are randomly placed inside the inner wall.
- **3** `2` objects are randomly placed between the two walls.

### Kontroller / Controls

| Tuş / Key | Yön / Direction |
|:-:|:-:|
| `W` veya `w` | Yukarı / Up |
| `S` veya `s` | Aşağı / Down |
| `A` veya `a` | Sol / Left |
| `D` veya `d` | Sağ / Right |

---

## 🔧 Fonksiyonlar / Functions

**TR:** Program üç ana fonksiyondan oluşur:

**EN:** The program consists of three main functions:

```c
void initialize_game();
```
**TR:** Tahta boyutunu ayarlar (16x16), oyuncuyu merkeze (9,9) yerleştirir, `1` ve `2` nesnelerini rastgele ve çakışmadan dağıtır.

**EN:** Sets the board size (16x16), places the player at the center (9,9), and randomly distributes `1` and `2` objects without overlap.

---

```c
void print_board();
```
**TR:** 16x16 tahtayı ekrana yazdırır. Her satır önceden tanımlı 1D karakter dizileri kullanılarak çizilir. Oyuncunun mevcut konumu her çizimde güncellenir.

**EN:** Prints the 16x16 board to the screen using predefined 1D character arrays. The player's current position is updated on every render.

---

```c
void move_player(char direction);
```
**TR:** Büyük/küçük harf farkı gözetmeksizin oyuncuyu yönlendirir. Duvar geçiş izni kontrolü, ECTS doğrulaması, ders toplama ve oyun bitiş koşulunu yönetir.

**EN:** Moves the player regardless of letter case. Handles wall passage permission, ECTS validation, course collection, and game-end condition.

---

## 🎯 Oyun Akışı / Game Flow

```
Başlat / Start
     │
     ▼
initialize_game()
  → 16x16 tahta boyutu
  → P'yi (9,9) merkezine yerleştir
  → 4x "1" → iç alana rastgele (P ile çakışmadan)
  → 3x "2" → iki duvar arasına rastgele
     │
     ▼
print_board() + "Enter your move:" prompt
     │
     ▼
move_player(direction)
  ├─ Duvar kenarına gelinirse ECTS kontrolü yap
  │    ├─ Yeterli ECTS → geç (duvarı atla)
  │    └─ Yetersiz ECTS → "You don't have enough points!" uyarısı
  ├─ "1" veya "2" üzerine gelinirse:
  │    ├─ totalECTS += 8
  │    └─ Nesneyi kaldır (koordinat 99,99'a taşı)
  ├─ print_board() tekrar çağır
  └─ P == (16,16) ise → "YOU WON!" → isGameEnd = 1
     │
     ▼
isGameEnd == 0 → döngü devam eder / loop continues
```

---

## 🛠️ Derleme / Compilation

```bash
gcc --ansi gorkem_uysal.c -o gorkem_uysal
```

## ▶️ Çalıştırma / Usage

```bash
./gorkem_uysal
```

---

## 📊 Örnek Çıktı / Sample Output

```
. . . # # # # # # # # . . . . .
. . . # . . . . . . # . . . . .
. . . # . # # # # # . # . . . .
. . . # . # . 1 . # . # . . . .
. . . # . # 1 P 1 # . # . . . .
. . . # . # 1 . . # . # . . . .
. . . # . # # # # # . # . . . .
. . . # . . 2 . . . . # . . . .
. . . # # # # # # # # # . . . .
. . . . . . . . . . . . . . . X

Total ECTS: 0
Enter your move: d

You don't have enough points to pass the wall!

...

YOU WON !
```

---

## 🔧 Kullanılan Araçlar / Tools Used

- **Dil / Language:** C (ANSI C)
- **Kütüphaneler / Libraries:** `stdio.h`, `stdlib.h`, `time.h`
- **Veri Yapısı / Data Structure:** 1D diziler — 2D dizi kullanılmadı / 1D arrays only, no 2D arrays
- **Derleyici / Compiler:** GCC 11.4.0

---

## 👤 Öğrenci / Student

- **Ad Soyad / Name:** Görkem Uysal
- **Ders / Course:** CSE 102 – Computer Programming (Spring 2024)
- **Son Teslim / Due Date:** March 20, 2024
