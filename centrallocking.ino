//This script is written by Chris-The-Tuner (Christian Schmela)
//Web: http://chris-the-tuner.tk/
//Mail: christhetuner1993@googlemail.com
//The script is under the GNU GENERAL PUBLIC LICENSE V3
//Have fun using it ;)


//Settings
int lightpin = 5; //pin for light (warning lights)
int hornpin = 6; //pin for the horn
int hornlength = 250; //time for horn to be on (500 = 1/2 second)
int motordelay = 500; //can be adjusted to match your motors (time needed to upen/close the doors)

//do only touch if your arduino does not match the arduino nano !!!
int rfinputpin = 2; //input pin for FR Reciver (goes LOW(GND) for activation [PULL-UP Resistor needed !(used a 2.2kOhm resistor for 5V supply)])
int relais1pin = 3; //relais 1 pin used for switching polarity to motors
int relais2pin = 4; //relais 2 pin used for switching +12V to motors


//NEVER TOUCH CODE BELOW
int val = 0;
int locked = 0; //when installing and powering up doors should be 0 (unlocked)

void setup() //setting up the pins
{
 pinMode(rfinputpin, INPUT);
 pinMode(relais1pin, OUTPUT);
 pinMode(relais2pin, OUTPUT);
 pinMode(lightpin, OUTPUT);
 pinMode(hornpin, OUTPUT);
}

void loop() //loop and wait for a signal
{
 val = digitalRead(2); //read if RF signal is comming in

 if (val == LOW) //react if pin is LOW (RF signal incomming)
 {
  if (locked == 0) //if doors are locked react like this
  {
   digitalWrite(relais1pin, LOW); //polarity is now set to "closing" (mainly the relay should now be off to save battery power)
   digitalWrite(lightpin, HIGH); //from now on lights are blinking (visual making of closing sequence)
   digitalWrite(relais2pin, HIGH); //door motors should close now
   delay(motordelay);
   digitalWrite(relais2pin, LOW); //doors should be closed by now (if not adjust "closingdelay" !)
   digitalWrite(hornpin, HIGH); //horn goes off for the set time
   delay(hornlength);
   digitalWrite(hornpin, LOW); //horn goes off
   digitalWrite(lightpin, LOW); //lights should be turned off now
   locked = 1; //setting value to locked doors
   delay(5000); //sleeping for 5 seconds (don't un-lock the doors again by accident)
  }


  if (locked == 1) //if doors are unlocked react like this
  {
   digitalWrite(relais1pin, HIGH); //polarity is now set to "opening"
   digitalWrite(lightpin, HIGH); //from now on lights are blinking (visual making of closing sequence)
   digitalWrite(relais2pin, HIGH); //door motors should open now
   delay(motordelay);
   digitalWrite(relais2pin, LOW); //doors should be open by now (if not adjust "motordelay" !)
   digitalWrite(hornpin, HIGH); //horn turns on for the set time
   delay(hornlength);
   digitalWrite(hornpin, LOW); //horn turns off
   digitalWrite(lightpin, LOW); //lights should be turned off now
   digitalWrite(relais1pin, LOW); //turning off the relay (state: closing) to save battery power)
   locked = 0; //setting value to un-locked doors
   delay(5000); //sleeping for 5 seconds (don't lock the doory by accident)
  }
 }
}
