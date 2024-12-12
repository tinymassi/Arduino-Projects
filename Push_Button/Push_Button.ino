
int LED = 13;
int BUTTON = 7;

int button_val = 0;
int old_button_val = 0;
int state = 0;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT);
}

void loop() {
  button_val = digitalRead(BUTTON);

  if ((button_val == HIGH) && (old_button_val == LOW)) {
    state = 1 - state;
    delay(10);
  }

  old_button_val = button_val;

  if (state == 1) {
    digitalWrite(LED, HIGH);
  } else {
    digitalWrite(LED, LOW);
  }

}
