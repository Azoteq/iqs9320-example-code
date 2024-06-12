/******************************************************************************
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
 * @file        iqs9320-example-code.ino                                      *
 * @brief       IQS9320 20 Key EV-KIT Example code                            *
 *              (PCB Version - AZP1342A1/B1)                                  *
 *              This example demonstrates how to write the desired settings   *
 *              to the IQS9320 in order to use the 20 Key IQS9320 EV-Kit.     *
 *                                                                            *
 *              All data is displayed over serial communication with the      *
 *              following outputs:                                            *
 *                  - Channel states (Channel 0 -> 19)                        *
 *                  - Power Mode Feedback                                     *
 *                                                                            *
 * @author      Azoteq PTY Ltd                                                *
 * @version     v1.5                                                          *
 * @date        2024-06-10                                                    *
 *****************************************************************************/

#include <Arduino.h>
#include "src\IQS9320\IQS9320.h"

/*** Defines ***/
#define DEMO_IQS9320_ADDR                      0x3E
#define DEMO_IQS9320_POWER_PIN                 4
#define DEMO_IQS9320_MCLR_PIN                  5
#define DEMO_IQS9320_NR_CHANNELS               20
#define DEMO_IQS9320_SAMPLE_TIME               10

/*** Instances ***/
IQS9320 iqs9320;

/*** Global Variables ***/
iqs9320_ch_states key_states[DEMO_IQS9320_NR_CHANNELS];
iqs9320_power_mode_e power_mode = IQS9320_NORMAL_POWER;
uint32_t demo_sample_timer = 0;

/* Channel layout for the keys on EV-Kit */
#ifdef IQS9320_V1_0
uint8_t ch_seq[DEMO_IQS9320_NR_CHANNELS] = {8,  18, 7,  17,
                                            19, 9,  6,  16,
                                            2,  11, 14, 5,
                                            10, 0,  4,  15,
                                            1,  12, 13, 3};
#endif

#ifdef IQS9320_V0_7
uint8_t ch_seq[DEMO_IQS9320_NR_CHANNELS] = {8,  18, 7,  17,
                                            19, 9,  6,  16,
                                            2,  11, 14, 5,
                                            10, 0,  4,  15,
                                            1,  12, 13, 3};
#endif
#ifdef IQS9320_V0_4
uint8_t ch_seq[DEMO_IQS9320_NR_CHANNELS] = {1,  11, 2,  12,
                                            10, 0,  3,  13,
                                            7,  18, 15, 4,
                                            19, 9,  5,  14,
                                            8,  17, 16, 6};
#endif

void setup()
{
  /* Start Serial Communication */
  Serial.begin(115200);
  while(!Serial);
  Serial.println("Start Serial communication");
  delay(200);

  /* Power On IQS9320 */
  pinMode(DEMO_IQS9320_POWER_PIN, OUTPUT);
  delay(200);
  digitalWrite(DEMO_IQS9320_POWER_PIN, LOW);
  delay(200);
  digitalWrite(DEMO_IQS9320_POWER_PIN, HIGH);

  /* Initialize the IQS9320 with input parameters device address and RDY pin */
  iqs9320.begin(DEMO_IQS9320_ADDR, DEMO_IQS9320_MCLR_PIN, DEMO_IQS9320_NR_CHANNELS);
  Serial.println("IQS9320 Ready");
  delay(200);

  /* Reset sample timer */
  demo_sample_timer = millis();
}

void loop()
{
  iqs9320.run(); // Runs the IQS9320 program loop

  /* Request data from IQS9320 devices every IQS_SAMPLE_TIME ms.
     IQS9320 should be in idle state */
  if(iqs9320.iqs9320_state.state == IQS9320_STATE_IDLE)
  {
    if(millis() - demo_sample_timer >= DEMO_IQS9320_SAMPLE_TIME)
    {
      iqs9320.requestData();
      demo_sample_timer = millis();
    }
  }

  /* Process data read from IQS9320 when new data is available */
  if(iqs9320.new_data_available)
  {
    check_power_mode();     // Verify if a power mode change occurred
    check_channel_states(); // Check if a channel state change has occurred

    iqs9320.new_data_available = false;
  }
}

/* Function to check when the current power mode of the IQS9320 changed */
void check_power_mode(void)
{
  iqs9320_power_mode_e current_pm = iqs9320.getPowerMode();
  if (current_pm != power_mode)
  {
    power_mode = current_pm;
    serial_ui_print();
  }
}

/* Function to check the proximity and touch states of the three IQS9320 channels*/
void check_channel_states(void)
{
  for (uint8_t i = 0; i < DEMO_IQS9320_NR_CHANNELS; i++)
  {
    /* Check if the activation state bit is set */
    if(iqs9320.getChannelActivation((iqs9320_channel_e)i))
    {
      if(key_states[i] != IQS9320_CH_ACTIVATION)
      {
        key_states[i] = IQS9320_CH_ACTIVATION;
        serial_ui_print();
      }
    }

    /* Check if the filter halt state bit is set */
    else if (iqs9320.getChannelFilterHalt((iqs9320_channel_e)i))
    {
      if(key_states[i] != IQS9320_CH_FILTER_HALT)
      {
        key_states[i] = IQS9320_CH_FILTER_HALT;
        serial_ui_print();
      }
    }

    /* None state if neither the activation nor filter halt bit was set to 1 */
    else
    {
      if(key_states[i] != IQS9320_CH_NONE)
      {
        key_states[i] = IQS9320_CH_NONE;
        serial_ui_print();
      }
    }
  }
}

/* Force the IQS9320 to open a RDY window and read the current state of the
 * device or request a software reset */
void force_comms_and_reset(void)
{
  char message = read_message();

  /* If an 'r' was received over serial, request a software (SW) reset */
  if(message == 'r')
  {
    Serial.println("Software Reset Requested!");
    iqs9320.iqs9320_state.state = IQS9320_STATE_SW_RESET;
  }
}

/* Read message sent over serial communication */
char read_message(void)
{
  while (Serial.available())
  {
    if(Serial.available() > 0)
    {
      return  Serial.read();
    }
  }

  return '\n';
}

/* Function that prints out the activation status of each channel over serial
   in table format. */
void serial_ui_print(void)
{
  Serial.println("");
  Serial.println("    IQS9320 20-KEY EV-KIT    ");
  Serial.println("=============================");
  Serial.print("|");

  /* Print channel names in table and split total channels in 2 lines */
  uint8_t half_ch = DEMO_IQS9320_NR_CHANNELS/2;
  for(uint8_t i = 0; i < DEMO_IQS9320_NR_CHANNELS; i++)
  {
    /* Print divider line */
    if (i % 4 == 0 && i != 0)
    {
      Serial.println(" ");
      Serial.println("|---------------------------|");
      Serial.print("|");
    }

    /* Check if activation bit is set and fill block */
    if(key_states[ch_seq[i]] == 2)
    {
      Serial.print("███");
      if (ch_seq[i] < 10)
      {
        Serial.print("█");
        Serial.print("██|");
      }
      else
      {
        Serial.print("██");
        Serial.print("█|");
      }
    }
    else
    {
      Serial.print(" CH");
      Serial.print(ch_seq[i]);
      if (ch_seq[i] < 10)
      {
        Serial.print("  |");
      }
      else
      {
        Serial.print(" |");
      }
    }
  }

  /* Close table with double line */
  Serial.println(" ");
  Serial.println("|---------------------------|");

  switch (power_mode)
  {
  case IQS9320_NORMAL_POWER:
    Serial.println("|        Normal Power       |");
    break;

  case IQS9320_LOW_POWER:
    Serial.println("|         Low Power         |");
    break;

  case IQS9320_ULTRA_LOW_POWER:
    Serial.println("|      Ultra Low Power      |");
    break;
  }

  Serial.println("=============================\n");
}
