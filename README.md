# 3223600047_Bintang-Endra-Erlangga_TugasRTOS
Berisikan program dan demo RTOS dari ESP32S3 

Langkah Percobaan

1. Persiapan Alat dan Bahan

   - ESP32-S3 Board
   - Sensor (misalnya: Potensiometer, DHT11, atau sensor cahaya)
   - Aktuator (misalnya: LED, Servo, atau Buzzer)
   - Breadboard dan kabel jumper
   - Arduino IDE atau VSCode dengan PlatformIO

2. Tujuan Percobaan

   - Memaksimalkan penggunaan dua core pada ESP32-S3.
   - Menerapkan konsep multitasking menggunakan FreeRTOS.
   - Membagi beban kerja antara dua core untuk meningkatkan efisiensi pemrosesan.
   - Mengamati bagaimana kedua core dapat menjalankan task secara paralel tanpa saling mengganggu.

3. Konfigurasi Task FreeRTOS

   - Buat dua task:
     - TaskSensor1/aktuator1 pada Core 0, bertugas membaca data dari sensor secara periodik.
     - TaskSensor2/aktuator2 pada Core 1, bertugas mengontrol aktuator berdasarkan nilai sensor.
   - Gunakan fungsi `xTaskCreatePinnedToCore()` untuk menempatkan setiap task pada core tertentu.
   - Tentukan prioritas task agar sistem tetap seimbang dan responsif.

4. Pembagian Beban Kerja Antar Core

   - Core 0: Fokus pada pengambilan dan pemrosesan data sensor.
   - Core 1: Fokus pada kontrol output dan tampilan hasil.

5. Pengujian

   - Upload program ke ESP32-S3.
   - Buka Serial Monitor untuk memantau eksekusi kedua task.
   - Ubah input sensor dan amati bagaimana aktuator merespons secara real-time.
   - Perhatikan bahwa kedua core berjalan simultan dan beban kerja terbagi rata.

---
Link Video Demo untuk masing-masing percobaan
https://drive.google.com/drive/folders/1U_H2UFLWd7YuUUSefW6HWZk4DE_HCtgZ?usp=sharing
