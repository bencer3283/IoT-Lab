byte transmitRequest_HelloWorld[] = {0x7E, 0x00, 0x19, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
0x00, 0x00, 0xFF, 0xFE, 0x00, 0x00, 0x48, 0x65, 0x6C, 0x6C, 0x6F, 0x20, 0x57, 0x6F, 0x72, 0x6C, 0x64, 0xD5};

byte tempHead[] = {0x7E, 0x00, 0x1c, 0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00, 0x00, 0x74,0x65,0x6d,0x70,0x65,0x72,0x61,0x74,0x75,0x72,0x65,0x3a};

byte illuHead[] = {0x10, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 
0x00, 0x00, 0x00, 0xFF, 0xFE, 0x00, 0x00, 0x69,0x6c,0x6c,0x75,0x6d,0x69,0x6e,0x61,0x74,0x69,0x6f,0x6e,0x3a};

#include <XBee.h>
#include <OneWire.h>
#include<DallasTemperature.h>

#define ONE_WIRE_BUS 7
int photodiode = 6;

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);

XBee xbee = XBee();
XBeeAddress64 remoteAddress = XBeeAddress64(0x00000000, 0x00000000);

void setup() {
  // put your setup code here, to run once:
  DS18B20.begin();
  Serial.begin(9600);
  xbee.begin(Serial);
  while(!Serial){
    ;
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  temperature();
  illumination();
  Serial.write(transmitRequest_HelloWorld, sizeof(transmitRequest_HelloWorld));
  delay(500);
}

void temperature(){
  int temp = 99;
  DS18B20.requestTemperatures();
  temp = DS18B20.getTempCByIndex(0);
  byte tempbyte[3];
  String(temp).getBytes(tempbyte, 3);
  long sum = 0;
  for(int i = 3; i < sizeof(tempHead); i++){
    sum = sum + tempHead[i];
  }
  sum = sum + tempbyte[0] + tempbyte[1];
  Serial.write(tempHead, sizeof(tempHead));
  Serial.write(tempbyte, 2);
  Serial.write(0xFF - ( sum & 0xFF));
}

void illumination(){
  int illu = analogRead(photodiode);
  byte illubyte[String(illu).length()+1];
  String(illu).getBytes(illubyte, sizeof(illubyte));
  long sum = 0;
  for(int i = 0; i < sizeof(illuHead); i++){
    sum = sum + illuHead[i];
  }
  for(int i = 0; i < sizeof(illubyte)-1; i++){
    sum = sum + illubyte[i];
  }
  Serial.write(0x7e);
  Serial.write(0x00);
  Serial.write(String(illu).length()+sizeof(illuHead));
  Serial.write(illuHead, sizeof(illuHead));
  Serial.write(illubyte, sizeof(illubyte)-1);
  Serial.write(0xFF - ( sum & 0xFF));
}
