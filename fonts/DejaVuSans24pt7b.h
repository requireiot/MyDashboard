// Created by http://oleddisplay.squix.ch/ Consider a donation
// In case of problems make sure that you are using the font file with the correct version!
const uint8_t DejaVu_Sans_Bold_24Bitmaps[] PROGMEM = {

	// Bitmap Data:
	0x00, // ' '
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xFF,0xFF, // '!'
	0xE7,0xE7,0xE7,0xE7,0xE7,0xE7,0xE7, // '"'
	0x03,0x8E,0x01,0xC7,0x00,0xE3,0x00,0x63,0x80,0x71,0xC3,0xFF,0xFD,0xFF,0xFE,0xFF,0xFF,0x06,0x38,0x07,0x1C,0x03,0x8C,0x1F,0xFF,0xEF,0xFF,0xF7,0xFF,0xF8,0x71,0xC0,0x38,0xC0,0x18,0xE0,0x1C,0x70,0x00, // '#'
	0x03,0x00,0x0C,0x00,0x30,0x07,0xF8,0x7F,0xF9,0xFF,0xEF,0xB1,0xBC,0xC0,0xF3,0x03,0xFE,0x07,0xFF,0x0F,0xFE,0x07,0xFC,0x0D,0xF0,0x33,0xF0,0xCF,0xFF,0xFB,0xFF,0xE3,0xFE,0x00,0xC0,0x03,0x00,0x0C,0x00,0x30,0x00, // '$'
	0x3E,0x00,0xC0,0xFE,0x03,0x03,0xDE,0x0E,0x07,0x1C,0x18,0x0E,0x38,0x60,0x1C,0x71,0xC0,0x38,0xE3,0x00,0x7B,0xCE,0x00,0x7F,0x18,0xF8,0x7C,0x63,0xF8,0x01,0xCF,0x78,0x03,0x1C,0x70,0x0E,0x38,0xE0,0x38,0x71,0xC0,0x60,0xE3,0x81,0xC1,0xEF,0x03,0x01,0xFC,0x0C,0x01,0xF0, // '%'
	0x03,0xF0,0x03,0xFE,0x01,0xFF,0x80,0x78,0x20,0x1E,0x00,0x07,0x80,0x01,0xF0,0x00,0x7E,0x00,0x3F,0xC7,0x9F,0xF9,0xEF,0xBF,0x73,0xC7,0xFC,0xF0,0xFE,0x3C,0x1F,0x8F,0x83,0xE1,0xFF,0xFC,0x3F,0xFF,0x83,0xF3,0xF0, // '&'
	0xFF,0xFF,0xF8, // '''
	0x1E,0x38,0xF1,0xC7,0x8F,0x1C,0x78,0xF1,0xE3,0xC7,0x8F,0x1E,0x1C,0x3C,0x78,0x70,0xF0,0xE1,0xE0, // '('
	0xF0,0xE1,0xE1,0xC3,0xC7,0x87,0x0F,0x1E,0x3C,0x78,0xF1,0xE3,0xC7,0x1E,0x3C,0x71,0xE3,0x8F,0x00, // ')'
	0x06,0x00,0x60,0x46,0x2F,0x6F,0x3F,0xC0,0xF0,0x3F,0xCF,0x6F,0x46,0x20,0x60,0x06,0x00, // '*'
	0x03,0x80,0x07,0x00,0x0E,0x00,0x1C,0x00,0x38,0x00,0x70,0x3F,0xFF,0xFF,0xFF,0xFF,0xFE,0x07,0x00,0x0E,0x00,0x1C,0x00,0x38,0x00,0x70,0x00,0xE0,0x00, // '+'
	0x7B,0xDE,0xF7,0xBB,0xDC, // ','
	0xFF,0xFF,0xF8, // '-'
	0xFF,0xFF,0xF0, // '.'
	0x03,0x81,0xC0,0xC0,0xE0,0x70,0x30,0x38,0x1C,0x0C,0x0E,0x07,0x03,0x03,0x81,0xC0,0xC0,0xE0,0x70,0x30,0x38,0x1C,0x00, // '/'
	0x0F,0xC0,0x7F,0x83,0xFF,0x1E,0x1E,0x78,0x7B,0xC0,0xFF,0x03,0xFC,0x0F,0xF0,0x3F,0xC0,0xFF,0x03,0xFC,0x0F,0xF0,0x3D,0xE1,0xE7,0x87,0x8F,0xFC,0x1F,0xE0,0x3F,0x00, // '0'
	0x3F,0x0F,0xF0,0xFF,0x0C,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0x0F,0xFF,0xFF,0xFF,0xFF, // '1'
	0x3F,0x87,0xFF,0x3F,0xFD,0xC1,0xF8,0x07,0x80,0x3C,0x01,0xE0,0x0F,0x00,0xF8,0x0F,0x81,0xF8,0x1F,0x81,0xF8,0x1F,0x81,0xF8,0x1F,0xFF,0xFF,0xFF,0xFF,0xC0, // '2'
	0x1F,0xC3,0xFF,0x9F,0xFE,0x81,0xF0,0x07,0x80,0x3C,0x03,0xC3,0xFC,0x1F,0xE0,0xFF,0x80,0x3E,0x00,0xF0,0x07,0x80,0x3F,0x03,0xFF,0xFE,0xFF,0xE3,0xFC,0x00, // '3'
	0x01,0xF0,0x07,0xE0,0x1F,0xC0,0x3F,0x80,0xFF,0x03,0xDE,0x07,0x3C,0x1E,0x78,0x38,0xF0,0xF1,0xE3,0xC3,0xC7,0x07,0x8F,0xFF,0xFF,0xFF,0xFF,0xFF,0x80,0x78,0x00,0xF0,0x01,0xE0, // '4'
	0x7F,0xF3,0xFF,0x9F,0xFC,0xF0,0x07,0x80,0x3C,0x01,0xFF,0x0F,0xFC,0x7F,0xF2,0x07,0xC0,0x1E,0x00,0xF0,0x07,0x80,0x3F,0x03,0xFF,0xFE,0xFF,0xE1,0xFC,0x00, // '5'
	0x07,0xF0,0x7F,0xE3,0xFF,0x9F,0x02,0x78,0x03,0xC0,0x0F,0x7E,0x3F,0xFC,0xFF,0xFB,0xE1,0xFF,0x03,0xFC,0x0F,0xF0,0x3D,0xC0,0xF7,0x87,0x8F,0xFE,0x1F,0xF0,0x3F,0x00, // '6'
	0xFF,0xFF,0xFF,0xFF,0xFE,0x01,0xF0,0x0F,0x00,0xF8,0x07,0x80,0x7C,0x03,0xC0,0x1E,0x01,0xF0,0x0F,0x00,0xF8,0x07,0x80,0x7C,0x03,0xC0,0x1E,0x01,0xF0,0x00, // '7'
	0x1F,0xE1,0xFF,0xEF,0xFF,0xFE,0x1F,0xF0,0x3F,0xC0,0xFF,0x87,0x9F,0xFE,0x1F,0xE1,0xFF,0xE7,0x87,0xBC,0x0F,0xF0,0x3F,0xC0,0xFF,0x87,0xDF,0xFE,0x3F,0xF0,0x7F,0x80, // '8'
	0x0F,0xC0,0xFF,0x87,0xFF,0x1E,0x1E,0xF0,0x3B,0xC0,0xFF,0x03,0xFC,0x0F,0xF8,0x7D,0xFF,0xF3,0xFF,0xC7,0xEF,0x00,0x38,0x01,0xE4,0x0F,0x9F,0xFC,0x7F,0xE0,0xFE,0x00, // '9'
	0xFF,0xFF,0xF0,0x00,0xFF,0xFF,0xF0, // ':'
	0x7B,0xDE,0xF7,0x80,0x00,0x7B,0xDE,0xF7,0xBB,0xDC, // ';'
	0x00,0x02,0x00,0x3C,0x03,0xF8,0x1F,0xE1,0xFE,0x1F,0xE0,0x3E,0x00,0x7C,0x00,0xFF,0x00,0x3F,0xC0,0x0F,0xF0,0x07,0xF0,0x01,0xE0,0x00,0x40, // '<'
	0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x00,0x00,0x00,0x00,0x00,0x3F,0xFF,0xFF,0xFF,0xFF,0xFE, // '='
	0x80,0x01,0xE0,0x03,0xF8,0x03,0xFC,0x00,0xFF,0x00,0x3F,0xC0,0x0F,0x80,0x1F,0x01,0xFE,0x1F,0xE1,0xFE,0x07,0xF0,0x0F,0x00,0x10,0x00,0x00, // '>'
	0xFF,0x1F,0xFB,0xFF,0xE1,0xF0,0x1E,0x03,0xC0,0xF0,0x7E,0x1F,0x07,0xC0,0xF0,0x1E,0x00,0x00,0x00,0x0F,0x01,0xE0,0x3C,0x07,0x80, // '?'
	0x01,0xFC,0x00,0x3F,0xF8,0x03,0xC0,0xF0,0x38,0x01,0xC3,0x80,0x07,0x38,0x7B,0x99,0x8F,0xFC,0xFC,0x71,0xE3,0xC7,0x07,0x1E,0x38,0x38,0xF1,0xC1,0xC7,0x8E,0x0E,0x3C,0x70,0x73,0x61,0xC7,0xB9,0x8F,0xFF,0x8E,0x1E,0xF0,0x30,0x00,0x00,0xE0,0x04,0x03,0xC0,0xE0,0x0F,0xFE,0x00,0x1F,0xC0,0x00, // '@'
	0x03,0xF0,0x00,0xFC,0x00,0x7F,0x80,0x1F,0xE0,0x07,0xF8,0x03,0xFF,0x00,0xF3,0xC0,0x3C,0xF0,0x1F,0x3E,0x07,0x87,0x81,0xE1,0xE0,0xF8,0x7C,0x3F,0xFF,0x0F,0xFF,0xC7,0xFF,0xF9,0xE0,0x1E,0x78,0x07,0xBC,0x00,0xF0, // 'A'
	0xFF,0xC3,0xFF,0xCF,0xFF,0xBC,0x3E,0xF0,0x7B,0xC1,0xEF,0x0F,0xBF,0xFC,0xFF,0xF3,0xFF,0xEF,0x07,0xFC,0x0F,0xF0,0x3F,0xC0,0xFF,0x07,0xFF,0xFE,0xFF,0xFB,0xFF,0x80, // 'B'
	0x03,0xF8,0x1F,0xFC,0xFF,0xF9,0xF0,0x77,0xC0,0x2F,0x00,0x3C,0x00,0x78,0x00,0xF0,0x01,0xE0,0x03,0xC0,0x07,0x80,0x07,0x80,0x0F,0x80,0x4F,0x83,0x9F,0xFF,0x0F,0xFE,0x07,0xF0, // 'C'
	0xFF,0xC0,0xFF,0xF0,0xFF,0xFC,0xF0,0x7C,0xF0,0x3E,0xF0,0x1E,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x1E,0xF0,0x3E,0xF0,0x7C,0xFF,0xFC,0xFF,0xF0,0xFF,0xC0, // 'D'
	0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0xFE,0xFF,0xEF,0xFE,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0xFF,0xFF,0xFF,0xFF, // 'E'
	0xFF,0xFF,0xFF,0xFF,0xFF,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0xFF,0xFF,0xFF,0xFF,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0x00, // 'F'
	0x03,0xFC,0x07,0xFF,0x8F,0xFF,0xC7,0xC0,0xE7,0xC0,0x13,0xC0,0x03,0xC0,0x01,0xE0,0x00,0xF0,0x3F,0xF8,0x1F,0xFC,0x0F,0xFE,0x00,0xF7,0x80,0x7B,0xE0,0x3C,0xF8,0x1E,0x3F,0xFF,0x0F,0xFF,0x81,0xFE,0x00, // 'G'
	0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F,0xF0,0x0F, // 'H'
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // 'I'
	0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x0F,0x1F,0xFE,0xFC,0xF0, // 'J'
	0xF0,0x3F,0x78,0x3F,0x3C,0x3E,0x1E,0x3E,0x0F,0x3E,0x07,0xBE,0x03,0xFE,0x01,0xFE,0x00,0xFE,0x00,0x7F,0x80,0x3F,0xE0,0x1E,0xF8,0x0F,0x3E,0x07,0x8F,0x83,0xC3,0xE1,0xE0,0xF8,0xF0,0x3E,0x78,0x0F,0xC0, // 'K'
	0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0x00,0xF0,0x0F,0xFF,0xFF,0xFF,0xFF, // 'L'
	0xF8,0x03,0xFF,0x80,0xFF,0xF0,0x1F,0xFF,0x07,0xFF,0xE0,0xFF,0xFC,0x1F,0xFD,0xC7,0x7F,0xB8,0xEF,0xF7,0xBD,0xFE,0x77,0x3F,0xCE,0xE7,0xF8,0xF8,0xFF,0x1F,0x1F,0xE3,0xE3,0xFC,0x38,0x7F,0x80,0x0F,0xF0,0x01,0xFE,0x00,0x3C, // 'M'
	0xF8,0x0F,0xFC,0x0F,0xFC,0x0F,0xFE,0x0F,0xFE,0x0F,0xFF,0x0F,0xF7,0x0F,0xF7,0x8F,0xF3,0x8F,0xF1,0xCF,0xF1,0xCF,0xF0,0xEF,0xF0,0xEF,0xF0,0x7F,0xF0,0x7F,0xF0,0x3F,0xF0,0x3F,0xF0,0x1F, // 'N'
	0x03,0xF0,0x07,0xFF,0x83,0xFF,0xF1,0xF8,0x7E,0x78,0x07,0xBE,0x01,0xEF,0x00,0x3F,0xC0,0x0F,0xF0,0x03,0xFC,0x00,0xFF,0x00,0x3F,0xC0,0x0F,0xF8,0x07,0x9E,0x01,0xE7,0xE1,0xF8,0xFF,0xFC,0x1F,0xFC,0x01,0xFE,0x00, // 'O'
	0xFF,0xE3,0xFF,0xCF,0xFF,0xBC,0x1F,0xF0,0x3F,0xC0,0xFF,0x03,0xFC,0x1F,0xFF,0xFB,0xFF,0xCF,0xFE,0x3C,0x00,0xF0,0x03,0xC0,0x0F,0x00,0x3C,0x00,0xF0,0x03,0xC0,0x00, // 'P'
	0x03,0xF0,0x07,0xFF,0x83,0xFF,0xF1,0xF8,0x7E,0x78,0x07,0xBE,0x01,0xEF,0x00,0x3F,0xC0,0x0F,0xF0,0x03,0xFC,0x00,0xFF,0x00,0x3F,0xC0,0x0F,0xF8,0x07,0xDE,0x01,0xE7,0xE1,0xF8,0xFF,0xFC,0x1F,0xFE,0x00,0xFF,0x00,0x03,0xE0,0x00,0x78,0x00,0x1F,0x00,0x03,0xC0, // 'Q'
	0xFF,0xE0,0xFF,0xF8,0xFF,0xF8,0xF0,0x7C,0xF0,0x3C,0xF0,0x3C,0xF0,0x3C,0xF0,0x78,0xFF,0xF8,0xFF,0xE0,0xFF,0xF8,0xF0,0xF8,0xF0,0x7C,0xF0,0x3C,0xF0,0x3E,0xF0,0x1E,0xF0,0x1E,0xF0,0x1F, // 'R'
	0x1F,0xF0,0xFF,0xE7,0xFF,0xBE,0x0E,0xF0,0x0B,0xC0,0x0F,0x80,0x3F,0xE0,0x7F,0xF0,0xFF,0xE0,0x7F,0xC0,0x1F,0x00,0x3E,0x00,0xFF,0x07,0xFF,0xFE,0xFF,0xF0,0xFF,0x00, // 'S'
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0,0x03,0xC0, // 'T'
	0xF0,0x1F,0xE0,0x3F,0xC0,0x7F,0x80,0xFF,0x01,0xFE,0x03,0xFC,0x07,0xF8,0x0F,0xF0,0x1F,0xE0,0x3F,0xC0,0x7F,0x80,0xFF,0x01,0xFE,0x07,0xDE,0x0F,0x3F,0xFE,0x3F,0xF8,0x1F,0xC0, // 'U'
	0xF0,0x03,0xDE,0x01,0xE7,0x80,0x79,0xE0,0x1E,0x3C,0x0F,0x0F,0x03,0xC3,0xE1,0xF0,0x78,0x78,0x1E,0x1E,0x07,0xCF,0x80,0xF3,0xC0,0x3C,0xF0,0x0F,0xFC,0x01,0xFE,0x00,0x7F,0x80,0x1F,0xE0,0x03,0xF0,0x00,0xFC,0x00, // 'V'
	0xF0,0x3E,0x07,0xF8,0x1F,0x03,0xDE,0x0F,0x83,0xCF,0x07,0xC1,0xE7,0x87,0x70,0xF3,0xC3,0xB8,0x79,0xF1,0xDC,0x7C,0x78,0xEE,0x3C,0x3C,0xE3,0x9E,0x1E,0x71,0xCF,0x0F,0xB8,0xEF,0x83,0xDC,0x77,0x81,0xFE,0x3F,0xC0,0xFE,0x0F,0xE0,0x7F,0x07,0xF0,0x1F,0x83,0xF0,0x0F,0xC1,0xF8,0x07,0xC0,0x7C,0x00, // 'W'
	0xF8,0x07,0xDF,0x03,0xE3,0xE1,0xF0,0xF8,0x7C,0x1F,0x3E,0x03,0xFF,0x00,0x7F,0x80,0x1F,0xE0,0x03,0xF0,0x00,0xFC,0x00,0x7F,0x80,0x3F,0xF0,0x0F,0x3C,0x07,0xCF,0x83,0xE1,0xF0,0xF0,0x3C,0x7C,0x0F,0xBE,0x01,0xF0, // 'X'
	0xF8,0x07,0xDF,0x03,0xE3,0xC1,0xF0,0xF8,0x7C,0x1F,0x3E,0x03,0xFF,0x00,0xFF,0xC0,0x1F,0xE0,0x03,0xF0,0x00,0xFC,0x00,0x1E,0x00,0x07,0x80,0x01,0xE0,0x00,0x78,0x00,0x1E,0x00,0x07,0x80,0x01,0xE0,0x00,0x78,0x00, // 'Y'
	0xFF,0xFF,0xFF,0xFF,0xFF,0xF8,0x03,0xF0,0x07,0xC0,0x1F,0x00,0x7C,0x01,0xF0,0x07,0xC0,0x0F,0x80,0x3E,0x00,0xF8,0x03,0xE0,0x0F,0x80,0x3F,0x00,0x7F,0xFF,0xFF,0xFF,0xFF,0xFC, // 'Z'
	0xFF,0xFF,0xFF,0x8F,0x1E,0x3C,0x78,0xF1,0xE3,0xC7,0x8F,0x1E,0x3C,0x78,0xF1,0xE3,0xFF,0xFF,0xE0, // '['
	0xE0,0x70,0x18,0x0E,0x07,0x01,0x80,0xE0,0x70,0x18,0x0E,0x07,0x01,0x80,0xE0,0x70,0x18,0x0E,0x07,0x01,0x80,0xE0,0x70, // '\'
	0xFF,0xFF,0xF8,0xF1,0xE3,0xC7,0x8F,0x1E,0x3C,0x78,0xF1,0xE3,0xC7,0x8F,0x1E,0x3F,0xFF,0xFF,0xE0, // ']'
	0x03,0x80,0x0F,0x80,0x3F,0x80,0xF7,0x83,0xC7,0x8F,0x07,0xB8,0x03,0x80, // '^'
	0xFF,0xFF,0xFF, // '_'
	0x70,0x70,0x70,0x70, // '`'
	0x1F,0xC3,0xFF,0x9F,0xFC,0x81,0xF0,0x07,0x8F,0xFD,0xFF,0xFF,0xFF,0xF0,0x7F,0x87,0xFF,0xFE,0xFF,0xF3,0xE7,0x80, // 'a'
	0xF0,0x03,0xC0,0x0F,0x00,0x3C,0x00,0xF0,0x03,0xCF,0x8F,0xFF,0x3F,0xFE,0xF8,0x7B,0xC0,0xFF,0x03,0xFC,0x0F,0xF0,0x3F,0xC0,0xFF,0x87,0xBF,0xFE,0xFF,0xF3,0xCF,0x80, // 'b'
	0x0F,0xE3,0xFF,0x7F,0xF7,0xC1,0xF8,0x0F,0x00,0xF0,0x0F,0x00,0xF8,0x07,0xC1,0x7F,0xF3,0xFF,0x0F,0xE0, // 'c'
	0x00,0x3C,0x00,0xF0,0x03,0xC0,0x0F,0x00,0x3C,0x7C,0xF3,0xFF,0xDF,0xFF,0x78,0x7F,0xC0,0xFF,0x03,0xFC,0x0F,0xF0,0x3F,0xC0,0xF7,0x87,0xDF,0xFF,0x3F,0xFC,0x7C,0xF0, // 'd'
	0x0F,0xC0,0xFF,0xC7,0xFF,0x9E,0x1E,0xF0,0x3F,0xFF,0xFF,0xFF,0xFF,0xFF,0xF0,0x01,0xE0,0x67,0xFF,0x8F,0xFE,0x0F,0xE0, // 'e'
	0x0F,0xC7,0xF3,0xFC,0xF0,0x3C,0x3F,0xFF,0xFF,0xFF,0x3C,0x0F,0x03,0xC0,0xF0,0x3C,0x0F,0x03,0xC0,0xF0,0x3C,0x0F,0x00, // 'f'
	0x1F,0x3C,0xFF,0xF7,0xFF,0xDE,0x1F,0xF0,0x3F,0xC0,0xFF,0x03,0xFC,0x0F,0xF0,0x3D,0xE1,0xF7,0xFF,0xCF,0xFF,0x1F,0x3C,0x00,0xF2,0x07,0xCF,0xFE,0x3F,0xF0,0x7F,0x00, // 'g'
	0xF0,0x07,0x80,0x3C,0x01,0xE0,0x0F,0x00,0x79,0xF3,0xFF,0xDF,0xFF,0xF8,0xFF,0x83,0xFC,0x1F,0xE0,0xFF,0x07,0xF8,0x3F,0xC1,0xFE,0x0F,0xF0,0x7F,0x83,0xC0, // 'h'
	0xFF,0xFF,0x0F,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // 'i'
	0x1E,0x3C,0x78,0xF0,0x03,0xC7,0x8F,0x1E,0x3C,0x78,0xF1,0xE3,0xC7,0x8F,0x1E,0x3C,0x79,0xFF,0xDF,0xBE,0x00, // 'j'
	0xF0,0x03,0xC0,0x0F,0x00,0x3C,0x00,0xF0,0x03,0xC3,0xEF,0x1F,0x3C,0xF8,0xF7,0xC3,0xFE,0x0F,0xF0,0x3F,0xC0,0xFF,0x83,0xDF,0x0F,0x3E,0x3C,0x7C,0xF0,0xFB,0xC1,0xF0, // 'k'
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // 'l'
	0xF3,0xC3,0xCF,0xFE,0xFE,0xFF,0xFF,0xFF,0x8F,0x8F,0xF0,0xF0,0xFF,0x0F,0x0F,0xF0,0xF0,0xFF,0x0F,0x0F,0xF0,0xF0,0xFF,0x0F,0x0F,0xF0,0xF0,0xFF,0x0F,0x0F,0xF0,0xF0,0xF0, // 'm'
	0xF3,0xE7,0xFF,0xBF,0xFF,0xF1,0xFF,0x07,0xF8,0x3F,0xC1,0xFE,0x0F,0xF0,0x7F,0x83,0xFC,0x1F,0xE0,0xFF,0x07,0x80, // 'n'
	0x0F,0xC0,0xFF,0xC7,0xFF,0x9E,0x1E,0xF0,0x3F,0xC0,0xFF,0x03,0xFC,0x0F,0xF0,0x3D,0xE1,0xE7,0xFF,0x8F,0xFC,0x0F,0xC0, // 'o'
	0xF3,0xE3,0xFF,0xCF,0xFF,0xBE,0x1E,0xF0,0x3F,0xC0,0xFF,0x03,0xFC,0x0F,0xF0,0x3F,0xE1,0xEF,0xFF,0xBF,0xFC,0xF3,0xE3,0xC0,0x0F,0x00,0x3C,0x00,0xF0,0x03,0xC0,0x00, // 'p'
	0x1F,0x3C,0xFF,0xF7,0xFF,0xDE,0x1F,0xF0,0x3F,0xC0,0xFF,0x03,0xFC,0x0F,0xF0,0x3D,0xE1,0xF7,0xFF,0xCF,0xFF,0x1F,0x3C,0x00,0xF0,0x03,0xC0,0x0F,0x00,0x3C,0x00,0xF0, // 'q'
	0xF3,0xFF,0xFF,0xFF,0xF1,0xF8,0x3C,0x0F,0x03,0xC0,0xF0,0x3C,0x0F,0x03,0xC0,0xF0,0x00, // 'r'
	0x3F,0x87,0xFE,0xFF,0xEF,0x06,0xF8,0x0F,0xFC,0x7F,0xE0,0xFF,0x00,0xFC,0x0F,0xFF,0xFF,0xFE,0x3F,0x80, // 's'
	0x3C,0x0F,0x03,0xC0,0xF0,0xFF,0xFF,0xFF,0xFC,0xF0,0x3C,0x0F,0x03,0xC0,0xF0,0x3C,0x0F,0x03,0xFC,0x7F,0x0F,0xC0, // 't'
	0xF0,0x7F,0x83,0xFC,0x1F,0xE0,0xFF,0x07,0xF8,0x3F,0xC1,0xFE,0x0F,0xF0,0x7F,0xC7,0xFF,0xFE,0xFF,0xF3,0xE7,0x80, // 'u'
	0xF0,0x1E,0xF0,0x79,0xE0,0xF3,0xC1,0xE3,0xC7,0x87,0x8F,0x07,0x1C,0x0F,0x78,0x1E,0xF0,0x1D,0xC0,0x3F,0x80,0x3E,0x00,0x7C,0x00, // 'v'
	0xF0,0x70,0x7F,0xC7,0xC7,0xDE,0x3E,0x3C,0xF1,0xF1,0xE7,0x8F,0x8F,0x3E,0xEE,0xF8,0xF7,0x77,0x87,0xBB,0xBC,0x3D,0xDD,0xE0,0xFC,0x7E,0x07,0xE3,0xF0,0x3F,0x1F,0x81,0xF8,0xFC,0x00, // 'w'
	0xF8,0x3E,0xF8,0xF8,0xFB,0xE0,0xF7,0x80,0xFE,0x01,0xFC,0x01,0xF0,0x07,0xF0,0x0F,0xE0,0x3D,0xE0,0xF1,0xE3,0xE3,0xEF,0x83,0xE0, // 'x'
	0xF8,0x3E,0xF0,0x79,0xE0,0xF1,0xE3,0xE3,0xC7,0x87,0xDF,0x07,0xBC,0x0F,0xF8,0x0F,0xF0,0x1F,0xC0,0x1F,0x80,0x3E,0x00,0x7C,0x00,0xF8,0x01,0xE0,0x1F,0xC0,0x3F,0x00,0x7C,0x00, // 'y'
	0xFF,0xFF,0xFF,0xFF,0xF0,0x3E,0x07,0xE0,0xFC,0x1F,0x83,0xF0,0x7E,0x07,0xC0,0xFF,0xFF,0xFF,0xFF,0xF0, // 'z'
	0x03,0xE0,0xFC,0x3F,0x87,0x80,0xF0,0x1E,0x03,0xC0,0x78,0x0F,0x03,0xE3,0xF8,0x7E,0x0F,0xE0,0x3E,0x03,0xC0,0x78,0x0F,0x01,0xE0,0x3C,0x07,0xF0,0x7E,0x07,0xC0, // '{'
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF, // '|'
	0xF8,0x1F,0x83,0xF8,0x0F,0x01,0xE0,0x3C,0x07,0x80,0xF0,0x1E,0x03,0xE0,0x3F,0x83,0xF0,0xFE,0x3E,0x07,0x80,0xF0,0x1E,0x03,0xC0,0x78,0x7F,0x0F,0xC1,0xF0,0x00 // '}'
};
const GFXglyph DejaVu_Sans_Bold_24Glyphs[] PROGMEM = {
// bitmapOffset, width, height, xAdvance, xOffset, yOffset
	  {     0,   1,   1,   9,    0,   -1 }, // ' '
	  {     1,   4,  18,  12,    3,  -18 }, // '!'
	  {    10,   8,   7,  14,    2,  -18 }, // '"'
	  {    17,  17,  18,  21,    2,  -18 }, // '#'
	  {    56,  14,  23,  18,    1,  -19 }, // '$'
	  {    97,  23,  18,  25,    1,  -18 }, // '%'
	  {   149,  18,  18,  22,    1,  -18 }, // '&'
	  {   190,   3,   7,   8,    2,  -18 }, // '''
	  {   193,   7,  21,  12,    2,  -18 }, // '('
	  {   212,   7,  21,  12,    2,  -18 }, // ')'
	  {   231,  12,  11,  14,    0,  -18 }, // '*'
	  {   248,  15,  15,  21,    3,  -15 }, // '+'
	  {   277,   5,   8,  10,    1,   -5 }, // ','
	  {   282,   7,   3,  11,    1,   -9 }, // '-'
	  {   285,   4,   5,  10,    2,   -5 }, // '.'
	  {   288,   9,  20,  10,    0,  -18 }, // '/'
	  {   311,  14,  18,  18,    1,  -18 }, // '0'
	  {   343,  12,  18,  18,    3,  -18 }, // '1'
	  {   370,  13,  18,  18,    2,  -18 }, // '2'
	  {   400,  13,  18,  18,    1,  -18 }, // '3'
	  {   430,  15,  18,  18,    1,  -18 }, // '4'
	  {   464,  13,  18,  18,    2,  -18 }, // '5'
	  {   494,  14,  18,  18,    1,  -18 }, // '6'
	  {   526,  13,  18,  18,    2,  -18 }, // '7'
	  {   556,  14,  18,  18,    1,  -18 }, // '8'
	  {   588,  14,  18,  18,    1,  -18 }, // '9'
	  {   620,   4,  13,  11,    3,  -13 }, // ':'
	  {   627,   5,  16,  11,    2,  -13 }, // ';'
	  {   637,  15,  14,  21,    3,  -14 }, // '<'
	  {   664,  15,   9,  21,    3,  -12 }, // '='
	  {   681,  15,  14,  21,    3,  -14 }, // '>'
	  {   708,  11,  18,  15,    2,  -18 }, // '?'
	  {   733,  21,  21,  25,    2,  -18 }, // '@'
	  {   789,  18,  18,  20,    0,  -18 }, // 'A'
	  {   830,  14,  18,  19,    2,  -18 }, // 'B'
	  {   862,  15,  18,  19,    1,  -18 }, // 'C'
	  {   896,  16,  18,  21,    2,  -18 }, // 'D'
	  {   932,  12,  18,  17,    2,  -18 }, // 'E'
	  {   959,  12,  18,  17,    2,  -18 }, // 'F'
	  {   986,  17,  18,  21,    1,  -18 }, // 'G'
	  {  1025,  16,  18,  21,    2,  -18 }, // 'H'
	  {  1061,   4,  18,  10,    2,  -18 }, // 'I'
	  {  1070,   8,  23,  10,   -2,  -18 }, // 'J'
	  {  1093,  17,  18,  20,    2,  -18 }, // 'K'
	  {  1132,  12,  18,  16,    2,  -18 }, // 'L'
	  {  1159,  19,  18,  25,    2,  -18 }, // 'M'
	  {  1202,  16,  18,  21,    2,  -18 }, // 'N'
	  {  1238,  18,  18,  21,    1,  -18 }, // 'O'
	  {  1279,  14,  18,  19,    2,  -18 }, // 'P'
	  {  1311,  18,  22,  21,    1,  -18 }, // 'Q'
	  {  1361,  16,  18,  19,    2,  -18 }, // 'R'
	  {  1397,  14,  18,  18,    2,  -18 }, // 'S'
	  {  1429,  16,  18,  17,    0,  -18 }, // 'T'
	  {  1465,  15,  18,  20,    2,  -18 }, // 'U'
	  {  1499,  18,  18,  20,    0,  -18 }, // 'V'
	  {  1540,  25,  18,  27,    1,  -18 }, // 'W'
	  {  1597,  18,  18,  20,    0,  -18 }, // 'X'
	  {  1638,  18,  18,  18,   -1,  -18 }, // 'Y'
	  {  1679,  15,  18,  18,    1,  -18 }, // 'Z'
	  {  1713,   7,  21,  12,    2,  -18 }, // '['
	  {  1732,   9,  20,  10,    0,  -18 }, // '\'
	  {  1755,   7,  21,  12,    2,  -18 }, // ']'
	  {  1774,  15,   7,  21,    2,  -18 }, // '^'
	  {  1788,  12,   2,  13,    0,    4 }, // '_'
	  {  1791,   7,   4,  13,    1,  -19 }, // '`'
	  {  1795,  13,  13,  17,    1,  -13 }, // 'a'
	  {  1817,  14,  18,  18,    2,  -18 }, // 'b'
	  {  1849,  12,  13,  15,    1,  -13 }, // 'c'
	  {  1869,  14,  18,  18,    1,  -18 }, // 'd'
	  {  1901,  14,  13,  17,    1,  -13 }, // 'e'
	  {  1924,  10,  18,  11,    1,  -18 }, // 'f'
	  {  1947,  14,  18,  18,    1,  -13 }, // 'g'
	  {  1979,  13,  18,  18,    2,  -18 }, // 'h'
	  {  2009,   4,  18,   9,    2,  -18 }, // 'i'
	  {  2018,   7,  23,   9,   -1,  -18 }, // 'j'
	  {  2039,  14,  18,  17,    2,  -18 }, // 'k'
	  {  2071,   4,  18,   9,    2,  -18 }, // 'l'
	  {  2080,  20,  13,  26,    2,  -13 }, // 'm'
	  {  2113,  13,  13,  18,    2,  -13 }, // 'n'
	  {  2135,  14,  13,  17,    1,  -13 }, // 'o'
	  {  2158,  14,  18,  18,    2,  -13 }, // 'p'
	  {  2190,  14,  18,  18,    1,  -13 }, // 'q'
	  {  2222,  10,  13,  13,    2,  -13 }, // 'r'
	  {  2239,  12,  13,  15,    1,  -13 }, // 's'
	  {  2259,  10,  17,  12,    0,  -17 }, // 't'
	  {  2281,  13,  13,  18,    2,  -13 }, // 'u'
	  {  2303,  15,  13,  17,    0,  -13 }, // 'v'
	  {  2328,  21,  13,  23,    1,  -13 }, // 'w'
	  {  2363,  15,  13,  16,    0,  -13 }, // 'x'
	  {  2388,  15,  18,  17,    0,  -13 }, // 'y'
	  {  2422,  12,  13,  15,    1,  -13 }, // 'z'
	  {  2442,  11,  22,  18,    3,  -18 }, // '{'
	  {  2473,   3,  24,  10,    3,  -18 }, // '|'
	  {  2482,  11,  22,  18,    3,  -18 } // '}'
};
const GFXfont DejaVu_Sans_Bold_24 PROGMEM = {
(uint8_t  *)DejaVu_Sans_Bold_24Bitmaps,(GFXglyph *)DejaVu_Sans_Bold_24Glyphs,0x20, 0x7E, 29};