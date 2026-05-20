# CSE 102 – Ödev 6 / Assignment 6

## 📊 Histogram ve İstatistiksel Hesaplamalar / Histogram & Statistical Calculations

---

## 📌 Açıklama / Description

**TR:**
Bu ödev, sabit bir sayı dizisindeki değerlerin belirli bir aralıktaki frekanslarını terminal üzerinde histogram olarak görselleştiren ve ardından ortalama, medyan, mod gibi istatistiksel hesaplamalar yapan bir C programıdır. Kullanıcı aralık belirler, isteğe bağlı yeni sayılar ekleyebilir.

**EN:**
This assignment is a C program that visualizes the frequency of values in a fixed number array as a terminal histogram within a user-defined interval, then performs statistical calculations including average, median, and mode. The user defines the interval and can optionally add new numbers.

---

## 📁 Dosya Yapısı / File Structure

```
└── 230104004174.c    # Ana kaynak kodu / Main source code
```

---

## 🔢 Sabit Dizi / Fixed Array

```c
int number_array[] = {3, 8, 9, 9, 5, 2, 4, 7, 4, 8, 9, 10, 2, 4, 5, -1};
```

> Dizi sonu `-1` ile işaretlenir. / Array is terminated with `-1`.

---

## ⚙️ Fonksiyonlar / Functions

```c
int find_size_of_array(int number_array[]);
```
**TR:** `-1` hariç dizinin eleman sayısını bulur.

**EN:** Returns the number of elements in the array, excluding `-1`.

---

```c
int count_of_number(int number, int number_array[]);
```
**TR:** Verilen sayının dizide kaç kez geçtiğini sayar.

**EN:** Counts how many times the given number appears in the array.

---

```c
int max_repetition(int number_array[]);
```
**TR:** Dizideki en çok tekrar eden sayının tekrar sayısını döndürür (histogram yüksekliği için kullanılır).

**EN:** Returns the maximum repetition count in the array (used for histogram height).

---

```c
void display_histogram(int max_repetition_number, int interval1, int interval2, int number_array[]);
```
**TR:** Verilen aralıktaki her sayının frekansını `*` karakteriyle dikey histogram olarak ekrana basar. En çok tekrar eden sayı en üstte yer alır.

**EN:** Prints a vertical `*` histogram for each number's frequency in the given interval. The most frequent number appears at the top.

---

```c
void calculation_of_average(int number_array[], int size_of_array, int interval1, int interval2);
```
**TR:** Aralık içindeki sayıların ortalamasını hesaplar ve `%.2f` formatında yazdırır.

**EN:** Calculates the average of numbers within the interval and prints it in `%.2f` format.

---

```c
void sort_the_numbers(int number_array[], int size_of_array);
```
**TR:** Diziyi küçükten büyüğe kabarcık sıralaması (bubble sort) ile sıralar.

**EN:** Sorts the array from smallest to largest using bubble sort.

---

```c
void calculation_of_median(int number_array[], int size_of_array);
```
**TR:** Diziyi sıralayarak medyanı hesaplar. Tek sayıda eleman varsa ortadaki değeri döndürür.

**EN:** Sorts the array and calculates the median. Returns the middle value for odd-sized arrays.

---

```c
void calculation_of_mode(int number_array[], int size_of_array, int max_repetition);
```
**TR:** En sık tekrar eden sayıyı (modu) bulur. Birden fazla mod varsa hepsini yazdırır.

**EN:** Finds the most frequently occurring number (mode). If multiple modes exist, prints all of them.

---

## 🖥️ Program Akışı / Program Flow

```
Başlat / Start
     │
     ▼
Kullanıcıdan interval1 ve interval2 gir
     │
     ▼
display_histogram() → Aralıktaki frekansları * ile göster
     │
     ▼
"Yeni sayı eklemek ister misiniz? (1/0)"
     ├─ 1 → En fazla 5 sayı gir (-1 ile sonlandır)
     │       Yeni diziyi oluştur → display_histogram() tekrar çalıştır
     └─ 0 → Mevcut diziyle devam et
     │
     ▼
calculation_of_average()
calculation_of_median()
calculation_of_mode()
```

---

## 📊 Örnek Çıktı / Sample Output

**Örnek 1 / Example 1 — Yeni sayı yok / No new numbers:**
```
Enter first interval: 2
Enter second interval: 9
  *    *
* **  **
**** ***
Would you like to add new numbers? (Press 1 for yes, Press 0 for no): 0
Average: 5.64
Median: 5
Mode: 4 9
```

**Örnek 2 / Example 2 — Yeni sayılar eklendi / New numbers added:**
```
Enter first interval: 2
Enter second interval: 9
  *    *
* **  **
**** ***
Would you like to add new numbers? (Press 1 for yes, Press 0 for no): 1
Enter the numbers: 5
6
-1
  **   *
* **  **
********
Average: 5.62
Median: 5
Mode: 4 5 9
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

- **Dil / Language:** C (ANSI C / C99)
- **Kütüphane / Library:** `stdio.h`
- **Sıralama Algoritması / Sorting:** Bubble Sort
- **Derleyici / Compiler:** GCC 11.4.0

---

## 👤 Öğrenci / Student

- **Öğrenci No / Student ID:** 230104004174
- **Ders / Course:** CSE 102 – Computer Programming (Spring 2024)
- **Son Teslim / Due Date:** April 10, 2024
