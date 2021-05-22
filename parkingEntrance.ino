#include <HCSR04.h>
#include <Servo.h>

#define trig 4
#define echo 5

HCSR04 ultrasonic(trig, echo);

Servo servoMotor; // Declaração da variável p/ o servo motor
long cm;          // Declaração da variável p/ distância
int buzzer = 11;  // Declaração da variável p/ o buzzer

void setup() {
  pinMode(13, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.begin(9600); // Inicialização do monitor serial
  Serial.println("Lendo dados do sensor...");
}

void loop() {
  cm = ultrasonic.dist(); // Atribuí a variável cm a função dist()

  servoMotor.attach(6);  // Liga o servo motor
  servoMotor.write(0);   // Coloca o servo motor em 0°
  digitalWrite(13, LOW); // Inicializa o loop com o LED verde desligado
  digitalWrite(8, LOW);  // Inicializa o loop com o LED vermelho desligado

  if (cm < 5) {             // Se a distância é menor que 5cm
    digitalWrite(13, HIGH);  // Liga o LED verde
    servoMotor.write(90);    // Posiciona o motor em 90°
    tone(buzzer, 1500);      // Emite um som com frequência de 1500Hz no buzzer
    delay(200);              // Aguarda 0,2 segundos
    noTone(buzzer);          // Encerra a reprodução do som no buzzer
    delay(2000);             // Aguarda 2 segundos
    Serial.println("Abriu"); // Envia "Abriu" para o monitor serial
  }
  else {                      // Senão
    digitalWrite(8, HIGH);    // Liga o LED vermelho
    servoMotor.write(0);      // Posiciona o motor em 0°
    delay(100);               // Aguarda 0,1 segundo
    Serial.println("Fechou"); // Envia "Fechou" para o monitor serial
  }

  servoMotor.detach(); // Desliga o servo motor

  Serial.print("Distância em cm: ");
  Serial.println(cm); // Printa a distância em CM no monitor serial
}
