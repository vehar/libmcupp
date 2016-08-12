#pragma once

#include "Utils/Sugar.h"

namespace Graphics {
	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	// RGB types

	#pragma pack(push, 1)

	struct RGBi {
		uint8_t r;
		uint8_t g;
		uint8_t b;

		RGBi(uint8_t r = 0, uint8_t g = 0, uint8_t b = 0) : r(r), g(g), b(b) {}
		void set(uint8_t r, uint8_t g, uint8_t b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}
	};
	
	struct RGBf {
		float r;
		float g;
		float b;

		RGBf(float r = .0, float g = .0, float b = .0) : r(r), g(g), b(b) {}
		void set(uint8_t r, uint8_t g, uint8_t b) {
			this->r = r;
			this->g = g;
			this->b = b;
		}
	};

	#pragma pack(pop)

	// ------------------------------------------------------------------------
	// HSV types

	#pragma pack(push, 1)

	struct HSVi {
		uint16_t	h	: 9;
		uint16_t	s	: 7;
		uint16_t	v	: 7;
	};

	struct HSVf {
		float		h;
		float		s;
		float		v;
	};

	#pragma pack(pop)

	// ------------------------------------------------------------------------
	// Colorref

	typedef uint32_t		COLORREF;

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	// Convert functions

	namespace Convert {
		RGBi		toRGB		(const RGBf& in);
		RGBi		toRGB		(const HSVi& in);
		RGBi		toRGB		(const COLORREF& in);
		RGBf		toRGB		(const RGBi& in);
		RGBf		toRGB		(const HSVf& in);
		void		toRGB		(const RGBf& in, RGBi& out);
		void		toRGB		(const RGBi& in, RGBf& out);
		void		toRGB		(const HSVi& in, RGBi& out);

		HSVi		toHSV		(const HSVf& in);
		HSVi		toHSV		(const RGBi& in);
		HSVf		toHSV		(const HSVi& in);
		HSVf		toHSV		(const RGBf& in);
		void		toHSV		(const HSVi& in, HSVf& out);
		void		toHSV		(const HSVf& in, HSVi& out);
		void		toHSV		(const RGBi& in, HSVi& out);

		COLORREF	toCOLORREF	(const RGBi& in);
	}

	// ------------------------------------------------------------------------
	// ------------------------------------------------------------------------
	// Constant colors

	typedef enum {
		Black		= 0,
		White		= 1,
		Red			= 2,
		Lime		= 3,
		Blue		= 4,
		Yellow		= 5,
		Cyan		= 6,
		Magenta		= 7,
		Silver		= 8,
		Gray		= 9,
		Maroon		= 10,
		Olive		= 11,
		Green		= 12,
		Purple		= 13,
		Teal		= 14,
		Navy		= 15,
		DarkGreen	= 16,
	} ConstantColor;
	
	const RGBi RGBColor[17] = {
		{0,   0,   0  },			// 0
		{255, 255, 255},			// 1
		{255, 0,   0  },			// 2
		{0,   255, 0  },			// 3
		{0,   0,   255},			// 4
		{255, 255, 0  },			// 5
		{0,   255, 255},			// 6
		{255, 0,   255},			// 7
		{192, 192, 192},			// 8
		{128, 128, 128},			// 9
		{128, 0,   0  },			// 10
		{128, 128, 0  },			// 11
		{0,   128, 0  },			// 12
		{128, 0,   128},			// 13
		{0,   128, 128},			// 14
		{0,   0,   128},			// 15
		{0,   1,   0  },			// 16
	};
}