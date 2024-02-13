/*
* This file contains all the necessary settings for the IQS9320 and this file can
* be changed from the GUI or edited here
* File:   IQS9320_init.h
* Author: Azoteq
*/

#ifndef IQS9320_INIT_H
#define IQS9320_INIT_H

/* Change the Version Info */
/* Memory Map Position 0x0000 - 0x01 */
#define PROD_0                                   0x16
#define PROD_1                                   0x07

/* Change the Device Configuration */
/* Memory Map Position 0x2000 - 0x2011 */
#define SYSTEM_CONTROL_0                         0x06
#define SYSTEM_CONTROL_1                         0x00
#define SYSTEM_CONFIG_0                          0x4A
#define SYSTEM_CONFIG_1                          0x5E
#define NP_SAMPLING_INTERVAL_0                   0x00
#define NP_SAMPLING_INTERVAL_1                   0x00
#define NP_TIMEOUT_0                             0x88
#define NP_TIMEOUT_1                             0x13
#define LP_SAMPLING_INTERVAL_0                   0x28
#define LP_SAMPLING_INTERVAL_1                   0x00
#define LP_TIMEOUT_0                             0x88
#define LP_TIMEOUT_1                             0x13
#define ULP_SAMPLING_INTERVAL_0                  0x50
#define ULP_SAMPLING_INTERVAL_1                  0x00
#define ULP_TIMEOUT_0                            0x00
#define ULP_TIMEOUT_1                            0x00
#define DEFAULT_READ_LOCATION_0                  0x0A
#define DEFAULT_READ_LOCATION_1                  0x10

/* Change the Multipliers and Dividers A */
/* Memory Map Position 0x3000 - 0x3013 */
#define MIRROR_SEL_CH0_0                         0x21
#define MIRROR_SEL_CH0_1                         0x45
#define MIRROR_SEL_CH1_0                         0x21
#define MIRROR_SEL_CH1_1                         0x47
#define MIRROR_SEL_CH2_0                         0x21
#define MIRROR_SEL_CH2_1                         0x45
#define MIRROR_SEL_CH3_0                         0xC1
#define MIRROR_SEL_CH3_1                         0x50
#define MIRROR_SEL_CH4_0                         0xC1
#define MIRROR_SEL_CH4_1                         0x50
#define MIRROR_SEL_CH5_0                         0xC1
#define MIRROR_SEL_CH5_1                         0x52
#define MIRROR_SEL_CH6_0                         0xC1
#define MIRROR_SEL_CH6_1                         0x4E
#define MIRROR_SEL_CH7_0                         0xC1
#define MIRROR_SEL_CH7_1                         0x50
#define MIRROR_SEL_CH8_0                         0x21
#define MIRROR_SEL_CH8_1                         0x45
#define MIRROR_SEL_CH9_0                         0x21
#define MIRROR_SEL_CH9_1                         0x45

/* Change the Multipliers and Dividers B */
/* Memory Map Position 0x3014 - 0x3027 */
#define MIRROR_SEL_CH10_0                        0x21
#define MIRROR_SEL_CH10_1                        0x47
#define MIRROR_SEL_CH11_0                        0x21
#define MIRROR_SEL_CH11_1                        0x45
#define MIRROR_SEL_CH12_0                        0xC1
#define MIRROR_SEL_CH12_1                        0x4E
#define MIRROR_SEL_CH13_0                        0xC1
#define MIRROR_SEL_CH13_1                        0x4E
#define MIRROR_SEL_CH14_0                        0x21
#define MIRROR_SEL_CH14_1                        0x51
#define MIRROR_SEL_CH15_0                        0xC1
#define MIRROR_SEL_CH15_1                        0x4E
#define MIRROR_SEL_CH16_0                        0xC1
#define MIRROR_SEL_CH16_1                        0x50
#define MIRROR_SEL_CH17_0                        0xC1
#define MIRROR_SEL_CH17_1                        0x52
#define MIRROR_SEL_CH18_0                        0x21
#define MIRROR_SEL_CH18_1                        0x55
#define MIRROR_SEL_CH19_0                        0x21
#define MIRROR_SEL_CH19_1                        0x45

/* Change the Calibration Parameters A */
/* Memory Map Position 0x3028 - 0x303B */
#define CALIB_STEP_CH0                           0x02
#define CALIB_CORRECT_CH0                        0x80
#define CALIB_STEP_CH1                           0x02
#define CALIB_CORRECT_CH1                        0x80
#define CALIB_STEP_CH2                           0x02
#define CALIB_CORRECT_CH2                        0x80
#define CALIB_STEP_CH3                           0x02
#define CALIB_CORRECT_CH3                        0x80
#define CALIB_STEP_CH4                           0x02
#define CALIB_CORRECT_CH4                        0x80
#define CALIB_STEP_CH5                           0x02
#define CALIB_CORRECT_CH5                        0x80
#define CALIB_STEP_CH6                           0x02
#define CALIB_CORRECT_CH6                        0x80
#define CALIB_STEP_CH7                           0x02
#define CALIB_CORRECT_CH7                        0x80
#define CALIB_STEP_CH8                           0x02
#define CALIB_CORRECT_CH8                        0x80
#define CALIB_STEP_CH9                           0x02
#define CALIB_CORRECT_CH9                        0x80

/* Change the Calibration Parameters B */
/* Memory Map Position 0x3042 - 0x3055 */
#define CALIB_STEP_CH10                          0x02
#define CALIB_CORRECT_CH10                       0x80
#define CALIB_STEP_CH11                          0x02
#define CALIB_CORRECT_CH11                       0x80
#define CALIB_STEP_CH12                          0x02
#define CALIB_CORRECT_CH12                       0x80
#define CALIB_STEP_CH13                          0x02
#define CALIB_CORRECT_CH13                       0x80
#define CALIB_STEP_CH14                          0x02
#define CALIB_CORRECT_CH14                       0x80
#define CALIB_STEP_CH15                          0x02
#define CALIB_CORRECT_CH15                       0x80
#define CALIB_STEP_CH16                          0x02
#define CALIB_CORRECT_CH16                       0x80
#define CALIB_STEP_CH17                          0x83
#define CALIB_CORRECT_CH17                       0x32
#define CALIB_STEP_CH18                          0xB2
#define CALIB_CORRECT_CH18                       0x2F
#define CALIB_STEP_CH19                          0xFC
#define CALIB_CORRECT_CH19                       0x32

/* Change the Effective Max Delta A */
/* Memory Map Position 0x3050 - 0x3063 */
#define MAX_DELTA_E_0_0                          0x83
#define MAX_DELTA_E_0_1                          0x32
#define MAX_DELTA_E_1_0                          0xB2
#define MAX_DELTA_E_1_1                          0x2F
#define MAX_DELTA_E_2_0                          0xFC
#define MAX_DELTA_E_2_1                          0x32
#define MAX_DELTA_E_3_0                          0xA9
#define MAX_DELTA_E_3_1                          0x24
#define MAX_DELTA_E_4_0                          0x35
#define MAX_DELTA_E_4_1                          0x23
#define MAX_DELTA_E_5_0                          0x93
#define MAX_DELTA_E_5_1                          0x22
#define MAX_DELTA_E_6_0                          0xB0
#define MAX_DELTA_E_6_1                          0x26
#define MAX_DELTA_E_7_0                          0x46
#define MAX_DELTA_E_7_1                          0x27
#define MAX_DELTA_E_8_0                          0x27
#define MAX_DELTA_E_8_1                          0x31
#define MAX_DELTA_E_9_0                          0x7D
#define MAX_DELTA_E_9_1                          0x33

/* Change the Effective Max Delta B */
/* Memory Map Position 0x3064 - 0x3077 */
#define MAX_DELTA_E_10_0                         0xE3
#define MAX_DELTA_E_10_1                         0x26
#define MAX_DELTA_E_11_0                         0xED
#define MAX_DELTA_E_11_1                         0x2B
#define MAX_DELTA_E_12_0                         0x5E
#define MAX_DELTA_E_12_1                         0x26
#define MAX_DELTA_E_13_0                         0x32
#define MAX_DELTA_E_13_1                         0x27
#define MAX_DELTA_E_14_0                         0x7A
#define MAX_DELTA_E_14_1                         0x28
#define MAX_DELTA_E_15_0                         0x73
#define MAX_DELTA_E_15_1                         0x25
#define MAX_DELTA_E_16_0                         0x31
#define MAX_DELTA_E_16_1                         0x23
#define MAX_DELTA_E_17_0                         0xF2
#define MAX_DELTA_E_17_1                         0x20
#define MAX_DELTA_E_18_0                         0x97
#define MAX_DELTA_E_18_1                         0x27
#define MAX_DELTA_E_19_0                         0xB6
#define MAX_DELTA_E_19_1                         0x33

/* Change the Sampled Max Delta A */
/* Memory Map Position 0x3078 - 0x308B */
#define MAX_DELTA_S_0_0                          0xBF
#define MAX_DELTA_S_0_1                          0x32
#define MAX_DELTA_S_1_0                          0xB2
#define MAX_DELTA_S_1_1                          0x2F
#define MAX_DELTA_S_2_0                          0xFC
#define MAX_DELTA_S_2_1                          0x32
#define MAX_DELTA_S_3_0                          0xA9
#define MAX_DELTA_S_3_1                          0x24
#define MAX_DELTA_S_4_0                          0x35
#define MAX_DELTA_S_4_1                          0x23
#define MAX_DELTA_S_5_0                          0x93
#define MAX_DELTA_S_5_1                          0x22
#define MAX_DELTA_S_6_0                          0xB0
#define MAX_DELTA_S_6_1                          0x26
#define MAX_DELTA_S_7_0                          0x46
#define MAX_DELTA_S_7_1                          0x27
#define MAX_DELTA_S_8_0                          0x27
#define MAX_DELTA_S_8_1                          0x31
#define MAX_DELTA_S_9_0                          0x7D
#define MAX_DELTA_S_9_1                          0x33

/* Change the Sampled Max Delta B */
/* Memory Map Position 0x308C - 0x309F */
#define MAX_DELTA_S_10_0                         0xF2
#define MAX_DELTA_S_10_1                         0x26
#define MAX_DELTA_S_11_0                         0xED
#define MAX_DELTA_S_11_1                         0x2B
#define MAX_DELTA_S_12_0                         0x5E
#define MAX_DELTA_S_12_1                         0x26
#define MAX_DELTA_S_13_0                         0x32
#define MAX_DELTA_S_13_1                         0x27
#define MAX_DELTA_S_14_0                         0x7A
#define MAX_DELTA_S_14_1                         0x28
#define MAX_DELTA_S_15_0                         0x73
#define MAX_DELTA_S_15_1                         0x25
#define MAX_DELTA_S_16_0                         0x31
#define MAX_DELTA_S_16_1                         0x23
#define MAX_DELTA_S_17_0                         0xF2
#define MAX_DELTA_S_17_1                         0x20
#define MAX_DELTA_S_18_0                         0x97
#define MAX_DELTA_S_18_1                         0x27
#define MAX_DELTA_S_19_0                         0xB6
#define MAX_DELTA_S_19_1                         0x33

/* Change the Calibration Max Delta A */
/* Memory Map Position 0x30A0 - 0x30B3 */
#define MAX_DELTA_C_0_0                          0x00
#define MAX_DELTA_C_0_1                          0x00
#define MAX_DELTA_C_1_0                          0x00
#define MAX_DELTA_C_1_1                          0x00
#define MAX_DELTA_C_2_0                          0x00
#define MAX_DELTA_C_2_1                          0x00
#define MAX_DELTA_C_3_0                          0x00
#define MAX_DELTA_C_3_1                          0x00
#define MAX_DELTA_C_4_0                          0x00
#define MAX_DELTA_C_4_1                          0x00
#define MAX_DELTA_C_5_0                          0x00
#define MAX_DELTA_C_5_1                          0x00
#define MAX_DELTA_C_6_0                          0x00
#define MAX_DELTA_C_6_1                          0x00
#define MAX_DELTA_C_7_0                          0x00
#define MAX_DELTA_C_7_1                          0x00
#define MAX_DELTA_C_8_0                          0x00
#define MAX_DELTA_C_8_1                          0x00
#define MAX_DELTA_C_9_0                          0x00
#define MAX_DELTA_C_9_1                          0x00

/* Change the Calibration Max Delta B */
/* Memory Map Position 0x30B4 - 0x30C7 */
#define MAX_DELTA_C_10_0                         0x00
#define MAX_DELTA_C_10_1                         0x00
#define MAX_DELTA_C_11_0                         0x00
#define MAX_DELTA_C_11_1                         0x00
#define MAX_DELTA_C_12_0                         0x00
#define MAX_DELTA_C_12_1                         0x00
#define MAX_DELTA_C_13_0                         0x00
#define MAX_DELTA_C_13_1                         0x00
#define MAX_DELTA_C_14_0                         0x00
#define MAX_DELTA_C_14_1                         0x00
#define MAX_DELTA_C_15_0                         0x00
#define MAX_DELTA_C_15_1                         0x00
#define MAX_DELTA_C_16_0                         0x00
#define MAX_DELTA_C_16_1                         0x00
#define MAX_DELTA_C_17_0                         0x00
#define MAX_DELTA_C_17_1                         0x00
#define MAX_DELTA_C_18_0                         0x00
#define MAX_DELTA_C_18_1                         0x00
#define MAX_DELTA_C_19_0                         0x00
#define MAX_DELTA_C_19_1                         0x00

/* Change the Calibration Counts A */
/* Memory Map Position 0x30C8 - 0x30DB */
#define CALIBRATION_COUNTS_0_0                   0x00
#define CALIBRATION_COUNTS_0_1                   0x00
#define CALIBRATION_COUNTS_1_0                   0x00
#define CALIBRATION_COUNTS_1_1                   0x00
#define CALIBRATION_COUNTS_2_0                   0x00
#define CALIBRATION_COUNTS_2_1                   0x00
#define CALIBRATION_COUNTS_3_0                   0x00
#define CALIBRATION_COUNTS_3_1                   0x00
#define CALIBRATION_COUNTS_4_0                   0x00
#define CALIBRATION_COUNTS_4_1                   0x00
#define CALIBRATION_COUNTS_5_0                   0x00
#define CALIBRATION_COUNTS_5_1                   0x00
#define CALIBRATION_COUNTS_6_0                   0x00
#define CALIBRATION_COUNTS_6_1                   0x00
#define CALIBRATION_COUNTS_7_0                   0x00
#define CALIBRATION_COUNTS_7_1                   0x00
#define CALIBRATION_COUNTS_8_0                   0x00
#define CALIBRATION_COUNTS_8_1                   0x00
#define CALIBRATION_COUNTS_9_0                   0x00
#define CALIBRATION_COUNTS_9_1                   0x00

/* Change the Calibration Counts B */
/* Memory Map Position 0x30DC - 0x30EF */
#define CALIBRATION_COUNTS_10_0                  0x00
#define CALIBRATION_COUNTS_10_1                  0x00
#define CALIBRATION_COUNTS_11_0                  0x00
#define CALIBRATION_COUNTS_11_1                  0x00
#define CALIBRATION_COUNTS_12_0                  0x00
#define CALIBRATION_COUNTS_12_1                  0x00
#define CALIBRATION_COUNTS_13_0                  0x00
#define CALIBRATION_COUNTS_13_1                  0x00
#define CALIBRATION_COUNTS_14_0                  0x00
#define CALIBRATION_COUNTS_14_1                  0x00
#define CALIBRATION_COUNTS_15_0                  0x00
#define CALIBRATION_COUNTS_15_1                  0x00
#define CALIBRATION_COUNTS_16_0                  0x00
#define CALIBRATION_COUNTS_16_1                  0x00
#define CALIBRATION_COUNTS_17_0                  0x00
#define CALIBRATION_COUNTS_17_1                  0x00
#define CALIBRATION_COUNTS_18_0                  0x00
#define CALIBRATION_COUNTS_18_1                  0x00
#define CALIBRATION_COUNTS_19_0                  0x00
#define CALIBRATION_COUNTS_19_1                  0x00

/* Change the Individual Thresholds */
/* Memory Map Position 0x30F0 - 0x3103 */
#define INDIVIDUAL_THRESHOLDS_0                  0x28
#define INDIVIDUAL_THRESHOLDS_1                  0x28
#define INDIVIDUAL_THRESHOLDS_2                  0x28
#define INDIVIDUAL_THRESHOLDS_3                  0x28
#define INDIVIDUAL_THRESHOLDS_4                  0x28
#define INDIVIDUAL_THRESHOLDS_5                  0x28
#define INDIVIDUAL_THRESHOLDS_6                  0x28
#define INDIVIDUAL_THRESHOLDS_7                  0x28
#define INDIVIDUAL_THRESHOLDS_8                  0x28
#define INDIVIDUAL_THRESHOLDS_9                  0x28
#define INDIVIDUAL_THRESHOLDS_10                 0x28
#define INDIVIDUAL_THRESHOLDS_11                 0x28
#define INDIVIDUAL_THRESHOLDS_12                 0x28
#define INDIVIDUAL_THRESHOLDS_13                 0x28
#define INDIVIDUAL_THRESHOLDS_14                 0x28
#define INDIVIDUAL_THRESHOLDS_15                 0x28
#define INDIVIDUAL_THRESHOLDS_16                 0x28
#define INDIVIDUAL_THRESHOLDS_17                 0x28
#define INDIVIDUAL_THRESHOLDS_18                 0x28
#define INDIVIDUAL_THRESHOLDS_19                 0x28

/* Change the Channel Select and Disable */
/* Memory Map Position 0x3104 - 0x3108 */
#define CYCLE_0_SELECT                           0x0A
#define CYCLE_1_SELECT                           0x0A
#define CHANNEL_DISABLE_0                        0x00
#define CHANNEL_DISABLE_0                        0x00
#define CHANNEL_DISABLE_0                        0x00

/* Change the Rx Select */
/* Memory Map Position 0x310A - 0x311D */
#define RX_SELECT_0                              0x1E
#define RX_SELECT_1                              0x1C
#define RX_SELECT_2                              0x19
#define RX_SELECT_3                              0x17
#define RX_SELECT_4                              0x12
#define RX_SELECT_5                              0x0D
#define RX_SELECT_6                              0x08
#define RX_SELECT_7                              0x05
#define RX_SELECT_8                              0x02
#define RX_SELECT_9                              0x00
#define RX_SELECT_10                             0x1F
#define RX_SELECT_11                             0x1D
#define RX_SELECT_12                             0x1A
#define RX_SELECT_13                             0x18
#define RX_SELECT_14                             0x13
#define RX_SELECT_15                             0x0E
#define RX_SELECT_16                             0x0B
#define RX_SELECT_17                             0x06
#define RX_SELECT_18                             0x03
#define RX_SELECT_19                             0x01

/* Change the Tx Select */
/* Memory Map Position 0x311E - 0x3131 */
#define TX_SELECT_0                              0x26
#define TX_SELECT_1                              0x28
#define TX_SELECT_2                              0x2A
#define TX_SELECT_3                              0x16
#define TX_SELECT_4                              0x11
#define TX_SELECT_5                              0x0C
#define TX_SELECT_6                              0x09
#define TX_SELECT_7                              0x04
#define TX_SELECT_8                              0x2B
#define TX_SELECT_9                              0x2D
#define TX_SELECT_10                             0x29
#define TX_SELECT_11                             0x27
#define TX_SELECT_12                             0x1B
#define TX_SELECT_13                             0x15
#define TX_SELECT_14                             0x14
#define TX_SELECT_15                             0x0F
#define TX_SELECT_16                             0x0A
#define TX_SELECT_17                             0x07
#define TX_SELECT_18                             0x10
#define TX_SELECT_19                             0x2C

/* Change the ATI Target and Band */
/* Memory Map Position 0x3132 - 0x3135 */
#define ATI_TARGET_0                             0xC8
#define ATI_TARGET_1                             0x00
#define ATI_BAND_0                               0x32
#define ATI_BAND_1                               0x00

/* Change the Thresholds */
/* Memory Map Position 0x3136 - 0x3139 */
#define ACTIVATION_THRESHOLD                     0x28
#define REFERENCE_HALT_THRESHOLD                 0x14
#define FAST_REF_THRESHOLD                       0x0A
#define MOVEMENT_THRESHOLD                       0x08

/* Change the Filter Values */
/* Memory Map Position 0x313A - 0x3142 */
#define BETA_LTA_NP                              0x0A
#define BETA_LTA_LP                              0x06
#define BETA_LTA_ULP                             0x05
#define BETA_FAST_LTA_NP                         0x08
#define BETA_FAST_LTA_LP                         0x05
#define BETA_FAST_LTA_ULP                        0x04
#define BETA_COUNTS_NP                           0x02
#define BETA_COUNTS_LP                           0x01
#define BETA_COUNTS_ULP                          0x00

/* Change the Reference Halt Timeout */
/* Memory Map Position 0x3144 - 0x3144 */
#define REF_HALT_TIMEOUT_0                       0x08

/* Change the Activation Hysteresis */
/* Memory Map Position 0x3145 - 0x3145 */
#define ACTIVATION_HYSTERESIS_0                  0x05

/* Change the Timing Generator Settings */
/* Memory Map Position 0x3146 - 0x3147 */
#define TIMING_GENERATOR_0                       0x00
#define TIMING_GENERATOR_0                       0x00

/* Change the Hardware Settings */
/* Memory Map Position 0x3148 - 0x3149 */
#define HARDWARE_SETTINGS_0                      0x8C
#define HARDWARE_SETTINGS_1                      0x00

#endif	/* IQS9320_INIT_H */