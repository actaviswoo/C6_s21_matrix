#include "s21_matrix.h"

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = OK;
  if (exist_matrix(*A) != 0) {
    res = INCORRECT_MATRIX;
  } else if ((A->rows == 1 || A->columns == 1)) {
    res = CALC_ERROR;
  } else if (A->rows == A->columns) {
    res = s21_create_matrix(A->rows, A->columns, result);
    if (res == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          matrix_t minor = minor_creator(i, j, A);
          double temp = 0;
          s21_determinant(&minor, &temp);
          result->matrix[i][j] = pow(-1, (j + i) + 2) * temp;
          s21_remove_matrix(&minor);
        }
      }
    } else {
      res = INCORRECT_MATRIX;
    }
  } else {
    res = CALC_ERROR;
  }
  return res;
}