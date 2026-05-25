// bibliotecas
#include "RFID.h"
#include <SPI.h>
#include <string.h>

// Construtor - inicializa o módulo RFID com os pinos SS e RST
RFIDController::RFIDController(byte ssPin, byte rstPin) : rfid(ssPin, rstPin) {}


// Inicializa a comunicação SPI e o módulo RFID
void RFIDController::begin() {
  SPI.begin();
  rfid.PCD_Init(10, 9);
}

// Verifica se um cartão foi detectado e lê seu serial
bool RFIDController::cardDetected() {
  if (!rfid.PICC_IsNewCardPresent()) return false;
  if (!rfid.PICC_ReadCardSerial()) return false;
  return true;
}

// Exibe o UID do cartão no monitor serial (formato hexadecimal)
void RFIDController::displayUID() {
  Serial.print(F("UID: "));
  for (byte i = 0; i < rfid.uid.size; i++) {
    // Adiciona zero à esquerda se o valor for menor que 0x10
    if (rfid.uid.uidByte[i] < 0x10) Serial.print("0");
    Serial.print(rfid.uid.uidByte[i], HEX);
    if (i < rfid.uid.size - 1) Serial.print(" ");
  }
  Serial.println();
}

// Para a comunicação com o cartão
void RFIDController::stop() {
  rfid.PICC_HaltA();
  rfid.PCD_StopCrypto1();
}

// Retorna o pointer para o array do UID do cartão
const byte* RFIDController::getUID() {
  return rfid.uid.uidByte;
}
