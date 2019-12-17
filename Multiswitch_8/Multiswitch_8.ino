/*
   Futaba_Multi-Switch_8
   Ziege-One
   v1.0
   www.Ziege-One.de
 
 Arduino pro Mini 5v/16mHz w/ Atmega 328

 
 /////Pin Belegung////
 D0: 
 D1: 
 D2:  Einstellung Kanal8  Memory Funktion (0=an)
 D3:  Eingang von Empfänger
 D4:  Ausgang Kanal 8
 D5:  Ausgang Kanal 7
 D6:  Ausgang Kanal 6
 D7:  Ausgang Kanal 5
 D8:  Ausgang Kanal 4
 D9:  Ausgang Kanal 3
 D10: Ausgang Kanal 2
 D11: Ausgang Kanal 1
 D12: 
 D13: LED
 
 A0: 
 A1: 
 A2: 
 A3: 
 A4: 
 A5: 
 
 */
 
// ======== Futaba_Multi-Switch_8  =======================================
#define kanaele 8    //Anzahl der Kanäle
int value1[kanaele]; //Speicher 1
int value2[kanaele]; //Speicher 2
bool memory_on;      //Einstellung Kanal8  Memory Funktion (1=an)
bool memory;         //Flanken Merker
bool memorylast;     //Speicher für Kanal 8

// ======== Setup & Initialisierung =======================================
void setup()
{
  Serial.begin(9600);
  pinMode(2, INPUT);  //Einstellung Kanal8  Memory Funktion (0=an)
  pinMode(3, INPUT);  //Eingang von Empfänger
  pinMode(4, OUTPUT); //Ausgang Kanal 8
  pinMode(5, OUTPUT); //Ausgang Kanal 7
  pinMode(6, OUTPUT); //Ausgang Kanal 6
  pinMode(7, OUTPUT); //Ausgang Kanal 5
  pinMode(8, OUTPUT); //Ausgang Kanal 4
  pinMode(9, OUTPUT); //Ausgang Kanal 3
  pinMode(10, OUTPUT);//Ausgang Kanal 2
  pinMode(11, OUTPUT);//Ausgang Kanal 1

  digitalWrite(2, HIGH);
}

// ======== Haupt Schleife  =======================================
void loop()
{
  // Schleife 1 
  while(pulseIn(3, HIGH) > 1000){} //Warten auf Startimpuls <1ms
  for(int x=0; x<=kanaele-1; x++) //Schleife bis alle Kanäle gespeichert sind
  {
    value1[x]=pulseIn(3, HIGH);
  }

  // Schleife 2 
  while(pulseIn(3, HIGH) > 1000){} //Warten auf Startimpuls <1ms
  for(int y=0; y<=kanaele-1; y++) //Schleife bis alle Kanäle gespeichert sind
  {
    value2[y]=pulseIn(3, HIGH);
  }
  
  memory_on = not digitalRead(2); //Einstellung Kanal8  Memory Funktion (0=an)
  
  for(int z=0; z<=kanaele-1; z++)
  {
  if ((value1[z] < 1100) && (value1[z] > 1000) && (value2[z] < 1100) && (value2[z] > 1000)) //Kanal x = 1
  {
    if  (z == 0 && memory_on) //Kanal 8 = 1 und Memory Funktion
    {
       if (not memory) //Flanke von 0 nach 1
       { 
          if (memorylast == LOW) //War Ausgang 8 = 0 dann Einschalten
          {
          digitalWrite(z+4, HIGH); //Ausgang schreiben
          memorylast = true;
          }
          else                   //War Ausgang 8 = 1 dann Ausschalten
          {
          digitalWrite(z+4, LOW); //Ausgang schreiben
          memorylast = false;
          }
       } 
       memory = true;  //Flanken Merker = 1
    } 
    else
    {
      digitalWrite(z+4, HIGH); //Ausgang schreiben
    }
  }
  else if ((value1[z] < 2000) && (value1[z] > 1600) && (value2[z] < 2000) && (value2[z] > 1600)) //Kanal x = 0
  {
    if  (z == 0 && memory_on) //Kanal 8 = 0 und Memory Funktion
    {
       memory = false;  //Flanken Merker = 0
    } 
    else
    {
      digitalWrite(z+4, LOW); //Ausgang schreiben
    }
  }
  }
}
