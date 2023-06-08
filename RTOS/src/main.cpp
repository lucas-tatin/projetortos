#include <Arduino.h>
#include <Arduino_FreeRTOS.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12,11,10,9,8,7);
#define LED_PIN_1 5
#define LED_PIN_2 4

void TaskBlink1(void *pvParameters);
void TaskBlink2(void *pvParameters);
// protótipos para as tarefas
void TaskReadTemperature(void *pvParameters);
// Variável para armazenar a temperatura lida
volatile float temperature = 0.0;
void setup() {
  pinMode(LED_PIN_1, OUTPUT);
xTaskCreate(
  TaskBlink1, //função da tarefa - Ponteiro
  "Blink1",
  128, //tamanho da pilha
  NULL, //Parametro da tarefa
  2, //Prioridade - números mais altos - proporcional a prioridade
  NULL //agendar tarefa
); pinMode(LED_PIN_2, OUTPUT);
xTaskCreate(
  TaskBlink2, 
  "Blink2",
  128, //tamanho da pilha
  NULL, //Parametro da tarefa
  1, //Prioridade - números mais altos - proporcional a prioridade
  NULL //agendar tarefa
);

Serial.begin(9600);
lcd.begin(16,2);
// cria as tarefas
xTaskCreate(
TaskReadTemperature,
"ReadTemperature",
128,
NULL,
3,
NULL );
//Crie as outras tarefas aqui
}
void loop() {
// nada aqui!
}
void TaskBlink1(void *pvParameters){
  (void) pvParameters;
  for(;;){
    digitalWrite(LED_PIN_1, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS); //Função milis do RTOS
    digitalWrite(LED_PIN_1, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS); //Função milis do RTOS
  }
}
void TaskBlink2(void *pvParameters){
  (void) pvParameters;
  for(;;){
    if ( temperature == 26.00)
    {
    
    digitalWrite(LED_PIN_2, HIGH);
    vTaskDelay(500 / portTICK_PERIOD_MS); //Função milis do RTOS
    digitalWrite(LED_PIN_2, LOW);
    vTaskDelay(500 / portTICK_PERIOD_MS); //Função milis do RTOS
  }
}}
void TaskReadTemperature(void *pvParameters) {
(void) pvParameters;
float sensorValue = 0.0;
for (;;) {
// Aqui você normalmente leria o valor do sensor de temperatura.
// Por simplicidade, vamos apenas simular um sensor variando a
//temperatura de -10 a 40.
sensorValue = -10.0 + (rand() % 51); // gera um número aleatório entre
//-10 e 40
temperature = sensorValue;
vTaskDelay(2000 / portTICK_PERIOD_MS); // aguarda por 2 segundos
lcd.setCursor(0,0);
lcd.print("Temp: ");
lcd.print(temperature);
lcd.print(" C");
// vTaskDelay(1000 / portTICK_PERIOD_MS);
}
}