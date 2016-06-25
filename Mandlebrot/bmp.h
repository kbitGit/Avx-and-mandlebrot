#pragma once
#include<complex>
#include<math.h>
#include<CL\cl.h>
#define WIDTH 2000
#define HEIGHT 2000	
#define XMAX 1.5
#define XMIN -2.5
#define YMAX 2.0
#define YMIN -2.0
#define MAXITERATIONS 20000
double PWIDTH = ((XMAX - XMIN) / WIDTH);
double PHEIGHT = ((YMAX - YMIN) / HEIGHT);

void mandelbrot(FILE* fp, int x, int y) {
	static unsigned char color[3];
	double cx = (XMIN + x*PWIDTH);
	double cy = (YMIN + y*PHEIGHT);
	int iter = 0;
	if (fabs(cy) < PHEIGHT / 2)
		cy = 0;
	double zx = 0.0;
	double zy = 0.0;
	double z2x = zx*zx;
	double z2y = zy*zy;
	while (iter < MAXITERATIONS && ((z2x + z2y) < 4)) {

		zy = 2 * zx*zy + cy;
		zx = z2x - z2y + cx;
		z2x = zx*zx;
		z2y = zy*zy;
		iter++;
	}
	color[0] = 0;
	color[1] = 0;
	color[2] = 0;

	if (iter < MAXITERATIONS)
	{
		color[0] = 255;
		color[1] = 255;
		color[2] = 255;
	}
	fwrite(color, 1, 3, fp);

}



void drawbmp(char * filename) {

	unsigned int headers[13];
	FILE* outfile;
	int extrabytes;
	int paddedsize;
	int x; int y; int n;


	extrabytes = 4 - ((WIDTH * 3) % 4);                 // How many bytes of padding to add to each
														// horizontal line - the size of which must
														// be a multiple of 4 bytes.
	if (extrabytes == 4)
		extrabytes = 0;

	paddedsize = ((WIDTH * 3) + extrabytes) * HEIGHT;

	// Headers...
	// Note that the "BM" identifier in bytes 0 and 1 is NOT included in these "headers".

	headers[0] = paddedsize + 54;      // bfSize (whole file size)
	headers[1] = 0;                    // bfReserved (both)
	headers[2] = 54;                   // bfOffbits
	headers[3] = 40;                   // biSize
	headers[4] = WIDTH;  // biWidth
	headers[5] = HEIGHT; // biHeight

						 // Would have biPlanes and biBitCount in position 6, but they're shorts.
						 // It's easier to write them out separately (see below) than pretend
						 // they're a single int, especially with endian issues...

	headers[7] = 0;                    // biCompression
	headers[8] = paddedsize;           // biSizeImage
	headers[9] = 0;                    // biXPelsPerMeter
	headers[10] = 0;                    // biYPelsPerMeter
	headers[11] = 0;                    // biClrUsed
	headers[12] = 0;                    // biClrImportant

	outfile = fopen(filename, "wb");

	//
	// Headers begin...
	// When printing ints and shorts, we write out 1 character at a time to avoid endian issues.
	//

	fprintf(outfile, "BM");

	for (n = 0; n <= 5; n++)
	{
		fprintf(outfile, "%c", headers[n] & 0x000000FF);
		fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
		fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
		fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
	}

	// These next 4 characters are for the biPlanes and biBitCount fields.

	fprintf(outfile, "%c", 1);
	fprintf(outfile, "%c", 0);
	fprintf(outfile, "%c", 24);
	fprintf(outfile, "%c", 0);

	for (n = 7; n <= 12; n++)
	{
		fprintf(outfile, "%c", headers[n] & 0x000000FF);
		fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
		fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
		fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
	}

	//
	// Headers done, now write the data...
	//

	for (y = HEIGHT - 1; y >= 0; y--)     // BMP image format is written from bottom to top...
	{

		for (x = 0; x <= WIDTH - 1; x++)
		{
			mandelbrot(outfile, x, y);
		}
		if (extrabytes)      // See above - BMP lines must be of lengths divisible by 4.
		{
			for (n = 1; n <= extrabytes; n++)
			{
				fprintf(outfile, "%c", 0);
			}
		}

	}

	fclose(outfile);
	return;
}