#include "DHT.h"             // Mengimpor library DHT untuk sensor suhu dan kelembapan

#define DHTPIN D3            // Definisikan pin yang terhubung ke sensor DHT
#define DHTTYPE DHT11        // Definisikan tipe sensor DHT (DHT11 dalam hal ini)
#define LED1 D1              // Definisikan pin LED1
#define LED2 D2              // Definisikan pin LED2

DHT dht(DHTPIN, DHTTYPE);    // Inisialisasi objek DHT dengan pin dan tipe sensor

void setup() {
  Serial.begin(9600);        // Memulai komunikasi serial dengan kecepatan 9600 bps
  dht.begin();                // Memulai sensor DHT
  
  pinMode(LED1, OUTPUT);      // Mengatur pin LED1 sebagai output
  pinMode(LED2, OUTPUT);      // Mengatur pin LED2 sebagai output
}

void loop() {
  float h = dht.readHumidity();     // Membaca nilai kelembapan dari sensor DHT
  float t = dht.readTemperature();  // Membaca nilai suhu dari sensor DHT

  if (isnan(h) || isnan(t)) {       // Memeriksa apakah pembacaan sensor valid
    Serial.println("Gagal membaca dari sensor DHT!");  // Cetak pesan kesalahan jika pembacaan gagal
    return;                         // Keluar dari fungsi loop
  }

  Serial.print("Kelembapan: ");      // Cetak label kelembapan
  Serial.print(h);                   // Cetak nilai kelembapan
  Serial.print(" %\t");               // Cetak satuan untuk kelembapan
  Serial.print("Suhu: ");            // Cetak label suhu
  Serial.print(t);                   // Cetak nilai suhu
  Serial.println(" *C ");             // Cetak satuan untuk suhu

  if (t > 30) {                      // Jika suhu lebih dari 30 derajat Celsius
    digitalWrite(LED1, HIGH);        // Nyalakan LED1
  } else {                           // Jika tidak
    digitalWrite(LED1, LOW);         // Matikan LED1
  }

  if (t < 20) {                      // Jika suhu kurang dari 20 derajat Celsius
    digitalWrite(LED2, HIGH);        // Nyalakan LED2
  } else {                           // Jika tidak
    digitalWrite(LED2, LOW);         // Matikan LED2
  }

  delay(2000);                       // Tunda selama 2 detik sebelum membaca ulang sensor
}
