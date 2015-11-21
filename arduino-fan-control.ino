#include <math.h>

const int RED_LED = 52;
const int GREEN_LED = 53;

const int DIGIT_1 = 43;
const int DIGIT_2 = 42;
const int DIGIT_3 = 41;
const int DIGIT_4 = 40;

const int SEGMENT_A = 32;
const int SEGMENT_B = 33;
const int SEGMENT_C = 34;
const int SEGMENT_D = 35;
const int SEGMENT_E = 36;
const int SEGMENT_F = 37;
const int SEGMENT_G = 38;

const int DECIMAL_POINT = 39;

const int TEMP_PIN = 0;

const int DIGIT[] = {DIGIT_1, DIGIT_2, DIGIT_3, DIGIT_4};

const int SAMPLES = 255;
float sample[SAMPLES];
int sample_index = 0;
int display_temp = 0;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);

  pinMode(SEGMENT_A, OUTPUT);
  pinMode(SEGMENT_B, OUTPUT);
  pinMode(SEGMENT_C, OUTPUT);
  pinMode(SEGMENT_D, OUTPUT);
  pinMode(SEGMENT_E, OUTPUT);
  pinMode(SEGMENT_F, OUTPUT);
  pinMode(SEGMENT_G, OUTPUT);

  pinMode(DECIMAL_POINT, OUTPUT);

  digitalWrite(DIGIT_1, HIGH);
  digitalWrite(DIGIT_2, HIGH);
  digitalWrite(DIGIT_3, HIGH);
  digitalWrite(DIGIT_4, HIGH);

  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, HIGH);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, HIGH);

  digitalWrite(DECIMAL_POINT, LOW);

  Serial.begin(9600);
}

void loop() {
  float temp;
  temp = analogRead(TEMP_PIN);
  temp = (temp/1024.0) * 5000;
  temp = temp / 10;

  sample_index = sample_index + 1;

  if (sample_index >= SAMPLES) {
    display_temp = 1;
    sample_index = 0;
  }

  sample[sample_index] = temp;

  if (display_temp) {

    float avg = average_temperature();
    char display_temp[3];
    dtostrf(avg, 3, 1, display_temp);

    render_number(display_temp[0]);
    select_digit(0);

    digitalWrite(DECIMAL_POINT, HIGH);
    render_number(display_temp[1]);
    select_digit(1);
    digitalWrite(DECIMAL_POINT, LOW);

    render_number(display_temp[3]);
    select_digit(2);

    centigrade();
    select_digit(3);

    if (avg > 27.0f ) {
      digitalWrite(GREEN_LED, LOW);
      digitalWrite(RED_LED, HIGH);
    } else {
      digitalWrite(GREEN_LED, HIGH);
      digitalWrite(RED_LED, LOW);
    }
  }
}

float average_temperature() {
  float accum = 0.0f;
  int i;

  for(i = 0; i < SAMPLES; i++) {
     accum += sample[i];
  }

  return accum / (float)SAMPLES;
}

void select_digit(int index) {
  digitalWrite(DIGIT[index], LOW);
  delay(5);
  digitalWrite(DIGIT[index], HIGH);
}

void render_number(int number) {
  // ascii character codes
  switch(number) {
    case 49: one(); break;
    case 50: two(); break;
    case 51: three(); break;
    case 52: four(); break;
    case 53: five(); break;
    case 54: six(); break;
    case 55: seven(); break;
    case 56: eight(); break;
    case 57: nine(); break;
    default: zero();
  }
}

void one() {
  digitalWrite(SEGMENT_A, LOW);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, LOW);
  digitalWrite(SEGMENT_E, LOW);
  digitalWrite(SEGMENT_F, LOW);
  digitalWrite(SEGMENT_G, LOW);
}

void two() {
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, LOW);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, HIGH);
  digitalWrite(SEGMENT_F, LOW);
  digitalWrite(SEGMENT_G, HIGH);
}

void three() {
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, LOW);
  digitalWrite(SEGMENT_F, LOW);
  digitalWrite(SEGMENT_G, HIGH);
}

void four() {
  digitalWrite(SEGMENT_A, LOW);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, LOW);
  digitalWrite(SEGMENT_E, LOW);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, HIGH);
}

void five() {
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, LOW);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, LOW);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, HIGH);
}

void six() {
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, LOW);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, HIGH);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, HIGH);
}

void seven() {
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, LOW);
  digitalWrite(SEGMENT_E, LOW);
  digitalWrite(SEGMENT_F, LOW);
  digitalWrite(SEGMENT_G, LOW);
}

void eight() {
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, HIGH);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, HIGH);
}

void nine() {
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, LOW);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, HIGH);
}

void zero() {
  digitalWrite(SEGMENT_A, HIGH);
  digitalWrite(SEGMENT_B, HIGH);
  digitalWrite(SEGMENT_C, HIGH);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, HIGH);
  digitalWrite(SEGMENT_F, HIGH);
  digitalWrite(SEGMENT_G, LOW);
}

void centigrade() {
  digitalWrite(SEGMENT_A, LOW);
  digitalWrite(SEGMENT_B, LOW);
  digitalWrite(SEGMENT_C, LOW);
  digitalWrite(SEGMENT_D, HIGH);
  digitalWrite(SEGMENT_E, HIGH);
  digitalWrite(SEGMENT_F, LOW);
  digitalWrite(SEGMENT_G, HIGH);
}

