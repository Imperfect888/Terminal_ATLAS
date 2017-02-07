//**************************************PROJECT PDA ATLAS**************************************
#include <SPI.h> //подключаем библиотеку
#include <RF24.h> //подключаем библиотеку
#include <TFT_HX8357.h> //подключаем библиотеку
#include <User_Setup.h> //подключаем библиотеку
#include <Time.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <EEPROM.h>

//***************************************ЭКРАН****************************************
TFT_HX8357 tft = TFT_HX8357(); //конструктор пинов
//***************************************РАДИО****************************************
RF24 radio(9, 53); //9 и 53 диджитал пины
const uint32_t pipe = 123456789;
//**************************************ДЖОЙСТИК**************************************
unsigned short int xPin = A1;
unsigned short int yPin = A0;
unsigned short int clickPin = A2;

unsigned short int positionX = 0;
unsigned short int positionY = 0;
unsigned short int clickState = 0;

short int x = 0;
short int y = 0;
short int c = 0;
//****************************************ЧАСЫ*****************************************
tmElements_t tm;

bool parse=false;
bool config=false;
//**************************************СТРУКТУРЫ**************************************

/*struct reducingDrugs
{
  unsigned short int _1 = 1000;
  unsigned short int _2 = 1000;
  unsigned short int _3 = 1000;
  unsigned short int _4 = 1000;
  unsigned short int _5 = 1000;
  unsigned short int _6 = 1000;
};

struct protectingDrugs
{
  unsigned short int _1 = 1000;
  unsigned short int _2 = 1000;
  unsigned short int _3 = 1000;
  unsigned short int _4 = 1000;
};

struct repair
{
  unsigned short int _1 = 1000;
  unsigned short int _2 = 1000;
  unsigned short int _3 = 1000;
  unsigned short int _4 = 1000;
};

struct foodAndDrinks
{
  unsigned short int _1 = 1000;
  unsigned short int _2 = 1000;
  unsigned short int _3 = 1000;
  unsigned short int _4 = 1000;
  unsigned short int _5 = 1000;
  unsigned short int _6 = 1000;
};

struct artifacts
{
  unsigned short int _1 = 0;
  unsigned short int _2 = 0;
  unsigned short int _3 = 0;
  unsigned short int _4 = 0;
  unsigned short int _5 = 0;
  unsigned short int _6 = 0;
  unsigned short int _7 = 0;
  unsigned short int _8 = 0;
  unsigned short int _9 = 0;
  unsigned short int _10 = 0;
  unsigned short int _11 = 0;
  unsigned short int _12 = 0;
  unsigned short int _13 = 0;
  unsigned short int _14 = 0;
  unsigned short int _15 = 0;
  unsigned short int _16 = 0;
  unsigned short int _17 = 0;
  unsigned short int _18 = 0;
  unsigned short int _19 = 0;
  unsigned short int _20 = 0;
  unsigned short int _21 = 0;
  unsigned short int _22 = 0;
  unsigned short int _23 = 0;
  unsigned short int _24 = 0;
  unsigned short int _25 = 0;
  unsigned short int _26 = 0;
  unsigned short int _27 = 0;
  unsigned short int _28 = 0;
  unsigned short int _29 = 0;
  unsigned short int _30 = 0;
};


struct reducingDrugs reducingDrugs; //объявление структуры
struct protectingDrugs protectingDrugs; //объявление структуры
struct repair repair; //объявление структуры
struct foodAndDrinks foodAndDrinks; //объявление структуры
struct artifacts artifacts; //объявление структуры*/

//**************************************ПЕРЕМЕННЫЕ**************************************




long int transferResolution = 0;
long int id = 0;
long int item = 0;
long int quantity = 0;

unsigned short int back = 0;

unsigned short int counter = 0;
//*************************************************************************************





void setup() 
{
  displaySetup(); //настройки дисплея

  //rtcSetup(); //установка времени

  radioSetup(); //настройки радиомодуля

  //writeEEPROM(); //запись в EEPROM

  //readEEPROM(); //считывание из EEPROM

}

void loop() 
{
  
  positionXLoop();

  switch(x)
  {
    
    case 0:
    y=0;
    tft.fillScreen(TFT_BLACK);//фон дисплея
    do
    {      
      positionYLoop(); 

      switch(y)
      {
        case 0:      
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageOne();
        chooseMarkerOne();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=1;
          transferPage();
          
        }
        
        break;
        
        case 1:
        tft.fillRect(425,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageOne();
        chooseMarkerTwo();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {          
          item=2;
          transferPage();
        }
        break;
          
        case 2:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageOne();
        chooseMarkerThree();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=3;
          transferPage();
        }
        break;
      
        case 3:
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageOne();
        chooseMarkerFour();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=4;
          transferPage();
        }
        break;
      
        case 4:
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageOne();
        chooseMarkerFive();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=5;
          transferPage();
        }
        break;
      
        case 5:
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        thirdPageOne();
        chooseMarkerSix();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=6;
          transferPage();
        }
        break;
      }
      
      delay(1000);
      positionX = analogRead(xPin);
    }while(positionX!=0);
    break;

    case 1:
    y=0;
    tft.fillScreen(TFT_BLACK);//фон дисплея
    do
    {      
      positionYLoop(); 

     switch(y)
     {
        case 0:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageTwo();
        chooseMarkerOne();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {          
          item=7;
          transferPage();
        }
        break;
        
        case 1:
        tft.fillRect(425,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageTwo();
        chooseMarkerTwo();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {       
          item=8;
          transferPage();
        }
        break;
        
        case 2:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageTwo();
        chooseMarkerThree();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=9;
          transferPage();
        }
        break;
      
        case 3:
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageTwo();
        chooseMarkerFour();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=10;
          transferPage();
        }
        break;
     }
      
      delay(1000);
      positionX = analogRead(xPin);
    }while(positionX!=1023&&positionX!=0&&x==1);
    break;

    case 2:
    y=0;
    tft.fillScreen(TFT_BLACK);//фон дисплея
    do
    {      
      positionYLoop();

      switch(y)
      {
        case 0:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageThree();
        chooseMarkerOne();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=11;
          transferPage();
        }
        break;
      
        case 1:
        tft.fillRect(425,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageThree();
        chooseMarkerTwo();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=12;
          transferPage();
        }
        break;
       
        case 2:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageThree();
        chooseMarkerThree();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=13;
          transferPage();
        }
        break;
      
        case 3:
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageThree();
        chooseMarkerFour();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=14;
          transferPage();
        }
        break;
      }
      
      delay(1000);
      positionX = analogRead(xPin);
    }while(positionX!=0&&positionX!=1023&&x==2);
    break;

    case 3:
    y=0;
    tft.fillScreen(TFT_BLACK);//фон дисплея
    do
    {
      positionYLoop();

      switch(y)
      {
        case 0:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFour();
        chooseMarkerOne();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=15;
          transferPage();
        }
        break;
       
        case 1:
        tft.fillRect(425,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFour();
        chooseMarkerTwo();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=16;
          transferPage();
        }
        break;
       
        case 2:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFour();
        chooseMarkerThree();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=17;
          transferPage();
        }
        break;
      
        case 3:
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFour();
        chooseMarkerFour();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=18;
          transferPage();
        }
        break;
      
        case 4:
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFour();
        chooseMarkerFive();   
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=19;
          transferPage();
        }
        break;  

        case 5:
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        thirdPageFour();
        chooseMarkerSix();
        clickState=analogRead(clickPin);
        if(clickState==0)
        {
          item=20;
          transferPage();
        }
        break;

        
      }
      
      delay(1000);
      positionX = analogRead(xPin);
    }while(positionX!=0&&positionX!=1023&&x==3);
    break; 

    case 4:
    y=0;
    unsigned short int counter = 0;
    tft.fillScreen(TFT_BLACK);//фон дисплея
    do
    {      
      positionYLoopArtifacts();

      switch(y)
      {
        case 0:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveOne();
        chooseMarkerOne();
        break;
       
        case 1:
        tft.fillRect(425,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveOne();
        chooseMarkerTwo();
        break;
       
        case 2:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveOne();
        chooseMarkerThree();
        break;
      
        case 3:
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveOne();
        chooseMarkerFour();
        break;
      
        case 4:
        if(counter==1)
        {
          tft.fillScreen(TFT_BLACK);//фон дисплея
          counter--;
        }
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveOne();
        chooseMarkerFive();
        break;    
        //---//
        case 5:
        if(counter==0)
        {
          tft.fillScreen(TFT_BLACK);//фон дисплея
          counter++;
        }
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveTwo();
        chooseMarkerOne();
        break;

        case 6:
        tft.fillRect(425,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveTwo();
        chooseMarkerTwo();
        break;
       
        case 7:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveTwo();
        chooseMarkerThree();
        break;
      
        case 8:
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveTwo();
        chooseMarkerFour();
        break;
      
        case 9:
        if(counter==0)
        {
          tft.fillScreen(TFT_BLACK);//фон дисплея
          counter++;
        }
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveTwo();
        chooseMarkerFive();    
        break;  
        //---//
        case 10:
        if(counter==1)
        {
          tft.fillScreen(TFT_BLACK);//фон дисплея
          counter--;
        }
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveThree();
        chooseMarkerOne();
        break;
       
        case 11:
        tft.fillRect(425,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveThree();
        chooseMarkerTwo();
        break;
       
        case 12:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveThree();
        chooseMarkerThree();
        break;
      
        case 13:
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveThree();
        chooseMarkerFour();
        break;
      
        case 14:
        if(counter==1)
        {
          tft.fillScreen(TFT_BLACK);//фон дисплея
          counter--;
        }
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveThree();
        chooseMarkerFive();    
        break;  
        //---//
        case 15:
        if(counter==0)
        {
          tft.fillScreen(TFT_BLACK);//фон дисплея
          counter++;
        }
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveFour();
        chooseMarkerOne();
        break;
       
        case 16:
        tft.fillRect(425,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveFour();
        chooseMarkerTwo();
        break;
       
        case 17:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveFour();
        chooseMarkerThree();
        break;
      
        case 18:
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveFour();
        chooseMarkerFour();
        break;
      
        case 19:
        if(counter==0)
        {
          tft.fillScreen(TFT_BLACK);//фон дисплея
          counter++;
        }
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveFour();
        chooseMarkerFive();    
        break;  
        //---//
        case 20:
        if(counter==1)
        {
          tft.fillScreen(TFT_BLACK);//фон дисплея
          counter--;
        }
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveFive();
        chooseMarkerOne();
        break;
       
        case 21:
        tft.fillRect(425,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveFive();
        chooseMarkerTwo();
        break;
       
        case 22:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveFive();
        chooseMarkerThree();
        break;
      
        case 23:
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveFive();
        chooseMarkerFour();
        break;
      
        case 24:
        if(counter==1)
        {
          tft.fillScreen(TFT_BLACK);//фон дисплея
          counter--;
        }
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveFive();
        chooseMarkerFive();    
        break;  
        //---//
        case 25:
        if(counter==0)
        {
          tft.fillScreen(TFT_BLACK);//фон дисплея
          counter++;
        }
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveSix();
        chooseMarkerOne();
        break;
       
        case 26:
        tft.fillRect(425,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,80,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveSix();
        chooseMarkerTwo();
        break;
       
        case 27:
        tft.fillRect(425,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,110,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveSix();
        chooseMarkerThree();
        break;
      
        case 28:
        tft.fillRect(425,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,140,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,200,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveSix();
        chooseMarkerFour();
        break;
      
        case 29:
        tft.fillRect(425,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(454,170,16,21,TFT_BLACK); //стирание маркера сверху-вниз
        tft.fillRect(425,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        tft.fillRect(454,230,16,21,TFT_BLACK); //стирание маркера снизу-вверх
        thirdPageFiveSix();
        chooseMarkerFive();    
        break;  
        //---//
      }
      
      delay(1000);
      positionX = analogRead(xPin);
    }while(positionX!=1023&&x==4);
    break; 
  }
}

void displaySetup()
{
  tft.init();//инициализация дисплея
  tft.setRotation(1);//ориентация дисплея
  tft.fillScreen(TFT_BLACK);//фон дисплея
  tft.setTextFont(4);//типа шрифта дисплея
  tft.setTextColor(TFT_LIGHTGREY);//цвет шрифта дисплея
}

void radioSetup()
{
  radio.begin();
  //delay(2);
  radio.setChannel(9);
  radio.setDataRate(RF24_1MBPS); // скорость обмена данными RF24_1MBPS или RF24_2MBPS
  radio.setPALevel(RF24_PA_MIN);
  radio.openWritingPipe(pipe); // открыть канал на отправку
}

void positionXLoop()
{
  positionX = analogRead(xPin);
  if(positionX == 1023) x--;
  if(positionX == 0) x++;
  if(x<0) x=0;
  if(x>6) x=6;
}

void positionYLoop()
{
  positionY = analogRead(yPin);
  if(positionY == 1023) y--;
  if(positionY == 0) y++;
  if(y<0) y=0;
  if(y>5) y=5;
}

void positionXLoopTransferId()
{
  positionX = analogRead(xPin);
  if(positionX == 1023) id--;
  if(positionX == 0) id++;
  if(id<0) id=0;
  if(id>999) id=0;
}

void positionXLoopTransferQuantity()
{
  positionX = analogRead(xPin);
  if(positionX == 1023) quantity--;
  if(positionX == 0) quantity++;
  if(quantity<0) quantity=0;
  if(quantity>999) quantity=0;
}

void positionYLoopTransfer()
{
  positionY = analogRead(yPin);
  if(positionY == 1023) y--;
  if(positionY == 0) y++;
  if(y<0) y=0;
  if(y>3) y=3;
}

void positionYLoopArtifacts()
{
  positionY = analogRead(yPin);
  if(positionY == 1023) y--;
  if(positionY == 0) y++;
  if(y<0) y=0;
  if(y>29) y=29;
}

void timeAndDate()
{
  if (RTC.read(tm)) 
 {
    tft.fillRoundRect(5,5,100,20,0,TFT_BLACK);
    tft.fillRoundRect(350,5,130,20,0,TFT_BLACK);
  
    tft.setCursor(5,5);//время
    print2digits(tm.Hour);
    tft.write(':');
    print2digits(tm.Minute);
    tft.write(':');
    print2digits(tm.Second);

    tft.setCursor(350,5);
    tft.print(tm.Day);
    tft.write('/');
    tft.print(tm.Month);
    tft.write('/');
    tft.print(tmYearToCalendar(tm.Year));
  
    tft.drawFastHLine(0, 31, 480, TFT_LIGHTGREY);
 }
}

void print2digits(int number) 
{
 if (number >= 0 && number < 10) 
 {
  tft.write('0');
 }
 tft.print(number);
}

bool getTime(const char *str)
{
 int Hour, Min, Sec;
 
 if (sscanf(str, "%d:%d:%d", &Hour, &Min, &Sec) != 3) return false;
 tm.Hour = Hour;
 tm.Minute = Min;
 tm.Second = Sec;
 return true;
}
 
bool getDate(const char *str)
{
 char Month[12];
 int Day, Year;
 uint8_t monthIndex;
 
 if (sscanf(str, "%s %d %d", Month, &Day, &Year) != 3) return false;
 if (monthIndex >= 12) return false;
 tm.Day = Day;
 tm.Month = monthIndex + 1;
 tm.Year = CalendarYrToTm(Year);
 return true;
}

void rtcSetup()
{
  // получаем дату и время на момент компиляции
  if (getDate(__DATE__) && getTime(__TIME__)) 
 {
  parse = true;
  // и конфигурируем RTC используя эту информацию
  if (RTC.write(tm)) 
  {
    config = true;
  }
  }
}

/*void writeEEPROM()
{
  EEPROM.write(13,reducingDrugs._1);
  EEPROM.write(14,reducingDrugs._2);
  EEPROM.write(15,reducingDrugs._3);
  EEPROM.write(16,reducingDrugs._4);
  EEPROM.write(17,reducingDrugs._5);
  EEPROM.write(18,reducingDrugs._6);

  EEPROM.write(19,protectingDrugs._1);
  EEPROM.write(20,protectingDrugs._2);
  EEPROM.write(21,protectingDrugs._3);
  EEPROM.write(22,protectingDrugs._4);

  EEPROM.write(23,repair._1);
  EEPROM.write(24,repair._2);
  EEPROM.write(25,repair._3);
  EEPROM.write(26,repair._4);

  EEPROM.write(27,foodAndDrinks._1);
  EEPROM.write(28,foodAndDrinks._2);
  EEPROM.write(29,foodAndDrinks._3);
  EEPROM.write(30,foodAndDrinks._4);
  EEPROM.write(31,foodAndDrinks._5);
  EEPROM.write(32,foodAndDrinks._6);
}

void readEEPROM()
{
  reducingDrugs._1 = EEPROM.read(13);
  reducingDrugs._2 = EEPROM.read(14);
  reducingDrugs._3 = EEPROM.read(15);
  reducingDrugs._4 = EEPROM.read(16);
  reducingDrugs._5 = EEPROM.read(17);
  reducingDrugs._6 = EEPROM.read(18);

  protectingDrugs._1 = EEPROM.read(19);
  protectingDrugs._2 = EEPROM.read(20);
  protectingDrugs._3 = EEPROM.read(21);
  protectingDrugs._4 = EEPROM.read(22);

  repair._1 = EEPROM.read(23);
  repair._2 = EEPROM.read(24);
  repair._3 = EEPROM.read(25);
  repair._4 = EEPROM.read(26);

  foodAndDrinks._1 = EEPROM.read(27);
  foodAndDrinks._2 = EEPROM.read(28);
  foodAndDrinks._3 = EEPROM.read(29);
  foodAndDrinks._4 = EEPROM.read(30);
  foodAndDrinks._5 = EEPROM.read(31);
  foodAndDrinks._6 = EEPROM.read(32);
}*/

void footer()
{
  tft.drawFastHLine(0, 295, 480, TFT_LIGHTGREY);
  tft.drawFastVLine(160, 295, 25, TFT_LIGHTGREY);
  tft.drawFastVLine(320, 295, 25, TFT_LIGHTGREY);

  tft.setCursor(73,297);
  tft.print("1");
  tft.setCursor(233,297);
  tft.print("2");
  tft.setCursor(393,297);
  tft.print("3");
}

void inventoryMenu()
{
  tft.drawFastHLine(0, 270, 480, TFT_LIGHTGREY); //вертикальная линия подменю
  tft.drawFastVLine(80, 270, 25, TFT_LIGHTGREY);  //-
  tft.drawFastVLine(160, 270, 25, TFT_LIGHTGREY); //--
  tft.drawFastVLine(240, 270, 25, TFT_LIGHTGREY); //--- 1-5 вертикальные линии подменю
  tft.drawFastVLine(320, 270, 25, TFT_LIGHTGREY); //--
  tft.drawFastVLine(400, 270, 25, TFT_LIGHTGREY); //-

  tft.fillRoundRect(37,275,6,16,0,TFT_LIGHTGREY); //крест вертикальная линия
  tft.fillRoundRect(32,280,16,6,0,TFT_LIGHTGREY); //крест горизонтальная линия

  tft.drawRoundRect(110,278,20,10,4,TFT_LIGHTGREY); //пилюля общий прямоугольник
  tft.fillRoundRect(119,278,11,10,4,TFT_LIGHTGREY); //пилюля заполнение наполовину

  tft.drawFastHLine(195,280,10,TFT_LIGHTGREY); //ключ верх рукоятки
  tft.drawFastHLine(195,285,10,TFT_LIGHTGREY); //ключ низ рукоятки
  tft.drawLine(205,280,208,277,TFT_LIGHTGREY); //головка ключа право верх
  tft.drawLine(205,285,208,288,TFT_LIGHTGREY); //головка ключа право низ
  tft.drawLine(195,280,192,277,TFT_LIGHTGREY); //головка ключа лево верх
  tft.drawLine(195,285,192,288,TFT_LIGHTGREY); //головка ключа лево низ
  tft.drawFastHLine(188,277,4,TFT_LIGHTGREY); //головка ключа от угла прямо лево верх
  tft.drawFastHLine(188,288,4,TFT_LIGHTGREY); //головка ключа от угла прямо лево низ
  tft.drawFastHLine(209,277,4,TFT_LIGHTGREY); //головка ключа от угла прямо право верх
  tft.drawFastHLine(209,288,4,TFT_LIGHTGREY); //головка ключа от угла прямо право низ
  tft.drawLine(213,277,210,280,TFT_LIGHTGREY); //головка ключа от второго угла во внутрь право верх
  tft.drawLine(213,288,210,285,TFT_LIGHTGREY); //головка ключа от второго угла во внутрь право низ
  tft.drawLine(187,277,190,280,TFT_LIGHTGREY); //головка ключа от второго угла во внутрь лево верх
  tft.drawLine(187,288,190,285,TFT_LIGHTGREY); //головка ключа от второго угла во внутрь лево низ
  tft.drawFastVLine(190, 280, 5, TFT_LIGHTGREY); //перемычка головки лево
  tft.drawFastVLine(210, 280, 5, TFT_LIGHTGREY); //перемычка головки право

  tft.drawRoundRect(270,278,20,10,3,TFT_LIGHTGREY); //хлебушек общий прямоугольник 
  tft.drawLine(272,287,276,278,TFT_LIGHTGREY); //хлебушек наклонная слева первая 
  tft.drawLine(277,287,281,278,TFT_LIGHTGREY); //хлебушек наклонная слева вторая 
  tft.drawLine(278,287,282,278,TFT_LIGHTGREY); //хлебушек наклонная слева третья
  tft.drawLine(283,287,287,278,TFT_LIGHTGREY); //хлебушек наклонная слева четвертая

  tft.drawRoundRect(347,276,27,14,3,TFT_LIGHTGREY); //книга общий контур
  tft.drawFastVLine(360, 276, 14, TFT_LIGHTGREY); //переплет книги
  tft.drawFastHLine(350,279,7,TFT_LIGHTGREY); //первая строчка книги слева
  tft.drawFastHLine(350,282,7,TFT_LIGHTGREY); //вторая строчка книги слева
  tft.drawFastHLine(350,283,7,TFT_LIGHTGREY); //третья строчка книги слева
  tft.drawFastHLine(350,286,7,TFT_LIGHTGREY); //чтвертая строчка книги слева
  tft.drawFastHLine(364,279,7,TFT_LIGHTGREY); //первая строчка книги слева
  tft.drawFastHLine(364,282,7,TFT_LIGHTGREY); //вторая строчка книги слева
  tft.drawFastHLine(364,283,7,TFT_LIGHTGREY); //третья строчка книги слева
  tft.drawFastHLine(364,286,7,TFT_LIGHTGREY); //чтвертая строчка книги слева

  tft.fillCircle(427,282,3,TFT_LIGHTGREY);
  tft.fillCircle(440,282,3,TFT_LIGHTGREY);
  tft.fillCircle(453,282,3,TFT_LIGHTGREY);
}



void thirdPageOne()
{
  timeAndDate();

  tft.setCursor(150,45);
  tft.print("Reducing Drugs");

  tft.setCursor(5,80);
  tft.print("Bint");
  tft.setCursor(440,80);
  tft.println("->");

  tft.setCursor(5,110);
  tft.print("Aptechka");
  tft.setCursor(440,110);
  tft.println("->");

  tft.setCursor(5,140);
  tft.print("Armeyskaya aptechka");
  tft.setCursor(440,140);
  tft.println("->");

  tft.setCursor(5,170);
  tft.print("Naychnaya aptechka");
  tft.setCursor(440,170);
  tft.println("->");

  tft.setCursor(5,200);
  tft.print("Protivoradiacionniye preparaty");
  tft.setCursor(440,200);
  tft.println("->");

  tft.setCursor(5,230);
  tft.print("Barvinok");
  tft.setCursor(440,230);
  tft.println("->");

  inventoryMenu();

  tft.drawFastVLine(20, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, левая вертикальная линия
  tft.drawFastVLine(59, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, правая вертикальная линия
  tft.drawFastHLine(20, 292, 39, TFT_LIGHTGREY); //прямоугольник выбора подменю, горизонтальная линия

  footer();

  tft.drawFastHLine(40, 319, 80, TFT_LIGHTGREY);
  tft.drawFastVLine(40, 295, 25, TFT_LIGHTGREY);
  tft.drawFastVLine(120, 295, 25, TFT_LIGHTGREY);
  }

void thirdPageTwo()
{
  timeAndDate();

  tft.setCursor(150,45);
  tft.print("Protecting Drugs");

  tft.setCursor(5,80);
  tft.print("Psi-blokada");
  tft.setCursor(440,80);
  tft.println("->");

  tft.setCursor(5,110);
  tft.print("Radioprotektor");
  tft.setCursor(440,110);
  tft.println("->");

  tft.setCursor(5,140);
  tft.print("Antidot");
  tft.setCursor(440,140);
  tft.println("->");

  tft.setCursor(5,170);
  tft.print("Anabiotik");
  tft.setCursor(440,170);
  tft.println("->");

  inventoryMenu();

  tft.drawFastVLine(100, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, левая вертикальная линия
  tft.drawFastVLine(139, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, правая вертикальная линия
  tft.drawFastHLine(100, 292, 39, TFT_LIGHTGREY); //прямоугольник выбора подменю, горизонтальная линия

  footer();

  tft.drawFastHLine(40, 319, 80, TFT_LIGHTGREY);
  tft.drawFastVLine(40, 295, 25, TFT_LIGHTGREY);
  tft.drawFastVLine(120, 295, 25, TFT_LIGHTGREY);
}

void thirdPageThree()
{
  timeAndDate();

  tft.setCursor(150,45);
  tft.print("Repair");

  tft.setCursor(5,80);
  tft.print("Zaplatka");
  tft.setCursor(440,80);
  tft.println("->");

  tft.setCursor(5,110);
  tft.print("Karmanny remnabor");
  tft.setCursor(440,110);
  tft.println("->");

  tft.setCursor(5,140);
  tft.print("Poxodnyi remnabor");
  tft.setCursor(440,140);
  tft.println("->");

  tft.setCursor(5,170);
  tft.print("Professionalniy remnabor");
  tft.setCursor(440,170);
  tft.println("->");

  inventoryMenu();

  tft.drawFastVLine(180, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, левая вертикальная линия
  tft.drawFastVLine(219, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, правая вертикальная линия
  tft.drawFastHLine(180, 292, 39, TFT_LIGHTGREY); //прямоугольник выбора подменю, горизонтальная линия

  footer();

  tft.drawFastHLine(40, 319, 80, TFT_LIGHTGREY);
  tft.drawFastVLine(40, 295, 25, TFT_LIGHTGREY);
  tft.drawFastVLine(120, 295, 25, TFT_LIGHTGREY);
}

void thirdPageFour()
{
  timeAndDate();

  tft.setCursor(150,45);
  tft.print("Eda i Napitki");

  tft.setCursor(5,80);
  tft.print("Hleb");
  tft.setCursor(440,80);
  tft.println("->");

  tft.setCursor(5,110);
  tft.print("Kolbasa");
  tft.setCursor(440,110);
  tft.println("->");

  tft.setCursor(5,140);
  tft.print("Konserva");
  tft.setCursor(440,140);
  tft.println("->");

  tft.setCursor(5,170);
  tft.print("Vodka Kazaki");
  tft.setCursor(440,170);
  tft.println("->");

  tft.setCursor(5,200);
  tft.print("Energeticheeskiy napitok");
  tft.setCursor(440,200);
  tft.println("->");

  tft.setCursor(5,230);
  tft.print("Chistaya voda");
  tft.setCursor(440,230);
  tft.println("->");

  inventoryMenu();

  tft.drawFastVLine(260, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, левая вертикальная линия
  tft.drawFastVLine(299, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, правая вертикальная линия
  tft.drawFastHLine(260, 292, 39, TFT_LIGHTGREY); //прямоугольник выбора подменю, горизонтальная линия

  footer();

  tft.drawFastHLine(40, 319, 80, TFT_LIGHTGREY);
  tft.drawFastVLine(40, 295, 25, TFT_LIGHTGREY);
  tft.drawFastVLine(120, 295, 25, TFT_LIGHTGREY);
}

void thirdPageFiveOne()
{
  timeAndDate();

  tft.setCursor(170,45);
  tft.print("Artifacts");

  tft.setCursor(5,80);
  tft.print("artifact_1");
  tft.setCursor(440,80);
  tft.println("->");

  tft.setCursor(5,110);
  tft.print("artifact_2");
  tft.setCursor(440,110);
  tft.println("->");

  tft.setCursor(5,140);
  tft.print("artifact_3");
  tft.setCursor(440,140);
  tft.println("->");

  tft.setCursor(5,170);
  tft.print("artifact_4");
  tft.setCursor(440,170);
  tft.println("->");

  tft.setCursor(5,200);
  tft.print("artifact_5");
  tft.setCursor(440,200);
  tft.println("->");

  tft.fillTriangle (228,230,244,230,236,241,TFT_LIGHTGREY);

  inventoryMenu();

  tft.drawFastVLine(340, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, левая вертикальная линия
  tft.drawFastVLine(379, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, правая вертикальная линия
  tft.drawFastHLine(340, 292, 39, TFT_LIGHTGREY); //прямоугольник выбора подменю, горизонтальная линия

  footer();

  tft.drawFastHLine(40, 319, 80, TFT_LIGHTGREY);
  tft.drawFastVLine(40, 295, 25, TFT_LIGHTGREY);
  tft.drawFastVLine(120, 295, 25, TFT_LIGHTGREY);
}

void thirdPageFiveTwo()
{
  timeAndDate();

  tft.fillTriangle (228,65,244,65,236,54,TFT_LIGHTGREY);

  tft.setCursor(5,80);
  tft.print("artifact_6");
  tft.setCursor(440,80);
  tft.println("->");

  tft.setCursor(5,110);
  tft.print("artifact_7");
  tft.setCursor(440,110);
  tft.println("->");

  tft.setCursor(5,140);
  tft.print("artifact_8");
  tft.setCursor(440,140);
  tft.println("->");

  tft.setCursor(5,170);
  tft.print("artifact_9");
  tft.setCursor(440,170);
  tft.println("->");

  tft.setCursor(5,200);
  tft.print("artifact_10");
  tft.setCursor(440,200);
  tft.println("->");

  tft.fillTriangle (228,230,244,230,236,241,TFT_LIGHTGREY);

  inventoryMenu();

  tft.drawFastVLine(340, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, левая вертикальная линия
  tft.drawFastVLine(379, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, правая вертикальная линия
  tft.drawFastHLine(340, 292, 39, TFT_LIGHTGREY); //прямоугольник выбора подменю, горизонтальная линия

  footer();

  tft.drawFastHLine(40, 319, 80, TFT_LIGHTGREY);
  tft.drawFastVLine(40, 295, 25, TFT_LIGHTGREY);
  tft.drawFastVLine(120, 295, 25, TFT_LIGHTGREY);
}

void thirdPageFiveThree()
{
  timeAndDate();

  tft.fillTriangle (228,65,244,65,236,54,TFT_LIGHTGREY);

  tft.setCursor(5,80);
  tft.print("artifact_11");
  tft.setCursor(440,80);
  tft.println("->");

  tft.setCursor(5,110);
  tft.print("artifact_12");
  tft.setCursor(440,110);
  tft.println("->");

  tft.setCursor(5,140);
  tft.print("artifact_13");
  tft.setCursor(440,140);
  tft.println("->");

  tft.setCursor(5,170);
  tft.print("artifact_14");
  tft.setCursor(440,170);
  tft.println("->");

  tft.setCursor(5,200);
  tft.print("artifact_15");
  tft.setCursor(440,200);
  tft.println("->");

  tft.fillTriangle (228,230,244,230,236,241,TFT_LIGHTGREY);

  inventoryMenu();

  tft.drawFastVLine(340, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, левая вертикальная линия
  tft.drawFastVLine(379, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, правая вертикальная линия
  tft.drawFastHLine(340, 292, 39, TFT_LIGHTGREY); //прямоугольник выбора подменю, горизонтальная линия

  footer();

  tft.drawFastHLine(40, 319, 80, TFT_LIGHTGREY);
  tft.drawFastVLine(40, 295, 25, TFT_LIGHTGREY);
  tft.drawFastVLine(120, 295, 25, TFT_LIGHTGREY);
}

void thirdPageFiveFour()
{
  timeAndDate();

  tft.fillTriangle (228,65,244,65,236,54,TFT_LIGHTGREY);

  tft.setCursor(5,80);
  tft.print("artifact_16");
  tft.setCursor(440,80);
  tft.println("->");

  tft.setCursor(5,110);
  tft.print("artifact_17");
  tft.setCursor(440,110);
  tft.println("->");

  tft.setCursor(5,140);
  tft.print("artifact_18");
  tft.setCursor(440,140);
  tft.println("->");

  tft.setCursor(5,170);
  tft.print("artifact_19");
  tft.setCursor(440,170);
  tft.println("->");

  tft.setCursor(5,200);
  tft.print("artifact_20");
  tft.setCursor(440,200);
  tft.println("->");

  tft.fillTriangle (228,230,244,230,236,241,TFT_LIGHTGREY);

  inventoryMenu();

  tft.drawFastVLine(340, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, левая вертикальная линия
  tft.drawFastVLine(379, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, правая вертикальная линия
  tft.drawFastHLine(340, 292, 39, TFT_LIGHTGREY); //прямоугольник выбора подменю, горизонтальная линия

  footer();

  tft.drawFastHLine(40, 319, 80, TFT_LIGHTGREY);
  tft.drawFastVLine(40, 295, 25, TFT_LIGHTGREY);
  tft.drawFastVLine(120, 295, 25, TFT_LIGHTGREY);
}

void thirdPageFiveFive()
{
  timeAndDate();

  tft.fillTriangle (228,65,244,65,236,54,TFT_LIGHTGREY);

  tft.setCursor(5,80);
  tft.print("artifact_21");
  tft.setCursor(440,80);
  tft.println("->");

  tft.setCursor(5,110);
  tft.print("artifact_22");
  tft.setCursor(440,110);
  tft.println("->");

  tft.setCursor(5,140);
  tft.print("artifact_23");
  tft.setCursor(440,140);
  tft.println("->");

  tft.setCursor(5,170);
  tft.print("artifact_24");
  tft.setCursor(440,170);
  tft.println("->");

  tft.setCursor(5,200);
  tft.print("artifact_25");
  tft.setCursor(440,200);
  tft.println("->");

  tft.fillTriangle (228,230,244,230,236,241,TFT_LIGHTGREY);

  inventoryMenu();

  tft.drawFastVLine(340, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, левая вертикальная линия
  tft.drawFastVLine(379, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, правая вертикальная линия
  tft.drawFastHLine(340, 292, 39, TFT_LIGHTGREY); //прямоугольник выбора подменю, горизонтальная линия

  footer();

  tft.drawFastHLine(40, 319, 80, TFT_LIGHTGREY);
  tft.drawFastVLine(40, 295, 25, TFT_LIGHTGREY);
  tft.drawFastVLine(120, 295, 25, TFT_LIGHTGREY);
}

void thirdPageFiveSix()
{
  timeAndDate();

  tft.fillTriangle (228,65,244,65,236,54,TFT_LIGHTGREY);

  tft.setCursor(5,80);
  tft.print("artifact_26");
  tft.setCursor(440,80);
  tft.println("->");

  tft.setCursor(5,110);
  tft.print("artifact_27");
  tft.setCursor(440,110);
  tft.println("->");

  tft.setCursor(5,140);
  tft.print("artifact_28");
  tft.setCursor(440,140);
  tft.println("->");

  tft.setCursor(5,170);
  tft.print("artifact_29");
  tft.setCursor(440,170);
  tft.println("->");

  tft.setCursor(5,200);
  tft.print("artifact_30");
  tft.setCursor(440,200);
  tft.println("->");

  inventoryMenu();

  tft.drawFastVLine(340, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, левая вертикальная линия
  tft.drawFastVLine(379, 270, 23, TFT_LIGHTGREY); //прямоугольник выбора подменю, правая вертикальная линия
  tft.drawFastHLine(340, 292, 39, TFT_LIGHTGREY); //прямоугольник выбора подменю, горизонтальная линия

  footer();

  tft.drawFastHLine(40, 319, 80, TFT_LIGHTGREY);
  tft.drawFastVLine(40, 295, 25, TFT_LIGHTGREY);
  tft.drawFastVLine(120, 295, 25, TFT_LIGHTGREY);
}

void transferPage()
{
  tft.fillScreen(TFT_BLACK);//фон дисплея
  x=0;
  y=0;
  back=0;
  do
    {
      tft.setCursor(100,40);
      tft.println("ID:");
      tft.setCursor(340,40);
      tft.print(id);

      tft.setCursor(100,120);
      tft.println("Quantity:");
      tft.setCursor(340,120);
      tft.println(quantity);

      tft.setCursor(70,200);
      tft.println("Accept");
      tft.setCursor(330,200);
      tft.println("Back");
            
      positionYLoopTransfer();

      switch(y)
      {
        case 0:
        tft.fillRect(320,120,20,30,TFT_BLACK);
        tft.fillRect(388,120,20,30,TFT_BLACK);
        tft.setCursor(320,40);
        tft.println("<");
        tft.setCursor(388,40);
        tft.println(">");
        delay(200);

        positionX = analogRead(xPin);
        if(positionX==0||positionX==1023)
        {
          tft.fillRect(340,40,48,30,TFT_BLACK);
          positionXLoopTransferId();
        }
        break;

        case 1:
        tft.fillRect(320,40,20,30,TFT_BLACK);
        tft.fillRect(388,40,20,30,TFT_BLACK);
        tft.fillRect(70,225,80,5,TFT_BLACK);
        tft.setCursor(320,120);
        tft.println("<");
        tft.setCursor(388,120);
        tft.println(">");
        delay(200);

        positionX = analogRead(xPin);
        if(positionX==0||positionX==1023)
        {
          tft.fillRect(340,120,48,30,TFT_BLACK);
          positionXLoopTransferQuantity();
        }
        break;

        case 2:
        tft.fillRect(320,120,20,30,TFT_BLACK);
        tft.fillRect(388,120,20,30,TFT_BLACK);
        tft.fillRect(330,225,80,5,TFT_BLACK);
        tft.setCursor(70,205);
        tft.println("______");
        delay(200);

        clickState=analogRead(clickPin);
        if(clickState==0)
        {    
          id=id*1000000;
          item=item*1000;
          transferResolution=id+item+quantity;

          do
          {
            radio.write(&transferResolution,4);  
            counter++;
           }while(counter<15);
           counter=0;
           id=0;
           item=0;
           quantity=0;
           back=1;
           y=0;
           tft.fillScreen(TFT_BLACK);//фон дисплея
           } 
           break;

           case 3:
           tft.fillRect(70,225,80,5,TFT_BLACK);
           tft.setCursor(330,205);
           tft.println("____");
           delay(200);

           clickState=analogRead(clickPin);
           if(clickState==0)
           {
             back=1;
             y=0;
             tft.fillScreen(TFT_BLACK);//фон дисплея
           }
           break;
        }
    }while(back==0);
}

void chooseMarkerOne()
{
  tft.drawFastHLine(425, 80, 10, TFT_LIGHTGREY); //скобочки выбора право верх
  tft.drawFastHLine(460, 80, 10, TFT_LIGHTGREY); //скобочки выбора лево верх  
  tft.drawFastHLine(425, 100, 10, TFT_LIGHTGREY); //скобочки выбора право низ
  tft.drawFastHLine(460, 100, 10, TFT_LIGHTGREY); //скобочки выбора лево низ
  tft.drawFastVLine(425, 80, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные лево
  tft.drawFastVLine(469, 80, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные право
}

void chooseMarkerTwo()
{
  tft.drawFastHLine(425, 110, 10, TFT_LIGHTGREY); //скобочки выбора право верх
  tft.drawFastHLine(460, 110, 10, TFT_LIGHTGREY); //скобочки выбора лево верх  
  tft.drawFastHLine(425, 130, 10, TFT_LIGHTGREY); //скобочки выбора право низ
  tft.drawFastHLine(460, 130, 10, TFT_LIGHTGREY); //скобочки выбора лево низ
  tft.drawFastVLine(425, 110, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные лево
  tft.drawFastVLine(469, 110, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные право
}

void chooseMarkerThree()
{
  tft.drawFastHLine(425, 140, 10, TFT_LIGHTGREY); //скобочки выбора право верх
  tft.drawFastHLine(460, 140, 10, TFT_LIGHTGREY); //скобочки выбора лево верх  
  tft.drawFastHLine(425, 160, 10, TFT_LIGHTGREY); //скобочки выбора право низ
  tft.drawFastHLine(460, 160, 10, TFT_LIGHTGREY); //скобочки выбора лево низ
  tft.drawFastVLine(425, 140, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные лево
  tft.drawFastVLine(469, 140, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные право
}

void chooseMarkerFour()
{
  tft.drawFastHLine(425, 170, 10, TFT_LIGHTGREY); //скобочки выбора право верх
  tft.drawFastHLine(460, 170, 10, TFT_LIGHTGREY); //скобочки выбора лево верх  
  tft.drawFastHLine(425, 190, 10, TFT_LIGHTGREY); //скобочки выбора право низ
  tft.drawFastHLine(460, 190, 10, TFT_LIGHTGREY); //скобочки выбора лево низ
  tft.drawFastVLine(425, 170, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные лево
  tft.drawFastVLine(469, 170, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные право
}

void chooseMarkerFive()
{
  tft.drawFastHLine(425, 200, 10, TFT_LIGHTGREY); //скобочки выбора право верх
  tft.drawFastHLine(460, 200, 10, TFT_LIGHTGREY); //скобочки выбора лево верх  
  tft.drawFastHLine(425, 220, 10, TFT_LIGHTGREY); //скобочки выбора право низ
  tft.drawFastHLine(460, 220, 10, TFT_LIGHTGREY); //скобочки выбора лево низ
  tft.drawFastVLine(425, 200, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные лево
  tft.drawFastVLine(469, 200, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные право
}

void chooseMarkerSix()
{
  tft.drawFastHLine(425, 230, 10, TFT_LIGHTGREY); //скобочки выбора право верх
  tft.drawFastHLine(460, 230, 10, TFT_LIGHTGREY); //скобочки выбора лево верх  
  tft.drawFastHLine(425, 250, 10, TFT_LIGHTGREY); //скобочки выбора право низ
  tft.drawFastHLine(460, 250, 10, TFT_LIGHTGREY); //скобочки выбора лево низ
  tft.drawFastVLine(425, 230, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные лево
  tft.drawFastVLine(469, 230, 20, TFT_LIGHTGREY); //скобочки выбора вертикальные право
}







