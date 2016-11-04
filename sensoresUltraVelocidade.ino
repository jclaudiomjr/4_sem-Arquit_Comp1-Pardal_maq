#include <Ultrasonic.h>   // inclui biblioteca de manipulação de servos motores.   
  #define echoPin_1 6 //Pino 6 recebe o pulso do echo   
  #define trigPin_1 7 //Pino 7 envia o pulso para gerar o echo
  #define echoPin_2 2 //Pino 2 recebe o pulso do echo   
  #define trigPin_2 3 //Pino 3 envia o pulso para gerar o echo
  #define red_led_1 12 //Pino 12 envia energia para o led 1
  #define red_led_2 13 //Pino 13 envia energia para o led 2
  #define white_led 8 //Pino 8 envia energia para o led
  #define distancia 0.64 //Distancia entre os sensores 
  Ultrasonic ultrasonic_1(7,6);
  Ultrasonic ultrasonic_2(3,2); 
  int carroPassouStart = 0, carroPassouFinish= 0;
  float velocidade = 0.0;
  float tempo = 0.0, start = 0.0, finish = 0.0, divisao = 1000.0;
  // Executado na inicialização do Arduino   
  void setup(){   
  Serial.begin(9600); // inicializa a comunicação serial para Debug ou para mostrar dados em um display LCD   
  pinMode(trigPin_1, OUTPUT);  // define o pino triger como saída.   
  pinMode(echoPin_1, INPUT);  // define o pino echo como entrada.
  pinMode(trigPin_2, OUTPUT);  // define o pino triger como saída.   
  pinMode(echoPin_2, INPUT);  // define o pino echo como entrada.
  pinMode(red_led_1, OUTPUT); // define o pino do led 1 como saída.  
  pinMode(red_led_2, OUTPUT); // define o pino do led 2 como saída.
  pinMode(white_led, OUTPUT); // define o pino do led branco como saída.
  digitalWrite(red_led_1, LOW);
  digitalWrite(red_led_2, LOW);
  digitalWrite(white_led, LOW);
  }   
  // Loop pincipal do Arduino   
  void loop(){   
    if (ultrasonic_1.Ranging(CM) < 6) {
      start = millis();//start cronometro
      carroPassouStart = 1;
      digitalWrite(red_led_1, HIGH);
      digitalWrite(white_led, LOW);
      digitalWrite(red_led_2, LOW);
    }
    if(ultrasonic_2.Ranging(CM) < 6) {
        finish = millis();//end cronometro
        carroPassouFinish = 1; //ativa flag
        digitalWrite(red_led_2, HIGH);
    }

    if ((carroPassouStart && carroPassouFinish) && finish > start) {
      tempo = (finish - start)/divisao;//tempo = tempoCronometrado;
      Serial.print("tempo: ");
      Serial.print(tempo);
      Serial.println(" s");
      velocidade = distancia / tempo;
      Serial.print("velocidade: ");
      Serial.print(velocidade);
      Serial.println(" m/s ");
      carroPassouStart = 0;
      carroPassouFinish = 0;
      if (velocidade > 1){
        digitalWrite(white_led, HIGH);
      }
      digitalWrite(red_led_1, LOW);
      //digitalWrite(red_led_2, LOW);
      //digitalWrite(white_led, LOW);
    }
    delay(50);
  }   
