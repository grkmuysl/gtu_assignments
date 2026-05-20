# CSE 102 – Ödev 7 / Assignment 7

## 🪨 Mancala Oyunu – Terminal Tabanlı / Mancala Game – Terminal Based

---

## 📌 Açıklama / Description

**TR:**
Bu ödev, klasik Mancala tahta oyununun C dilinde uygulamasıdır. Oyun, 12 küçük kap (her tarafta 6) ve 2 büyük kaptan oluşan bir tahta üzerinde oynanır. Oyuncu bilgisayara karşı oynayarak taşları saat yönünün tersine dağıtır. Kazanan, büyük kabında en fazla taşa sahip olan taraftır.

**EN:**
This assignment is a C implementation of the classic Mancala board game. The game is played on a board with 12 small cups (6 on each side) and 2 large cups. The player plays against the computer, distributing stones counterclockwise. The winner is the side with the most stones in their large cup.

---

## 📁 Dosya Yapısı / File Structure

```
└── 230104004174.c    # Ana kaynak kodu / Main source code
```

---

## 🎮 Oyun Kuralları / Game Rules

**TR:**
- Oyun başında kullanıcıdan taş sayısı (n) alınır; her küçük kaba n taş yerleştirilir.
- Oyuncu alt satırı (cups 1-6), bilgisayar üst satırı kullanır.
- Taşlar seçilen kaptan alınarak saat yönünün tersine dağıtılır (her kaba 1 taş).
- Kendi büyük kabına taş düşürülür; rakibin büyük kabı atlanır.
- Son taş büyük kaba düşerse aynı oyuncunun sırası tekrarlanır.
- Son taş boş bir kaba düşerse sıra değişir.
- Bir tarafın tüm küçük kapları boşalınca oyun biter; büyük kaplardaki taşlar sayılır.

**EN:**
- At game start, the user enters stone count (n); each small cup gets n stones.
- Player uses the bottom row (cups 1-6), computer uses the top row.
- Stones are taken from the selected cup and distributed counterclockwise (1 stone per cup).
- Stones are placed in the player's own large cup but skip the opponent's large cup.
- If the last stone lands in the large cup, the same player gets another turn.
- If the last stone lands in an empty cup, the turn switches.
- The game ends when all small cups on one side are empty; stones in large cups are counted.

---

## 🖥️ Tahta Görünümü / Board Layout

```
+----+---+---+---+---+---+---+----+
|    | 6 | 5 | 4 | 3 | 2 | 1 |    |   ← Bilgisayar / Computer (cups 1-6)
| 12 |---+---+---+---+---+---|  0 |   ← Büyük kaplar / Large cups
|    | 1 | 2 | 3 | 4 | 5 | 6 |    |   ← Oyuncu / Player (cups 1-6)
+----+---+---+---+---+---+---+----+
```

> Tahta `5x35` boyutunda 2D integer dizi ile temsil edilir.
> The board is represented as a `5x35` 2D integer array.

**Dizi Kodlaması / Array Encoding:**

| Değer / Value | Karakter / Character |
|:-:|:-:|
| `-1` | `+` (köşe / corner) |
| `-2` | `-` (yatay çizgi / horizontal) |
| `-3` | `\|` (dikey çizgi / vertical) |
| `-4` | ` ` (boşluk / space) |
| `0-99` | Taş sayısı / Stone count |

---

## ⚙️ Fonksiyonlar / Functions

```c
void initializeGame(int stoneCount, int lines[5][35]);
```
**TR:** Tahtayı başlatır. Her küçük kaba `stoneCount` taş yerleştirir; büyük kapları 0 olarak bırakır. Çift basamaklı sayılarda onlar ve birler basamağı ayrı hücrelere yazılır.

**EN:** Initializes the board. Places `stoneCount` stones in each small cup; large cups start at 0. For two-digit numbers, tens and units digits are stored in separate cells.

---

```c
void printBoard(int lines[5][35]);
```
**TR:** 2D diziyi okuyarak tahta görüntüsünü terminale basar. Kodlama değerlerine göre `+`, `-`, `|` veya sayı yazdırır.

**EN:** Reads the 2D array and prints the board to the terminal. Prints `+`, `-`, `|`, or numbers based on encoding values.

---

```c
int distributeStonesForPlayer(int indexOfCup, int countOfStone, int lineOfCups, int lines[5][35], int isPlayer);
```
**TR:** Oyuncu için taş dağıtımı yapar. Alt satırdan sağa doğru, ardından üst satırdan sola doğru saat yönünün tersine dağıtır. Kendi büyük kabına taş ekler. Son taşın indeksini döndürür (satır bilgisiyle kodlanmış: alt satır 300+, üst satır 100+).

**EN:** Distributes stones for the player. Goes right along the bottom row, then left along the top row counterclockwise. Adds stones to the player's large cup. Returns the last stone's index encoded with row info (300+ for bottom, 100+ for top).

---

```c
int distributeStonesForComputer(int indexOfCup, int countOfStone, int lineOfCups, int lines[5][35], int isComputer);
```
**TR:** Bilgisayar için taş dağıtımı yapar. Üst satırdan sola doğru, ardından alt satırdan sağa doğru dağıtır. Kendi büyük kabına taş ekler.

**EN:** Distributes stones for the computer. Goes left along the top row, then right along the bottom row. Adds stones to the computer's large cup.

---

```c
int move(int indexOfCup, int lines[5][35], int turn, int lineOfCups);
```
**TR:** Seçilen kap ve sıra bilgisine göre uygun dağıtım fonksiyonunu çağırır, tahtayı günceller ve son taşın konumunu döndürür.

**EN:** Calls the appropriate distribution function based on the selected cup and current turn, updates the board, and returns the last stone's position.

---

```c
int isGameEndF(int lines[5][35]);
```
**TR:** Oyunun bitip bitmediğini kontrol eder. Bir tarafın tüm küçük kapları boşsa oyunu bitirir, kazananı ve skoru ekrana basar.

**EN:** Checks if the game has ended. If all small cups on one side are empty, ends the game, prints the winner and score.

---

```c
int gamePlay(int lines[5][35]);
```
**TR:** Oyun döngüsünü yönetir. Oyuncu ve bilgisayar sırayla hamle yapar. `move()` fonksiyonunun dönüş değerine göre sıra değişimi ve özel durumlar işlenir.

**EN:** Manages the game loop. Player and computer take turns. Handles turn switching and special cases based on `move()` return value.

---

## 📊 Örnek Çıktı / Sample Output

```
Enter stone count: 4
+----+---+---+---+---+---+---+----+
|    | 4 | 4 | 4 | 4 | 4 | 4 |    |
| 00 |---+---+---+---+---+---| 00 |
|    | 4 | 4 | 4 | 4 | 4 | 4 |    |
+----+---+---+---+---+---+---+----+
Your turn!
Please select a cup: 4
...
You won! Your score is: 17
```

---

## 🛠️ Derleme / Compilation

```bash
gcc --ansi 230104004174.c -o 230104004174
```

## ▶️ Çalıştırma / Usage

```bash
./230104004174
```

---

## 🔧 Kullanılan Araçlar / Tools Used

- **Dil / Language:** C (ANSI C)
- **Kütüphane / Library:** `stdio.h`
- **Veri Yapısı / Data Structure:** `int lines[5][35]` — 2D integer dizi / 2D integer array
- **Kısıtlamalar / Constraints:** İşaretçi (pointer) kullanılmadı / No pointers used
- **Derleyici / Compiler:** GCC 11.4.0

---

## 👤 Öğrenci / Student

- **Öğrenci No / Student ID:** 230104004174
- **Ders / Course:** CSE 102 – Computer Programming (Spring 2024)
- **Son Teslim / Due Date:** April 24, 2024
