#include <Keypad.h>
#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;
int a=0;
LiquidCrystal lcd(5, 4, 3, 2, A4, A5);
int tempPin = A2; int val;
char passN[4]={'1','2','3','4'};
char passC[4]={' ',' ',' ',' '};
char passT[4];
char passM[4];
int i, dem =0;
int lap = 0;
int op;
const byte ROWS = 4; 
const byte COLS = 4; 
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {A0, A1, 11, 10}; 
byte colPins[COLS] = {9, 8, 7, 6}; 

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup(){
   Serial.begin(9600);
   lcd.begin(16, 2);
   myservo.attach(12);
   myservo.write(90);
   pinMode(13, OUTPUT);
   digitalWrite(13,0);
   lcd.setCursor(2, 0);
   lcd.print("Welcome home");   
   delay(3000);
   lcd.clear();
   lcd.setCursor(1,0);
   lcd.print("Door is closed");
   }

void nhapnhay(){
  digitalWrite(13, 1);
  delay(800); 
  digitalWrite(13, 0);
  delay(800); 
  digitalWrite(13, 1);
}  

void temp(){
  if(a==0){
  val = analogRead(tempPin);
  float mv = ( val/1023.0)*5000; 
  float cel = mv/10-50;
  Serial.print(cel);
  if(cel>100){
    lcd.clear();
    lcd.print("  Temp is high");
    delay(1000);
    lcd.clear();
    lcd.print("   Warnning!!!");
    nhapnhay();
    delay(500);
    lcd.clear();
    myservo.write(180);
    lcd.print("  Door opened!");  
    a=1;
  }
  }
}

void loop(){
  char key = keypad.getKey(); 
  if(key == 'A'){
    lap = 1;
    lcd.clear();
    lcd.print("Enter password: ");
    key = 0;
  }
  if(lap == 1){
    if(key){
    if (i == 0) {
      passC[0] = key;
      lcd.setCursor(6, 1);
      lcd.print(passC[0]);
      delay(1000); 
      lcd.setCursor(6, 1);
      lcd.print("*");
    }
    if (i == 1) {
      passC[1] = key;
      lcd.setCursor(7, 1);
      lcd.print(passC[1]);
      delay(1000);
      lcd.setCursor(7, 1);
      lcd.print("*");
    }
    if (i == 2) {
      passC[2] = key;
      lcd.setCursor(8, 1);
      lcd.print(passC[2]);
      delay(1000);
      lcd.setCursor(8, 1);
      lcd.print("*");
    }
    if (i == 3) {
      passC[3] = key;
      lcd.setCursor(9, 1);
      lcd.print(passC[3]);
      delay(1000);
      lcd.setCursor(9, 1);
      lcd.print("*");
      dem = 1;
    }
    i = i + 1;
   }
  }
    
  if((key == '*') and (lap==1)){
      i=0;
      key=0;
      lcd.clear();                
      lcd.setCursor(0, 0);
      lcd.print("Enter password:");
  }
  
  if(lap == 1){
  if (dem == 1) {
    if (passC[0] == passN[0] && passC[1] == passN[1] && passC[2] == passN[2] &&
        passC[3] == passN[3]) {
      lcd.clear();
      lcd.print("    Correct!");
      delay(3000);
      nhapnhay();
      myservo.write(180);
      lap = 1;
      op = 1;
      lcd.clear();
      lcd.print("  Door opened!");
      i = 0;
      dem = 0;
    } else {
      lcd.clear();
      lcd.print("   Incorrect!");
      delay(3000);
      lcd.clear();
      lcd.print("   Try Again!");
      delay(3000);
      lcd.clear();
      lcd.print(" Enter password");
      i = 0;
      dem = 0;
    }
  }
  }
  
  if((key == '#')and(lap==1)and(op==1)){
    lcd.clear();
    lcd.print("Change password");
    delay(2000);
    lap = 2;
    i=0;
    lcd.clear();
    lcd.print("Enter new pass:");  
    key = 0;
  }
  if(lap==2){
    if(key){
    if (i == 0) {
      passT[0] = key;
      lcd.setCursor(6, 1);
      lcd.print(passT[0]);
      delay(1000); 
      lcd.setCursor(6, 1);
      lcd.print("*");
    }
    if (i == 1) {
      passT[1] = key;
      lcd.setCursor(7, 1);
      lcd.print(passT[1]);
      delay(1000);
      lcd.setCursor(7, 1);
      lcd.print("*");
    }
    if (i == 2) {
      passT[2] = key;
      lcd.setCursor(8, 1);
      lcd.print(passT[2]);
      delay(1000);
      lcd.setCursor(8, 1);
      lcd.print("*");
    }
    if (i == 3) {
      passT[3] = key;
      lcd.setCursor(9, 1);
      lcd.print(passT[3]);
      delay(1000);
      lcd.setCursor(9, 1);
      lcd.print("*");
      dem = 1;
      i=-1;
      key=0;
      lap=3;
      lcd.clear();
    lcd.setCursor(2,0);
    lcd.print("Enter again:");
    delay(200);
    }
    i = i + 1;
   }    
  }
  
  if(lap==3){  
    if(key){
    if (i == 0) {
      passM[0] = key;
      lcd.setCursor(6, 1);
      lcd.print(passM[0]);
      delay(1000); 
      lcd.setCursor(6, 1);
      lcd.print("*");
    }
    if (i == 1) {
      passM[1] = key;
      lcd.setCursor(7, 1);
      lcd.print(passM[1]);
      delay(1000);
      lcd.setCursor(7, 1);
      lcd.print("*");
    }
    if (i == 2) {
      passM[2] = key;
      lcd.setCursor(8, 1);
      lcd.print(passM[2]);
      delay(1000);
      lcd.setCursor(8, 1);
      lcd.print("*");
    }
    if (i == 3) {
      passM[3] = key;
      lcd.setCursor(9, 1);
      lcd.print(passM[3]);
      delay(1000);
      lcd.setCursor(9, 1);
      lcd.print("*");
      dem = 1;
      i=-1;
      key=0;
      lap=4;
    }
    i = i + 1;
   }    
  }
  
  if(lap==4){
    if (passT[0] == passM[0] && passT[1] == passM[1] && passT[2] == passM[2] &&
        passT[3] == passM[3]) {
      lcd.clear();
      lcd.print("Change success!");
      passN[0]=passT[0];
      passN[1]=passT[1];
      passN[2]=passT[2];
      passN[3]=passT[3];
      delay(500);
      lcd.clear();
      myservo.write(90);
      digitalWrite(13, 0);
      a=0;
      lcd.print(" Door is closed!");
      key=0; i=0; lap=0; dem=0;
      passC[0]=' ';
      passC[1]=' ';
      passC[2]=' ';
      passC[3]=' ';
   }else{
        lcd.clear();
        lcd.print("Failed to change");
        lap=2;
        i=0; key=0; 
        delay(2000);
        lcd.clear();        
        lcd.print("Enter new pass:");
        
      }
  }
        
  switch (key) {
  case 'C':
    lcd.clear(); 
    myservo.write(90);
    nhapnhay();
    a=0;
    lcd.print(" Door is closed!");
    digitalWrite(13, 0);
    delay(2000);
    i = 0;
    break;
  } 
}
