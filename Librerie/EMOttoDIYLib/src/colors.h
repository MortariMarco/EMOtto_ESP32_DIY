#ifndef COLORS_H
#define COLORS_H

// Colori definiti tramite codici RGB565 (usati da TFT_eSPI)

// --- COLORI --- //
#define TFT_RED     0xF800
#define TFT_GREEN   0x07E0
#define TFT_BLUE    0x001F
#define TFT_YELLOW  0xFFE0
#define TFT_WHITE   0xFFFF
#define TFT_BLACK   0x0000
#define TFT_GIALLO_CHIARO 0xFFF3
#define TFT_ROSSO_SCURO   0xA800
#define TFT_VIOLA   0xF81F
#define TFT_ARANCIONE 0xFD20
#define TFT_AZZURRO_CHIARO 0x7D7C
#define TFT_TURCHESE 0x7DDF
#define TFT_MAGENTA 0x780F
#define TFT_GIALLO_PASTELLO  0xFFE0   // giallo crema
#define TFT_ROSA_PASTELLO    0xF81F   // rosa chiaro
#define TFT_MENTA_PASTELLO   0xD7E0   // verde menta
#define TFT_LILLA_PASTELLO   0xAFFF   // lilla soft
#define TFT_AZZURRO_PASTELLO 0x87FF   // azzurro cielo
#define TFT_VERDE_ACIDO  0x87E0   // RGB565: verdino con un filo di giallo
#define TFT_GRIGIO_CHIARO 0xC618  // grigio chiaro
#define TFT_ANXIA 0x7BEF  // un grigio-blu tenue
#define TFT_AZZURRO_NOSTALGIA 0xAEDC // un azzurro soft, nostalgico
#define TFT_CANTANTE_BG 0x5AD6  // un turchese-grigio medio, soft
#define TFT_NOTE_GOLD    0xFEA0  // oro caldo, brillante
#define TFT_NOTE_COLOR 0x7BFF  // un azzurrino brillante,
#define TFT_SKIN     0xFDB8  // color pelle
#define TFT_ORANGE   0xFDA0  // compatibile con TFT_ARANCIONE

inline uint16_t nextPastelColor() {
    static const uint16_t palette[] = {
        TFT_GIALLO_PASTELLO,
        TFT_ROSA_PASTELLO,
        TFT_MENTA_PASTELLO,
        TFT_LILLA_PASTELLO,
        TFT_AZZURRO_PASTELLO
    };
    static uint8_t i = 0;
    uint16_t c = palette[i];
    i = (i + 1) % (sizeof(palette) / sizeof(uint16_t));
    return c;
}

inline uint16_t getSkinColor(ExpressionType expr) {
  switch (expr) {
    case EXP_NORMAL:    return TFT_GIALLO_CHIARO;
    case EXP_ANGRY:     return TFT_ROSSO_SCURO;
    case EXP_SURPRISED: return TFT_VIOLA;
    case EXP_SAD:       return TFT_BLUE;
    case EXP_DISGUST:   return TFT_VERDE_ACIDO;
    case EXP_LOVE:      return TFT_ARANCIONE;
    case EXP_AVOID:     return TFT_MAGENTA;
    case EXP_FOLLOW:    return TFT_ARANCIONE;
    case EXP_EMBARRASSED:  return  TFT_ROSA_PASTELLO; 
    case EXP_BORED:     return  TFT_GRIGIO_CHIARO;
    case EXP_ANXIOUS:   return TFT_ANXIA;
    case EXP_NOSTALGIC: return TFT_AZZURRO_NOSTALGIA;
    case EXP_SINGER:    return TFT_CANTANTE_BG;
    case EXP_DANCE:     return   nextPastelColor(); 
    default:            return TFT_WHITE;
  }
}
#endif // COLORS_H