/**
 * SCHRÖDINGER's CAT
 * Developed by: Rafael Anguiano 
 * Cibernética y Sistemas Computacionales
 * 6to Semestre
 * 03/03/2021
 */
#include <stdlib.h>   
#include <time.h>     //Librería de tiempo
#include <EEPROM.h>   //Librería de EEPROM
unsigned long tiempo = 0; 
int b = 0;            //Trigger para ejecutar la función deseada
int g = 0;            //Creo al Sensor
int h;
int s;
int l;

void setup() {
  Serial.begin(9600);
  h = EEPROM.read(0);         //Mi dirección 0 me dirá si el gato está afuera o adentro, leo dónde se quedó el gato
  EEPROM.write(0, h);         //Escribo otra vez por en caso de que h
  srand(time(NULL));
  pinMode(8,OUTPUT);
}

void miretardo(int a){        // Función de retardo que funciona con millis y no delay
  if( millis() > tiempo + a){ //Comparador para saber si ya pasó el total de milisegundos a esperar.
    tiempo = millis();        //Vuelvo a poner el tiempo en 0
    b = 1;                    //Setéo mi bandera o variable auxiliar en 1 para indicar en el loop que ya se esperó el tiempo.
  }
}

void entro(){
  digitalWrite(8, LOW);
  delay(250);
  digitalWrite(8, HIGH);   //Parpadeo 1
  delay(250);
  digitalWrite(8, LOW);
}

void salio(){
  digitalWrite(8, LOW);
  delay(250);
  digitalWrite(8, HIGH);   //Parpadeo 1
  delay(250);
  digitalWrite(8, LOW);
  delay(250);
  digitalWrite(8, HIGH);   //Parpadeo 2
  delay(250);
  digitalWrite(8, LOW);
}

void loop() {
  int a = 5000;               //En esta variable indico la cantidad de tiempo a esperar en milisegundos.
  miretardo(a);               //Mando llamar mi función "miretardo"
  if(b==1){
    
    g = rand()%2;           //Cada que g == 1, es porque el sensor detectó y cambió de lugar el gato.
    Serial.println(g);
    if(g == 1){         //Pregunto si el sensor detectó.
      s = EEPROM.read(0);     //Leo el estado del gato,  0 para saber si el gato se encuentra adentro o afuera 0 (adentro), 1 (afuera).
      //Serial.println("Cambio");
      if( s == 0 ){           //Pregunto si está adentro
        l = 1;                //Cambio mi variable s que es con la que defino si está afuera.
        EEPROM.update(0, l);  //Actualizo en memoria dónde está el gato.
        Serial.println("Salio");
        //salio();    //Envío a mi función de led salida
        salio();
      }
      if( s == 1){            //Pregunto si esta afuera
        l = 0;                //Cambio mi variable s
        EEPROM.update(0, l);  //Actualizo mi memoria del estado.
        Serial.println("Entro");
        entro();
      }
    } 
    b=0;
  }
}
