#include <TaskManager.h>
#include <ESP32Servo.h>
#include <WiFi.h>
#include "ThingSpeak.h"

const char* ssid = "Xiaomi JT";   // your network SSID (name)
const char* password = "12345jrtb";   // your network password

WiFiClient  client;

unsigned long myChannelNumber = 1850988;
const char * myWriteAPIKey = "7R5LZ8SCG3AP3OD0";

unsigned long lastTime = 0;
unsigned long timerDelay = 30000;


int ENA = 14;         //pin GPIO14
int IN1 = 17;         //pin GPIO27
int IN2 = 5;         //pin GPIO26

int ENB = 32;         //pin GPIO32
int IN3 = 18;         //pin GPIO25
int IN4 = 19;         //pin GPIO33

int trigPin = 0;      // trigger pin
int echoPin = 4;      // echo pin

int led_RED = 32;
int led_GREEN = 33;
int led_YELLOW = 27;

Servo Brazo;
Servo Pinza;

int pos_brazo = 0;
int pos_pinza = 0;

int pin_brazo = 13;
int pin_pinza = 12;

int recoleccion = 0;

int periodo = 15000;
unsigned long tiempoAhora = 0;
long t; //timepo que demora en llegar el eco
long d; //distancia en centimetros

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200) ; //iniciailzamos la comunicación
  // Declaramos todos los pines como salidas
  pinMode (ENA, OUTPUT);
  pinMode (ENB, OUTPUT);
  pinMode (IN1, OUTPUT);
  pinMode (IN2, OUTPUT);
  pinMode (IN3, OUTPUT);
  pinMode (IN4, OUTPUT);
  pinMode(trigPin, OUTPUT); //pin como salida
  pinMode(echoPin, INPUT);  //pin como entrada
  digitalWrite(trigPin, LOW);//Inicializamos el pin con 0
  pinMode(led_RED, OUTPUT);
  pinMode(led_GREEN, OUTPUT);
  pinMode(led_YELLOW, OUTPUT);

  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  Brazo.setPeriodHertz(50);    // standard 50 hz servo
  Brazo.attach(pin_brazo, 500, 2400);
  Pinza.setPeriodHertz(50);    // standard 50 hz servo
  Pinza.attach(pin_pinza, 500, 2400);

  WiFi.mode(WIFI_STA);

// Connect or reconnect to WiFi
    if (WiFi.status() != WL_CONNECTED) {
      Serial.print("Attempting to connect");
      while (WiFi.status() != WL_CONNECTED) {
        WiFi.begin(ssid, password);
        delay(5000);
      }
      Serial.println("\nConnected.");
    }
  ThingSpeak.begin(client);
}

void loop() {
  Leds();

  Adelante();
 // Tasks.update();

  ///BASE DE DATO////////

  if ((millis() - lastTime) > timerDelay) { 
    ///////////////ultra
    dist();
    if (d <= 20) {
      recoleccion += 1 ;
      digitalWrite(led_RED, HIGH);

      Parar();
      Brazo.write(90);              // tell servo to go to position in variable 'pos'
      delay(1000);

      Pinza.write(90);              // tell servo to go to position in variable 'pos'
      delay(1000);

      Brazo.write(10);              // tell servo to go to position in variable 'pos'
      delay(150);
      Pinza.write(0);              // tell servo to go to position in variable 'pos'
      delay(1000);
    }
  }

  ThingSpeak.setField(1, (recoleccion));

  if (millis() >= tiempoAhora + periodo) {
    tiempoAhora += periodo;
    int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
    //delay(15000);
    if (x == 200) {
      Serial.println("Channel update successful.");
    }
    else {
      Serial.println("Problem updating channel. HTTP error code " + String(x));
    }
    digitalWrite(led_RED, LOW);
  }
}

void dist() {
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);          //Enviamos un pulso de 10us
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);          //Enviamos un pulso de 10us

  t = pulseIn(echoPin, HIGH); //obtenemos el ancho del pulso
  d = t / 59;           //escalamos el tiempo a una distancia en cm
  Serial.print("Distancia: ");
  Serial.print(d);      //Enviamos serialmente el valor de la distancia
  Serial.print("cm");
  Serial.println();
  delay(10);          //Hacemos una pausa de 100ms
}

void Leds() {
  digitalWrite(led_YELLOW, HIGH);
  delay(500);
  digitalWrite(led_GREEN, HIGH);
  delay(500);
  digitalWrite(led_YELLOW, LOW);
  delay(500);
  digitalWrite(led_GREEN, LOW);
}

void Parar()
{
  //Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, LOW);
  digitalWrite (ENA, HIGH); //Velocidad motor A
  //Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, LOW);

}

void Adelante()
{
  Serial.print("ADELANTE");
  //Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  digitalWrite (ENA, HIGH); //Velocidad motor A
  //Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  digitalWrite (ENB, HIGH); //Velocidad motor B
}

void Atras ()
{
  Serial.print("ATRAS");
  //Direccion motor A
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  digitalWrite (ENA, HIGH); //Velocidad motor A
  //Direccion motor B
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  digitalWrite (ENB, HIGH); //Velocidad motor B
}

void Izquierda()
{
  Serial.print("DERECHA");
  //Direccion motor A
  digitalWrite (IN1, LOW);
  digitalWrite (IN2, HIGH);
  digitalWrite (ENA, HIGH); //Velocidad motor A
  //Direccion motor B
  digitalWrite (IN3, HIGH);
  digitalWrite (IN4, LOW);
  digitalWrite (ENB, HIGH); //Velocidad motor A
}

void Derecha()
{
  Serial.print("IZQUIERDA");
  //Direccion motor A
  digitalWrite (IN1, HIGH);
  digitalWrite (IN2, LOW);
  digitalWrite (ENA, HIGH); //Velocidad motor A
  //Direccion motor B
  digitalWrite (IN3, LOW);
  digitalWrite (IN4, HIGH);
  digitalWrite (ENB, HIGH); //Velocidad motor A
}
