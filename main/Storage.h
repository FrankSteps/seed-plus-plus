/*
  Controlador de Armazenamento - EEPROM
  Gerencia armazenamento dinâmico de UIDs na memória não-volátil
*/

#ifndef STORAGE_H
#define STORAGE_H
#include <Arduino.h>
#include <EEPROM.h>

class StorageController {
  private:
    // Constantes de configuração
    static constexpr byte UID_SIZE = 4;                             // Tamanho do UID em bytes
    static constexpr byte MAX_UIDS = 30;                            // Máximo de UIDs armazenáveis
    static constexpr int EEPROM_START = 0;                          // Endereço inicial da EEPROM
    static constexpr int ADDR_COUNT = EEPROM_START;                 // Endereço do contador de UIDs
    static constexpr int ADDR_UIDS = EEPROM_START + 1;              // Endereço inicial dos UIDs
    static constexpr int TOTAL_BYTES = 1 + (MAX_UIDS * UID_SIZE);   // Total de bytes utilizados
    
    // Métodos privados de leitura/escrita
    byte readByte(int address);
    void writeByte(int address, byte value);
    
  public:
    // Construtor
    StorageController();
    
    // Operações básicas
    void begin();           
    void clear();           
    void displayAll();     
    
    // Armazenamento de UIDs
    bool addUID(const byte* uid);      
    bool removeUID(const byte* uid);   
    bool uidExists(const byte* uid);  
    
    // Consulta de UIDs
    byte getTotalUIDs();                    
    const byte* getUID(byte index);        
};

#endif
