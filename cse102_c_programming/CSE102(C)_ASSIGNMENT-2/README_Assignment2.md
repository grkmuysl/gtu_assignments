# CSE 102 – Ödev 2 / Assignment 2

## 🤖 Temel Yapay Zeka Algoritması – 2D Düzlem Sınıflandırıcı / Basic AI Algorithm – 2D Plane Classifier

---

## 📌 Açıklama / Description

**TR:**
Bu ödev, C programlama dili kullanılarak temel bir yapay zeka algoritmasının uygulanmasını içermektedir. Program; bir veri dosyasını okur, 2D koordinat uzayını iki ayırıcı (separator) ile dört bölgeye ayırır ve her bölgeye bir sınıf etiketi (0 veya 1) atayarak sınıflandırma yapar. Hedef, eğitim verisindeki sınıflandırma hatasını en aza indiren en iyi ayırıcı koordinatları bulmaktır.

**EN:**
This assignment involves implementing a basic AI algorithm in C. The program reads a data file, divides a 2D coordinate space into four regions using two separators, and assigns a class label (0 or 1) to each region for classification. The goal is to find the best separator coordinates that minimize the classification error on the training data.

---

## 📁 Dosya Yapısı / File Structure

```
├── 230104004174.c     # Ana kaynak kodu / Main source code
├── data.txt           # Eğitim verisi / Training data
├── test_1.txt         # Test verisi (etiketli) / Test data (labeled)
└── test-final.txt     # Test verisi (etiketsiz) / Test data (unlabeled)
```

---

## ⚙️ Nasıl Çalışır / How It Works

### Veri Formatı / Data Format

`data.txt` ve `test_1.txt` dosyalarındaki her satır şu formatı izler / Each line in `data.txt` and `test_1.txt` follows this format:

```
X_koordinatı  Y_koordinatı  Sınıf_etiketi
X_coordinate  Y_coordinate  Class_label
```

`test-final.txt` etiket içermez / `test-final.txt` does not contain labels:

```
X_koordinatı  Y_koordinatı
X_coordinate  Y_coordinate
```

---

### Part 1 – Veri Keşfi / Data Exploration

**TR:** `data.txt` dosyası okunarak her sınıf (0 ve 1) için X ve Y koordinatlarının minimum ve maksimum değerleri hesaplanır ve ekrana yazdırılır.

**EN:** The `data.txt` file is read and the minimum/maximum X and Y values are calculated and printed for each class (0 and 1).

Örnek çıktı / Example output:
```
Minimum and Maximum X and Y values:
Class 0: X in [1 48], Y in [3 45]
Class 1: X in [5 49], Y in [0 49]
```

---

### Part 2 – Model Eğitimi / Model Training

**TR:**
İki ayırıcı koordinat (sepX, sepY), 2D düzlemi dört bölgeye ayırır:

**EN:**
Two separator coordinates (sepX, sepY) divide the 2D plane into four regions:

```
┌─────────────┬─────────────┐
│  R1         │  R2         │
│ x≤sepX,y>sepY│ x>sepX,y>sepY│
├─────────────┼─────────────┤
│  R3         │  R4         │
│ x≤sepX,y≤sepY│ x>sepX,y≤sepY│
└─────────────┴─────────────┘
```

**TR:** Her bölgeye 0 veya 1 etiketi atanır. Tüm olası ayırıcı koordinat ve etiket kombinasyonları denenerek en az hata veren kombinasyon seçilir.

**EN:** Each region is assigned label 0 or 1. All possible separator coordinate and label combinations are tried, and the one with the minimum error is selected.

Örnek çıktı / Example output:
```
Best separator coordinates: X = 15, Y = 27, Total Error = 14
Region Labels:
R1: Class Label 0
R2: Class Label 1
R3: Class Label 1
R4: Class Label 0
success rate : % 83
```

---

### Part 3 – Model Testi / Model Testing

**TR:** Etiket içermeyen `test-final.txt` dosyasındaki noktalar, eğitilen modelin bulduğu en iyi ayırıcı koordinatlarına göre sınıflandırılır.

**EN:** Points in `test-final.txt` (without labels) are classified using the best separator coordinates found during training.

Örnek çıktı / Example output:
```
For this point: X = 26, Y = 31 Class should be: 1
For this point: X = 27, Y = 15 Class should be: 0
...
```

---

### Part 4 – Menü / Menu

**TR:** Program, kullanıcıya 4 seçenek sunan bir menü ile çalışır:

**EN:** The program runs with a menu that offers 4 options to the user:

```
MENU:
 1. Explore Data   (Veriyi Keşfet)
 2. Train Model    (Modeli Eğit)
 3. Test Model     (Modeli Test Et)
 4. EXIT           (Çıkış)
```

**TR:** Kullanıcı çıkışı seçene kadar menü tekrar gösterilir. Geçersiz girişlerde uyarı mesajı verilir.

**EN:** The menu repeats until the user selects Exit. Invalid inputs display a warning message.

---

## 🛠️ Derleme / Compilation

```bash
gcc --ansi 230104004174.c -o 230104004174
```

---

## ▶️ Çalıştırma / Usage

```bash
./230104004174
```

> **Not / Note:** Kaynak kodundaki dosya yollarını (`data.txt`, `test_1.txt`, `test-final.txt`) kendi sisteminize göre güncellemeyi unutmayın. / Make sure to update the file paths in the source code to match your system.

---

## 📊 Program Akışı / Program Flow

```
Başlat / Start
     │
     ▼
data.txt oku → Min/Max hesapla
     │
     ▼
Tüm (sepX, sepY, R1..R4) kombinasyonlarını dene
     │
     ▼
En az hatalı kombinasyonu kaydet
     │
     ▼
test_1.txt ile başarı oranını hesapla
     │
     ▼
Menü → Kullanıcı seçimine göre işlem yap
     │
     ▼
EXIT seçilince kapat
```

---

## 🔧 Kullanılan Araçlar / Tools Used

- **Dil / Language:** C (ANSI C)
- **Kütüphane / Library:** `stdio.h`
- **Derleyici / Compiler:** GCC 11.4.0

---

## 👤 Öğrenci / Student

- **Öğrenci No / Student ID:** 230104004174
- **Ders / Course:** CSE 102 – Computer Programming (Spring 2024)
- **Son Teslim / Due Date:** March 13, 2024
