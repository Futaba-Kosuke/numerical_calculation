#include<stdio.h>
#include<math.h>

// 必要情報を読み込む
void scan_data(int *n, float x[10], float y[10]);
// 拡大係数行列を整形
void format_metrix(int n, float x[10], float y[10], float Result[2][3]);
// 行を入れ替える
void swap_line(int n, float a[], float b[]);
// 現在の拡大係数行列の状態を表示
void display_metrix(float A[2][3]);
// 左辺の係数行列を対角行列に整形する
int format_diagonal(float A[2][3]);
// 上三角1次連立方程式の解を算出する
void calcute_diagonal(float A[2][3]);

int main(void) {

  int n =  0;
  float x[10] = {0};
  float y[10] = {0};

  float expansion_factor_matrix[2][3] = {0};

  scan_data(&n, x, y);

  format_metrix(n, x, y, expansion_factor_matrix);

  if (format_diagonal(expansion_factor_matrix)) {
    calcute_diagonal(expansion_factor_matrix);
  } else {
    printf("一意解が存在しません。");
  }

  return 0;

}

void scan_data(int *n, float x[10], float y[10]) {

  char y_or_n = 'n';

  int i;

  printf("このプログラムは最小2乗法によって\n");
  printf("\ty = a*e^(bx)\n");
  printf("の形の曲線をあてはめるものです。\n");

  while (y_or_n != 'Y' && y_or_n != 'y') {
    
    *n = 0; // 正しく入力できていなかった場合用

    while (!(1 < *n && *n < 11)) {
      printf("データの個数は何個ですか。(1 < n < 11) n = ");
      scanf("%d%*c", n);
    }

    for (i = 0; i < *n; i++) {
      printf("%d個目のデータ\n", i + 1);
      printf("\tx = ");
      scanf("%f%*c", &x[i]);
      printf("\ty = ");
      scanf("%f%*c", &y[i]);
    }

    printf("正しく入力しましたか。(y/n) ");
    scanf("%c%*c", &y_or_n);
  }

  return;
}

void format_metrix(int n, float x[10], float y[10], float Result[2][3]) {
  
  int i, j, k;
  
  float A[10][2];
  float b[10];

  // Aを整形
  for (i = 0; i < n; i++) {
    A[i][0] = 1;
    A[i][1] = x[i];
  }

  for (i = 0; i < 2; i++) {
    for (j = 0; j < 3; j++) {
      for (k = 0; k < n; k++) {
        if (j != 2) {
          Result[i][j] += A[k][i] * A[k][j];
        } else {
          Result[i][j] += A[k][i] * logf(y[k]);
        }
      }
    }
  }

  return;
}

void swap_line(int n, float a[], float b[]) {
  int i;
  float temp;
  for (i = 0; i < n + 1; i++) {
    temp = a[i];
    a[i] = b[i];
    b[i] = temp;
  }
  return;
}

void display_metrix(float A[2][3]) {
  int n = 2;
  int i, j;

  for (i = 0; i < n; i++) {
    printf("\t");
    for (j = 0; j < n + 1; j++) {
      printf("%f ", A[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  return;
}

int format_diagonal(float A[2][3]) {
  
  int n = 2;
  int i, j, k;
  int upper_line;
  float diagonal;

  // printf("入力された拡大係数行列\n");
  // display_metrix(A);

  for (i = 0; i < n; i++) {

    // (i, i)の絶対値が最も大きくなるように行を入れ替え（0除算を防ぐ）
    upper_line = i;
    for (j = i + 1; j < n; j++) {
      if (fabsf(A[upper_line][i]) < fabsf(A[j][i])) {
        upper_line = j;
      }
    }
    if (upper_line != i) {
      swap_line(n, A[i], A[upper_line]);
      // printf("%d行目と%d行目を入れ替えました。\n", i + 1, upper_line + 1);
      // display_metrix(n, A);
    }

    // (i, i)の要素を1に調整
    diagonal = A[i][i];
    if (diagonal) {
      for (j = i; j < n + 1; j++) {
        A[i][j] /= diagonal;
      }
    }
    
    // (i, i)以外の行のi列目の要素が0になるように減算
    for (j = 0; j < n; j++) {
      if (i == j) continue;
      for (k = n; k >= i; k--) {
        A[j][k] -= A[j][i] * A[i][k];
      }
    }
    // printf("(%d, %d)成分を軸として掃き出した行列\n", i + 1, i + 1);
    // display_metrix(A);
  }
  
  // 一意解ができるか否か
  if (A[n-1][n-1] == 0) return 0;
  
  return 1;
}

void calcute_diagonal(float A[2][3]) {
  
  int n = 2;
  float solutions[2];
  int i, j;
  for (i = n - 1; i >= 0; i--) {
    solutions[i] = A[i][n];
    for (j = n - 1; j > i; j--) {
      solutions[i] -= A[i][j] * solutions[j];
    }
  }

  // 解を表示
  printf("\nxとyの関数関係は，");
  printf("y = %f*e^%fx\n", expf(solutions[0]), solutions[1]);
  printf("です。");

  return;
}
