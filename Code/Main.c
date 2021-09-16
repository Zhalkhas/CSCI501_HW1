/****************************************************************************************************************************************************
*
* Copyright (C) 2021 Selim Temizer.
*
* This program is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
* as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License along with this program. If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************************************************************************************************/




/***************************************************************************************************************************************************/

#include "PPM.h"
#include "ColorSpace.h"
#include "AffineTransformation.h"
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

/***************************************************************************************************************************************************/

#if    defined(_WIN16) || defined(_WIN32) || defined(_WIN64)
       #define OS ( "Windows" )  /* This is a Windows environment.                            */
#elif  defined(__linux__)
       #define OS ( "Linux"   )  /* This is a Linux environment (any GNU/Linux distribution). */
#elif  defined(__APPLE__)
       #define OS ( "MacOSX"  )  /* This is a Mac OS X environment.                           */
#endif

/***************************************************************************************************************************************************/

#define READSTRINGINDOUBLEQUOTES " \"%[^\"]\""
#define SCWS                     skipCommentsAndWhiteSpace( file , '#' )

/***************************************************************************************************************************************************/

void skipCommentsAndWhiteSpace ( FILE * file , char  commentStarter )
{
  int c ;

  while ( 1 )
  {
    c = fgetc( file ) ;

    if      ( isspace( c )        )  {                                    /* White space: Do nothing, just skip    */ }
    else if ( c == commentStarter )  { while ( fgetc( file ) != '\n' ) ;  /* Skip until end of line (inclusive)    */ }
    else                             { ungetc( c , file ) ;  break ;      /* Push the character back and exit loop */ }
  }
}

/*=================================================================================================================================================*/

void modifyFilenameAccordingToOS ( char * filename )
{
  char fromChar , toChar ;

  if   ( strcmp( OS , "Windows" ) == 0 )  { fromChar = '/'  ;  toChar = '\\' ; }
  else /* Assumption : Linux */           { fromChar = '\\' ;  toChar =  '/' ; }

  while ( *filename )
  {
    if ( *filename == fromChar )  { *filename = toChar ; }

    filename ++ ;
  }
}

/*=================================================================================================================================================*/

void displayImage ( char * filename )
{
  char displayImageSystemCommand[1024] = {0} ;

  if   ( strcmp( OS , "Windows" ) == 0 )  { sprintf( displayImageSystemCommand , "CMD /C START %s" , filename ) ; }
  else /* Assumption : Linux */           { sprintf( displayImageSystemCommand , "xdg-open %s &"   , filename ) ; }

  if ( system( displayImageSystemCommand ) ) ;  /* "if" statement is used to eliminate warning about unused return value of "system" call */
}

/*=================================================================================================================================================*/

PPMPixel interpolate
(
  PPMPixel  pixel1 , short int maxColorValue1 , double weight1 ,
  PPMPixel  pixel2 , short int maxColorValue2 , double weight2 ,
  short int desiredMaxColorValue
)
{
  HsvColor * pHsv1 = Hsv_CreateFromRgbF( (double) pixel1.r / maxColorValue1 ,
                                         (double) pixel1.g / maxColorValue1 ,
                                         (double) pixel1.b / maxColorValue1 ) ;

  HsvColor * pHsv2 = Hsv_CreateFromRgbF( (double) pixel2.r / maxColorValue2 ,
                                         (double) pixel2.g / maxColorValue2 ,
                                         (double) pixel2.b / maxColorValue2 ) ;

  double weightSum = weight1 + weight2 ;

  double h = (weight1 / weightSum) * pHsv1->H + (weight2 / weightSum) * pHsv2->H ;
  double s = (weight1 / weightSum) * pHsv1->S + (weight2 / weightSum) * pHsv2->S ;
  double v = (weight1 / weightSum) * pHsv1->V + (weight2 / weightSum) * pHsv2->V ;

  RgbFColor * pRgbF = RgbF_CreateFromHsv( h , s , v ) ;

  PPMPixel result ;

  result.r = (short int) ( pRgbF->R * desiredMaxColorValue ) ;
  result.g = (short int) ( pRgbF->G * desiredMaxColorValue ) ;
  result.b = (short int) ( pRgbF->B * desiredMaxColorValue ) ;

  free( pHsv1 ) ;
  free( pHsv2 ) ;
  free( pRgbF ) ;

  return result ;
}

/*=================================================================================================================================================*/

void primitiveCopy ( PPMImage source , PPMImage target , XMatrix matrix )
{
  /* TODO */
}

/*=================================================================================================================================================*/

void advancedCopy ( PPMImage source , PPMImage target , XMatrix matrix )
{
  /* TODO (Bonus) */
}

/*=================================================================================================================================================*/

void processTasksFile ( char * filename )
{
  FILE *   file                  = fopen( filename , "r" ) ;
  char     command        [1024]                           ;
  char     inputFileName  [1024]                           ;
  char     outputFileName [1024]                           ;
  PPMImage inputImage            = {0}                     ;
  PPMImage outputImage           = {0}                     ;
  XMatrix  matrix                = xMatrixIdentity()       ;  /* Current (running) transformation matrix */

  do
  {
    /* Read command */

    SCWS ;    if ( fscanf( file , " %s" , command ) != 1 )  { break ; }

    /* Parse and execute command */

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    if      ( strcmp( command , "Output"    ) == 0 )
    {
      short int width , height , maxColorValue , red , green , blue ;

      SCWS ;    fscanf( file , READSTRINGINDOUBLEQUOTES ,  outputFileName ) ;    modifyFilenameAccordingToOS( outputFileName ) ;
      SCWS ;    fscanf( file , " %hi"                   , &width          ) ;
      SCWS ;    fscanf( file , " %hi"                   , &height         ) ;
      SCWS ;    fscanf( file , " %hi"                   , &maxColorValue  ) ;
      SCWS ;    fscanf( file , " %hi"                   , &red            ) ;
      SCWS ;    fscanf( file , " %hi"                   , &green          ) ;
      SCWS ;    fscanf( file , " %hi"                   , &blue           ) ;

      deletePPM( outputImage ) ;    outputImage = createPPM( width , height , maxColorValue , createPixel( red , green , blue ) ) ;
    }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    else if ( strcmp( command , "Read"      ) == 0 )
    {
      SCWS ;    fscanf( file , READSTRINGINDOUBLEQUOTES , inputFileName )  ;    modifyFilenameAccordingToOS( inputFileName ) ;

      deletePPM( inputImage ) ;    inputImage = readPPM( inputFileName ) ;
    }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    else if ( strcmp( command , "Copy"      ) == 0 )
    {
         primitiveCopy( inputImage , outputImage , matrix ) ;
      /* advancedCopy ( inputImage , outputImage , matrix ) ; */
    }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    else if ( strcmp( command , "Translate" ) == 0 )
    {
      double tx , ty ;

      SCWS ;    fscanf( file , " %lf" , &tx ) ;
      SCWS ;    fscanf( file , " %lf" , &ty ) ;

      matrix = xMultiplyMM( matrix , xMatrixTranslate( tx , ty ) ) ;
    }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    else if ( strcmp( command , "Rotate"    ) == 0 )
    {
      double thetaDegreesClockwise ;

      SCWS ;    fscanf( file , " %lf" , &thetaDegreesClockwise ) ;

      matrix = xMultiplyMM( matrix , xMatrixRotate( thetaDegreesClockwise ) ) ;
    }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    else if ( strcmp( command , "Scale"     ) == 0 )
    {
      double sx , sy ;

      SCWS ;    fscanf( file , " %lf" , &sx ) ;
      SCWS ;    fscanf( file , " %lf" , &sy ) ;

      matrix = xMultiplyMM( matrix , xMatrixScale( sx , sy ) ) ;
    }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    else if ( strcmp( command , "Shear"     ) == 0 )
    {
      double sxy , syx ;

      SCWS ;    fscanf( file , " %lf" , &sxy ) ;
      SCWS ;    fscanf( file , " %lf" , &syx ) ;

      matrix = xMultiplyMM( matrix , xMatrixShear( sxy , syx ) ) ;
    }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    else if ( strcmp( command , "Reset"     ) == 0 )
    {
      matrix = xMatrixIdentity() ;
    }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/

    else
    {
      printf( "Skipping invalid command: %s\n" , command ) ;
    }

    /*---------------------------------------------------------------------------------------------------------------------------------------------*/
  }
  while ( 1 ) ;  /* Infinite do-while loop */

  fclose( file ) ;

  savePPM     ( outputImage , outputFileName ) ;
  displayImage(               outputFileName ) ;

  deletePPM(  inputImage ) ;
  deletePPM( outputImage ) ;
}

/*=================================================================================================================================================*/

int main ( int argc , char * argv[] )
{
  if ( argc < 2 )  { printf( "\nUsage: %s <TPC Script File>\n\n" , argv[0] ) ;    return 0 ; }

  processTasksFile( argv[1] ) ;

  return 0 ;
}

/***************************************************************************************************************************************************/
