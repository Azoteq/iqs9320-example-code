/******************************************************************************
 *                                                                            *
 *                                                                            *
 *                                Copyright by                                *
 *                                                                            *
 *                              Azoteq (Pty) Ltd                              *
 *                          Republic of South Africa                          *
 *                                                                            *
 *                           Tel: +27(0)21 863 0033                           *
 *                           E-mail: info@azoteq.com                          *
 *                                                                            *
 * ========================================================================== *
 * @file        IQS9320.h                                                      *
 * @brief       This file contains all the necessary settings for the IQS9320  *
 *              and this file can be changed from the GUI or edited here      *
 * @author      JN. Lochner - Azoteq PTY Ltd                                  *
 * @version     v1.5.2                                                        *
 * @date        2023                                                          *
 * ========================================================================== *
 * @attention  Makes use of the following standard Arduino libraries:         *
 * - Arduino.h -> Included in IQS9320.h, comes standard with Arduino           *
 * - Wire.h    -> Included in IQS9320.h, comes standard with Arduino           *
 ******************************************************************************/

#ifndef IQS9320_H
#define IQS9320_H

// Include Files
#include "Arduino.h"
#include "Wire.h"
#include "./inc/iqs9320_addresses.h"

/* Select the version of IQS9320 used */
// #define IQS9320_V0_4
#define IQS9320_V0_7

/* Choose to ATI on start-up or read the Mirror selection and disable ATI (should be true for IQS9320 v0.3 or less) */
#define IQS9320_RESET_ON_STARTUP        false
#define IQS9320_I2C_RETRY               10

// Public Global Definitions
/* For use with Wire.h library. True argument with some functions closes the
   I2C communication window.*/
#define STOP    true
/* For use with Wire.h library. False argument with some functions keeps the
   I2C communication window open. */
#define RESTART false

// Device Info
#define IQS9320_PRODUCT_NUM             1814

// Memory addresses that changed over IQS9320 versions.
#ifdef IQS9320_V0_4
#define IQS9320_MM_ACTIVATION_FLAGS             0x1002
#define IQS9320_MM_REFERENCE_HALT_FLAGS         0x1005
#define IQS9320_MM_CH0_NORM_DELTA               0x100C
#define IQS9320_MM_CH0_DELTA                    0x1034

#define IQS9320_MM_INDIVIDUAL_THRESHOLDS_CH0    0x30C8
#define IQS9320_MM_CYCLE_0_CHANNELS             0x30DC
#define IQS9320_MM_RX_SELECT                    0x30E2
#define IQS9320_MM_TX_SELECT                    0x30F6
#define IQS9320_MM_ATI_TARGET                   0x310A
#define IQS9320_MM_ACTIVATION_THRESHOLD         0x310E
#define IQS9320_MM_LTA_BETA_FILTER              0x3112
#define IQS9320_MM_REFERENCE_HALT_TIMEOUT       0x311C
#define IQS9320_MM_ACTIVATION_HYSTERESIS        0x311D
#endif
#ifdef IQS9320_V0_7
#define IQS9320_MM_ACTIVATION_FLAGS             0x100A
#define IQS9320_MM_REFERENCE_HALT_FLAGS         0x1006
#define IQS9320_MM_CH0_NORM_DELTA               0x100E
#define IQS9320_MM_CH0_DELTA                    0x1036

#define IQS9320_MM_INDIVIDUAL_THRESHOLDS_CH0    0x30F0
#define IQS9320_MM_CYCLE_0_CHANNELS             0x3104
#define IQS9320_MM_RX_SELECT                    0x310A
#define IQS9320_MM_TX_SELECT                    0x311E
#define IQS9320_MM_ATI_TARGET                   0x3132
#define IQS9320_MM_ACTIVATION_THRESHOLD         0x3136
#define IQS9320_MM_LTA_BETA_FILTER              0x313A
#define IQS9320_MM_REFERENCE_HALT_TIMEOUT       0x3144
#define IQS9320_MM_ACTIVATION_HYSTERESIS        0x3145
#endif

// System event bits
#define IQS9320_ATI_ACTIVE_BIT		 3
#define IQS9320_SHOW_RESET_BIT		 6

// Utility Bits
#define IQS9320_RECONFIG_DEV_BIT	0
#define IQS9320_EXE_CALLIBRATION_BIT	5
#define IQS9320_ACK_RESET_BIT		6
#define IQS9320_SW_RESET_BIT		7
#define IQS9320_RE_ATI_BIT		4
#define IQS9320_RESEED_BIT		3
#define IQS9320_MOVE_EN_BIT	        4

#define IQS9320_MAX_CNTS_BIT_0		0
#define IQS9320_MAX_CNTS_BIT_1		1
#define IQS9320_MAX_CNTS_BIT_2		2

/* Defines and structs for IQS9320 states */
/**
* @brief  iqs9320 Init Enumeration.
*/
typedef enum {
        IQS9320_INIT_NONE = (uint8_t) 0x00,
        IQS9320_INIT_VERIFY_PRODUCT,
        IQS9320_INIT_READ_RESET,
	IQS9320_INIT_CHIP_RESET,
        IQS9320_INIT_ACK_RESET,
        IQS9320_INIT_UPDATE_SETTINGS,
        IQS9320_INIT_DEFAULT_READ_SYS_STATUS,
        IQS9320_INIT_RECONFIG_DEV,
        IQS9320_INIT_ATI,
        IQS9320_INIT_WAIT_FOR_ATI,
        IQS9320_INIT_RESEED,
        IQS9320_INIT_READ_DATA,
	IQS9320_INIT_DONE
} iqs9320_init_e;

typedef enum {
        IQS9320_STATE_NONE = (uint8_t) 0x00,
        IQS9320_STATE_START,
        IQS9320_STATE_INIT,
        IQS9320_STATE_SW_RESET,
        IQS9320_STATE_CHECK_RESET,
	IQS9320_STATE_RUN,
        IQS9320_STATE_IDLE,
} iqs9320_state_e;

typedef enum {
        IQS9320_CH0 = (uint8_t) 0x00,
        IQS9320_CH1,
        IQS9320_CH2,
        IQS9320_CH3,
        IQS9320_CH4,
        IQS9320_CH5,
        IQS9320_CH6,
        IQS9320_CH7,
        IQS9320_CH8,
        IQS9320_CH9,
        IQS9320_CH10,
        IQS9320_CH11,
        IQS9320_CH12,
        IQS9320_CH13,
        IQS9320_CH14,
        IQS9320_CH15,
        IQS9320_CH16,
        IQS9320_CH17,
        IQS9320_CH18,
        IQS9320_CH19,
} iqs9320_channel_e;

typedef enum {
        IQS9320_NORMAL_POWER = (uint8_t) 0x00,
        IQS9320_LOW_POWER,
        IQS9320_ULTRA_LOW_POWER,
} iqs9320_power_mode_e;

typedef enum
{
        IQS9320_CH_NONE = (uint8_t) 0x00,
        IQS9320_CH_FILTER_HALT,
        IQS9320_CH_ACTIVATION,
        IQS9320_CH_UNKNOWN,
} iqs9320_ch_states;

/* IQS9320 Memory map data variables, only save the data that might be used
during program runtime */
#pragma pack(1)
typedef struct
{
	/* READ ONLY */			        //  I2C Addresses:
	uint8_t VERSION_DETAILS[12]; 	        // 	0x0000 -> 0x000A
	uint8_t SYSTEM_STATUS[2];               // 	0x1000
        uint8_t ATI_ERROR[4];                   // 	0x1002
        uint8_t ACTIVATION_FLAGS[4];            // 	0x1002 (v0.4) 0x100A (v0.7)
        uint8_t FILTER_HALT_FLAGS[4];           // 	0x1005 (v0.4) 0x1006 (v0.7)
        uint8_t CH_NORM_DELTA[20];              // 	0x100C (v0.4) 0x100E (v0.7)
        uint8_t CH_MOVEMENT[20];                // 	0x1020 (v0.4) 0x1022 (v0.7)
        uint8_t CH_DELTA[40];                   // 	0x1034 (v0.4) 0x1036 (v0.7)

	/* READ WRITE */		        //  I2C Addresses:
	uint8_t SYSTEM_CONTROL[2]; 	        // 	0x2000
        uint8_t MIRROR_SELECTION[40];           // 	0x3000 -> 0x301D
} IQS9320_MEMORY_MAP;
#pragma pack(4)

#pragma pack(1)
typedef struct {
        iqs9320_state_e        state;
        iqs9320_init_e         init_state;
}iqs9320_s;
#pragma pack(4)

// Class Prototype
class IQS9320
{
public:
        // Public Constructors
        IQS9320();

        // Public Device States
        iqs9320_s iqs9320_state;

        // Public Variables
        IQS9320_MEMORY_MAP IQSMemoryMap;
        bool new_data_available;

        // Public Methods
        void begin(uint8_t deviceAddressIn, uint8_t mclr_pin, uint8_t nChannels);
        bool init(void);
        void run(void);
        void queueValueUpdates(void);
        void requestData(void);

        uint16_t getProductNum(bool stopOrRestart);
        uint8_t getmajorVersion(bool stopOrRestart);
        uint8_t getminorVersion(bool stopOrRestart);

        bool readATIactive(void);
        void acknowledgeReset(bool stopOrRestart);
        void ReATI(bool stopOrRestart);
        void ReSeed(bool stopOrRestart);
        void SW_Reset(bool stopOrRestart);

        void DebugOn(void);
        void DebugOff(void);

        void updateInfoFlags(bool stopOrRestart);
        bool checkReset(void);

        void updateSettings(bool stopOrRestart);
        void reconfigureDevice(bool stopOrRestart);
        void enableMovement(bool enable, bool stopOrRestart);
        void changeDefaultRead(uint16_t read_address, bool stopOrRestart);
        void executeCallibration(bool stopOrRestart);
        void readATIMirrors(bool stopOrRestart);

        bool getChannelActivation(iqs9320_channel_e ch);
        bool getChannelFilterHalt(iqs9320_channel_e ch);
        uint8_t getChannelNormDelta(iqs9320_channel_e ch);
        uint8_t getChannelMovement(iqs9320_channel_e ch);
        int16_t getChannelDelta(iqs9320_channel_e ch);
        iqs9320_power_mode_e getPowerMode(void);

private:
        // Private Variables
        uint8_t _deviceAddress;
        uint8_t _nChannels;
        uint8_t _mclr_pin;
        bool _debug_en;

        // Private Methods
        void readRandomBytes8(uint8_t deviceAddress, uint8_t memoryAddress, uint8_t numBytes, uint8_t bytesArray[], bool stopOrRestart);
        void readRandomBytes16(uint8_t deviceAddress, uint16_t memoryAddress, uint8_t numBytes, uint8_t bytesArray[], bool stopOrRestart);
        void writeRandomBytes8(uint8_t deviceAddress, uint8_t memoryAddress, uint8_t numBytes, uint8_t bytesArray[], bool stopOrRestart);
        void writeRandomBytes16(uint8_t deviceAddress, uint16_t memoryAddress, uint8_t numBytes, uint8_t bytesArray[], bool stopOrRestart);
        bool getBit(uint8_t data, uint8_t bit_number);
        uint8_t setBit(uint8_t data, uint8_t bit_number);
        uint8_t clearBit(uint8_t data, uint8_t bit_number);
};
#endif // IQS9320_h
