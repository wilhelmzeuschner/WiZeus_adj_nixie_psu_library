/// WiZeus_adj_nixie_psu_library.cpp
/// @author Wilhelm Zeuschner
/// @date 03. October 2021
/// @version 1

#include <Wire.h>

#include "WiZeus_adj_nixie_psu_library.h"
#include "adjNixiePSU_config.h"

adjNixiePSU::adjNixiePSU(int shdnPin)
{
	r1 = DEFAULT_R1;
	r2 = DEFAULT_R2;
	rPotMax = DEFAULT_R_POT_MAX;

	shdnPin = shdnPin;

	outputVoltage = 0;
	outputState = false;

	digiPotConnectionStatus = 0;
}

adjNixiePSU::adjNixiePSU(int shdnPin, unsigned long r1, unsigned long r2, int rPotMax)
{
	r1 = r1;
	r2 = r2;
	rPotMax = rPotMax;

	shdnPin = shdnPin;

	outputVoltage = 0;
	outputState = false;

	digiPotConnectionStatus = 0;
}

int adjNixiePSU::setOutputVoltage(unsigned int outputVoltage)
{
	/// Clamp to min / max
	if (outputVoltage > MAX_OUTPUT_VOLTAGE)
	{
		outputVoltage = MAX_OUTPUT_VOLTAGE;
	}
	else if (outputVoltage < MIN_OUTPUT_VOLTAGE)
	{
		outputVoltage = MIN_OUTPUT_VOLTAGE;
	}

	/// Check if connection to digi pot already exists
	if (digiPotConnectionStatus == 1)
	{
	}
	/// Not connected yet, attempt to connect
	else
	{
		/// Pot was not found
		if (findDigiPot(POT_ADDRESS) == -1)
		{
			return -1;
		}
		/// Pot was found, now begin to set the voltage
		else
		{
		}
	}
}

int adjNixiePSU::findDigiPot(int address)
{
	byte error;

	Wire.begin();
	Wire.beginTransmission(address);
	error = Wire.endTransmission();

	/// A I2C device was found at the specified address, assume it is the digi pot
	if (error == 0)
	{
		digiPotConnectionStatus = 1;
		return digiPotConnectionStatus;
	}
	/// No device was found
	else
	{
		digiPotConnectionStatus = -1;
		return digiPotConnectionStatus;
	}
}

byte adjNixiePSU::calcPotRegValFromVoltage(unsigned int voltage)
{
	unsigned int rPot;
	byte potReg;

	/// Calculate the digi pot resistance required to achieve the desired voltage
	rPot = ((r1 * V_REF))/(voltage - V_REF)) - r2;

	/// Calculate the potentiometer value (0 to 127)
	potReg = float((float(temp_resistance) / float(rPotMax)) * POT_NUM_STEPS);



	return 0;
}

int adjNixiePSU::getSetOutputVoltage()
{
	return outputVoltage;
}

int adjNixiePSU::turnOutputOn()
{
	if (digiPotConnectionStatus == 1)
	{
		outputState = HV_PSU_ON;
		digitalWrite(shdnPin, HV_PSU_ON);
		return 0;
	}
	else
		return -1;
}

int adjNixiePSU::turnOutputOff()
{
	if (digiPotConnectionStatus)
	{
		outputState = HV_PSU_OFF;
		digitalWrite(shdnPin, HV_PSU_OFF);
		return 0;
	}
	else
		return -1;
}
