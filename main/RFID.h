/*
 * Controlador RFID - MFRC522
 * Gerencia leitura e escrita de cartões RFID
 */
#ifndef RFID_H
#define RFID_H
#include <Arduino.h>
#include <MFRC522.h>

class RFIDController {
  private:
    MFRC522 rfid;                              // Instância do leitor RFID
    static constexpr byte UID_SIZE = 4;        // Tamanho do UID em bytes
  
  public:
    RFIDController(byte ssPin, byte rstPin);
    
    void begin();
    bool cardDetected();
    const byte* getUID();
    void displayUID();
    void stop();
};

#endif
