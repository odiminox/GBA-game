
/**************************************************************************************
* DISPCNT.h
* Simon Jordan
*
* Description:
*	REG_DISPCNT is a 16-bit register with different bits being set for different modes
* Use:
*	It is defined in the main source code as REG_DISPCNT = (); with the bit control flags in parens
*
* Details:
* 
*Bits 0-2 
*These three bits allow you to set the screen mode from 0 to 5. So you can choose which of the modes you want to use.
*
*Bit 3 
*This bit is only set if a Gameboy or Gameboy Colour cartridge is to be run from your GBA.
*
*Bit 4 
*Modes 4 and 5 have two frame buffers. This bit used for switching between frame buffers
*
*Bit 5 
*Updates the OAM (Object Attribute Memory) during a horizontal blank (H_BLANK)
*
*Bit 6 
*Choose the mapping mode for sprites.
*
*Bit 7
*Forces screen to go white
*
*Bits 8-11 
*Enables the four backgrounds
*
*Bit 12 
*Enables sprite objects
*
*Bit 13
*Display seperate windows
***************************************************************************************/

//Hex values corrpesponds with where the bit is in the register

//Define bits to control the screen mode
//First three are tile modes
#define MODE_0 0x0 //All 4 backgrounds
#define MODE_1 0x1 //0, 1, and 2 backgrounds
#define MODE_2 0x2 //2 and 3 backgrounds

//Last three are bitmap modes
#define MODE_3 0x3 //Background 2 which is 240x160 pixels, 1 frame buffer used, 15-bit true colour
#define MODE_4 0x4 //Background 2 which is 240x160 pixels, 2 frame buffers used, 8-bit indexed palette
#define MODE_5 0x5 //Background 2 which is 160x128 pixels, 2 frame buffers used, 15-bit true colour

//for sprite graphics 2D or 1D
#define OBJ_MAP_2D 0x0
#define OBJ_MAP_1D 0x40

//define the flags for enabling backgrounds and objects(sprites)
#define BG0_ENABLE 0x100
#define BG1_ENABLE 0x200
#define BG2_ENABLE 0x400
#define BG3_ENABLE 0x800
#define OBJ_ENABLE 0x1000
