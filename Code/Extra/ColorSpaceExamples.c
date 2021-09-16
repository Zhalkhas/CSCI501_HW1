/***************************************************************************************************************************************************/
/*
 *  From:  http://dystopiancode.blogspot.com/2012/02/defining-color-space-structures.html
 *
 *  ------------------------------
 *
 *  ColorSpaceExamples.c
 *
 *  Created on: Aug 12, 2012
 *  Author    : bogdan
 *
 *  ------------------------------
 *
 *  Beautified and fixed (some minor typos)
 *  by Selim Temizer
 *  September, 2021
 */
/***************************************************************************************************************************************************/

#include <stdio.h>
#include "ColorSpace.h"

/***************************************************************************************************************************************************/

void HsvRgbExample( void ) ;
void HsiRgbExample( void ) ;
void HslRgbExample( void ) ;
void YiqRgbExample( void ) ;
void YuvRgbExample( void ) ;

/***************************************************************************************************************************************************/

int main ( int argc , char** argv )
{
  HsvRgbExample() ;  printf( "\n" ) ;
  HsiRgbExample() ;  printf( "\n" ) ;
  HslRgbExample() ;  printf( "\n" ) ;
  YiqRgbExample() ;  printf( "\n" ) ;
  YuvRgbExample() ;  printf( "\n" ) ;

  return 0 ;
}

/***************************************************************************************************************************************************/

void HsvRgbExample ( void )
{
  HsvColor  * hsv  = NULL ;
  RgbFColor * rgbF = NULL ;
  RgbIColor * rgbI = NULL ;

  /* HSV to RGB */
  hsv  = Hsv_Create( 240.5 , 0.316 , 0.721 ) ;

  rgbF = RgbF_CreateFromHsv     ( hsv ->H , hsv ->S , hsv ->V ) ;
  rgbI = RgbI_CreateFromRealForm( rgbF->R , rgbF->G , rgbF->B ) ;

  printf( "HSV  : %f %f %f\n" , hsv ->H , hsv ->S , hsv ->V ) ;
  printf( "RGBf : %f %f %f\n" , rgbF->R , rgbF->G , rgbF->B ) ;
  printf( "RGBi : %d %d %d\n" , rgbI->R , rgbI->G , rgbI->B ) ;

  free( hsv  ) ;
  free( rgbF ) ;
  free( rgbI ) ;

  /* RGB to HSV */
  rgbI = RgbI_Create( 126U , 126U , 184U ) ;

  rgbF = RgbF_CreateFromIntegerForm( rgbI->R , rgbI->G , rgbI->B ) ;
  hsv  = Hsv_CreateFromRgbF        ( rgbF->R , rgbF->G , rgbF->B ) ;

  printf( "HSV  : %f %f %f\n" , hsv ->H , hsv ->S , hsv ->V ) ;
  printf( "RGBf : %f %f %f\n" , rgbF->R , rgbF->G , rgbF->B ) ;
  printf( "RGBi : %d %d %d\n" , rgbI->R , rgbI->G , rgbI->B ) ;

  free( hsv  ) ;
  free( rgbF ) ;
  free( rgbI ) ;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

void HsiRgbExample ( void )
{
  HsiColor  * hsi  = NULL ;
  RgbFColor * rgbF = NULL ;
  RgbIColor * rgbI = NULL ;

  /* HSI to RGB */
  hsi = Hsi_Create( 30.0 , 0.3 , 0.2 ) ;

  rgbF = RgbF_CreateFromHsi     ( hsi ->H , hsi ->S , hsi ->I ) ;
  rgbI = RgbI_CreateFromRealForm( rgbF->R , rgbF->G , rgbF->B ) ;

  printf( "HSI  : %f %f %f\n" , hsi ->H , hsi ->S , hsi ->I ) ;
  printf( "RGBf : %f %f %f\n" , rgbF->R , rgbF->G , rgbF->B ) ;
  printf( "RGBi : %d %d %d\n" , rgbI->R , rgbI->G , rgbI->B ) ;

  free( hsi  ) ;
  free( rgbF ) ;
  free( rgbI ) ;

  /* RGB to HSI */
  rgbI = RgbI_Create( 25U , 170U , 59U ) ;

  rgbF = RgbF_CreateFromIntegerForm( rgbI->R , rgbI->G , rgbI->B ) ;
  hsi  = Hsi_CreateFromRgbF        ( rgbF->R , rgbF->G , rgbF->B ) ;

  printf( "HSI  : %f %f %f\n" , hsi ->H , hsi ->S , hsi ->I ) ;
  printf( "RGBf : %f %f %f\n" , rgbF->R , rgbF->G , rgbF->B ) ;
  printf( "RGBi : %d %d %d\n" , rgbI->R , rgbI->G , rgbI->B ) ;

  free( hsi  ) ;
  free( rgbF ) ;
  free( rgbI ) ;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

void HslRgbExample ( void )
{
  HslColor  * hsl  = NULL ;
  RgbFColor * rgbF = NULL ;
  RgbIColor * rgbI = NULL ;

  /* HSL to RGB */
  hsl = Hsl_Create( 84.0 , 1.0 , 0.4 ) ;

  rgbF = RgbF_CreateFromHsl     ( hsl ->H , hsl ->S , hsl ->L ) ;
  rgbI = RgbI_CreateFromRealForm( rgbF->R , rgbF->G , rgbF->B ) ;

  printf( "HSL  : %f %f %f\n" , hsl ->H , hsl ->S , hsl ->L ) ;
  printf( "RGBf : %f %f %f\n" , rgbF->R , rgbF->G , rgbF->B ) ;
  printf( "RGBi : %d %d %d\n" , rgbI->R , rgbI->G , rgbI->B ) ;

  free( hsl  ) ;
  free( rgbF ) ;
  free( rgbI ) ;

  /* RGB to HSL */
  rgbI = RgbI_Create( 122U , 204U , 0U ) ;

  rgbF = RgbF_CreateFromIntegerForm( rgbI->R , rgbI->G , rgbI->B ) ;
  hsl  = Hsl_CreateFromRgbF        ( rgbF->R , rgbF->G , rgbF->B ) ;

  printf( "HSL  : %f %f %f\n" , hsl ->H , hsl ->S , hsl ->L ) ;
  printf( "RGBf : %f %f %f\n" , rgbF->R , rgbF->G , rgbF->B ) ;
  printf( "RGBi : %d %d %d\n" , rgbI->R , rgbI->G , rgbI->B ) ;

  free( hsl  ) ;
  free( rgbF ) ;
  free( rgbI ) ;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

void YiqRgbExample ( void )
{
  YiqColor  * yiq  = NULL ;
  RgbFColor * rgbF = NULL ;
  RgbIColor * rgbI = NULL ;

  /* YIQ to RGB */
  yiq = Yiq_Create( 0.4 , 0.1 , -0.11 ) ;

  rgbF = RgbF_CreateFromYiq     ( yiq ->Y , yiq ->I , yiq ->Q ) ;
  rgbI = RgbI_CreateFromRealForm( rgbF->R , rgbF->G , rgbF->B ) ;

  printf( "YIQ  : %f %f %f\n" , yiq ->Y , yiq ->I , yiq ->Q ) ;
  printf( "RGBf : %f %f %f\n" , rgbF->R , rgbF->G , rgbF->B ) ;
  printf( "RGBi : %d %d %d\n" , rgbI->R , rgbI->G , rgbI->B ) ;

  free( yiq  ) ;
  free( rgbF ) ;
  free( rgbI ) ;

  /* RGB to YIQ */
  rgbI = RgbI_Create( 109U , 113U , 26U ) ;

  rgbF = RgbF_CreateFromIntegerForm( rgbI->R , rgbI->G , rgbI->B ) ;
  yiq  = Yiq_CreateFromRgbF        ( rgbF->R , rgbF->G , rgbF->B ) ;

  printf( "YIQ  : %f %f %f\n" , yiq ->Y , yiq ->I , yiq ->Q ) ;
  printf( "RGBf : %f %f %f\n" , rgbF->R , rgbF->G , rgbF->B ) ;
  printf( "RGBi : %d %d %d\n" , rgbI->R , rgbI->G , rgbI->B ) ;

  free( yiq  ) ;
  free( rgbF ) ;
  free( rgbI ) ;
}

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

void YuvRgbExample ( void )
{
  YuvColor  * yuv  = NULL ;
  RgbFColor * rgbF = NULL ;
  RgbIColor * rgbI = NULL ;

  /* YUV to RGB */
  yuv = Yuv_Create( 0.4 , 0.1 , -0.11 ) ;

  rgbF = RgbF_CreateFromYuv     ( yuv ->Y , yuv ->U , yuv ->V ) ;
  rgbI = RgbI_CreateFromRealForm( rgbF->R , rgbF->G , rgbF->B ) ;

  printf( "YUV  : %f %f %f\n" , yuv ->Y , yuv ->U , yuv ->V ) ;
  printf( "RGBf : %f %f %f\n" , rgbF->R , rgbF->G , rgbF->B ) ;
  printf( "RGBi : %d %d %d\n" , rgbI->R , rgbI->G , rgbI->B ) ;

  free( yuv  ) ;
  free( rgbF ) ;
  free( rgbI ) ;

  /* RGB to YUV */
  rgbI = RgbI_Create( 70U , 108U , 154U ) ;

  rgbF = RgbF_CreateFromIntegerForm( rgbI->R , rgbI->G , rgbI->B ) ;
  yuv  = Yuv_CreateFromRgbF        ( rgbF->R , rgbF->G , rgbF->B ) ;

  printf( "YUV  : %f %f %f\n" , yuv ->Y , yuv ->U , yuv ->V ) ;
  printf( "RGBf : %f %f %f\n" , rgbF->R , rgbF->G , rgbF->B ) ;
  printf( "RGBi : %d %d %d\n" , rgbI->R , rgbI->G , rgbI->B ) ;

  free( yuv  ) ;
  free( rgbF ) ;
  free( rgbI ) ;
}

/***************************************************************************************************************************************************/
