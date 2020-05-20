#pragma once

#include <stdint.h>

// readelf -s font.o to check symbol names
extern char _binary_font_psf_start[];
extern char _binary_font_psf_end[];
extern char _binary_font_psf_size[];

// probably doesn't need to be backed, everything is 32 bits.
typedef struct __attribute__((packed)) 
{
	uint32_t magic;
	uint32_t version;
	uint32_t header_size;
	uint32_t flags;
	uint32_t num_glyph;
	uint32_t bytes_per_glyph;
	uint32_t height;
	uint32_t width;
	// &glyph
	uint8_t glyph;
} em_psfheader_t;

em_psfheader_t *em_g_font_header = (em_psfheader_t *)_binary_font_psf_start;

