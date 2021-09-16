/****************************************************************************************************************************************************
*
* Copyright (C) 2021 Selim Temizer.
*
* This file is part of PPM.
*
* PPM is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
* as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
* PPM is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License along with PPM. If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************************************************************************************************/




/***************************************************************************************************************************************************/

#ifndef __PPM_H__
#define __PPM_H__

/***************************************************************************************************************************************************/

/* Pixel and Image data types for PPM images */

typedef struct
{
  short int r ;
  short int g ;
  short int b ;
}
PPMPixel ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

typedef struct
{
  short int  width         ;
  short int  height        ;
  short int  maxColorValue ;
  PPMPixel * pixels        ;
}
PPMImage ;

/***************************************************************************************************************************************************/

PPMPixel createPixel ( short int r , short int g , short int b ) ;

PPMPixel getPixel    ( PPMImage image ,                  short int row , short int col ) ;  /* Top row is 0, Leftmost col is 0 */
void     setPixel    ( PPMImage image , PPMPixel pixel , short int row , short int col ) ;  /* Top row is 0, Leftmost col is 0 */

PPMImage createPPM   ( short int width , short int height , short int maxColorValue , PPMPixel backgroundColor ) ;
void     deletePPM   ( PPMImage image )                                                                          ;

PPMImage readPPM     (                  char * fileName ) ;
void     savePPM     ( PPMImage image , char * fileName ) ;

/***************************************************************************************************************************************************/

#endif

/***************************************************************************************************************************************************/
