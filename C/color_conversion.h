/*
 * Simple functions for RGB<->HSV colors converting
 * 
 * Author: Dennis Koslowski <dennis.koslowski@gmx.de>
 * Date:   2020-01-13
 * 
 */


#include <stdint.h>
#include <math.h>

#ifndef COLOR_CONVERSION_H
#define COLOR_CONVERSION_H

typedef struct {
    double r; // a fraction between 0 and 1
    double g; // a fraction between 0 and 1
    double b; // a fraction between 0 and 1
} rgb;

typedef struct {
    uint8_t r; // 0..255
    uint8_t g; // 0..255
    uint8_t b; // 0..255
} rgbint;

typedef struct {
    double h; // angle in degrees
    double s; // a fraction between 0 and 1
    double v; // a fraction between 0 and 1
} hsv;

/*
 * RGB(0..1) -> HSV
 */
hsv rgb2hsv(rgb in);

/*
 * RGB(0..255) -> HSV
 */
hsv rgbint2hsv(rgbint in);

/*
 * HSV -> RGB(0..1)
 */
rgb hsv2rgb(hsv in);

/*
 * HSV -> RGB(0..255)
 */
rgbint hsv2rgbint(hsv in);

#endif // #ifndef COLOR_CONVERSION_H
