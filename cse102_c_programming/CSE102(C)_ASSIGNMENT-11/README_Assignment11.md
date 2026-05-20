# CSE 102 – Ödev 11 / Assignment 11

> **Ders / Course:** CSE 102 – Computer Programming (Spring 2024)  
> **Öğrenci / Student:** Görkem Uysal  
> **Teslim Tarihi / Due Date:** May 22, 2024

---

## 🇹🇷 Türkçe

### 📌 Genel Açıklama

Bu ödev üç bağımsız bölümden oluşmaktadır. Her bölümde özyinelemeli fonksiyonlar ve `struct` kullanımı ön plana çıkmaktadır. Yalnızca `stdio.h`, `string.h`, `stdlib.h` ve `time.h` kütüphaneleri kullanılmıştır.

---

### Bölüm 1 – Akıllı Şehir Navigasyonu (`part_1.c`)

Amazon Scout robotu, şehir ızgarasında belirli bir başlangıç noktasından `(1. Sokak, 1. Cadde)` hedef noktasına kadar yalnızca **batı** (sol) ve **güney** (aşağı) yönünde hareket edebilir. Program, kullanıcıdan alınan koordinatlara göre ev yoluna giden **optimal yol sayısını** özyinelemeli olarak hesaplar.

#### Özyineleme Mantığı

- Hedef `(1, 1)` noktasına ulaşılırsa `1` döner (geçerli yol).
- Haritanın dışına çıkılırsa `0` döner (geçersiz yol).
- Her adımda sola ve aşağıya giden yolların toplamı döndürülür.

#### Derleme ve Çalıştırma

```bash
gcc --ansi part_1.c -o part_1
./part_1
```

**Örnek:**
```
Enter the street number: 2
Enter the avenue number: 3
Number of optimal paths to take back home: 3
```

> Geçerli giriş aralığı: 1–5 (sokak ve cadde için)

---

### Bölüm 2 – Sürdürülebilir Sağlık Hizmetleri (`part_2.c`)

4 potansiyel hastane ve 6 şehir (`A–F`) bulunmaktadır. Kullanıcıdan maksimum inşa edilebilecek hastane sayısı alınır. Program, seçilen hastane kombinasyonunun tüm şehirleri kapsayıp kapsamadığını özyinelemeli olarak kontrol eder.

#### Hastane Verileri

| Hastane | Kapsadığı Şehirler |
|---------|--------------------|
| Hospital - 1 | A, B, C |
| Hospital - 2 | A, C, D |
| Hospital - 3 | B, F |
| Hospital - 4 | C, E, F |

#### Özyineleme Mantığı

`find_hospitals()` fonksiyonu, belirlenen maksimum hastane sayısına kadar tüm kombinasyonları dener. `is_covered()` ile seçilen hastanelerin tüm şehirleri kapsayıp kapsamadığı kontrol edilir.

#### Derleme ve Çalıştırma

```bash
gcc --ansi part_2.c -o part_2
./part_2
```

**Örnek:**
```
Enter the maximum number of hospitals that can be constructed(1-4): 3
Yes, can offer health care to all!
Hospital - 1  →  ABC
Hospital - 2  →  ACD
Hospital - 4  →  CEF
```

---

### Bölüm 3 – Sanal Kart Destesi Karıştırıcı (`part_3.c`)

52 kartlık standart bir iskambil destesi `Card` struct'ı ile modellenir, rastgele karıştırılır ve ekrana iki sütun halinde yazdırılır.

#### Kart Yapısı

```c
typedef struct {
    const char *face;  /* Ace, Deuce, Three, ..., King */
    const char *suit;  /* Hearts, Diamonds, Clubs, Spades */
} Card;
```

#### Algoritma

`generate_cards()` ile 52 kart sırayla üretilip `all_cards` dizisine eklenir. `generate_random_indexes()` ile `srand(time(0))` kullanılarak tekrarsız rastgele indeksler üretilir. Kartlar bu indekslere göre `shuffled_deck` dizisine yerleştirilir ve 26 satır halinde (2 kart yan yana) ekrana yazdırılır.

#### Derleme ve Çalıştırma

```bash
gcc --ansi part_3.c -o part_3
./part_3
```

---

### Kullanılan Kavramlar

- Özyinelemeli fonksiyonlar (`numPathsHome`, `find_hospitals`)
- `struct` ile veri modelleme (`Hospital`, `Card`)
- `strchr`, `strcmp`, `strlen` ile string işlemleri
- `srand` / `rand` ile rastgele sayı üretimi
- `time.h` ile tohum (seed) başlatma

---

### 📁 Dosya Yapısı

```
📦 Assignment_11/
├── part_1.c            # Bölüm 1 – Navigasyon
├── part_2.c            # Bölüm 2 – Hastane kapsama
├── part_3.c            # Bölüm 3 – Kart destesi karıştırıcı
├── 230104004174.pdf    # Program çıktıları ve YouTube linki
└── README.md
```

---

---

## 🇬🇧 English

### 📌 Overview

This assignment consists of three independent parts. Each part emphasizes recursive functions and struct usage. Only `stdio.h`, `string.h`, `stdlib.h`, and `time.h` libraries are used.

---

### Part 1 – Smart City Navigation (`part_1.c`)

The Amazon Scout robot starts at a user-specified grid position and must return to `(1st Street, 1st Avenue)` by moving only **west** (left) or **south** (down). The program recursively calculates the number of optimal paths home.

#### Recursion Logic

- Returns `1` when the target `(1, 1)` is reached (valid path).
- Returns `0` when out of bounds (invalid path).
- Each call sums paths going left and paths going down.

#### Compile & Run

```bash
gcc --ansi part_1.c -o part_1
./part_1
```

**Example:**
```
Enter the street number: 2
Enter the avenue number: 3
Number of optimal paths to take back home: 3
```

> Valid input range: 1–5 for both street and avenue.

---

### Part 2 – Sustainable Health Services (`part_2.c`)

There are 4 potential hospitals and 6 cities (`A–F`). The user provides the maximum number of hospitals that can be built. The program recursively checks whether any combination of that many hospitals can cover all cities.

#### Hospital Data

| Hospital | Cities Covered |
|----------|----------------|
| Hospital - 1 | A, B, C |
| Hospital - 2 | A, C, D |
| Hospital - 3 | B, F |
| Hospital - 4 | C, E, F |

#### Recursion Logic

`find_hospitals()` tries all combinations up to the given maximum. `is_covered()` verifies whether the selected hospitals collectively cover all six cities.

#### Compile & Run

```bash
gcc --ansi part_2.c -o part_2
./part_2
```

**Example:**
```
Enter the maximum number of hospitals that can be constructed(1-4): 3
Yes, can offer health care to all!
Hospital - 1  →  ABC
Hospital - 2  →  ACD
Hospital - 4  →  CEF
```

---

### Part 3 – Virtual Card Game Mixer (`part_3.c`)

A standard 52-card deck is modeled using a `Card` struct, randomly shuffled, and printed in two columns.

#### Card Struct

```c
typedef struct {
    const char *face;  /* Ace, Deuce, Three, ..., King */
    const char *suit;  /* Hearts, Diamonds, Clubs, Spades */
} Card;
```

#### Algorithm

`generate_cards()` fills the `all_cards` array with all 52 cards in order. `generate_random_indexes()` produces 52 unique random indices using `srand(time(0))`. Cards are placed into `shuffled_deck` according to these indices and printed 26 lines of two cards side by side.

#### Compile & Run

```bash
gcc --ansi part_3.c -o part_3
./part_3
```

---

### Concepts Used

- Recursive functions (`numPathsHome`, `find_hospitals`)
- Struct-based data modeling (`Hospital`, `Card`)
- String operations with `strchr`, `strcmp`, `strlen`
- Random number generation with `srand` / `rand`
- Seed initialization with `time.h`

---

### 📁 File Structure

```
📦 Assignment_11/
├── part_1.c            # Part 1 – Navigation
├── part_2.c            # Part 2 – Hospital coverage
├── part_3.c            # Part 3 – Card deck shuffler
├── 230104004174.pdf    # Program outputs and YouTube link
└── README.md
```
