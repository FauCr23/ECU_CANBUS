/* Creado por a01735674 Fausto Carrillo, programa para sistema de alarma de proximidad
 *  correo A01735674@tec.mx
 */
#include <LiquidCrystal_I2C.h> //LIbreria para comunicarse con el modulo I2C de la pantalla LCD
#include <Wire.h> //Libreria para comunicación I2C
#include <LCD.h> //Libreria para comandos de la pantalla LCD
#include <mcp2515.h> //Libreria de comandos para modulo MCP

struct can_frame canMsg; //Definición de la estructura del mensaje
MCP2515 mcp2515(10); //Declaración del Pin para conexión con modulo MCP

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7); //Declaración de los pines utilizados en la pantalla LCD

int a;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS); /Velocidad de comunicación del modulo MCP
  mcp2515.setNormalMode(); //Modo de recibir y enviar
  
  lcd.setBacklightPin(3,POSITIVE);  //parametros de la pantalla LCD
  lcd.setBacklight(HIGH);
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  a=recibir_msg();
  /* se despliega el mensaje recibido por el modulo MCP2515 CAN BUS en la pantalla LCD
   *  con la leyenda de distancia ya que presenta el dato recibido de la alarma de proximidad
   */
  Serial.print("mensaje: ");
  Serial.println(a);
  lcd.setCursor(0, 0);
  lcd.print("Distancia: ");
  lcd.setCursor(12, 0);
  lcd.print(a);
  delay(3000);
  lcd.clear();
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
