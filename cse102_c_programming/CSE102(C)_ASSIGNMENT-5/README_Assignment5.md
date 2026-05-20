# CSE 102 – Ödev 5 / Assignment 5

## 🚀 Günlük Basın – Uzay Haberleri Okuyucu / Daily Press – Space News Reader

---

## 📌 Açıklama / Description

**TR:**
Bu ödev, Türkiye'nin ilk astronotu Alper Gezeravcı'nın ISS'deki görevine ilişkin 4 farklı haber metnini okuyan, okunan haberleri kalıcı olarak kaydeden ve her haberdeki gizli "sihirli sayılar"dan deney anahtarlarını hesaplayan bir C programıdır. Program tamamen `menu()` fonksiyonu üzerinden çalışır.

**EN:**
This assignment is a C program that reads 4 different news texts about Turkey's first astronaut Alper Gezeravcı's mission on the ISS, persistently tracks which news have been read, and calculates experiment keys from hidden "magic numbers" in each news text. The program operates entirely through the `menu()` function.

---

## 📁 Dosya Yapısı / File Structure

```
├── 230104004174.c       # Ana kaynak kodu / Main source code
└── news/
    ├── 1.txt            # Haber 1 / News 1
    ├── 2.txt            # Haber 2 / News 2
    ├── 3.txt            # Haber 3 / News 3
    └── 4.txt            # Haber 4 / News 4
```

> Program ayrıca okunan haberleri kaydetmek için `readed_news.txt` dosyasını otomatik oluşturur.
> The program also automatically creates `readed_news.txt` to store read history.

---

## ⚙️ Fonksiyonlar / Functions

```c
void readTheTitle(FILE *file_name, int order);
```
**TR:** Haber dosyasının ilk satırını (başlığını) ekrana yazdırır.

**EN:** Prints the first line (title) of the news file to the screen.

---

```c
void readTheNew1();
void readTheNew2();
void readTheNew3();
void readTheNew4();
```
**TR:** İlgili haber dosyasını açarak tüm içeriği ekrana yazdırır. Her haber için dosya ayrı ayrı açılıp kapatılır (tekrar okunabilmesi için).

**EN:** Opens the corresponding news file and prints its full content. Each news file is opened and closed independently to allow re-reading.

---

```c
int isNewsAdded(FILE *readed_news_list, int order_of_list);
```
**TR:** Verilen haber numarasının `readed_news.txt` dosyasında kayıtlı olup olmadığını kontrol eder. Kayıtlıysa `1`, değilse `0` döner.

**EN:** Checks whether the given news number is recorded in `readed_news.txt`. Returns `1` if found, `0` otherwise.

---

```c
void readedNews(FILE *readed_news_list);
```
**TR:** Daha önce okunan haberlerin numaralarını `readed_news.txt` dosyasından okuyarak ekrana listeler.

**EN:** Reads and lists the numbers of previously read news from `readed_news.txt`.

---

```c
int findMagicNumberFor_1();
int findMagicNumberFor_2();
int findMagicNumberFor_3();
int findMagicNumberFor_4();
```
**TR:** İlgili haber dosyasındaki `#` işaretinin hemen ardından gelen rakamları (sihirli sayıları) bulur ve aşağıdaki formülle deney anahtarını hesaplar.

**EN:** Finds the digits (magic numbers) immediately following `#` signs in the corresponding news file and calculates the experiment key using the formula below.

---

```c
void menu();
```
**TR:** Programın tüm akışını yönetir: başlıkları listeler, menüyü gösterir ve kullanıcı seçimlerini işler.

**EN:** Manages the entire program flow: lists headlines, displays the menu, and handles user selections.

---

## 🔢 Sihirli Sayı Formülü / Magic Number Formula

Her haber metninde `#` işaretinin yanında gizli rakamlar (`X_i`) bulunur. Deney anahtarı aşağıdaki formülle hesaplanır:

Each news text contains hidden digits (`X_i`) next to `#` signs. The experiment key is calculated with:

```
f(x) = x³ - x² + 2
g(x) = x²

Secret Number = Σ g(f(Xᵢ))   (i = 1 to n)
```

**Uygulama / Implementation:**
```c
totalOfMagicNumbers += ((X³ - X² + 2)² )
```

---

## 🖥️ Menü Seçenekleri / Menu Options

| Tuş / Key | İşlev (TR) | Function (EN) |
|:-:|---|---|
| `a` | Haber oku (okunmuşsa tekrar okuma sorusu) | Read a news (prompts if already read) |
| `b` | Okunan haberleri listele | List all read news |
| `c` | Haberdeki sihirli sayıdan deney anahtarını hesapla | Decrypt experiment key from news |

---

## 💾 Kalıcı Okuma Takibi / Persistent Read Tracking

**TR:**
- Okunan haberlerin ID'leri `readed_news.txt` dosyasına `ID;` formatında kaydedilir.
- Program kapatılıp tekrar açıldığında okuma geçmişi korunur.
- Aynı haber tekrar seçilirse kullanıcıya "Tekrar okumak ister misiniz?" sorusu sorulur.
- Bir haber birden fazla kez okunsa da listeye yalnızca bir kez eklenir.

**EN:**
- Read news IDs are saved to `readed_news.txt` in `ID;` format.
- Read history is preserved when the program is closed and reopened.
- If a news item is selected again, the user is asked "Would you like to read it again?"
- Even if read multiple times, a news item is only added to the list once.

---

## 📊 Örnek Çıktı / Sample Output

```
**********Daily Press**********
Today's news are listed for you :
Title of 1. news: Astronot Alper Gezeravcı'nın Dünya'ya dönüşü ertelendi
Title of 2. news: Bakan Kacır, Astronot Gezeravcı ile Videokonferans Görüşmesi Gerçekleştirdi
Title of 3. news: Alper Gezeravcı uzayda 9. deneyini yaptı
Title of 4. news: Astronotların uzaydaki ilk sözleri

What do you want to do?
a.Read a new
b.List the readed news
c.Get decrypted information from the news
c
Which news would you like to decrypt?: 1
[news content printed here...]
First Experiment Key = 257232

Do you want to continue? Yes(y)/No(n): y

What do you want to do?
...
b
3. new is readed.
2. new is readed.
1. new is readed.
Do you want to continue? Yes(y)/No(n): n
Good Bye!
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

> **Not / Note:** Kaynak kodundaki dosya yollarını (`news/` klasörü ve `readed_news.txt`) kendi sisteminize göre güncellemeyi unutmayın. / Make sure to update the hardcoded file paths in the source code to match your system.

---

## 🔧 Kullanılan Araçlar / Tools Used

- **Dil / Language:** C (ANSI C)
- **Kütüphane / Library:** `stdio.h`
- **Kalıcı Depolama / Persistent Storage:** `readed_news.txt` (veritabanı dosyası / database file)
- **Derleyici / Compiler:** GCC 11.4.0

---

## 👤 Öğrenci / Student

- **Öğrenci No / Student ID:** 230104004174
- **Ders / Course:** CSE 102 – Computer Programming (Spring 2024)
- **Son Teslim / Due Date:** April 03, 2024
