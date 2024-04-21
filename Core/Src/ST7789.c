/*
 * lcd.c
 *
 *  Created on: Apr 16, 2024
 *      Author: Sadziooo
 */

//----------------------------------------------------------------------|
//------------------------- INCLUDES -----------------------------<
//----------------------------------------------------------------------|

#include "ST7789.h"
#include "spi.h"

//----------------------------------------------------------------------|
//-------------------------- DEFINES -----------------------------<
//----------------------------------------------------------------------|

#define ST7789_NOP 							0x00 		// 	NOP
#define ST7789_SWRESET 					0x01		// 	Software Reset
#define ST7789_RDDID 						0x04		// 	Read Display ID
#define ST7789_RDDST 						0x09		// 	Read Display Status
#define ST7789_RDDPM 						0x0A		// 	Read Display Power Mode
#define ST7789_RDDMADCTL 				0x0B		// 	Read Display MADCTL
#define ST7789_RDDCOLMOD  			0x0C		// 	Read Display Pixel Format
#define ST7789_RDDIM  						0x0D		// 	Read Display Image Mode
#define ST7789_RDDSM  						0x0E		// 	Read Display Signal Mode
#define ST7789_RDDSDR  					0x0F		// 	Read Display Self-diagnostic Result
#define ST7789_SLPIN  						0x10		// 	Sleep In
#define ST7789_SLPOUT  						0x11		// 	Sleep Out
#define ST7789_PTLON  						0x12		// 	Partial Display Mode On
#define ST7789_NORON  						0x13		// 	Normal Display Mode On
#define ST7789_INVOFF  						0x20		// 	Display Inversion Off
#define ST7789_INVON  						0x21		// 	Display Inversion On
#define ST7789_GAMSET  					0x26		// 	Gamma Set
#define ST7789_DISPOFF  					0x28		// 	Display Off
#define ST7789_DISPON  						0x29		// 	Display On
#define ST7789_CASET  						0x2A		// 	Column Address Set
#define ST7789_RASET  						0x2B		//	Row Address Set
#define ST7789_RAMWR 						0x2C		//	Memory Write
#define ST7789_RAMRD  						0x2E		//	Memory Read
#define ST7789_PTLAR  						0x30		//	Partial Area
#define ST7789_VSCRDEF  					0x33		//	Vertical Scrolling Definition
#define ST7789_TEOFF  						0x34		//	Tearing Effect Line Off
#define ST7789_TEON  							0x35		//	Tearing Effect Line On
#define ST7789_MADCTL  					0x36		//	Memory Data Access Control
#define ST7789_VSCSAD 						0x37		//	Vertical Scroll Start Address of RAM
#define ST7789_IDMOFF  						0x38		//	Idle Mode Off
#define ST7789_IDMON  						0x39		//	Idle Mode On
#define ST7789_COLMOD  					0x3A		//	Interface Pixel Format
#define ST7789_WRMEMC  					0x3C		//	Write Memory Continue
#define ST7789_RDMEMC  					0x3E		//	Read Memory Continue
#define ST7789_STE  							0x44		//	Set Tear Scanline
#define ST7789_GSCAN  						0x45		//	Get Scanline
#define ST7789_WRDISBV 					0x51		//	Write Display Brightness
#define ST7789_RDDISBV  					0x52		//	Read Display Brightness
#define ST7789_WRCTRLD  					0x53		//	Write CTRL Display
#define ST7789_RDCTRLD  					0x54		//	Read CTRL Value Display
#define ST7789_WRCACE  					0x55		//	Write Content Adaptive Brightness Control and Color Enhancement
#define ST7789_RDCABC  					0x56		//	Read Content Adaptive Brightness Control
#define ST7789_WRCABCMB  				0x5E		//	Write CABC Minimum Brightness
#define ST7789_RDCABCMB  				0x5F		//	Read CABC Minimum Brightness
#define ST7789_RDABCSDR  				0x68		//	Read Automatic Brightness Control Self-Diagnostic Result
#define ST7789_RDID1  						0xDA		// 	Read ID1
#define ST7789_RDID2  						0xDB		// 	Read ID2
#define ST7789_RDID3							0xDC	// 	Read ID3
#define ST7789_RAMCTRL 					0xB0		//	RAM Control
#define ST7789_RGBCTRL  					0xB1		//	RGB Interface Control
#define ST7789_PORCTRL  					0xB2		//	Porch Setting
#define ST7789_FRCTRL1  					0xB3		//	Frame Rate Control 1 (In partial mode/ idle colors)
#define ST7789_PARCTRL  					0xB5		//	Partial Control
#define ST7789_GCTRL  						0xB7		// 	Gate Control
#define ST7789_GTADJ  						0xB8		//	Gate On Timing Adjustment
#define ST7789_DGMEN  						0xBA		//	Digital Gamma Enable
#define ST7789_VCOMS  						0xBB		//	VCOM Setting
#define ST7789_POWSAVE  					0xBC		//	Power Saving Mode
#define ST7789_DLPOFFSAVE  			0xBD		//	Display Off Power Save
#define ST7789_LCMCTRL  					0xC0		//	LCM Control
#define ST7789_IDSET  						0xC1		//	ID Code Setting
#define ST7789_VDVVRHEN  				0xC2		//	VDV and VRH Command Enable
#define ST7789_VRHS  						0xC3		//	VRH Set
#define ST7789_VDVS  						0xC4		//	VDV Set
#define ST7789_VCMOFSET  				0xC5		//	VCOM Offset Set
#define ST7789_FRCTRL2  					0xC6		//	Frame Rate Control in Normal Mode
#define ST7789_CABCCTRL  				0xC7		//	CABC Control
#define ST7789_REGSEL1  					0xC8		//	Register Value Selection 1
#define ST7789_REGSEL2  					0xCA		//	Register Value Selection 2
#define ST7789_PWMFRSEL  				0xCC	//	PWM Frequency Selection
#define ST7789_PWCTRL1  					0xD0		//	Power Control 1
#define ST7789_VAPVANEN  				0xD2		//	Enable VAP/VAN signal output
#define ST7789_CMD2EN  					0xDF		//	Command 2 Enable
#define ST7789_PVGAMCTRL  				0xE0		// 	Positive Voltage Gamma Control
#define ST7789_NVGAMCTRL  				0xE1		// 	Negative Voltage Gamma Control
#define ST7789_DGMLUTR  					0xE2		//	Digital Gamma Look-up Table for Red
#define ST7789_DGMLUTB  					0xE3		//	Digital Gamma Look-up Table for Blue
#define ST7789_GATECTRL  					0xE4		//	Gate Control
#define ST7789_SPI2EN  						0xE7		//	SPI2 Enable
#define ST7789_PWCTRL2  					0xE8		//	Power Control 2
#define ST7789_EQCTRL  					0xE9		//	Equalize Time Control
#define ST7789_PROMCTRL  				0xEC		//	Program Mode Control
#define ST7789_PROMEN  					0xFA		//	Program Mode Enable
#define ST7789_NVMSET  					0xFC		//	NVM Setting
#define ST7789_PROMACT  					0xFE		//	Program Action

/* Page Address Order ('0': Top to Bottom, '1': the opposite) */
#define ST7789_MADCTL_MY  0x80
/* Column Address Order ('0': Left to Right, '1': the opposite) */
#define ST7789_MADCTL_MX  0x40
/* Page/Column Order ('0' = Normal Mode, '1' = Reverse Mode) */
#define ST7789_MADCTL_MV  0x20
/* Line Address Order ('0' = LCD Refresh Top to Bottom, '1' = the opposite) */
#define ST7789_MADCTL_ML  0x10
/* RGB/BGR Order ('0' = RGB, '1' = BGR) */
#define ST7789_MADCTL_RGB 0x00

#define ST7789_COLMOD_65K		0x50
#define ST7789_COLMOD_262K	0x60
#define ST7789_COLMOD_12bit	0x03
#define ST7789_COLMOD_16bit	0x05
#define ST7789_COLMOD_18bit	0x06
#define ST7789_COLMOD_16M		0x07

#define CMD(x)			((x) | 0x100)
#define ABS(x) ((x) > 0 ? (x) : -(x))

#define LCD_OFFSET_X	0
#define LCD_OFFSET_Y	0

//----------------------------------------------------------------------|
//------------------------ VARIABLES ----------------------------<
//----------------------------------------------------------------------|

static const uint16_t ST7789_init_table[] = {
	CMD(ST7789_COLMOD), (ST7789_COLMOD_262K | ST7789_COLMOD_16bit),
	CMD(ST7789_PORCTRL), 0x0C, 0x0C, 0x00, 0x33, 0x33,
	CMD(ST7789_GATECTRL), 0x35,
	CMD(ST7789_VCOMS), 0x20,
	CMD(ST7789_LCMCTRL), 0x2C,
	CMD(ST7789_VDVVRHEN), 0x01,
	CMD(ST7789_VRHS), 0x0B,
	CMD(ST7789_VDVS), 0x20,
	CMD(ST7789_FRCTRL2), 0x0F,
	CMD(ST7789_PWCTRL1), 0xA4, 0xA1,

	CMD(ST7789_PVGAMCTRL), 0xD0, 0x04, 0x0D, 0x11, 0x13, 0x2B, 0x3F, 0x54, 0x4C, 0x18, 0x0D, 0x0B, 0x1F, 0x23,
	CMD(ST7789_NVGAMCTRL), 0xD0, 0x04, 0x0C, 0x11, 0x13, 0x2C, 0x3F, 0x44, 0x51, 0x2F, 0x1F, 0x1F, 0x20, 0x23,
	CMD(ST7789_INVOFF),
	CMD(ST7789_NORON),

	CMD(ST7789_MADCTL), (ST7789_MADCTL_MV | ST7789_MADCTL_MX | ST7789_MADCTL_RGB)
};

static uint8_t LCD_ID = 0x00;

//----------------------------------------------------------------------|
//---------------- FUNCTION PROROTYPES ------------------<
//----------------------------------------------------------------------|

static void ST7789_cmd(uint8_t cmd);
static void ST7789_data(uint8_t data);
static void ST7789_send(uint16_t value);
static uint8_t ST7789_read_id(void);
static void ST7789_data16(uint16_t value);
static void ST7789_data_bulk(const uint8_t* data, uint16_t size);
static void ST7789_set_window(int x, int y, int width, int height);

//----------------------------------------------------------------------|
//------------------------------- CODE ----------------------------<
//----------------------------------------------------------------------|

static void ST7789_cmd(uint8_t cmd) {
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &cmd, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

static void ST7789_data(uint8_t data) {
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &data, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

static void ST7789_send(uint16_t value) {
	if (value & 0x100) {
		ST7789_cmd(value);
	} else {
		ST7789_data(value);
	}
}

void ST7789_init(void) {
	int i;
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, RESET);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, SET);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, RESET);
	HAL_GPIO_WritePin(LCD_RST_GPIO_Port, LCD_RST_Pin, SET);
	HAL_Delay(50);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, SET);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_DC_Pin, SET);

	LCD_ID = ST7789_read_id();

	HAL_Delay(50);
	ST7789_cmd(ST7789_SWRESET);
	HAL_Delay(100);

	for (i = 0; i < sizeof(ST7789_init_table) / sizeof(uint16_t); i++) {
		ST7789_send(ST7789_init_table[i]);
	}

	HAL_Delay(200);
	ST7789_cmd(ST7789_SLPOUT);
	HAL_Delay(120);
	ST7789_cmd(ST7789_DISPON);
	ST7789_fill_box(0, 0, DISPLAY_W, DISPLAY_H, BLACK);
	HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, SET);
}

uint8_t ST7789_read_id(void) {
	uint8_t reg = ST7789_RDID3;
	uint8_t tx = ST7789_NOP;
	uint8_t rx;

	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, RESET);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, RESET);
	HAL_SPI_Transmit(&hspi1, &reg, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, SET);
	HAL_SPI_TransmitReceive(&hspi1, &tx, &rx, 1, HAL_MAX_DELAY);
	HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, SET);

	return rx;
}

static void ST7789_data16(uint16_t value) {
    uint8_t data[2];
    data[0] = value >> 8;
    data[1] = value;
    ST7789_data_bulk(data, 2);
}

static void ST7789_data_bulk(const uint8_t* data, uint16_t size) {
    HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_RESET);
    HAL_SPI_Transmit(&hspi1, (uint8_t*) data, size, HAL_MAX_DELAY);
    HAL_GPIO_WritePin(LCD_CS_GPIO_Port, LCD_CS_Pin, GPIO_PIN_SET);
}

static void ST7789_set_window(int x, int y, int width, int height) {
	ST7789_cmd(ST7789_CASET);
  ST7789_data16(LCD_OFFSET_X + x);
  ST7789_data16(LCD_OFFSET_X + x + width - 1);
	
  ST7789_cmd(ST7789_RASET);
  ST7789_data16(LCD_OFFSET_Y + y);
  ST7789_data16(LCD_OFFSET_Y + y + height - 1);
}

void ST7789_fill_box(int x, int y, int width, int height, uint16_t color) {
	ST7789_set_window(x, y, width, height);
	ST7789_cmd(ST7789_RAMWR);

	for (int i = 0; i < width * height; i++) {
		ST7789_data16(color);
	}
}

void ST7789_draw_image(int x, int y, int width, int height, const uint8_t* data) {
	ST7789_set_window(x, y, width, height);

	ST7789_cmd(ST7789_RAMWR);
	for (int i = 0; i < width * height * 2; i++)
		ST7789_data(data[i]);
}

void ST7789_draw_image_fast(int x, int y, int width, int height, const uint16_t* data) {
    const int chunk_size = 12800; // Number of pixels per chunk
    int current_x = x;
    int current_y = y;
    int pixels_remaining = width * height;
    int pixels_sent = 0;

    while (pixels_remaining > 0) {
        int chunk_pixels = (pixels_remaining < chunk_size) ? pixels_remaining : chunk_size;
        int chunk_rows = chunk_pixels / width;
        int chunk_cols = (chunk_pixels % width == 0) ? width : (chunk_pixels % width);

        ST7789_set_window(current_x, current_y, chunk_cols, chunk_rows);
        ST7789_cmd(ST7789_RAMWR);
        ST7789_data_bulk((uint8_t*)(data + pixels_sent), chunk_pixels * sizeof(uint16_t) * 2);

        // Update current position
        current_x += chunk_cols;
        if (current_x >= x + width) {
            current_x = x;
            current_y += chunk_rows;
        }

        pixels_remaining -= chunk_pixels;
        pixels_sent += chunk_pixels;
    }
}

void ST7789_put_pixel(int x, int y, uint16_t color) {
	ST7789_fill_box(x, y, 1, 1, color);
}

void ST7789_draw_line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color) {
	uint16_t swap;
    uint16_t steep = ABS(y1 - y0) > ABS(x1 - x0);
    if (steep) {
		swap = x0;
		x0 = y0;
		y0 = swap;

		swap = x1;
		x1 = y1;
		y1 = swap;
        //_swap_int16_t(x0, y0);
        //_swap_int16_t(x1, y1);
    }

    if (x0 > x1) {
		swap = x0;
		x0 = x1;
		x1 = swap;

		swap = y0;
		y0 = y1;
		y1 = swap;
        //_swap_int16_t(x0, x1);
        //_swap_int16_t(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = ABS(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0<=x1; x0++) {
        if (steep) {
        	ST7789_put_pixel(y0, x0, color);
        } else {
        	ST7789_put_pixel(x0, y0, color);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

void ST7789_draw_rectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color) {
	ST7789_draw_line(x1, y1, x2, y1, color);
	ST7789_draw_line(x1, y1, x1, y2, color);
	ST7789_draw_line(x1, y2, x2, y2, color);
	ST7789_draw_line(x2, y1, x2, y2, color);
}

void ST7789_draw_circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;


	ST7789_put_pixel(x0, y0 + r, color);
	ST7789_put_pixel(x0, y0 - r, color);
	ST7789_put_pixel(x0 + r, y0, color);
	ST7789_put_pixel(x0 - r, y0, color);

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		ST7789_put_pixel(x0 + x, y0 + y, color);
		ST7789_put_pixel(x0 - x, y0 + y, color);
		ST7789_put_pixel(x0 + x, y0 - y, color);
		ST7789_put_pixel(x0 - x, y0 - y, color);

		ST7789_put_pixel(x0 + y, y0 + x, color);
		ST7789_put_pixel(x0 - y, y0 + x, color);
		ST7789_put_pixel(x0 + y, y0 - x, color);
		ST7789_put_pixel(x0 - y, y0 - x, color);
	}
}

void ST7789_write_char(uint16_t x, uint16_t y, char ch, FontDef font, uint16_t color, uint16_t bgcolor) {
	uint32_t i, b, j;

	ST7789_set_window(x, y, x + font.width - 1, y + font.height - 1);

	for (i = 0; i < font.height; i++) {
		b = font.data[(ch - 32) * font.height + i];
		for (j = 0; j < font.width; j++) {
			if ((b << j) & 0x8000) {
				ST7789_put_pixel(x + j, y + i, color);
			} else {
				ST7789_put_pixel(x + j, y + i, bgcolor);
			}
		}
	}
}

void ST7789_write_string(uint16_t x, uint16_t y, const char *str, FontDef font, uint16_t color, uint16_t bgcolor) {
	while (*str) {
		if (x + font.width >= DISPLAY_W) {
			x = 0;
			y += font.height;
			if (y + font.height >= DISPLAY_H) {
				break;
			}

			if (*str == ' ') {
				// skip spaces in the beginning of the new line
				str++;
				continue;
			}
		}
		ST7789_write_char(x, y, *str, font, color, bgcolor);
		x += font.width;
		str++;
	}

}

