#include <Arduino.h>
#include <WiZeus_adj_nixie_psu_library.h>

#define SHDN_PIN    12



adjNixiePSU myNixiePSU(SHDN_PIN);

void setup() {

  Serial.begin(115200);
  Serial.println(F("Demo Code for HV Nixie PSU"));

  //Initalize
  myNixiePSU.init();

  //Set Ouput Voltage to 100V
  myNixiePSU.setOutputVoltage(200);

  //Activate the output (as long as it is not enabled, no high voltage will be generated)
  myNixiePSU.turnOutputOn();
  delay(10000);
  myNixiePSU.turnOutputOff();

}


void loop() {

}
