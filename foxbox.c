// This is not technically C, but syntax-highlights decently as it.

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */

const int DIT = 100;
const int DAH = DIT * 3;
const int LETTER_SPACE = DIT * 3;
const int WORD_SPACE = DIT * 7;

// Seconds to delay between identifying.
const int ID_DELAY = 15;

// Miliseconds to wait after keying PTT, before sending audio.
const int PRE_ID = 500;

// Pin assignments
const int LED_PIN = 13;
const int PTT_PIN = 5;
const int TONE_PIN = 6;

String convert_morse(char letter) {
  
  switch (letter) {
    case 'a': return ".-";
    case 'b': return "-...";
    case 'c': return "-.-.";
    case 'd': return "-..";
    case 'e': return ".";
    case 'f': return "..-.";
    case 'g': return "--.";
    case 'h': return "....";
    case 'i': return "..";
    case 'j': return ".---";
    case 'k': return "-.-";
    case 'l': return ".-..";
    case 'm': return "--";
    case 'n': return "-.";
    case 'o': return "---";
    case 'p': return ".--.";
    case 'q': return "--.-";
    case 'r': return ".-.";
    case 's': return "...";
    case 't': return "-";
    case 'u': return "..-";
    case 'v': return "...-";
    case 'w': return ".--";
    case 'x': return "-..-";
    case 'y': return "-.--";
    case 'z': return "--..";
    case '1': return ".----";
    case '2': return "..---";
    case '3': return "...--";
    case '4': return "....-";
    case '5': return ".....";
    case '6': return "-....";
    case '7': return "--...";
    case '8': return "---..";
    case '9': return "----.";
    case '0': return "-----";
    case '?': return "..--..";
    case '.': return ".-.-.-";
    case ',': return "--..--";
    case '-': return "-....-";
    case '/': return "-..-.";
    default:
      return "";
  }
}

void setup() {
  // LED stuff.
  pinMode(LED_PIN, OUTPUT);
  
  // PTT stuff.
  pinMode(PTT_PIN, OUTPUT);
  
  // Audio output.
  pinMode(TONE_PIN, OUTPUT);
  
//  Serial.begin(9600);
}

void blink(char type_delay) {
  analogWrite(TONE_PIN, 127);
  digitalWrite(LED_PIN, HIGH);
  if (type_delay == '.') {
    delay(DIT);
  } else if (type_delay == '-') {
    delay(DAH);
  }
  analogWrite(TONE_PIN, 0);
  digitalWrite(LED_PIN, LOW);
  delay(DIT);
}

void perform_blink(String text) {
  for (int i = 0; i <= text.length(); i++) {

    // Handle special cases here.
    if (text.charAt(i) == ' ') {
      delay(WORD_SPACE);
      continue;
    }
    
    // Convert the letter to morse, ...
    String morseified = convert_morse(text.charAt(i));

    // For each char of the morse string, ...
    for (int j = 0; j <= morseified.length(); j++) {
      
      if (morseified.charAt(j) == '.') {
        blink('.');
      } else if (morseified.charAt(j) == '-') {
        blink('-');
      }
    }
    delay(LETTER_SPACE);
  }
}

void loop() {
  digitalWrite(PTT_PIN, HIGH);
  delay(PRE_ID);
  perform_blink("w8upd/b");
  digitalWrite(PTT_PIN, LOW);
  delay(ID_DELAY * 1000);
}
