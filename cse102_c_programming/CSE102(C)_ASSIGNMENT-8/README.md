# CSE 102 – Ödev 8 / Assignment 8

> **Ders / Course:** CSE 102 – Computer Programming (Spring 2024)  
> **Öğrenci / Student:** Görkem Uysal  
> **Teslim Tarihi / Due Date:** April 29, 2024

---

## 🇹🇷 Türkçe

### 📌 Genel Açıklama

Bu ödev iki bölümden oluşmaktadır. Her iki bölümde de dosya okuma, çok boyutlu diziler ve string işlemleri kullanılmıştır. Yalnızca `stdio.h` ve `string.h` kütüphaneleri kullanılmıştır.

---

### Bölüm 1 – Bilim İnsanları Veritabanı (`gorkem_uysal_part_1.c`)

`input1.txt` dosyasından ünlü bilim insanlarının adı, soyadı, yaşı ve uzmanlık alanları okunarak çok boyutlu bir karakter dizisine kaydedilir. Program, kullanıcıya bir menü sunar ve seçime göre işlem yapar.

#### Menü Seçenekleri

| Seçenek | İşlev |
|---------|-------|
| 1 | Tüm kişileri yaşa göre küçükten büyüğe sırala ve listele |
| 2 | Kişileri uzmanlık alanına göre alfabetik, aynı alanda ise yaşa göre sırala |
| 3 | Adında "SCIENCE" geçen uzmanlık alanlarındaki kişileri filtrele |
| 4 | Yalnızca "COMPUTER SCIENCE" uzmanı olan (matematiği olmayanları) listele |
| 5 | Çıkış |

#### Kullanılan Kavramlar

- Çok boyutlu karakter dizileri (`char[MAX_ROWS][MAX_COLUMNS][MAX_LENGTH]`)
- Bubble Sort algoritması
- `strcmp`, `strstr`, `strlen`, `strcpy` fonksiyonları
- Dosya okuma (`fgetc`, `fopen`, `fclose`)
- Menü döngüsü ve hata yönetimi

#### Derleme ve Çalıştırma

```bash
gcc --ansi gorkem_uysal_part_1.c -o part_1
./part_1
```

> ⚠️ `main()` içindeki dosya yolunu (`input1.txt`) kendi sisteminize göre güncelleyin.

---

### Bölüm 2 – Karakter Deseni Arama (`gorkem_uysal_part_2.c`)

`input2.txt` dosyasından `*` ve `+` karakterlerinden oluşan bir desen okunur. Program üç farklı deseni arar ve konumlarını `(satır, sütun)` formatında ekrana yazar.

#### Aranan Desenler

| Desen | Yön | Pattern |
|-------|-----|---------|
| P1 | Yatay (soldan sağa) | `***++++***++++***` |
| P2 | Dikey (yukarıdan aşağıya) | `+*+*+` |
| P3 | Çapraz (sol üstten sağ alta) | `+**+++****+++**+` |

#### Örnek Çıktı

```
P1 @ (3,3)
P2 @ (1,30)
```

#### Kullanılan Kavramlar

- 2D karakter dizisi ile dosya okuma
- Yatay, dikey ve çapraz desen eşleştirme
- İşaretçi (pointer) ile `num_matches` güncelleme
- `strlen`, `strcmp` fonksiyonları

#### Derleme ve Çalıştırma

```bash
gcc --ansi gorkem_uysal_part_2.c -o part_2
./part_2
```

> ⚠️ `main()` içindeki dosya yolunu (`input2.txt`) kendi sisteminize göre güncelleyin.

---

### 📁 Dosya Yapısı

```
📦 Assignment_8/
├── gorkem_uysal_part_1.c   # Bölüm 1 kaynak kodu
├── gorkem_uysal_part_2.c   # Bölüm 2 kaynak kodu
├── input1.txt              # Bilim insanları verisi
├── input2.txt              # * ve + karakterlerinden oluşan desen
├── Gorkem_Uysal.pdf        # Program çıktıları ve YouTube linki
└── README.md
```

---

---

## 🇬🇧 English

### 📌 Overview

This assignment consists of two parts. Both parts make use of file reading, multidimensional arrays, and string operations. Only `stdio.h` and `string.h` libraries are used.

---

### Part 1 – Scientists Database (`gorkem_uysal_part_1.c`)

The program reads names, surnames, ages, and fields of study of famous scientists from `input1.txt` into a multidimensional character array. It presents an interactive menu and performs operations based on user input.

#### Menu Options

| Option | Function |
|--------|----------|
| 1 | Sort and display all individuals by age (ascending) |
| 2 | Sort individuals alphabetically by branch; within the same branch, sort by age |
| 3 | Filter individuals whose branch contains the word "SCIENCE" |
| 4 | Show only "COMPUTER SCIENCE" specialists who are not mathematicians |
| 5 | Exit |

#### Concepts Used

- Multidimensional character arrays (`char[MAX_ROWS][MAX_COLUMNS][MAX_LENGTH]`)
- Bubble Sort algorithm
- `strcmp`, `strstr`, `strlen`, `strcpy` functions
- File I/O (`fgetc`, `fopen`, `fclose`)
- Menu loop with error handling for invalid inputs

#### Compile & Run

```bash
gcc --ansi gorkem_uysal_part_1.c -o part_1
./part_1
```

> ⚠️ Update the file path for `input1.txt` inside `main()` to match your system.

---

### Part 2 – Pattern Matching (`gorkem_uysal_part_2.c`)

The program reads a grid of `*` and `+` characters from `input2.txt` and searches for three distinct patterns, printing each match's location as `(row, column)`.

#### Patterns Searched

| Pattern | Direction | Sequence |
|---------|-----------|----------|
| P1 | Horizontal (left to right) | `***++++***++++***` |
| P2 | Vertical (top to bottom) | `+*+*+` |
| P3 | Diagonal (top-left to bottom-right) | `+**+++****+++**+` |

#### Sample Output

```
P1 @ (3,3)
P2 @ (1,30)
```

#### Concepts Used

- Reading a file into a 2D character array
- Horizontal, vertical, and diagonal pattern matching
- Pointer-based output parameter (`int* num_matches`)
- `strlen`, `strcmp` functions

#### Compile & Run

```bash
gcc --ansi gorkem_uysal_part_2.c -o part_2
./part_2
```

> ⚠️ Update the file path for `input2.txt` inside `main()` to match your system.

---

### 📁 File Structure

```
📦 Assignment_8/
├── gorkem_uysal_part_1.c   # Part 1 source code
├── gorkem_uysal_part_2.c   # Part 2 source code
├── input1.txt              # Scientists dataset
├── input2.txt              # Star/plus character grid
├── Gorkem_Uysal.pdf        # Program outputs and YouTube demo link
└── README.md
```
