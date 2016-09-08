
/*  morsecode in arduino. takes input from serial port. Converts text to sound and light based morse code*/

int ledPin = 12;
int buzzerPin = 11; //  Must use PWM pin to control volume
int volume;


char* letters[] = {
  ".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..",    // A-I
  ".---", "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.",  // J-R
  "...", "-", "..-", "...-", ".--", "-..-", "-.--", "--.."          // S-Z
};

char* numbers[] = {"-----", ".----", "..---", "...--", "....-", ".....", "-....", "--...", "---..", "----."};

int dotDelay = 200;

void setup()                 
{
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin,OUTPUT);
  Serial.begin(9600);
}

void loop()                    
{
  char ch;
  if (Serial.available())      // is there anything to be read from USB?
  {
    ch = Serial.read();        // read a single letter
    if (ch >= 'a' && ch <= 'z')
    {
      flashSequence(letters[ch - 'a']);
    }
    else if (ch >= 'A' && ch <= 'Z')
    {
      flashSequence(letters[ch - 'A']);
    }
    else if (ch >= '0' && ch <= '9')
    {
      flashSequence(numbers[ch - '0']);
    }
    else if (ch == ' ')
    {
     delay(dotDelay * 4);      // gap between words  
    }
  }
}

void flashSequence(char* sequence)
{
   int i = 0;
   while (sequence[i] != NULL)
   {
       flashDotOrDash(sequence[i]);
       i++;
   }
   delay(dotDelay * 3);    // gap between letters
}

void flashDotOrDash(char dotOrDash)
{
  digitalWrite(ledPin, HIGH);
    volume=map(analogRead(A0),0,1023,1,200); // The Map function
//  potValue = analogRead(potPin); 
  analogWrite(buzzerPin, volume);   
  
  if (dotOrDash == '.')
  {
    delay(dotDelay);           
  }
  else // must be a -
  {
    delay(dotDelay * 3);           
  }
  digitalWrite(ledPin, LOW);
  analogWrite(buzzerPin, LOW);   
  
  delay(dotDelay); // gap between flashes
}
