#include <Stepper.h>
#include <LiquidCrystal.h>

// digital Inputs - Outputs
const int m1 = 0;
const int m2 = 1;
const int m3 = 2;
const int m4 = 3;

const int freq_pot = A0;
const int depth_pot = A1;

const int stp_1 = 6;
const int stp_2 = 5;
const int stp_3 = 4;
const int stp_4 = 3;


const int stepsPerRevolution = 200;   // the steps of our motor
int freq = 12;                        // breath frequency [breath per minute]
int depth = 5;                        // breath depth set from [5 - 8] as integer
int cycle = stepsPerRevolution*depth; // steps per one breath

LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
Stepper myStepper(210, 6, 5, 4, 3);

void setup() {
      pinMode(m1, OUTPUT);
      pinMode(m2, OUTPUT);
      pinMode(m3, OUTPUT);
      pinMode(m4, OUTPUT);
      pinMode(0, OUTPUT);
      pinMode(7, OUTPUT);
      pinMode(6, OUTPUT);
      pinMode(4, OUTPUT);
      pinMode(5, OUTPUT);
      pinMode(2, OUTPUT);
      pinMode(stp_1, OUTPUT);
      pinMode(stp_2, OUTPUT);
      pinMode(stp_3, OUTPUT);
      pinMode(stp_4, OUTPUT);
      
      myStepper.setSpeed(30);
      Serial.begin(9600);
      lcd.begin(16, 2);
}


void loop() {

  cycle = stepsPerRevolution*depth;
  myStepper.setSpeed(2*freq*depth);

  freq = get_frequency();
  depth = get_depth();
  update_display(freq, depth);

  
  myStepper.step(cycle);
  freq = get_frequency();
  depth = get_depth();
  update_display(freq, depth);
  delay(500);

  myStepper.step(-cycle);
  freq = get_frequency();
  depth = get_depth();
  update_display(freq, depth);
  delay(500);
}

int get_frequency(){
  freq = analogRead(freq_pot);
  freq = map(freq, 0, 1024, 12, 20);
  return(freq);
}

int get_depth(){
  depth = analogRead(depth_pot);
  depth = map(depth, 0, 1024, 5, 10);
  return(depth);
}

void update_display(int freq, int depth){
  lcd.setCursor(0, 0);
  lcd.print("Freq.: "); lcd.print(freq); lcd.print(" b/min");

  lcd.setCursor(0, 1);
  lcd.print("Volume: "); lcd.print(depth*50); lcd.print(" ml");
  }
