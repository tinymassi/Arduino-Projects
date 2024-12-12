// Blinking LED

const int LED = 13;  // LED connected to digital pin 13

void setup() {
  pinMode(LED, OUTPUT);  // Sets the digital pin as output

}

void loop() {
  digitalWrite(LED, HIGH);  // Turns the LED on
  delay(1000);              // Waits one second
  digitalWrite(LED, LOW);   // Turns LED off
  delay(1000);              // Wait one second
}
