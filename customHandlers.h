
#include <Arduino_StoneHMIv2.h>
extern StoneHMI hmi;
int sliderValue;
int sliderSaved;

void printButton(String dataToPrint){
  Serial.print("Button "); Serial.print(dataToPrint); Serial.println(" got Pressed");
}

void buttonUpdate_handler(byte buttonStatus)
{
  switch (buttonStatus) {
    printButton("update");
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
  printButton("Save");
  switch (buttonStatus) {
        case 0x01: {
        sliderSaved = sliderValue;
        break;
      }
  }
}
void buttonBack_handler(byte buttonStatus) {
  printButton("back");
}
void beep_button_handler(byte buttonStatus) {
  printButton("beeping");
}
void homeButton_handler(byte buttonStatus) {
  printButton("Home");
}
void buttonPrint_handler(byte buttonStatus){
  printButton("Print");
  switch (buttonStatus) {
        case 0x01: {
          if (sliderSaved != NULL){
            hmi.setLabelText("label_print", sliderSaved);
          }
        break;
      }
  }
}
void slider_handler(float sliderStep) {
  //sliderValue = sliderStep;
  //hmi.sendSet(CmdCode::SetText, "label_scrollbar", WidgetType::Label, sliderStep);
  sliderValue = sliderStep;
  hmi.setLabelText("label_saved_value", sliderStep);
}

