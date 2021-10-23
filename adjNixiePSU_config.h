/// adjNixiePSU_config.h
/// @author Wilhelm Zeuschner
/// @date 03. October 2021
/// @version 1

#ifndef __adjNixiePSU_config_H
#define __adjNixiePSU_config_H

/// @brief This is the maximum allowed voltage.
/// 
/// If the user attempts to set a higher voltage, it is clamped to this value
/// @see MIN_OUTPUT_VOLTAGE
#define MAX_OUTPUT_VOLTAGE 		175

/// This is the minimum allowed voltage.
/// If the user attempts to set a lower voltage, it is clamped to this value
/// @see MAX_OUTPUT_VOLTAGE
#define MIN_OUTPUT_VOLTAGE 		85

/// These are the default resistor values
#define DEFAULT_R1 				1000000
#define DEFAULT_R2 				8489
#define DEFAULT_R_POT_MAX 		10000

/// Reference voltage of the DC converter IC
#define V_REF					1.5

/// This is the I2C address of the digital potentiometer IC
/// 46 (dec) corresponds to 0x2E HEX
#define POT_ADDRESS 			46
#define POT_INSTRUCTION_ADDR	0

/// Number of individual steps / resistances the digital pot has
#define POT_NUM_STEPS			(128-1)

/// Logic assignment for ON
/// This might seem illogical by themselves but the SHDN pin operates as active low.
/// If the alias is used in the code, this is no issue / should not be confusing
/// @see HV_PSU_OFF
#define HV_PSU_ON				LOW

/// Logic assignment for OFF
/// This might seem illogical by themselves but the SHDN pin operates as active low.
/// If the alias is used in the code, this is no issue / should not be confusing 
/// @see HV_PSU_ON
#define HV_PSU_OFF				HIGH


#endif