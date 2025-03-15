#define PWMA 4
#define DirA 5

// MOTOR 1
int p_pin_1A = 2;
int p_pin_1B = 3;

// MOTOR 2
int p_pin_2A = 4;
int p_pin_2B = 5;

// MOTOR 3
int p_pin_3A = 6;
int p_pin_3B = 7;



//delay var for MOTOR 1
long int current_millis;
long int previous_millis;


// pulses for MOTOR 1,2 and 3
volatile long int pulse_1=0;
volatile long int pulse_2=0;
volatile long int pulse_3=0;

int ppr=749;


void setup() {
 pinMode(p_pin_1A,INPUT_PULLUP);
 pinMode(p_pin_1B,INPUT_PULLUP);
 pinMode(p_pin_2A,INPUT_PULLUP);
 pinMode(p_pin_2B,INPUT_PULLUP);
 pinMode(p_pin_3A,INPUT_PULLUP);
 pinMode(p_pin_3B,INPUT_PULLUP);

 attachInterrupt(digitalPinToInterrupt(p_pin_1A), ISR_1, RISING);
 attachInterrupt(digitalPinToInterrupt(p_pin_2A), ISR_2, RISING);
 attachInterrupt(digitalPinToInterrupt(p_pin_3A), ISR_3, RISING);

 Serial.begin(9600);

 previous_millis = millis();
}

void loop() {

  current_millis = millis();

  if((current_millis - previous_millis)>=1000){

    detachInterrupt(digitalPinToInterrupt(p_pin_1A)); 
    detachInterrupt(digitalPinToInterrupt(p_pin_2A)); 
    detachInterrupt(digitalPinToInterrupt(p_pin_3A)); 
    

    int count_1 = pulse_1/ppr;
    int RPM_1 = count_1*60;

    int count_2 = pulse_2/ppr;
    int RPM_2 = count_2*60;

    int count_3 = pulse_3/ppr;
    int RPM_3 = count_3*60;


    Serial.print("M1 RPM -- ");
    Serial.print(RPM_1);
    Serial.print("  M2 RPM -- ");
    Serial.print(RPM_2);
    Serial.print("  M3 RPM -- ");
    Serial.print(RPM_3);

    count_1,count_2,count_3 = 0;

    attachInterrupt(digitalPinToInterrupt(p_pin_1A), ISR_1, RISING);
    attachInterrupt(digitalPinToInterrupt(p_pin_2A), ISR_2, RISING);
    attachInterrupt(digitalPinToInterrupt(p_pin_3A), ISR_3, RISING);
  }
  

}

void ISR_1(){
  if(digitalRead(p_pin_1B)==LOW){
    pulse_1++;
  }
  else{
    pulse_1--;
  }
}

void ISR_2(){
  if(digitalRead(p_pin_2B)==LOW){
    pulse_2++;
  }
  else{
    pulse_2--;
  }
}

void ISR_3(){
  if(digitalRead(p_pin_3B)==LOW){
    pulse_3++;
  }
  else{
    pulse_3--;
  }
}