// expressions.h
#ifndef EXPRESSIONS_H
#define EXPRESSIONS_H

#include <Arduino.h>
#include <EMOtto.h>

// Enum per le espressioni
enum ExpressionType {
  EXP_NONE, 
  EXP_NORMAL,
  EXP_SAD,
  EXP_ANGRY,
  EXP_SURPRISED,
  EXP_LOVE,
  EXP_DISGUST,
  EXP_EMBARRASSED,
  EXP_BORED,    // annoiato
  EXP_ANXIOUS,
  EXP_NOSTALGIC,
  EXP_TOTAL, // utile per il numero totale di espressioni
  EXP_AVOID,
  EXP_FOLLOW,
  EXP_DANCE,
  EXP_SINGER
};

extern ExpressionType expression;
// Funzione pubblica per disegnare un'espressione
void drawExpression(ExpressionType expression);
 void performExpression(ExpressionType type);
#endif
