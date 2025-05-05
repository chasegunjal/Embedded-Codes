#define led1 12
#define led2 14
void Task1 (void * pvParameters);
void Task2 (void*pvParameters);


void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  Serial.begin(115200);
  xTaskCreate(
    Task1,
    "Task1",
    1000,
    NULL,
    1,
    NULL
  )
  xTaskCreate(
    Task2,
    "Task2",
    1000,
    NULL,
    1,
    NULL
  )
}

void loop() {
  

}

void Task1 (void*pvParameters){
  while(1){
    digitalWrite(led1, HIGH);
    Serial.Print("Task1 is running.........");
    vTaskDelay(500/portTICK_PERIOD_MS);
  }
}

void Task2 (void*pvParameters){
  while(1){
    digitalWrite(led2, HIGH);
    Serial.Print("Task1 is running.........");
    vTaskDelay(1000/portTICK_PERIOD_MS);
  }
}