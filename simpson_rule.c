#include<stdio.h>
#include<math.h>

void scan_data(int *a, int *b, int *n);

float function(float x);

void simpson_rule(int h, int a, int b);

void display(float A[3][20], int row, float width);

int main(void) {

  int n;
  // 積分範囲
  int a;
  int b;

  printf("シンプソンの公式により，以下の関数の積分計算を行います．\n");
  printf("\tf(x) = 1/(1+x^2)\n\n");

  scan_data(&a, &b, &n);

  simpson_rule(n, a, b); 

  return 0;
}

void scan_data(int *a, int *b, int *n) {
  printf("積分区間[a, b]を入力してください．\n");
  printf("\ta = ");
  scanf("%d", a);
  printf("\tb = ");
  scanf("%d", b);

  printf("2n 分割します．分割数の 1/2 を入力してください．\n");
  printf("\tn = ");
  scanf("%d", n);
  printf("\n");
  return;
}

float function(float x) {
  return 1 / (1 + powf(x, 2));
}

void simpson_rule(int n, int a, int b) {
  
  float h = (float)(b - a) / (2 * n);
  
  int i, j;
  
  float solution;
  float solutions[3][20] = {0};

  for (i = 0; i <= 2 * n; i++) {
    solution = function(a + h * i);
    if (i == 0 || i == 2 * n) {
      solutions[0][i / (2 * n)] = solution;
      solutions[0][n] += solution;
    } else if (i % 2 == 0) {
      solutions[1][i / 2 - 1] = solution;
      solutions[1][n] += solution;
    } else {
      solutions[2][i / 2] = solution;
      solutions[2][n] += solution;
    }
  }

  display(solutions, n + 1, h);

  return;

}

void display(float A[3][20], int row, float width) {
  int i, j;

  for (i = 0; i < row; i++) {
    printf("\t");
    for (j = 0; j < 3; j++) {
      printf("%f ", A[j][i]);
    }
    printf("\n");
  }
  printf("\n");

  printf("\t解: %f\n", width * (A[0][row - 1] + A[1][row - 1] * 2 + A[2][row - 1] * 4) / 3);

  return;
}
