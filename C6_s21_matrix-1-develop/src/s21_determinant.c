#include "s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int res = OK;
  if (!result) {
    res = CALC_ERROR;
  } else if (exist_matrix(*A) != 0) {
    res = INCORRECT_MATRIX;
  } else if (A->columns != A->rows) {
    res = CALC_ERROR;
  } else {
    *result = 0;
    if (A->rows == 1) {
      *result = A->matrix[0][0];
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      for (int j = 0; j < A->columns; j++) {
        matrix_t minor = minor_creator(0, j, A);
        double temp = 0;
        s21_determinant(&minor, &temp);
        *result += pow(-1.0, j) * temp * A->matrix[0][j];
        s21_remove_matrix(&minor);
      }
    }
  }
  return res;
}