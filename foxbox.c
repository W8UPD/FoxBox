/*
 * foxbox.c - An Arduino Fox-Hunt system.
 * (c) 2011-present, W8UPD - the Univ. Akron Amat. Radio Club
 * Authored by Ricky Elrod, N8SQL
 * Co-Authored by Jimmy Carter, KG4SGP and Chris Egeland, KD8LCV
 * Released under a two-clause BSD license. See LICENSE for details.
 */

// This is not technically C, but syntax-highlights decently as it.

// ============== Configuration of FoxBox ===================

// These values are in miliseconds
const int DIT = 60;
const int DAH = DIT * 3;
const int LETTER_SPACE = DIT * 3;
const int WORD_SPACE = DIT * 7;

// Random number of seconds to delay between identifying.
const int ID_DELAY_MINIMUM = 60;
const int ID_DELAY_MAXIMUM = ID_DELAY_MINIMUM * 3;

// Miliseconds to wait after keying PTT, before sending audio.
const int PRE_ID = 1000;

// What to send
const String MESSAGE = "de w8upd/b";

// ========= Pin assignments ==========
// The pin to blink morse, as sending.
const int LED_PIN = 13;

// The pin to activate PTT.
const int PTT_PIN = 5;

// The pin to send audio out of.
const int TONE_PIN = 6;

/**
 * Convert a char/letter to appropriate dots and dashes.
 * @param char letter The letter to encode
 * @return String Morse code representation (ASCII "." and "-") of the given
                  char.
*/
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
    default: return "";
  }
}

/**
 * Blink the LED and sound the tone for one "dit" or "dah"
 *
 * @param char type_delay A char representing a dit or dah ('.' or '-') which
                          determines how long the action happens.
*/
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

/**
 * Iterate through a given string and perform blink() on each character.
 *
 * @param String text The string of letters to encode to morse.
 */
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

/**
 * Delays for a random amount of seconds, based on given arguments.
 *
 * @param int minimum Minimum number of miliseconds to delay
 * @param int maximum Maximum number of miliseconds to delay
 * @return int The number of seconds actually delayed
 */
int randomDelay(int minimum, int maximum) {
  // Random noise on unconnected pin 0.
  randomSeed(analogRead(0));
  int randomSeconds = random(minimum, maximum);

  // This math has to be done in the function call to prevent an overflow.
  delay(randomSeconds * 1000);
  return randomSeconds;
}


/**
 * Enter the program here.
 */
void setup() {
  // LED stuff.
  pinMode(LED_PIN, OUTPUT);
  
  // PTT stuff.
  pinMode(PTT_PIN, OUTPUT);
  
  // Audio output.
  pinMode(TONE_PIN, OUTPUT);
}

/**
 * Do this as the program runs.
 */
void loop() {
  digitalWrite(PTT_PIN, HIGH);
  delay(PRE_ID);
  perform_blink(MESSAGE);
  digitalWrite(PTT_PIN, LOW);
  randomDelay(ID_DELAY_MINIMUM, ID_DELAY_MAXIMUM);
}
