#include <WiFi.h>
#include <HCSR04.h>

#include "FirebaseESP32.h"

#define FIREBASE_HOST "https://iot8-45b64.firebaseio.com/"
#define FIREBASE_AUTH "Eh0Gw0H8VbDPH8oJAPqiSN2Fc5pSjSQOoZ71Y7a4"
#define WIFI_SSID "Kontrakan Wacana"
#define WIFI_PASSWORD "tanyadia"

UltraSonicDistanceSensor distanceSensor(19,18);//initialisation class HCSR04 (trig pin , echo pin)

#define led1 32
#define led2 33
#define ldr 34

FirebaseData firebaseData;

String path = "/Node1";
int oldDistance;
int newDistance;

int oldAdcLdr;
int newAdcLdr;

int stateMotion = LOW;             // default tidak ada gerakan
int valMotion = 0;                 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  pinMode(led1,OUTPUT);
  pinMode(led2,OUTPUT);
  pinMode(ldr,INPUT);
    
  initWifi();

  oldDistance = distanceSensor.measureDistanceCm();
  oldAdcLdr = analogRead(ldr);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(500);

  //ambil nilai dari sensor ultarsonic dan kirim ke firebase
  newDistance = distanceSensor.measureDistanceCm();
  Serial.println(newDistance);
  if(newDistance != oldDistance){
    Firebase.setInt(firebaseData, path + "/distance", newDistance);
    oldDistance = newDistance; 
  }

  //ambil nilai dari sensor LDR dan kirim ke firebase
  newAdcLdr = analogRead(ldr);
  Serial.println(newAdcLdr);
  if(newAdcLdr != oldAdcLdr){
    Firebase.setDouble(firebaseData, path + "/ldr", newAdcLdr);
    oldAdcLdr = newAdcLdr;
  }
  
  //get value /Node1/led1
  if(Firebase.getInt(firebaseData, path + "/led1")){
    /*Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.print("VALUE: ");
    Serial.println(firebaseData.intData());
    */
    if(firebaseData.intData() == 0)
      digitalWrite(led1,0);
    else
      digitalWrite(led1,1);    
  }
 

  //get value /Node1/led2
  if(Firebase.getInt(firebaseData, path + "/led2")){
    /*Serial.println("PASSED");
    Serial.println("PATH: " + firebaseData.dataPath());
    Serial.println("TYPE: " + firebaseData.dataType());
    Serial.println("ETag: " + firebaseData.ETag());
    Serial.print("VALUE: ");
    Serial.println(firebaseData.intData());
    */
    if(firebaseData.intData() == 0)
      digitalWrite(led2,0);
    else
      digitalWrite(led2,1);
  }
}

void initWifi(){
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  Firebase.reconnectWiFi(true);
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
  //Set database read timeout to 1 minute (max 15 minutes)
  Firebase.setReadTimeout(firebaseData, 1000 * 60);
  //tiny, small, medium, large and unlimited.
  //Size and its write timeout e.g. tiny (1s), small (10s), medium (30s) and large (60s).
  Firebase.setwriteSizeLimit(firebaseData, "tiny");
}
