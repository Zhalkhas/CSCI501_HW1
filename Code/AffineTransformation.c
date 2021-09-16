/****************************************************************************************************************************************************
 *
 * Copyright (C) 2021 Selim Temizer.
 *
 * This file is part of AffineTransformation.
 *
 * AffineTransformation is free software: you can redistribute it and/or modify
 *it under the terms of the GNU Lesser General Public License as published by
 *the Free Software Foundation, either version 3 of the License, or (at your
 *option) any later version.
 *
 * AffineTransformation is distributed in the hope that it will be useful, but
 *WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 *FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License
 *for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 *along with AffineTransformation. If not, see <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************************************************************************************/

/***************************************************************************************************************************************************/

#include "AffineTransformation.h"
#include <math.h>
#include <stdio.h>

/***************************************************************************************************************************************************/

XVector xVectorZero(void) {
  XVector vector = {{{0.0}, {0.0}, {0.0}}};
  return vector;
}

/*=================================================================================================================================================*/

XVector xVector(double x, double y) {
  XVector vector = {{{x}, {y}, {1.0}}};
  return vector;
}

/*=================================================================================================================================================*/

double xGetX(XVector vector) { return vector.data[0][0]; }
double xGetY(XVector vector) { return vector.data[1][0]; }

/*=================================================================================================================================================*/

XMatrix xMatrixZero(void) {
  XMatrix matrix = {{{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}};
  return matrix;
}

/*=================================================================================================================================================*/

XMatrix xMatrixIdentity(void) {
  XMatrix matrix = {{{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}};
  return matrix;
}

/*=================================================================================================================================================*/

XMatrix xMatrixTranslate(double tx, double ty) {
  XMatrix matrix = {{{1.0, 0.0, tx}, {0.0, 1.0, ty}, {0.0, 0.0, 1.0}}};
  return matrix;
}

/*=================================================================================================================================================*/

XMatrix xMatrixRotate(double thetaDegreesClockwise) {
  double thetaRadians = M_PI * (thetaDegreesClockwise / 180.0);

  XMatrix matrix = {{{cos(thetaRadians), -sin(thetaRadians), 0.0},
                     {sin(thetaRadians), cos(thetaRadians), 0.0},
                     {0.0, 0.0, 1.0}}};
  return matrix;
}

/*=================================================================================================================================================*/

XMatrix xMatrixScale(double sx, double sy) {
  XMatrix matrix = {{{sx, 0.0, 0.0}, {0.0, sy, 0.0}, {0.0, 0.0, 1.0}}};
  return matrix;
}

/*=================================================================================================================================================*/

XMatrix xMatrixShear(double sxy, double syx) {
  XMatrix matrix = {{{1.0, sxy, 0.0}, {syx, 1.0, 0.0}, {0.0, 0.0, 1.0}}};
  return matrix;
}

/*=================================================================================================================================================*/

double xDetermninant2x2(int x, int y, XMatrix matrix) {
  double res[4];
  int count = 0;
  for (int i = 0; i < 3 && count < 4; i++) {
    for (int j = 0; j < 3 && count < 4; j++) {
      if (i != x && j != y) {
        res[count] = matrix.data[i][j];
        count++;
      }
    }
  }
  return res[0] * res[3] - res[1] * res[2];
}

/*=================================================================================================================================================*/

double xDeterminant(XMatrix matrix) {
  double det_0_0 = xDetermninant2x2(0, 0, matrix);

  double det_0_1 = xDetermninant2x2(0, 1, matrix);

  double det_0_2 = xDetermninant2x2(0, 2, matrix);

  return matrix.data[0][0] * det_0_0 - matrix.data[0][1] * det_0_1 +
         matrix.data[0][2] * det_0_2;
}

/*=================================================================================================================================================*/

XMatrix xTranspose(XMatrix matrix) {
  XMatrix res = xMatrixZero();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      res.data[i][j] = matrix.data[j][i];
    }
  }
  return res;
}

/*=================================================================================================================================================*/

XMatrix xMultiplyByScalar(XMatrix matrix, double x) {
  XMatrix res = xMatrixZero();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      res.data[i][j] = matrix.data[i][j] * x;
    }
  }
  return res;
}

/*=================================================================================================================================================*/

XMatrix xInverse(XMatrix matrix) {
  // 1. find determinant
  double determinant = xDeterminant(matrix);
  if (!determinant) {
    // if determinant is zero, inverse does not exist
    return xMatrixZero();
  }
  // 2. transpose matrix
  XMatrix transpose = xMatrixZero();
  transpose = xTranspose(matrix);
  // 3. create adjugate matrix
  XMatrix adj = xMatrixZero();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      adj.data[i][j] = xDetermninant2x2(i, j, transpose);
      if (i % 2 == 0 && j % 2 == 0) {
        adj.data[i][j] *= -1;
      }
    }
  }
  // 4. divide matrix by determinant
  return xMultiplyByScalar(adj, determinant);
  /* TODO */
}

/*=================================================================================================================================================*/

XVector xMultiplyMV(XMatrix matrixLeft, XVector vectorRight) {
  XVector res = xVectorZero();
  for (int i = 0; i < 3; i++) {
    for (int k = 0; k < 3; k++) {
      res.data[i][0] += matrixLeft.data[i][k] * vectorRight.data[k][0];
    }
  }
  return res;
  /* TODO */
}

/*=================================================================================================================================================*/

XMatrix xMultiplyMM(XMatrix matrixLeft, XMatrix matrixRight) {
  XMatrix res = xMatrixZero();
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 3; k++) {
        res.data[i][j] += matrixLeft.data[i][k] * matrixRight.data[k][j];
      }
    }
  }
  return res;
  /* TODO */
}

/*=================================================================================================================================================*/

void xPrintVector(XVector vector) {
  printf("| % lf |\n", vector.data[0][0]);
  printf("| % lf |\n", vector.data[1][0]);
  printf("| % lf |\n", vector.data[2][0]);
}

/*=================================================================================================================================================*/

void xPrintMatrix(XMatrix matrix) {
  printf("| % lf % lf % lf |\n", matrix.data[0][0], matrix.data[0][1],
         matrix.data[0][2]);
  printf("| % lf % lf % lf |\n", matrix.data[1][0], matrix.data[1][1],
         matrix.data[1][2]);
  printf("| % lf % lf % lf |\n", matrix.data[2][0], matrix.data[2][1],
         matrix.data[2][2]);
}

/***************************************************************************************************************************************************/
