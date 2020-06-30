#include<stdio.h>

int main(void) {

  float x[7];
  
  int n = 0;
  float A[7][7] = {0};
  float b[7] = {0};

  int i, j;
  
  float diagonal;
  char y_or_n = 'n';

  printf("上三角型1次連立方程式の解法\n\n");

  while(y_or_n != 'Y' && y_or_n != 'y') {
    while(!(1 < n && n < 7)) {
      printf("未知数の個数 n を入力してください。(1 < n < 7) = ");
      scanf("%d", &n);
    }

    printf("\n係数と右辺の値を入力してください。\n");

    for (i = 0; i < n; i++) {
      printf("\n第%d式:\n", i + 1);
      for (j = i; j < n; j++) {
        printf("\tx%dの係数 = ", j + 1);
        scanf("%f", &A[i][j]);
        // 対角成分を取得
        if (i == j) { diagonal = A[i][j]; }
        A[i][j] /= diagonal;
      }
      printf("\n\t右辺の値 = ");
      scanf("%f%*c", &b[i]);
      b[i] /= diagonal;
    }

    // テスト用
    // for (i = 0; i < n; i++) {
    //   for (j = 0; j < n; j++) {
    //     printf("%f ", A[i][j]);
    //   }
    //   printf("%f\n", b[i]);
    // }

    printf("正しく入力しましたか。(y/n) ");
    scanf("%c", &y_or_n);
  }

  for (i = 0; i < n; i++) {
    x[n-1-i] = b[n-1-i];
    for (j = n - i; j < n; j++) {
      x[n-1-i] -= A[n-1-i][j] * x[j];
    }
    printf("\n");
  }

  printf("\n上三角型連立1次方程式の解\n\n");

  for (i = 0; i < n; i++) {
    printf("\tx%d =\t%f\n", i + 1, x[i]);
  }

}
