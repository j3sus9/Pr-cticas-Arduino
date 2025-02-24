#include <Arduino.h>

#define LOOP_TMP 10		//miliseconds
const byte button1 = 3;
const byte button2 = 10;
const byte button_Optoacoplado = 11;

int apartado = 0; //Variable para almacenar el apartado en el que estamos

void setup() {
  Serial.begin(115200);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button_Optoacoplado, INPUT_PULLUP);

  Serial.println("PRÁCTICA 1 - PULSADORES");

  Serial.println("Seleccione el modo escribiendo un número en el Serial Monitor:");
  Serial.println("1 - Mensajes al pulsar/soltar");
  Serial.println("2 - Interruptor ON/OFF");
  Serial.println("3 - Conmutador con los 3 botones");
}

void apartadoUno(){
  static int tmp_loop = 0;
    static int stateButton1 = HIGH;
    static int stateButton2 = HIGH;
    static int stateButton_OptoAcoplado = HIGH;

    if ((millis() - tmp_loop) > LOOP_TMP) {
        tmp_loop = millis();

        int state1 = digitalRead(button1);
        if (stateButton1 != state1) {
          stateButton1 = state1;
          if(state1 == LOW){ //Cuando está pulsado es un LOW porque está declarado como INPUT_PULLUP
            Serial.println("Botón 1 --> Soltado");
          }else{
            Serial.println("Botón 1 --> Pulsado");
          }
        }

        int state2 = digitalRead(button2);
        if (stateButton2 != state2) {
            stateButton2 = state2;
            if(state2 == LOW){
              Serial.println("Botón 2 --> Soltado");
            }else{
              Serial.println("Botón 2 --> Pulsado");
            }
        }

        int state3 = digitalRead(button_Optoacoplado);
        if (stateButton_OptoAcoplado != state3) {
          stateButton_OptoAcoplado = state3;
          if(state3 == LOW){ //Cuando está pulsado es un LOW porque está declarado como INPUT_PULLUP
            Serial.println("Botón Optoacoplado --> Soltado");
          }else{
            Serial.println("Botón Optoacoplado --> Pulsado");
          }
        }
    }
}

void apartadoDos(){
  static int tmp_loop = 0;
  static int stateButton1 = HIGH; 
  static int stateButton2 = HIGH;
  static int stateButton_OptoAcoplado = HIGH;

  if((millis()-tmp_loop) > LOOP_TMP){
      tmp_loop = millis();

      int state1 = digitalRead(button1);
      if(stateButton1 != state1){
        stateButton1 = state1;
        static int cont1 = 0;
        cont1++;
        if(cont1 == 1){
          Serial.println("Boton 1 --> Estado: OFF");
        }else{
          Serial.println("Boton 1 --> Estado: ON");
          cont1 = 0;
        }
      }

      int state2 = digitalRead(button2);
      if(stateButton2 != state2){
        stateButton2 = state2;
        static int cont2 = 0;
        cont2++;
        if(cont2 == 1){
          Serial.println("Boton 2 --> Estado: OFF");
        }else{
          Serial.println("Boton 2 --> Estado: ON");
          cont2 = 0;
        }
      }

      int state3 = digitalRead(button_Optoacoplado);
      if(stateButton_OptoAcoplado != state3){
        stateButton_OptoAcoplado = state3;
        static int cont3 = 0;
        cont3++;
        if(cont3 == 1){
          Serial.println("Boton Optoacoplado --> Estado: OFF");
        }else{
          Serial.println("Boton Optoacoplado --> Estado: ON");
          cont3 = 0;
        }
      }
  }
}

void cambiarModo(){
  static int cont = 0;
  cont++;
  if(cont == 1){
    Serial.println("Estado: OFF");
  }else{
    Serial.println("Estado: ON");
    cont = 0;
  }
}

void apartadoTres(){
  static int tmp_loop = 0;
  static int stateButton1 = 1; 
  static int stateButton2 = 1;
  static int stateButtonOptoacoplado = 1;

  if((millis()-tmp_loop) > LOOP_TMP){ 
      tmp_loop = millis();

      int state1 = digitalRead(button1);
      if(stateButton1 != state1){
        if(stateButton1 == 0 && state1 == 1){
          cambiarModo();
        }
        stateButton1 = state1;
      }

      int state2 = digitalRead(button2);
      if(stateButton2 != state2){
        if(stateButton2 == 0 && state2 == 1){
          cambiarModo();
        }
        stateButton2 = state2;
      }

      int state3 = digitalRead(button_Optoacoplado);
      if(stateButtonOptoacoplado != state3){
        if(stateButtonOptoacoplado == 0 && state3 == 1){
          cambiarModo();
        }
        stateButtonOptoacoplado = state3;
      }
  }
}

void loop(){
  if (Serial.available()) {
    char entrada = Serial.read();
    if (entrada >= '1' && entrada <= '3') {
        apartado = entrada - '0';  // Convertir char a int
        Serial.print("Modo seleccionado: ");
        Serial.println(apartado);
    }
  }

  switch (apartado){
    case 1:
      apartadoUno();
      break;
    case 2:
      apartadoDos();
      break;
    case 3:
      apartadoTres();
      break;
  }
}

/* PARTE I - MOSTRAR MENSAJES PULSAR Y SOLTAR 
#define LOOP_TMP 10		//miliseconds
const byte interruptPin = 3;
const byte button1 = 10;
const byte button2 = 11;

void detectarCambio() {
  int estadoPulsador = digitalRead(interruptPin);  // Leer estado del botón
  if(estadoPulsador == LOW){
    Serial.println("Botón 1 --> Soltado");
  }else{
    Serial.println("Botón 1 --> Pulsado");
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(interruptPin, INPUT_PULLUP);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), detectarCambio, CHANGE);
}

void loop() {
  static int tmp_loop = 0;
  static int stateButton1 = 1; 
  static int stateButton2 = 1;

  if((millis()-tmp_loop) > LOOP_TMP){ //Solo se ejecuta si han pasado más de 10 ms para ahorrarse miles de comparaciones inncesarias
      tmp_loop = millis();

      int state1 = digitalRead(button1);

      if (stateButton1 != state1) {
        stateButton1 = state1;  // Actualizar el estado
        if(state1 == LOW){ //Cuando está pulsado es un LOW porque está declarado como INPUT_PULLUP
          Serial.println("Botón 2 --> Soltado");
        }else{
          Serial.println("Botón 2 --> Pulsado");
        }
      }

      int state2 = digitalRead(button2);

      if (stateButton2 != state2) {
        stateButton2 = state2;  // Actualizar el estado
        if (state2 == LOW) {
          Serial.println("Botón Optoacoplado --> Soltado");
        } else {
          Serial.println("Botón Optoacoplado --> Pulsado");
        }
      }
  }
}
*/

/* PARTE II - Cada botón pasa de ON a OFF al pulsar/soltar
#define LOOP_TMP 10		//miliseconds
const byte button1 = 3;
const byte button2 = 10;
const byte button_Optoacoplado = 11;

void setup() {
  Serial.begin(115200);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button_Optoacoplado, INPUT_PULLUP);
}

void cambiarModo(byte pin){
  if(pin == 3){
    static int cont1 = 0;
    cont1++;
    if(cont1 == 1){
      Serial.println("Boton 1 --> Estado: OFF");
    }else{
      Serial.println("Boton 1 --> Estado: ON");
      cont1 = 0;
    }
  }
  if(pin == 10){
    static int cont2 = 0;
    cont2++;
    if(cont2 == 1){
      Serial.println("Boton 2 --> Estado: OFF");
    }else{
      Serial.println("Boton 2 --> Estado: ON");
      cont2 = 0;
    }
  }
  if(pin == 11){
    static int cont3 = 0;
    cont3++;
    if(cont3 == 1){
      Serial.println("Boton Optoacoplado --> Estado: OFF");
    }else{
      Serial.println("Boton Optoacoplado --> Estado: ON");
      cont3 = 0;
    }
  }
}

void loop() {
  static int tmp_loop = 0;
  static int stateButton1 = 1; 
  static int stateButton2 = 1;
  static int stateButtonOptoacoplado = 1;

  if((millis()-tmp_loop) > LOOP_TMP){ //Solo se ejecuta si han pasado más de 10 ms para ahorrarse miles de comparaciones inncesarias
      tmp_loop = millis();

      int state1 = digitalRead(button1);
      if(stateButton1 != state1){
        stateButton1 = state1;
        cambiarModo(button1);
      }

      int state2 = digitalRead(button2);
      if(stateButton2 != state2){
        stateButton2 = state2;
        cambiarModo(button2);
      }

      int state3 = digitalRead(button_Optoacoplado);
      if(stateButtonOptoacoplado != state3){
        stateButtonOptoacoplado = state3;
        cambiarModo(button_Optoacoplado);
      }
  }
}
*/

/* PARTE III - Los tres botones funcionan como un conmutador
#define LOOP_TMP 10		//miliseconds
const byte button1 = 3;
const byte button2 = 10;
const byte button_Optoacoplado = 11;

void setup() {
  Serial.begin(115200);
  pinMode(button1, INPUT_PULLUP);
  pinMode(button2, INPUT_PULLUP);
  pinMode(button_Optoacoplado, INPUT_PULLUP);
}

void cambiarModo(){
  static int cont = 0;
  cont++;
  if(cont == 1){
    Serial.println("Estado: OFF");
  }else{
    Serial.println("Estado: ON");
    cont = 0;
  }
}

void loop() {
  static int tmp_loop = 0;
  static int stateButton1 = 1; 
  static int stateButton2 = 1;
  static int stateButtonOptoacoplado = 1;

  if((millis()-tmp_loop) > LOOP_TMP){ //Solo se ejecuta si han pasado más de 10 ms para ahorrarse miles de comparaciones inncesarias
      tmp_loop = millis();

      int state1 = digitalRead(button1);
      if(stateButton1 != state1){
        if(stateButton1 == 0 && state1 == 1){
          cambiarModo();
        }
        stateButton1 = state1;
      }

      int state2 = digitalRead(button2);
      if(stateButton2 != state2){
        if(stateButton2 == 0 && state2 == 1){
          cambiarModo();
        }
        stateButton2 = state2;
      }

      int state3 = digitalRead(button_Optoacoplado);
      if(stateButtonOptoacoplado != state3){
        if(stateButtonOptoacoplado == 0 && state3 == 1){
          cambiarModo();
        }
        stateButtonOptoacoplado = state3;
      }
  }
}
*/