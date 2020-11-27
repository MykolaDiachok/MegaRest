#include <Arduino.h>
#line 1 "c:\\Repos\\MegaRest\\MegaRest.ino"
#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>
#include "aREST.h"
#include "Light.h"
#include "Button.h"

// Enter a MAC address for your controller below.
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0xFE, 0x40};

// IP address in case DHCP fails
IPAddress ip(192, 168, 1, 61);

// Ethernet server
EthernetServer server(80);

// Create aREST instance
aREST rest = aREST("192.168.1.132", 3001);

#define ON LOW
#define OFF HIGH

#define ON2 HIGH
#define OFF2 LOW

#define hallSW0 14 // выключатель в холе кнопка 0

#define hallSW1 2 // выключатель в холе кнопка 1

#define hallLight 3 // коридор свет
Light _lightHall(hallLight, ON);
#line 32 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightHall(String command);
#line 40 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightBathroom(String command);
#line 46 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightbathroomFan(String command);
#line 53 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightbathroomBrace(String command);
#line 61 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightWC(String command);
#line 68 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightWCFan(String command);
#line 76 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightWCBrace(String command);
#line 86 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightKitchen(String command);
#line 93 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightKitchen1(String command);
#line 99 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightKitchen2(String command);
#line 105 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightKitchenDots(String command);
#line 113 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightBalcony(String command);
#line 122 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightLivingRoom(String command);
#line 128 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightLivingRoomBrace(String command);
#line 141 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightBedRoom(String command);
#line 147 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightBedRoomBrace0(String command);
#line 153 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightBedRoomBrace1(String command);
#line 164 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightChildRoom(String command);
#line 170 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightChildRoomBrace(String command);
#line 180 "c:\\Repos\\MegaRest\\MegaRest.ino"
void initLights();
#line 242 "c:\\Repos\\MegaRest\\MegaRest.ino"
void initButtons();
#line 253 "c:\\Repos\\MegaRest\\MegaRest.ino"
void setup();
#line 331 "c:\\Repos\\MegaRest\\MegaRest.ino"
template <typename V>void publishhttp(const String &buttonName, V eventName);
#line 348 "c:\\Repos\\MegaRest\\MegaRest.ino"
void loop();
#line 32 "c:\\Repos\\MegaRest\\MegaRest.ino"
int lightHall(String command)
{
  return _lightHall.Function(command);
}

#define bathroomSW0 4   // ванная выключатель
#define bathroomLight 5 // ванная свет
Light _LightBathroom(bathroomLight, ON);
int lightBathroom(String command)
{
  return _LightBathroom.Function(command);
}
#define bathroomFan 6 // ванная вентилятор
Light _LightbathroomFan(bathroomFan, ON);
int lightbathroomFan(String command)
{
  return _LightbathroomFan.Function(command);
}

#define bathroomBrace 7 // ванная бра
Light _LightbathroomBrace(bathroomBrace, ON);
int lightbathroomBrace(String command)
{
  return _LightbathroomBrace.Function(command);
}

#define wcSW0 8   // туалет выключатель
#define wcLight 9 // теалет свет
Light _LightWC(wcLight, ON);
int lightWC(String command)
{
  return _LightWC.Function(command);
}

#define wcFan 10 // туалет выключатель
Light _LightWCFan(wcFan, ON);
int lightWCFan(String command)
{
  return _LightWCFan.Function(command);
}
int iwcFan = 0;

#define wcBrace 11 // туалет бра
Light _LightWCBrace(wcBrace, ON);
int lightWCBrace(String command)
{
  return _LightWCBrace.Function(command);
}

#define kitchenSW0_0 15 // кухня выключатель кнопка 0
#define kitchenSW0_1 16 // кухня выключатель кнопка 1
#define kitchenSW1_0 17 // кухня выключатель кнопка возле поверхности кнопка 0
#define kitchenLight 18
Light _LightKitchen(kitchenLight, ON);
int lightKitchen(String command)
{
  return _LightKitchen.Function(command);
}

#define kitchenLight1 19
Light _LightKitchen1(kitchenLight1, ON);
int lightKitchen1(String command)
{
  return _LightKitchen1.Function(command);
}
#define kitchenLight2 20
Light _LightKitchen2(kitchenLight2, ON);
int lightKitchen2(String command)
{
  return _LightKitchen2.Function(command);
}
#define kitchenLightDots 21
Light _LightKitchenDots(kitchenLightDots, ON);
int lightKitchenDots(String command)
{
  return _LightKitchenDots.Function(command);
}

#define balconySW0 22
#define balconyLight 23
Light _LightBalcony(balconyLight, ON);
int lightBalcony(String command)
{
  return _LightBalcony.Function(command);
}

#define livingRoomSW0 24
#define livingRoomSW1 25
#define livingRoomLight 26
Light _LightLivingRoom(livingRoomLight, ON2);
int lightLivingRoom(String command)
{
  return _LightLivingRoom.Function(command);
}
#define livingRoomBrace 27
Light _LightLivingRoomBrace(livingRoomBrace, ON2);
int lightLivingRoomBrace(String command)
{
  return _LightLivingRoomBrace.Function(command);
}

#define bedRoomSW0_0 29 //Mykola
#define bedRoomSW0_1 28 //Mykola
#define bedRoomSW1_0 30
#define bedRoomSW1_1 31
#define bedRoomSW2_0 32
#define bedRoomSW2_1 33
#define bedRoomLight 34
Light _LightBedRoom(bedRoomLight, ON2);
int lightBedRoom(String command)
{
  return _LightBedRoom.Function(command);
}
#define bedRoomBrace0 35
Light _LightBedRoomBrace0(bedRoomBrace0, ON2);
int lightBedRoomBrace0(String command)
{
  return _LightBedRoomBrace0.Function(command);
}
#define bedRoomBrace1 36
Light _LightBedRoomBrace1(bedRoomBrace1, ON2);
int lightBedRoomBrace1(String command)
{
  return _LightBedRoomBrace1.Function(command);
}

#define childRoomSW0_0 37
//#define childRoomSW0_1 38
#define childRoomSW1_0 38
//#define childRoomSW1_1 40
#define childRoomLight 41
Light _LightChildRoom(childRoomLight, ON2);
int lightChildRoom(String command)
{
  return _LightChildRoom.Function(command);
}
#define childRoomBrace 42
Light _LightChildRoomBrace(childRoomBrace, ON2);
int lightChildRoomBrace(String command)
{
  return _LightChildRoomBrace.Function(command);
}

//#define inOutDoorSensor 12
#define inOutDoorSensor 38

unsigned long HallTimeOff = 0;

void initLights()
{
  rest.function("hall", lightHall);

  rest.function("bathroom", lightBathroom);
  rest.function("bathroomfan", lightbathroomFan);
  rest.function("bathroombrace", lightbathroomBrace);

  rest.function("wc", lightWC);
  rest.function("wcfan", lightWCFan);
  rest.function("wcbrace", lightWCBrace);

  rest.function("kitchen", lightKitchen);
  rest.function("kitchen1", lightKitchen1);
  rest.function("kitchen2", lightKitchen2);
  rest.function("kitchendots", lightKitchenDots);

  rest.function("balcony", lightBalcony);

  rest.function("livingroom", lightLivingRoom);
  rest.function("livingroombrace", lightLivingRoomBrace);

  rest.function("bedroom", lightBedRoom);
  rest.function("bedroombrace0", lightBedRoomBrace0);
  rest.function("bedroombrace1", lightBedRoomBrace1);

  rest.function("childroom", lightChildRoom);
  rest.function("childroombrace", lightChildRoomBrace);
}

Button hButton;

struct myButtom
{
  byte order;
  String name;
  byte pin;
};

myButtom nameButtons[] = {
    {0, "hallSW0", hallSW0},
    {1, "hallSW1", hallSW1},
    {2, "bathroomSW0", bathroomSW0},
    {3, "wcSW0", wcSW0},
    {4, "kitchenSW0_0", kitchenSW0_0},
    {5, "kitchenSW0_1", kitchenSW0_1},
    {6, "kitchenSW1_0", kitchenSW1_0},
    {7, "balconySW0", balconySW0},
    {8, "livingRoomSW0", livingRoomSW0},
    {9, "livingRoomSW1", livingRoomSW1},
    {10, "bedRoomSW0_0", bedRoomSW0_0},
    {11, "bedRoomSW0_1", bedRoomSW0_1},
    {12, "bedRoomSW1_0", bedRoomSW1_0},
    {13, "bedRoomSW1_1", bedRoomSW1_1},
    {14, "bedRoomSW2_0", bedRoomSW2_0},
    {15, "bedRoomSW2_1", bedRoomSW2_1},
    {16, "childRoomSW0_0", childRoomSW0_0},
    {17, "childRoomSW1_0", childRoomSW1_0},
    {18, "inOutDoorSensor", inOutDoorSensor}};

int buttonCount = sizeof(nameButtons) / sizeof(myButtom);

void initButtons()
{
  //  Serial.println("buttons:" + String(buttonCount));
  //  byte regbuttons[buttonCount];
  //  for (size_t i = 0; i < buttonCount; i++)
  //  {
  //    regbuttons[i] = nameButtons[i].pin;
  //    Serial.println("" + String(nameButtons[i].order) + " " + nameButtons[i].name + ":" + String(nameButtons[i].pin));
  //  }
}

void setup()
{
  // Start Serial
  Serial.begin(115200);
  hButton.NO(); // N.O. Normal Open
  // hButton.NC(); // N.C. Normal Closed
  hButton.pullUp();
  //hButton.pullDn(); // - подтяжка пинов кнопок к GND
  hButton.duration_bounce(50);
  hButton.duration_click_Db(250);
  hButton.duration_inactivity_Up(5000);
  hButton.duration_inactivity_Dn(1000);
  hButton.duration_press(500);
  
  hButton.button(hallSW0 //0
                 ,
                 hallSW1 //1
                 ,
                 bathroomSW0 //2
                 ,
                 wcSW0 //3
                 ,
                 kitchenSW0_0 //4
                 ,
                 kitchenSW0_1 //5
                 ,
                 kitchenSW1_0 //6
                 ,
                 balconySW0 //7
                 ,
                 livingRoomSW0 //8
                 ,
                 livingRoomSW1 //9
                 ,
                 bedRoomSW0_0 //10
                 ,
                 bedRoomSW0_1 //11
                 ,
                 bedRoomSW1_0 //12
                 ,
                 bedRoomSW1_1 //13
                 ,
                 bedRoomSW2_0 //14
                 ,
                 bedRoomSW2_1 //15
                 ,
                 childRoomSW0_0 //16
                 //, childRoomSW0_1  //17
                 ,
                 childRoomSW1_0 //17
                 // , childRoomSW1_1  //19
                 ,
                 inOutDoorSensor //18
  );                             // arduino pins connected to button

  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("001");
  rest.set_name("master_home");

  // Start the Ethernet connection and the server
  if (Ethernet.begin(mac) == 0)
  {
    Serial.println("Failed to configure Ethernet using DHCP");
    // no point in carrying on, so do nothing forevermore:
    // try to congifure using IP address instead of DHCP:
    Ethernet.begin(mac, ip);
  }
  server.begin();
  Serial.print("server is at ");
  Serial.println(Ethernet.localIP());

  // Start watchdog
  wdt_enable(WDTO_4S);

  initLights();
  initButtons();
}
EthernetClient httpclient;

template <typename V>
void publishhttp(const String &buttonName, V eventName)
{
  String PATH_NAME = "/button-" + buttonName;
  String queryString = "?event=" + String(eventName);
  if (httpclient.connect("192.168.1.132", 3001))
  {
    httpclient.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    Serial.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    httpclient.println("Host: 192.168.1.132");
    httpclient.println("Connection: close");
    httpclient.println(); // end HTTP request header
    httpclient.stop();
  }
}

void loop()
{
  hButton.read();
  //

  if (hButton.event_click_Dn(0) == 1)
  {
    Serial.println(String("hallSW0") + "event_click_Dn");
  }
  if (hButton.event_click_Db(0) == 1)
  {
    Serial.println(String("hallSW0") + "event_click_Db");
  }
  if (hButton.event_press_short(0) == 1)
  {
    Serial.println(String("hallSW0") + "event_press_short");
  }
  if (hButton.event_press_long(0) == 1)
  {
    Serial.println(String("hallSW0") + "event_press_long");
  }

  if (hButton.event_click_Dn(1) == 1)
  {
    Serial.println(String("hallSW0") + "event_click_Dn");
  }
  if (hButton.event_click_Db(1) == 1)
  {
    Serial.println(String("hallSW0") + "event_click_Db");
  }
  if (hButton.event_press_short(1) == 1)
  {
    Serial.println(String("hallSW0") + "event_press_short");
  }
  if (hButton.event_press_long(1) == 1)
  {
    Serial.println(String("hallSW0") + "event_press_long");
  }

  
  EthernetClient client = server.available();
  rest.handle(client);
  wdt_reset();
}

