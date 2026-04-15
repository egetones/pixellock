<div align="center">

# pixellock

![C++](https://img.shields.io/badge/C++-Binary_Manipulation-blue?style=flat&logo=c%2B%2B)
![License](https://img.shields.io/badge/License-MIT-green)
![Type](https://img.shields.io/badge/Type-Steganography-purple)

<p>
  <strong>A CLI tool to hide secret text inside BMP images using LSB Steganography.</strong>
</p>

[Report Bug](https://github.com/egetones/pixellock/issues) · [Request Feature](https://github.com/egetones/pixellock/issues)

</div>

---

## Description

**pixellock** is a steganography tool written in C++. It utilizes the **Least Significant Bit (LSB)** technique to embed hidden text messages directly into the binary data of an image.

The human eye cannot distinguish the slight color variations caused by LSB modification, making the message effectively invisible. This tool is designed to work with 24-bit `.bmp` (Bitmap) images to ensure lossless data manipulation.

### Key Features

  **LSB Manipulation:** Modifies only the last bit of each pixel byte.
  **Invisible Storage:** The visual appearance of the image remains identical.
  **Text Embedding:** Supports hiding standard ASCII text strings.
  **Lightweight:** Written in pure C++ with no external dependencies.

---

## Usage

### 1. Compile
```bash
make
```

### 2. Hide a Message
You need a `.bmp` image file. (You can convert any image to bmp using GIMP or online tools).

```bash
./pixellock hide image.bmp "This is a top secret message!"
```
*The `image.bmp` now contains the hidden data.*

### 3. Reveal the Message
To read the secret data from the image:

```bash
./pixellock reveal image.bmp
```
**Output:**
```text
[+] Gizli Mesaj: This is a top secret message!
```

---

## ⚠️ Note
Use only **24-bit BMP** files. Formats like JPEG or PNG use compression that will destroy the LSB data, corrupting the hidden message.

---

## License

Distributed under the MIT License. See `LICENSE` for more information.
Çrş 15 Nis 2026 22:06:41 +03
