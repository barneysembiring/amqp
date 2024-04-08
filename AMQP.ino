#include <WiFi.h>
#include <AMQP.h>

const char* ssid = "Kangkung Recycle";
const char* password = "123456798";
const char* RabbitMQ_server_IP = "localhost";
const int RabbitMQ_server_port = 15672; // Port AMQP RabbitMQ

WiFiClient client; // Deklarasikan objek WiFiClient di sini
AMQP amqp(&client); // Inisialisasi objek AMQP

void setup() {
  Serial.begin(115200);

  // Inisialisasi koneksi WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Membuat koneksi TCP ke RabbitMQ
  if (client.connect(RabbitMQ_server_IP, RabbitMQ_server_port)) {
    Serial.println("Connected to RabbitMQ");
  } else {
    Serial.println("Connection to RabbitMQ failed!");
  }
}

void loop() {
  // Kirim pesan ke RabbitMQ
  String message = "Hello from ESP32!";
  amqp.publish("sensor_data", "test", message);

  delay(10000); // Tunggu 10 detik sebelum mengirim pesan berikutnya
}
