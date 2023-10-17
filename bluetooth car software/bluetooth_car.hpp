// building a bluetooth car 

#include<Arduino.h>

// define the first bts7960 motor driver 
#define R_EN_FIRST 2 //right enable pin connect on pin number 2 
#define L_EN_FIRST 3  //left enable pin connect on pin number 3
#define R_PWM_FIRST 4  //right pwm signal connect on pin number 4 
#define L_PWM_FIRST 5  //left pwm signal connect on pin number 5 

// define the second  bts7960 motor driver 
#define R_EN 6  //right enable pin connect on pin number 6 
#define L_EN 7  //left enable pin connect on pin number 7 
#define R_PWM 8  //right pwm signal  connect to pin number 8 
#define L_PWM 9 //left pwm signal connect to pin number 9 

// define hc-06 ultrasonic sensor 
const int echo_pin = 11;
const int trig_pin = 10 ;

// DEFINE THE BUZZER 
const int buzzer = 12;

void setup(){
    Serial.begin(9600);

    pinMode(R_EN , OUTPUT);
    pinMode(L_EN , OUTPUT);
    pinMode(L_PWM , OUTPUT);
    pinMode(R_PWM , OUTPUT);

    pinMode(R_EN_FIRST , OUTPUT);
    pinMode(L_EN_FIRST , OUTPUT);
    pinMode(R_PWM_FIRST , OUTPUT);
    pinMode(L_PWM_FIRST , OUTPUT);

    pinMode(echo_pin , INPUT);
    pinMode(trig_pin , OUTPUT);

    pinMode(buzzer , OUTPUT);


    // ENABLE THE BOTH LEFT AND RIGHT MOTOR PIN 
    digitalWrite(R_EN , HIGH);
    digitalWrite(L_EN , HIGH);
    digitalWrite(R_EN_FIRST , HIGH);
    digitalWrite(L_EN_FIRST , HIGH);

    // command print on serial monitor
    Serial.println("welcome to Pie.space");
    Serial.println("There are some instruction to control the car ");
    Serial.println("Forward press 'f'");
    Serial.println("Backward press 'b'");
    Serial.println("Right press 'r' ");
    Serial.println("left press 'l");
    Serial.println("stop the car press 's'");
    delay(10000); //delay for 10 second 
}
void loop(){

        if(Serial.available()){
        char command = Serial.read();

        if(command == 'f'){
            digitalWrite(R_PWM , LOW);
            digitalWrite(L_PWM , HIGH);
            digitalWrite(L_PWM_FIRST , LOW); 
            digitalWrite(R_PWM_FIRST , HIGH); 
            Serial.println("Forward");
        
        }
        else if(command == 'b'){
            digitalWrite(L_PWM , LOW);
            digitalWrite(R_PWM , HIGH);
            digitalWrite(R_PWM_FIRST , LOW);
            digitalWrite(L_PWM_FIRST , HIGH);
            Serial.println("Backward");
        }
        else if(command == 'r'){
            digitalWrite(L_PWM , HIGH);
            digitalWrite(R_PWM , LOW);
            digitalWrite(L_PWM_FIRST , HIGH);
            digitalWrite(R_PWM_FIRST, LOW);
        }
        else if(command == 'l'){
            digitalWrite(L_PWM , LOW);
            digitalWrite(R_PWM , HIGH);
            digitalWrite(L_PWM_FIRST , LOW);
            digitalWrite(R_PWM_FIRST, HIGH);

        }
        else if(command == 's'){
            digitalWrite(L_PWM , LOW);
            digitalWrite(R_PWM , LOW);
            digitalWrite(R_PWM_FIRST , LOW);
            digitalWrite(L_PWM_FIRST , LOW);
            Serial.println("Stop");

        }
    }

    digitalWrite(trig_pin , LOW);
    delayMicroseconds(2);
    digitalWrite(trig_pin , HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin , LOW);

    // turn on the echo pin 
    float duration = pulseIn(echo_pin , HIGH);

    // calculate the distance
    float distance = duration/58.2;

    if(distance <= 15){
            digitalWrite(L_PWM , LOW);
            digitalWrite(R_PWM , LOW);
            digitalWrite(R_PWM_FIRST , LOW);
            digitalWrite(L_PWM_FIRST , LOW);
            digitalWrite(buzzer , HIGH);
            Serial.println("ultrasonic stop");
    }
    else{
        digitalWrite(buzzer , LOW);
    }

    Serial.print("Distance:");
    Serial.print(distance);
    Serial.println("CM");





}