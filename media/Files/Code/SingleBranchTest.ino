// ---------------------------------------------------------------------------
// Example NewPing library sketch that pings 3 sensors 20 times a second.
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define SONAR_NUM 2      // Number of sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.
#define LED_1 13
#define MAIN_SWITCH 8

bool stateSPOW = LOW;
bool state_LED_1 = LOW;
bool state_LED_2 = LOW;

bool valueSPOW = LOW;
bool value_LED_1 = LOW;
bool value_LED_2 = LOW;

bool old_valueSPOW = LOW;
bool old_value_LED_1 = LOW;
bool old_value_LED_2 = LOW;


NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(4, 4, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(6, 6, MAX_DISTANCE), 
  //NewPing(8, 9, MAX_DISTANCE)
};

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
  //Ultrasonics
  pinMode(4, OUTPUT);
  pinMode(6, OUTPUT);

  //Mosfets
  pinMode(LED_1, OUTPUT); 
  pinMode(MAIN_SWITCH, OUTPUT); 
}

void loop() { 

  //Flags for SPOW
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  if ( sonar[1].ping_cm() > 3 && sonar[1].ping_cm() < 10)
  {
      value_LED_1 = true;
  }else{
      value_LED_1 = false;
  }
  
  if ( sonar[0].ping_cm() > 3 && sonar[0].ping_cm() < 10)
  {
      valueSPOW = true;
  }else{
      valueSPOW = false;
  }

  if( valueSPOW == LOW && old_valueSPOW == HIGH){  
    
      if( stateSPOW == true){
          Serial.println("STATE 2!!!");
          digitalWrite(LED_1, HIGH);   // turn the LED on (HIGH is the voltage level)
          digitalWrite(MAIN_SWITCH, HIGH);   // turn the LED on (HIGH is the voltage level)
      }
      else if( stateSPOW == false){
           Serial.println("STATE 1!!!");
           digitalWrite(LED_1, LOW);   // turn the LED on (HIGH is the voltage level)
          digitalWrite(MAIN_SWITCH, LOW);   // turn the LED on (HIGH is the voltage level)
          
      }
      stateSPOW = 1 - stateSPOW;
      Serial.println("MAIN SWITCH SWIPE!!!");

  }
  old_valueSPOW = valueSPOW; // value is now old and store the old value

  if( value_LED_1 == LOW && old_value_LED_1 == HIGH){  
  
    if( state_LED_1 == true){
          Serial.println("STATE 3!!!");
          digitalWrite(LED_1, HIGH);   // turn the LED on (HIGH is the voltage level)
          
      }
    else if( state_LED_1 == false){
          Serial.println("STATE 2!!!");
          digitalWrite(LED_1, LOW);   // turn the LED on (HIGH is the voltage level)
          
     }
      
    state_LED_1 = 1 - state_LED_1; 
    Serial.println("SWITCH 1 SWIPE!!!");

  }
  old_value_LED_1 = value_LED_1; // value is now old and store the old value






}
