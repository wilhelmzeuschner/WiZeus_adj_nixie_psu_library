/// WiZeus_adj_nixie_psu_library.h
/// @author Wilhelm Zeuschner
/// @date 03. October 2021
/// @version 1

#ifndef __WiZeus_adj_nixie_psu_library_H
#define __WiZeus_adj_nixie_psu_library_H

#if (ARDUINO >= 100)
#include <Arduino.h>
#else
#include <WProgram.h>
#include <pins_arduino.h>
#endif

#include "adjNixiePSU_config.h"

/// @brief This class implements the controls for the HV PSU
///
/// @details There are two ways to initialize an instance of this class
/// The default constructor takes no parameters and assumes the default values for the feedback resistors
/// If these values do not match the hardware configuration, the second constructor option allows to pass custom values
class adjNixiePSU
{

public:
	/// Default constructor which assumes default resistance values
	/// @param shdnPin specifies which Arduino pin is connected to the SHDN pin of the module
	/// @see adjNixiePSU(int shdnPin, int r1, int r2, int rPotMax)
	adjNixiePSU(int shdnPin);

	/// Advanced constructor which allows to pass custom reststance values
	/// @param r1 This is the "upper" part of the voltage divider, i.e. the resistor that drops most of the voltage
	/// @param r2 This is the "lower" part of the voltage divider, which is in series with the digital potentiometer
	/// @param rPotMax This is the resistance the digital potentiometer has on its maximum setting
	/// @param shdnPin Specifies which Arduino pin is connected to the SHDN pin of the module
	/// @see adjNixiePSU(int shdnPin)
	adjNixiePSU(int shdnPin, int r1, int r2, int rPotMax);

	/// Sets the output voltage to the specified value
	/// @param outputVoltage Desired output voltage
	/// @attention Since there is NO feedback of the actual output voltage to the Arduino, the actual output voltage might vary. The module itself does use a closed loop control system. This means that the module will attempt to maintain the voltage, independent of the load (within its physical limitations).
	/// @see getSetOutputVoltage()
	void setOutputVoltage(int outputVoltage);

	/// Returns the currently set output voltage
	/// @return Currently set output voltage as int
	/// @attention Just as setOutputVoltage(int voltage), this method has no actual way to measure the output voltage. It just returns the value the output voltage was set to.
	int getSetOutputVoltage();

	/// Turns the high voltage output ON by setting the SHDN pin LOW
	/// @return 0 if executed successfully, -1 on error: no connection to digi pot
	/// @see turnOutputOff()
	int turnOutputOn();

	/// Turns the high voltage output OFF by setting the SHDN pin HIGH
	/// @return 0 if executed successfully, -1 on error: no connection to digi pot
	/// @see turnOutputOn()
	int turnOutputOff();

private:
	/// Internal class variables
	int r1, r2, rPotMax;
	int shdnPin;
	int outputVoltage;

	/// Saves the current output state (ON / OFF), defaults to off on startup
	bool outputState;

	/// Status for the connection to the digi pot
	/// 0 if not connected / not found
	/// 1 if connected / found
	int digiPotConnectionStatus;
};

#endif