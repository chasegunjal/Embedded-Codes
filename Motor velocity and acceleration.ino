// USING ARDUINO

#define PWMA 4
//#define PWMB 9
#define DirA 5
//#define DirB 8
const int pulsePinA = 2;
const int pulsePinB = 3;
int count = 0;
long prev_millis = 0;
long curr_millis = 0;
int interval = 1000;
int ppr = 470;
float RPM;

void setup() {
  pinMode(PWMA,OUTPUT);
  pinMode(DirA,OUTPUT);
  //pinMode(DirB,OUTPUT);
  //pinMode(PWMB,OUTPUT);
  pinMode(pulsePinA,INPUT_PULLUP);
  pinMode(pulsePinB,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(pulsePinA),counter,RISING); //ataching interrupt at pin 2
  Serial.begin(9600);
  prev_millis = millis(); //setting timer before the loop.

}

void loop() {
  //forward();
  //backward();
  float velocity;
  curr_millis = millis(); //setting timer during loop.
  
  if((curr_millis - prev_millis)>interval){   // Calculating RPM and velocity every second.
    detachInterrupt(digitalPinToInterrupt(pulsePinA)); // we are detaching the interrupt because, use of interrupt during calculation may cause errors in calculations. As priority of inerrupt is highest,when interrupt gets triggered calculations gets interfered with new values. 
    RPM = (count/ppr)*60;
    velocity = (RPM*2*3.14)/60;
    Serial.println("RPM: ");
    Serial.println(RPM);
    Serial.println("Velocity: ");
    Serial.print( velocity);
    delay(1000);
    count =0;
    prev_millis = curr_millis;   
    attachInterrupt(digitalPinToInterrupt(pulsePinA),counter,RISING);
  }
}
//Cytron MD30C code.

void forward(){
  // pwm and dir high -------- OutB=HIGH OutA=Low 
  digitalWrite(DirA,HIGH);
  analogWrite(PWMA,255);
  //digitalWrite(DirB,HIGH);
  //analogWrite(PWMB,HIGH);

}

void backward(){
  // pwm high and dir low -------- OutB=low OutA=high
  digitalWrite(DirA,LOW);
  analogWrite(PWMA,255);
  //digitalWrite(DirB,LOW);
  //analogWrite(PWMB,HIGH);
}

void counter(){
  if(digitalRead(pulsePinB)==LOW){
      count++;
    }
    else{
      count--;
    }
}
