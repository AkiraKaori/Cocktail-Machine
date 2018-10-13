#include<Servo.h>
                    /*############################################################################################################*/
Servo servo;
int steps = 10;       // pin step 10
int direccion = 12;   // pin direccion 12
int sentido = false;    // True= izquierda   False=Derecha
int x;
int estado = 0;       //Letra enviada por bluetooth
int enviar = 0;       //Comienzo de la app BARBOT
int vrgb = 6;
int rrgb = 3;
int argb = 5;

                    /*############################################################################################################*/
void setup() {
  Serial.begin(9600);            
  pinMode(steps, OUTPUT); 
  pinMode(direccion, OUTPUT);
  servo.attach(9); 
  pinMode(vrgb,OUTPUT);
  pinMode(argb,OUTPUT);
  pinMode(rrgb,OUTPUT);
}
                    /*############################################################################################################*/
void loop() {
  if (Serial.available() > 0){
    estado = Serial.read();
  }
  if (  estado == 0){
    analogWrite(rrgb,255);
    analogWrite(vrgb,64);
    analogWrite(argb,120);
  }
    switch(estado){
      case 'a'://MANZANA
        Uno(700,true);
        SERVO(0,255,0);
        Uno(700,false);
        estado = 0; 
       break;
       
       case 'b'://PIÑA
        Uno(1400,true);
        SERVO(10,200,90);
        Uno(1400,false);   
        estado = 0; 
       break;
       
       case'c'://NARANJA
        Uno(2100,true);
        SERVO(255,18,0);
        Uno(2100,false);
        estado = 0; 
       break;
       
       case 'd'://NARANJA PIÑA
        Uno(1400,true);
        SERVO(10,200,90);
        Uno(700,true);
        SERVO(255,18,0);
        Uno(2100,false);
        estado = 0; 
       break;

       case 'e'://NARANJA MANZANA
        Uno(700,true);
        SERVO(0,255,0);
        Uno(1400,true);
        SERVO(255,18,0);
        Uno(2100,false);
        estado = 0; 
       break;

       case 'f'://PIÑA MANZANA
       Uno(700,true);
       SERVO(0,255,0);
       Uno(700,true);
       SERVO(10,200,90);
       Uno(1400,false);
       estado = 0; 
       break;
  }

  Serial.print("Estado: ");
  Serial.println(estado);
  delay(1000); 

 }
                    /*############################################################################################################*/
 void Uno(int distancia,bool VoF){
       for (x = 0 ; x < distancia ;x++){
         int sentido = VoF;    // True= izquierda   False=Derecha
         digitalWrite(direccion, sentido);    // cambiamos de dirección segun sentido
         digitalWrite(steps, HIGH);         // Aqui generamos un flanco de bajada HIGH - LOW
         delayMicroseconds(5);              // Pequeño retardo para formar el pulso en STEP
         digitalWrite(steps, LOW);         // y el A4988 de avanzara un paso el motor
         delayMicroseconds(1000); // generamos un retardo con el valor leido del potenciometro               }
      }
 }

                    /*############################################################################################################*/
 
void SERVO(int rojo, int verde, int azul){
  delay(750);
  for(int i = 0 ; i <= 180 ; i++){
    servo.write(i);
    analogWrite(rrgb,rojo);
    analogWrite(vrgb,verde);
    analogWrite(argb,azul);
  } 
    analogWrite(rrgb,rojo);
    analogWrite(vrgb,verde);
    analogWrite(argb,azul);
    delay(1500);
  for(int i = 179 ; i > 0 ; i--) {
    servo.write(i);
  }
    analogWrite(rrgb,rojo);
    analogWrite(vrgb,verde);
    analogWrite(argb,azul);
  delay(750);
    analogWrite(rrgb,0);
    analogWrite(vrgb,0);
    analogWrite(argb,0);
}
