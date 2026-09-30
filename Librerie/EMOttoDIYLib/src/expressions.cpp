#include <Arduino.h>
#include <TFT_eSPI.h>
#include <EMOtto.h>
#include "expressions.h"
#include "modes.h"
#include "colors.h"
#include "draw_utils.h"
#include "sleep.h"
#include "dance.h"

extern void forceHome();
extern TFT_eSPI tft;
extern Otto Otto;
extern ExpressionType expression;

// Lacrime
extern int tearY;
extern const int tearStartY;
extern const int tearEndY;
extern unsigned long lastTearTime;
extern const int tearSpeed;
extern bool tearJustStarted;
extern bool tearVisible;
extern bool tearExploding;
extern int explosionStep;
extern const int maxExplosionSteps;

//lacrimuccia
extern bool yawnRunning;     // indica se l’animazione sbadiglio è in corso
extern unsigned long yawnStartTime;
extern int yawnPhase;            // fasi dell’animazione sbadiglio
extern bool yawnTearActive;
extern int yawnTearY;
extern unsigned long lastYawnTearUpdate;
// Cuori
extern unsigned long lastHeartbeatTime;
extern int heartbeatIndex;
extern int heartbeatSizes[];
extern int heartbeatDelays[];
extern const int numHeartbeatFrames;
extern bool isInLove;
extern bool lastBluetoothState;
// cantante
extern bool singerIntroDone;
extern unsigned long singerIntroStart;
// === Espressioni (volto) ===

void drawNormal() {
  drawEyes();
  drawSmile();
  drawBrowsNormal();
  drawBlush();
 }

void drawAngry() {
  drawEyes();
  drawStraightMouth();
  drawBrowsAngry();
 }

void drawSurprised() {
  drawEyes();
  drawOMouth();
  drawBrowsSurprised();
}

void drawSad() {
  drawEyes();
  drawSadMouth();
  drawBrowsSad();
  updateTears();
}

void drawInLove() {
 updateHeartEyes();
  drawSmile();
  drawBlush();
}
void drawAvoid() {
  drawEyes();
  drawStraightMouth();
  drawBrowsAngry();
}
void drawDance() {            // occhi + bocca “felice”
  drawEyes();
  drawMouthOpenSmile();
  drawBrowsNormal();
  drawBlush();
}
void drawDisgust() {
  drawEyesDisgust();
  drawBrowsDisgust();
  drawDisgustMouth();
 }
void drawEmbarrassed() {
  drawEyes();
  drawEyelids(20);
  drawBlush();                 // guance rosse
  drawEmbarrassedMouth();     // bocca timida
  drawBrowsEmbarrassed();     // sopracciglia inarcate
}
void drawBored() {
  drawEyesBored();
  drawBoredMouth();
  drawBlush();
  drawBrowsBored();
}
void drawAnxious() {
  drawBrowsAnxious();
  drawEyesAnxious();
  drawWavyMouth(120, 160, 60, 5);  // centro bocca (x=120,y=160), larghezza 60, ampiezza 5
}
void drawNostalgic() {
  drawEyesNostalgic();     // occhi sognanti, verso l’alto
  drawBrowsNostalgic();    // sopracciglia leggermente inclinate
  drawMouthNostalgic();    // bocca morbida, curvata in giù
  drawBlush();             // opzionale: guance rosa
}

void drawSinger() {
   drawEyes();
   drawEyebrowsRaised();    // Sopracciglia
   drawSingingMouth();
}

void drawExpression(ExpressionType expression) {
  uint16_t bgColor = getSkinColor(expression);
 tft.fillScreen(bgColor);

  switch (expression) {
    case EXP_NORMAL:    drawNormal();    break;
    case EXP_ANGRY:     drawAngry();     break;
    case EXP_SURPRISED: drawSurprised(); break;
    case EXP_SAD:       drawSad();       break;
    case EXP_DISGUST:   drawDisgust();   break;
    case EXP_EMBARRASSED: drawEmbarrassed(); break;
    case EXP_BORED:     drawBored();     break;
    case EXP_ANXIOUS:   drawAnxious();   break;
    case EXP_LOVE:      drawInLove();    break;
    case EXP_DANCE:     drawDance();     break;
    case EXP_AVOID:     drawAvoid();     break;
	  case EXP_FOLLOW:    drawInLove();    break;
    case EXP_NOSTALGIC: drawNostalgic(); break;
    case EXP_SINGER:    drawSinger();    break;
    }
     }
void performExpression(ExpressionType type) {
  expression = type;
  drawExpression(type);
  Serial.print(">> performExpression, tipo = ");
  Serial.println(type);

  switch (type) {
    case EXP_NORMAL:
      Serial.println("   NORMALE");
     // myDFPlayer.play(20);//wow e tutto bellissimo
   //    Otto.swing(2, 1000, 20);
      forceHome();
      break;
    case EXP_ANGRY:
      Serial.println("   ARRABBIATO");
      myDFPlayer.play(17); //sono arrabbiato 
      Otto.swing(2, 1000, 20);
      forceHome();
      break;
    case EXP_SURPRISED:
      Serial.println("   SORPRESO");
      myDFPlayer.play(7);// che paura aiuto
      Otto.updown(2, 1500, 20);  // 20 = H "HEIGHT of movement"T 
      forceHome();
      break;
    case EXP_SAD:
      Serial.println("   TRISTE");
      myDFPlayer.play(19); // sono triste uffa
      Otto.flapping(2, 1000, 20,1);
      Otto.flapping(2, 1000, 20,-1);
      forceHome();
      break;
    case EXP_DISGUST:
       Serial.println("   DISGUSTO");
       myDFPlayer.play(28); // DISGUSTO
       Otto.tiptoeSwing(2, 1000, 20);
       forceHome();
       break;
    case EXP_EMBARRASSED:
       Serial.println("   IMBARAZZATO");
       myDFPlayer.play(24);  // Es: "ehm... che imbarazzo"
       Otto.shakeLeg(2, 1000, 1); // movimento nervoso
       forceHome();
       break;
    case EXP_BORED:
       Serial.println("   ANNOIATO");
       myDFPlayer.play(27); // es: “Uff che noia…”
       startYawnAnimation(); // avvia animazione sbadiglio
       Otto.bend(1, 1000, 20); // lento piegamento verso il basso
       forceHome();
       break;
    case EXP_ANXIOUS:
       Serial.println("   ANSIOSO");
       myDFPlayer.play(26); // es: “CHE ANSIA
       startYawnAnimation(); // avvia animazione sbadiglio
       Otto.tiptoeSwing(1, 1000, 20); // ondeggiamento sulle punte
       Otto.bend(1, 600, 15);         // si piega leggermente in avanti
       Otto.jitter(1, 400, 8);        // tremore
       forceHome();
       break;
    case EXP_NOSTALGIC:
      Serial.println("   NOSTALGIA");
      myDFPlayer.play(23); // traccia audio nostalgica
      Otto.swing(1, 1000, 20);  // movimento lento e ondeggiante
      forceHome();
      break;
    case EXP_LOVE:
      Serial.println("   INNAMORATO");
      myDFPlayer.play(16);// sei il mio umano preferito
      Otto.crusaito(2,1500,15,1);
      forceHome();
      break;
  	case EXP_AVOID:
      Serial.println("   EVITAMENTO");
      myDFPlayer.play(15);// modalita evita ostacoli attivata
      delay(3000);
      myDFPlayer.play(11);// evito gli ostacoli come un puma
      break;
	  case EXP_FOLLOW:
      Serial.println("   INSEGUIMENTO");
      myDFPlayer.play(22);//modalita inseguimento
      delay(3000);
      myDFPlayer.play(5);// abbracciami dai
      break;
    case EXP_DANCE:
      Serial.println("   BALLO!");
      expression = EXP_DANCE;   // imposta l'espressione corrente
      drawExpression(expression); // (opzionale, primo frame)
      startDance();             // avvia la danza non bloccante
      break;
    case EXP_SINGER:
      Serial.println("   CANTO!");
      expression = EXP_SINGER;   // imposta l'espressione corrente
      drawExpression(expression); // (opzionale, primo frame)
      break;
  }
}