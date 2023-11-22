//       Oudoum Ali Houmed
//         19010011092

#include <Wire.h>  // I2C protokolünü kullanabilmek için Wire kütüphanesini dahil ediyoruz
#include <Adafruit_GFX.h>  // Adafruit GFX kütüphanesi ekranla çizim işlemleri için
#include <Adafruit_SSD1306.h>  // Adafruit SSD1306 kütüphanesi OLED ekran kontrolü için
#include "MPU6050.h"  // MPU6050 sensörünü kullanabilmek için kütüphaneyi dahil ediyoruz

#define SCREEN_WIDTH 128  // OLED ekran genişliği
#define SCREEN_HEIGHT 64  // OLED ekran yüksekliği

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire);  // SSD1306 OLED ekranının bir nesnesini oluşturuyoruz
MPU6050 mpu;  // MPU6050 sensörünün bir nesnesini oluşturuyoruz

void setup() {
  Wire.begin();  // I2C iletişimini başlatıyoruz
  Serial.begin(9600);  // Seri iletişim başlatıyoruz, baud hızı 9600

  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {  // Ekranın başlatılması ve kontrol edilmesi
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  display.clearDisplay();  // Ekranın başlangıçta temizlenmesi

  mpu.initialize();  // MPU6050 sensörünü başlatıyoruz
}

void loop() {
  // MPU6050'den verileri okuyoruz
  int16_t ax, ay, az, gx, gy, gz, temp;
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  temp = mpu.getTemperature();

  // Sensör verilerini düzgün bir formata dönüştürüyoruz
  float x = ax / 16384.0; // m/s^2
  float y = ay / 16384.0; // m/s^2
  float z = az / 16384.0; // m/s^2
  float x1 = gx / 131.0; // rps
  float y1 = gy / 131.0; // rps
  float z1 = gz / 131.0; // rps
  float temperature = temp / 340.0 + 36.53; // degC

  // OLED Displayde gösterim
  display.clearDisplay();  // Ekranı temizliyoruz
  display.setTextSize(1);  // Yazı tipi boyutunu ayarlıyoruz
  display.setTextColor(WHITE);  // Yazı tipi rengini ayarlıyoruz
  
  display.setCursor(0, 0);  // Imleci belirli bir konuma ayarlıyoruz
  display.println("Accelerometer-m/s^2: ");
  display.print(x1);
  display.print(", ");
  display.print(y1);
  display.print(", ");
  display.println(z1);
  //display.print("\n");
  display.println("Gyroscope-rps: ");
  display.print(x1);
  display.print(", ");
  display.print(y1);
  display.print(", ");
  display.println(z1);
  //display.print("\n");  
  display.println("Temperature: ");
  display.print(temperature);
  display.println(" degC");

  // Seri terminalde gösterim
  Serial.println("Accelerometer – m/s^2: ");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.println(z);
  Serial.println("Gyroscope – rps: ");
  Serial.print(x);
  Serial.print(", ");
  Serial.print(y);
  Serial.print(", ");
  Serial.println(z);
  Serial.println("Temperature: ");
  Serial.print(temperature);
  Serial.println(" degC");


  display.display();  // Ekranı güncelliyoruz
  delay(2000);
}
