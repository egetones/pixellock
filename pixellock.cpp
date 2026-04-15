#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <bitset>

// Renkler
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define CYAN    "\033[36m"
#define YELLOW  "\033[33m"

using namespace std;

// BMP Header boyutu (Genellikle 54 byte)
const int HEADER_SIZE = 54;

void hideMessage(string imgPath, string secretMsg) {
    // Resmi Binary modda aç
    fstream file(imgPath, ios::in | ios::out | ios::binary);
    if (!file) {
        cerr << RED << "[!] Hata: Resim dosyası açılamadı." << RESET << endl;
        return;
    }

    // Mesajın sonuna 'null terminator' ekle ki nerede duracağımızı bilelim
    secretMsg += '\0';

    // Header'ı atla (İlk 54 byte'a dokunma, resim bozulur)
    file.seekp(HEADER_SIZE, ios::beg);

    cout << CYAN << "[*] Mesaj gizleniyor..." << RESET << endl;

    for (char c : secretMsg) {
        // Her karakter 8 bittir
        bitset<8> charBits(c);

        for (int i = 0; i < 8; i++) {
            char imgByte;
            file.read(&imgByte, 1); // Resimden 1 byte oku

            // En Önemsiz Biti (LSB) temizle (son biti 0 yap)
            imgByte &= 0xFE; 
            
            // Mesajın bitini LSB'ye yerleştir
            // charBits[i] yerine charBits[7-i] kullanarak sırayı koruyoruz
            imgByte |= charBits[7 - i];

            // Değiştirilmiş byte'ı geri yaz (bir adım geri gidip yaz)
            file.seekp(-1, ios::cur);
            file.write(&imgByte, 1);
        }
    }
    
    file.close();
    cout << GREEN << "[+] Başarılı! Mesaj resmin içine gömüldü." << RESET << endl;
}

void revealMessage(string imgPath) {
    ifstream file(imgPath, ios::binary);
    if (!file) {
        cerr << RED << "[!] Hata: Resim dosyası açılamadı." << RESET << endl;
        return;
    }

    file.seekg(HEADER_SIZE, ios::beg);
    
    string revealedMsg = "";
    char charBuffer = 0;
    int bitCount = 0;

    cout << YELLOW << "[*] Mesaj okunuyor..." << RESET << endl;

    char imgByte;
    while (file.read(&imgByte, 1)) {
        // LSB'yi al (imgByte & 1)
        int lsb = imgByte & 1;

        // Biti buffer'a ekle (Sola kaydır ve ekle)
        charBuffer = (charBuffer << 1) | lsb;
        bitCount++;

        // 8 bit toplandığında 1 karakter oluşur
        if (bitCount == 8) {
            // Null karakter (\0) gördüysek mesaj bitmiştir
            if (charBuffer == '\0') break;

            revealedMsg += charBuffer;
            bitCount = 0;
            charBuffer = 0;
        }
    }

    cout << GREEN << "[+] Gizli Mesaj: " << RESET << revealedMsg << endl;
    file.close();
}

int main(int argc, char* argv[]) {
    cout << R"(
    ____  _          __   __           __  
   / __ \(_)  _____ / /  / /   ____   / /__
  / /_/ / / |/_/ _ \/ /  / /   / __ \ / //_/
 / ____/ />  </  __/ /  / /___/ /_/ // ,<   
/_/   /_/_/|_|\___/_/  /_____/\____//_/|_|  
    LSB Steganography Tool v1.0
    )" << endl;

    if (argc < 3) {
        cout << "Kullanım:" << endl;
        cout << "  Gizle: ./pixellock hide <resim.bmp> \"Gizli Mesaj\"" << endl;
        cout << "  Oku:   ./pixellock reveal <resim.bmp>" << endl;
        return 1;
    }

    string mode = argv[1];
    string imgPath = argv[2];

    if (mode == "hide" && argc == 4) {
        hideMessage(imgPath, argv[3]);
    } else if (mode == "reveal") {
        revealMessage(imgPath);
    } else {
        cout << RED << "[!] Hatalı parametre." << RESET << endl;
    }

    return 0;
}
