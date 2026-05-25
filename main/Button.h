/*
  Controlador de Botões com Debounce
  Gerencia múltiplos botões com leitura analógica
*/

#ifndef BUTTON_H
#define BUTTON_H
#include <Arduino.h>

 
// Enumeração dos botões disponíveis
enum class Button {
  NONE, RECORD, REMOVE, CANCEL, CONFIRM
};

 
class ButtonController {
  private:
    byte _pin;                                    // Pino analógico de leitura
    unsigned long lastButtonTime = 0;             // Último tempo de pressão de botão
    const unsigned long DEBOUNCE_TIME = 700;      // Tempo mínimo entre pressões (ms)
    
    Button lastButton = Button::NONE;             // Botão lido anteriormente
    Button currentButton = Button::NONE;          // Botão atualmente pressionado
    
    // Converte valor analógico para tipo de botão
    Button readButton(int value);
  
  public:
    ButtonController(byte pin);
    void begin();
    void update();
    Button getButton();
};
 
#endif
