#include <IFTTTMaker.h>

#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>

//------- WiFi Settings -------
//char ssid[] = "Rushabh";       // your network SSID (name)
//char password[] = "a1b2c3d4e5";  // your network key

const char* ssid = "Rushabh";
const char* password = "a1b2c3d4e5";

#define IFTTT_BUTTON_PIN D2


// ------- IFTTT Maker config --------
#define KEY "f42Co9SZokK9gEjdu_YVOW0rWekQsLiJHrfoD-GkLyx"  // Get it from this page https://ifttt.com/services/maker/settings
#define EVENT_NAME "button_pressed" // Name of your event name, set when you are creating the applet


// SSL client needed for both libraries
WiFiClientSecure client;

IFTTTMaker ifttt(KEY, client);


String ipAddress = "";


volatile bool iftttButtonPressedFlag = false;

void setup() {

  Serial.begin(115200);

  // Initlaze the buttons
 
  pinMode(IFTTT_BUTTON_PIN, INPUT);

  // NOTE:
  // It is important to use interupts when making network calls in your sketch
  // if you just checked the status of te button in the loop you might
  // miss the button press.
 
  attachInterrupt(IFTTT_BUTTON_PIN, iftttButtonPressed, RISING);

  // Set WiFi to station mode and disconnect from an AP if it was Previously
  // connected
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);

  // Attempt to connect to Wifi network:
  Serial.print("Connecting Wifi: ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  IPAddress ip = WiFi.localIP();
  Serial.println(ip);

  ipAddress = ip.toString();

}



void iftttButtonPressed() {
  Serial.println("iftttButtonPressed");
  int button = digitalRead(IFTTT_BUTTON_PIN);
  if(button == HIGH)
  {
    iftttButtonPressedFlag = true;
  }
  return;
}

void triggerIftttEvent() {
  if(ifttt.triggerEvent(EVENT_NAME, ssid, ipAddress)){
    Serial.println("IFTTT Successfully sent");
  }
  iftttButtonPressedFlag = false;
}



void loop() {
  if ( iftttButtonPressedFlag ) {
    triggerIftttEvent();
  
  }

}
