/*
    /////////////////////////////////////////////////////////////
   //                                                         //
  //                    config-File                          //
 //                                                         //
/////////////////////////////////////////////////////////////
 */

/*================================================================================
Descprition: Stammdaten
Author     : M. Ruettimann
Date       : 17.01.24
Version    : 2.0
================================================================================*/

Servo servoblau; // servo kann ab sofort mit 'servoblau' angesprochen werden
char P1 = '1'; char P2 = '2'; char P3 = '3'; char P4 = 'A'; // Definition Passwort Tastenfeld (123A)
char C1, C2, C3, C4; // Speichern der 4 Zeichen im Loop
int SERVO_PIN = 13; // Belegung Servo Pin
int SS_PIN = 53; // Belegung SS Pin (RFID-Empfänger)
int RST_PIN = 2; // Belegung RST Pin (RFID-Empfänger)
int SERVO_ZU = 90; // Winkel Servo wenn geschlossen
int SERVO_AUF = 180; // Winkel Servo wenn geöffnet
int T1 = 2000; // Leuchtdauer LED rot und grün (2s)
int roteLED = 11; // Belegung Pin rote LED
int grueneLED = 12; // Belegung Pin grüne LED
const byte COLS = 4; // 4 Spalten
const byte ROWS = 4; // 4 Zeilen
int z1 = 0, z2, z3, z4; // Diese Variablen werden verwendet, um für die einzelnen Zahlencodes dei Eingabe freizuschalten.
// Ziffern und Zeichen der Tastatur 
char hexaKeys[ROWS][COLS] = {
  {'D', '#', '0', '*'},
  {'C', '9', '8', '7'},
  {'B', '6', '5', '4'},
  {'A', '3', '2', '1'}
};
byte colPins[COLS] = {3, 4, 5, 6}; // Definition der Pins für die 4 Spalten
byte rowPins[ROWS] = {7, 8, 9, 10}; // Definition der Pins für die 4 Zeilen
Keypad Tastenfeld = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); // Keypad kann ab sofort mit 'Tastenfeld' angesprochen werden
char Taste; // Variable für die gedrückte Taste