# CSE 102 – Ödev 1 / Assignment 1

## 🔐 Caesar Cipher – C Kodu Şifreleme & Çözme / C Code Encryption & Decryption

---

## 📌 Açıklama / Description

**TR:**
Bu ödev, geçerli bir C kaynak kodunu özel bir şifreleme yöntemiyle şifreleyen ve çözen iki program içermektedir. Şifreleme anahtarı, öğrenci numarasının basamakları tek basamaklı bir sayıya ulaşana kadar toplanmasıyla elde edilir. Şifreleme için Caesar şifresi yöntemi kullanılmaktadır.

**EN:**
This assignment contains two programs that encrypt and decrypt a valid C source code using a custom cipher method. The encryption key is derived by repeatedly summing the digits of the student ID until a single digit is reached. The Caesar cipher method is used for encryption.

---

## 📁 Dosya Yapısı / File Structure

```
├── 230104004174_part1.c   # Şifreleme programı / Encryption program
└── 230104004174_part2.c   # Çözme programı / Decryption program
```

---

## ⚙️ Nasıl Çalışır / How It Works

### Anahtar Hesaplama / Key Calculation

**TR:** Öğrenci numarasının tüm basamakları, sonuç tek basamaklı olana kadar tekrar tekrar toplanır.

**EN:** All digits of the student ID are summed repeatedly until the result is a single digit.

```
230104004174 → 2+3+0+1+0+4+0+0+4+1+7+4 = 26
26 → 2+6 = 8
Key = 8
```

### Part 1 – Şifreleme / Encryption

**TR:**
- `/* ... */` içindeki yorumlar şifrelenmez; bunun yerine `@ <şifreli_karakter_sayısı>` formatında bir işaretçi bırakılır.
- Diğer karakterler 61 karakterlik özel alfabe üzerinde Caesar şifresiyle şifrelenir.
- Boşluk ve satır sonu karakterleri olduğu gibi aktarılır.

**EN:**
- Comments inside `/* ... */` are not encrypted; instead, a marker `@ <encrypted_char_count>` is placed.
- All other characters are encrypted using Caesar cipher over a custom 61-character alphabet.
- Spaces and newlines are passed through unchanged.

### Part 2 – Çözme / Decryption

**TR:**
- `@` işaretçisiyle karşılaşıldığında, `/*There is a XX characters are as a comment.*/` formatında çıktı verilir.
- Diğer şifreli karakterler ters Caesar yöntemiyle çözülür.

**EN:**
- When the `@` marker is encountered, the output is `/*There is a XX characters are as a comment.*/`.
- All other encrypted characters are decrypted using the reverse Caesar method.

### Alfabe / Alphabet

```c
char alphabet[61] = {
  'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s',
  't','u','v','w','x','y','z','(','<','=','+',')','[','*','/',']','{','>','!',
  '-','}','?','\\','&','|','%','_',';','"','#','.','\'','0','1','2','3','4',
  '5','6','7','8','9'
};
```

---

## 🛠️ Derleme / Compilation

```bash
gcc --ansi 230104004174_part1.c -o homework1_1
gcc --ansi 230104004174_part2.c -o homework1_2
```

---

## ▶️ Çalıştırma / Usage

```bash
# Şifreleme / Encrypt
./homework1_1 < input.txt > encrypted.txt

# Çözme / Decrypt
./homework1_2 < encrypted.txt > decrypted.txt
```

---

## 📊 Örnek / Example

**Girdi / Input (`input.txt`):**
```c
#include <stdio.h>
int main() { /*This is the main function.*/
    int number_one = 3;
    int number_two = 4;
    int add = number_one + number_two;
    return 0;
}
```

**Şifreli Çıktı / Encrypted Output (`encrypted.txt`):**
```
5qvkt=ln {(<lqw6p%
5qv< ulqv]·  @ aa
  qv< v=ujmz2wvm > b3
...
```

**Çözülmüş Çıktı / Decrypted Output (`decrypted.txt`):**
```c
#include <stdio.h>
int main() { /*There is a 22 characters are as a comment.*/
    int number_one = 3;
    int number_two = 4;
    int add = number_one + number_two;
    return 0;
}
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
- **Son Teslim / Due Date:** March 11, 2024
