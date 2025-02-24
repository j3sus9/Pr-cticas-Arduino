#include <Arduino.h>

#define LOOP_TMP 10		//miliseconds
#define	BUTTON1 3   	// Pulsador 1

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON1, INPUT);
}

void loop() {
  static int tmp_loop = 0;
  static int state_Button1 = 1; 

  if((millis()-tmp_loop) > LOOP_TMP){ //Solo se ejecuta si han pasado más de 10 ms para ahorrarse miles de comparaciones inncesarias
      tmp_loop = millis();

      int state = digitalRead(BUTTON1);

      if (state_Button1 != state) {
        state_Button1 = state;  // Actualizar el estado

        Serial.print("Estado: ");
        Serial.println(state_Button1);
      }
  }
}
