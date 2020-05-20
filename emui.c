#include "emui.h"
#include <stdint.h>
#include "font.h"
#ifdef DEBUG
#include <stdio.h>
#endif

#ifndef DEBUG
size_t strlen(char *t)
{
	size_t i = 0;
	while (t[i++])
    		;
	return i;
}
#else
#include <string.h>
#endif

uint8_t *em_glyph(char c)
{
	return &em_g_font_header->glyph + c * em_g_font_header->bytes_per_glyph;
}


#ifdef DEBUG
void em_printglyph(char c)
{
	uint8_t *glyph = em_glyph(c);

	for (int i = 0; i < em_g_font_header->height; i++)
	{
		for (int j = 0; j < em_g_font_header->width; j++)
		{
			putchar(*glyph & (0b10000000 >> j) ? '#' : ' ');
		}
		putchar('\n');
		glyph += em_g_font_header->width / 8;
	}
}
#endif

uint32_t em_encodecolor(int pf, em_color_t c)
{
	if (pf == EM_RGB32)
	{
		return (c.r << 16) | (c.g << 8) | c.b;
	}
}

void em_setpixel(em_ui_t *ui, unsigned x, unsigned y, em_color_t c)
{
	uint32_t encoded = em_encodecolor(ui->pixel_format, c);
	((uint32_t *)ui->buffer)[ (x + ui->width * y) ] = encoded;
}

void em_rect(em_ui_t *ui, unsigned x, unsigned y, unsigned w, unsigned h, em_color_t c)
{
	for (int i = y; i < y + h; i++)
	{
		for (int j = x; j < x + w; j++)
		{
			em_setpixel(ui, j, i, c);
		}
	}
}

void em_drawglyph(em_ui_t *ui, unsigned x, unsigned y, char c, em_color_t color)
{
	uint8_t *glyph = em_glyph(c);

	for (int i = y; i < y + em_g_font_header->height; i++)
	{
		for (int j = 0; j < em_g_font_header->width; j++)
		{
    			int xpos = j + x;
			if (*glyph & (0b10000000 >> j))
			{
				em_setpixel(ui, xpos, i, color);
			}
		}
		glyph += em_g_font_header->width / 8;
	}
}

void em_drawstring(em_ui_t *ui, unsigned x, unsigned y, char *t, em_color_t color)
{
	size_t len = strlen(t);
	for (int i = 0; i < len; i++)
	{
		em_drawglyph(ui, x, y, t[i], color);
		x += em_g_font_header->width;
	}
}
