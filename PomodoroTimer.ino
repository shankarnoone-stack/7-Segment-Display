#include <TM1637Display.h>

// Hardware Pin Defs
const int PIN_CLK   = D6;
const int PIN_DIO   = D7;
const int ENC_A     = D8;
const int ENC_B     = D9;
const int ENC_SW    = D10;
const int PIN_START = D2;
const int PIN_RESET = D3;
const int PIN_BUZZ_ = D1; // Optional piezobuzzer output

TM1637Display display(PIN_CLK, PIN_DIO);

// State Machine Variables
enum TimerState { SET_WORK, SET_BREAK, RUNNING_WORK, WORK_DONE, RUNNING_BREAK, BREAK_DONE };
TimerState currentState = SET_WORK;

// Core Configuration Storage
int workMinutes = 25;
int breakMinutes = 5;
long timeRemainingSeconds = 0;

// Timing Registers
unsigned long lastTickTime = 0;
int lastEncA = HIGH;

// Display Colon Toggle Control
bool colonState = false;
unsigned long lastColonToggle = 0;

void setup() {
  pinMode(ENC_A, INPUT_PULLUP);
  pinMode(ENC_B, INPUT_PULLUP);
  pinMode(ENC_SW, INPUT_PULLUP);
  pinMode(PIN_START, INPUT_PULLUP);
  pinMode(PIN_RESET, INPUT_PULLUP);
  pinMode(PIN_BUZZ_, OUTPUT);

  display.setBrightness(4);
  updateDisplayTime(workMinutes, 0);
}

void loop() {
  handleInputs();
  handleTimerEngine();
}

void handleInputs() {
  unsigned long currentMillis = millis();
  
  // 1. ROTARY ENCODER INPUT (Time Settings)
  int currentEncA = digitalRead(ENC_A);
  if (currentEncA != lastEncA && currentEncA == LOW) {
    int direction = (digitalRead(ENC_B) == HIGH) ? 1 : -1;
    
    if (currentState == SET_WORK) {
      workMinutes = constrain(workMinutes + direction, 1, 99);
      updateDisplayTime(workMinutes, 0);
    } else if (currentState == SET_BREAK) {
      breakMinutes = constrain(breakMinutes + direction, 1, 99);
      updateDisplayTime(breakMinutes, 0);
    }
  }
  lastEncA = currentEncA;

  // 2. ENCODER INTERNAL SWITCH (Toggle Setup Modes)
  if (digitalRead(ENC_SW) == LOW) {
    if (currentState == SET_WORK) {
      currentState = SET_BREAK;
      updateDisplayTime(breakMinutes, 0);
    } else if (currentState == SET_BREAK) {
      currentState = SET_WORK;
      updateDisplayTime(workMinutes, 0);
    }
    delay(250); // Soft primitive debounce for setup phase switches
  }

  // 3. SWITCH 1 (Start / Pause Engine Execution)
  if (digitalRead(PIN_START) == LOW) {
    if (currentState == SET_WORK || currentState == WORK_DONE) {
      timeRemainingSeconds = workMinutes * 60;
      currentState = RUNNING_WORK;
    } else if (currentState == SET_BREAK || currentState == BREAK_DONE) {
      timeRemainingSeconds = breakMinutes * 60;
      currentState = RUNNING_BREAK;
    } else if (currentState == RUNNING_WORK) {
      currentState = SET_WORK; // Actively Pauses & Drops to adjustment mode
      updateDisplayTime(workMinutes, 0);
    } else if (currentState == RUNNING_BREAK) {
      currentState = SET_BREAK; // Actively Pauses & Drops to adjustment mode
      updateDisplayTime(breakMinutes, 0);
    }
    delay(250);
  }

  // 4. SWITCH 2 (Hard System Reset to Defaults)
  if (digitalRead(PIN_RESET) == LOW) {
    currentState = SET_WORK;
    updateDisplayTime(workMinutes, 0);
    digitalWrite(PIN_BUZZ_, LOW);
    delay(250);
  }
}

void handleTimerEngine() {
  unsigned long currentMillis = millis();

  // Handle Dynamic Countdown Engine
  if (currentState == RUNNING_WORK || currentState == RUNNING_BREAK) {
    // 1-Second Decrement Clock Tracker
    if (currentMillis - lastTickTime >= 1000) {
      lastTickTime = currentMillis;
      timeRemainingSeconds--;

      if (timeRemainingSeconds <= 0) {
        triggerAlarm();
        currentState = (currentState == RUNNING_WORK) ? WORK_DONE : BREAK_DONE;
      } else {
        int displayMins = timeRemainingSeconds / 60;
        int displaySecs = timeRemainingSeconds % 60;
        updateDisplayTime(displayMins, displaySecs);
      }
    }

    // Flash Center Colon Point Every 500ms Without Code Pausing
    if (currentMillis - lastColonToggle >= 500) {
      lastColonToggle = currentMillis;
      colonState = !colonState;
      int displayMins = timeRemainingSeconds / 60;
      int displaySecs = timeRemainingSeconds % 60;
      display.showNumberDecEx(displayMins, colonState ? 0b01000000 : 0, true, 2, 0);
      display.showNumberDecEx(displaySecs, 0, true, 2, 2);
    }
  }
  
  // Flash Display When Session is Finished
  if (currentState == WORK_DONE || currentState == BREAK_DONE) {
    if ((currentMillis / 300) % 2 == 0) {
      display.clear();
    } else {
      updateDisplayTime(0, 0);
    }
  }
}

void updateDisplayTime(int minutes, int seconds) {
  // Pushes parsed structural variables across the dual display memory blocks
  display.showNumberDecEx(minutes, 0b01000000, true, 2, 0); 
  display.showNumberDecEx(seconds, 0, true, 2, 2);
}

void triggerAlarm() {
  // Non-blocking primitive click notification pulse
  for(int i=0; i<3; i++) {
    digitalWrite(PIN_BUZZ_, HIGH);
    delay(70);
    digitalWrite(PIN_BUZZ_, LOW);
    delay(70);
  }
}
