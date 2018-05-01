// Juho Valkama
// Clock basics
// It lacks the setting of the time and the alarm fuction

int tunnit=0; 
int minuutit; 
int sekunnit;
// Hälytyksen ajoitus
int hal_tunnit;
int hal_minuutit;

void setup() { 
  Serial.begin(9600);
} 

// Tänne hälytys
void start_alarm(){
}

void loop() {  
  sekunnit=sekunnit+1; 
  Serial.print("AIKA:"); 
  Serial.print(tunnit); 
  Serial.print(":"); 
  Serial.print(minuutit); 
  Serial.print(":"); 
  Serial.print(sekunnit);
  Serial.print("\n");
  delay(1000);
  
  if(sekunnit == 60){ 
   sekunnit=0; 
   minuutit=minuutit+1; 
  } 
  if(minuutit == 60) 
  { 
   minuutit=0; 
   tunnit=tunnit+1; 
  } 
  if(tunnit == 25) 
  { 
   tunnit=0; 
  }

  // Jos aika == hälytys, niin suorita hälytys
  if (tunnit == hal_tunnit && minuutit == hal_minuutit) {
    start_alarm();
  }
  
}