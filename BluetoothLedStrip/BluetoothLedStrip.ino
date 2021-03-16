#include <SoftwareSerial.h>// import the serial library
#include <FastLED.h>

#define NUM_LEDS 20
#define DATA_PIN 3
#define BRIGHTNESS 255

CRGB leds[NUM_LEDS];

 
SoftwareSerial BT(8,9); // RX, TX
int ledpin=13; // led on D13 will show blink on / off
String BluetoothData; // the data given from Computer

char incomingData[12];
int incomingDataSize;
const char dataDelimiter = ',';

void fadeall() { for(int i = 0; i < NUM_LEDS; i++) { leds[i].nscale8(250); } }


void setup() 
{
  Serial.begin(19200);
  // put your setup code here, to run once:
  BT.begin(9600);
  BT.println("Bluetooth On please press 1 or 0 blink LED ..");

  FastLED.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void setLeds(String dataIn){
  Serial.println(dataIn);
  
  //Code adapted from: https://stackoverflow.com/questions/9072320/split-string-into-string-array
  int valuesFound = 0;
  int r = 0;
  int values[3];
  for (int i = 0; i < dataIn.length(); i++){
    if(dataIn.charAt(i) == ','){
      values[valuesFound] = dataIn.substring(r,i).toInt();
      r = i + 1;
      valuesFound++;
    }
  }

  for(int i = 0; i < 3; i++){
    Serial.println(values[i]);
  }

  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB((map(values[0], 0, 255, 0, BRIGHTNESS)),(map(values[1], 0, 255, 0, BRIGHTNESS)),(map(values[2], 0, 255, 0, BRIGHTNESS)));
  }

  FastLED.show();
  fadeall();
  
}

void changeLeds(char dataIn[]){
  int counter = 0;
  char colorValuesChar[3][255];
  int colorValuesInt[3];
  char * pch;
  pch = strtok(dataIn,",");
  while(pch != NULL){
    strncpy(colorValuesChar[counter], pch, sizeof(colorValuesChar[counter]));
    pch = strtok(NULL,",");
    counter++;
  }

  for(int i = 0; i<3; i++){
    colorValuesInt[i] = atoi(colorValuesChar[i]);
  }

  for(int i = 0; i < NUM_LEDS; i++){
    leds[i] = CRGB((map(colorValuesInt[0], 0, 255, 0, BRIGHTNESS)),(map(colorValuesInt[1], 0, 255, 0, BRIGHTNESS)),(map(colorValuesInt[2], 0, 255, 0, BRIGHTNESS)));
  }
  FastLED.show();
  fadeall();
}

void loop() 
{
  if (BT.available())
  {
    char incomingChar = BT.read();

    // Check if this is the start of the incoming data.
    if(incomingChar == '<'){
      memset(incomingData, 0, sizeof(incomingData));
      incomingDataSize = 0;
    }
    // Check if it is the end of the data, if so, send the command to alter the LEDs.
    else if(incomingChar == '>'){
      changeLeds(incomingData);
    }
    // If neither of the conditions fit, then append the incoming data to the data string.
    else{
      incomingData[incomingDataSize] = incomingChar;
      incomingDataSize++;
    }
  }
delay(10);
}
