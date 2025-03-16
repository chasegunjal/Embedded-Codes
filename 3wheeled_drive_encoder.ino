#define PWM1 15
#define Dir1 16
#define PWM2 17
#define Dir2 18
#define PWM3 19
#define Dir3 20

// MOTOR 1
volatile int p_pin_1A = 2;
volatile int p_pin_1B = 3;

// MOTOR 2
volatile int p_pin_2A = 4;
volatile int p_pin_2B = 5;

// MOTOR 3
volatile int p_pin_3A = 6;
volatile int p_pin_3B = 7;


//initialize hardware timer pointer
hw_timer_t *timer= NULL;


// pulses for MOTOR 1,2 and 3
volatile long int pulse_1=0;
volatile long int pulse_2=0;
volatile long int pulse_3=0;

volatile int RPM_1=0;
volatile int RPM_2=0;
volatile int RPM_3=0;

volatile int count_1=0;
volatile int count_2=0;
volatile int count_3=0;

int ppr=749;


void setup() {
 pinMode(PWM1,OUTPUT);
 pinMode(PWM2,OUTPUT);
 pinMode(PWM3,OUTPUT);
 pinMode(Dir1,OUTPUT);
 pinMode(Dir2,OUTPUT);
 pinMode(Dir3,OUTPUT);
 
 pinMode(p_pin_1A,INPUT_PULLUP);
 pinMode(p_pin_1B,INPUT_PULLUP);
 pinMode(p_pin_2A,INPUT_PULLUP);
 pinMode(p_pin_2B,INPUT_PULLUP);
 pinMode(p_pin_3A,INPUT_PULLUP);
 pinMode(p_pin_3B,INPUT_PULLUP);

 attachInterrupt(digitalPinToInterrupt(p_pin_1A), ISR_1, RISING);
 attachInterrupt(digitalPinToInterrupt(p_pin_2A), ISR_2, RISING);
 attachInterrupt(digitalPinToInterrupt(p_pin_3A), ISR_3, RISING);
 
 //it initializes esp32's hardware timer
 timer = timerBegin(0,80, TRUE);  //timerBegin(timer_number, prescaler, countup) esp32 has inbuilt 3 hardware timers so we have to choose one of them. prescaler divides the 80Mhz clock to set timer resolution. if true counting increases, otherwise.
 
 //it attaches an ISR to timer
 timerAttachInterrupt(timer, &calc, TRUE);// timerAttachInterrupt(timer pointer, function, edge) // A pointer to the hardware timer created using timerBegin(). The function to execute when the timer interrupt triggers. true → The ISR triggers on the rising edge of the timer event, false → The ISR triggers on the falling edge of the timer event.
 
 //This function sets the time interval after which the timer triggers an interrupt.
 timerAlarmWrite(timer, 1000000, TRUE); //timerAlarmWrite(timer pointer, value, autoreload).  .count till "value". true → timer restart, false→The timer triggers only once unless restarted manually.

 
 //This function starts the timer, allowing it to count and trigger interrupts
 timerAlarmEnable(timer);
 
 Serial.begin(9600);

 
}

void loop() {
    Serial.print("M1 RPM -- ");
    Serial.print(RPM_1);
    Serial.print("  M2 RPM -- ");
    Serial.print(RPM_2);
    Serial.print("  M3 RPM -- ");
    Serial.print(RPM_3);

}

void IRAM_ATTR ISR_1(){
  if(digitalRead(p_pin_1B)==LOW){
    pulse_1++;
  }
  else{
    pulse_1--;
  }
}

void IRAM_ATTR ISR_2(){
  if(digitalRead(p_pin_2B)==LOW){
    pulse_2++;
  }
  else{
    pulse_2--;
  }
}

void IRAM_ATTR ISR_3(){
  if(digitalRead(p_pin_3B)==LOW){
    pulse_3++;
  }
  else{
    pulse_3--;
  }
}

void IRAM_ATTR calc(){
 count_1 = pulse_1/ppr;
 count_2 = pulse_2/ppr;
 count_3 = pulse_3/ppr;

 RPM_1 = count_1*60;
 RPM_2 = count_2*60;
 RPM_3 = count_3*60;
}


void Drive_forward(){
 digitalWrite(Dir1,HIGH);
 analogWrite(PWM1,255);
 digitalWrite(Dir2,LOW);
 analogWrite(PWM2,255);
}

void Drive_backward(){
 digitalWrite(Dir1,LOW);
 analogWrite(PWM1,255);
 digitalWrite(Dir2,HIGH);
 analogWrite(PWM2,255);
}

void clockwise(){
 digitalWrite(Dir1,LOW);
 analogWrite(PWM1,255);
 digitalWrite(Dir2,LOW);
 analogWrite(PWM2,255);
 digitalWrite(Dir3,LOW);
 analogWrite(PWM3,255);
 }
