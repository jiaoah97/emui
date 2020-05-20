#pragma once

typedef struct
{
	unsigned width;
	unsigned height;
	unsigned char *buffer;
	enum
	{
		EM_RGB32,
	} pixel_format;
} em_ui_t;

typedef struct
{
	unsigned char r, g, b;
} em_color_t;

void em_rect(em_ui_t *ui, unsigned x, unsigned y, unsigned w, unsigned h, em_color_t c);
void em_drawglyph(em_ui_t *ui, unsigned x, unsigned y, char c, em_color_t color);
void em_drawstring(em_ui_t *ui, unsigned x, unsigned y, char *t, em_color_t color);
