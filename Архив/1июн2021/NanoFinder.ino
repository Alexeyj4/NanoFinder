
// Определяем вывод RX
#define RX 5

// Определяем вывод TX
#define TX 6

// Подключаем библиотеку программного UART
#include <SoftwareSerial.h>

// Создаём объект программного UART
SoftwareSerial softSerial(RX, TX);

int silent=0; //1-silent; 0-not silent
char ans[7];
int ttf;

void setup() {
  // put your setup code here, to run once:
  
  ans[6]="/0";

  Serial.begin(115200);

  softSerial.begin(115200);

  delay(1000);

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
  for(int i=ttf-9;i>0;i--)
  {
    Serial.write('*');    
  }
  Serial.write("\n\r");    
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

    exe();
    
    int i=5;
    if(i>=5)
    {
      silent=1;
      exe("at dst 0x0605\r");
      silent=0;
            
      exe("rt\r");       
      
      i=0;
    }
    
    delay(10);
    i=i+1;


      
  
  // put your main code here, to run repeatedly:

}
