/****************************************************************************************************************************************************
*
* Copyright (C) 2021 Selim Temizer.
*
* This file is part of AffineTransformation.
*
* AffineTransformation is free software: you can redistribute it and/or modify it under the terms of the GNU Lesser General Public License
* as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
*
* AffineTransformation is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
*
* You should have received a copy of the GNU Lesser General Public License along with AffineTransformation.
* If not, see <http://www.gnu.org/licenses/>.
*
****************************************************************************************************************************************************/




/***************************************************************************************************************************************************/

#ifndef __AFFINETRANSFORMATION_H__
#define __AFFINETRANSFORMATION_H__

/***************************************************************************************************************************************************/

/* Vector and Matrix data types for 2D affine transformations */

typedef struct
{
  double data [3][1] ;
}
XVector ;

/*-------------------------------------------------------------------------------------------------------------------------------------------------*/

typedef struct
{
  double data [3][3] ;
}
XMatrix ;

/***************************************************************************************************************************************************/

XVector xVectorZero      ( void                                     ) ;
XVector xVector          ( double x , double y                      ) ;
double  xGetX            ( XVector vector                           ) ;
double  xGetY            ( XVector vector                           ) ;

XMatrix xMatrixZero      ( void                                     ) ;
XMatrix xMatrixIdentity  ( void                                     ) ;
XMatrix xMatrixTranslate ( double tx  , double ty                   ) ;
XMatrix xMatrixRotate    ( double thetaDegreesClockwise             ) ;
XMatrix xMatrixScale     ( double sx  , double sy                   ) ;
XMatrix xMatrixShear     ( double sxy , double syx                  ) ;

XMatrix xInverse         ( XMatrix matrix                           ) ;
XVector xMultiplyMV      ( XMatrix matrixLeft , XVector vectorRight ) ;
XMatrix xMultiplyMM      ( XMatrix matrixLeft , XMatrix matrixRight ) ;

void    xPrintVector     ( XVector vector                           ) ;
void    xPrintMatrix     ( XMatrix matrix                           ) ;

/***************************************************************************************************************************************************/

#endif

/***************************************************************************************************************************************************/
