# RTOS - Task 2

## 🧩 Deskripsi Tugas
Tugas ini bertujuan untuk membuat **program multitasking sederhana** menggunakan pendekatan _task-based_ (tanpa delay blocking) pada mikrokontroler **ESP32**.  
Setiap _task_ bertanggung jawab mengontrol **satu peripheral** secara independen, seperti:
- LED  
- Buzzer  
- Button  
- Servo  
- Stepper Motor  
- Rotary Encoder  
- Potensiometer  
- OLED Display  

Program dibuat sedemikian rupa agar **setiap komponen bekerja secara independen**, menyerupai konsep _Real-Time Operating System (RTOS)_ tanpa harus menggunakan FreeRTOS secara eksplisit.

---

## ⚙️ Fitur Program
| Peripheral | Fungsi | Keterangan |
|-------------|---------|------------|
| **LED** | Menyala berurutan | Menggunakan pola bergantian tiap 300 ms |
| **Buzzer** | Bunyi otomatis dengan variasi nada | Interval antar bunyi 2 detik |
| **Button** | Hitung jumlah tekan | Ditampilkan di Serial Monitor |
| **Servo** | Bergerak otomatis bolak-balik 0–180° | Pergerakan setiap 20 ms |
| **Stepper Motor** | Bergerak maju-mundur otomatis | Digerakkan menggunakan AccelStepper |
| **Rotary Encoder** | Baca arah putaran & tombol tekan | Menambah/mengurangi nilai encoder |
| **Potensiometer** | Membaca nilai analog | Update setiap 100 ms |
| **OLED Display** | Menampilkan teks “Hai” berganti animasi | Update setiap 3 detik |

---

## 🧠 Konsep Utama
Alih-alih menggunakan `delay()`, program ini menggunakan **non-blocking timing** dengan fungsi `millis()` untuk membuat setiap komponen berjalan secara **independen dan bersamaan**, menyerupai sistem multitasking dalam RTOS.

---

## 🛠️ Persiapan Lingkungan

### 1️⃣ Opsi 1 — Menggunakan [Wokwi Simulator](https://wokwi.com)
1. Buka [https://wokwi.com](https://wokwi.com)
2. Login (opsional) lalu klik **"New Project" → "ESP32 Project"**
3. Hapus kode default dan **salin seluruh kode program dari file ini**
4. Klik **"Code" → "Show Diagram.json"**  
   Lalu **paste konfigurasi hardware JSON** (yang sudah disediakan di bagian bawah)
5. Klik tombol ▶️ **Start Simulation**
6. Lihat hasil di:
   - LED yang berkedip bergantian  
   - Servo dan Stepper yang bergerak otomatis  
   - OLED menampilkan “Hai”  
   - Output di **Serial Monitor**

---

### 2️⃣ Opsi 2 — Menggunakan ESP32 Nyata
#### 💡 Alat & Komponen
- ESP32 DevKit v1  
- 5 LED + Resistor  
- Push Button  
- Buzzer aktif  
- Servo SG90  
- Driver Stepper (A4988) + Motor NEMA17  
- Potensiometer  
- Rotary Encoder (KY-040)  
- OLED Display 0.96" (I2C, alamat 0x3C)

#### 🔌 Wiring
Gunakan pin sesuai definisi di dalam kode:
| Komponen | Pin ESP32 |
|-----------|------------|
| LED1–LED5 | 2, 3, 6, 7, 8 |
| Button | 9 |
| Buzzer | 10 |
| Servo | 11 |
| Stepper | STEP=12, DIR=13 |
| Encoder | SW=14, DT=15, CLK=16 |
| Potensiometer | A1 |
| OLED | SDA=5, SCL=4 |

> ⚠️ Gunakan resistor 220–330Ω untuk LED dan sambungkan semua GND ke satu titik yang sama.

#### 🧱 Instalasi Library (di Arduino IDE)
1. Buka **Tools → Manage Libraries...**
2. Instal library berikut:
   - `Adafruit GFX`
   - `Adafruit SSD1306`
   - `ESP32Servo`
   - `AccelStepper`
3. Pilih board:  
   **Tools → Board → ESP32 Arduino → ESP32 Dev Module**
4. Upload program ke board

---

## 🧩 File JSON Wokwi (diagram konfigurasi)
Salin isi JSON berikut ke tab `diagram.json` di Wokwi agar simulasi berjalan:

<details>
<summary>Klik untuk melihat kode JSON</summary>

```json
PASTE_JSON_DI_SINI
