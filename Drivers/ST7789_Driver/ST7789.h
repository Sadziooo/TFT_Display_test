/*
 * lcd.h
 *
 *  Created on: Apr 16, 2024
 *      Author: Sadziooo
 */

#ifndef INC_ST7789_H_
#define INC_ST7789_H_

#pragma once

//----------------------------------------------------------------------|
//------------------------- INCLUDES -----------------------------<
//----------------------------------------------------------------------|

#include <stdint.h>
#include <stdlib.h>

#include "Fonts.h"

//----------------------------------------------------------------------|
//-------------------------- DEFINES -----------------------------<
//----------------------------------------------------------------------|

#define DISPLAY_H	240
#define DISPLAY_W	320

#define WHITE       		0xFFFF
#define BLACK       		0x0000
#define BLUE       		 	0x001F
#define RED        		 	0xF800
#define MAGENTA     	0xF81F
#define GREEN       		0x07E0
#define CYAN        		0x7FFF
#define YELLOW      	0xFFE0
#define GRAY        		0X8430
#define BRED        		0XF81F
#define GRED        		0XFFE0
#define GBLUE       		0X07FF
#define BROWN       		0XBC40
#define BRRED       		0XFC07
#define DARKBLUE    	0X01CF
#define LIGHTBLUE   	0X7D7C
#define GRAYBLUE    	0X5458
#define LIGHTGREEN  	0X841F
#define LGRAY       		0XC618
#define LGRAYBLUE   	0XA651
#define LBBLUE      		0X2B12

//----------------------------------------------------------------------|
//------------------------ VARIABLES ----------------------------<
//----------------------------------------------------------------------|



//----------------------------------------------------------------------|
//---------------- FUNCTION PROROTYPES ------------------<
//----------------------------------------------------------------------|

void ST7789_init(void);
void ST7789_fill_box(int x, int y, int width, int height, uint16_t color);
void ST7789_put_pixel(int x, int y, uint16_t color);
void ST7789_draw_image(int x, int y, int width, int height, const uint8_t* data);
void ST7789_draw_image_fast(int x, int y, int width, int height, const uint16_t* data);
void ST7789_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void ST7789_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void ST7789_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
void ST7789_write_char(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor);
void ST7789_write_string(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor);


#endif /* INC_ST7789_H_ */
