/*
* This file contains all the necessary settings for the IQS9320 and this file can
* be changed from the GUI or edited here
* File:   IQS9320_init.h
* Author: Azoteq
*/

#ifndef IQS9320_INIT_H
#define IQS9320_INIT_H

/* Change the Version Info */
/* Memory Map Position 0x0000 - 0x00 */
#define PROD_0                                   0x16
#define PROD_1                                   0x07

/* Change the Device Configuration */
/* Memory Map Position 0x2000 - 0x2007 */
#define SYSTEM_CONTROL_0                         0x06
#define SYSTEM_CONTROL_1                         0x00
#define SYSTEM_CONFIG_0                          0x4A
#define SYSTEM_CONFIG_1                          0x1E
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
#define DEFAULT_READ_LOCATION_0                  0x0C
#define DEFAULT_READ_LOCATION_1                  0x00

/* Change the Mirror Selection CH 0-9 */
/* Memory Map Position 0x3000 - 0x3009 */
#define MIRROR_SEL_CH0_0                         0x21
#define MIRROR_SEL_CH0_1                         0x45
#define MIRROR_SEL_CH1_0                         0x21
#define MIRROR_SEL_CH1_1                         0x47
#define MIRROR_SEL_CH2_0                         0x21
#define MIRROR_SEL_CH2_1                         0x53
#define MIRROR_SEL_CH3_0                         0xC1
#define MIRROR_SEL_CH3_1                         0x50
#define MIRROR_SEL_CH4_0                         0x21
#define MIRROR_SEL_CH4_1                         0x51
#define MIRROR_SEL_CH5_0                         0xC1
#define MIRROR_SEL_CH5_1                         0x4E
#define MIRROR_SEL_CH6_0                         0xC1
#define MIRROR_SEL_CH6_1                         0x50
#define MIRROR_SEL_CH7_0                         0x21
#define MIRROR_SEL_CH7_1                         0x45
#define MIRROR_SEL_CH8_0                         0x21
#define MIRROR_SEL_CH8_1                         0x45
#define MIRROR_SEL_CH9_0                         0x21
#define MIRROR_SEL_CH9_1                         0x45

/* Change the Mirror Selection CH 10-19 */
/* Memory Map Position 0x3014 - 0x301D */
#define MIRROR_SEL_CH10_0                        0x21
#define MIRROR_SEL_CH10_1                        0x45
#define MIRROR_SEL_CH11_0                        0x21
#define MIRROR_SEL_CH11_1                        0x51
#define MIRROR_SEL_CH12_0                        0x21
#define MIRROR_SEL_CH12_1                        0x51
#define MIRROR_SEL_CH13_0                        0xC1
#define MIRROR_SEL_CH13_1                        0x4E
#define MIRROR_SEL_CH14_0                        0xC1
#define MIRROR_SEL_CH14_1                        0x52
#define MIRROR_SEL_CH15_0                        0x21
#define MIRROR_SEL_CH15_1                        0x4F
#define MIRROR_SEL_CH16_0                        0xC1
#define MIRROR_SEL_CH16_1                        0x4E
#define MIRROR_SEL_CH17_0                        0x21
#define MIRROR_SEL_CH17_1                        0x55
#define MIRROR_SEL_CH18_0                        0x21
#define MIRROR_SEL_CH18_1                        0x43
#define MIRROR_SEL_CH19_0                        0x21
#define MIRROR_SEL_CH19_1                        0x45

/* Change the Calibration Parameters CH 0-9 */
/* Memory Map Position 0x3028 - 0x3031 */
#define CALIB_STEP_CH0                           0x00
#define CALIB_CORRECT_CH0                        0x00
#define CALIB_STEP_CH1                           0x00
#define CALIB_CORRECT_CH1                        0x00
#define CALIB_STEP_CH2                           0x00
#define CALIB_CORRECT_CH2                        0x00
#define CALIB_STEP_CH3                           0x00
#define CALIB_CORRECT_CH3                        0x00
#define CALIB_STEP_CH4                           0x00
#define CALIB_CORRECT_CH4                        0x00
#define CALIB_STEP_CH5                           0x00
#define CALIB_CORRECT_CH5                        0x00
#define CALIB_STEP_CH6                           0x00
#define CALIB_CORRECT_CH6                        0x00
#define CALIB_STEP_CH7                           0x00
#define CALIB_CORRECT_CH7                        0x00
#define CALIB_STEP_CH8                           0x00
#define CALIB_CORRECT_CH8                        0x00
#define CALIB_STEP_CH9                           0x00
#define CALIB_CORRECT_CH9                        0x00

/* Change the Calibration Parameters CH 10-19 */
/* Memory Map Position 0x3042 - 0x304B */
#define CALIB_STEP_CH10                          0x00
#define CALIB_CORRECT_CH10                       0x00
#define CALIB_STEP_CH11                          0x00
#define CALIB_CORRECT_CH11                       0x00
#define CALIB_STEP_CH12                          0x00
#define CALIB_CORRECT_CH12                       0x00
#define CALIB_STEP_CH13                          0x00
#define CALIB_CORRECT_CH13                       0x00
#define CALIB_STEP_CH14                          0x00
#define CALIB_CORRECT_CH14                       0x00
#define CALIB_STEP_CH15                          0x00
#define CALIB_CORRECT_CH15                       0x00
#define CALIB_STEP_CH16                          0x00
#define CALIB_CORRECT_CH16                       0x00
#define CALIB_STEP_CH17                          0x00
#define CALIB_CORRECT_CH17                       0x00
#define CALIB_STEP_CH18                          0x00
#define CALIB_CORRECT_CH18                       0x00
#define CALIB_STEP_CH19                          0x00
#define CALIB_CORRECT_CH19                       0x00

/* Change the Effective Max Delta CH 0-9 */
/* Memory Map Position 0x3050 - 0x3059 */
#define MAX_DELTA_E_0_0                          0x10
#define MAX_DELTA_E_0_1                          0x27
#define MAX_DELTA_E_1_0                          0x10
#define MAX_DELTA_E_1_1                          0x27
#define MAX_DELTA_E_2_0                          0x10
#define MAX_DELTA_E_2_1                          0x27
#define MAX_DELTA_E_3_0                          0x10
#define MAX_DELTA_E_3_1                          0x27
#define MAX_DELTA_E_4_0                          0x10
#define MAX_DELTA_E_4_1                          0x27
#define MAX_DELTA_E_5_0                          0x10
#define MAX_DELTA_E_5_1                          0x27
#define MAX_DELTA_E_6_0                          0x10
#define MAX_DELTA_E_6_1                          0x27
#define MAX_DELTA_E_7_0                          0x10
#define MAX_DELTA_E_7_1                          0x27
#define MAX_DELTA_E_8_0                          0x10
#define MAX_DELTA_E_8_1                          0x27
#define MAX_DELTA_E_9_0                          0x10
#define MAX_DELTA_E_9_1                          0x27

/* Change the Effective Max Delta CH 10-19 */
/* Memory Map Position 0x3064 - 0x306D */
#define MAX_DELTA_E_10_0                         0x10
#define MAX_DELTA_E_10_1                         0x27
#define MAX_DELTA_E_11_0                         0x10
#define MAX_DELTA_E_11_1                         0x27
#define MAX_DELTA_E_12_0                         0x10
#define MAX_DELTA_E_12_1                         0x27
#define MAX_DELTA_E_13_0                         0x10
#define MAX_DELTA_E_13_1                         0x27
#define MAX_DELTA_E_14_0                         0x10
#define MAX_DELTA_E_14_1                         0x27
#define MAX_DELTA_E_15_0                         0x10
#define MAX_DELTA_E_15_1                         0x27
#define MAX_DELTA_E_16_0                         0x10
#define MAX_DELTA_E_16_1                         0x27
#define MAX_DELTA_E_17_0                         0x10
#define MAX_DELTA_E_17_1                         0x27
#define MAX_DELTA_E_18_0                         0x10
#define MAX_DELTA_E_18_1                         0x27
#define MAX_DELTA_E_19_0                         0x10
#define MAX_DELTA_E_19_1                         0x27

/* Change the Sampled Max Delta CH 0-9 */
/* Memory Map Position 0x3078 - 0x3081 */
#define MAX_DELTA_S_0_0                          0x7F
#define MAX_DELTA_S_0_1                          0x30
#define MAX_DELTA_S_1_0                          0x79
#define MAX_DELTA_S_1_1                          0x32
#define MAX_DELTA_S_2_0                          0xF2
#define MAX_DELTA_S_2_1                          0x28
#define MAX_DELTA_S_3_0                          0xB1
#define MAX_DELTA_S_3_1                          0x26
#define MAX_DELTA_S_4_0                          0x21
#define MAX_DELTA_S_4_1                          0x29
#define MAX_DELTA_S_5_0                          0x39
#define MAX_DELTA_S_5_1                          0x28
#define MAX_DELTA_S_6_0                          0x00
#define MAX_DELTA_S_6_1                          0x27
#define MAX_DELTA_S_7_0                          0x60
#define MAX_DELTA_S_7_1                          0x33
#define MAX_DELTA_S_8_0                          0x67
#define MAX_DELTA_S_8_1                          0x38
#define MAX_DELTA_S_9_0                          0x48
#define MAX_DELTA_S_9_1                          0x34

/* Change the Sampled Max Delta CH 10-19 */
/* Memory Map Position 0x3092 - 0x309B */
#define MAX_DELTA_S_10_0                         0x60
#define MAX_DELTA_S_10_1                         0x28
#define MAX_DELTA_S_11_0                         0xDA
#define MAX_DELTA_S_11_1                         0x24
#define MAX_DELTA_S_12_0                         0x92
#define MAX_DELTA_S_12_1                         0x25
#define MAX_DELTA_S_13_0                         0x94
#define MAX_DELTA_S_13_1                         0x27
#define MAX_DELTA_S_14_0                         0x09
#define MAX_DELTA_S_14_1                         0x26
#define MAX_DELTA_S_15_0                         0x00
#define MAX_DELTA_S_15_1                         0x00
#define MAX_DELTA_S_16_0                         0x00
#define MAX_DELTA_S_16_1                         0x00
#define MAX_DELTA_S_17_0                         0x00
#define MAX_DELTA_S_17_1                         0x00
#define MAX_DELTA_S_18_0                         0x00
#define MAX_DELTA_S_18_1                         0x00
#define MAX_DELTA_S_19_0                         0x00
#define MAX_DELTA_S_19_1                         0x00

/* Change the Individual Thresholds */
/* Memory Map Position 0x30C8 - 0x30D1 */
#define INDIVIDUAL_THRESHOLDS_0                  0x00
#define INDIVIDUAL_THRESHOLDS_1                  0x00
#define INDIVIDUAL_THRESHOLDS_2                  0x00
#define INDIVIDUAL_THRESHOLDS_3                  0x00
#define INDIVIDUAL_THRESHOLDS_4                  0x00
#define INDIVIDUAL_THRESHOLDS_5                  0x00
#define INDIVIDUAL_THRESHOLDS_6                  0x00
#define INDIVIDUAL_THRESHOLDS_7                  0x00
#define INDIVIDUAL_THRESHOLDS_8                  0x00
#define INDIVIDUAL_THRESHOLDS_9                  0x00
#define INDIVIDUAL_THRESHOLDS_10                 0x00
#define INDIVIDUAL_THRESHOLDS_11                 0x00
#define INDIVIDUAL_THRESHOLDS_12                 0x00
#define INDIVIDUAL_THRESHOLDS_13                 0x00
#define INDIVIDUAL_THRESHOLDS_14                 0x00
#define INDIVIDUAL_THRESHOLDS_15                 0x00
#define INDIVIDUAL_THRESHOLDS_16                 0x00
#define INDIVIDUAL_THRESHOLDS_17                 0x00
#define INDIVIDUAL_THRESHOLDS_18                 0x00
#define INDIVIDUAL_THRESHOLDS_19                 0x00

/* Change the Channel Select and Disable */
/* Memory Map Position 0x30DC - 0x30DC */
#define CYCLE_0_SELECT                           0x0A
#define CYCLE_1_SELECT                           0x0A

/* Change the Rx Select */
/* Memory Map Position 0x30E2 - 0x30EB */
#define RX_SELECT_0                              0x00
#define RX_SELECT_1                              0x02
#define RX_SELECT_2                              0x05
#define RX_SELECT_3                              0x08
#define RX_SELECT_4                              0x0D
#define RX_SELECT_5                              0x12
#define RX_SELECT_6                              0x17
#define RX_SELECT_7                              0x19
#define RX_SELECT_8                              0x1C
#define RX_SELECT_9                              0x1E
#define RX_SELECT_10                             0x01
#define RX_SELECT_11                             0x03
#define RX_SELECT_12                             0x06
#define RX_SELECT_13                             0x0B
#define RX_SELECT_14                             0x0E
#define RX_SELECT_15                             0x13
#define RX_SELECT_16                             0x18
#define RX_SELECT_17                             0x1A
#define RX_SELECT_18                             0x1D
#define RX_SELECT_19                             0x1F

/* Change the Tx Select */
/* Memory Map Position 0x30F6 - 0x30FF */
#define TX_SELECT_0                              0x28
#define TX_SELECT_1                              0x26
#define TX_SELECT_2                              0x04
#define TX_SELECT_3                              0x09
#define TX_SELECT_4                              0x0C
#define TX_SELECT_5                              0x11
#define TX_SELECT_6                              0x16
#define TX_SELECT_7                              0x25
#define TX_SELECT_8                              0x23
#define TX_SELECT_9                              0x21
#define TX_SELECT_10                             0x27
#define TX_SELECT_11                             0x10
#define TX_SELECT_12                             0x07
#define TX_SELECT_13                             0x0A
#define TX_SELECT_14                             0x0F
#define TX_SELECT_15                             0x14
#define TX_SELECT_16                             0x15
#define TX_SELECT_17                             0x1B
#define TX_SELECT_18                             0x22
#define TX_SELECT_19                             0x24

/* Change the ATI Target and Band */
/* Memory Map Position 0x310A - 0x310B */
#define ATI_TARGET_0                             0xC8
#define ATI_TARGET_1                             0x00
#define ATI_BAND_0                               0x64
#define ATI_BAND_1                               0x00

/* Change the Thresholds */
/* Memory Map Position 0x310E - 0x310F */
#define ACTIVATION_THRESHOLD                     0x28
#define REFERENCE_HALT_THRESHOLD                 0x14
#define FAST_REF_THRESHOLD                       0x0A
#define MOVEMENT_THRESHOLD                       0x08

/* Change the Filter Values */
/* Memory Map Position 0x3112 - 0x3115 */
#define BETA_LTA_NP                              0x0A
#define BETA_LTA_LP                              0x06
#define BETA_LTA_ULP                             0x00
#define BETA_FAST_LTA_NP                         0x08
#define BETA_FAST_LTA_LP                         0x05
#define BETA_FAST_LTA_ULP                        0x04
#define BETA_COUNTS_NP                           0x02
#define BETA_COUNTS_LP                           0x01
#define BETA_COUNTS_ULP                          0x00

/* Change the Reference Halt Timeout */
/* Memory Map Position 0x311C - 0x311B */
#define REF_HALT_TIMEOUT_0                       0x08

/* Change the Activation Hysteresis */
/* Memory Map Position 0x311D - 0x311C */
#define ACTIVATION_HYSTERESIS_0                  0x05

#endif	/* IQS9320_INIT_H */