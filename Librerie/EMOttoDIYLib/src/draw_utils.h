#ifndef DRAW_UTILS_H
#define DRAW_UTILS_H

#include <EMOtto.h>
#include "expressions.h"
#include "modes.h"
extern ExpressionType expression;

// === Dichiarazioni funzioni di disegno comuni ===
void forceHome();
void drawEyes();
void drawBlinkFrame(int height);
void drawEyelids(int height);
void animateBlink();
void drawSmile();
void drawStraightMouth();
void drawSadMouth();
void drawOMouth();
void drawTears();
void drawBlush();
void drawBrowsNormal();
void drawBrowsAngry();
void drawBrowsSurprised();
void drawBrowsSad();
void updateTears();
void updateHeartEyes();
void drawTearDrop(int x, int y, uint16_t color);
void drawHeart(int x, int y, int r);
void drawExplosion(int x, int y);
void showBluetoothOn(ExpressionType expression);
void showBluetoothOff(ExpressionType expression);
void drawMouthOpenSmile();
uint16_t nextPastelColor();
void drawEyesDisgust();
void drawBrowsDisgust();
void drawEyesDisgust();
void drawDisgustMouth();
void drawEmbarrassedMouth();
void drawBrowsEmbarrassed();
void drawEyesBored();
void drawBoredMouth();
void drawBrowsBored();
void animateTearDrop(); 
void updateYawnAnimation();
void startYawnTear();       
void updateYawnTear();       
void startYawnAnimation();
// --- ansia
void drawBrowsAnxious();
void drawEyesAnxious();
void drawWavyMouth(int cx, int cy, int width, int amplitude);
// nostalgia
void drawEyesNostalgic();
void drawMouthNostalgic();
void drawBrowsNostalgic();
//  -- CANTANTE
void drawSinging();
void drawMouthOpen();
void drawMouthMedium();
void drawMouthClosed();
void drawEyebrowsRaised();
void updateSingingMouth();
void drawSingingMouth();
void updateSingerFoot();     // piede che batte a tempo
void playRandomSong();
void startSingerFoot();
void exitSingerMode();
extern TFT_eSPI tft;

#endif // DRAW_UTILS_H
