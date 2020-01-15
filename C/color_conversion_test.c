/*
 * Test program for color_conversion library
 * 
 * Author: Dennis Koslowski <dennis.koslowski@gmx.de>
 * Date: 2020-01-14
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color_conversion.h"

/*
 * Get the first character from stdin
 */
static char get_char() {
	
	char ch = 0;
	const size_t len = 64;
	char buf[len];
	
	printf("\nPlease make you choice: ");

	fgets(buf, len, stdin);

	if (2 == strlen(buf)) {
		ch = buf[0];
	}
	
	return ch;
}

/*
 * Get a double from stdin
 */
static double get_double(const char* name) {

	double d = 0.0;
	const size_t len = 64;
	char buf[len];

	int ok = 0;
	do {
		printf("%s: ", name);
		fgets(buf, len, stdin);

		if (sscanf(buf, "%lf", &d) == 1) {
			ok = 1;
		} else {
			printf("Invalid input, please enter a decimal value\n");
		}

	} while (!ok);

	return d;
}

/*
 * Get a byte from stdin
 */
static double get_uint8(const char* name) {

	unsigned int val = 0;
	const size_t len = 64;
	char buf[len];

	int ok = 0;
	do {
		printf("%s: ", name);
		fgets(buf, len, stdin);

		if (sscanf(buf, "%d", &val) == 1 && val <= 0xff) {
			ok = 1;
		} else {
			printf("Invalid input, please enter a value lower then 256\n");
		}

	} while (!ok);

	return (uint8_t)val;
}

/*
 * Print HSL data
 */
static void print_hsl_data(const hsl_data *hsl) {
	printf("\nHSL data:\n");
	printf("H: %lf\n", hsl->h);
	printf("S: %lf\n", hsl->s);
	printf("L: %lf\n", hsl->l);
}

/*
 * Print HSV data
 */
static void print_hsv_data(const hsv_data *hsv) {
	printf("\nHSV data:\n");
	printf("H: %lf\n", hsv->h);
	printf("S: %lf\n", hsv->s);
	printf("V: %lf\n", hsv->v);
}

/*
 * Print RGB data
 */
static void print_rgb_data(const rgb_data *rgb) {
	printf("\nRGB data:\n");
	printf("R: %f\n", rgb->r);
	printf("G: %f\n", rgb->g);
	printf("B: %f\n", rgb->b);
}

/*
 * HSL -> RGB
 */
static void test_hsl2rgb() {
	
	printf("\nTesting hsl2rgb()\n");
	
	hsl_data hsl;
	rgb_data rgb;

	hsl.h = get_double("H");
	hsl.s = get_double("S");
	hsl.l = get_double("L");

	print_hsl_data(&hsl);
	
	if (hsl2rgb(&hsl, &rgb)) {
		print_rgb_data(&rgb);
	} else {
		printf("\nError: invalid HSL data.\n");
	}
	
}

/*
 * RGB -> HSL
 */
static void test_rgb2hsl() {
	
	printf("\nTesting rgb2hsl()\n");
	
	hsl_data hsl;
	rgb_data rgb;

	rgb.r = get_double("R");
	rgb.g = get_double("G");
	rgb.b = get_double("B");

	print_rgb_data(&rgb);
	rgb2hsl(&rgb, &hsl);
	print_hsl_data(&hsl);
}

/*
 * HSV -> RGB
 */
static void test_hsv2rgb() {

	printf("\nTesting hsv2rgb()\n");
	
	hsv_data hsv;
	rgb_data rgb;

	hsv.h = get_double("H");
	hsv.s = get_double("S");
	hsv.v = get_double("V");

	print_hsv_data(&hsv);
	
	if (hsv2rgb(&hsv, &rgb)) {
		print_rgb_data(&rgb);
	} else {
		printf("\nError: invalid HSV data.\n");
	}
	
}

/*
 * RGB -> HSV
 */
static void test_rgb2hsv() {
	
	printf("\nTesting rgb2hsv()\n");
	
	hsv_data hsv;
	rgb_data rgb;

	rgb.r = get_double("R");
	rgb.g = get_double("G");
	rgb.b = get_double("B");

	print_rgb_data(&rgb);
	rgb2hsv(&rgb, &hsv);
	print_hsv_data(&hsv);
}

int main() {
	
	printf("\nTesting the 'color_conversion' library\n");

	int repeat = 1;
	
	while (repeat) {
		
		printf("\nPossible choices:\n");
		printf("  [1] Function hsl2rgb()\n");
		printf("  [2] Function rgb2hsl()\n");
		printf("  [3] Function hsv2rgb()\n");
		printf("  [4] Function rgb2hsv()\n");
		printf("  [Q] Exit\n");
		
		switch (get_char()) {

		case '1':
			test_hsl2rgb();
			break;

		case '2':
			test_rgb2hsl();
			break;

		case '3':
			test_hsv2rgb();
			break;

		case '4':
			test_rgb2hsv();
			break;

		case 'q':
		case 'Q':
			repeat = 0;
			printf("Exit\n");
			break;

		default:
			// do nothing
			break;
		} 
	}
	
	return EXIT_SUCCESS;
}
