#include <ESP8266WiFi.h>
const char* ssid     = "behrooz";      // SSID
const char* password = "06530653";      // Password172.217.169.243:80
const char* host = "192.168.1.4";  // IP serveur - Server IP
const int   port = 8000;            // Port serveur - Server Port
const int   watchdog = 5000;        // Fréquence du watchdog - Watchdog frequency
unsigned long previousMillis = millis();

void setup() {
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  unsigned long currentMillis = millis();

  if ( currentMillis - previousMillis > watchdog ) {
    previousMillis = currentMillis;
    WiFiClient client;

    if (!client.connect(host, port)) {
      Serial.println("connection failed");
      return;
    }

    //   String url = "https://www.instagram.com/p/CEPnn2RBA-eyekzNimDzC2x8lwIThw18Tyd1_U0/?__a=1";
    String url = "";
    //url += String(millis());
    //url += "&ip=";
    // url += WiFi.localIP().toString();
    String cookie = "sessionid=39188415601%3Avf9L6sXx7w6DA2%3A18;";
    // Envoi la requete au serveur - This will send the request to the server
    client.print(String("GET ") +  "/first/"+" HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
      if (millis() - timeout > 5000) {
        Serial.println(">>> Client Timeout !");
        client.stop();
        return;
      }
    }

    // Read all the lines of the reply from server and print them to Serial
    while (client.available()) {
      String line = client.readStringUntil('\r');
      //Serial.print("hi");
      //Serial.println(line.indexOf("this: "));
      if(line.indexOf("this")==1){
        
        line.remove(1,6);
        int salam;
        salam=line.toInt();
        Serial.println(salam);
        }
   /*   else{
        Serial.println(line);
        } */
    }
  }
}
