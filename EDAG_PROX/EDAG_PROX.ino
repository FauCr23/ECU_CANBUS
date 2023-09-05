/* Creado por a01735674 Fausto Carrillo, programa para sistema de alarma de proximidad
 *  correo A01735674@tec.mx
 */
#include <SPI.h>  //Librerias para comunicación con perifericos SPI
#include <mcp2515.h> //Libreria para comunicacion con modulo MCP2515

#define NOTE_A7  3520 //Nota musical para el zumbador

int ECHO=5;
int TRIG=4;
int DURACION;
int DISTANCIA;
int BUZZER = A4;

struct can_frame canMsg1; //Definición de la estructura del mensaje 

MCP2515 mcp2515(10); //Declaración del Pin para conexión con modulo MCP


void setup() { 
  while (!Serial);
  Serial.begin(9600);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS); //Velocidad de comunicación con el modulo MCP
  mcp2515.setNormalMode(); //Modo de recibir y enviar
  
  Serial.println("Example: Write to CAN");

  pinMode(BUZZER, OUTPUT);
  pinMode(ECHO, INPUT);
  pinMode(TRIG,OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {
  digitalWrite(TRIG, HIGH); //Encendido del sensor ultrasonico
  delay(1);
  digitalWrite(TRIG,LOW);
  DURACION= pulseIn(ECHO, HIGH);
  DISTANCIA = DURACION/ 58.2;
  //Serial.print("DISTANCIA: ");
  //Serial.println(DISTANCIA);
  
  delay(200);
  
  if (DISTANCIA <=15){ //condición para el encendido de la alarma 
    digitalWrite(LED_BUILTIN, HIGH);
    tone(BUZZER, NOTE_A7, 8);
    delay(DISTANCIA*7);
    digitalWrite(LED_BUILTIN, LOW);
    noTone(BUZZER);
    delay(DISTANCIA*7);
  }

  canMsg1.can_id  = 0x0F6; //Direccion del dispositivo de envio
  canMsg1.can_dlc = 1; //Largo del mensaje
  canMsg1.data[0] = DISTANCIA; //Variable que se envia mediante el CAN bus
  
  
  mcp2515.sendMessage(&canMsg1);
  

  Serial.println("Messages sent");
  
}
