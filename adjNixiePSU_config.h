/// adjNixiePSU_config.h
/// @author Wilhelm Zeuschner
/// @date 03. October 2021
/// @version 1

#ifndef __adjNixiePSU_config_H
#define __adjNixiePSU_config_H

/// This is the maximum allowed voltage.
/// If the user attempts to set a higher voltage, it is clamped to this value
#define MAX_OUTPUT_VOLTAGE 		170

/// These are the default resistor values
#define DEFAULT_R1 				1000000
#define DEFAULT_R2 				8489
#define DEFAULT_R_POT_MAX 		10000

/// This is the I2C address of the digital potentiometer IC
/// 46 (dec) corresponds to 0x2E HEX
#define POT_ADDRESS 			46

/// Logic assignments for ON / OFF
/// These might seem illogical by themselves but the SHDN pin operates as active low.
/// If the aliases are used in the code, this is no issue / should not be confusing 
#define HV_PSU_ON				0
#define HV_PSU_OFF				1


#endif