#define GREEN 3
#define YELLOW 4
#define RED 5
#define BUZZER 6
#define TEMP A0
#define SMOKE A1

#include<LiquidCrystal.h>
LiquidCrystal lcd(12,11,10,9,8,7);

void setup(){
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    pinMode(YELLOW, OUTPUT);
    pinMode(BUZZER, OUTPUT);
    pinMode(SMOKE, INPUT);
    pinMode(TEMP, INPUT);
    Serial.begin(9600);
}

void loop(){
  float Temp = ((analogRead(TEMP)/1024.00)*5000)/10;
  if(analogRead(SMOKE)>=500 && Temp>=100.0){
      alert(analogRead(SMOKE),Temp);
      noTone(BUZZER);
  }else if(((analogRead(SMOKE)>=400 && analogRead(SMOKE)<500)
           &&(Temp>=90.0 && Temp<100.0))
           ||(analogRead(SMOKE)>=500 || Temp>=100.0)){
      semi_alert(analogRead(SMOKE),Temp);
  }
  else{
    Serial.print(analogRead(SMOKE));
    Serial.print(", ");
    Serial.println(Temp);
    lcd.setCursor(0,0);
    lcd.print("SAFE");
    digitalWrite(GREEN, HIGH);
    digitalWrite(RED, LOW);
    digitalWrite(YELLOW, LOW);
    digitalWrite(BUZZER, LOW);
  }
}

void alert(int A,int B){
    Serial.print(A);
    Serial.print(", ");
    Serial.println(B);
    lcd.setCursor(0,0);
    lcd.print("DANGER!!");
    digitalWrite(YELLOW, LOW);
    digitalWrite(GREEN, LOW);
    digitalWrite(RED, HIGH);
    tone(BUZZER, 500);
    delay(500);
    digitalWrite(RED, LOW);
    delay(500);
    digitalWrite(RED, HIGH);
    lcd.clear();
}

void semi_alert(int A,int B){
    Serial.print(A);
    Serial.print(", ");
    Serial.println(B);
    lcd.setCursor(0,0);
    lcd.print("WARNING!!");
    digitalWrite(RED, LOW);
    digitalWrite(BUZZER, LOW);  
    digitalWrite(GREEN, LOW);
    digitalWrite(YELLOW, HIGH);
    delay(500);
    digitalWrite(YELLOW, LOW);
    delay(500);
    digitalWrite(YELLOW, HIGH);
    lcd.clear();
}
