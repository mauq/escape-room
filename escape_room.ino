//include libraries
#include <Button.h>
#include <Servo.h>

///////////////variables///////////////

//button to turn on all the lights
Button lightButt(7, INPUT_PULLUP);
boolean light = false;

//button to open the exit door once the hall effect sensor unlocks it
Button doorButt(8, INPUT_PULLUP);

//servo to open door with magnet lock
Servo magServo;

//when on, indicates all the lights in the room are on
int allOnLed = 13;

//turns on when magnet is close enough to the hall effect sensor
int unlock = 12;

int off = 3;
int on = 2;

//pin for the hall effect sensor
int lock = 11;

void setup() {
  //initialize all the pins to be used
  //leds output
  pinMode(allOnLed, OUTPUT);
  pinMode(unlock, OUTPUT);

  pinMode(off, OUTPUT);
  pinMode(on, OUTPUT);
  digitalWrite(off, HIGH);

  //hall effect sends input
  pinMode(lock, INPUT);

  //attach servo to pin
  magServo.attach(4);
  magServo.write(0);

  //begin serial
  Serial.begin(9600);
}

void loop() {

  //print the state of the magnet lock to serial
  Serial.println(digitalRead(lock));

  //if button is pressed and magnet is by sensor, turn LED on (open door)
  //if button is pressed and magnet is not by sensor, do nothing
  //if button is not pressed, turn LED off (close door)
  if(doorButt.checkButtonAction() == Button::CLICKED) {
    if(digitalRead(lock) == 0) {
      digitalWrite(unlock, HIGH);
      magServo.write(180);
    }

    // test else statement
    else {
      magServo.write(0);
    }
  } else {
    digitalWrite(unlock, LOW);
//    magServo.write(0);
  }

  //if magnet is close enough turn green light on 
  //else have red light on indicating locked
  if(digitalRead(lock) == 0) {
    digitalWrite(on, HIGH);
    digitalWrite(off, LOW);
  } else {
    digitalWrite(on, LOW);
    digitalWrite(off, HIGH);
  }

  //---------------------------------------------------//

  //if button is pressed and lights are off, turn lights on
  //if button is pressed and lights are on, turn lights off
  if(lightButt.checkButtonAction() == Button::CLICKED) {
    light = !light;
  }
  if(light) {
    digitalWrite(allOnLed, HIGH);
  } else {
    digitalWrite(allOnLed, LOW);
  }

  //----------------------------------------------------//
}
