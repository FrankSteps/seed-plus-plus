/*
  Seed++ V2

  Sistema de Controle de Acesso com RFID para Laboratório
  Desenvolvido para o laboratório da FnE (Física na Escola) com o objetivo
  de automatizar e controlar o acesso aos recursos do laboratório através
  de cartões RFID, com modo administrativo para gerenciamento de usuários.

  Características:
    - Autenticação via cartões RFID (MFRC522)
    - Armazenamento dinâmico de UIDs na EEPROM
    - Modo administrativo para adicionar/remover cartões
    - Controle de acesso com relé eletromecânico
    - Sistema de botões multifunção com debounce

  Hardware:
    - Arduino Uno/Nano
    - Leitor RFID MFRC522
    - Módulo Relé 5V
    - Painel de Botões Analógicos
    - Painel LCD com módulo I2C
    - Botões e LEDs

  Autores:
    - Francisco Passos (Desenvolvimento)
    - Dr. Edvaldo Alves (Orientação)
    - Dr. Leo Sousa (Orientação)

  Versão: 2.0
  Data de desenvolvimento:    20 de Maio de 2026
  Data de modificação:        25 de Maio de 2026

  Para mais informações, consulte a documentação do projeto disponibilizado
  no repositório oficial no GitHub.
*/

 
#include "RFID.h"
#include "Button.h"
#include "Storage.h"

// Pinos de controle
const int relayPin = 2;           
const int modeSwitchPin = 6;      

// Controladores dos dispositivos
RFIDController rfid(10, 9);          
ButtonController buttons(A3);         
StorageController storage;            

bool adminMode = false;              

// Inicialização do sistema
void setup() {
  Serial.begin(9600);
  rfid.begin();
  buttons.begin();
  storage.begin();
  
  pinMode(relayPin, OUTPUT);
  pinMode(modeSwitchPin, INPUT_PULLUP);
  digitalWrite(relayPin, LOW);
  
  Serial.println(F("System started"));
}


// Abre a porta acionando o relé por 3 segundos
void unlockDoor() {
  digitalWrite(relayPin, HIGH);
  delay(3000);
  digitalWrite(relayPin, LOW);
}


// Loop principal - seleciona entre modo admin ou leitura
void loop() {
  if (!digitalRead(modeSwitchPin)) {
    loopAdmin();
  } else {
    loopRead();
  }
}


// Loop de leitura - verifica cartões e botões de liberação rápida
void loopRead() {
  // Verifica se um cartão foi detectado
  if (rfid.cardDetected()) {
    rfid.displayUID();
    
    // Compara o UID com os armazenados na EEPROM
    if (storage.uidExists(rfid.getUID())) {
      Serial.println(F("Access granted"));
      unlockDoor();
    } else {
      Serial.println(F("Access denied"));
    }
    
    rfid.stop();
    delay(1000);
  }
  
  // Verifica se um botão foi pressionado para abrir manualmente
  buttons.update();
  
  if (buttons.getButton() != Button::NONE) {
    Serial.println(F("Door opened"));
    unlockDoor();
    delay(1000);
  }
}


// Loop administrativo - adiciona ou remove cartões
void loopAdmin() {
  // Verifica se um cartão foi detectado
  if (rfid.cardDetected()) {
    rfid.displayUID();
    const byte* uid = rfid.getUID();
    
    // Aguarda comando do botão
    buttons.update();
    Button btn = buttons.getButton();
    
    // Grava o cartão na EEPROM se o botão RECORD foi pressionado
    if (btn == Button::RECORD) {
      storage.addUID(uid);
    } 
    // Remove o cartão na EEPROM se o botão REMOVE foi pressionado
    else if (btn == Button::REMOVE) {
      storage.removeUID(uid);
    }
    
    rfid.stop();
    delay(1000);
  }
  
  buttons.update();
}
