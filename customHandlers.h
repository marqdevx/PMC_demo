
#include <Arduino_StoneHMIv2.h>
extern StoneHMI hmi;
extern int sliderValue;
int sliderSaved;

void buttonUpdate_handler(byte buttonStatus)
{
  switch (buttonStatus) {
    case 0x02: {
        // hmi.sendGet(CmdCode::GetValue, "slider", WidgetType::Slider, &sliderValue);
        //hmi.getSliderValue("slider" , &sliderValue);
        //hmi.sendGet(CmdCode::GetPercent, "slider", WidgetType::Slider, &sliderValue);
        //hmi.getLabelValue("label_value", &sliderValue);
        hmi.setLabelText("label_saved_value", sliderValue);
        
        break;
      }
  }
}

void buttonSave_handler(byte buttonStatus) {
  switch (buttonStatus) {
        case 0x01: {
        Serial.print("press");
        sliderSaved = sliderValue;
        
        hmi.sendSet(CmdCode::SetText, "label_print", WidgetType::Label, sliderSaved);
        break;
      }
  }
}
void buttonBack_handler(byte buttonStatus) {}
void beep_button_handler(byte buttonStatus) {}
void homeButton_handler(byte buttonStatus) {}
void slider_handler(float sliderStep) {
  //sliderValue = sliderStep;
  hmi.sendSet(CmdCode::SetText, "label_scrollbar", WidgetType::Label, sliderStep);
}