#include "dance2.h"
#include "EMOtto.h"
#include "DFRobotDFPlayerMini.h"
//-- cantstopthefeeling
extern Otto Otto;
extern DFRobotDFPlayerMini myDFPlayer;

unsigned long music2Start = 0;
bool music2Started = false;
bool dance2Active = false;
bool music2Finished = false;
bool dance2Finished = false;
int danceIndex = 0;
unsigned long stepStart = 0;


typedef struct {
  void (*moveFunc)();
  unsigned long duration;
} DanceMove;

void move1() { Otto.swing(4,1000,30); }
void move2() { Otto.updown(3,1000,30); }
void move3() { Otto.swing(4,1000,30); }
void move4() { Otto.updown(3,1000,30);Otto.home(); }
void move5() {   
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.flapping(1,1000,30,1);
  Otto.flapping(1,1000,30,-1);
  Otto.home(); }
void move6() {
  Otto.jump(1,700);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.flapping(1,1000,30,1);
  Otto.flapping(1,1000,30,-1);
  Otto.home();}
void move7() {
  Otto.jump(1,700);
  Otto.home();
  Otto.jump(1,1000);
  Otto.moonwalker(1,2000,30,1);
  Otto.moonwalker(1,2000,30,-1);
  Otto.moonwalker(1,2000,30,1);
  Otto.moonwalker(1,2000,30,-1);
  Otto.moonwalker(1,2000,30,1);
  Otto.ascendingTurn(2,2000,30); 
  Otto.home(); }
void move8() {
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.home(); }
void move9() {
  Otto.jitter(4,1000,30);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.home();}
void move10() {
  Otto.jitter(4,1000,30);
  Otto.updown(2,1000,30);
  Otto.walk(2,1000,1);
  Otto.updown(2,1000,30);
  Otto.walk(2,1000,-1);
  Otto.home();}
void move11() {
  Otto.swing(2,1000,30);
  Otto.jitter(2,1000,30);
  Otto.walk(2,1000,1);
  Otto.walk(2,1000,-1);
  Otto.swing(2,1000,30);
  Otto.jitter(2,1000,30);
  Otto.walk(2,1000,1); 
  Otto.walk(2,1000,-1); }
void move12() {  
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.flapping(1,1000,30,1);
  Otto.flapping(1,1000,30,-1);
  Otto.home();}
void move13() {  
  Otto.jump(1,700);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.flapping(1,1000,30,1);
  Otto.flapping(1,1000,30,-1);
  Otto.home();
  Otto.jump(1,700);
  Otto.home();}
void move14() {  
  Otto.jump(1,1000);
  Otto.moonwalker(1,2000,30,1);
  Otto.moonwalker(1,2000,30,-1);
  Otto.moonwalker(1,2000,30,1);
  Otto.moonwalker(1,2000,30,-1);
  Otto.moonwalker(1,2000,30,1); 
  Otto.ascendingTurn(2,2000,30); 
  Otto.home();}
void move15() {  
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.home();}
void move16() {  
  Otto.jitter(4,1000,30);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.home();}
void move17() {  
  Otto.jitter(4,1000,30);
  Otto.updown(2,1000,30);
  Otto.walk(2,1000,1);
  Otto.updown(2,1000,30);
  Otto.walk(2,1000,-1);
  Otto.jitter(4,1000,30);
  Otto.updown(2,1000,30);
  Otto.walk(2,1000,1);
  Otto.updown(2,1000,30);
  Otto.walk(2,1000,-1);
  Otto.home();}
void move18() {  
  Otto.flapping(1,1000,30,1);
  Otto.flapping(1,1000,30,-1);
  Otto.flapping(1,1000,30,1);
  Otto.flapping(1,1000,30,-1); 
  Otto.swing(10,1000,30); }
 void move19() {  
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.flapping(1,1000,30,1);
  Otto.flapping(1,1000,30,-1);
  Otto.home();}
void move20() {  
  Otto.jump(1,700);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.crusaito(1,1000,30,1);
  Otto.crusaito(1,1000,30,-1);
  Otto.flapping(1,1000,30,1);
  Otto.flapping(1,1000,30,-1);
  Otto.home();}
void move21() {  
  Otto.jitter(4,1000,30);
  Otto.updown(2,1000,30);
  Otto.walk(2,1000,1);
  Otto.updown(2,1000,30);
  Otto.walk(2,1000,-1);
  Otto.jitter(4,1000,30);
  Otto.updown(2,1000,30);
  Otto.walk(2,1000,1);
  Otto.updown(2,1000,30);
  Otto.walk(2,1000,-1);
  Otto.home();
  Otto.updown(4,1000,30);
  Otto.home(); }

void moveEnd() { Otto.home(); }

static  DanceMove steps[] = {
  {move1, 4400},
  {move2, 3500},
  {move3, 4400},
  {move4, 4000},
  {move5, 6700},
  {move6, 6000},
  {move7, 17300},
  {move8, 4000},
  {move9, 8000},
  {move10, 12000},
  {move11, 16700},
  {move12, 6000},
  {move13, 7400},
  {move14, 15500},
  {move15, 4000},
  {move16, 8000},
  {move17, 24000},
  {move18, 14700},
  {move19, 6000},
  {move20, 6700},
  {move21, 28000},

  {moveEnd, 1000}
};

const int NUM_STEPS = sizeof(steps) / sizeof(steps[0]);

void startDance2() {
  Serial.println(">> Inizio Dance2");
  myDFPlayer.play(35);  // Avvia musica
  music2Start = millis();
  danceIndex = -1;
  dance2Finished = false;
  music2Finished = false;
  dance2Active = true;
}



void updateDance2() {
  if (dance2Finished) return;

  unsigned long now = millis();

  if (danceIndex == -1 && now - music2Start > 6000 && dance2Active) {
    danceIndex = 0;
    stepStart = now;
    steps[danceIndex].moveFunc();
    return;
  }

  if (danceIndex >= 0 && now - stepStart >= steps[danceIndex].duration) {
    danceIndex++;

    // Se la danza è stata fermata, quando finisce il movimento corrente termina
    if (!dance2Active) {
      dance2Finished = true;
      Otto.home();
      Serial.println(">> Dance2 interrotta dopo movimento.");
      return;
    }

    if (danceIndex < NUM_STEPS) {
      steps[danceIndex].moveFunc();
      stepStart = now;
    } else {
      dance2Finished = true;
      dance2Active = false;
           danceIndex = -1; 
      Otto.home();
      Serial.println(">> Fine Dance2");
    }
  }
}




void stopDance2() {
  dance2Active = false;
  music2Finished = true;
  dance2Finished = true;
  myDFPlayer.stop();
  danceIndex = -1;  
  Otto.home();
  Serial.println(">> Dance2 stop richiesta.");
}



void toggleDance2() {
  if (dance2Active) {
    stopDance2();
  } else {
    startDance2();
  }
}

void updateMusic2Status() {
  if (!dance2Active) return;
  if (myDFPlayer.available()) {
    int type = myDFPlayer.readType();
    int value = myDFPlayer.read();
    if (type == DFPlayerPlayFinished && value == 35) {  // 35 è il brano dance2
      Serial.println(">> Musica dance2 finita");
      music2Finished = true;
      stopDance2();
    }
  }
}

bool isDance2Finished() {
  return dance2Finished;
}

