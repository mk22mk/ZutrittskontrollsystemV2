/*
    /////////////////////////////////////////////////////////////
   //                                                         //
  //              Code-Zutrittskontrollsystem                //
 //                                                         //
/////////////////////////////////////////////////////////////
 */

/*================================================================================
Descprition: Zutrittskontrollsystem 
Author     : M. Ruettimann
Date       : 17.01.24
Version    : 2.0
================================================================================*/

// Einbindung der Bibliotheken/Files
#include <Keypad.h>
#include <Servo.h>
#include <SPI.h>
#include <MFRC522.h>
#include "arduino_config.h"

MFRC522 mfrc522(SS_PIN, RST_PIN); // RFID-Empfänger benennen

// Start viod setup
void setup()
{
SPI.begin(); // SPI-Verbindung aufbauen
mfrc522.PCD_Init(); // Initialisierung des RFID-Empfängers
Serial.begin(9600); // Serielle Verbindung starten (Monitor)
pinMode(roteLED, OUTPUT); // Die LEDs werden als Ausgang festgelegt
pinMode(grueneLED, OUTPUT); 
servoblau.attach(SERVO_PIN); // Ausgang Servo wird festgelegt
}

// Start void loop
void loop()
{
// Tastenfeld-Code
Anfang: // Markierung für Sprung nach dem 'goto' Befehl
Taste = Tastenfeld.getKey(); // Unter 'Taste' wird die gedrückte Taste gespeichert
if (Taste) // Wenn eine Taste gedrückt wird...
 {
  if (Taste=='*') // Wenn die * Taste gedrückt wird..
   {
   Serial.print("Die Taste "); // Anzeige auf dem Seriellen Monitor
   Serial.print("*");
   Serial.println(" wurde gedrueckt");
   Serial.println("Tuer verriegelt");
   servoblau.write(SERVO_ZU); // Ansteuerung Servo (Zustand geschlossen)
   digitalWrite(roteLED, HIGH); // Rote LED ein
   digitalWrite(grueneLED, LOW); // Grüne LED aus
   delay(T1); // Verzögerung 
   digitalWrite(roteLED, LOW); // Rote LED aus
   C1=0; C2=0; C3=0; C4=0; // Stellt das Zurückstellen des PINs sicher
   z1=0; z2=1; z3=1; z4=1; // Zugang erste Zeicheneingabe freischalten
   goto Anfang; // Sprung zum 'Anfang'
   }
  if (Taste=='#') // Wenn die # Taste gedrückt wird..
   {
   if (C1==P1&&C2==P2&&C3==P3&&C4==P4) // Prüft Übereinstimmung Passwort (PIN) mit Zahlen/Zeichen Speicher
   {
   Serial.print("Die Taste "); // Anzeige auf dem Seriellen Monitor
   Serial.print("#");
   Serial.println(" wurde gedrueckt");
   Serial.println ("Code korrekt, Schloss offen");
   servoblau.write(SERVO_AUF); // Ansteuerung Servo (Zustand geöffnet)
   digitalWrite(roteLED, LOW); // Rote LED aus
   digitalWrite(grueneLED, HIGH); // Grüne LED ein
   delay(T1); // Verzögerung
   digitalWrite(grueneLED, LOW); // Grüne LED aus
   z1=0; z2=1; z3=1; z4=1; // Zugang erste Zeicheneingabe freischalten
   }
   else
   {
   Serial.println ("Code falsch, Schloss gesperrt"); // Anzeige auf dem Seriellen Monitor
   digitalWrite(roteLED, HIGH); // Rote LED ein
   digitalWrite(grueneLED, LOW); // Grüne LED aus
   delay(T1);
   digitalWrite(roteLED, LOW); // Rote LED aus
   z1=0; z2=1; z3=1; z4=1; // Zugang erste Zeicheneingabe freischalten
   goto Anfang; // Sprung zum 'Anfang'
   }
  }
  if (z1==0)
  {
  C1=Taste;
  Serial.print("Die Taste "); // Anzeige auf dem Seriellen Monitor
  Serial.print(C1);
  Serial.println(" wurde gedrueckt");
  z1=1; z2=0; z3=1; z4=1; // Zugang zweite Zeicheneingabe freischalten
  goto Anfang; // Sprung zum 'Anfang'
  }

  if (z2==0)
  {
  C2=Taste;
  Serial.print("Die Taste "); // Anzeige auf dem Seriellen Monitor
  Serial.print(C2);
  Serial.println(" wurde gedrueckt");
  z1=1; z2=1; z3=0; z4=1; // Zugang dritte Zeicheneingabe freischalten
  goto Anfang; // Sprung zum 'Anfang'
  }

  if (z3==0)
  {
  C3=Taste;
  Serial.print("Die Taste "); // Anzeige auf dem Seriellen Monitor
  Serial.print(C3);
  Serial.println(" wurde gedrueckt");
  z1=1; z2=1; z3=1; z4=0; // Zugang vierte Zeicheneingabe freischalten
  goto Anfang; // Sprung zum 'Anfang'
  }

  if (z4==0)
  {
  C4=Taste;
  Serial.print("Die Taste "); // Anzeige auf dem Seriellen Monitor
  Serial.print(C4);
  Serial.println(" wurde gedrueckt");
  z1=1; z2=1; z3=1; z4=1; // Zugang zu weiteren Zeichen sperren
  goto Anfang; // Sprung zum 'Anfang'
  }
 }

// Batch-Leser-Code
if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) // Wenn ein Batch in reichweite ist und ein RFID-Sender ausgewählt wurden:
 {
  Serial.print("Die ID des RFID-TAGS lautet:"); // Anzeige auf dem Seriellen Monitor
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    Serial.print(mfrc522.uid.uidByte[i], HEX); // UID wird ausgelesen, Übertragung von 4 Blöcken in HEX-Zahlen auf den Seriellen Monitor
    Serial.print(" "); // Leerzeichen Zwischen den ausgelesenen Blöcken
  }
  Serial.println(); // Zeilenumbruchauf dem Seriellen Monitor

  // Überprüfe, ob die Batch-ID übereinstimmt
  if (mfrc522.uid.uidByte[0] == 0x83 &&
      mfrc522.uid.uidByte[1] == 0xD &&
      mfrc522.uid.uidByte[2] == 0xCD &&
      mfrc522.uid.uidByte[3] == 0x12)
    {
    Serial.println ("ID korrekt, Schloss offen"); // Anzeige auf dem Seriellen Monitor
    servoblau.write(SERVO_AUF); // Ansteuerung Servo (Zustand geöffnet)
    digitalWrite(roteLED, LOW); // Rote LED aus
    digitalWrite(grueneLED, HIGH); // Grüne LED ein
    delay(T1); // Verzögerung
    digitalWrite(grueneLED, LOW); // Grüne LED aus
    }
  //
  else
  {
  Serial.println ("ID falsch, Schloss gesperrt"); // Anzeige auf dem Seriellen Monitor
  digitalWrite(roteLED, HIGH); // Rote LED ein
  digitalWrite(grueneLED, LOW); // Grüne LED aus
  delay(T1); // Verzögerung
  digitalWrite(roteLED, LOW); // Rote LED aus
  goto Anfang; // Sprung zum 'Anfang'
  }
 }
}