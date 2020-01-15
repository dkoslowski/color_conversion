/*
 * Simple functions for RGB<->HSV or RGB<->HSL color conversion
 * 
 * Author: Dennis Koslowski <dennis.koslowski@gmx.de>
 *
 */

#include <stdint.h>

#ifndef COLOR_CONVERSION_H
#define COLOR_CONVERSION_H

/*
 * HSL data
 */
typedef struct {
	double h; // hue (° of angle) 0.0 - 360.0
	double s; // saturation       0.0 - 100.0
	double l; // luminance        0.0 - 100.0
} hsl_data;

/*
 * HSV data
 */
typedef struct {
	double h; // hue (° of angle) 0.0 - 360.0
	double s; // saturation       0.0 - 100.0
	double v; // value            0.0 - 100.0
} hsv_data;

/*
 * RGB data
 */
typedef struct {
	double r; // red   0.0 - 255.0
	double g; // green 0.0 - 255.0
	double b; // blue  0.0 - 255.0
} rgb_data;

/*
 * HSL->RGB
 */
int hsl2rgb(const hsl_data *hsl, rgb_data *rgb);

/*
 * RGB->HSL
 */
int rgb2hsl(const rgb_data *rgb, hsl_data *hsl);

/*
 * HSV->RGB
 */
int hsv2rgb (const hsv_data *hsv, rgb_data *rgb);

/*
 * RGB->HSV
 */
int rgb2hsv (const rgb_data *rgb, hsv_data *hsv);

#endif // COLOR_CONVERSION_H
