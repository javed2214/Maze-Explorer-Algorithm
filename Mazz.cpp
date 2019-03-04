#include<Arduino.h>

const int ENA=11;
const int ENB=10;
const int M_A1=3;
const int M_A2=2;
const int M_B1=4;
const int M_B2=5;

const int R_S=8;
const int S_S=7;
const int L_S=6;

int RS=digitalRead(R_S);
int CS=digitalRead(S_S);
int LS=digitalRead(L_S);

String str,s;

void setup(){

  pinMode(LS, INPUT);
  pinMode(CS, INPUT);
  pinMode(RS, INPUT);
  pinMode(M_B1, OUTPUT);
  pinMode(M_B2, OUTPUT);
  pinMode(M_A1, OUTPUT);
  pinMode(M_A2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENA, OUTPUT);

  Serial.begin (9600);
}
void forward(){
  
  digitalWrite(M_A1, HIGH);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);  
  analogWrite (ENA,150);
  analogWrite (ENB,150);
  s+="S"; 
}

void turnLeft(){
    
  digitalWrite(M_A1, HIGH);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, LOW);
  analogWrite (ENA,120);
  analogWrite (ENB,0);
  s+="L";
}

void turnRight(){

  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);  
  analogWrite (ENA,0);
  analogWrite (ENB,120);
  s+="R";
}

void backward(){

  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, HIGH);
  digitalWrite(M_B1, LOW);
  digitalWrite(M_B2, HIGH);
  analogWrite (ENA,60);
  analogWrite (ENB,60); 
  s+="B"; 
}

void func1(){

  digitalWrite(M_A1, HIGH);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);
  analogWrite (ENA,60);
  analogWrite (ENB,60);  
}

void func2(){

  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);
  analogWrite (ENA,0);
  analogWrite (ENB,40);  
}

void forwardLoop(){
  while(true){
    forward();
    if(!(LS == 0 && CS == 1 && RS == 0)) break;
  }
}

void leftLoop(){
  while(true){
    turnLeft();
    if((LS == 0 && CS == 1 && RS == 0)) break;
  }
  forwardLoop();
}

void rightLoop(){
  while(true){
    turnRight();
    if((LS == 0 && CS == 1 && RS == 0)) break;
  }
  forwardLoop();
}

void backLoop(){
  while(true){
    backward();
    if((LS == 0 && CS == 1 && RS == 0)) break;
  }
}

String shortestPath(){
  
  int count=3;
  // s="LLLBLLLRBLLBSRSRS";
  Serial.println(s.length());
  for(int i=0;i<s.length();i++){
      String str=s.substring(i,count);
      Serial.println(str);
      if(str=="LBR") s.replace("LBR","B"),i=0,count=3;
      else if(str=="LBS") s.replace("LBS","R"),i=0,count=3;
      else if(str=="RBL") s.replace("RBL","B"),i=0,count=3;
      else if(str=="SBL") s.replace("SBL","R"),i=0,count=3;
      else if(str=="SBS") s.replace("SBS","B"),i=0,count=3;
      else if(str=="LBL") s.replace("LBL","S"),i=0,count=3;
      count++;
    }
    Serial.print("Shortest Path: ");
    if(str=="LBR") s="B";
    else if(s=="LBS") s="R";
    else if(s=="RBL") s="B";
    else if(s=="SBL") s="R";
    else if(s=="SBS") s="B";
    else if(s=="LBL") s="S";
    Serial.println(s);

    return s;
}

void tracePath(String sst){
  
  forwardLoop();

  for(int i=0;i<sst.length();i++){
    if(sst[i]=='S') forwardLoop(),Serial.println("Forward");
    else if(sst[i]=='L') leftLoop(),Serial.println("Left");
    else if(sst[i]=='R') rightLoop(),Serial.println("Right");
    else if(sst[i]=='B') backLoop(),Serial.println("Backward");
  }
}

void loop(){

  if (LS == 0 && CS == 1 && RS == 0) forward();
  else if (LS == 1 && CS == 1 && RS == 0) turnLeft();
  else if (LS == 1 && CS == 0 && RS == 0) turnLeft();
  else if (LS == 0 && CS == 1 && RS == 1) turnRight();
  else if (LS == 0 && CS == 0 && RS == 1) turnRight();
  else if (LS == 0 && CS == 0 && RS == 0) backward();
  else if( LS == 1 && CS == 1 && RS == 1) func1();
  else func2();
  
  String s=shortestPath();
  delay(5000);
  tracePath(s);

//  for(int i=0;i<ss.length();i++){
//    if(ss[i]=='S') forward(),Serial.println("Forward");
//    else if(!(LS == 0 && CS == 1 && RS == 0)){
//      if(ss[i]=='L') turnLeft(),Serial.println("Left");
//      else if(ss[i]=='R') turnRight(),Serial.println("Right");
//      else if(ss[i]=='B') backward(),Serial.println("Back");
//    }
//    else forward(),Serial.println("Forward");
//  }

  delay(1000); 
  exit(1);      
}
