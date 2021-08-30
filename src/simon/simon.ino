#include <EEPROM.h>

#define CLOCK_SPEED 1

#include "ioMapping.h"
#include "timings.h"
#include "notes.h"

// Mode -1 = pre game (i.e. press button to start)
// Mode 0 = output (i.e. displaying pattern)
// Mode 1 = input (i.e. player inputs pattern)
int current_mode = -1; 

int pattern[100] = {-1};
int end_index = 0;
unsigned int score = 0;

// System LED codes
void initDone();
void error();

// Game logic
void gameStart();
void outputPattern();
void playerInput();
void gameOver();
void correct();

// I/O handling
void blinkLight(int index);
void writeTone(unsigned char divisor, unsigned char octave);
void clearTone();
int debounce(int pin);
void outputFlip();
void inputFlip();
void outputScore(bool high_score);


void setup() {
  outputFlip();
  pinMode(SPEAKER_PIN, OUTPUT);
  // Speaker pin will always be set to output
  initDone();
}

void loop() {
  if (current_mode == -1) {
    gameStart();
  } else if (current_mode == 0) {
    outputPattern();
  } else if (current_mode == 1) {
    playerInput();
  }
}

void initDone() {
  for (int j = 0; j < 2; j++) {
    writeTone(NOTE_C, 5);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    digitalWrite(RED_PIN, HIGH);
    digitalWrite(YELLOW_PIN, HIGH);
    delay(SHORT_3);
    writeTone(NOTE_G, 5);
    digitalWrite(RED_PIN, LOW);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(BLUE_PIN, HIGH);
    delay(SHORT_3);
  }
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
  writeTone(NOTE_C, 4);
  delay(MED_1);
  clearTone();
}

void error() {
  // Indicates an error has occured and the system should be reset
  while (true) {
    writeTone(NOTE_F, 3);
    delay(MED_2);
    clearTone();
    delay(SHORT_3);
  }
}

void gameStart() {
  score = 0;
  end_index = 0;
  while (true) {
    pinMode(RED_PIN, INPUT);
    // TODO: Change this to red_read once red wire is resoldered
    int red_read = digitalRead(RED_PIN);

    if (red_read == HIGH) {
      int verified_read = debounce(RED_PIN);
      if (verified_read == RED_PIN) {
        randomSeed(micros());
        
        pinMode(RED_PIN, OUTPUT);
        digitalWrite(RED_PIN, HIGH);
        digitalWrite(GREEN_PIN, HIGH);
        digitalWrite(BLUE_PIN, HIGH);
        digitalWrite(YELLOW_PIN, HIGH);
        
        writeTone(NOTE_C, 5);
        delay(MED_1);
        writeTone(NOTE_E, 5);
        delay(MED_1);
        clearTone();
        
        digitalWrite(RED_PIN, LOW);
        digitalWrite(GREEN_PIN, LOW);
        digitalWrite(BLUE_PIN, LOW);
        digitalWrite(YELLOW_PIN, LOW);
        analogWrite(SPEAKER_PIN, 0);
        delay(LONG_2);
        current_mode = 0;
        return;
      }
    }
  }
}

void outputPattern() {
  outputFlip();
  int new_color = random(0,4);

  if (new_color == 0) {
    pattern[end_index] = RED_PIN;
  } else if (new_color == 1) {
    pattern[end_index] = GREEN_PIN;
  } else if (new_color == 2) {
    pattern[end_index] = BLUE_PIN;
  } else if (new_color == 3) {
    pattern[end_index] = YELLOW_PIN;
  } else {
    error();
  }

  for (int k = 0; k <= end_index; k++) {
    if (pattern[k] == -1) {
      error();
    }
    blinkLight(k);
  }
  delay(SHORT_1);
  end_index += 1;
  current_mode = 1;
}

void playerInput() {
  inputFlip();
  int input_index = 0;
  while(true) {
    int red_read = digitalRead(RED_PIN);
    int green_read = digitalRead(GREEN_PIN);
    int blue_read = digitalRead(BLUE_PIN);
    int yellow_read = digitalRead(YELLOW_PIN);

    int input_read = -1;
    
    if (red_read == HIGH) {
      input_read = debounce(RED_PIN);
    } else if (green_read == HIGH) {
      input_read = debounce(GREEN_PIN);
    } else if (blue_read == HIGH) {
      input_read = debounce(BLUE_PIN);
    } else if (yellow_read == HIGH) {
      input_read = debounce(YELLOW_PIN);
    }

    if (input_read != -1) {
      if (input_read != pattern[input_index]) {
        gameOver();
        return;
      }

      input_index += 1;

      if (input_index >= end_index) {
        score += 1;
        current_mode = 0;
        correct();
        return;
      }
    }
  }
}

void gameOver() {
  outputFlip();
  delay(SHORT_3);
  for (int i = 0; i < 5; i++) {
    digitalWrite(RED_PIN, HIGH);
    writeTone(NOTE_F, 3);
    delay(SHORT_3);
    digitalWrite(RED_PIN, LOW);
    clearTone();
    delay(SHORT_1);
  }
  delay(SHORT_3);

  byte final_score = (byte)score;
  byte stored_score = EEPROM.read(SCORE_ADDRESS);
  
  if (final_score > stored_score) {
    EEPROM.write(SCORE_ADDRESS, final_score);
    digitalWrite(GREEN_PIN, HIGH);
    writeTone(NOTE_F, 4);
    delay(SHORT_3);
    writeTone(NOTE_C, 6);
    delay(LONG_1);
    digitalWrite(GREEN_PIN, LOW);
    clearTone();
    delay(SHORT_1);
  }

  current_mode = -1;
}

void outputScore(bool high_score) {
  if (!high_score) {
    
  }
}

void correct() {
  delay(SHORT_3);
  for (int i = 0; i < 3; i++) {
    writeTone(NOTE_C, 5);
    delay(SHORT_2);
    clearTone();
    delay(SHORT_1);
  }
}


// I/O Functions
void blinkLight(int index) {
  int pin_color = pattern[index];
  digitalWrite(pin_color, HIGH);
  if (pin_color == RED_PIN) {
    writeTone(NOTE_B, 4);
  } else if (pin_color == GREEN_PIN) {
    writeTone(NOTE_G, 4);
  } else if (pin_color == BLUE_PIN) {
    writeTone(NOTE_E, 4);
  } else if (pin_color == YELLOW_PIN) {
    writeTone(NOTE_C, 4);
  }

  delay(MED_2);

  digitalWrite(pattern[index], LOW);
  clearTone();

  delay(MED_2);
}

void writeTone(unsigned char divisor, unsigned char octave) {
  // PWM a tone 
  TCCR1 = 0x90 | (11-octave);
  OCR1C = divisor-1;
}

void clearTone() {
  TCCR1 = 0x90;
}

int debounce(int pin) {
  // Debounces a button input
  // Should be called on first HIGH read from pin
  // Returns pin value on successful read

  // TODO: MUST BE UPDATED TO LONGER DELAY WHEN CLOCK SPEED IS FIXED
  delay(PULSE);
  int pin_read = digitalRead(pin);
  if (pin_read == HIGH) {
    if (pin == RED_PIN) {
      writeTone(NOTE_B, 4);
    } else if (pin == GREEN_PIN) {
      writeTone(NOTE_G, 4);
    } else if (pin == BLUE_PIN) {
      writeTone(NOTE_E, 4);
    } else if (pin == YELLOW_PIN) {
      writeTone(NOTE_C, 4);
    }
    
    int previous_state = HIGH;
    while(true) {
      pin_read = digitalRead(pin);
      if (pin_read == LOW && previous_state == LOW) {
        clearTone();
        return pin;
      } else if (pin_read == LOW) {
        previous_state = LOW;
        delay(PULSE);
      } else {
        previous_state = HIGH;
      }
    }
  } else {
    // Return -1 if button was not held down
    return -1;
  }
}

void outputFlip() {
  pinMode(RED_PIN, OUTPUT);
  delay(PULSE);
  pinMode(GREEN_PIN, OUTPUT);
  delay(PULSE);
  pinMode(BLUE_PIN, OUTPUT);
  delay(PULSE);
  pinMode(YELLOW_PIN, OUTPUT);
}

void inputFlip() {
  pinMode(RED_PIN, INPUT);
  delay(PULSE);
  pinMode(GREEN_PIN, INPUT);
  delay(PULSE);
  pinMode(BLUE_PIN, INPUT);
  delay(PULSE);
  pinMode(YELLOW_PIN, INPUT);
}
