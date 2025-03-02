/*==============================================================================
 Project: Intro-4-Functions
 Date:    May 16, 2021
 
 This program demonstrates the use of functions, and variable passing between
 the main and function code.
 
 Additional program analysis and programming activities examine function code
 location, function prototypes, and reinforce the concepts of global and local
 variables.
==============================================================================*/

#include    "xc.h"              // Microchip XC8 compiler include file
#include    "stdint.h"          // Include integer definitions
#include    "stdbool.h"         // Include Boolean (true/false) definitions

#include    "UBMP4.h"           // Include UBMP4 constants and functions

// TODO Set linker ROM ranges to 'default,-0-7FF' under "Memory model" pull-down.
// TODO Set linker code offset to '800' under "Additional options" pull-down.

// Button constant definitions


// Program variable definitions
unsigned int eightbitvalue = 142;
unsigned char ONES;
unsigned char TENS;
unsigned char HUNDREDS;

void Splittingdigits(unsigned char number)
{
  ONES = eightbitvalue % 10;   
  TENS = eightbitvalue/10 % 10;
  HUNDREDS = eightbitvalue/100 % 10;
}

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    while(1)
	{
      Splittingdigits(eightbitvalue);
      if(ONES == 2)
      {
          LED3 = 1;
      }
      if(TENS == 4)
      {
          LED4 = 1;
      }
      if(HUNDREDS == 1)
      {
          LED5 = 1;
      }
      if(SW1 == 0)
      {
          RESET();
      }
    }
}




// Move the function code to here in Program Analysis, step 5.


/* Program Analysis
 * 
 * 1.   Which function in this program will run first? How do you know?
 * The main function will run first in the program because when the UBMP4 starts up, it searches for the main function first.

 * 2.   What is the purpose of the 'unsigned char' variable type declaration in
 *      the button_pressed() function? Is it used by this function to receive
 *      a variable from, or return a variable to the main code?
 *  The purpose of the button_pressed() function is to give a value when it is asked for one. It is used to return a variable to the main code.

 * 3.   How does the function call statement 'button = button_pressed();' in the
 *      main code support your answer in 2, above?
 *      It supports my answer since button is used in main and is the same as button_pressed();, every time button is called, it's actually calling for button_pressed();.

 * 4.   What is the purpose of the 'unsigned char' variable type declaration in
 *      the pwm_LED5() function? Where does the value of the variable come from?
 *      Where does this value get stored in the function?
The purpose of pwn_LED5() is to control the brightness of the LED. The value comes from pwmValue, which gets its value from LED5Brightness.
The value gets stored in if(pwmValue == t) line.
 * 
 * 5.   C language compilers typically read through the entire program in a
 *      single pass, converting C code into machine code. The two functions,
 *      button_pressed() and pwm_LED5(), are located above the main() function
 *      so that their memory locations and variable requirements will be
 *      determined before the rest of the program compiles. When the compiler
 *      interprets the function call statements in the main code, it already
 *      knows where those functions are be in memory and which memory locations
 *      are used by their variables.
 * 
 *      Try moving the button_pressed() and pwm_LED5() functions to below the
 *      closing brace of the main() function, and build the code. What happens?
 * 
 *      The compiler should have reported an error since it did not understand
 *      what the function call was referring to because it had not seen the
 *      function before the function call. We can eliminate this error by adding
 *      a function prototype above the main code. The function prototype is like
 *      the function declaration (the first line of the function), and lets the
 *      compiler know both the function's name and the type of variables that
 *      the function will use. A C language 'linker' program will take care of
 *      sorting out the names and memory locations of all of the functions and
 *      variables in a program following the compilation step.
 * 
 *      Let's try this out. Leave the functions in their new location, below
 *      the main() function, and add the two function prototypes (shown below)
 *      above main(), in the location where the functions were originally
 *      located:

unsigned char button_pressed(void);

void pwm_LED5(unsigned char);

 *      What is the difference between the function prototype for pwm_LED5()
 *      and the actual pwm_LED5() function declaration statement later in the
 *      code?
 The difference between the prototype and actual is that the actual one is processing all the info and returning it. 
 The prototype just lets the program knows that there is a function available.
 * 
 * 6.   Building the program with the added function prototypes should now work
 *      without generating errors, just as it did in the original program.
 * 
 *      In C, functions may be located above the code that calls them, below
 *      their function calls if a function prototype is supplied, or even in 
 *      completely separate files known as function libraries.
 * 
 *      Function libraries are typically joined to your project's main '.c' file
 *      using an 'include' statement to a '.h' header file containing both
 *      variable definitions and the function prototypes for an associated C
 *      file which contains the actual function code.
 * 
 *      The '#include "UBMP4.h"' statement near the top of this program is an
 *      example of a statement that adds external functions to our program. The
 *      'UBMP4.h' file contains function prototypes for functions located in
 *      the 'UBMP4.c' file, along with various symbolic constants used by both
 *      our program and the code in the UBMP4.c functions.
 * 
 *      Open the UBMP4.c file to find the OSC_config() and UBMP4_config()
 *      functions called from the main() function in this program. Are any
 *      values passed between this code and the two setup functions? How do
 *      you know?
 *  There are values passed from the setup functions to the main() function. In the setup functions, there are multiple variables that are assigned new values with purpose.
   For example, In OSC_config(), the first line is  OSCCON = 0xFC;              // Set 16MHz HFINTOSC with 3x PLL enabled, OSCCON is assigned a new value to set the Mhz to 16.

 * 7.   The 'button' variable is a global variable because it was assigned
 *      at the beginning of the program, outside of any functions. Global
 *      variables are available to all functions. How does the 'button' variable
 *      get assigned a value? In which function does this occur?
    The button variable gets its value from the button_pressed() function, but it happens in the main function.

 * 
 * 8.   Which variable does the value of LED5Brightness get transferred to in
 *      the pwm_LED5() function? Is this variable global, or local to the LED
 *      function? Could the pwm_LED5 function use the LED5Brightness variable
 *      directly, instead of transferring its value to another variable?
        LED5Brightness variable gets transfered to the pwmValue variable. The pwmValue variable is only local to the pwm_LED5() function since it is assigned in that function.
        No, you cannot use the LED5Brightness directly replace the pwm_LED5.
 * 
 * Programming Activities
 * 
 * 1.   It might be useful to have a button that instantly turns LED D5 fully
 *      on or off instead of waiting for it to brighten and dim while the UP
 *      and DOWN buttons are held to change the PWM duty cycle. But, PWM dimming
 *      dimming capability is still a useful feature that should be retained.
 * 
 *      Modify the button_pressed() and main() functions to use SW3 as an
 *      instant on button, and SW2 as an instant off button. Pressing either of
 *      these buttons will over-write the current LED5Brightness value with
 *      either 255 or 0, while still allowing SW4 and SW5 to adjust the
 *      brightness in smaller increments when pressed.
//Variables
    const char noButton = 0;
    const char UP = 1;
    const char DOWN = 2;
    const char MAX = 3;
    const char OFF = 4;
//declarations  

unsigned char button_pressed(void);

void pwm_LED5(unsigned char);

//Inside main()
    while(1)
	{
        // Read up/down buttons and adjust LED5 brightness
        button = button_pressed();
        
        if(button == UP && LED5Brightness < 255)
        {
            LED5Brightness += 1;
        }

        if(button == DOWN && LED5Brightness > 0)
        {
            LED5Brightness -= 1;
        }
        if(button == MAX)
        {
            LED5Brightness = 255;
        }

        if(button == OFF)
        {
            LED5Brightness = 0;
        }

        // PWM LED5 with current brightness
        pwm_LED5(LED5Brightness);
     } 
//Functions  
unsigned char button_pressed(void)
{
    if(SW3 == 0)
    {
        return(MAX);
    }
    else if(SW2 == 0)
    {
        return(OFF);
    }
    else if(SW4 == 0)
    {
        return(UP);
    }
    else if(SW5 == 0)
    {
        return(DOWN);
    }
    else
    {
        return(noButton);
    }
}

void pwm_LED5(unsigned char pwmValue)
{
    for(unsigned char t = 255; t != 0; t --)
    {
        if(pwmValue == t)
        {
            LED5 = 1;
        }
        __delay_us(20);
    }
    // End the pulse if pwmValue < 255
    if(pwmValue < 255)
    {
        LED5 = 0;
    }
}
 *
 * 2.   Create a function that will return a number from 1-4 corresponding to
 *      which of the SW2 to SW5 switches is pressed, or return 0 if no switches
 *      are pressed. Then, create a function that will accept a number from 1 to
 *      4 that lights the corresponding LED beside each button.
//variables

const char noButton = 0;
const char SW2LED = 1;
const char SW3LED = 2;
const char SW4LED = 3;
const char SW5LED = 4;

//declarations

unsigned char button_pressed(void);

void TurnOnLED(unsigned char);

//Inside Main
    while(1)
	{
     TurnOnLED(button_pressed());
    }
//functions
unsigned char button_pressed(void)
{
    if(SW2 == 0)
    {
        return(SW2LED);
    }
    else if(SW3 == 0)
    {
        return(SW3LED);
    }
    else if(SW4 == 0)
    {
        return(SW4LED);
    }
    else if(SW5 == 0)
    {
        return(SW5LED);
    }
    else
    {
        return(noButton);
    }
}
void TurnOnLED(unsigned char whichSwitch)
{
        if(whichSwitch == SW2LED)
        {
            LED3 = 1;
        }
        if(whichSwitch == SW3LED)
        {
            LED4 = 1; 
        }
        if(whichSwitch == SW4LED)
        {
            LED5 = 1;
        }
        if(whichSwitch == SW5LED)
        {
            LED6 = 1;
        }
}
 * 
 * 3.   Create a sound function that receives a parameter representing a tone's
 *      period. Modify your button function, above, to return a variable that
 *      will be passed to the sound function to make four different tones.
//variables
const char noButton = 0;
const char SW2Sound = 500;
const char SW3Sound = 1000;
const char SW4Sound = 750;
const char SW5Sound = 1500;
//declarations
unsigned char button_pressed(void);

void BeeperSounds(unsigned char);
//inside main
     while(1)
	{
     BeeperSounds(button_pressed());
    }

//functions
unsigned char button_pressed(void)
{
    if(SW2 == 0)
    {
        return(SW2Sound);
    }
    else if(SW3 == 0)
    {
        return(SW3Sound);
    }
    else if(SW4 == 0)
    {
        return(SW4Sound);
    }
    else if(SW5 == 0)
    {
        return(SW5Sound);
    }
    else
    {
        return(noButton);
    }
}
void BeeperSounds(unsigned char pitch)
{
    if(pitch != 0)
    {
       for(unsigned int cycles = 50; cycles != 0; cycles--) //length of time 
        {
            BEEPER = !BEEPER;
            for(unsigned int p = pitch; p != 0; p --); //pitch
        }
    }
}
 * 
 * 4.   A function that converts an 8-bit binary value into its decimal
 *      equivalent would be useful for helping us to debug our programs. Create
 *      a function that converts an 8-bit binary number into three decimal
 *      character variables representing the hundreds, tens and ones digits
 *      of the binary number passed to it. For example, passing the function
 *      a value of 142 will result in the hundreds variable containing the
 *      value 1, the tens variable containing 4, and the ones variable 2. How
 *      could you test this function to verify that it works? Try it!
//Variables
unsigned int eightbitvalue = 142;
unsigned char ONES;
unsigned char TENS;
unsigned char HUNDREDS;
//Declarations/Function
void Splittingdigits(unsigned char number)
{
  ONES = eightbitvalue % 10;   
  TENS = eightbitvalue/10 % 10;
  HUNDREDS = eightbitvalue/100 % 10;
}

int main(void)
{
    OSC_config();               // Configure internal oscillator for 48 MHz
    UBMP4_config();             // Configure on-board UBMP4 I/O devices
	
    while(1)
	{
      Splittingdigits(eightbitvalue);
      if(ONES == 2)
      {
          LED3 = 1;
      }
      if(TENS == 4)
      {
          LED4 = 1;
      }
      if(HUNDREDS == 1)
      {
          LED5 = 1;
      }
}
 */
