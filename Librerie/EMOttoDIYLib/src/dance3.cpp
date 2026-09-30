#include "dance3.h"
#include "EMOtto.h"
#include "DFRobotDFPlayerMini.h"
//-- Happy
extern Otto Otto;
extern DFRobotDFPlayerMini myDFPlayer;

unsigned long music3Start = 0;
bool music3Started = false;
bool dance3Active = false;
bool music3Finished = false;
bool dance3Finished = false;
int danceIndex3 = 0;
unsigned long stepStart3 = 0;


typedef struct {
  void (*moveFunc)();
  unsigned long duration3;
} Dance3Move;

void move1_1() {
    Otto.jitter(2,750,20);
  Otto.crusaito(1,800,30,1);
  Otto.crusaito(1,800,30,-1);
  Otto.crusaito(1,800,30,1);
}
void move2_1() {
  Otto.walk(1,1500,-1);
  Otto.walk(2,1000,1);
 }
void move3_1() { 
  Otto.moonwalker(1,600,30,1);
  Otto.moonwalker(1,600,30,-1);
  Otto.moonwalker(1,600,30,1);
  Otto.moonwalker(1,600,30,-1);
 }
void move4_1() { 
  Otto.walk(1,1500,-1);
  Otto.walk(2,1000,1);
 }
void move5_1() {   
  Otto.moonwalker(1,600,30,1);
  Otto.moonwalker(1,600,30,-1);
  Otto.moonwalker(1,600,30,1);
  Otto.moonwalker(1,600,30,-1);
 }
void move6_1() {
Otto.walk(1,1500,-1);
  Otto.walk(2,1000,1);
  Otto.shakeLeg(1,700,1);
  Otto.shakeLeg(1,700,-1);
}//-pausa 1000
void move7_1() {
  Otto.home();
  Otto.moonwalker(1,3000,50,1);
  Otto.moonwalker(1,3000,50,-1);
 }// pausa 100
void move8_1() {
  Otto.moonwalker(1,3000,50,-1);
  Otto.moonwalker(1,3000,50,1);
  }
void move9_1() {
Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
}// pausa 500
void move10_1() {
  Otto.crusaito(1,800,30,1);
  Otto.crusaito(1,800,30,-1);
  Otto.crusaito(1,800,30,1);
}// 300
void move11_1() {
  Otto.walk(1,1500,-1);
  Otto.walk(2,1000,1);
 }
void move12_1() {  
  Otto.moonwalker(1,600,30,1);
  Otto.moonwalker(1,600,30,-1);
  Otto.moonwalker(1,600,30,1);
  Otto.moonwalker(1,600,30,-1);
}
void move13_1() {  
  Otto.walk(1,1500,-1);
  Otto.walk(2,1000,1);
}
void move14_1() {  
 Otto.moonwalker(1,600,30,1);
  Otto.moonwalker(1,600,30,-1);
  Otto.moonwalker(1,600,30,1);
  Otto.moonwalker(1,600,30,-1);
}
void move15_1() {  
  Otto.walk(1,1500,-1);
  Otto.walk(2,1000,1);
  Otto.shakeLeg(1,700,1);
  Otto.shakeLeg(1,700,-1);
}// 1000
void move16_1() {  
  Otto.home();
  Otto.moonwalker(1,3000,50,1);
  Otto.moonwalker(1,3000,50,-1);
}//100
void move17_1() {  
  Otto.moonwalker(1,3000,50,-1);
  Otto.moonwalker(1,3000,50,1);
}
void move18_1() {  
Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
 }
 void move19_1() {  
    Otto.updown(3,900,30);
  Otto.jitter(3,1000,20);
  Otto.updown(3,900,30);
  Otto.jitter(3,1000,20);
  }
void move20_1() {  
 Otto.jump(1,400);
  Otto.jump(1,400);
  Otto.jump(1,400);
  Otto.jump(1,400);
  Otto.jitter(4,800,20);
  Otto.jump(1,400);
  Otto.jump(1,400);
  Otto.jump(1,400);
  Otto.jump(1,400);
  Otto.jitter(2,800,20);
 }//1500
void move21_1() {  
   Otto.home();
  Otto.moonwalker(1,3000,50,1);
  Otto.moonwalker(1,3000,50,-1);
  }//100
void move22_1() {  
  Otto.moonwalker(1,3000,50,-1);
  Otto.moonwalker(1,3000,50,1);
  }//
void move23_1() {  
 Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
  }//
void move24_1() {  
   Otto.moonwalker(1,3000,50,1);
  Otto.moonwalker(1,3000,50,-1);
  }//100
  void move25_1() {  
   Otto.moonwalker(1,3000,50,-1);
  Otto.moonwalker(1,3000,50,1);
  }//
  void move26_1() {  
   Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
  }//
  void move27_1() {  
 Otto.home();
  Otto.updown(3,900,30);
  Otto.jitter(3,1000,20);
  Otto.updown(3,900,30);
  Otto.jitter(3,1000,20);
  }//
    void move28_1() {  
   Otto.moonwalker(1,3000,50,1);
  Otto.moonwalker(1,3000,50,-1);
  }//100
    void move29_1() {  
   Otto.moonwalker(1,3000,50,-1);
  Otto.moonwalker(1,3000,50,1);
  }//
    void move30_1() {  
   Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
  }//
    void move31_1() {  
   Otto.moonwalker(1,3000,50,1);
  Otto.moonwalker(1,3000,50,-1);
  }//100
      void move32_1() {  
   Otto.moonwalker(1,3000,50,-1);
  Otto.moonwalker(1,3000,50,1);
  }//
      void move33_1() {  
   Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.jump(1,370);
  Otto.bend(1,100,1);
  Otto.bend(1,100,-1);
  Otto.home();
  }//
 
void moveEnd_1() { Otto.home(); }

static Dance3Move steps[] = {
  {move1_1, 4200},
  {move2_1, 3500},
  {move3_1, 2400},
  {move4_1, 3500},
  {move5_1, 2400},
  {move6_1, 5900},
  {move7_1, 6100},
  {move8_1, 6000},
  {move9_1, 3960},
  {move10_1, 2700},
  {move11_1, 3500},
  {move12_1, 2400},
  {move13_1, 3500},
  {move14_1, 2400},
  {move15_1, 6000},
  {move16_1, 6100},
  {move17_1, 6000},
  {move18_1, 3360},
  {move19_1, 11400},
  {move20_1, 9500},
  {move21_1, 6100},
  {move22_1, 6000},
  {move23_1, 3360},
  {move24_1, 6100},
  {move25_1, 6000},
  {move26_1, 3360},
  {move27_1, 11400 },
    {move28_1, 6100},
      {move29_1, 6000},
        {move30_1, 3360},
 {move31_1, 6100},
 {move32_1, 6000},
 {move33_1, 3360},

  {moveEnd_1, 1000}
};

const int NUM_STEPS3 = sizeof(steps) / sizeof(steps[0]);

void startDance3() {
  Serial.println(">> Inizio Dance3");
  myDFPlayer.play(36);  // Avvia musica
  music3Start = millis();
  danceIndex3 = -1;
  dance3Finished = false;
  music3Finished = false;
  dance3Active = true;
}



void updateDance3() {
  if (dance3Finished) return;

  unsigned long now = millis();

  if (danceIndex3 == -1 && now - music3Start > 6000 && dance3Active) {
    danceIndex3 = 0;
    stepStart3 = now;
    steps[danceIndex3].moveFunc();
    return;
  }

  if (danceIndex3 >= 0 && now - stepStart3 >= steps[danceIndex3].duration3) {
    danceIndex3++;

    // Se la danza è stata fermata, quando finisce il movimento corrente termina
    if (!dance3Active) {
      dance3Finished = true;
      Otto.home();
      Serial.println(">> Dance3 interrotta dopo movimento.");
      return;
    }

    if (danceIndex3 < NUM_STEPS3) {
      steps[danceIndex3].moveFunc();
      stepStart3 = now;
    } else {
      dance3Finished = true;
      dance3Active = false;
           danceIndex3 = -1; 
      Otto.home();
      Serial.println(">> Fine Dance3");
    }
  }
}




void stopDance3() {
  dance3Active = false;
  music3Finished = true;
  dance3Finished = true;
  myDFPlayer.stop();
  danceIndex3 = -1;  
  Otto.home();
  Serial.println(">> Dance3 stop richiesta.");
}



void toggleDance3() {
  if (dance3Active) {
    stopDance3();
  } else {
    startDance3();
  }
}

void updateMusic3Status() {
  if (!dance3Active) return;
  if (myDFPlayer.available()) {
    int type = myDFPlayer.readType();
    int value = myDFPlayer.read();
    if (type == DFPlayerPlayFinished && value == 36) {  // 36 è il brano dance3
      Serial.println(">> Musica dance3 finita");
      music3Finished = true;
      stopDance3();
    }
  }
}

bool isDance3Finished() {
  return dance3Finished;
}