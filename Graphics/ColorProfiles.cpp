#include "ColorProfiles.h"

namespace Graphics {
	namespace Convert {
		// Support macro
		#define MIN(x,y)			(x < y ? x : y)
		#define MAX(x,y)			(x > y ? x : y)
		#define ABS(x)				(x < 0 ? -x : x)
		
		// Internal constants
		static const uint16_t	INT_MULTIPLIER	= 100;
		static const float		EPSILON			= 0.00001f;

		#define FIXEDP_2_INT(x)		((x * 255) / INT_MULTIPLIER)

		// Implementation
		RGBi toRGB(const RGBf& in) {
			RGBi ret = { (uint8_t)(in.r * 255), (uint8_t)(in.g * 255), (uint8_t)(in.b * 255) }; 
			return ret;
		}

		RGBi toRGB(const COLORREF& in) {
			RGBi ret = { (uint8_t)(in & 0x000000FF), (uint8_t)((in & 0x0000FF00) >> 8), (uint8_t)((in & 0x00FF0000) >> 16) };
			return ret;
		}

		RGBi toRGB(const HSVi& in) {
			RGBi ret;
			toRGB(in, ret);
			return ret;
		}

		RGBf toRGB(const RGBi& in) {
			RGBf ret = { (float)(in.r / 255.0), (float)(in.g / 255.0), (float)(in.b / 255.0) };
			return ret;
		}

		RGBf toRGB(const HSVf& in) {
			RGBf out;
			float		hh, p, q, t, ff;
			uint32_t	i;

			if (in.s <= 0.0) {
				out.r = in.v;
				out.g = in.v;
				out.b = in.v;
				return out;
			}
			hh = in.h;
			if (hh >= 360.0) {
				hh = 0.0;
			}
			hh /= 60.0;
			i = (uint32_t)hh;
			ff = hh - i;
			p = in.v * (1.0f - in.s);
			q = in.v * (1.0f - (in.s * ff));
			t = in.v * (1.0f - (in.s * (1.0f - ff)));

			switch (i) {
				case 0:
					out.r = in.v;
					out.g = t;
					out.b = p;
					break;
				case 1:
					out.r = q;
					out.g = in.v;
					out.b = p;
					break;
				case 2:
					out.r = p;
					out.g = in.v;
					out.b = t;
					break;

				case 3:
					out.r = p;
					out.g = q;
					out.b = in.v;
					break;
				case 4:
					out.r = t;
					out.g = p;
					out.b = in.v;
					break;
				case 5:
				default:
					out.r = in.v;
					out.g = p;
					out.b = q;
					break;
			}
			return out;
		}

		void toRGB(const RGBf& in, RGBi& out) {
			out = toRGB(in);
		}

		void toRGB(const RGBi& in, RGBf& out) {
			out = toRGB(in);
		}

		void toRGB(const HSVi& in, RGBi& out) {
			int32_t		h = in.h, s = in.s, v = in.v;
			int32_t		hh, p, q, t, ff;
			uint32_t	i;

			if (s == 0) {
				uint8_t temp = (v * 255) / 100;
				out.r = temp;
				out.g = temp;
				out.b = temp;
				return;
			}
			hh = h * INT_MULTIPLIER;
			if (hh >= 36000) {
				hh = 0;
			}
			hh /= 60;
			i = hh / INT_MULTIPLIER;
			ff = hh - i * INT_MULTIPLIER;
			p = (in.v * (100 - in.s)) / INT_MULTIPLIER;
			q = (in.v * (100 - ((in.s * ff ) / INT_MULTIPLIER) )) / INT_MULTIPLIER;
			t = ( in.v * (100 - ((in.s * (100 - ff)) / INT_MULTIPLIER )) ) / INT_MULTIPLIER;

			switch (i) {
				case 0:
					out.r = FIXEDP_2_INT(in.v);
					out.g = FIXEDP_2_INT(t);
					out.b = FIXEDP_2_INT(p);
					break;
				case 1:
					out.r = FIXEDP_2_INT(q);
					out.g = FIXEDP_2_INT(in.v);
					out.b = FIXEDP_2_INT(p);
					break;
				case 2:
					out.r = FIXEDP_2_INT(p);
					out.g = FIXEDP_2_INT(in.v);
					out.b = FIXEDP_2_INT(t);
					break;

				case 3:
					out.r = FIXEDP_2_INT(p);
					out.g = FIXEDP_2_INT(q);
					out.b = FIXEDP_2_INT(in.v);
					break;
				case 4:
					out.r = FIXEDP_2_INT(t);
					out.g = FIXEDP_2_INT(p);
					out.b = FIXEDP_2_INT(in.v);
					break;
				case 5:
				default:
					out.r = FIXEDP_2_INT(in.v);
					out.g = FIXEDP_2_INT(p);
					out.b = FIXEDP_2_INT(q);
					break;
			}
		}

		HSVi toHSV(const HSVf& in) {
			HSVi ret = { (uint16_t)in.h, (uint8_t)(in.s * 100), (uint8_t)(in.v * 100) };
			return ret;
		}

		HSVf toHSV(const HSVi& in) {
			HSVf ret = { (float)in.h, ((float)in.s) / 100,  ((float)in.v) / 100 };
			return ret;
		}

		HSVi toHSV(const RGBi& in) {
			HSVi res;
			toHSV(in, res);
			return res;
		}

		HSVf toHSV(const RGBf& in) {
			HSVf out;
			float	min, max, delta;

			min = MIN(MIN(in.r, in.g), in.b);
			max = MAX(MAX(in.r, in.g), in.b);

			out.v = max;
			delta = max - min;
			if (delta < EPSILON) {
				out.s = 0;
				out.h = 0;
				return out;
			}
			if (max > 0.0f) {
				out.s = (delta / max);
			} else {
				out.s = 0.0f;
				out.h = 0.0f;
				return out;
			}
			if (in.r >= max) {
				out.h = (in.g - in.b) / delta;
			} else {
				if (in.g >= max) {
					out.h = 2.0f + (in.b - in.r) / delta;
				} else {
					out.h = 4.0f + (in.r - in.g) / delta;
				}
			}
			out.h *= 60.0;

			if (out.h < 0.0) {
				out.h += 360.0;
			}

			return out;
		}

		void toHSV(const HSVi& in, HSVf& out) {
			out = toHSV(in);
		}

		void toHSV(const HSVf& in, HSVi& out) {
			out = toHSV(in);
		}

		void toHSV(const RGBi& in, HSVi& out) {
			int16_t r = (in.r * INT_MULTIPLIER) / 255;
			int16_t g = (in.g * INT_MULTIPLIER) / 255;
			int16_t b = (in.b * INT_MULTIPLIER) / 255;

			int16_t	min, max, h;

			min = MIN(MIN(r, g), b);
			max = MAX(MAX(r, g), b);

			// H
			if (max == min) {
				h = 0;
			} else if (max == r && g >= b) {
				h = 60 * INT_MULTIPLIER * ((g - b)/(max - min));
			} else if (max == r && g < b) {
				h = 60 * INT_MULTIPLIER * ((g - b) / (max - min)) + 360 * INT_MULTIPLIER;
			} else if (max == g) {
				h = 60 * INT_MULTIPLIER * ((b - r) / (max - min)) + 120 * INT_MULTIPLIER;
			} else if (max == b) {
				h = 60 * INT_MULTIPLIER * ((r - g) / (max - min)) + 240 * INT_MULTIPLIER;
			}
			out.h = h / INT_MULTIPLIER;

			// S
			if (max == 0) {
				out.s = 0;
			} else {
				out.s = 100 - (min * 100 / max);
			}

			// V
			out.v = max;
		}

		COLORREF toCOLORREF(const RGBi& in) {
			return (in.r | (in.g << 8) | (in.b << 16)) & 0x00FFFFFF;
		}
	}
}