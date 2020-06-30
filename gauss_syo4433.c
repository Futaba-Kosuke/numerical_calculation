#include<stdio.h>
#include<math.h>

// 必要情報を読み込む
void scan_equations(int *n, float A[6][7], char solutions_char[]);
// 行を入れ替える
void swap_line(int n, float a[], float b[]);
// 現在の拡大係数行列の状態を表示
void display_metrix(int n, float A[6][7]);
// 上三角行列に整形する
int format_ue3kaku(int n, float A[6][7]);
// 上三角1次連立方程式の解を算出する
void calcute_ue3kaku(int n, float A[6][7], float solutions[], char solutions_char[]);

int main(void) {

  float solutions[6];
  char solutions_char[6] = {'x', 'y', 'z', 'u', 'v', 'w'};

  int n =  0;
  float A[6][7] = {0};

  int i, j;

  printf("ガウスの消去法による連立1次方程式の解法\n");

  scan_equations(&n, A, solutions_char);

  if(format_ue3kaku(n, A)) {
    calcute_ue3kaku(n, A, solutions, solutions_char);
  } else {
    printf("一意解が存在しません。\n");
  }

  return 0;

}

void scan_equations(int *n, float A[6][7], char solutions_char[]) {

  char y_or_n = 'n';

  int i, j;

  while (y_or_n != 'Y' && y_or_n != 'y') {
    
    *n = 0; // 正しく入力できていなかった場合用

    while (!(1 < *n && *n < 7)) {
      printf("何元連立1次方程式ですか。(1 < n < 7) n = ");
      scanf("%d%*c", n);
    }

    printf("係数と右辺の値を入力してください。\n\n");

    for (i = 0; i < *n; i++) {
      printf("第%d式\n", i + 1);
      for (j = 0; j < *n; j++) {
        printf("\t%cの係数 A(%d, %d) = ", solutions_char[i], i + 1, j + 1);
        scanf("%f%*c", &A[i][j]);
      }
      printf("\n\t右辺の値 A(%d, %d) = ", i + 1, *n + 1);
      scanf("%f%*c", &A[i][*n]);
      printf("\n");
    }

    printf("正しく入力しましたか。(y/n) ");
    scanf("%c%*c", &y_or_n);
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

void display_metrix(int n, float A[6][7]) {
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

int format_ue3kaku(int n, float A[6][7]) {
  
  int i, j, k;
  int upper_line;
  float diagonal;

  printf("入力された拡大係数行列\n");
  display_metrix(n, A);

  for (i = 0; i < n; i++) {

    // (i, i)の絶対値が最も大きくなるように行を入れ替え
    upper_line = i;
    for (j = i + 1; j < n; j++) {
      if (fabsf(A[upper_line][i]) < fabsf(A[j][i])) {
        upper_line = j;
      }
    }
    if (upper_line != i) {
      swap_line(n, A[i], A[upper_line]);
      printf("%d行目と%d行目を入れ替えました。\n", i + 1, upper_line + 1);
      display_metrix(n, A);
    }

    // (i, i)の要素を1に調整
    diagonal = A[i][i];
    if (diagonal) {
      for (j = i; j < n + 1; j++) {
        A[i][j] /= diagonal;
      }
    }
    
    // (i, i)以外の行のi列目の要素が0になるように減算
    for (j = i + 1; j < n; j++) {
      for (k = n; k >= i; k--) {
        A[j][k] -= A[j][i] * A[i][k];
      }
    }
    printf("(%d, %d)成分を軸として掃き出した行列\n", i + 1, i + 1);
    display_metrix(n, A);
  }
  
  // 一意解ができるか否か
  if (A[n-1][n-1] == 0) return 0;
  
  return 1;
}

void calcute_ue3kaku(int n, float A[6][7], float solutions[], char solutions_char[]) {
  int i, j;
  for (i = n - 1; i >= 0; i--) {
    solutions[i] = A[i][n];
    for (j = n - 1; j > i; j--) {
      solutions[i] -= A[i][j] * solutions[j];
    }
  }

  // 解を表示
  printf("連立1次方程式の解は\n");
  for (i = 0; i < n; i++) {
    printf("%c =\t%f\n", solutions_char[i], solutions[i]);
  }

  return;
}