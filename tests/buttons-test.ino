enum class BUTTON{
  NONE, BUTTON_RECODE, BUTTON_DELETE, BUTTON_CANCEL, BUTTON_CONFIRM
};

BUTTON buttonRead(int value){
  if(value < 50)        return BUTTON::BUTTON_CONFIRM;
  else if(value < 150)  return BUTTON::BUTTON_RECODE;
  else if(value < 350)  return BUTTON::BUTTON_DELETE;
  else if(value < 700)  return BUTTON::BUTTON_CANCEL;
  else                  return BUTTON::NONE;
}

void setup(){
  Serial.begin(9600);
}

BUTTON lastButton = BUTTON::NONE;

void loop(){
  int value = analogRead(A0);
  BUTTON button = buttonRead(value);

  if(button != lastButton){
    lastButton = button;

    switch(button){
      case BUTTON::BUTTON_RECODE:
        Serial.println(F("recode"));
        break;

      case BUTTON::BUTTON_DELETE:
        Serial.println(F("delete"));
        break;

      case BUTTON::BUTTON_CANCEL:
        Serial.println(F("cancel"));
        break;

      case BUTTON::BUTTON_CONFIRM:
        Serial.println(F("confirm"));
        break;

      case BUTTON::NONE:
        Serial.println(F("none..."));
        break;
    }
  }

  delay(50);
}