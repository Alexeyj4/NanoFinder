
// Определяем вывод RX
#define RX 5

// Определяем вывод TX
#define TX 6

int ledPin = 4;



// Подключаем библиотеку программного UART
#include <SoftwareSerial.h>

#include <LiquidCrystal.h>  // Лобавляем необходимую библиотеку для LCD
LiquidCrystal lcd(7, 8, 9, 10, 11, 12); // (RS, E, DB4, DB5, DB6, DB7) //physical pin

// Создаём объект программного UART
SoftwareSerial softSerial(RX, TX);

int silent=1; //1-silent; 0-not silent (debug info to serial)
char ans[7];
int ttf;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  ans[6]="/0";

  Serial.begin(115200);

  softSerial.begin(115200);

  delay(5000);

}


void exe(char*s)
{
  
  delay(10);
  softSerial.write(s);
  softSerial.write('\r');
  delay(10);

  exe();
  
}

void exe()
{
  while(softSerial.available()) 
  {
    char c=softSerial.read();

    analyze(c);

    if(silent==0)
    {
      //if(c=='\r')Serial.write("\n\r");
      //else Serial.write(c);
    }
  }
}

void shift(char c)
{
  ans[0]=ans[1];
  ans[1]=ans[2];
  ans[2]=ans[3];
  ans[3]=ans[4];
  ans[4]=ans[5];
  ans[5]=c;
  ans[6]="\0";
}


void showttf()
{
  digitalWrite(ledPin, HIGH);
  lcd.begin(16, 2);                  // Задаем размерность экрана
  lcd.setCursor(0, 0);              // Устанавливаем курсор в начало 1 строки

  lcd.print("TTF:");       // Выводим текст 
  for(int i=ttf-9;i>0;i--)
  {
    Serial.write('*');
    lcd.print("*");       // Выводим текст    
  }
  lcd.setCursor(0, 1);              // Устанавливаем курсор в начало 2 строки
  lcd.print("RSSI:");       // Выводим текст 
  Serial.write("\n\r");
  delay(100);
  digitalWrite(ledPin, LOW);
      
}

void analyze(char c)
{  

  //debug("analyze");//debug(ans);
  shift(c);  
  if(ans[0]=='[')
  {
    if(ans[1]=='0')
    {
      if(ans[2]==']')
      {
        if(ans[3]==' ')
        {
          if(ans[4]=='1')
          {
            readdigit();
            showttf();            
          }
          
                    

        }
      }
    }
  }
  
}



void debug(char*str)
{
  Serial.print("\n\r");
  Serial.print("**********");
  Serial.print(str);
  Serial.print("**********");
  Serial.print("\n\r");
}

void debug(int n)
{
  Serial.print("\n\r");
  Serial.print("**********");
  Serial.print(n);
  Serial.print("**********");
  Serial.print("\n\r");
}



void readdigit()
{
  //debug("++++++++++++++++++++++++++++++++++++++++++++"); 
  ttf=10+(int(ans[5]-'0'));
  //debug(ttf);

  
}


void loop() {

    digitalWrite(ledPin, LOW);
    

    exe();
    
    int i=5;
    if(i>=5)
    {
      silent=1;
      exe("at dst 0x1\r"); //был 0x0605 теперь 0x1
      silent=0;
            
      exe("rt\r");       
      
      i=0;
    }
    
    delay(100);
    i=i+1;

    lcd.begin(16, 2);    
      
  
  // put your main code here, to run repeatedly:

}
