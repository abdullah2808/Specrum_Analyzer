

#include <RGBmatrixPanel.h>



#define CLK  12   // USE THIS ON ARDUINO UNO, ADAFRUIT METRO M0, etc.
//#define CLK A4 // USE THIS ON METRO M4 (not M0)
//#define CLK 11 // USE THIS ON ARDUINO MEGA
#define OE   13
#define LAT 10
#define A   A2
#define B   A3
#define C   A4
#define D   A5
#define STROBE 4
#define RESET 5
#define DC_One A0
#define DC_Two A1 


RGBmatrixPanel matrix(A, B, C, D, CLK, LAT, OE, false);
  int freq_amp;
  int Frequencies_One[7];
  int Frequencies_Two[7]; 
  int i;
void setup() {


  
  pinMode(STROBE, OUTPUT);
  pinMode(RESET, OUTPUT);
  pinMode(DC_One, INPUT);
  pinMode(DC_Two, INPUT);  
  digitalWrite(STROBE, HIGH);
  digitalWrite(RESET, HIGH);

  //Initialize Spectrum Analyzers
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, HIGH);
  delay(1);
  digitalWrite(STROBE, HIGH);
  delay(1);
  digitalWrite(STROBE, LOW);
  delay(1);
  digitalWrite(RESET, LOW);


 
   Serial.begin(9600); 
  
  matrix.begin();


  // draw some text!
  matrix.setCursor(0, 0);    // start at top left, with one pixel of spacing
  matrix.setTextSize(1);     // size 1 == 8 pixels high
  matrix.setTextWrap(false); // Don't wrap at end of line - will do ourselves





  // whew!
}

  void Read_Frequencies()
{
  //Read frequencies for each band
  for (freq_amp = 0; freq_amp<7; freq_amp++)
  {
    Frequencies_One[freq_amp] = analogRead(DC_One);
    Frequencies_Two[freq_amp] = analogRead(DC_Two); 
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);
   Serial.println(freq_amp);
   Serial.println(Frequencies_One[freq_amp]);
   Serial.println(Frequencies_Two[freq_amp]);
  }
}

  int Return_Frequencies()
{
    digitalWrite(STROBE, HIGH);
    digitalWrite(STROBE, LOW);

  return analogRead(DC_One); 
}



void loop() {

  Read_Frequencies();
  matrix.fillScreen(matrix.Color333(0, 0, 0));
  matrix.fillRect(0, 31, 6, ((-Frequencies_One[0] / 18)+6), matrix.Color333(7, 0, 0));
  matrix.fillRect(6, 31, 4, ((-Frequencies_One[1] / 18)+6), matrix.Color333(5, 2, 0));
  matrix.fillRect(10, 31, 4, ((-Frequencies_One[2]  / 18)+9), matrix.Color333(2, 5, 0));
  matrix.fillRect(14, 31, 4, ((-Frequencies_One[3] / 18)+6), matrix.Color333(0, 7, 0));
  matrix.fillRect(18, 31, 4, ((-Frequencies_One[4] / 18)+6), matrix.Color333(0, 5, 2));
  matrix.fillRect(22, 31, 4, ((-Frequencies_One[5] / 18)+6), matrix.Color333(0, 2, 5));
  matrix.fillRect(26, 31, 6, ((-Frequencies_One[6] / 18)+6), matrix.Color333(0, 0, 7));
//  matrix.fillRect(28, 31, 4, (-Return_Frequencies() / 16), matrix.Color333(3, 0, 3));
  delay(10);




}
