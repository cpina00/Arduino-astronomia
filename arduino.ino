#include <OneWire.h>
#include <DallasTemperature.h>

// Pin donde se conecta el bus 1-Wire
const int pinDatosDQ = 9;

//Pin donde se conectan los leds
int pinLed1 = 2;
int pinLed2 = 3;
int pinLed3 = 4;
// Pin analógico de entrada para el LDR
int pinLDR = 0;

// Variable donde se almacena el valor del LDR
int valorLDR = 0; 


// Instancia a las clases OneWire y DallasTemperature
OneWire oneWireObjeto(pinDatosDQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);
 
void setup() {
    // Configuramos como salidas los pines donde se conectan los led
    pinMode(pinLed1, OUTPUT);
    pinMode(pinLed2, OUTPUT);
    pinMode(pinLed3, OUTPUT);
  
  
    // Iniciamos la comunicación serie
    Serial.begin(9600);
    // Iniciamos el bus 1-Wire
    sensorDS18B20.begin(); 
}
 
void loop() {
    // Mandamos comandos para toma de temperatura a los sensores
    Serial.println("Mandando comandos a los sensores");
    sensorDS18B20.requestTemperatures();
 
    // Leemos y mostramos los datos de los sensores DS18B20
    Serial.print("Temperatura sensor : ");
    Serial.print(sensorDS18B20.getTempCByIndex(0));
    Serial.println(" C");
    delay(1000); 
    
    
    // Apagar todos los leds siempre que se inicia el ciclo
  digitalWrite(pinLed1, LOW);
  digitalWrite(pinLed2, LOW);
  digitalWrite(pinLed3, LOW);

  // Guardamos el valor leído del ADC en una variable
  // El valor leído por el ADC (voltaje) aumenta de manera directamente proporcional con respecto a la luz percibida por el LDR
  valorLDR= analogRead(pinLDR);
 
  // Devolver el valor leído a nuestro monitor serial en el IDE de Arduino
  Serial.print("Luminosidad: ");
  Serial.println(valorLDR);

  // Encender los leds apropiados de acuerdo al valor de ADC
  if(valorLDR > 590)
  {
    digitalWrite(pinLed1, HIGH);
  }
  if(valorLDR >650)
  {
    digitalWrite(pinLed2, HIGH);
  }
  if(valorLDR > 768)
  {
    digitalWrite(pinLed3, HIGH);
  }
  // Esperar unos milisegundos antes de actualizar
  delay(200);
    
}
