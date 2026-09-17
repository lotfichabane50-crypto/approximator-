#include <BitBang_LiquidCrystal_I2C.h>
#include <Keypad.h>

// 1. CONFIGURATION MATÉRIELLE
BitBang_LiquidCrystal_I2C lcd(0x27, 16, 2, 8, 9);
const byte brochesLED[5] = {A0, A1, A2, A3, A4};
const byte pinBuzzer = A5;

const byte LIGNES = 4;
const byte COLONNES = 4;

char touches[LIGNES][COLONNES] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte brochesLignes[LIGNES]     = {7, 6, 5, 4};
byte brochesColonnes[COLONNES] = {3, 2, 1, 0};

Keypad clavier = Keypad(makeKeymap(touches), brochesLignes, brochesColonnes, LIGNES, COLONNES);

// 3. VARIABLES GLOBALES
String calculEnCours = "";
bool attenteTouchePourReset = false;

// Mode James Bond
bool modeJamesBondActif = false;
unsigned long dernierNoteTime = 0;
int noteIndex = 0;

const int melodie007[] = {
  262, 294, 294, 294, 294, 262, 262, 262,
  262, 311, 311, 311, 311, 294, 294, 262
};
const int durees007[] = {
  200, 200, 200, 400, 200, 200, 200, 400,
  200, 200, 200, 400, 200, 200, 200, 400
};
const int nbNotes007 = 16;

const char* repliquesRick[] = {
  "RED",
  "BLUE",
  "PEANUT BUTTER",
  "INCOME",
  "SPIDER-MAN !!!",
  "SINJ",
  "FEASTABLES",
  "MYDIL<3",
  "PURPLE",
  "KOI FISH",
  "WALLMART",
  "UK GARAGE",
  "GATORADE",
  "CRISTALINE",
  "10/04/2046"
};
const int nbPhrases = 15;

// NOTES MUSICALES POUR LE THÈME RICK & MORTY
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_G4  392
#define NOTE_A4  440
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988

void setup() {
  for (int i = 0; i < 5; i++) {
    pinMode(brochesLED[i], OUTPUT);
    digitalWrite(brochesLED[i], LOW);
  }
  pinMode(pinBuzzer, OUTPUT);

  lcd.begin();
  reinitialiser();
}

void loop() {
  if (modeJamesBondActif) {
    unsigned long courant = millis();
    if (courant - dernierNoteTime >= durees007[noteIndex]) {
      dernierNoteTime = courant;
      tone(pinBuzzer, melodie007[noteIndex], durees007[noteIndex] - 50);
      noteIndex = (noteIndex + 1) % nbNotes007;
    }
  }

  char touche = clavier.getKey();

  if (touche) {
    if (attenteTouchePourReset) {
      if (!modeJamesBondActif) tone(pinBuzzer, 2000, 30);
      reinitialiser();
      return;
    }

    if (!modeJamesBondActif) tone(pinBuzzer, 2000, 30);

    if (touche == '#') {
      reinitialiser();
    }
    else if (touche == '*') {
      if (calculEnCours.length() > 0) {
        if (calculEnCours == "7355608") {
          armerBombeCSGO();
          return;
        }

        int typeCalcul = determinerEvenement();
        bool valide = attendreValidation(typeCalcul);

        if (valide) {
          saboterCalcul(typeCalcul);
          modeJamesBondActif = false;
          noTone(pinBuzzer);
        } else {
          reinitialiser();
        }
      }
    }
    else {
      char caractere = touche;
      if (touche == 'A') caractere = '+';
      if (touche == 'B') caractere = '-';
      if (touche == 'C') caractere = '*';
      if (touche == 'D') caractere = '/';

      if (calculEnCours.length() < 16) {
        calculEnCours += caractere;
        lcd.setCursor(0, 1);
        lcd.print(calculEnCours);

        if (calculEnCours == "007") {
          modeJamesBondActif = true;
          noteIndex = 0;
          dernierNoteTime = millis();
        }

        if (calculEnCours.endsWith("+-*/")) {
          executerModeHacker();
          reinitialiser();
          return;
        }

        if (calculEnCours == "7355608") {
          delay(200);
          armerBombeCSGO();
          return;
        }
      }
    }
  }
}

bool attendreValidation(int typeCalcul) {
  unsigned long dureeTotale = (typeCalcul == 0) ? 3000 : random(1000, 3001);
  unsigned long intervalleParLed = dureeTotale / 5;

  eteindreToutesLesLED();
  lcd.setCursor(0, 1);
  lcd.print("Chargement...   ");

  for (int led = 0; led < 5; led++) {
    if (typeCalcul == 0 && led == 4) {
      unsigned long debutPause = millis();
      while (millis() - debutPause < 1000) {
        char k = clavier.getKey();
        if (k == '#') {
          tone(pinBuzzer, 2000, 30);
          eteindreToutesLesLED();
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Calcul annule !");
          delay(1000);
          return false;
        }
      }
      eteindreToutesLesLED();
      return true;
    }

    digitalWrite(brochesLED[led], HIGH);
    
    unsigned long debutEtape = millis();
    while (millis() - debutEtape < intervalleParLed) {
      char k = clavier.getKey();
      if (k == '#') {
        tone(pinBuzzer, 2000, 30);
        eteindreToutesLesLED();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Calcul annule !");
        delay(1000);
        return false;
      }
    }
  }

  eteindreToutesLesLED();
  return true;
}

void executerModeHacker() {
  modeJamesBondActif = false;
  noTone(pinBuzzer);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("SYSTEM HACKED...");

  unsigned long debutHack = millis();
  
  while (millis() - debutHack < 10000) {
    lcd.setCursor(0, 1);
    for (int i = 0; i < 16; i++) {
      char charAlea = (char)random(33, 126);
      lcd.print(charAlea);
    }

    for (int i = 0; i < 5; i++) {
      digitalWrite(brochesLED[i], random(0, 2));
    }

    int freqAlea = random(800, 4000);
    tone(pinBuzzer, freqAlea, 30);

    delay(60);
  }

  noTone(pinBuzzer);
  eteindreToutesLesLED();
}

void armerBombeCSGO() {
  modeJamesBondActif = false;
  noTone(pinBuzzer);

  lcd.clear();

  bool etatLed = false;
  unsigned long dernierClignotement = 0;
  unsigned long debutMaintienHash = 0;
  unsigned long debutArmement = millis();
  bool enMaintien = false;

  // Variables pour l'animation des points de "defusing . . ."
  unsigned long dernierUpdateDefuseText = 0;
  int etapeDefuseText = 0;

  const unsigned long DELAI_EXPLOSION = 30000;
  const unsigned long TEMPS_DEFUSE = 10000;

  while (true) {
    unsigned long courant = millis();
    unsigned long tempsEcoule = courant - debutArmement;

    if (tempsEcoule >= DELAI_EXPLOSION) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("*** BOOM ! ***");
      lcd.setCursor(0, 1);
      lcd.print("TERRORISTS WIN");

      tone(pinBuzzer, 100, 5000);

      unsigned long debutExplosion = millis();
      while (millis() - debutExplosion < 5000) {
        etatLed = !etatLed;
        for (int i = 0; i < 5; i++) {
          digitalWrite(brochesLED[i], etatLed ? HIGH : LOW);
        }
        delay(30);
      }

      noTone(pinBuzzer);
      reinitialiser();
      return;
    }

    // Le clignotement des LED et du buzzer continue sans interruption
    if (courant - dernierClignotement >= 500) {
      dernierClignotement = courant;
      etatLed = !etatLed;

      for (int i = 0; i < 5; i++) {
        digitalWrite(brochesLED[i], etatLed ? HIGH : LOW);
      }
      if (etatLed) {
        tone(pinBuzzer, 3000, 40);
      }
    }

    // Affichage permanent de la détonation sur la ligne du haut (ligne 0)
    int secondesRestantes = (DELAI_EXPLOSION - tempsEcoule) / 1000;
    lcd.setCursor(0, 0);
    lcd.print("Detonation: ");
    if (secondesRestantes < 10) lcd.print("0");
    lcd.print(secondesRestantes);
    lcd.print("s ");

    clavier.getKey();
    byte state = clavier.getState();

    if (clavier.key[0].kchar == '#' && (state == PRESSED || state == HOLD)) {
      if (!enMaintien) {
        enMaintien = true;
        debutMaintienHash = courant;
      }

      unsigned long tempsMaintenu = courant - debutMaintienHash;

      // Animation "defusing . . ." qui remplace "BOMB IS ARMED !" sur la ligne 1
      if (courant - dernierUpdateDefuseText >= 400) {
        dernierUpdateDefuseText = courant;
        etapeDefuseText = (etapeDefuseText + 1) % 4;

        lcd.setCursor(0, 1);
        switch (etapeDefuseText) {
          case 0: lcd.print("defusing       "); break;
          case 1: lcd.print("defusing .     "); break;
          case 2: lcd.print("defusing . .   "); break;
          case 3: lcd.print("defusing . . . "); break;
        }
      }

      if (tempsMaintenu >= TEMPS_DEFUSE) {
        eteindreToutesLesLED();
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("BOMB DEFUSED !");
        
        tone(pinBuzzer, 1000, 100); delay(120);
        tone(pinBuzzer, 1500, 100); delay(120);
        tone(pinBuzzer, 2000, 300); delay(400);

        reinitialiser();
        return;
      }
    } else {
      if (enMaintien) {
        enMaintien = false;
      }
      // Réaffiche "BOMB IS ARMED !" sur la ligne du bas tant qu'on ne defuse pas
      lcd.setCursor(0, 1);
      lcd.print("BOMB IS ARMED ! ");
    }

    delay(20);
  }
}

int determinerEvenement() {
  int tirage = random(0, 100);
  if (tirage < 5) return 0;
  if (tirage < 10) return 1;
  return 2;
}

void eteindreToutesLesLED() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(brochesLED[i], LOW);
  }
}

void reinitialiser() {
  calculEnCours = "";
  attenteTouchePourReset = false;
  modeJamesBondActif = false;
  noTone(pinBuzzer);
  eteindreToutesLesLED();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Calcul [*=Envoi]:");
  lcd.setCursor(0, 1);
}

void jouerMelodie(int type) {
  if (type == 1) { 
    // SUCCÈS : Arpège rapide Rick & Morty
    tone(pinBuzzer, NOTE_B5, 100); delay(120);
    tone(pinBuzzer, NOTE_G5, 100); delay(120);
    tone(pinBuzzer, NOTE_E5, 100); delay(120);
    tone(pinBuzzer, NOTE_B4, 100); delay(120);
    tone(pinBuzzer, NOTE_E5, 100); delay(120);
    tone(pinBuzzer, NOTE_G5, 100); delay(120);
    tone(pinBuzzer, NOTE_B5, 250); delay(300);
  } 
  else if (type == 0) { 
    // ÉCHEC / FLEMME : Descente chromatique
    tone(pinBuzzer, NOTE_E4, 150); delay(170);
    tone(pinBuzzer, NOTE_DS4, 150); delay(170);
    tone(pinBuzzer, NOTE_D4, 150); delay(170);
    tone(pinBuzzer, NOTE_C4, 300); delay(350);
  } 
  else { 
    // SABOTAGE / RICKTROLL : Thème principal Rick & Morty (E-B-G-E / D-A-F#-D)
    tone(pinBuzzer, NOTE_E5, 120); delay(140);
    tone(pinBuzzer, NOTE_B5, 120); delay(140);
    tone(pinBuzzer, NOTE_G5, 120); delay(140);
    tone(pinBuzzer, NOTE_E5, 120); delay(140);
    
    tone(pinBuzzer, NOTE_D5, 120); delay(140);
    tone(pinBuzzer, NOTE_A5, 120); delay(140);
    tone(pinBuzzer, NOTE_FS5, 120); delay(140);
    tone(pinBuzzer, NOTE_D5, 250); delay(280);
  }
}

void saboterCalcul(int typeCalcul) {
  char op = 0;
  int indexOp = -1;

  for (int i = 0; i < calculEnCours.length(); i++) {
    char c = calculEnCours[i];
    if (c == '+' || c == '-' || c == '*' || c == '/') {
      op = c;
      indexOp = i;
      break;
    }
  }

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(calculEnCours);
  lcd.setCursor(0, 1);

  if (indexOp <= 0 || indexOp >= calculEnCours.length() - 1) {
    lcd.print("Syntaxe invalide");
    jouerMelodie(0);
    attenteTouchePourReset = true;
    return;
  }

  if (typeCalcul == 0) {
    lcd.print("nan pas envie");
    jouerMelodie(0);
    attenteTouchePourReset = true;
    return;
  }

  long val1 = calculEnCours.substring(0, indexOp).toInt();
  long val2 = calculEnCours.substring(indexOp + 1).toInt();
  long vraiResultat = 0;

  switch (op) {
    case '+': vraiResultat = val1 + val2; break;
    case '-': vraiResultat = val1 - val2; break;
    case '*': vraiResultat = val1 * val2; break;
    case '/': 
      if (val2 == 0) {
        lcd.print("IMPOSSIBLE!!!!");
        jouerMelodie(0);
        attenteTouchePourReset = true;
        return;
      }
      vraiResultat = val1 / val2; 
      break;
  }

  if (typeCalcul == 1) {
    lcd.print("= ");
    lcd.print(vraiResultat);
    jouerMelodie(1);
  } 
  else {
    int alea = random(0, 2);
    if (alea == 0) {
      int r = random(0, nbPhrases);
      lcd.print(repliquesRick[r]);
    } else {
      int decalage = random(1, 10);
      if (random(0, 2) == 1) decalage = -decalage;

      lcd.print("= ");
      lcd.print(vraiResultat + decalage);
    }
    jouerMelodie(2);
  }

  attenteTouchePourReset = true;
}