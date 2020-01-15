/*
 * Simple functions for RGB<->HSV or RGB<->HSL color conversion
 * 
 * Author: Dennis Koslowski <dennis.koslowski@gmx.de>
 *
 */

#include <math.h>

#include "color_conversion.h"

#define FULL_CIRCLE 360.0

/*
 * A helper for transformation in hsl2rgb()
 */
static double rgb_comp(double tX, double t1, double t2) {
	
	double comp;
	
	if (tX * 6 < 1.0) {
		comp = t2 + (t1 - t2) * tX * 6;
	} else if (tX * 2 < 1.0) {
		comp = t1;
	} else if (tX * 3 < 2.0) {
		comp = t2 + (t1 - t2) * (0.666 - tX) * 6;
	} else {
		comp = t2;
	}
	
	return comp * 255.0;
}

/*
 * HSL->RGB
 */
int hsl2rgb(const hsl_data *hsl, rgb_data *rgb) {

	double h, s, l;
	double p, q;
	double r, g, b;
	
	h = hsl->h / 360.0;
	s = hsl->s / 100.0;
	l = hsl->l / 100.0;

	// data consistency check
	if (h < 0.0 || h > 1.0 ||
		s < 0.0 || s > 1.0 ||
		l < 0.0 || l > 1.0)
	{
		return 0;
	}
	
	if (0 == s) {

		// no saturation, just convert the luminance to RGB
		double tmp = l * 255.0;
		rgb->r = tmp;
		rgb->g = tmp;
		rgb->b = tmp;
		
		return 1;	
	}

	if (l < 0.5) {
		p = l * (1.0 + s);
	} else {
		p = l + s - l * s;
	}
	
	q = 2 * l - p;
	
	r = h + 0.333;
	if (r > 1)
		r -= 1.0;
	g = h;
	b = h - 0.333;
	if (b < 0)
		b += 1;

	rgb->r = rgb_comp(r, p, q);
	rgb->g = rgb_comp(g, p, q);
	rgb->b = rgb_comp(b, p, q);
	
	return 1;
}

/*
 * RGB->HSL
 */
int rgb2hsl(const rgb_data *rgb, hsl_data *hsl) {
	
	double r,g,b;
	double min, max, delta;
	double h,s,l;
	
	r = rgb->r / 255.0;
	g = rgb->g / 255.0;
	b = rgb->b / 255.0;

	// data consistency check
	if (r < 0.0 || r > 1.0 ||
		g < 0.0 || g > 1.0 ||
		b < 0.0 || b > 1.0)
	{
		return 0;
	}

	min   = fmin(r, fmin(g, b));
	max   = fmax(r, fmax(g, b));
	delta = max - min;
	
	// Luminance
	l = (min + max) / 2;
	hsl->l = l * 100.0; 

	if (min == max) {

		// Gray, no saturation, hue irrelevant
		hsl->h = 0.0;
		hsl->s = 0.0;
		return 1;
	}
	
	// Saturation
	if (l < 0.5) {
		hsl->s = delta / (max + min) * 100.0;
	} else {
		hsl->s = delta / (2.0 - max - min) * 100.0;
	}

	// Hue
	if (r == max)
		// Yellow -- Magenta
		h = (g - b) / delta;

	else if (g == max)
		// Cyan -- Yellow
		h = 2.0 + (b - r) / delta;

	else
		// Magenta -- Cyan
		h = 4.0 + (r - g) / delta;

	if (h > 6.0)
		h -= 6.0;
	else if (h < 0.0)
		h += 6.0;

	hsl->h = h * 60;
	
	return 1;
}

/*
 * HSV->RGB
 */
int hsv2rgb (const hsv_data *hsv, rgb_data *rgb) {

	int i;
	double h, s, v;
	double f, p, q, t;
	double r, g, b;

	h = hsv->h / 60.0; // sector 0 to 5
	s = hsv->s / 100.0;
	v = hsv->v / 100.0;
	
	// data consistency check
	if (h < 0.0 || h > 6.0 ||
		s < 0.0 || s > 1.0  ||
		v < 0.0 || v > 1.0)
	{
		return 0;
	}

	if( s == 0 ) {
		// shades of gray
		rgb->r = rgb->g = rgb->b = v * 255.0;
		return 1;
	}

	i = floor(h);  // integral part of h
	f = h - i;     // factorial part of h
	p = v * (1 - s);
	q = v * (1 - s * f);
	t = v * (1 - s * (1 - f));

	switch (i) {

	case 0:
		r = v;
		g = t;
		b = p;
		break;

	case 1:
		r = q;
		g = v;
		b = p;
		break;

	case 2:
		r = p;
		g = v;
		b = t;
		break;

	case 3:
		r = p;
		g = q;
		b = v;
		break;
	
	case 4:
		r = t;
		g = p;
		b = v;
		break;
	
	case 5:
		r = v;
		g = p;
		b = q;
		break;

	default:
		break;
	}
	
	rgb->r = r * 255.0;
	rgb->g = g * 255.0;
	rgb->b = b * 255.0;
	
	return 1;
}

/*
 * RGB->HSV
 */
int rgb2hsv (const rgb_data *rgb, hsv_data *hsv) { 

	double r, g, b;
	double min, max, delta;
	double h;

	r = rgb->r / 255.0;
	g = rgb->g / 255.0;
	b = rgb->b / 255.0;

	// data consistency check
	if (r < 0.0 || r > 1.0 ||
		g < 0.0 || g > 1.0 ||
		b < 0.0 || b > 1.0)
	{
		return 0;
	}

	max = fmax(r, fmax(g, b));
	min = fmin(r, fmin(g, b));
	delta = max - min;

	// Value
	hsv->v = max * 100.0;

	if( max != 0 ) {
		hsv->s = (delta / max) * 100.0;
	
	} else {
		// black
		hsv->h = 0.0;
		hsv->s = 0.0;
		return;
	}

	if (max == min) {
		// gray
		hsv->h = 0.0;
		hsv->s = 0.0;
		return;
	}

	// Hue
	if (r == max)
		// Yellow -- Magenta
		h = (g - b) / delta;

	else if (g == max)
		// Cyan -- Yellow
		h = 2.0 + (b - r) / delta;

	else
		// Magenta -- Cyan
		h = 4.0 + (r - g) / delta;

	if (h < 0.0)
		h += 6.0;

	hsv->h = h * 60.0;
}
