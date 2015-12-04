//Control de motores de barco 
//Este programa recibe datos mediante un bluetooth 
//conectado a los pines TX, RX del arduino, 
//y los procesa para controlar 2 motores 
//de un barco mediante pulsos PWM. 
//El circuito externo esta compuesto por 2 puentes H,
//el cual sus entradas van conectadas a 4 pines de PWM
//del arduino. 
// 
// 
//Creaded by Serred Nov/15/15

int duty_motor_izq = 0; //variables que guardan el estado  
int duty_motor_der = 0; //actual del duty cycle de ambos motores

//Pines PWM
int pin_motor_der_cw = 9;
int pin_motor_der_ccw = 6; 
int pin_motor_izq_cw = 5; 
int pin_motor_izq_ccw = 3;

void setup()
{
  //Inicializacion de serial para comunicacion por bluetooth.
  Serial.begin(9600);
  
  //Configurar pines de PWM como salidas
  pinMode(pin_motor_der_cw,OUTPUT);
  pinMode(pin_motor_der_ccw,OUTPUT);
  pinMode(pin_motor_izq_cw,OUTPUT);
  pinMode(pin_motor_izq_ccw,OUTPUT);  
}

void loop()
{
  
  //Si existe un nuevo dato en serial actualizar los valores
  if(Serial.available())
  {
    char c = Serial.read(); 
     
    //Si el comando es a actualizar valor de motor izquierdo 
    if(c == 'a')
    {
      //Actualizar valor solo cuando dentro de rango.
      if(duty_motor_izq <=255 && duty_motor_izq >= -255)
      {
         duty_motor_izq -=1; 
      }
    }else if(c == 'b') //Si el comando es b actualizar motor der
    {
      //Actualizar dentro de un rango. 
      if(duty_motor_der <=255 && duty_motor_der >=-255)
      {
         duty_motor_der -=1;
      }
    }
  } 
 
  //Actualizar potencia en motores
  if(duty_motor_der < 0)
  {
    //convertir en valor positivo
    int pwm_value = duty_motor_der * -1; 
    
    analogWrite(pin_motor_der_cw,0); 
    analogWrite(pin_motor_der_ccw,pwm_value);
  }else if(duty_motor_der >=0)
  {
    analogWrite(pin_motor_der_cw,duty_motor_der);
    analogWrite(pin_motor_der_ccw,0);
  }

  //Actualizar potencia en motores
  if(duty_motor_izq < 0)
  {
    //convertir en valor positivo
    int pwm_value = duty_motor_izq * -1; 
    
    analogWrite(pin_motor_izq_cw,0);
    analogWrite(pin_motor_izq_ccw,pwm_value);
  }else if(duty_motor_izq >=0)
  {
    analogWrite(pin_motor_izq_cw,duty_motor_der);
    analogWrite(pin_motor_izq_ccw,0);
  }  
   
}