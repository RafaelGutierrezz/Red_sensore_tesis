#include <Separador.h>


#include <teubico_XBeeSeries1.h>
#include <teubico_utils.h>
#include <SPI.h>
#include <Ethernet.h>
#include <Wire.h>//libreria I2C

XBeeSeries1 * myXBee;

// Variable para el pseudo-timer
long lastMessage = 0;

//Variables para la recepcion de los datos
int vec;
String vec1;
String vec2;
String vec3;
String vec4;
String dato;
String separador;
String sensor1;
String sensor2;
String sensor3;
String sensor4;
String ojala[2];
Separador s;
int j=0;
//Asignacion de ip y conexion a gateway (tener en cuenta que es mediante Ethernet
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress server(192,168,0,5);  // numeric IP for Google (no DNS)
IPAddress ip(192, 168, 0, 177);
IPAddress myDns(192, 168, 0, 1);
EthernetClient client;

void setup() {
  Serial.begin(9600);
 
  // Indicamos que debera de pegarse al Serial
  // Con la direccion 0x0002
  myXBee = new XBeeSeries1(Serial, 0x0002);
  myXBee->onDataReceived16(dataReceived);
  myXBee->init();

   //inicio de la conexion Ethernet
  Serial.println("Initialize Ethernet with DHCP:");
  if (Ethernet.begin(mac) == 0) {
    Serial.println("Failed to configure Ethernet using DHCP");
    // Check for Ethernet hardware present
    if (Ethernet.hardwareStatus() == EthernetNoHardware) {
      Serial.println("Ethernet shield was not found.  Sorry, can't run without hardware. :(");
      while (true) {
        delay(1); // do nothing, no point running without Ethernet hardware
      }
    }
    if (Ethernet.linkStatus() == LinkOFF) {
      Serial.println("Ethernet cable is not connected.");
    }
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip, myDns);
  } else {
    Serial.print("  DHCP assigned IP ");
    Serial.println(Ethernet.localIP());
  }
  // give the Ethernet shield a second to initialize:
  delay(1000);
  Serial.print("connecting to ");
  Serial.print(server);
  Serial.println("...");

}


void loop() {
  // Escuchar por nuevos datos
  myXBee->listen();
  
  // Enviar un mensaje cada segundo aproximadamente
  if(checkTimeout(lastMessage,1000)) {
    
    lastMessage = millis();
  }
}

// Procesa los datos recibidos
void dataReceived(uint16_t addr, uint8_t *data, uint16_t dataSize) {


    // if you get a connection, report back via serial:
  if (client.connect(server, 80)) {
    Serial.print("connected to ");
    Serial.println(client.remoteIP());
    //for para recibir solo 3 datos de la variable data que se obtiene del handler

       j=j+1;
      
      
      vec1=(data[0])-48;
      vec2=(data[1])-46;
      vec3=(data[2])-48;
      vec4=(data[3])-48;
     //Se concatenan las variables en un nuevo String
    dato=vec1+"."+vec3+vec4+",";
    
    Serial.println("el dato que llego es");
        Serial.println(dato);
      ojala[j-1]=dato;  
      if(j==3){
        j=0;
    String separar = ojala[0]+ojala[1]+ojala[2]+",";
    sensor1=s.separa(separar,',',0);
    sensor2=s.separa(separar,',',1);
    sensor3=s.separa(separar,',',2);
    sensor4=s.separa(separar,',',3);
    
   
    Serial.println("El elemento 1 es:"+sensor1);
    Serial.println("El elemento 2 es:"+sensor2);
    Serial.println("El elemento 3 es:"+sensor3);
    Serial.println("El elemento 4 es:"+sensor4);


   
      }
    // Make a HTTP request:
   
      client.print("GET /arduino/control/conexion_arduino.php?pre_php="); // Enviamos los datos por GET
   client.print(sensor1);
   client.print("&hum_php=");
   client.print(sensor2);
   client.print("&temp_php=");
   client.print(sensor3);
   client.print("&dist_php=");
   client.print("12");
   client.println(" HTTP/1.0");
   client.println("User-Agent: Arduino 1.0");
   client.println();
    Serial.println("Envio con exito (al archivo controller/index y models/herramienta)");
    Serial.print("Envio con exito");
    delay(1000);;
  } else {
    // if you didn't get a connection to the server:
    Serial.println("connection failed");
  }


     delay(200);
}
  
