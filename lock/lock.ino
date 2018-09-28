
//#include <EEPROM.h>
#include <SPI.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <math.h>


///////////////////////////////////////////////////////////////////
//----- OLED instance
//// If using software SPI with arduino pro micro:
#define OLED_CLK   A3    // D0
#define OLED_MOSI  A2   // D1
#define OLED_DC    A1     // DC
#define OLED_CS    15    // CS
#define OLED_RESET 15     // RES

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#if (SSD1306_LCDHEIGHT != 64)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif
///////////////////////////////////////////////////////////////////


SoftwareSerial bleSerial(16, 14); //16:RX 14:TX

int sensrPin = 9;
int relayPin = 8;
int sensrValue;
long startTime;
long markTime;
long durTime;
String cmd;
String mode; //debug / TurnOn Once / Always On / Timer

void setup() {
  PORTD |= (1 << PORTD5);
  PORTB |= (1 << PORTB0);
  //----- by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);  // initialize display (for the 128x64)
  
  Serial.begin(9600);
  bleSerial.begin(9600);
  pinMode(sensrPin, INPUT);
  pinMode(relayPin, OUTPUT);

  drawStartUp();    // Show TokyoWatch Logo

  mode = "initial";
}






void loop() {
  
  markTime = millis();

  if(mode == "initial"){showText("Lock is ready ...", 1, 10);}

  if(mode == "OFF" || mode =="initial"){
      // start reading sensor
      sensrValue = digitalRead(sensrPin);
      if(sensrValue == 1){
        digitalWrite(relayPin, HIGH);
        startTime = millis();
        showText("PUSH", 5, 5);
        mode = "ONCE";
      }
  }


  
  
  
  if(bleSerial.available()){
    
    cmd = bleSerial.readString();
    // unlock once with 3 seconds delay: ASCII:??????? 
    if(cmd == "unlockonce3sec"){
      digitalWrite(relayPin, HIGH);
      startTime = millis();
      bleSerial.write("unlock for 1 time!");
      showText("Unlocked", 3, 0);
      mode = "ONCE";
    }
    //Manual ON mode : ASCII:???
    if(cmd == "stayunlocked"){ 
      mode = "ON";
      digitalWrite(relayPin, HIGH);
      bleSerial.write("UNLOCKED!");
      showText("Standby", 3, 0);
    }
    // Manually Turn Off : ASCII: ????? 
    if(cmd == "LOCKED"){
      mode = "OFF";
      digitalWrite(relayPin, LOW);
      bleSerial.write("LOCKED");
      showText("LOCKED", 3, 10);
    }
    // Timer mode : ASCII:???????
    if(cmd == "stayunlock1HR"){
      digitalWrite(relayPin, HIGH);
      startTime = millis();
      mode = "1HR";
      bleSerial.write("Open for 1 hour!");
      showText("UNLOCKED:  1 hour", 2, 10);
    }
    // Timer mode 30 mins : ASCII:??????????? 
    if(cmd == "stayunlock30MINS"){
      digitalWrite(relayPin, HIGH);
      startTime = millis();
      mode = "30MINS";
      bleSerial.write("Open for 30 minutes!");
      showText("UNLOCKED: 30 mins", 2, 10);
    }

    // Timer mode 2 mins : ASCII:???????? 
    if(cmd == "stayunlock2MINS"){
      digitalWrite(relayPin, HIGH);
      startTime = millis();
      mode = "2MINS";
      bleSerial.write("Open for 2 minutes!");
      showText("UNLOCKED: 2 mins", 2, 10);
    }
  }

  durTime = markTime - startTime;
  
  if(durTime >= 3000 && mode == "ONCE"){
    digitalWrite(relayPin, LOW);
    mode = "OFF";
    showText("LOCKED", 3, 10);
  }
  if(durTime >= 3600000 && mode == "1HR"){
    digitalWrite(relayPin, LOW);
    mode = "OFF";
    showText("LOCKED", 3, 10);
  }
  if(durTime >= 120000 && mode == "2MINS"){
    digitalWrite(relayPin, LOW);
    mode = "OFF";
    showText("LOCKED", 3, 10);
  }
  if(durTime >= 1800000 && mode == "30MINS"){
    digitalWrite(relayPin, LOW);
    mode = "OFF";
    showText("LOCKED", 3, 10);
  }


  
}


void showText(String ct, int tSize, int X){
    display.clearDisplay();
    display.setTextSize(tSize);
    display.setTextColor(WHITE);
    display.setCursor(X, 20);
    display.println(ct);
    display.display();
//    delay(2000);
}


// show logo
void drawStartUp() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 12);
  display.println("Toky");
  display.setCursor(0, 28);
  display.println("Watch");
  display.setTextSize(1);
  display.setCursor(0, 45);
  display.setTextColor(WHITE);
  display.println("Smart Lock Trigger");
  display.display();
}
