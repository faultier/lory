/*
 * loryconv
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 Taro Sako

 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <jpeglib.h>

#include <lory/lory.h>

typedef struct jpeg_decompress_struct jdec;
typedef struct jpeg_compress_struct jcomp;
typedef struct jpeg_error_mgr jerr;

void usage(char *);

int main(int argc, char **argv)
{
    double hue = -1.0, range = 60.0;
    char *inname = NULL, *outname = "lory-out.jpg";

    int opt;
    while ((opt = getopt(argc, argv, "h:r:o:")) != -1)
    {
        switch (opt)
        {
            case 'h':
                hue = atof(optarg);
                break;
            case 'r':
                range = atof(optarg);
                break;
            case 'o':
                outname = optarg;
                break;
            case '?':
                fprintf(stderr, "Unknown or required argument option -%c\n", optopt);
                usage(argv[0]);
                return 1;
        }
    }

    if (hue < 0.0 || hue > 360.0) {
        fprintf(stderr, "hue should be in range of 0 to 360\n");
        usage(argv[0]);
        return 1;
    }

    if (range < 0.0 || range > 180.0) {
        fprintf(stderr, "range should be in range of 0 to 180.\n");
        usage(argv[0]);
        return 1;
    }

    if (optind >= argc) {
        fprintf(stderr, "required input file path\n");
        usage(argv[0]);
        return 1;
    }

    inname = argv[optind];

    // decompress
    {
        FILE *infile;
        if ((infile = fopen(inname, "rb")) == NULL) {
            fprintf(stderr, "can't open %s\n", inname);
            return 1;
        }
        jerr err;
        jdec in;
        in.err = jpeg_std_error(&err);
        jpeg_create_decompress(&in);
        jpeg_stdio_src(&in, infile);
        jpeg_read_header(&in, TRUE);
        jpeg_start_decompress(&in);

        if (in.out_color_space != JCS_RGB || in.output_components != 3)
        {
            fprintf(stderr, "input file is not RGB color image.\n");
            return 1;
        }

        // compress
        {
            FILE *outfile;
            if ((outfile = fopen(outname, "wb")) == NULL) {
                fprintf(stderr, "can't open %s\n", outname);
                return 1;
            }
            jerr err;
            jcomp out;
            out.err = jpeg_std_error(&err);
            jpeg_create_compress(&out);
            jpeg_stdio_dest(&out, outfile);
            out.image_width = in.output_width;
            out.image_height = in.output_height;
            out.input_components = 3;
            out.in_color_space = JCS_RGB;
            jpeg_set_defaults(&out);
            jpeg_set_quality(&out, 100, TRUE);
            jpeg_start_compress(&out, TRUE);

            // convert
            {
                JSAMPROW buffer = (JSAMPROW)calloc(sizeof(JSAMPLE), in.output_width * in.output_components);
                while (in.output_scanline < in.output_height)
                {
                    jpeg_read_scanlines(&in, &buffer, 1);
                    lory_convert_rgb_array(buffer, in.output_width, hue, range);
                    jpeg_write_scanlines(&out, &buffer, 1);
                }
                free(buffer);
            }

            jpeg_finish_compress(&out);
            jpeg_destroy_compress(&out);
            fclose(outfile);
        }

        jpeg_finish_decompress(&in);
        jpeg_destroy_decompress(&in);
        fclose(infile);
    }

    return 0;
}

void usage(char *program)
{
    fprintf(stderr, "Usage: %s -h hue [-r range] [-o output] input\n", program);
}
