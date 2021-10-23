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
	/// @see adjNixiePSU(int shdnPin, unsigned long r1, unsigned long r2, int rPotMax)
	adjNixiePSU(int shdnPin);

	/// Advanced constructor which allows to pass custom reststance values
	/// @param r1 This is the "upper" part of the voltage divider, i.e. the resistor that drops most of the voltage
	/// @param r2 This is the "lower" part of the voltage divider, which is in series with the digital potentiometer
	/// @param rPotMax This is the resistance the digital potentiometer has on its maximum setting
	/// @param shdnPin Specifies which Arduino pin is connected to the SHDN pin of the module
	/// @see adjNixiePSU(int shdnPin)
	adjNixiePSU(int shdnPin, unsigned long r1, unsigned long r2, int rPotMax);

	/// Init function
	/// Sets all pins to the the right mode and attempts to connect to the digi-pot
	void init();

	/// Sets the output voltage to the specified value
	/// @param outputVoltage Desired output voltage
	/// @return Voltage value that was set. Since the passed parameter might exceed the min and max allowed voltages. Returns -1 if no connection to the digi pot could be established
	/// @attention Since there is NO feedback of the actual output voltage to the Arduino, the actual output voltage might vary. The module itself does use a closed loop control system. This means that the module will attempt to maintain the voltage, independent of the load (within its physical limitations).
	/// @see getSetOutputVoltage()
	int setOutputVoltage(unsigned int outputVoltage);

	/// Returns the currently set output voltage
	/// @return Currently set output voltage as int
	/// @attention Just as setOutputVoltage(int voltage), this method has no actual way to measure the output voltage. It just returns the value the output voltage was set to.
	int getSetOutputVoltage();

	/// Turns the high voltage output ON by setting the SHDN pin LOW
	/// @return 0 if executed successfully, -1 on error (no connection to digi pot)
	/// @see turnOutputOff()
	int turnOutputOn();

	/// Turns the high voltage output OFF by setting the SHDN pin HIGH. Does not check the connection status
	/// @return 0 
	/// @see turnOutputOn()
	int turnOutputOff();

	/// Simply returns the value of r1
	/// @return r1
	unsigned long getR1();

	/// Simply returns the value of r2
	/// @return r2
	unsigned long getR2();

	/// Simply returns the value of rPotMax
	/// @return rPotMax
	unsigned int getRPotMax();

	/// Simply returns the value of shdnPin
	/// @return shdnPin
	unsigned int getSHDNPin();

	/// Simply returns the value of outputState
	/// @return outputState
	bool getOutputState();

	/// Simply returns the value of digiPotConnectionStatus
	/// @return digiPotConnectionStatus
	int getDigiPotConnectionStatus();

private:
	/// Method attempts to find the digi pot on the I2C bus
	/// @param address digi pot I2C address
	/// @return digiPotConnectionStatus
	/// @see digiPotConnectionStatus
	int findDigiPot(int address);

	/// Calculates the necessary pot resistance value based on the supplied voltage
	/// @param voltage Desired output voltage
	/// @return 0 to 127 which corresponds to the register value the digi pot needs to be set to
	/// @attention Not all voltages are possible. Before calling this method, the voltage value should ideally already be clamped.
	unsigned char calcPotRegValFromVoltage(unsigned int voltage);

	/// Internal class variables
	unsigned long r1, r2;
	unsigned int rPotMax;
	unsigned int shdnPin;
	unsigned int outputVoltage;

	/// Saves the current output state (ON / OFF), defaults to off on startup
	bool outputState;

	/// Status for the connection to the digi pot
	/// -1 if not connected / not found
	/// 1 if connected / found
	int digiPotConnectionStatus;
};

#endif