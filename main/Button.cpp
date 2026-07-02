#include "Button.h"

// Construtor - inicializa os botões no pino Analógico a qual estão conectadas
ButtonController::ButtonController(byte pin) {
  _pin = pin;
}

// Configura o pino como entrada
void ButtonController::begin() {
  pinMode(_pin, INPUT);
}

// Mapeia os valores analógicos para botões específicos
Button ButtonController::readButton(int value) {
  if (value < 40)                   return Button::CONFIRM;
  if (value >= 40 && value < 120)   return Button::RECORD;
  if (value >= 120 && value < 300)  return Button::REMOVE;
  if (value >= 300 && value < 700)  return Button::CANCEL;
  return Button::NONE;
}
 
void ButtonController::update() {
  // Lê o valor analógico do pino
  int value = analogRead(_pin);
  Button button = readButton(value);
  
  // Se nenhum botão foi pressionado, reseta os estados
  if (button == Button::NONE) {
    lastButton = Button::NONE;
    currentButton = Button::NONE;
    return;
  }
  
  // Detecta mudança no botão pressionado
  if (button != lastButton) {
    unsigned long now = millis();
    
    // Verifica se passou tempo suficiente desde o último botão (debounce)
    if (now - lastButtonTime >= DEBOUNCE_TIME) {
      lastButton = button;
      currentButton = button;
      lastButtonTime = now;
      
      // Imprime o botão pressionado no serial
      switch (button) {
        case Button::CONFIRM:   
          Serial.println(F("CONFIRM"));
          break;
          
        case Button::RECORD:    
          Serial.println(F("RECORD"));
          break;
          
        case Button::REMOVE:    
          Serial.println(F("REMOVE"));
          break;
          
        case Button::CANCEL:    
          Serial.println(F("CANCEL"));
          break;
      }
    }
  }
}

// Retorna o botão atualmente pressionado
Button ButtonController::getButton() {
  return currentButton;
}
