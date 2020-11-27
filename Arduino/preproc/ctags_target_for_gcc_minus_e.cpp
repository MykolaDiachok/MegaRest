# 1 "c:\\Repos\\MegaRest\\MegaRest.ino"
# 2 "c:\\Repos\\MegaRest\\MegaRest.ino" 2
# 3 "c:\\Repos\\MegaRest\\MegaRest.ino" 2
# 4 "c:\\Repos\\MegaRest\\MegaRest.ino" 2
# 5 "c:\\Repos\\MegaRest\\MegaRest.ino" 2
# 6 "c:\\Repos\\MegaRest\\MegaRest.ino" 2
# 7 "c:\\Repos\\MegaRest\\MegaRest.ino" 2

// Enter a MAC address for your controller below.
byte mac[] = {0x90, 0xA2, 0xDA, 0x0E, 0xFE, 0x40};

// IP address in case DHCP fails
IPAddress ip(192, 168, 1, 61);

// Ethernet server
EthernetServer server(80);

// Create aREST instance
aREST rest = aREST("192.168.1.132", 3001);
# 31 "c:\\Repos\\MegaRest\\MegaRest.ino"
Light _lightHall(3 /* коридор свет*/, 0x0);
int lightHall(String command)
{
  return _lightHall.Function(command);
}



Light _LightBathroom(5 /* ванная свет*/, 0x0);
int lightBathroom(String command)
{
  return _LightBathroom.Function(command);
}

Light _LightbathroomFan(6 /* ванная вентилятор*/, 0x0);
int lightbathroomFan(String command)
{
  return _LightbathroomFan.Function(command);
}


Light _LightbathroomBrace(7 /* ванная бра*/, 0x0);
int lightbathroomBrace(String command)
{
  return _LightbathroomBrace.Function(command);
}



Light _LightWC(9 /* теалет свет*/, 0x0);
int lightWC(String command)
{
  return _LightWC.Function(command);
}


Light _LightWCFan(10 /* туалет выключатель*/, 0x0);
int lightWCFan(String command)
{
  return _LightWCFan.Function(command);
}
int iwcFan = 0;


Light _LightWCBrace(11 /* туалет бра*/, 0x0);
int lightWCBrace(String command)
{
  return _LightWCBrace.Function(command);
}





Light _LightKitchen(18, 0x0);
int lightKitchen(String command)
{
  return _LightKitchen.Function(command);
}


Light _LightKitchen1(19, 0x0);
int lightKitchen1(String command)
{
  return _LightKitchen1.Function(command);
}

Light _LightKitchen2(20, 0x0);
int lightKitchen2(String command)
{
  return _LightKitchen2.Function(command);
}

Light _LightKitchenDots(21, 0x0);
int lightKitchenDots(String command)
{
  return _LightKitchenDots.Function(command);
}



Light _LightBalcony(23, 0x0);
int lightBalcony(String command)
{
  return _LightBalcony.Function(command);
}




Light _LightLivingRoom(26, 0x1);
int lightLivingRoom(String command)
{
  return _LightLivingRoom.Function(command);
}

Light _LightLivingRoomBrace(27, 0x1);
int lightLivingRoomBrace(String command)
{
  return _LightLivingRoomBrace.Function(command);
}
# 140 "c:\\Repos\\MegaRest\\MegaRest.ino"
Light _LightBedRoom(34, 0x1);
int lightBedRoom(String command)
{
  return _LightBedRoom.Function(command);
}

Light _LightBedRoomBrace0(35, 0x1);
int lightBedRoomBrace0(String command)
{
  return _LightBedRoomBrace0.Function(command);
}

Light _LightBedRoomBrace1(36, 0x1);
int lightBedRoomBrace1(String command)
{
  return _LightBedRoomBrace1.Function(command);
}


//#define childRoomSW0_1 38

//#define childRoomSW1_1 40

Light _LightChildRoom(41, 0x1);
int lightChildRoom(String command)
{
  return _LightChildRoom.Function(command);
}

Light _LightChildRoomBrace(42, 0x1);
int lightChildRoomBrace(String command)
{
  return _LightChildRoomBrace.Function(command);
}

//#define inOutDoorSensor 12


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
    {0, "hallSW0", 14 /* выключатель в холе кнопка 0*/},
    {1, "hallSW1", 2 /* выключатель в холе кнопка 1*/},
    {2, "bathroomSW0", 4 /* ванная выключатель*/},
    {3, "wcSW0", 8 /* туалет выключатель*/},
    {4, "kitchenSW0_0", 15 /* кухня выключатель кнопка 0*/},
    {5, "kitchenSW0_1", 16 /* кухня выключатель кнопка 1*/},
    {6, "kitchenSW1_0", 17 /* кухня выключатель кнопка возле поверхности кнопка 0*/},
    {7, "balconySW0", 22},
    {8, "livingRoomSW0", 24},
    {9, "livingRoomSW1", 25},
    {10, "bedRoomSW0_0", 29 /*Mykola*/},
    {11, "bedRoomSW0_1", 28 /*Mykola*/},
    {12, "bedRoomSW1_0", 30},
    {13, "bedRoomSW1_1", 31},
    {14, "bedRoomSW2_0", 32},
    {15, "bedRoomSW2_1", 33},
    {16, "childRoomSW0_0", 37},
    {17, "childRoomSW1_0", 38},
    {18, "inOutDoorSensor", 38}};

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

  hButton.button_(sizeof((byte[]){14 /* выключатель в холе кнопка 0*/ /*0*/ , 2 /* выключатель в холе кнопка 1*/ /*1*/ , 4 /* ванная выключатель*/ /*2*/ , 8 /* туалет выключатель*/ /*3*/ , 15 /* кухня выключатель кнопка 0*/ /*4*/ , 16 /* кухня выключатель кнопка 1*/ /*5*/ , 17 /* кухня выключатель кнопка возле поверхности кнопка 0*/ /*6*/ , 22 /*7*/ , 24 /*8*/ , 25 /*9*/ , 29 /*Mykola*/ /*10*/ , 28 /*Mykola*/ /*11*/ , 30 /*12*/ , 31 /*13*/ , 32 /*14*/ , 33 /*15*/ , 37 /*16*/ /*, childRoomSW0_1  //17*/ , 38 /*17*/ /* , childRoomSW1_1  //19*/ , 38 /*18*/}),14 /* выключатель в холе кнопка 0*/ /*0*/ , 2 /* выключатель в холе кнопка 1*/ /*1*/ , 4 /* ванная выключатель*/ /*2*/ , 8 /* туалет выключатель*/ /*3*/ , 15 /* кухня выключатель кнопка 0*/ /*4*/ , 16 /* кухня выключатель кнопка 1*/ /*5*/ , 17 /* кухня выключатель кнопка возле поверхности кнопка 0*/ /*6*/ , 22 /*7*/ , 24 /*8*/ , 25 /*9*/ , 29 /*Mykola*/ /*10*/ , 28 /*Mykola*/ /*11*/ , 30 /*12*/ , 31 /*13*/ , 32 /*14*/ , 33 /*15*/ , 37 /*16*/ /*, childRoomSW0_1  //17*/ , 38 /*17*/ /* , childRoomSW1_1  //19*/ , 38 /*18*/)
# 306 "c:\\Repos\\MegaRest\\MegaRest.ino"
   ; // arduino pins connected to button

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
  wdt_enable(
# 325 "c:\\Repos\\MegaRest\\MegaRest.ino" 3
            8
# 325 "c:\\Repos\\MegaRest\\MegaRest.ino"
                   );

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
  
# 390 "c:\\Repos\\MegaRest\\MegaRest.ino" 3
 __asm__ __volatile__ ("wdr")
# 390 "c:\\Repos\\MegaRest\\MegaRest.ino"
            ;
}
