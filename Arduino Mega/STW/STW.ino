#include <WiFi.h>
#include "PubSubClient.h"

char ssid[] = "HACKATON_Mty";     //  your network SSID (name)
char pass[] = "HackGlobal78415";    // your network password

int status = WL_IDLE_STATUS;     // the Wifi radio's status
char mqttServer[] = "broker.mqttdashboard.com";
char mqttText[] = "STWAmber0990";

WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

String incomingText = "";   // for incoming serial data
int Foquito = 0; // for Foquitos

void setup() {
    Serial.begin(9600);     // opens serial port, sets data rate to 9600 bps
    Serial.println("turn lights OFF");
    digitalWrite(21, LOW); //A
    digitalWrite(23, LOW); //B
    digitalWrite(24, LOW); //C
    digitalWrite(25, LOW); //D
    digitalWrite(26, LOW); //E
    digitalWrite(27, LOW); //F
    digitalWrite(28, LOW); //G
    digitalWrite(29, LOW); //H
    digitalWrite(30, LOW); //I
    digitalWrite(31, LOW); //J
    digitalWrite(32, LOW); //K
    digitalWrite(33, LOW); //L
    digitalWrite(34, LOW); //M
    digitalWrite(35, LOW); //N
    digitalWrite(36, LOW); //O
    digitalWrite(37, LOW); //P
    digitalWrite(38, LOW); //Q
    digitalWrite(39, LOW); //R
    digitalWrite(40, LOW); //S
    digitalWrite(41, LOW); //T
    digitalWrite(42, LOW); //O
    digitalWrite(43, LOW); //V
    digitalWrite(44, LOW); //W
    digitalWrite(45, LOW); //X
    digitalWrite(46, LOW); //Y
    digitalWrite(47, LOW); //Z

  mqttClient.setServer(mqttServer, 1883);
  mqttClient.setCallback(callback);

  connectWifi();
}

void loop() {

        // send data only when you receive data:
        if (Serial.available() > 0) {
                // read the incoming byte:
                incomingText = Serial.readString();
                incomingText.toUpperCase();

                for(auto CHAR: incomingText){
                  SelectChar(CHAR);
                  }

        }
        mqttClient.loop();
}

void SelectChar(char CHAR){
  switch(CHAR){
    case 'A':Foquito = 22; break;
    case 'B':Foquito = 23; break;
    case 'C':Foquito = 24; break;
    case 'D':Foquito = 25; break;
    case 'E':Foquito = 26; break;
    case 'F':Foquito = 27; break;
    case 'G':Foquito = 28; break;
    case 'H':Foquito = 29; break;
    case 'I':Foquito = 30; break;
    case 'J':Foquito = 31; break;
    case 'K':Foquito = 32; break;
    case 'L':Foquito = 33; break;
    case 'M':Foquito = 34; break;
    case 'N':Foquito = 35; break;
    case 'O':Foquito = 36; break;
    case 'P':Foquito = 37; break;
    case 'Q':Foquito = 38; break;
    case 'R':Foquito = 39; break;
    case 'S':Foquito = 40; break;
    case 'T':Foquito = 41; break;
    case 'U':Foquito = 42; break;
    case 'V':Foquito = 43; break;
    case 'W':Foquito = 44; break;
    case 'X':Foquito = 45; break;
    case 'Y':Foquito = 46; break;
    case 'Z':Foquito = 47; break;
    default: Foquito = 0; break;
    }
    Serial.println(CHAR);
    if(Foquito != 0){
    digitalWrite(Foquito, HIGH);
    Serial.println(Foquito);
    delay(800);
    digitalWrite(Foquito, LOW);
    }
    else{delay(1500);}
    
    
}

void callback(char* topic, uint8_t* payload, unsigned int length) {

  // output to serial monitor
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i=0;i<length;i++) {
    char CHART = (char)payload[i];
    String CHART2 = String(CHART);
    CHART2.toUpperCase();
    for(auto CHAR: CHART2){
        SelectChar(CHAR);
        }
  }
  Serial.println();
  
}

void subscribeToMqttTopic(char atopic[]) {

  if (mqttClient.subscribe(atopic)) {
    
    Serial.print("subscribed to topic ");
    Serial.print(atopic);
    Serial.println(" successfully");
    
  } else {
    
    Serial.print("unable to subscribe to topic");
    Serial.println(atopic);
    // Wait 5 seconds before retrying
    delay(5000);
    subscribeToMqttTopic(atopic);
    
  }
  
}

void connectMqtt() {
  
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    
    Serial.println("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect("hiveMq")) {
      
      Serial.println("mqtt connected");
      // you can subscribe/publish to topics now... 
      subscribeToMqttTopic(mqttText);
      
    } else {
      
      Serial.print("failed, rc=");
      Serial.print(mqttClient.state());
      Serial.println(" try again in 3 seconds");
      // Wait 3 seconds before retrying
      delay(3000);
      
    }
  }
  
}

void connectWifi() {
  
  Serial.println("Attempting to connect to WPA network...");
  status = WiFi.begin(ssid, pass);

  // if you're not connected, stop here:
  if ( status != WL_CONNECTED) {
    
    Serial.println("Couldn't connect to wifi, retry in 5 secs");
    delay(5000);
    connectWifi();
    
  } else {
    
    Serial.println("Connected to wifi network");
    connectMqtt();
    
  }
  
}

