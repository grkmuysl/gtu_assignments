# CSE 102 – Ödev 4 / Assignment 4

## 🎓 Öğrenci Bilgi Sorgulama Sistemi / Student Information Query System

---

## 📌 Açıklama / Description

**TR:**
Bu ödev, iki ayrı metin dosyasından okunan kişi bilgilerini sorgulayan etkileşimli bir C programıdır. Kullanıcı; öğrenci notlarını, GPA değerlerini, ders bilgilerini ve eğitmen verilerini menü aracılığıyla sorgulayabilir. Program, isim/soyisim baş harfine göre filtreleme, GPA hesaplama ve ders bazlı ortalama alma gibi işlevleri destekler.

**EN:**
This assignment is an interactive C program that queries person information read from two separate text files. Users can query student grades, GPA values, course information, and instructor data through a menu. The program supports filtering by first/last name initial, GPA calculation, and course-based average computation.

---

## 📁 Dosya Yapısı / File Structure

```
├── 230104004174.c    # Ana kaynak kodu / Main source code
├── first_1.txt       # Not ve ders bilgileri / Grade and course info
└── second_1.txt      # İsim, soyisim, rol bilgileri / Name, surname, role info
```

---

## 📄 Veri Dosyası Formatları / Data File Formats

### `first_1.txt` (Not Dosyası / Grade File)

Her satır şu formatlardan birini izler / Each line follows one of these formats:

```
# 2 vize + final olan öğrenci / Student with 2 midterms + final:
<id>;<midterm1>;<midterm2>;<final>;<course_id>

# 1 vize + final olan öğrenci / Student with 1 midterm + final:
<id>;<midterm>;<final>;<course_id>

# Eğitmen / Instructor:
<id>;<# of classes>;<department>
```

### `second_1.txt` (Kişi Dosyası / Person File)

```
<id>;<name>;<surname>;<role>;<department>
```

---

## ⚙️ Fonksiyonlar / Functions

```c
char first_initial(FILE *id_fp, int id);
```
**TR:** Verilen ID'ye sahip kişinin adının baş harfini döndürür. Dosyayı karakter karakter okuyarak ID eşleşmesi bulunca bir sonraki karakteri alır.

**EN:** Returns the first letter of the name of the person with the given ID. Reads character by character and retrieves the next character upon ID match.

---

```c
char last_initial(FILE *id_fp, int id);
```
**TR:** Verilen ID'ye sahip kişinin soyadının baş harfini döndürür. ID eşleşmesinden sonra ikinci noktalı virgüle kadar ilerleyerek soyadının ilk karakterini alır.

**EN:** Returns the first letter of the surname of the person with the given ID. After ID match, advances to the second semicolon and retrieves the first character of the surname.

---

```c
void calculate_average_midterm(FILE *id_fp);
```
**TR:** Tüm öğrencilerin vize ortalamalarını hesaplar ve global `midtermAverage` değişkenine atar.

**EN:** Calculates the average midterm score of all students and assigns it to the global `midtermAverage` variable.

---

```c
void calculate_average_final(FILE *id_fp);
```
**TR:** Tüm öğrencilerin final ortalamalarını hesaplar ve global `finalAverage` değişkenine atar.

**EN:** Calculates the average final score of all students and assigns it to the global `finalAverage` variable.

---

```c
int average_grade(FILE *id_fp, int id);
```
**TR:** Verilen ID'ye sahip öğrencinin GPA değerini aşağıdaki tabloya göre hesaplayıp döndürür.

**EN:** Calculates and returns the GPA of the student with the given ID according to the table below.

---

```c
int get_id_fi(FILE *id_fp, char first_initial);
```
**TR:** Adı verilen harfle başlayan tüm kişilerin ID'lerini ekrana yazdırır. Sonuçları geçici bir dosyaya (`students1.txt`) yazar, ardından okur.

**EN:** Prints the IDs of all persons whose first name starts with the given letter. Writes results to a temporary file (`students1.txt`), then reads from it.

---

```c
int get_id_li(FILE *id_fp, char last_initial);
```
**TR:** Soyadı verilen harfle başlayan tüm kişilerin ID'lerini ekrana yazdırır. Geçici dosya (`students2.txt`) kullanılır.

**EN:** Prints the IDs of all persons whose last name starts with the given letter. Uses a temporary file (`students2.txt`).

---

```c
void number_of_classes(FILE *id_fp, int user_id);
```
**TR:** Verilen ID'ye sahip eğitmenin ders sayısını yazdırır. Öğrenci satırlarını atlayarak eğitmen satırlarına ulaşır.

**EN:** Prints the number of classes for the instructor with the given ID. Skips student lines to reach instructor lines.

---

```c
void print_course_id(FILE *id_fp, int user_id);
```
**TR:** Verilen öğrenci ID'sine ait ders ID'sini yazdırır.

**EN:** Prints the course ID associated with the given student ID.

---

```c
void print_average_grade_of_course(FILE *id_fp, int course_id);
```
**TR:** Verilen ders ID'sine kayıtlı tüm öğrencilerin ortalama GPA değerini hesaplayıp yazdırır.

**EN:** Calculates and prints the average GPA of all students enrolled in the given course.

---

## 📊 GPA Hesaplama Tablosu / GPA Calculation Table

| Koşul / Condition | Harf Notu / Letter Grade | GPA |
|---|:-:|:-:|
| Vize < 40 ve Vize < VizeOrt **ve** Final < 40 ve Final < FinalOrt | F | 1 |
| Vize > 40 ve Vize < VizeOrt **ve** Final > 40 ve Final < FinalOrt | D | 2.5 |
| Vize > 40 ve Vize < VizeOrt **ve** Final > 40 ve Final > FinalOrt | C | 3 |
| 90 > Vize > VizeOrt **ve** 90 > Final > FinalOrt | B | 3.5 |
| Vize ≥ 90 **ve** Final ≥ 90 | A | 4 |

**Formüller / Formulas:**

```
İki vize varsa / If two midterms:   M = (M1 + M2) / 2
GPA:                                GPA = (M + F) / 2
```

---

## 🖥️ Menü Seçenekleri / Menu Options

| Tuş / Key | İşlev (TR) | Function (EN) |
|:-:|---|---|
| `p` | Tüm öğrencilerin geçti/kaldı durumunu yazdır | Print pass/fail for all students |
| `n` | Belirli bir baş harfle başlayan adlara sahip öğrencileri listele | List students by first name initial |
| `g` | Belirli bir öğrencinin GPA ve harf notunu hesapla | Calculate GPA and letter grade for a student |
| `c` | Belirli bir dersin ortalama GPA'sını yazdır | Print average GPA for a course |
| `t` | Bir eğitmenin ders sayısını yazdır | Print number of classes for an instructor |
| `d` | Role göre kişilerin departmanlarını listele | List departments by role |
| `l` | Bir öğrencinin ders ID'sini yazdır | Print course ID for a student |
| `e` | Programdan çık | Exit the program |

---

## 📊 Örnek Çıktı / Sample Output

```
Choose an option: n
Enter a letter for the initial: r
List of students whose names start with r:
220015022
210015002
210015012
210015024
195001005
195001009

Choose an option: g
Enter the studentId for the GPA: 220015015
Student's GPA is: 3
Studen'ts letter grade is: C

Choose an option: l
Enter the USER ID: 220015003
Course ID is : 102

Choose an option: l
Enter the USER ID: 195001003
This user is not a student!

Choose an option: e
Exiting...
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

> **Not / Note:** Kaynak kodundaki dosya yollarını (`first_1.txt`, `second_1.txt`) kendi sisteminize göre güncellemeyi unutmayın. / Make sure to update the hardcoded file paths to match your system.

---

## 🔧 Kullanılan Araçlar / Tools Used

- **Dil / Language:** C (ANSI C)
- **Kütüphane / Library:** `stdio.h`
- **Kısıtlamalar / Constraints:** Dizi ve string kullanılmadı / No arrays or strings used
- **Derleyici / Compiler:** GCC 11.4.0

---

## 👤 Öğrenci / Student

- **Öğrenci No / Student ID:** 230104004174
- **Ders / Course:** CSE 102 – Computer Programming (Spring 2024)
- **Son Teslim / Due Date:** March 27, 2024
