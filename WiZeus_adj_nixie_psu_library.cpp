/// WiZeus_adj_nixie_psu_library.cpp
/// @author Wilhelm Zeuschner
/// @date 03. October 2021
/// @version 1

#include <Arduino.h>
#include <Wire.h>

#include "WiZeus_adj_nixie_psu_library.h"
#include "adjNixiePSU_config.h"

adjNixiePSU::adjNixiePSU(int inShdnPin)
{
	r1 = DEFAULT_R1;
	r2 = DEFAULT_R2;
	rPotMax = DEFAULT_R_POT_MAX;

	shdnPin = inShdnPin;

	outputVoltage = 0;
	outputState = false;

	digiPotConnectionStatus = -1;
}

adjNixiePSU::adjNixiePSU(int inShdnPin, unsigned long inR1, unsigned long inR2, int inRPotMax)
{
	r1 = inR1;
	r2 = inR2;
	rPotMax = inRPotMax;

	shdnPin = inShdnPin;

	outputVoltage = 0;
	outputState = false;

	digiPotConnectionStatus = -1;
}

void adjNixiePSU::init()
{
	pinMode(shdnPin, OUTPUT);
	turnOutputOff();

	//Attempt to connect to the digi-pot
	findDigiPot(POT_ADDRESS);
}

int adjNixiePSU::setOutputVoltage(unsigned int inOutputVoltage)
{
	/// Clamp outputVoltage to min / max
	if (inOutputVoltage > MAX_OUTPUT_VOLTAGE)
		outputVoltage = MAX_OUTPUT_VOLTAGE;

	else if (inOutputVoltage < MIN_OUTPUT_VOLTAGE)
		outputVoltage = MIN_OUTPUT_VOLTAGE;

	/// Check if connection to digi pot already exists
	if (digiPotConnectionStatus == 1)
	{
		/// Write data to digi pot
		Wire.beginTransmission(POT_ADDRESS);
		Wire.write(byte(POT_INSTRUCTION_ADDR));
		Wire.write(calcPotRegValFromVoltage(outputVoltage));
		Wire.endTransmission();

		return outputVoltage;
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
			/// Write data to digi pot
			Wire.beginTransmission(POT_ADDRESS);
			Wire.write(byte(POT_INSTRUCTION_ADDR));
			Wire.write(calcPotRegValFromVoltage(outputVoltage));
			Wire.endTransmission();

			return outputVoltage;
		}
	}
}

int adjNixiePSU::findDigiPot(int address)
{
	unsigned char error;

	Wire.begin();
	Wire.beginTransmission(address);
	error = Wire.endTransmission();
	Wire.endTransmission();

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

unsigned char adjNixiePSU::calcPotRegValFromVoltage(unsigned int voltage)
{
	unsigned int rPot;
	unsigned char potReg;

	/// Calculate the digi pot resistance required to achieve the desired voltage
	rPot = ((r1 * V_REF) / (voltage - V_REF)) - r2;

	/// Calculate the potentiometer value (0 to 127)
	potReg = float((float(rPot) / float(rPotMax)) * POT_NUM_STEPS);

	if (potReg > 127)
	{
		potReg = 127;
	}
	else if (potReg < 0)
	{
		potReg = 0;
	}

	return potReg;
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
		digitalWrite(shdnPin, outputState);
		return 0;
	}
	else
		return -1;
}

int adjNixiePSU::turnOutputOff()
{
	outputState = HV_PSU_OFF;
	digitalWrite(shdnPin, outputState);
	return 0;
}

unsigned long adjNixiePSU::getR1()
{
	return r1;
}

unsigned long adjNixiePSU::getR2()
{
	return r2;
}

unsigned int adjNixiePSU::getRPotMax()
{
	return rPotMax;
}

unsigned int adjNixiePSU::getSHDNPin()
{
	return shdnPin;
}

bool adjNixiePSU::getOutputState()
{
	return outputState;
}

int adjNixiePSU::getDigiPotConnectionStatus()
{
	return digiPotConnectionStatus;
}