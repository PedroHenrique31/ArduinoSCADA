/*
  Autor: Pedro Henrique Cerneiro de Araújo        RA:22108287
  Autor: Bruna Stephanie Soares Gonçalves         RA:21707921
*/
#include "SimpleModbusSlave.h"
/*#define saida1
#define saida2
#define saida3*/
#define LED_AZ 9
#define LED_VD 10
#define LED_VM 11
#define CHAVE  12
enum
{
  VALOR_POT1,
  VALOR_POT2,
  VALOR_POT3,
  VALOR_ELIPSER,
  VALOR_ELIPSEG,
  VALOR_ELIPSEB,
  VALOR_PWMR,
  VALOR_PWMG,
  VALOR_PWMB,
  MAN_AUTO,
  HOLDING_REGS_SIZE
};
unsigned int holdingRegs[HOLDING_REGS_SIZE];

void setup() {
  pinMode(LED_AZ,OUTPUT);
  pinMode(LED_VD,OUTPUT);
  pinMode(LED_VM,OUTPUT);
  //Serial.begin(9600);
  modbus_configure(&Serial, 9600, SERIAL_8N1, 1, 2, HOLDING_REGS_SIZE,holdingRegs);
  modbus_update_comms(9600, SERIAL_8N1, 1);

}

void loop() {
  modbus_update();
  int valor1,valor2,valor3;

  holdingRegs[VALOR_POT1] = analogRead(A0);
  holdingRegs[VALOR_POT2] = analogRead(A1);
  holdingRegs[VALOR_POT3] = analogRead(A2);
  holdingRegs[MAN_AUTO] = digitalRead(CHAVE);
 
  valor1=map(holdingRegs[VALOR_POT1],0,1023,0,255);
  valor2=map(holdingRegs[VALOR_POT2],0,1023,0,255);
  valor3=map(holdingRegs[VALOR_POT3],0,1023,0,255);


  /* int estado0 = holdingRegs[VALOR_POT1];
   int estado1 = holdingRegs[VALOR_POT2];
   int estado2 = holdingRegs[VALOR_POT3];   */  

if (holdingRegs[MAN_AUTO] == 0) {
   
    holdingRegs[VALOR_PWMR] = map (holdingRegs[VALOR_POT1], 0, 1023, 0, 255);
    analogWrite (LED_VM, holdingRegs [VALOR_PWMR]);

    holdingRegs[VALOR_PWMG] = map (holdingRegs[VALOR_POT2], 0, 1023, 0, 255);
    analogWrite (LED_VD, holdingRegs [VALOR_PWMG]);  

    holdingRegs[VALOR_PWMR] = map (holdingRegs[VALOR_POT3], 0, 1023, 0, 255);
    analogWrite (LED_AZ, holdingRegs [VALOR_PWMB]);
   
  }

  else {
    holdingRegs[VALOR_PWMR] = holdingRegs[VALOR_ELIPSER];
    analogWrite (LED_VM, holdingRegs [VALOR_PWMR]);

    holdingRegs[VALOR_PWMG] = holdingRegs[VALOR_ELIPSEG];
    analogWrite (LED_VD, holdingRegs [VALOR_PWMG]);    
   
    holdingRegs[VALOR_PWMB] = holdingRegs[VALOR_ELIPSEB];
    analogWrite (LED_AZ, holdingRegs [VALOR_PWMB]);    
 
  }
// ==============================================================
// retirar isso daqui depois, mas pra enquanto tá top  
/*    Serial.print("Estado do botão: ");
    Serial.print(estado0);
    Serial.print(" ");    
    Serial.print(estado1);
    Serial.print(" ");
    Serial.print(estado2);
    Serial.println(" ");

//==============================================================
 */  
  analogWrite(LED_AZ,valor1);
  analogWrite(LED_VD,valor2);
  analogWrite(LED_VM,valor3);


}