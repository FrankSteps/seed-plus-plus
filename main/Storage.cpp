#include "Storage.h"

// Construtor padrão
StorageController::StorageController() {}

// Inicializa o controlador de armazenamento
void StorageController::begin() {
  // Verifica se a EEPROM está corrompida (contador > limite)
  if (EEPROM.read(ADDR_COUNT) > MAX_UIDS) {
    clear();
  }
}

// Lê um byte da EEPROM
byte StorageController::readByte(int address) {
  return EEPROM.read(address);
}

// Escreve um byte na EEPROM
void StorageController::writeByte(int address, byte value) {
  EEPROM.write(address, value);
}

// Retorna o total de UIDs armazenados
byte StorageController::getTotalUIDs() {
  return readByte(ADDR_COUNT);
}

// Adiciona um novo UID na EEPROM
bool StorageController::addUID(const byte* uid) {
  if (uid == nullptr) return false;
  
  byte total = getTotalUIDs();
  
  // Verifica se o UID já existe
  if (uidExists(uid)) {
    Serial.println(F("UID already registered"));
    return false;
  }
  
  // Verifica se há espaço disponível
  if (total >= MAX_UIDS) {
    Serial.println(F("Memory full"));
    return false;
  }
  
  // Adiciona o novo UID no final da lista
  int baseAddr = ADDR_UIDS + (total * UID_SIZE);
  for (byte i = 0; i < UID_SIZE; i++) {
    writeByte(baseAddr + i, uid[i]);
  }
  
  // Incrementa o contador de UIDs
  writeByte(ADDR_COUNT, total + 1);
  
  Serial.print(F("UID added. Total: "));
  Serial.println(getTotalUIDs());
  return true;
}

// Verifica se um UID já existe na EEPROM
bool StorageController::uidExists(const byte* uid) {
  if (uid == nullptr) return false;
  
  byte total = getTotalUIDs();
  
  // Itera por todos os UIDs armazenados
  for (byte i = 0; i < total; i++) {
    int baseAddr = ADDR_UIDS + (i * UID_SIZE);
    bool found = true;
    
    // Compara byte por byte
    for (byte j = 0; j < UID_SIZE; j++) {
      if (readByte(baseAddr + j) != uid[j]) {
        found = false;
        break;
      }
    }
    
    if (found) return true;
  }
  
  return false;
}

// Remove um UID da EEPROM
bool StorageController::removeUID(const byte* uid) {
  if (uid == nullptr) return false;
  
  byte total = getTotalUIDs();
  
  // Procura pelo UID
  for (byte i = 0; i < total; i++) {
    int baseAddr = ADDR_UIDS + (i * UID_SIZE);
    bool found = true;
    
    for (byte j = 0; j < UID_SIZE; j++) {
      if (readByte(baseAddr + j) != uid[j]) {
        found = false;
        break;
      }
    }
    
    // Se encontrou, remove deslocando os demais para cima
    if (found) {
      // Move todos os UIDs após este para cima
      for (byte k = i; k < total - 1; k++) {
        int source = ADDR_UIDS + ((k + 1) * UID_SIZE);
        int destination = ADDR_UIDS + (k * UID_SIZE);
        
        for (byte m = 0; m < UID_SIZE; m++) {
          writeByte(destination + m, readByte(source + m));
        }
      }
      
      // Decrementa o contador
      writeByte(ADDR_COUNT, total - 1);
      Serial.println(F("UID removed"));
      return true;
    }
  }
  
  Serial.println(F("UID not found"));
  return false;
}

// Retorna o UID armazenado no índice especificado
const byte* StorageController::getUID(byte index) {
  if (index >= getTotalUIDs()) return nullptr;
  
  static byte uidBuffer[4];
  int baseAddr = ADDR_UIDS + (index * UID_SIZE);
  
  // Copia o UID do índice para o buffer
  for (byte i = 0; i < UID_SIZE; i++) {
    uidBuffer[i] = readByte(baseAddr + i);
  }
  
  return uidBuffer;
}

// Exibe todos os UIDs armazenados no monitor serial
void StorageController::displayAll() {
  byte total = getTotalUIDs();
  Serial.print(F("Total UIDs: "));
  Serial.println(total);
  
  // Itera por todos os UIDs e exibe em formato hexadecimal
  for (byte i = 0; i < total; i++) {
    const byte* uid = getUID(i);
    Serial.print(F("  ["));
    Serial.print(i);
    Serial.print(F("] "));
    
    for (byte j = 0; j < UID_SIZE; j++) {
      if (uid[j] < 0x10) Serial.print("0");
      Serial.print(uid[j], HEX);
      if (j < UID_SIZE - 1) Serial.print(" ");
    }
    Serial.println();
  }
}

// Limpa toda a EEPROM
void StorageController::clear() {
  for (int i = EEPROM_START; i < TOTAL_BYTES; i++) {
    writeByte(i, 0);
  }
  Serial.println(F("Memory cleared"));
}
