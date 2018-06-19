#include <LiquidCrystal.h>

LiquidCrystal lcd(0, 1, 2, 3, 4, 5);

int delayTimer = 2000;
int roundCounter = 0;
int lightCounter = 0;
int points = 0;

int lightList[100];
int listCounter = 0;

int previouslyPressedList[100];
int pressCounter = 0;

boolean gameStarted = false;

int i = 0;

int val1 = 0;
int val2 = 0;
int val3 = 0;
int val4 = 0;

void setup() {
    
    pinMode(6, INPUT);
    pinMode(7, OUTPUT);
    pinMode(8, INPUT);
    pinMode(9, INPUT);
    pinMode(10,INPUT);
    pinMode(13, OUTPUT);
    pinMode(12, OUTPUT);
    pinMode(11, OUTPUT);
      
  lcd.begin(16, 2);

  startGame();
  
  randomSeed(analogRead(0));
}

void loop() {
  
  val1 = digitalRead(6);
  val2 = digitalRead(8);
  val3 = digitalRead(9);
  val4 = digitalRead(10);
  
  if(val1 == HIGH) {
    updatePressedList(1);   
    if(roundCounter == lightCounter){ 
      setLights();  
   }
  }
  
  if(val2 == HIGH){
    updatePressedList(2);    
    if(roundCounter == lightCounter){ 
      setLights();  
   }
  }
 
  if (val3 == HIGH) {    
    updatePressedList(3);   
    if(roundCounter == lightCounter){ 
      setLights();  
   }
  }
  
  if (val4 == HIGH) {
    updatePressedList(4);    
    if(roundCounter == lightCounter){ 
      setLights();  
   } 
  }
}

void stopGame(){
 
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Final points");
 lcd.setCursor(0,1);
 lcd.print(points);
 
 while(true){
 }
 
}

void startGame(){
   
 lcd.print("Game starts in");
 lcd.setCursor(3,1);
 lcd.print("Seconds"); 
 for(int i = 5; i > 0; i--){
  
  lcd.setCursor(0, 1);
  lcd.print(i);
  delay(1000);
 }
 goLive();
}

void goLive(){
  
 lcd.clear();
 lcd.setCursor(0,0);
 lcd.print("Press any button");
 lcd.setCursor(0,1);
 lcd.print("to start");
 delay(1000);
 loop();
 
}

void setLights(){
  
  checkAnswer();
  lcd.clear();
  lcd.print("Points");
  lcd.setCursor(0,1);
  lightCounter++;
  lcd.print(points);
  for(int i = 0; i < lightCounter; i++){
  setRandomLight();
  }
  
}

void checkAnswer(){
 
 if(!gameStarted) {
  gameStarted = true;
 }
 
 else {
   for(int i = 0; i < listCounter; i++){
     
     if(previouslyPressedList[i] == lightList[i]){
      points++; 
     }
     
     else {
      stopGame();
     }
  } 
 }
 roundCounter = 0;
}

void setRandomLight() {

  int randNumber = random(1,5);

  if(randNumber == 1){
     updateLightList(1);
     lightUpRed();
  }
  else if(randNumber == 2){
     updateLightList(2);
     lightUpYellow();
  }
  else if(randNumber == 3){
     updateLightList(3);
     lightUpGreen();
  }
  else{
     updateLightList(4);
     lightUpBlue();  
  }
}

void lightUpRed(){
  
 digitalWrite(7, HIGH);
 delay(delayTimer);
 digitalWrite(7, LOW);
 delay(300);
 
}

void lightUpYellow(){
  
 digitalWrite(11, HIGH);
 delay(delayTimer);
 digitalWrite(11, LOW);
 delay(300);
 
}

void lightUpGreen(){
  
 digitalWrite(12, HIGH);
 delay(delayTimer);
 digitalWrite(12, LOW);
 delay(300);
 
}

void lightUpBlue(){
  
 digitalWrite(13, HIGH);
 delay(delayTimer);
 digitalWrite(13, LOW);
 delay(300);
}

void updateLightList(int num){
  
 if(gameStarted){
  lightList[listCounter] = num;
  listCounter++;  
 }
}

void updatePressedList(int num){
  
 delay(500);
 
 if(gameStarted){
  previouslyPressedList[pressCounter] = num;
  roundCounter++;
  pressCounter++;
 }
}
