/****************************************************************************************************************************************************
 *
 * Copyright (C) 2021 Selim Temizer.
 *
 * This file is part of PPM.
 *
 * PPM is free software: you can redistribute it and/or modify it under the
 *terms of the GNU Lesser General Public License as published by the Free
 *Software Foundation, either version 3 of the License, or (at your option) any
 *later version.
 *
 * PPM is distributed in the hope that it will be useful, but WITHOUT ANY
 *WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 *A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more
 *details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 *along with PPM. If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************************************************************************************/

/***************************************************************************************************************************************************/

#include "PPM.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************************************************************************************/

/* Parsing States */

#define SMAGICNUMBER (0)   /* Needs to read magic number "P3"                */
#define SWIDTH (1)         /* Needs to read width                            */
#define SHEIGHT (2)        /* Needs to read height                           */
#define SMAXCOLORVALUE (3) /* Needs to read maxColorValue */
#define SRED (4)           /* Needs to read red   component of current pixel */
#define SGREEN (5)         /* Needs to read green component of current pixel */
#define SBLUE (6)          /* Needs to read blue  component of current pixel */

/***************************************************************************************************************************************************/

PPMPixel createPixel(short int r, short int g, short int b) {
  PPMPixel pixel;

  pixel.r = r;
  pixel.g = g;
  pixel.b = b;

  return pixel;
}

/*=================================================================================================================================================*/

PPMPixel getPixel(PPMImage image, short int row,
                  short int col) /* Top row is 0, Leftmost col is 0 */
{
  return image.pixels[row * image.width + col];
}

/*=================================================================================================================================================*/

void setPixel(PPMImage image, PPMPixel pixel, short int row,
              short int col) /* Top row is 0, Leftmost col is 0 */
{
  image.pixels[row * image.width + col] = pixel;
}

/*=================================================================================================================================================*/

PPMImage createPPM(short int width, short int height, short int maxColorValue,
                   PPMPixel backgroundColor) {
  PPMImage image;
  short int row;
  short int col;

  image.width = width;
  image.height = height;
  image.maxColorValue = maxColorValue;
  image.pixels = (PPMPixel *)malloc(width * height * sizeof(PPMPixel));

  for (row = 0; row < height; row++) {
    for (col = 0; col < width; col++) {
      setPixel(image, backgroundColor, row, col);
    }
  }

  return image;
}

/*=================================================================================================================================================*/

void deletePPM(PPMImage image) {
  if (image.pixels != NULL) {
    free(image.pixels);
  }
}

/*=================================================================================================================================================*/

PPMImage readPPM(char *fileName) {
  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  PPMImage image;
  int currentPixelIndex = 0;
  FILE *file = fopen(fileName, "r");
  int state = SMAGICNUMBER;
  char line[1024];
  char *commentLocation;
  char *cursor;
  int numberOfCharactersRead;
  int lineConsumed;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  while (fgets(line, 1024, file)) {
    /* Remove comment from the line (if any) */

    commentLocation = strchr(line, '#');

    if (commentLocation != NULL) {
      commentLocation[0] = '\n';
      commentLocation[1] = '\0';
    }

    /* Initialize control variables */

    cursor = line;
    numberOfCharactersRead = 0;
    lineConsumed = 0;

    /* Consume line */

    while (!lineConsumed) {
      switch (state) {
        /*-----------------------------------------------------------------------------------------------------------------------------------------*/

      case SMAGICNUMBER:
        if (sscanf(cursor, " P3%n", &numberOfCharactersRead) >= 0) {
          state = SWIDTH;
          cursor += numberOfCharactersRead;
        } else {
          lineConsumed = 1;
          break;
        }

        /*-----------------------------------------------------------------------------------------------------------------------------------------*/

      case SWIDTH:
        if (sscanf(cursor, "%hi%n", &(image.width), &numberOfCharactersRead) >
            0) {
          state = SHEIGHT;
          cursor += numberOfCharactersRead;
        } else {
          lineConsumed = 1;
          break;
        }

        /*-----------------------------------------------------------------------------------------------------------------------------------------*/

      case SHEIGHT:
        if (sscanf(cursor, "%hi%n", &(image.height), &numberOfCharactersRead) >
            0) {
          state = SMAXCOLORVALUE;
          cursor += numberOfCharactersRead;

          image.pixels =
              (PPMPixel *)malloc(image.width * image.height * sizeof(PPMPixel));
        } else {
          lineConsumed = 1;
          break;
        }

        /*-----------------------------------------------------------------------------------------------------------------------------------------*/

      case SMAXCOLORVALUE:
        if (sscanf(cursor, "%hi%n", &(image.maxColorValue),
                   &numberOfCharactersRead) > 0) {
          state = SRED;
          cursor += numberOfCharactersRead;
        } else {
          lineConsumed = 1;
          break;
        }

        /*-----------------------------------------------------------------------------------------------------------------------------------------*/

      case SRED:
        if (sscanf(cursor, "%hi%n", &(image.pixels[currentPixelIndex].r),
                   &numberOfCharactersRead) > 0) {
          state = SGREEN;
          cursor += numberOfCharactersRead;
        } else {
          lineConsumed = 1;
          break;
        }

        /*-----------------------------------------------------------------------------------------------------------------------------------------*/

      case SGREEN:
        if (sscanf(cursor, "%hi%n", &(image.pixels[currentPixelIndex].g),
                   &numberOfCharactersRead) > 0) {
          state = SBLUE;
          cursor += numberOfCharactersRead;
        } else {
          lineConsumed = 1;
          break;
        }

        /*-----------------------------------------------------------------------------------------------------------------------------------------*/

      case SBLUE:
        if (sscanf(cursor, "%hi%n", &(image.pixels[currentPixelIndex].b),
                   &numberOfCharactersRead) > 0) {
          state = SRED;
          cursor += numberOfCharactersRead;

          currentPixelIndex++;
        } else {
          lineConsumed = 1;
          break;
        }

        /*-----------------------------------------------------------------------------------------------------------------------------------------*/
      }
    }
  }

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/

  fclose(file);

  return image;

  /*-----------------------------------------------------------------------------------------------------------------------------------------------*/
}

/*=================================================================================================================================================*/

void savePPM(PPMImage image, char *fileName) {
  FILE *file = fopen(fileName, "w");
  // 1. magic number
  fprintf(file, "P3\n");
  // 2. width and height
  fprintf(file, "%d %d\n", image.width, image.height);
  // 3. max color value
  fprintf(file, "%d\n", image.maxColorValue);
  // 4. pixels, each row on new line
  for (int i = 0; i < image.height; i++) {
    for (int j = 0; j < image.width; j++) {
      PPMPixel pixel = image.pixels[i*image.width +j];
      fprintf(file, "%d %d %d ", pixel.r, pixel.g, pixel.b);
    }
    fprintf(file, "\n");
  }
  /* TODO */
}

/***************************************************************************************************************************************************/
