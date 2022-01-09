/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpceia <joao.p.ceia@gmail.com>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/09 17:03:41 by jpceia            #+#    #+#             */
/*   Updated: 2022/01/09 17:46:37 by jpceia           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "miniRT.h"

// creates an BMP file with W x H dimensions, from a given array of pixels
void create_bmp(const char *fname, int width, int height, t_rgb *pixels)
{
	// open file
	FILE *fp = fopen(fname, "wb");
	if (!fp)
		return;

	// write header
	unsigned char header[54] = {
		'B', 'M', // magic
		0, 0, 0, 0, // size in bytes
		0, 0, // app data
		0, 0, // app data
		54, 0, 0, 0, // start of data - 54 bytes from start
		40, 0, 0, 0, // struct - 40 bytes
		0, 0, 0, 0, // width in pixels
		0, 0, 0, 0, // height in pixels
		1, 0, // number of planes
		24, 0, // bits per pixel
		0, 0, 0, 0, // compression is none
		0, 0, 0, 0, // image bits size
		0, 0, 0, 0, // horz resolution in pixels / m
		0, 0, 0, 0, // vert resolution in pixels / m
		0, 0, 0, 0, // #colors in palette
		0, 0, 0, 0 // #important colors
	};

	// fill in data
	int size = width * height * 3;
	header[2] = (unsigned char)(size);
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[18] = (unsigned char)(width);
	header[19] = (unsigned char)(width >> 8);
	header[20] = (unsigned char)(width >> 16);
	header[21] = (unsigned char)(width >> 24);
	header[22] = (unsigned char)(height);
	header[23] = (unsigned char)(height >> 8);
	header[24] = (unsigned char)(height >> 16);
	header[25] = (unsigned char)(height >> 24);

	// write header
	fwrite(header, 1, 54, fp);

	// write pixels
	for (int i = 0; i < width * height; i++)
	{
		unsigned char data[3] = {
			(255 * atan(fmaxf(pixels[i].z, 0) * BRIGHTNESS_RATIO) * 2 / M_PI),
			(255 * atan(fmaxf(pixels[i].y, 0) * BRIGHTNESS_RATIO) * 2 / M_PI),
			(255 * atan(fmaxf(pixels[i].x, 0) * BRIGHTNESS_RATIO) * 2 / M_PI)
		};
		fwrite(data, 1, 3, fp);
	}

	// close file
	fclose(fp);
}
