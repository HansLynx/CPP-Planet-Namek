#include <ESP8266WiFi.h>

String apiWritekey = ""; //masukan api thingspeak untuk melakukan upload data ke web thingspeak
const char* ssid = ""; // masukan ssid wifi
const char* password = "" ;// masukan password wifi
 
const char* server = "api.thingspeak.com"; menghubungkan ke server thingspreak

const int LM_35 = A0; //memberikan sourc code untuk input data sensor lm35 untuk masuk port A0
int input_val = 0; //menambahkan input dengan nilai default 0
float celsius = 0; //menambahkan celsius dengan nilai default 0
float farnheit = 0; //menambahkan farnheit dengan nilai default 0
WiFiClient client; //konfigurasi terhadap wifi
void setup() {
  // masukan buid dari port yang digunakan dan menggunakan pembacaan sesor 1x:
  Serial.begin(9600);
   WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

   WiFi.begin(ssid, password);      //kelompok C++ Planet Namek
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
   }
  Serial.println("");
  Serial.print("NodeMcu konek ke wifi...");
  Serial.println(ssid);
  Serial.println();
}

void loop() {
  // pemberian kode dan fungsi dari int, float yang kita buat:
  input_val = analogRead(LM_35);

 celsius = (input_val * 500) / 1023;

  farnheit = 1.8 * celsius + 32;
if (client.connect(server,80))  //melakukan upload ke web server thingspeak
  {  
    String tsData = apiWritekey; //memanggil api dari server
           tsData +="&field1="; // memanggil filed yg digunakan pada web
           tsData += String(celsius); //memanggil celsius untuk outputnya
           tsData += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // memberi jarak pada filed yang ditampilkan
     client.print(tsData);

     Serial.print("temperatur: "); //menampilkan output temperatur
     Serial.print(celsius); // memanggil celsius 
  }
  if(client.connect(server,80))
  {  
    String tsData = apiWritekey; //memanggil api dari server
           tsData +="&field2="; // memanggil filed yg digunakan pada web
           tsData += String(farnheit); //memanggil farnheit untuk outputnya
           tsData += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // memberi jarak pada filed yang ditampilkan
     client.print(tsData);

     Serial.print("\nFarnheit: "); //menampilkan output Farnheit
  Serial.println(farnheit); // memanggil farnheit untuk outputnya
     Serial.println("upload ke server Thinkspeak....");
  }
  client.stop();

 
  Serial.println("Menunggu untuk upload selanjutnya ...");
  Serial.println();
  // melakukan update 5 detik sekali
  delay(5000);
}
