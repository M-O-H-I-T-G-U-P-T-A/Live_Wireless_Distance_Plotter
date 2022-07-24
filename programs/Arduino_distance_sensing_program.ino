#include <ESP8266WiFi.h>
#include<ESP8266WebServer.h>
String ssid="ESP8266 Server";// set your hotspot name to be shown to the devices 
String pass="";//set your hotspot password
static float c=0;
#define echoPin 14 //I am using D5 as echo pin
#define trigPin 12 //I am using D6 as trig pin
long duration; 
int distance;
ESP8266WebServer Server(80);

// Set your Static IP address
IPAddress local_IP(192, 168, 137, 20);
// Set your Gateway IP address
IPAddress gateway(192, 168, 1, 1);
IPAddress subnet(255, 255, 0, 0);
  


void setup()
{
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(local_IP,gateway,subnet);
  WiFi.softAP(ssid,pass);
  WiFi.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(16,OUTPUT);
  while(!WiFi.softAPgetStationNum())
  {
    digitalWrite(2,1);
    digitalWrite(16,0);
    delay(750);
    digitalWrite(16,1);
    delay(750);
  }
  Serial.println("Got IP:");
  Serial.println(WiFi.softAPIP());
  Server.begin();
  digitalWrite(16,1);
  digitalWrite(2,0);
  Server.on("/", hc);
}
String html(float c){
  String p=String(c);
  String ptr = "<html><HEAD>"+p+"</HEAD></html>";
  return ptr;
}

float dis()
{
  digitalWrite(trigPin, 0);
  delayMicroseconds(50);
  // Sets the trigPin 1 (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, 1);
  delayMicroseconds(10);
  digitalWrite(trigPin, 0);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, 1);
  // Calculating the distance
  distance = duration * 0.01715;
  if(distance>250)
  {
    delay(50);
    return dis();
  }
  return(distance);
}
void hc()
{
  c=dis();
  Serial.println(html(c));
  Server.send(200,"text/html",html(c));
}
void loop()
{
  Server.handleClient();
  delay(1);
  while(!WiFi.softAPgetStationNum())
  {
    digitalWrite(2,1);
    digitalWrite(16,0);
    delay(750);
    digitalWrite(16,1);
    delay(750);
  }
  digitalWrite(2,0);
}
