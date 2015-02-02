#include <Wire.h>  // Comes with Arduino IDE
// Get the LCD I2C Library here: 
// https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads
// Move any other LCD libraries to another folder or delete them
// See Library "Docs" folder for possible commands etc.
#include <LiquidCrystal_I2C.h>
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN  9 
#define SS_PIN  10


byte readCard[4];
MFRC522 mfrc522(SS_PIN, RST_PIN); 

/*-----( Declare Constants )-----*/
/*-----( Declare objects )-----*/
// set the LCD address to 0x27 for a 20 chars 4 line display
// Set the pins on the I2C chip used for LCD connections:
//                    addr, en,rw,rs,d4,d5,d6,d7,bl,blpol
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);  // Set the LCD I2C address
 
/*-----( Declare Variables )-----*/
//NONE
 
void setup()   /*----( SETUP: RUNS ONCE )----*/
{
  Serial.begin(9600);  // Used to type in characters
 
  lcd.begin(16,2);   // initialize the lcd for 16 chars 2 lines, turn on backlight
 
// ------- Quick 3 blinks of backlight  -------------
  for(int i = 0; i< 3; i++)
  {
    lcd.backlight();
    delay(250);
    lcd.noBacklight();
    delay(250);
  }
  lcd.backlight(); // finish with backlight on  
 
//-------- Write characters on the display ------------------
// NOTE: Cursor Position: (CHAR, LINE) start at 0  
  lcd.setCursor(0,0); //Start at character 4 on line 0
  lcd.print("Hello, world!");
  delay(1000);
  lcd.setCursor(0,1);
  lcd.print("HI!YourDuino.com");
  delay(8000);  
 
 /*
// Wait and then tell user they can start the Serial Monitor and type in characters to
// Display. (Set Serial Monitor option to "No Line Ending")
  lcd.clear();
  lcd.setCursor(0,0); //Start at character 0 on line 0
  lcd.print("Use Serial Mon");
  lcd.setCursor(0,1);
  lcd.print("Type to display");  
 */ 
  SPI.begin();                             // Init SPI bus
  mfrc522.PCD_Init();                     // Init MFRC522 
  Serial.println(" Scan PICC to see UID, type, and data blocks...");
 
 
}/*--(end setup )---*/
 
 
void loop()   /*----( LOOP: RUNS CONSTANTLY )----*/
{
  
  //Look for new cards
  if(!mfrc522.PICC_IsNewCardPresent())
  {
    return;
  }
  // Select one of the cards
  if(!mfrc522.PICC_ReadCardSerial())
  {
     return; 
  }
   
  //Dump debug info about the card; PICC_HAlta() is autimatically called.
  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
  Serial.println("Scanned PICC's UID:");
  for (int i = 0; i < 4; i++) {  // 
    readCard[i] = mfrc522.uid.uidByte[i];
    Serial.print(readCard[i], HEX);
  }
  Serial.println("");
  mfrc522.PICC_HaltA(); // Stop reading
  
  
    // when characters arrive over the serial port...
    if (Serial.available()) 
    {
      // wait a bit for the entire message to arrive
      delay(100);
      // clear the screen
      lcd.clear();
      // read all the available characters
      while (Serial.available() > 0) 
      {
        // display each character to the LCD
        lcd.write(Serial.read());
      }
    }
  
 
}/* --(end main loop )-- */
