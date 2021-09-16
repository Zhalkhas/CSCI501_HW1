/***************************************************************************************************************************************************/
/*
 *  From:  http://dystopiancode.blogspot.com/2012/02/defining-color-space-structures.html
 *
 *  ------------------------------
 *
 *  ColorSpace.h
 *
 *  Created on: Aug 11, 2012
 *  Author    : bogdan
 *
 *  ------------------------------
 *
 *  Beautified and fixed (some errors)
 *  by Selim Temizer
 *  September, 2021
 *
 *  ------------------------------
 *
 *  NOTE: The following conversions may further need to be verified for correctness!
 *        See the examples (they output suspicious values).
 *
 *  HSI <-> RGB
 *  YIQ <-> RGB
 *  YUV <-> RGB
 */
/***************************************************************************************************************************************************/
/* Summary of the library

Types:
------

RgbFColor
RgbIColor
HsvColor
HsiColor
HslColor
YiqColor
YuvColor

Functions:
----------

bool           RealIsWithinBounds     ( double  value , double  lowerLimit , double  upperLimit ) ;
bool        IntegerIsWithinBounds     ( uint8_t value , uint8_t lowerLimit , uint8_t upperLimit ) ;

double      Double_GetMinimum         ( double  r , double  g , double  b ) ;
double      Double_GetMaximum         ( double  r , double  g , double  b ) ;

bool        RgbF_IsValid              ( double  r , double  g , double  b ) ;
bool        RgbI_IsValid              ( uint8_t r , uint8_t g , uint8_t b ) ;
bool         Hsv_IsValid              ( double  h , double  s , double  v ) ;
bool         Hsi_IsValid              ( double  h , double  s , double  i ) ;
bool         Hsl_IsValid              ( double  h , double  s , double  l ) ;
bool         Yiq_IsValid              ( double  y , double  i , double  q ) ;
bool         Yuv_IsValid              ( double  y , double  u , double  v ) ;

RgbFColor * RgbF_Create               ( double  r , double  g , double  b ) ;
RgbIColor * RgbI_Create               ( uint8_t r , uint8_t g , uint8_t b ) ;
HsvColor  *  Hsv_Create               ( double  h , double  s , double  v ) ;
HsiColor  *  Hsi_Create               ( double  h , double  s , double  i ) ;
HslColor  *  Hsl_Create               ( double  h , double  s , double  l ) ;
YiqColor  *  Yiq_Create               ( double  y , double  i , double  q ) ;
YuvColor  *  Yuv_Create               ( double  y , double  u , double  v ) ;

RgbFColor * RgbF_CreateFromIntegerForm( uint8_t r , uint8_t g , uint8_t b ) ;
RgbFColor * RgbF_CreateFromHsv        ( double  h , double  s , double  v ) ;
RgbFColor * RgbF_CreateFromHsi        ( double  h , double  s , double  i ) ;
RgbFColor * RgbF_CreateFromHsl        ( double  h , double  s , double  l ) ;
RgbFColor * RgbF_CreateFromYiq        ( double  y , double  i , double  q ) ;
RgbFColor * RgbF_CreateFromYuv        ( double  y , double  u , double  v ) ;

RgbIColor * RgbI_CreateFromRealForm   ( double  r , double  g , double  b ) ;
HsvColor  *  Hsv_CreateFromRgbF       ( double  r , double  g , double  b ) ;
HsiColor  *  Hsi_CreateFromRgbF       ( double  r , double  g , double  b ) ;
HslColor  *  Hsl_CreateFromRgbF       ( double  r , double  g , double  b ) ;
YiqColor  *  Yiq_CreateFromRgbF       ( double  r , double  g , double  b ) ;
YuvColor  *  Yuv_CreateFromRgbF       ( double  r , double  g , double  b ) ;

*/
/***************************************************************************************************************************************************/

#ifndef __COLORSPACE_H__
#define __COLORSPACE_H__

/***************************************************************************************************************************************************/

#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/***************************************************************************************************************************************************/

#define   PER_LOWER_LIMIT (   0.0    )  /* The lower limit for R, G, B (real version), S, I */
#define   PER_UPPER_LIMIT (   1.0    )  /* The upper limit for R, G, B (real version), S, I */
#define   HUE_LOWER_LIMIT (   0.0    )  /* The lower limit for H                            */
#define   HUE_UPPER_LIMIT ( 360.0    )  /* The upper limit for H                            */
#define  RGBI_LOWER_LIMIT (   0U     )  /* The lower limit for R, G, B (integer version)    */
#define  RGBI_UPPER_LIMIT ( 255U     )  /* The upper limit for R, G, B (integer version)    */
#define YIQ_I_LOWER_LIMIT (  -0.5957 )  /* The lower limit for I in YIQ                     */
#define YIQ_I_UPPER_LIMIT (   0.5957 )  /* The upper limit for I in YIQ                     */
#define YIQ_Q_LOWER_LIMIT (  -0.5226 )  /* The lower limit for Q in YIQ                     */
#define YIQ_Q_UPPER_LIMIT (   0.5226 )  /* The upper limit for Q in YIQ                     */
#define YUV_U_LOWER_LIMIT (  -0.436  )  /* The lower limit for U in YUV                     */
#define YUV_U_UPPER_LIMIT (   0.436  )  /* The upper limit for U in YUV                     */
#define YUV_V_LOWER_LIMIT (  -0.615  )  /* The lower limit for V in YUV                     */
#define YUV_V_UPPER_LIMIT (   0.615  )  /* The upper limit for V in YUV                     */

/***************************************************************************************************************************************************/

typedef struct
{
  double  R ;  /* Range: [0.0, 1.0] */
  double  G ;  /* Range: [0.0, 1.0] */
  double  B ;  /* Range: [0.0, 1.0] */
} RgbFColor ;

typedef struct
{
  uint8_t R ;  /* Range: [0, 255] */
  uint8_t G ;  /* Range: [0, 255] */
  uint8_t B ;  /* Range: [0, 255] */
} RgbIColor ;

typedef struct
{
  double  H ;  /* Range: [0.0, 360.0] */
  double  S ;  /* Range: [0.0,   1.0] */
  double  V ;  /* Range: [0.0,   1.0] */
} HsvColor  ;

typedef struct
{
  double  H ;  /* Range: [0.0, 360.0] */
  double  S ;  /* Range: [0.0,   1.0] */
  double  I ;  /* Range: [0.0,   1.0] */
} HsiColor  ;

typedef struct
{
  double  H ;  /* Range: [0.0, 360.0] */
  double  S ;  /* Range: [0.0,   1.0] */
  double  L ;  /* Range: [0.0,   1.0] */
} HslColor  ;

typedef struct
{
  double  Y ;  /* Range: [ 0.0   , 1.0   ] */
  double  I ;  /* Range: [-0.5957, 0.5957] */
  double  Q ;  /* Range: [-0.5226, 0.5226] */
} YiqColor  ;

typedef struct
{
  double  Y ;  /* Range: [ 0.0  , 1.0  ] */
  double  U ;  /* Range: [-0.436, 0.436] */
  double  V ;  /* Range: [-0.615, 0.615] */
} YuvColor  ;

/***************************************************************************************************************************************************/

/*
 * Description:
 *  Checks if a value is within a specified interval
 *
 * Parameters:
 *  value      - the value who is checked
 *  lowerLimit - the lower limit of the interval
 *  upperLimit - the upper limit of the interval
 *
 * Returns:
 *  true  if the value is within the interval
 *  false if the value is not within the interval
 */
bool RealIsWithinBounds( double value , double lowerLimit , double upperLimit ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Checks if a value is within a specified interval
 *
 * Parameters:
 *  value      - the value who is checked
 *  lowerLimit - the lower limit of the interval
 *  upperLimit - the upper limit of the interval
 *
 * Returns:
 *  true  if the value is within the interval
 *  false if the value is not within the interval
 */
bool IntegerIsWithinBounds( uint8_t value , uint8_t lowerLimit , uint8_t upperLimit ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Returns the smallest of the three parameters
 *
 * Parameters
 *  r,g,b - 3 real numbers
 *
 * Returns
 *  The smallest real number from the set {r,g,b}
 */
double Double_GetMinimum( double r , double g , double b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Returns the largest of the three parameters
 *
 * Parameters
 *  r,g,b - 3 real numbers
 *
 * Returns
 *  The largest real number from the set {r,g,b}
 */
double Double_GetMaximum( double r , double g , double b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Checks if the RGB components are valid
 *
 * Parameters:
 *  r,g,b - the components of an RGB model expressed as real numbers
 *
 * Returns:
 *  true  if the values are correct
 *  false if the values are incorrect
 */
bool RgbF_IsValid( double r , double g , double b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Checks if the RGB components are valid
 *
 * Parameters:
 *  r,g,b - the components of an RGB model expressed as natural numbers
 *
 * Returns:
 *  true  if the values are correct
 *  false if the values are incorrect
 */
bool RgbI_IsValid( uint8_t r , uint8_t g , uint8_t b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Checks if the HSV components are valid
 *
 * Parameters:
 *  h,s,v - the components of an HSV model expressed as real numbers
 *
 * Returns:
 *  true  if the values are correct
 *  false if the values are incorrect
 */
bool Hsv_IsValid( double h , double s , double v ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Checks if the HSI components are valid
 *
 * Parameters:
 *  h,s,i - the components of an HSI model expressed as real numbers
 *
 * Returns:
 *  true  if the values are correct
 *  false if the values are incorrect
 */
bool Hsi_IsValid( double h , double s , double i ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Checks if the HSL components are valid
 *
 * Parameters:
 *  h,s,l - the components of an HSL model expressed as real numbers
 *
 * Returns:
 *  true  if the values are correct
 *  false if the values are incorrect
 */
bool Hsl_IsValid( double h , double s , double l ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Checks if the YIQ components are valid
 *
 * Parameters:
 *  y,i,q - the components of an YIQ model expressed as real numbers
 *
 * Returns:
 *  true  if the values are correct
 *  false if the values are incorrect
 */
bool Yiq_IsValid( double y , double i , double q ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Checks if the YUV components are valid
 *
 * Parameters:
 *  y,u,v - the components of an YUV model expressed as real numbers
 *
 * Returns:
 *  true  if the values are correct
 *  false if the values are incorrect
 */
bool Yuv_IsValid( double y , double u , double v ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a RgbfColor structure
 *
 * Parameters:
 *  r,g,b - the components of an RGB model expressed as real numbers
 *
 * Returns:
 *  A pointer to the RgbFColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
RgbFColor * RgbF_Create( double r , double g , double b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a RgbIColor structure
 *
 * Parameters:
 *  r,g,b - the components of an RGB model expressed as natural numbers
 *
 * Returns:
 *  A pointer to the RgbIColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
RgbIColor * RgbI_Create( uint8_t r , uint8_t g , uint8_t b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a HsvColor structure
 *
 * Parameters:
 *  h,s,v - the components of an HSV model expressed as real numbers
 *
 * Returns:
 *  A pointer to the HsvColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
HsvColor * Hsv_Create( double h , double s , double v ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a HsiColor structure
 *
 * Parameters:
 *  h,s,i - the components of an HSI model expressed as real numbers
 *
 * Returns:
 *  A pointer to the HsiColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
HsiColor * Hsi_Create( double h , double s , double i ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a HslColor structure
 *
 * Parameters:
 *  h,s,l - the components of an HSL model expressed as real numbers
 *
 * Returns:
 *  A pointer to the HslColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
HslColor * Hsl_Create( double h , double s , double l ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a YiqColor structure
 *
 * Parameters:
 *  y,i,q - the components of an YIQ model expressed as real numbers
 *
 * Returns:
 *  A pointer to the YiqColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
YiqColor * Yiq_Create( double y , double i , double q ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a YuvColor structure
 *
 * Parameters:
 *  y,u,v - the components of an YUV model expressed as real numbers
 *
 * Returns:
 *  A pointer to the YuvColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
YuvColor * Yuv_Create( double y , double u , double v ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a RgbFColor structure from RGB components
 *
 * Parameters:
 *  r,g,b - the components of an RGB model expressed as natural numbers
 *
 * Returns:
 *  A pointer to the RgbFColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
RgbFColor * RgbF_CreateFromIntegerForm( uint8_t r , uint8_t g , uint8_t b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a RgbFColor structure from HSV components
 *
 * Parameters:
 *  h,s,v - the components of an HSV model expressed as real numbers
 *
 * Returns:
 *  A pointer to the RgbFColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
RgbFColor * RgbF_CreateFromHsv( double h , double s , double v ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a RgbFColor structure from HSI components
 *
 * Parameters:
 *  h,s,i - the components of an HSI model expressed as real numbers
 *
 * Returns:
 *  A pointer to the RgbFColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
RgbFColor * RgbF_CreateFromHsi( double h , double s , double i ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a RgbFColor structure from HSL components
 *
 * Parameters:
 *  h,s,l - the components of an HSL model expressed as real numbers
 *
 * Returns:
 *  A pointer to the RgbFColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
RgbFColor * RgbF_CreateFromHsl( double h , double s , double l ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a RgbFColor structure from YIQ components
 *
 * Parameters:
 *  y,i,q - the components of an YIQ model expressed as real numbers
 *
 * Returns:
 *  A pointer to the RgbFColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
RgbFColor * RgbF_CreateFromYiq( double y , double i , double q ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a RgbFColor structure from YUV components
 *
 * Parameters:
 *  y,u,v - the components of an YUV model expressed as real numbers
 *
 * Returns:
 *  A pointer to the RgbFColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
RgbFColor * RgbF_CreateFromYuv( double y , double u , double v ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * Description:
 *  Creates a RgbIColor structure from RGB components
 *
 * Parameters:
 *  r,g,b - the components of an RGB model expressed as real numbers
 *
 * Returns:
 *  A pointer to the RgbIColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
RgbIColor * RgbI_CreateFromRealForm( double r , double g , double b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Description:
 *  Creates a HsvColor structure from RGB components
 *
 * Parameters:
 *  r,g,b - the components of an RGB model expressed as real numbers
 *
 * Returns:
 *  A pointer to the HsvColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
HsvColor * Hsv_CreateFromRgbF( double r , double g , double b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Description:
 *  Creates a HsiColor structure from RGB components
 *
 * Parameters:
 *  r,g,b - the components of an RGB model expressed as real numbers
 *
 * Returns:
 *  A pointer to the HsiColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
HsiColor * Hsi_CreateFromRgbF( double r , double g , double b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Description:
 *  Creates a HslColor structure from RGB components
 *
 * Parameters:
 *  r,g,b - the components of an RGB model expressed as real numbers
 *
 * Returns:
 *  A pointer to the HslColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
HslColor * Hsl_CreateFromRgbF( double r , double g , double b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Description:
 *  Creates a YiqColor structure from RGB components
 *
 * Parameters:
 *  r,g,b - the components of an RGB model expressed as real numbers
 *
 * Returns:
 *  A pointer to the YiqColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
YiqColor * Yiq_CreateFromRgbF( double r , double g , double b ) ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Description:
 *  Creates a YuvColor structure from RGB components
 *
 * Parameters:
 *  r,g,b - the components of an RGB model expressed as real numbers
 *
 * Returns:
 *  A pointer to the YuvColor is the parameters are correct.
 *  Otherwise returns NULL.
 */
YuvColor * Yuv_CreateFromRgbF( double r , double g , double b ) ;

/***************************************************************************************************************************************************/

#endif

/***************************************************************************************************************************************************/
