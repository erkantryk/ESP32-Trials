#include <BluetoothSerial.h>

BluetoothSerial SerialBT;

const int ledPin = 4; 

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  
  SerialBT.begin("ESP32_BT"); 
  Serial.println("Bluetooth device is ready to pair");
  Serial.println("Type on or off to control the LED");
}

void loop() {
  if (SerialBT.available()) {
    String command = SerialBT.readString();
    command.trim(); 

    if (command == "on") {
      digitalWrite(ledPin, LOW); 
      SerialBT.println("LED is ON");
    }
    else if (command == "off") {
      digitalWrite(ledPin, HIGH);  
      SerialBT.println("LED is OFF");
    }
    else {
      SerialBT.println("Invalid command"); 
    }
  }
}
