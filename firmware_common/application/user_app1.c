/*!*********************************************************************************************************************
@file user_app1.c
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1RunActiveState(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags; /*!< @brief Global state flags */

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;    /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;     /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;      /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags; /*!< @brief From main.c */

/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_<type>" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_pfStateMachine; /*!< @brief The state machine function pointer */
// static u32 UserApp1_u32Timeout;                           /*!< @brief Timeout counter used across states */

/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserApp1Initialize(void)

@brief
Initializes the State Machine and its variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserApp1Initialize(void)
{
  LedOff(RED0);
  LedOff(GREEN0);
  LedOff(BLUE0);

  LedOff(RED1);
  LedOff(GREEN1);
  LedOff(BLUE1);

  LedOff(RED2);
  LedOff(GREEN2);
  LedOff(BLUE2);

  LedOff(RED3);
  LedOff(GREEN3);
  LedOff(BLUE3);

  LedOff(LCD_BL);

  /* If good initialization, set state to Idle */
  if (1)
  {
    UserApp1_pfStateMachine = UserApp1SM_Idle;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_pfStateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserApp1RunActiveState(void)

@brief Selects and runs one iteration of the current state in the state machine.

All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
- State machine function pointer points at current state

Promises:
- Calls the function to pointed by the state machine function pointer

*/
void UserApp1RunActiveState(void)
{
  UserApp1_pfStateMachine();

} /* end UserApp1RunActiveState */

/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */
/*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
// void check_toggle_music(bool *play_music)
// {
//   if (play_music == 1 && IsButtonPressed(BUTTON0))
//   {
//     play_music = 0;
//   }
//   else if (play_music == 0 && IsButtonPressed(BUTTON0))
//   {
//     play_music = 1;
//   }
//   // ButtonAcknowledge(BUTTON0);
// }
/*-------------------------------------------------------------------------------------------------------------------*/
/* What does this state do? */
static void UserApp1SM_Idle(void)
{
  // DebugPrintf
  static bool bool_music_state = 0;
  // static bool bool_pause_state = 0;
  static u16 u16_NOTE_COUNTER = 0;
  static u16 u16_NOTE_INDEX = 0;
  static u16 u16_NOTES[] = {
      NOTE_A4_SHARP,
      0,
      NOTE_D4_SHARP,
      0,
      NOTE_B4,
      0,
      NOTE_A5_SHARP,
      0,

      NOTE_A4_SHARP,
      0,
      NOTE_D4_SHARP,
      0,
      NOTE_B4,
      0,
      NOTE_A5_SHARP,
      0,

      NOTE_A4_SHARP,
      0,
      NOTE_D4_SHARP,
      0,
      NOTE_B4,
      0,

      NOTE_A4_SHARP,
      0,
      NOTE_A5,
      0,
      NOTE_A4_SHARP,
      0,
      NOTE_C5,
      0,
      NOTE_C5,
      0

  };
  static u16 u16_NOTE_LENGTHS[] = {
      QN,
      ST,
      QN,
      ST,
      QN,
      ST,
      HN + QN,
      ST,

      QN,
      ST,
      QN,
      ST,
      QN,
      ST,
      HN + QN,
      ST,

      QN,
      ST,
      QN,
      ST,
      QN,
      ST,

      QN,
      ST,
      HN,
      ST,
      QN,
      ST,
      EN + QN,
      ST,
      SN,
      ST,

  };

  // check_toggle_music(&bool_music_state);
  if (bool_music_state == 1 && IsButtonPressed(BUTTON0))
  {
    bool_music_state = 0;
    u16_NOTE_COUNTER = 0;
    u16_NOTE_INDEX = 0;
    PWMAudioOff(BUZZER1);
  }
  else if (bool_music_state == 0 && IsButtonPressed(BUTTON0))
  {
    bool_music_state = 1;
  }

  if (bool_music_state == 1)
  {
    if (u16_NOTES[u16_NOTE_INDEX] == 0)
    {
      PWMAudioOff(BUZZER1);
    }
    else if (u16_NOTE_COUNTER == 0)
    {
      PWMAudioOff(BUZZER1);
      PWMAudioSetFrequency(BUZZER1, u16_NOTES[u16_NOTE_INDEX]);
      PWMAudioOn(BUZZER1);
    }

    // update the counter for note length;
    u16_NOTE_COUNTER++;
    if (u16_NOTE_COUNTER >= u16_NOTE_LENGTHS[u16_NOTE_INDEX])
    {
      u16_NOTE_INDEX++;
      u16_NOTE_COUNTER = 0;
      // check if we've run out of notes (size of notes)
      if (u16_NOTE_INDEX >= 32)
      {
        // Reset back to the start of the song and stop
        u16_NOTE_INDEX = 0;
        u16_NOTE_COUNTER = 0;
        bool_music_state = 0;
      }
    }
  }

  // if (IsButtonPressed(BUTTON0))
  // {
  //   PWMAudioSetFrequency(BUZZER1, 440);
  //   LedOn(RED0);
  //   PWMAudioOn(BUZZER1);
  // }
  // else
  // {
  //   LedOff(RED0);
  //   PWMAudioOff(BUZZER1);
  // }

  // // PWMAudioSetFrequency(BUZZER1, 440);
  // if (IsButtonPressed(BUTTON1))
  // {
  //   // LcdShift(LCD_SHIFT_LEFT);
  //   PWMAudioSetFrequency(BUZZER1, 262);
  //   PWMAudioOn(BUZZER1);
  //   LedOn(RED1);
  // }
  // else
  // {
  //   LedOff(RED1);
  //   PWMAudioOff(BUZZER1);
  // }
  // // LedInitialize();
  // LedOn(BLUE0);

  // // LedToggle(RED3);
  // static u16 u16BlinkCount = 0;
  // static u8 u8Counter = 0;

  // u16BlinkCount++;
  // if (u16BlinkCount == 500)
  // {
  //   u16BlinkCount = 0;
  //   LedToggle(BLUE3);
  //   LedToggle(RED3);
  //   LedToggle(LCD_BL);

  //   u8Counter++;
  //   if (u8Counter == 16)
  //   {
  //     u8Counter = 0;
  //   }

  //   if (u8Counter % 2 == 1)
  //   {
  //     LedOn(BLUE0);
  //     LedOn(RED0);
  //   }
  //   else
  //   {
  //     LedOff(BLUE0);
  //     LedOff(RED0);
  //   }

  //   if ((u8Counter & 0b0010) == 0b0010)
  //   {
  //     LedOn(BLUE1);
  //     LedOn(RED1);
  //   }
  //   else
  //   {
  //     LedOff(BLUE1);
  //     LedOff(RED1);
  //   }

  //   if ((u8Counter & 0b0100) == 0b0100)
  //   {
  //     LedOn(BLUE2);
  //     LedOn(RED2);
  //   }
  //   else
  //   {
  //     LedOff(BLUE2);
  //     LedOff(RED2);
  //   }
  //   if ((u8Counter & 0b1000) == 0b1000)
  //   {
  //     LedOn(BLUE3);
  //     LedOn(RED3);
  //   }
  //   else
  //   {
  //     LedOff(BLUE3);
  //     LedOff(RED3);
  //   }
  // }

} /* end UserApp1SM_Idle() */

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)
{

} /* end UserApp1SM_Error() */

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
