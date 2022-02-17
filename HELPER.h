/**************************************************************************************
* DISPCNT.h
* Simon Jordan
*
* Description:
*	I got fed up with 'black box functions' that have no documentation, so I decided to learn the memory locations
*	myself, which, for me, is easier
* Use:
*	Include and use
*
* Details:
*   Contains named literals, macros and sub routines of memory locations to use in main code
***************************************************************************************/


u16* OAMAddress = (u16 *)0x06010000;//Starting point of the raw sprite image data 
u32* OAMspriteHolder = (u32* )0x07000000;//Starting point of the OAM sprite holders

#define vid_mem     ((u16*)MEM_VRAM) //Take a 16 bit pointer to the start of the video memory ram

typedef u16 COLOR;

typedef unsigned char   u8;
typedef unsigned short  u16;
typedef unsigned int    u32;

#define MEM_IO      0x04000000
#define MEM_VRAM    0x06000000

#define CLR_BLACK   0x0000
#define CLR_RED     0x001F
#define CLR_LIME    0x03E0
#define CLR_YELLOW  0x03FF
#define CLR_BLUE    0x7C00
#define CLR_MAG     0x7C1F
#define CLR_CYAN    0x7FE0
#define CLR_WHITE   0x7FFF

static inline void m3_plot(int x, int y, COLOR clr)
{   vid_mem[y*SCREEN_WIDTH+x]= clr;    }


static inline COLOR RGB15(u32 red, u32 green, u32 blue)
{   return red | (green<<5) | (blue<<10);   }
