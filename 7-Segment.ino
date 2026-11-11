#include <TM1637Display.h>

const int clk = 0;
const int dio = 1;
const int enc_a = 2;
const int enc_b = 3;
const int enc_sw = 4;
const int btn_1 = 5;
const int btn_2 = 6;

long time1 = 0;
bool running1 = false;
unsigned long count1 = 0;
bool alarm1 = false;

long time2 = 0;
bool running2 = false;
unsigned long count2 = 0;
bool alarm2 = false;

int active = 1;
TM1637Display display(clk, dio);
int last_a = HIGH;

unsigned long last_switch_time = 0;
unsigned long last_button1_time = 0;
unsigned long last_button2_time = 0;

int last_displayed_value = -1;
uint8_t last_colon_state = 255;

void setup() {
  pinMode(enc_a, INPUT_PULLUP);
  pinMode(enc_b, INPUT_PULLUP);
  pinMode(enc_sw, INPUT_PULLUP);
  pinMode(btn_1, INPUT_PULLUP);
  pinMode(btn_2, INPUT_PULLUP);
  display.setBrightness(4);
  last_a = digitalRead(enc_a);
}

void loop() {
  unsigned long now = millis();

  if (running1 == true) {
    if (now - count1 >= 1000) {
      time1 = time1 - 1;
      count1 = now;
      if (time1 <= 0) {
        time1 = 0;
        running1 = false;
        alarm1 = true;
      }
    }
  }

  if (running2 == true) {
    if (now - count2 >= 1000) {
      time2 = time2 - 1;
      count2 = now;
      if (time2 <= 0) {
        time2 = 0;
        running2 = false;
        alarm2 = true;
      }
    }
  }

  if (digitalRead(enc_sw) == LOW) {
    if (now - last_switch_time > 250) {
      last_switch_time = now;
      if (active == 1) {
        active = 2;
      } else {
        active = 1;
      }
    }
  }

  if (digitalRead(btn_1) == LOW) {
    if (now - last_button1_time > 250) {
      last_button1_time = now;
      if (active == 1) {
        if (time1 > 0) {
          running1 = true;
          count1 = millis();
        }
      }
      if (active == 2) {
        if (time2 > 0) {
          running2 = true;
          count2 = millis();
        }
      }
    }
  }

  if (digitalRead(btn_2) == LOW) {
    if (now - last_button2_time > 250) {
      last_button2_time = now;
      if (active == 1) {
        running1 = false;
        alarm1 = false;
      }
      if (active == 2) {
        running2 = false;
        alarm2 = false;
      }
    }
  }

  int current_a = digitalRead(enc_a);
  if (current_a != last_a) {
    if (current_a == LOW) {
      if (digitalRead(enc_b) == HIGH) {
        if (active == 1) {
          time1 = time1 + 60;
        }
        if (active == 2) {
          time2 = time2 + 60;
        }
      } else {
        if (active == 1) {
          time1 = time1 - 60;
          if (time1 < 0) {
            time1 = 0;
          }
        }
        if (active == 2) {
          time2 = time2 - 60;
          if (time2 < 0) {
            time2 = 0;
          }
        }
      }
    }
    last_a = current_a;
  }

  long total_seconds = 0;
  if (active == 1) {
    total_seconds = time1;
  }
  if (active == 2) {
    total_seconds = time2;
  }

  int display_minutes = total_seconds / 60;
  int display_seconds = total_seconds % 60;
  int final_value = (display_minutes * 100) + display_seconds;

  uint8_t colon_dots = 0;
  if ((now / 500) % 2 == 0) {
    colon_dots = 0b01000000;
  } else {
    colon_dots = 0;
  }

  if (final_value != last_displayed_value || colon_dots != last_colon_state) {
    display.showNumberDecEx(final_value, colon_dots, true);
    last_displayed_value = final_value;
    last_colon_state = colon_dots;
  }
}
