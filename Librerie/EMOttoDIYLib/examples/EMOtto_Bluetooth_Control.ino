#include <Arduino.h>
#include <EMOtto.h>                // o <EMOtto.h> se hai rinominato la libreria
#include <BluetoothSerial.h>

BluetoothSerial SerialBT;
Otto Otto;

// Variabili di stato movimento
bool walkingForward = false;
bool walkingBackward = false;
bool turningLeft = false;
bool turningRight = false;
int walkSpeed = 1000;  // velocità (ms per passo)

// Espressioni
enum ExpressionType {
  EXP_NORMAL,
  EXP_ANGRY,
  EXP_SAD,
  EXP_LOVE,
  EXP_TOTAL
};

ExpressionType expression = EXP_NORMAL;

void performExpression(ExpressionType type) {
  switch (type) {
    case EXP_NORMAL:
      Serial.println("🙂 NORMAL");
      break;
    case EXP_ANGRY:
      Serial.println("😠 ANGRY");
      break;
    case EXP_SAD:
      Serial.println("😢 SAD");
      break;
    case EXP_LOVE:
      Serial.println("😍 LOVE");
      break;
    default:
      break;
  }
}

void updateWalking() {
  if (walkingForward)  Otto.walk(1, walkSpeed, 1);
  if (walkingBackward) Otto.walk(1, walkSpeed, -1);
  if (turningLeft)     Otto.turn(1, walkSpeed, -1);
  if (turningRight)    Otto.turn(1, walkSpeed, 1);
}

void setup() {
  Serial.begin(115200);
  SerialBT.begin("EMOtto");
  Serial.println("Bluetooth avviato. Pronto!");
  Otto.init(2, 3, 4, 5, 6, 7);  // cambia i pin se necessario
  Otto.home();
}

void loop() {
  if (SerialBT.available()) {
    char cmd = SerialBT.read();
    Serial.print("Ricevuto: ");
    Serial.println(cmd);

    switch (cmd) {
      // Espressioni
      case 'N': expression = EXP_NORMAL; break;
      case 'A': expression = EXP_ANGRY;  break;
      case 'S': expression = EXP_SAD;    break;
      case 'L': expression = EXP_LOVE;   break;

      // Movimenti continui
      case 'W': walkingForward  = true; break;
      case 'i': walkingBackward = true; break;
      case 's': turningLeft     = true; break;
      case 'D': turningRight    = true; break;
      case 'X':
        walkingForward = walkingBackward = turningLeft = turningRight = false;
        Otto.home();
        break;

      // Velocità
      case '+':
        if (walkSpeed > 200) walkSpeed -= 100;
        Serial.print("Velocità ↑: "); Serial.println(walkSpeed);
        break;
      case '-':
        if (walkSpeed < 2000) walkSpeed += 100;
        Serial.print("Velocità ↓: "); Serial.println(walkSpeed);
        break;

      default:
        Serial.println("Comando sconosciuto");
        break;
    }

    performExpression(expression);
  }

  updateWalking();
}
