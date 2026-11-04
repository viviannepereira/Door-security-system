#include <Keypad.h>

#include <string.h>



const int sensor_pin = 13;

const int buzzer_pin = 12;

int safe = 1;

const int led_pin = 11;

unsigned long last_time = millis();

int toggle_led = 0;

int toggle_alarm = 0;

String password = "";

String my_password = "1234";



const byte ROWS = 4;  //four rows

const byte COLS = 4;  //four columns

//define the cymbols on the buttons of the keypads

char hexaKeys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }

};

byte rowPins[ROWS] = { 5, 4, 3, 2 };  //connect to the row pinouts of the keypad

byte colPins[COLS] = { 9, 8, 7, 6 };  //connect to the column pinouts of the keypad



//initialize an instance of class NewKeypad

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);



void setup() {

  pinMode(sensor_pin, INPUT_PULLUP);

  pinMode(buzzer_pin, INPUT);

  pinMode(led_pin, OUTPUT);

  Serial.begin(9600);
}



void alarm() {

  tone(buzzer_pin, 1000);

  if (millis() - last_time >= 300) {

    toggle_led = !toggle_led;

    digitalWrite(led_pin, toggle_led);
    last_time = millis();
  }
}



void no_alarm() {

  noTone(buzzer_pin);

  digitalWrite(led_pin, 0);
}



void loop() {

  safe = digitalRead(sensor_pin);



  if (!safe) {

    toggle_alarm = 1;
  }

  if (toggle_alarm) {

    alarm();
    
    char customKey = customKeypad.getKey();

    if (customKey) {

      password += customKey;

    if (password.length() == 4) {

      if (password == my_password) {

        toggle_alarm = 0;

        no_alarm();
      }

      password = "";

    }
    }
  }
}