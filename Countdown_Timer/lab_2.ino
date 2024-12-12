//**** PIN SETUP  ****
int serialDataRight = 3;    // SER for right shift register is on pin 3
int latchClockRight = 4;    // RCLK for right shift register is on pin 4
int shiftClockRight = 5;    // SRCLK for right shift register is on pin 5

int serialDataLeft = 8;     // SER for left shift register is on pin 8
int latchClockLeft = 9;     // RCLK for left shift register is on pin 9
int shiftClockLeft = 10;    // SRCLK for left shift register is on pin 10

const int clkPin= 11;       // The clk attaches to pin 11
const int dtPin= 12;        // Dt attaches to pin 12
const int swPin= 13;        // The click button attaches to pin 13
int encoderVal = 0;
int button_val = 0;
int old_button_val = 0;

//**** 7-SEGMENT DISPLAY SETUP ****
int EMPTY = 0;

// Decimal values for each number on left 7 segment display
int ZERO_DOT = 254;
int ONE_DOT = 200;
int TWO_DOT = 189;
int THREE_DOT = 237;
int FOUR_DOT = 203;
int FIVE_DOT = 231;
int SIX_DOT = 247;
int SEVEN_DOT = 204;
int EIGHT_DOT = 255;
int NINE_DOT = 207;

String left = "left";

int NUMBERS_LEFT[] = {ZERO_DOT, ONE_DOT, TWO_DOT, THREE_DOT, FOUR_DOT, FIVE_DOT, SIX_DOT, SEVEN_DOT, EIGHT_DOT, NINE_DOT};
int NUMBERS_LEFT_SIZE = 10;

// Decimal values for each number on right 7 segment display
int ZERO = 126;
int ONE = 72;
int TWO = 61;
int THREE = 109;
int FOUR = 75;
int FIVE = 103;
int SIX = 119;
int SEVEN = 76;
int EIGHT = 127;
int NINE = 79;

String right = "right";

int NUMBERS_RIGHT[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
int NUMBERS_RIGHT_SIZE = 10;

void setup() {

  // For left 7 segment display
  pinMode(serialDataLeft, OUTPUT);
  pinMode(shiftClockLeft, OUTPUT);
  pinMode(latchClockLeft, OUTPUT);

  // For right 7 segment display
  pinMode(serialDataRight, OUTPUT);
  pinMode(shiftClockRight, OUTPUT);
  pinMode(latchClockRight, OUTPUT);

  // For the rotary encoder
  pinMode(clkPin, INPUT);
  pinMode(dtPin, INPUT);
  pinMode(swPin, INPUT);
  digitalWrite(swPin, HIGH);

  // initialize encoder to 99 (the program adds 1 to it in the loop functon)
  encoderVal = 98;

  Serial.begin(9600);

}



// Sets the number to display on 7 segment display
void set_display_number (String left_or_right, char argument_number_string, int argument_number_int) {

  int number_value = 0;

  if (argument_number_string != 'N') {
    if (left_or_right == left) {

      if (argument_number_string == '0') {
        number_value = ZERO_DOT;
      } else if (argument_number_string == '1') {
        number_value = ONE_DOT;
      } else if (argument_number_string == '2') {
        number_value = TWO_DOT;
      } else if (argument_number_string == '3') {
        number_value = THREE_DOT;
      } else if (argument_number_string == '4') {
        number_value = FOUR_DOT;
      } else if (argument_number_string == '5') {
        number_value = FIVE_DOT;
      } else if (argument_number_string == '6') {
        number_value = SIX_DOT;
      } else if (argument_number_string == '7') {
        number_value = SEVEN_DOT;
      } else if (argument_number_string == '8') {
        number_value = EIGHT_DOT;
      } else if (argument_number_string == '9') {
        number_value = NINE_DOT;
      }

    } else {

      if (argument_number_string == '0') {
        number_value = ZERO;
      } else if (argument_number_string == '1') {
        number_value = ONE;
      } else if (argument_number_string == '2') {
        number_value = TWO;
      } else if (argument_number_string == '3') {
        number_value = THREE;
      } else if (argument_number_string == '4') {
        number_value = FOUR;
      } else if (argument_number_string == '5') {
        number_value = FIVE;
      } else if (argument_number_string == '6') {
        number_value = SIX;
      } else if (argument_number_string == '7') {
        number_value = SEVEN;
      } else if (argument_number_string == '8') {
        number_value = EIGHT;
      } else if (argument_number_string == '9') {
        number_value = NINE;
      }

    }
  } else {
    number_value = argument_number_int;
  }


  if (left_or_right == left) {
    digitalWrite(latchClockLeft, LOW);
    shiftOut(serialDataLeft, shiftClockLeft, MSBFIRST, number_value);  // shift out all the bits
    digitalWrite(latchClockLeft, HIGH);  // now we can transfer the data from storage registers to outputs
  } else {
    digitalWrite(latchClockRight, LOW);
    shiftOut(serialDataRight, shiftClockRight, MSBFIRST, number_value);
    digitalWrite(latchClockRight, HIGH);  // now we can transfer the data from storage registers to outputs
  }

  return;
}



// Counts down from a number (0.0 - 9.9) passed in through the function arguments
void countdown (char seconds_index_char, char miliseconds_index_char) {

  delay(500);

  int seconds_index = seconds_index_char - '0';
  int miliseconds_index = miliseconds_index_char - '0';
  int temp = 0;
  int return_status = 0;
  int change = 0;
  bool breakout = false;

  for (int i = seconds_index; i != -1; i--) {  // countdown for seconds
    change = getEncoderTurn();

    if (breakout) {
        break;
    }
    

    if (digitalRead(swPin) == LOW) {
      encoderVal = 99;
      delay(100);
      break;
    } else if (change != 0) {
      break;
    }

    set_display_number(left, 'N', NUMBERS_LEFT[i]);

    for (int k = NUMBERS_RIGHT_SIZE-1; k != -1; k--) {  // countdown for miliseconds
      change = getEncoderTurn();

      if (i == seconds_index && temp == 0) {
        k = miliseconds_index;
        temp++;
      }

      if (digitalRead(swPin) == LOW) {
        encoderVal = 99;
        breakout = true;
        delay(100);
        break;
      } else if (change != 0) {
        breakout = true;
        break;
      }

      set_display_number(right, 'N', NUMBERS_RIGHT[k]);

      delay(20);


      if (NUMBERS_LEFT[i] == ZERO_DOT && NUMBERS_RIGHT[k] == ZERO) {
        for (int i = 0; i < 5; i++) {
          
          set_display_number(left, 'N', ZERO_DOT);
          set_display_number(right, 'N', ZERO);

          delay(400);
          
          set_display_number(left, 'N', EMPTY);
          set_display_number(right, 'N', EMPTY);

          delay(400);
        }
      }

      
      delay(185);
    }
  }

  return;
}



int getEncoderTurn(void)
{
  static int oldA = HIGH; //set the oldA as HIGH
  static int oldB = HIGH; //set the oldB as HIGH
  int result = 0;
  int newA = digitalRead(clkPin);//read the value of clkPin to newA
  int newB = digitalRead(dtPin);//read the value of dtPin to newB
  if (newA != oldA || newB != oldB) //if the value of clkPin or the dtPin has changed
  {
    // something has changed
    if (oldA == HIGH && newA == LOW)
    {
      result = (oldB * 2 - 1);
    }
  }
  oldA = newA;
  oldB = newB;

  return result;
}



void loop() {
  int change = getEncoderTurn();
  button_val = digitalRead(swPin);
  encoderVal = encoderVal + change;

  if (encoderVal == 100) {
    encoderVal = 0;
  } else if (encoderVal < 0) {
    encoderVal = 99;
  }

  String encoderValString = String(encoderVal);  // convert the encoder value to a string to make it easily parsible

  if ((button_val == LOW) && (old_button_val == HIGH))    //if button pull down
  {
    if (encoderValString.length() == 1) {
      countdown('0', encoderValString[0]);
    } else {
      countdown(encoderValString[0], encoderValString[1]);
    }
  }

  old_button_val = button_val;


  if (encoderValString.length() == 1) {
    set_display_number(left, '0', 0);
    set_display_number(right, encoderValString[0], 0);
  } else {
    set_display_number(left, encoderValString[0], 0);
    set_display_number(right, encoderValString[1], 0);
  }

}
