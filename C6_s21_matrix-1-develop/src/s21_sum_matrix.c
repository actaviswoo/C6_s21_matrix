#include "s21_matrix.h"

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = OK;
  nullife(result);
  if (exist_matrix(*A) != 0 || exist_matrix(*B) != 0) {
    res = INCORRECT_MATRIX;
  } else if (size_match(*A, *B)) {
    s21_create_matrix(A->rows, A->columns, result);
    if (res == OK) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + (B->matrix[i][j]);
        }
      }
    }
  } else {
    res = CALC_ERROR;
  }
  return res;
}