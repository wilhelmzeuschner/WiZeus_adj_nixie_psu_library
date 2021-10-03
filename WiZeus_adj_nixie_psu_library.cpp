/// WiZeus_adj_nixie_psu_library.cpp
/// @author Wilhelm Zeuschner
/// @date 03. October 2021
/// @version 1

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

adjNixiePSU::adjNixiePSU(int shdnPin, int r1, int r2, int rPotMax)
{
	r1 = r1;
	r2 = r2;
	rPotMax = rPotMax;

	shdnPin = shdnPin;

	outputVoltage = 0;
	outputState = false;

	digiPotConnectionStatus = 0;
}

int outputVoltage::getSetOutputVoltage()
{
	return outputVoltage;
}

int outputVoltage::turnOutputOn()
{
	if (digiPotConnectionStatus)
	{
		outputState = HV_PSU_ON;
		digitalWrite(shdnPin, HV_PSU_ON);
		return 0;
	}
	else
		return -1;
}

int outputVoltage::turnOutputOff()
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