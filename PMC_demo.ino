//#include <Arduino_StoneHMIv2.h>
#include "customHandlers.h"

// For TTL connection over Serial1/UART1
// StoneHMI hmi(Serial1, SerialType::SERIAL_TTL);

// For RS485 connection on PMC
StoneHMI hmi(machinecontrol::comm_protocols.rs485, SerialType::SERIAL_RS485);
//extern StoneHMI hmi;

void setup()
{
  // put your setup code here, to run once:

  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.print("Initializing the Arduino/Stone interface... ");
  while (!hmi.begin())
  {
    Serial.print('.');
    delay(500);
  }
  Serial.println("done.");

  Serial.print("Restarting the Stone display...");
  hmi.sysReboot();
  Serial.println(" done.");

  /*Serial.print("Connecting to the Stone display...");
  while (!hmi.sysHello()) {
    Serial.print('.');
    delay(100);
  }
  Serial.println(" done.");
*/
  Serial.print("Version: ");
  String version;
  hmi.sysVersion(&version);
  Serial.println(version);

  // Buttons handlers

  hmi.addButtonHandler("button_update", buttonUpdate_handler);
  hmi.addButtonHandler("button_save", buttonSave_handler);
  hmi.addButtonHandler("button_back_home", buttonBack_handler);

  hmi.addButtonHandler("beep_button", beep_button_handler);
  hmi.addButtonHandler("beep_button_home", beep_button_handler);

  hmi.addButtonHandler("home_button", homeButton_handler);

  // Slider handler
  hmi.addSliderChangedHandler("slider", slider_handler);

  hmi.sendSet(CmdCode::SetText, "label_updated", WidgetType::Label, "sliderValue");

  hmi.debug();
}
constexpr unsigned long sendCommandsInterval { 5000 };
unsigned long sendCommandsNow {};
void loop()
{
  // put your main code here, to run repeatedly:
  hmi.loop();

  if (millis() > sendCommandsNow)
  {
    int sliderValue;
    hmi.sendGet(CmdCode::GetValue, "slider", WidgetType::Slider, &sliderValue);

    hmi.sendSet(CmdCode::SetText, "label_updated", WidgetType::Label, sliderValue);
    Serial.print("Slider: ");
    Serial.println(sliderValue);
    sendCommandsNow = millis() + sendCommandsInterval;
  }
}
