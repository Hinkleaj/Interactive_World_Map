// ---------------------------------------------------------------------------
// Full Circuit Code for Worldmap
// ---------------------------------------------------------------------------

#include <NewPing.h>

#define SONAR_NUM 7       // Number of sensors
#define PingMin 2         // Min distance to ping sensor (in cm)
#define PingMax 10        // Max distance to ping sensor (in cm)
#define MAX_DISTANCE 200  // Maximum distance to ping (in cm)
#define MFPOW 11          // MOSFET for main power
#define MFLED1 2          // MOSFET for LED1 
#define MFLED2 3          // MOSFET for LED2
#define MFLED3 4          // MOSFET for LED3
#define MFLED4 5          // MOSFET for LED4
#define MFLED5 6          // MOSFET for LED5
#define MFLED6 7          // MOSFET for LED6
#define SPOW 12           // Sensor for main power
#define SLED1 8           // Sensor for LED1
#define SLED2 9           // Sensor for LED2
#define SLED3 10          // Sensor for LED3
#define SLED4 A3          // Sensor for LED4
#define SLED5 A2          // Sensor for LED5
#define SLED6 A1          // Sensor for LED6

// Boolean flags for making sensors act like switches
// State1
bool stateSPOW = LOW;
bool state_LED_1 = LOW;
bool state_LED_2 = LOW;
bool state_LED_3 = LOW;
bool state_LED_4 = LOW;
bool state_LED_5 = LOW;
bool state_LED_6 = LOW;

// Values
bool valueSPOW = LOW;
bool value_LED_1 = LOW;
bool value_LED_2 = LOW;
bool value_LED_3 = LOW;
bool value_LED_4 = LOW;
bool value_LED_5 = LOW;
bool value_LED_6 = LOW;

// Old values
bool old_valueSPOW = LOW;
bool old_value_LED_1 = LOW;
bool old_value_LED_2 = LOW;
bool old_value_LED_3 = LOW;
bool old_value_LED_4 = LOW;
bool old_value_LED_5 = LOW;
bool old_value_LED_6 = LOW;

int pingDistance[7];

// Sensor object array
NewPing sonar[SONAR_NUM] =              
{
  NewPing(SPOW, SPOW, MAX_DISTANCE),    // Main power sensor
  NewPing(SLED1, SLED1, MAX_DISTANCE),  // Sensor for LED1
  NewPing(SLED2, SLED2, MAX_DISTANCE),  // Sensor for LED2
  NewPing(SLED3, SLED3, MAX_DISTANCE),  // Sensor for LED3
  NewPing(SLED4, SLED4, MAX_DISTANCE),  // Sensor for LED4
  NewPing(SLED5, SLED5, MAX_DISTANCE),  // Sensor for LED5
  NewPing(SLED6, SLED6, MAX_DISTANCE)   // Sensor for LED6
};

void setup() 
{
  Serial.begin(115200);     // Open serial monitor at 115200 baud to see ping results.
  
  //Ultrasonics
  pinMode(SPOW, OUTPUT);    // Sensor for main power
  pinMode(SLED1, OUTPUT);   // Sensor for LED1
  pinMode(SLED2, OUTPUT);   // Sensor for LED2
  pinMode(SLED3, OUTPUT);   // Sensor for LED3
  pinMode(SLED4, OUTPUT);   // Sensor for LED4
  pinMode(SLED5, OUTPUT);   // Sensor for LED5
  pinMode(SLED6, OUTPUT);   // Sensor for LED6

  //Mosfets
  pinMode(MFPOW, OUTPUT);   //MOSFET for main power
  pinMode(MFLED1, OUTPUT);  //MOSFET for LED1
  pinMode(MFLED2, OUTPUT);  //MOSFET for LED2
  pinMode(MFLED3, OUTPUT);  //MOSFET for LED3
  pinMode(MFLED4, OUTPUT);  //MOSFET for LED4
  pinMode(MFLED5, OUTPUT);  //MOSFET for LED5
  pinMode(MFLED6, OUTPUT);  //MOSFET for LED6
}

void loop() 
{ 
  delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.

  // If sonar pings between 2 and 10 cm, then change the value of the boolean flag
  pingDistance[0] = sonar[0].ping_cm();
  if (pingDistance[0] > PingMin && pingDistance[0] < PingMax)   // Sensor for main power
  {
    valueSPOW = true;
  }else{
    valueSPOW = false;
  }
  pingDistance[1] = sonar[1].ping_cm();
  if (pingDistance[1] > PingMin && pingDistance[1] < PingMax)   // Sensor for LED1
  {
    value_LED_1 = true;
  }else{
    value_LED_1 = false;
  }
  pingDistance[2] = sonar[2].ping_cm();
  if (pingDistance[2] > PingMin && pingDistance[2] < PingMax)   // Sensor for LED2
  {
    value_LED_2 = true;
  }else{
    value_LED_2 = false;
  }
  pingDistance[3] = sonar[3].ping_cm();
  if (pingDistance[3] > PingMin && pingDistance[3] < PingMax)   // Sensor for LED3
  {
    value_LED_3 = true;
  }else{
    value_LED_3 = false;
  }
  pingDistance[4] = sonar[4].ping_cm();
  if (pingDistance[4] > PingMin && pingDistance[4] < PingMax)   // Sensor for LED4
  {
    value_LED_4 = true;
  }else{
    value_LED_4 = false;
  }
  pingDistance[5] = sonar[5].ping_cm();
  if (pingDistance[5] > PingMin && pingDistance[5] < PingMax)   // Sensor for LED5
  {
    value_LED_5 = true;
  }else{
    value_LED_5 = false;
  }
  pingDistance[6] = sonar[6].ping_cm();
  if (pingDistance[6] > PingMin && pingDistance[6] < PingMax)   // Sensor for LED6
  {
    value_LED_6 = true;
  }else{
    value_LED_6 = false;
  }
  if (valueSPOW == HIGH && old_valueSPOW == LOW)
  {
    // If stateSPOW changes from LOW to HIGH: ==> State2
    if (stateSPOW == false)
    {
      digitalWrite(MFPOW, HIGH);    // Energize the main power MOSFET
      digitalWrite(MFLED1, HIGH);   // turn on MOSFET for LED1
      digitalWrite(MFLED2, HIGH);   // turn on MOSFET for LED2
      digitalWrite(MFLED3, HIGH);   // turn on MOSFET for LED3
      digitalWrite(MFLED4, HIGH);   // turn on MOSFET for LED4
      digitalWrite(MFLED5, HIGH);   // turn on MOSFET for LED5
      digitalWrite(MFLED6, HIGH);   // turn the LED on (HIGH is the voltage level)
      state_LED_1 = true;
      state_LED_2 = true;
      state_LED_3 = true;
      state_LED_4 = true;
      state_LED_5 = true;
      state_LED_6 = true;
    }
    else if (stateSPOW == true)
    {      
      digitalWrite(MFPOW, LOW);     // Turn on the main power MOSFET
      digitalWrite(MFLED1, LOW);    // turn off MOSFET for LED1
      digitalWrite(MFLED2, LOW);    // turn off MOSFET for LED2
      digitalWrite(MFLED3, LOW);    // turn off MOSFET for LED3
      digitalWrite(MFLED4, LOW);    // turn off MOSFET for LED4
      digitalWrite(MFLED5, LOW);    // turn off MOSFET for LED5
      digitalWrite(MFLED6, LOW);    // turn off MOSFET for LED6
    }
    stateSPOW = 1 - stateSPOW;
  }
  old_valueSPOW = valueSPOW; // value is now old and store the old value
  
  // If the 
  if (stateSPOW == true && value_LED_1 == HIGH && old_value_LED_1 == LOW)
  {    
    if (state_LED_1 == false)
    {
      digitalWrite(MFLED1, HIGH);   // turn on MOSFET for LED1     
      //digitalWrite(MFLED2, LOW);    // turn off MOSFET for LED2
      //digitalWrite(MFLED3, LOW);    // turn off MOSFET for LED3
      //digitalWrite(MFLED4, LOW);    // turn off MOSFET for LED4
      //digitalWrite(MFLED5, LOW);    // turn off MOSFET for LED5
      //digitalWrite(MFLED6, LOW);    // turn off MOSFET for LED6
      
    }
    else if (state_LED_1 == true)
    {
      digitalWrite(MFLED1, LOW);   // turn the LED on (HIGH is the voltage level)
    }
    state_LED_1 = 1 - state_LED_1;
  }
  old_value_LED_1 = value_LED_1; // value is now old and store the old value





  if (stateSPOW == true && value_LED_2 == HIGH && old_value_LED_2 == LOW)
  {    
    if (state_LED_2 == false)
    {
      //digitalWrite(MFLED1, LOW);    // turn off MOSFET for LED1
      digitalWrite(MFLED2,  HIGH);   // turn on MOSFET for LED2
      //digitalWrite(MFLED3, LOW);    // turn off MOSFET for LED3
      //digitalWrite(MFLED4, LOW);    // turn off MOSFET for LED4
      //digitalWrite(MFLED5, LOW);    // turn off MOSFET for LED5
      //digitalWrite(MFLED6, LOW);    // turn off MOSFET for LED6
      
    }
    else if (state_LED_2 == true)
    {
      digitalWrite(MFLED2, LOW);   // turn the LED on (HIGH is the voltage level)
    }
    state_LED_2 = 1 - state_LED_2;
  }
  old_value_LED_2 = value_LED_2; // value is now old and store the old value





  if (stateSPOW == true && value_LED_3 == HIGH && old_value_LED_3 == LOW)
  {    
    if (state_LED_3 == false)
    {
      //digitalWrite(MFLED1, LOW);    // turn off MOSFET for LED1
      //digitalWrite(MFLED2, LOW);    // turn off MOSFET for LED2
      digitalWrite(MFLED3,  HIGH);   // turn on MOSFET for LED3
      //digitalWrite(MFLED4, LOW);    // turn off MOSFET for LED4
      //digitalWrite(MFLED5, LOW);    // turn off MOSFET for LED5
      //digitalWrite(MFLED6, LOW);    // turn off MOSFET for LED6
    }
    else if (state_LED_3 == true)
    {
      digitalWrite(MFLED3, LOW);   // turn the LED on (HIGH is the voltage level)
    }
    state_LED_3 = 1 - state_LED_3;
  }
  old_value_LED_3 = value_LED_3; // value is now old and store the old value





  if (stateSPOW == true && value_LED_4 == HIGH && old_value_LED_4 == LOW)
  {    
    if (state_LED_4 == false)
    {
      //digitalWrite(MFLED1, LOW);    // turn off MOSFET for LED1
      //digitalWrite(MFLED2, LOW);    // turn off MOSFET for LED2
      //digitalWrite(MFLED3, LOW);    // turn off MOSFET for LED3
      digitalWrite(MFLED4,  HIGH);   // turn on MOSFET for LED4
      //digitalWrite(MFLED5, LOW);    // turn off MOSFET for LED5
      //digitalWrite(MFLED6, LOW);    // turn off MOSFET for LED6
      
    }
    else if (state_LED_4 == true)
    {
      digitalWrite(MFLED4, LOW);   // turn the LED on (HIGH is the voltage level)
    }
    state_LED_4 = 1 - state_LED_4;
  }
  old_value_LED_4 = value_LED_4; // value is now old and store the old value





  if (stateSPOW == true && value_LED_5 == HIGH && old_value_LED_5 == LOW)
  {    
    if (state_LED_5 == false)
    {
      //digitalWrite(MFLED1, LOW);    // turn off MOSFET for LED1
      //digitalWrite(MFLED2, LOW);    // turn off MOSFET for LED2
      //digitalWrite(MFLED3, LOW);    // turn off MOSFET for LED3
      //digitalWrite(MFLED4, LOW);    // turn off MOSFET for LED4
      digitalWrite(MFLED5,  HIGH);   // turn on MOSFET for LED5
      //digitalWrite(MFLED6, LOW);    // turn off MOSFET for LED6
      
    }
    else if (state_LED_5 == true)
    {
      digitalWrite(MFLED5, LOW);   // turn the LED on (HIGH is the voltage level)
    }
    state_LED_5 = 1 - state_LED_5;
  }
  old_value_LED_5 = value_LED_5; // value is now old and store the old value





  if (stateSPOW == true && value_LED_6 == HIGH && old_value_LED_6 == LOW)
  {    
    if (state_LED_6 == false)
    {
      //digitalWrite(MFLED1, LOW);    // turn off MOSFET for LED1
      //digitalWrite(MFLED2, LOW);    // turn off MOSFET for LED2
      //digitalWrite(MFLED3, LOW);    // turn off MOSFET for LED3
      //digitalWrite(MFLED4, LOW);    // turn off MOSFET for LED4
      //digitalWrite(MFLED5, LOW);    // turn off MOSFET for LED5
      digitalWrite(MFLED6,  HIGH);   // turn on MOSFET for LED6
      
    }
    else if (state_LED_6 == true)
    {
      digitalWrite(MFLED6, LOW);   // turn the LED on (HIGH is the voltage level)
    }
    state_LED_6 = 1 - state_LED_6;
  }
  old_value_LED_6 = value_LED_6; // value is now old and store the old value




  
}
