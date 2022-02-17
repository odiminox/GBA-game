
unsigned int* OAMAddress = (unsigned int *)0x06010000;//Starting point of the raw sprite image data 
unsigned short* OAMspriteHolder = (unsigned short* )0x07000000;//Starting point of the OAM sprite holders

u16* BG_palettRAM =  (u16*)0x05000000;//(512 bytes, 256 colors)   - the start of Background pallet RAM: BG_COLORS[] in gba_video.h
u16* OBJ_palletRAM = ((u16 *)0x05000200);//(512 bytes, 256 colors) - Sprite color table - the start of OBJ pallet RAM: OBJ_COLORS[] in gba_video.h

#define CharBaseBlock(n)		(((n)*0x4000)+0x6000000)
#define ScreenBaseBlock(n)		(((n)*0x800)+0x6000000)

#define CHAR_SHIFT			2
#define SCREEN_SHIFT		8

#define BG_CBB(n)		((n)<<CHAR_SHIFT)
#define BG_SBB(n)		((n)<<SCREEN_SHIFT)

unsigned int* Char_BaseRAM = CHAR_BASE_ADR(0); //point to 0
//16 bit pointer because each memory location is 16 bits of memory
u16* Map_BaseRAM = MAP_BASE_ADR(4); //point to 4 because that is where map memory begins

//colour conversion (converts a RGB colour to a 15-bit BGR value used by the GBA)
#define RGB16_RGB(r, g, b) ((r)+(g<<5)+(b<<10)) // BG_COLORS[(0 *16) + 0] = ((0 << 0) | (10 << 5) | (10 << 10));//Change the background colour

void drawSprite(u8 spAdr, u8 spriteX, u8 spriteY, u8 spNum, u8 pNum, u8 flipX, u8 flipY){

		OAMspriteHolder[(spAdr * 4) + 0] = ( (0 << 14) | (0 << 7) | (spriteY << 0) );										  
		OAMspriteHolder[(spAdr * 4) + 1] = ( (1 << 14) | (flipY << 13) | (flipX << 12) | (0 << 8) | (spriteX << 0) );   
		OAMspriteHolder[(spAdr * 4) + 2] = ( (pNum << 12) | (0 << 10) | (0 << 7) | ( spNum << 0) );
		OAMspriteHolder[(spAdr * 4) + 3] = 0;
}

