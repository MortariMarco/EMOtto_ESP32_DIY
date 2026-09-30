#include "dance4.h"
#include "EMOtto.h"
#include "DFRobotDFPlayerMini.h"
//-- Happy
extern Otto Otto;
extern DFRobotDFPlayerMini myDFPlayer;

unsigned long music4Start = 0;
bool music4Started = false;
bool dance4Active = false;
bool music4Finished = false;
bool dance4Finished = false;
int danceIndex4 = 0;
unsigned long stepStart4 = 0;


typedef struct {
  void (*moveFunc)();
  unsigned long duration4;
} Dance4Move;

void move1_4() {
  Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
}//150
void move2_4() {
 Otto.home();
  Otto.moonwalker(1,1000,30,1);
  Otto.moonwalker(1,1000,30,-1);
  Otto.moonwalker(1,1000,30,1); 
 }//150
void move3_4() { 
   Otto.home();
  Otto.swing(3,1000,30);
 }//150
void move4_4() { 
  Otto.home();
  Otto.swing(3,1000,30);
  Otto.home();
 }
void move5_4() {   
Otto.ascendingTurn(8,870,30);
  Otto.home();
  Otto.jitter(8,900,30);
  Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
 }//150
void move6_4() {
  Otto.home();
  Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
}//-pausa 150
void move7_4() {
  Otto.home();
  Otto.swing(3,1000,30);
 }// pausa 150
void move8_4() {
  Otto.home();
  Otto.swing(3,1000,30);
  Otto.home();
  Otto.ascendingTurn(8,870,30);
  Otto.home();
  }
void move9_4() {
 Otto.jitter(8,900,30);
  Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
}// pausa 150
void move10_4() {
   Otto.home();
  Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
}// 150
void move11_4() {
    Otto.home();
  Otto.swing(3,1000,30);
 }//150
void move12_4() {  
Otto.home();
  Otto.swing(3,1000,30);
  Otto.home();
  Otto.ascendingTurn(8,870,30);
  Otto.home();
}
void move13_4() {  
  Otto.jitter(8,900,30);
  Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
}//150
void move14_4() {  
   Otto.home();
  Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
}//150
void move15_4() {  
  Otto.home();
  Otto.swing(3,1000,30);
}// 150
void move16_4() {  
  Otto.home();
  Otto.swing(3,1000,30);
}//150
void move17_4() {  
  Otto.home();
  Otto.updown(8,870,30);
  Otto.tiptoeSwing(7,900,30);
}//150
void move18_4() {  
  Otto.home();
  Otto.ascendingTurn(8,870,30);
 }//100
 void move19_4() {  
   Otto.jitter(8,900,30);
  }//500
void move20_4() {  
 Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
 }//150
void move21_4() {  
    Otto.home();
  Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
  }//150
void move22_4() {  
   Otto.home();
  Otto.swing(3,1000,30);
  }//150
void move23_4() {  
  Otto.home();
  Otto.swing(3,1000,30);
  }//150
void move24_4() {  
    Otto.home();
  Otto.updown(8,870,30);
  Otto.tiptoeSwing(7,900,30);
  }//150
  void move25_4() {  
   Otto.home();
  Otto.ascendingTurn(8,870,30);
  }//100
  void move26_4() {  
 Otto.jitter(8,900,30);
  }//500
  void move27_4() {  
  Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
  }//150
    void move28_4() {  
 Otto.home();
  Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
  }//150
    void move29_4() {  
    Otto.home();
  Otto.swing(3,1000,30);
  }//150
    void move30_4() {  
  Otto.home();
  Otto.swing(3,1000,30);
  }//150
    void move31_4() {  
    Otto.home();
  Otto.updown(8,870,30);
  Otto.tiptoeSwing(7,900,30);
  }//500
      void move32_4() {  
    Otto.home();
  Otto.moonwalker(1,950,30,1);
  Otto.moonwalker(1,950,30,-1);
  Otto.moonwalker(1,950,30,1); 
  }//150
      void move33_4() {  
  Otto.home();
  Otto.moonwalker(1,1000,30,1);
  Otto.moonwalker(1,1000,30,-1);
  Otto.moonwalker(1,1000,30,1); 
  }//150
      void move34_4() {  
  Otto.home();
  Otto.swing(3,1000,30);
  }//150
      void move35_4() {  
Otto.home();
  Otto.swing(3,1000,30);
  Otto.home();
  }//
        void move36_4() {  
Otto.ascendingTurn(8,870,30);
  Otto.home();
  Otto.jitter(8,900,30);
  }//150
        void move37_4() {  
  Otto.home();
  Otto.updown(8,870,30);
  Otto.tiptoeSwing(7,900,30);
  }//150
        void move38_4() {  
Otto.home();
  }//
 
void moveEnd_4() { Otto.home(); }

static Dance4Move steps[] = {
  {move1_4, 3000},
  {move2_4, 3150},
  {move3_4, 3150},
  {move4_4, 3000},
  {move5_4, 17160},
  {move6_4, 3000},
  {move7_4, 3150},
  {move8_4, 9960},
  {move9_4, 10200},
  {move10_4, 3000},
  {move11_4, 3150},
  {move12_4, 9960},
  {move13_4, 10200},
  {move14_4, 3000},
  {move15_4, 3150},
  {move16_4, 3150},
  {move17_4, 13410},
  {move18_4, 7060},
  {move19_4, 7700},
  {move20_4, 3000},
  {move21_4, 3000},
  {move22_4, 3150},
  {move23_4, 3150},
  {move24_4, 13410},
  {move25_4, 7060},
  {move26_4, 7700},
  {move27_4, 3000 },
  {move28_4, 3000},
  {move29_4, 3150},
  {move30_4, 3150},
  {move31_4, 13760},
  {move32_4, 3000},
  {move33_4, 3150},
  {move34_4, 3150},
  {move35_4, 3000},
  {move36_4, 14310},
  {move37_4, 13410},
  {move38_4, 1000},

  {moveEnd_4, 1000}
};

const int NUM_STEPS4 = sizeof(steps) / sizeof(steps[0]);

void startDance4() {
  Serial.println(">> Inizio Dance4");
  myDFPlayer.play(37);  // Avvia musica
  music4Start = millis();
  danceIndex4 = -1;
  dance4Finished = false;
  music4Finished = false;
  dance4Active = true;
}



void updateDance4() {
  if (dance4Finished) return;

  unsigned long now = millis();

  if (danceIndex4 == -1 && now - music4Start > 1000 && dance4Active) {
    danceIndex4 = 0;
    stepStart4 = now;
    steps[danceIndex4].moveFunc();
    return;
  }

  if (danceIndex4 >= 0 && now - stepStart4 >= steps[danceIndex4].duration4) {
    danceIndex4++;

    // Se la danza è stata fermata, quando finisce il movimento corrente termina
    if (!dance4Active) {
      dance4Finished = true;
      Otto.home();
      Serial.println(">> Dance4 interrotta dopo movimento.");
      return;
    }

    if (danceIndex4 < NUM_STEPS4) {
      steps[danceIndex4].moveFunc();
      stepStart4 = now;
    } else {
      dance4Finished = true;
      dance4Active = false;
           danceIndex4 = -1; 
      Otto.home();
      Serial.println(">> Fine Dance4");
    }
  }
}




void stopDance4() {
  dance4Active = false;
  music4Finished = true;
  dance4Finished = true;
  myDFPlayer.stop();
  danceIndex4 = -1;  
  Otto.home();
  Serial.println(">> Dance4 stop richiesta.");
}



void toggleDance4() {
  if (dance4Active) {
    stopDance4();
  } else {
    startDance4();
  }
}

void updateMusic4Status() {
  if (!dance4Active) return;
  if (myDFPlayer.available()) {
    int type = myDFPlayer.readType();
    int value = myDFPlayer.read();
    if (type == DFPlayerPlayFinished && value == 37) {  // 37 è il brano dance4
      Serial.println(">> Musica dance4 finita");
      music4Finished = true;
      stopDance4();
    }
  }
}

bool isDance4Finished() {
  return dance4Finished;
}