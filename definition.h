/*
 * definition.h
 *
 */

#ifndef DEFINITION_H_
#define DEFINITION_H_

//        sw_sliders
#define  _SW0 0x00000001
#define  _SW1 0x00000002
#define  _SW2 0x00000004
#define  _SW3 0x00000008
#define  _SW4 0x00000010
#define  _SW5 0x00000020
#define  _SW6 0x00000040
#define  _SW7 0x00000080
#define  _SW8 0x00000100
#define  _SW9 0x00000200
#define  _SW10 0x00000400

//      pushbuttons
#define  _KEY1 0x00000002
#define  _KEY2 0x00000004
#define  _KEY3 0x00000008
#define  _KEY4 0x00000010

//      leds
#define  _LED0 0x00000001
#define  _LED1 0x00000002
#define  _LED2 0x00000004
#define  _LED3 0x00000008
#define  _LED4 0x00000010
#define  _LED5 0x00000020
#define  _LED6 0x00000040
#define  _LED7 0x00000080
#define  _LED8 0x00000100
#define  _LED9 0x00000200

//      hex
#define  SEGA 0x00001
#define  SEGB 0x00002
#define  SEGC 0x00004
#define  SEGD 0x00008
#define  SEGE 0x00010
#define  SEGF 0x00020
#define  SEGG 0x00040

//     hex - Numbers Letters
#define _ZERO SEGA | SEGB | SEGC | SEGD |SEGE | SEGF
#define _ONE  SEGB | SEGC
#define _TWO  SEGA | SEGB | SEGG | SEGE | SEGD
#define _THREE SEGA | SEGB | SEGC | SEGD | SEGG
#define _FOUR SEGB | SEGC | SEGF | SEGG
#define _FIVE SEGA | SEGF | SEGG | SEGC | SEGD
#define _SIX SEGA | SEGC | SEGD | SEGE | SEGF | SEGG
#define _SEVEN SEGA | SEGB | SEGC
#define _EIGHT SEGA | SEGB | SEGC | SEGD | SEGE | SEGF | SEGG
#define _NINE SEGA | SEGB | SEGC | SEGD | SEGF | SEGG
#define _MINUS SEGG
#define _ERROR_E SEGA | SEGD | SEGE | SEGF | SEGG
#define _ERROR_R SEGE | SEGG
#define _ERROR_O SEGC | SEGD | SEGE | SEGG


#endif /* DEFINITION_H_ */
