#include<Arduino.h>

const int ENA = 10;  //speed motor a
const int M_A1 = 5; //motor a RIGHT, HIGH=forward(+)
const int M_A2 = 4; //motor a -
const int M_B1 = 2; //motor b LEFT
const int M_B2 = 3; //motor b = +
const int ENB = 11;  //speed motor b
  
const int R_S = 8; //sensor R
const int R_S1 =9; //sensor R1
const int S_S = 7; //sensor S
const int L_S1 =12; //sensor L1
const int L_S = 6; //sensor L 

int RS = digitalRead (R_S); //sensor R
int RS1 = digitalRead (R_S1); //sensor R near
int CS = digitalRead (S_S); //sensor S
int LS1 = digitalRead (L_S1); //sensor L near
int LS = digitalRead (L_S); //sensor L

String s;

void setup(){

  pinMode(LS, INPUT);
  pinMode(LS1, INPUT);
  pinMode(CS, INPUT);
  pinMode(RS, INPUT);
  pinMode(RS1, INPUT);
  pinMode(M_B1, OUTPUT);
  pinMode(M_B2, OUTPUT);
  pinMode(M_A1, OUTPUT);
  pinMode(M_A2, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(ENA, OUTPUT);

  Serial.begin(9600);
}

void loop(){

    int RS = digitalRead (R_S); //sensor R
    int RS1 = digitalRead (R_S1); //sensor R1
    int CS = digitalRead (S_S); //sensor S
    int LS1 = digitalRead (L_S1); //sensor L1
    int LS = digitalRead (L_S); //sensor L

    forwardCase();
    uTurnCase();
    rightCase();
    leftCase();

    if (LS == 1 && LS1==1  && CS == 0 &&  RS1 ==0  &&RS==1){SRTURN();}//(11001)
    else if (LS == 1 && LS1==1  && CS == 0 &&  RS1 ==1  &&RS==0){SRTURN();}//(11010)
    else if (LS == 1 && LS1==0  && CS == 1 &&  RS1 ==1  &&RS==0){SRTURN();}//(10110)
    else if (LS == 1 && LS1==0  && CS == 1 &&  RS1 ==0  &&RS==0){SRTURN();}//(10100)
    else if (LS == 1 && LS1==0  && CS == 0 &&  RS1 ==1  &&RS==0){SLTURN();}//(10010)
    else if (LS == 0 && LS1==1  && CS == 1 &&  RS1 ==0  &&RS==1){SRTURN();}

    //SLT
    else if (LS == 0 && LS1==0  && CS == 1 &&  RS1 ==0  &&RS==1){SLTURN();}
    else if (LS == 0 && LS1==1  && CS == 0 &&  RS1 ==1  &&RS==1){SLTURN();}
    else if (LS == 0 && LS1==0  && CS == 0 &&  RS1 ==0  &&RS==1){SLTURN();}//}
    else if (LS == 1 && LS1==0  && CS == 1 &&  RS1 ==1  &&RS==1){SLTURN();}
    else if (LS == 1 && LS1==0  && CS == 0 &&  RS1 ==1  &&RS==1){SLTURN();}//(10011)

    if((LS == 0 && LS1==0  && CS == 0 &&  RS1 ==0  && RS==0)){
      STOP();
      delay(5000);
      String str=shortestPath();
      tracePath(str);
      delay(5000);
      exit(1);
    }
}

String shortestPath(){
  
  int count=3;
  // s="LLLBLLLRBLLBSRSRS";
  String str;
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
  
  forwardCase();

  for(int i=0;i<sst.length();i++){
    if(sst[i]=='S') forwardCase(),Serial.println("Forward");
    else if(sst[i]=='L') leftCase(),Serial.println("Left");
    else if(sst[i]=='R') rightCase(),Serial.println("Right");
    else if(sst[i]=='B') uTurnCase(),Serial.println("Backward");
  }
}

void allBackCase(){
  while(true){
    STOP();
    Serial.println("Stop");
    if ((LS == 0 && LS1==0  && CS == 0 &&  RS1 ==0  && RS==0)) continue;
    else break;
  }
}

void uTurnCase(){
  int flag=0;
  while(true){
    UTURN();
    Serial.println("U Turn");
    if ((LS == 1 && LS1==1  && CS == 1 &&  RS1 ==1  && RS==1)) {flag=1;continue;}
    else break;
  }
  if(flag==1) s+="B";
}

void forwardCase(){
  int flag=0;
  while(true){
    FORWARD();
    Serial.println("Forward");
    if ((LS == 0 && LS1==0  && CS == 0 &&  RS1 ==1  &&RS==0)) {flag=1;continue;}
    else if (LS == 0 && LS1==0  && CS == 1 &&  RS1 ==1  &&RS==0) {flag=1;continue;}
    else if (LS == 0 && LS1==1  && CS == 0 &&  RS1 ==0  &&RS==0) {flag=1;continue;}
    else if (LS == 0 && LS1==1  && CS == 0 &&  RS1 ==1  &&RS==0) {flag=1;continue;}
    else if (LS == 0 && LS1==1  && CS == 1 &&  RS1 ==0  &&RS==0) {flag=1;continue;}
    else if (LS == 1 && LS1==1  && CS == 0 &&  RS1 ==1  &&RS==1) {flag=1;continue;}
    else if (LS == 1 && LS1==0  && CS == 1 &&  RS1 ==0  &&RS==1) {flag=1;continue;}
    else if (LS == 1 && LS1==0  && CS == 0 &&  RS1 ==0  &&RS==1) {flag=1;continue;}
    else break;
  }
  if(flag==1) s+="S";
}

void rightCase(){
  int flag=0;
  while(true){
    RT();
    Serial.println("Right");
    if (LS == 1 && LS1==1  && CS == 1 &&  RS1 ==0  && RS==0) {flag=1;continue;}
    else if (LS == 1 && LS1==1  && CS == 0 &&  RS1 ==0  && RS==0) {flag=1;continue;}
    else if (LS == 1 && LS1==1  && CS == 1 &&  RS1 ==1  && RS==0) {flag=1;continue;}
    else break;
  }
  if(flag==1) s+="R";
}

void leftCase(){
  int flag=0;
  while(true){
    LT();
    Serial.println("Left");
    if (LS == 0 && LS1==0  && CS == 0 &&  RS1 ==1  && RS==1) {flag=1;continue;}
    else if (LS == 0 && LS1==0  && CS == 1 &&  RS1 ==1  && RS==1) {flag=1;continue;}
    else if (LS == 0 && LS1==1  && CS == 1 &&  RS1 ==1  && RS==1) {flag=1;continue;}
  }
  if(flag==1) s+="L";
}

void FORWARD()
{
   digitalWrite(M_A1, HIGH);
   digitalWrite(M_A2, LOW);
   digitalWrite(M_B1, HIGH);
   digitalWrite(M_B2, LOW);  
   analogWrite (ENA,80);
   analogWrite (ENB,80);   
}

void RIGHTTURN()
{
  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, HIGH);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);  
  analogWrite (ENA,45);
  analogWrite (ENB,90);
} 
void LT()
{
   digitalWrite(M_A1, HIGH);
   digitalWrite(M_A2, LOW);
   digitalWrite(M_B1, LOW);
   digitalWrite(M_B2, HIGH);
   analogWrite (ENA,90);
   analogWrite (ENB,45);
   delay(60);
   
}
void INCH()
{
   digitalWrite(M_A1, HIGH);
   digitalWrite(M_A2, LOW);
   digitalWrite(M_B1, HIGH);
   digitalWrite(M_B2, LOW);
   analogWrite (ENA,50);
   analogWrite (ENB,50);
   delay(250);
   digitalWrite(M_A1, LOW);
   digitalWrite(M_A2, LOW);
   digitalWrite(M_B1, LOW);
   digitalWrite(M_B2, LOW);
   analogWrite (ENA,0);
   analogWrite (ENB,0);
}
void BACKINCH()
{
   digitalWrite(M_A1, LOW);
   digitalWrite(M_A2, HIGH);
   digitalWrite(M_B1, LOW);
   digitalWrite(M_B2, HIGH);
   analogWrite (ENA,55);
   analogWrite (ENB,55);
   delay(250);
   digitalWrite(M_A1, LOW);
   digitalWrite(M_A2, LOW);
   digitalWrite(M_B1, LOW);
   digitalWrite(M_B2, LOW);
   analogWrite (ENA,0);
   analogWrite (ENB,0);
   
}
void UTURN()//LEFT SE UTURN
{
   digitalWrite(M_A1, HIGH);
   digitalWrite(M_A2, LOW);
   digitalWrite(M_B1, LOW);
   digitalWrite(M_B2, HIGH);
   analogWrite (ENA,80);
   analogWrite (ENB,80);

}
void SRTURN()
{
  digitalWrite(M_A1, LOW);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);  
  analogWrite (ENA,0);
  analogWrite (ENB,50);
}
/*
void SLONGRTURN()
{
  digitalWrite(M_A1, HIGH);
  digitalWrite(M_A2, LOW);
  digitalWrite(M_B1, HIGH);
  digitalWrite(M_B2, LOW);  
  analogWrite (ENA,40);
  analogWrite (ENB,80);
}
*/
void SLTURN()
{
   digitalWrite(M_A1, HIGH);
   digitalWrite(M_A2, LOW);
   digitalWrite(M_B1, LOW);
   digitalWrite(M_B2, LOW);
   analogWrite (ENA,70);
   analogWrite (ENB,0); 
}
void STOP()
{
   digitalWrite(M_A1, LOW);
   digitalWrite(M_A2, LOW);
   digitalWrite(M_B1, LOW);
   digitalWrite(M_B2, LOW);
   analogWrite (ENA,0);
   analogWrite (ENB,0); 
}

void ALLBLACK()
{
  INCH();
    
   int RS = digitalRead (R_S); //sensor R
   int RS1 = digitalRead (R_S1); //sensor Rs1
   int CS = digitalRead (S_S); //sensor S
   int LS1 = digitalRead (L_S1); //sensor ls1
   int LS = digitalRead (L_S); //sensor L
   delay(500);
   if (LS == 1 && LS1==1  && CS == 1 &&  RS1 ==1  &&RS==1)
     {
      BACKINCH();
      LT();
      delay(250);
     }
    else if(LS == 1 && LS1==1  && CS == 0 &&  RS1 ==1  &&RS==1)//+
     {
      BACKINCH();
      LT();
      delay(650);
      
     }
    else if(LS == 0 && LS1==0  && CS == 0 &&  RS1 ==0  &&RS==0)//STOP
     {
      BACKINCH();
      STOP();
      delay(600);
      
     }
     
    else
     { BACKINCH();
       LT ();
       delay(600);
       }
  }

void RT()
{
  INCH();
   int RS = digitalRead (R_S); //sensor R
   int RS1 = digitalRead (R_S1); //sensor R
   int CS = digitalRead (S_S); //sensor S
   int LS1 = digitalRead (L_S1); //sensor R
   int LS = digitalRead (L_S); //sensor L
   delay(500);
   
   {
   if(LS == 1 && LS1==1  && CS == 1 &&  RS1 ==1  &&RS==1)
     { BACKINCH();
      RIGHTTURN();
      delay(650);
   }
   else if (LS == 1 && LS1==1  && CS == 0 &&  RS1 ==1  &&RS==1)
   {
    BACKINCH();
   
    FORWARD();
   delay(500);
   }
   else if(LS == 1 && LS1==0  && CS == 0 &&  RS1 ==1  &&RS==1)
   {
    BACKINCH();
    FORWARD();
   delay(500);
   }
   else if(LS == 1 && LS1==1  && CS == 0 &&  RS1 ==0  &&RS==1)
   {
    BACKINCH();
    FORWARD();
   delay(500);
   }
    else if(LS == 1 && LS1==1  && CS == 0 &&  RS1 ==0  &&RS==0)
     { BACKINCH();
    RIGHTTURN();
   delay(500);
   }
   else
   { BACKINCH();
    RIGHTTURN();
   delay(500);
   }
   }
}
