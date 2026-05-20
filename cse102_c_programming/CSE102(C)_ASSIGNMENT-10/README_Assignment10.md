# CSE 102 – Ödev 10 / Assignment 10

> **Ders / Course:** CSE 102 – Computer Programming (Spring 2024)  
> **Öğrenci / Student:** Görkem Uysal  
> **Teslim Tarihi / Due Date:** May 17, 2024

---

## 🇹🇷 Türkçe

### 📌 Genel Açıklama

Bu ödevde assembly dili komutlarını simüle eden bir C programı geliştirilmiştir. Program, `.asm` uzantılı bir dosyayı okuyarak komutları sırasıyla çözümler ve çalıştırır. İkili (binary) ve onluk (decimal) sayı dönüşümleri, komut seti okuma ve opcode eşleştirme işlemleri `struct` kullanılarak gerçekleştirilmiştir.

> ⚠️ **Not:** Ödev tam olarak tamamlanamamıştır. Binary/decimal dönüşümleri ve `instructions_1.txt` dosyasından opcode okuma kısımları çalışmaktadır. Komutların tam olarak yürütülmesi (execute) kısmı eksik kalmıştır.

---

### 🏗️ Mimari

Simülatör aşağıdaki bileşenlerden oluşur:

| Bileşen | Açıklama | Boyut |
|---------|----------|-------|
| Register A | Genel amaçlı yazmaç | 8 bit |
| Register B | Genel amaçlı yazmaç | 8 bit |
| Program Counter (PC) | Çalışan satırı tutar | 16 bit |
| Instruction Register (IR) | Aktif komutu tutar | 24 bit |
| Bellek | Stack yapısında, her sözcük 8 bit | Değişken |

---

### 🔧 Fonksiyonlar

**`to_binary(int)`** — Onluk sayıyı 8 bitlik ikili gösterime çevirir.

**`to_decimal(char[])`** — 8 bitlik ikili karakter dizisini onluk sayıya çevirir.

**`find_opcode(...)`** — Komut adını `instructions_1.txt` dosyasındaki komut seti ile eşleştirip opcode'unu döndürür.

**`registersExecute(...)`** — Opcode'a göre register üzerinde işlem yapar (ADD, SUB, AND, OR, SHL, SHR vb.).

**`execute_program(...)`** — Kullanıcıdan `.asm` dosya adı alır, satır satır okur ve her komut için opcode arar.

**`main()`** — `instructions_1.txt` dosyasını okur, komut setini `Instructions` struct'ına yükler ve simülatörü başlatır.

---

### 📋 Komut Seti (Özet)

`instructions_1.txt` dosyası `|` ile ayrılmış 30 komut içerir:

| Opcode | Tür | Komut | Açıklama |
|--------|-----|-------|----------|
| 00000001 | G | ADD A B | A = A + B |
| 00000010 | T | ADDI A I | A = A + I |
| 00001010 | G | SUB A B | A = A - B |
| 00001101 | T | INC A | A = A + 1 |
| 00001110 | T | DEC A | B = B - 1 |
| 00001111 | T | SHL A I | A sola I kez kaydır |
| 00010000 | T | SHR A I | A sağa I kez kaydır |
| 00010111 | G | SWP A B | A ve B'yi değiştir |
| 00011010 | G | PRI A | A'yı onlukta yazdır |
| 00011101 | T | LDAI A I | A = I |
| 00011110 | - | EXIT | Programı bitir |
| ... | ... | ... | ... |

Tam komut seti için `instructions_1.txt` dosyasına bakınız.

---

### Kullanılan Kavramlar

- `struct` ile komut seti ve register modelleme (`Instructions`, `Registers`)
- Binary ↔ Decimal dönüşümü
- `strtok` ile `|` ayracına göre satır ayrıştırma
- `strstr` ve `strcmp` ile komut eşleştirme
- Dosya okuma (`fgets`, `fscanf`, `fopen`, `fclose`)

---

### Derleme ve Çalıştırma

```bash
gcc --ansi 230104004174.c -o 230104004174
./230104004174
```

Program çalışınca `.asm` uzantılı bir dosya adı girmek gerekir:

```
enter a file name: example.asm
```

> ⚠️ `main()` içindeki `instructions_1.txt` dosya yolunu kendi sisteminize göre güncelleyin.

---

### `instructions_1.txt` Formatı

```
opcode|tür|komut|açıklama
00000001|G|ADD A B|addition operation
00000010|T|ADDI A I|addition with number
...
```

---

### 📁 Dosya Yapısı

```
📦 Assignment_10/
├── 230104004174.c          # Kaynak kod
├── instructions_1.txt      # Komut seti tanım dosyası
├── 230104004174.pdf        # Program çıktıları ve notlar
└── README.md
```

---

---

## 🇬🇧 English

### 📌 Overview

This assignment implements an assembly language execution simulator in C. The program reads a `.asm` file and processes instructions through a fetch-decode-execute cycle. Binary/decimal conversions, instruction set loading, and opcode matching are implemented using structs.

> ⚠️ **Note:** The assignment was not fully completed. Binary/decimal conversions and opcode lookup from `instructions_1.txt` are functional. Full instruction execution is incomplete.

---

### 🏗️ Architecture

| Component | Description | Size |
|-----------|-------------|------|
| Register A | General-purpose register | 8 bits |
| Register B | General-purpose register | 8 bits |
| Program Counter (PC) | Tracks current instruction line | 16 bits |
| Instruction Register (IR) | Holds the active instruction | 24 bits |
| Memory | Stack-structured, one word per slot | 8 bits/word |

---

### 🔧 Functions

**`to_binary(int)`** — Converts a decimal integer to an 8-bit binary representation.

**`to_decimal(char[])`** — Converts an 8-bit binary character array to its decimal value.

**`find_opcode(...)`** — Matches an instruction name against the loaded instruction set and returns its opcode.

**`registersExecute(...)`** — Performs the operation specified by the opcode on the registers (ADD, SUB, AND, OR, SHL, SHR, etc.).

**`execute_program(...)`** — Prompts for a `.asm` filename, reads it line by line, and looks up the opcode for each instruction.

**`main()`** — Reads `instructions_1.txt`, loads the instruction set into the `Instructions` struct, and launches the simulator.

---

### 📋 Instruction Set (Summary)

`instructions_1.txt` contains 30 instructions separated by `|`:

| Opcode | Type | Instruction | Description |
|--------|------|-------------|-------------|
| 00000001 | G | ADD A B | A = A + B |
| 00000010 | T | ADDI A I | A = A + I |
| 00001010 | G | SUB A B | A = A - B |
| 00001101 | T | INC A | A = A + 1 |
| 00001110 | T | DEC A | B = B - 1 |
| 00001111 | T | SHL A I | Shift A left I times |
| 00010000 | T | SHR A I | Shift A right I times |
| 00010111 | G | SWP A B | Swap A and B |
| 00011010 | G | PRI A | Print A as decimal |
| 00011101 | T | LDAI A I | A = I |
| 00011110 | - | EXIT | End the program |
| ... | ... | ... | ... |

See `instructions_1.txt` for the full instruction set.

---

### Concepts Used

- Struct-based modeling for instruction set and registers (`Instructions`, `Registers`)
- Binary ↔ Decimal conversion
- Line parsing with `strtok` using `|` as delimiter
- Instruction matching with `strstr` and `strcmp`
- File I/O (`fgets`, `fscanf`, `fopen`, `fclose`)

---

### Compile & Run

```bash
gcc --ansi 230104004174.c -o 230104004174
./230104004174
```

When prompted, enter a `.asm` file name:

```
enter a file name: example.asm
```

> ⚠️ Update the file path for `instructions_1.txt` inside `main()` to match your system.

---

### `instructions_1.txt` Format

```
opcode|type|instruction|description
00000001|G|ADD A B|addition operation
00000010|T|ADDI A I|addition with number
...
```

---

### 📁 File Structure

```
📦 Assignment_10/
├── 230104004174.c          # Source code
├── instructions_1.txt      # Instruction set definition file
├── 230104004174.pdf        # Program outputs and notes
└── README.md
```
