#include "s21_matrix.h"

// void print_matrix(matrix_t A) {
//     for (int i = 0; i < A.rows; i++) {
//         for (int j = 0; j < A.columns; j++) {
//             if (j != A.rows - 1) printf("%lf ", A.matrix[i][j]);
//             else printf("%lf", A.matrix[i][j]);
//         }
//         printf("\n");
//     }
// }

// void init_matrix(matrix_t *A) {
//     int counter = 1;
//     for (int i = 0; i < A->columns; i++) {
//         for (int j = 0; j < A->rows; j++) {
//             A->matrix[i][j] = counter;
//             counter++;
//         }
//     }
// }

void nullife(matrix_t *A) {
  A->matrix = NULL;
  A->columns = 0;
  A->rows = 0;
}

int size_match(matrix_t A, matrix_t B) {
  int res = 0;
  if (A.columns == B.columns && A.rows == B.rows) res = 1;
  return res;
}

int exist_matrix(matrix_t A) {
  int res = OK;
  if (A.columns < 1 || A.rows < 1 || A.matrix == NULL || !A.matrix)
    res = INCORRECT_MATRIX;
  return res;
}

matrix_t minor_creator(int i, int j, matrix_t *A) {
  matrix_t minor;
  s21_create_matrix(A->rows - 1, A->columns - 1, &minor);
  int n = 0;
  int k = 0;
  int m = 0;
  for (int l = 0; l < A->rows; l++) {
    for (n = 0; n < A->columns; n++) {
      if (n != j && l != i) {
        minor.matrix[k][m] = A->matrix[l][n];
        m++;
        if (m == A->columns - 1) {
          k++;
          m = 0;
        }
      }
    }
  }
  return minor;
}