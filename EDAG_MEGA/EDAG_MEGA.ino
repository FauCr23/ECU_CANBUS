/* Creado por a01735674 Fausto Carrillo, programa para sistema de alarma de proximidad
 *  correo A01735674@tec.mx
 */
#include <SPI.h> //Librerias para comunicación con perifericos SPI
#include <mcp2515.h> //Libreria para comunicacion con modulo MCP2515

struct can_frame canMsg; //Definición de la estructura del mensaje 
MCP2515 mcp2515(53); //Declaración del Pin para conexión con modulo MCP

int a;
void setup() {
  Serial.begin(9600);
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS); //Velocidad de comunicación del modulo MCP
  mcp2515.setNormalMode(); //Modo de recibir y enviar
  
}

void loop() {
  a=recibir_msg();
  Serial.print("mensaje: ");
  Serial.println(a);
  enviar_msg(a);
  delay(500);
}

int recibir_msg(){ 
  /*Esta funcion toma el dato recibido por el modulo CAN a traves del BUS CAN y lo 
   * guarda en una variable y regresa la variable
   */
  int x; 
  if (mcp2515.readMessage(&canMsg) == MCP2515::ERROR_OK) {
    x=canMsg.data[0];         
  }
  return x;
}

int enviar_msg(int msg){
  /* Esta funcion envia el mensaje deseado por medio del CAN BUS tomando una direccion
   * el largo del mensaje y el mensaje
   */
  struct can_frame canMsg1;
  canMsg1.can_id  = 0x0F7;
  canMsg1.can_dlc = 1;
  canMsg1.data[0] = msg;
  
  
  mcp2515.sendMessage(&canMsg1);
  

  Serial.print("Message sent:  ");
  Serial.println(msg);
}
