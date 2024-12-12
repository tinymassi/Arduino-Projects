const int LED_1 = 2;
const int LED_2 = 3;
const int LED_3 = 4;
const int LED_4 = 5;
const int LED_5 = 6;
const int LED_6 = 7;
const int LED_7 = 8;

int LED_PINS[] = {LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7};

const int BUTTON = 12;

const String NAME = "Maddi Higham";
const int NAME_size = 12;
String binary_values[NAME_size];

const String NAME_2 = "Maddi Higham";

int button_state = 0;
int val = 0;
int val_old = 0;
int i = 0;

void setup() {
    pinMode(BUTTON, INPUT);
    Serial.begin(9600);

    for (int k = 0; k < 7; k++) {
      pinMode(LED_PINS[k], OUTPUT);
    }

  
    for (; i < NAME.length(); i++) {
        int ascii_value = (int)NAME[i];
        String binary_value;

        if (ascii_value != 32) {
          for (int j = 6; j >= 0; j--) {
              // Check if the j-th bit is set
              binary_value += ((ascii_value >> j) & 1) ? '1' : '0';
          }
        } else {
          binary_value = "0000000";
        }

        binary_values[i] = binary_value;
    }

    i = 0;
}

void loop() {
  val = digitalRead(BUTTON);


  if ((val == HIGH) && (val_old == LOW)) {
    String binary_value = binary_values[i];
    Serial.print(NAME_2[i]);
    Serial.print(" -> ");
    Serial.println(binary_value);
    for (int k = 0; k < 7; k++) {
      if (binary_value[k] == '1') {
        digitalWrite(LED_PINS[k], HIGH);
      } else {
        digitalWrite(LED_PINS[k], LOW);
      }
    }
    i++;
    if (i == NAME_2.length()) {
      i = 0;
    }
  }


  delay(100);
  val_old = val;
}
