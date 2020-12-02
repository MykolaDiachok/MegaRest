#include <SPI.h>
#include <Ethernet.h>
#include <avr/wdt.h>
#include "aREST.h"
#include "Button.h"

// Enter a MAC address for your controller below.
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0xFE, 0x40};

// IP address in case DHCP fails
IPAddress ip(192, 168, 1, 61);

// Ethernet server
EthernetServer server(80);

// Create aREST instance
aREST rest = aREST("192.168.1.132", 3001);

#define hallSW0 14 // выключатель в холе кнопка 0

#define hallSW1 2 // выключатель в холе кнопка 1

#define hallLight 3 // коридор свет

#define bathroomSW0 4   // ванная выключатель
#define bathroomLight 5 // ванная свет
#define bathroomFan 6   // ванная вентилятор
#define bathroomBrace 7 // ванная бра

#define wcSW0 8    // туалет выключатель
#define wcLight 44  // теалет свет
#define wcFan 43   // туалет вентилятор
#define wcBrace 45 // туалет бра

#define kitchenSW0_0 15 // кухня выключатель кнопка 0
#define kitchenSW0_1 16 // кухня выключатель кнопка 1
#define kitchenSW1_0 17 // кухня выключатель кнопка возле поверхности кнопка 0
#define kitchenLight 18
#define kitchenLight1 19
#define kitchenLight2 20
#define kitchenLightDots 21

#define balconySW0 22
#define balconyLight 23

#define livingRoomSW0 24
#define livingRoomSW1 25
#define livingRoomLight 26
#define livingRoomBrace 27

#define bedRoomSW0_0 29 //Mykola
#define bedRoomSW0_1 28 //Mykola
#define bedRoomSW1_0 30
#define bedRoomSW1_1 31
#define bedRoomSW2_0 32
#define bedRoomSW2_1 33
#define bedRoomLight 34
#define bedRoomBrace0 35
#define bedRoomBrace1 36

#define childRoomSW0_0 37
//#define childRoomSW0_1 38
#define childRoomSW1_0 38
//#define childRoomSW1_1 40
#define childRoomLight 41
#define childRoomBrace 42

//#define inOutDoorSensor 12
#define inOutDoorSensor 38

unsigned long HallTimeOff = 0;

void initLights()
{
  pinMode(hallLight, OUTPUT);
  digitalWrite(hallLight, HIGH);
  pinMode(bathroomLight, OUTPUT);
  digitalWrite(bathroomLight, HIGH);
  pinMode(bathroomFan, OUTPUT);
  digitalWrite(bathroomFan, HIGH);
  pinMode(bathroomBrace, OUTPUT);
  digitalWrite(bathroomBrace, HIGH);
  pinMode(wcLight, OUTPUT);
  digitalWrite(wcLight, HIGH);
  pinMode(wcFan, OUTPUT);
  digitalWrite(wcFan, HIGH);
  pinMode(wcBrace, OUTPUT);
  digitalWrite(wcBrace, HIGH);
  pinMode(kitchenLight, OUTPUT);
  digitalWrite(kitchenLight, HIGH);
  pinMode(kitchenLight1, OUTPUT);
  digitalWrite(kitchenLight1, HIGH);
  pinMode(kitchenLight2, OUTPUT);
  digitalWrite(kitchenLight2, HIGH);
  pinMode(kitchenLightDots, OUTPUT);
  digitalWrite(kitchenLightDots, HIGH);
  pinMode(balconyLight, OUTPUT);
  digitalWrite(balconyLight, HIGH);
  pinMode(livingRoomLight, OUTPUT);
  pinMode(livingRoomBrace, OUTPUT);
  pinMode(bedRoomLight, OUTPUT);
  pinMode(bedRoomBrace0, OUTPUT);
  pinMode(bedRoomBrace1, OUTPUT);
  pinMode(childRoomLight, OUTPUT);
  pinMode(childRoomBrace, OUTPUT);
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
    {4, "kitchenSW0-0", kitchenSW0_0},
    {5, "kitchenSW0-1", kitchenSW0_1},
    {6, "kitchenSW1-0", kitchenSW1_0},
    {7, "balconySW0", balconySW0},
    {8, "livingRoomSW0", livingRoomSW0},
    {9, "livingRoomSW1", livingRoomSW1},
    {10, "bedRoomSW0-0", bedRoomSW0_0},
    {11, "bedRoomSW0-1", bedRoomSW0_1},
    {12, "bedRoomSW1-0", bedRoomSW1_0},
    {13, "bedRoomSW1-1", bedRoomSW1_1},
    {14, "bedRoomSW2-0", bedRoomSW2_0},
    {15, "bedRoomSW2-1", bedRoomSW2_1},
    {16, "childRoomSW0-0", childRoomSW0_0},
    {17, "childRoomSW1-0", childRoomSW1_0},
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
  //hButton.pullUp();
  hButton.pullDn(); // - подтяжка пинов кнопок к GND
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

void publishhttp(int id, int eventName)
{
  
  String PATH_NAME = "/button-" + nameButtons[id].name;

  String queryString = "?event=click";
  if (eventName == 1)
    queryString = "?event=double-click";
  else if (eventName == 2)
    queryString = "?event=hold";
  if (httpclient.connect("192.168.1.132", 3001))
  {
    httpclient.println("GET " + PATH_NAME + queryString + " HTTP/1.1");
    Serial.println("SEND GET " + PATH_NAME + queryString + " HTTP/1.1");
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
#pragma region OutDoor //TODO доделать
  if (hButton.event_click_Dn(18) == 1)
  {
    publishhttp(18, 0);
  }
  if (hButton.event_click_Up(18) == 1)
  {
    publishhttp(18, 2);
  }
#pragma endregion

#pragma region hall
#pragma region hallSW0
  if (hButton.event_click_Dn(0) == 1)
  {
    publishhttp(0, 0);
  }
  if (hButton.event_click_Db(0) == 1)
  {
    publishhttp(0, 1);
  }
  if (hButton.event_press_long(0) == 1)
  {
    publishhttp(0, 2);
  }
#pragma endregion

#pragma region hallSW1
  if (hButton.event_click_Dn(1) == 1)
  {
    publishhttp(1, 0);
  }
  if (hButton.event_click_Db(1) == 1)
  {
    publishhttp(1, 1);
  }
  if (hButton.event_press_long(1) == 1)
  {
    publishhttp(1, 2);
  }
#pragma endregion
#pragma endregion

#pragma region bathroom
  if (hButton.event_click_Dn(2) == 1)
  {
    publishhttp(2, 0);
  }
  if (hButton.event_click_Db(2) == 1) //only lights
  {
    publishhttp(2, 1);
  }
  if (hButton.event_press_long(2) == 1) //only fan
  {
    publishhttp(2, 2);
  }
#pragma endregion

#pragma region WC //wcSW0
  if (hButton.event_click_Dn(3) == 1)
  {
    publishhttp(3, 0);
  }
  if (hButton.event_click_Db(3) == 1)
  {
    publishhttp(3, 1);
  }  
  if (hButton.event_press_long(3) == 1)
  {
    publishhttp(3, 2);
  }
#pragma endregion

#pragma region kitchen
#pragma region kitchenSW0_0
  if (hButton.event_click_Dn(4) == 1)
  {
    publishhttp(4, 0);
  }
  if (hButton.event_click_Db(4) == 1)
  {
    publishhttp(4, 1);
  }
  
  if (hButton.event_press_long(4) == 1)
  {
    publishhttp(4, 2);
  }
#pragma endregion

#pragma region kitchenSW0_1
  if (hButton.event_click_Dn(5) == 1)
  {
    publishhttp(5, 0);
  }
  if (hButton.event_click_Db(5) == 1)
  {
    publishhttp(5, 1);
  }  
  if (hButton.event_press_long(5) == 1)
  {
    publishhttp(5, 2);
  }
#pragma endregion

#pragma region kitchenSW1_0
  if (hButton.event_click_Dn(6) == 1)
  {
    publishhttp(6, 0);
  }
  if (hButton.event_click_Db(6) == 1)
  {
    publishhttp(6, 1);
  }  
  if (hButton.event_press_long(6) == 1)
  {
    publishhttp(6, 2);
  }
#pragma endregion
#pragma endregion

#pragma region balconySW0
  if (hButton.event_click_Dn(7) == 1)
  {
    publishhttp(7, 0);
  }
  if (hButton.event_click_Db(7) == 1)
  {
    publishhttp(7, 1);
  }  
  if (hButton.event_press_long(7) == 1)
  {
    publishhttp(7, 2);
  }
#pragma endregion

#pragma region livingRoom
#pragma region livingRoomSW0
  if (hButton.event_click_Dn(8) == 1)
  {
    publishhttp(8, 0);
  }
  if (hButton.event_click_Db(8) == 1)
  {
    publishhttp(8, 1);
  }  
  if (hButton.event_press_long(8) == 1)
  {
    publishhttp(8, 2);
  }
#pragma endregion

#pragma region livingRoomSW1
  if (hButton.event_click_Dn(9) == 1)
  {
    publishhttp(9, 0);
  }
  if (hButton.event_click_Db(9) == 1)
  {
    publishhttp(9, 1);
  }  
  if (hButton.event_press_long(9) == 1)
  {
    publishhttp(9, 2);
  }
#pragma endregion

#pragma endregion

#pragma region bedRoom
#pragma region bedRoomSW0_0
  if (hButton.event_click_Dn(10) == 1)
  {
    publishhttp(10, 0);
  }
  if (hButton.event_click_Db(10) == 1)
  {
    publishhttp(10, 1);
  }  
  if (hButton.event_press_long(10) == 1)
  {
    publishhttp(10, 2);
  }
#pragma endregion

#pragma region bedRoomSW0_1
  if (hButton.event_click_Dn(11) == 1)
  {
    publishhttp(11, 0);
  }
  if (hButton.event_click_Db(11) == 1)
  {
    publishhttp(11, 1);
  }  
  if (hButton.event_press_long(11) == 1)
  {
    publishhttp(11, 2);
  }
#pragma endregion

#pragma region bedRoomSW1_0
  if (hButton.event_click_Dn(12) == 1)
  {
    publishhttp(12, 0);
  }
  if (hButton.event_click_Db(12) == 1)
  {
    publishhttp(12, 1);
  }  
  if (hButton.event_press_long(12) == 1)
  {
    publishhttp(12, 2);
  }
#pragma endregion
#pragma region bedRoomSW1_1
  if (hButton.event_click_Dn(13) == 1)
  {
    publishhttp(13, 0);
  }
  if (hButton.event_click_Db(13) == 1)
  {
    publishhttp(13, 1);
  }  
  if (hButton.event_press_long(13) == 1)
  {
    publishhttp(13, 2);
  }
#pragma endregion
#pragma region bedRoomSW2_1
  if (hButton.event_click_Dn(14) == 1)
  {
    publishhttp(14, 0);
  }
  if (hButton.event_click_Db(14) == 1)
  {
    publishhttp(14, 1);
  }  
  if (hButton.event_press_long(14) == 1)
  {
    publishhttp(14, 2);
  }
#pragma endregion
#pragma region bedRoomSW2_2
  if (hButton.event_click_Dn(15) == 1)
  {
    publishhttp(15, 0);
  }
  if (hButton.event_click_Db(15) == 1)
  {
    publishhttp(15, 1);
  }  
  if (hButton.event_press_long(15) == 1)
  {
    publishhttp(15, 2);
  }
#pragma endregion

#pragma endregion

#pragma region childRoom
#pragma region childRoomSW0_0
  if (hButton.event_click_Dn(16) == 1)
  {
    publishhttp(16, 0);
  }
  if (hButton.event_click_Db(16) == 1)
  {
    publishhttp(16, 1);
  }  
  if (hButton.event_press_long(16) == 1)
  {
    publishhttp(16, 2);
  }
#pragma endregion

#pragma region childRoomSW1_0
  if (hButton.event_click_Dn(17) == 1)
  {
    publishhttp(17, 0);
  }
  if (hButton.event_click_Db(17) == 1)
  {
    publishhttp(17, 1);
  }  
  if (hButton.event_press_long(17) == 1)
  {
    publishhttp(17, 2);
  }
#pragma endregion
#pragma endregion

  EthernetClient client = server.available();
  rest.handle(client);
  wdt_reset();
}
