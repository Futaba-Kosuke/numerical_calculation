#include<stdio.h>
#include<math.h>

void scan_data(int *a, int *b, int *n);

float function(float x);

void trapezoid_rule(int a, int b, int n);

int main(void) {

  int a, b;
  int n;

  printf("台形公式により，以下の関数の積分計算を行います．\n");
  printf("\tf(x) = 1/(1+x^2)\n\n");

  scan_data(&a, &b, &n);

  trapezoid_rule(a, b, n);

  return 0;
}

void scan_data(int *a, int *b, int *n) {
  printf("積分区間[a, b]を入力してください．\n");
  printf("\ta = ");
  scanf("%d", a);
  printf("\tb = ");
  scanf("%d", b);

  printf("分割数を入力してください．\n");
  printf("\tn = ");
  scanf("%d", n);
  printf("\n");
  return;
}

float function(float x) {
  return 1 / (1 + powf(x, 2));
}

void trapezoid_rule(int a, int b, int n) {

  float solution = 0;
  float solution_first_last = 0;
  float solution_middle = 0;

  float h = 1 / (float)n;
  int i, j;  

  for (i = 0; i <= n; i++) {
    if (i == 0 || i == n) {
      solution_first_last += function(a + i * h);
    } else {
      solution_middle += function(a + i * h);
    }
  }
  solution = (h / 2.0) * (solution_first_last + 2 * solution_middle);

  printf("---- 計算過程の表示 ----\n");
  printf("\t刻み幅 h = %f\n\n", h);
  printf("\tf(a) + f(b) = %f\n", solution_first_last);
  printf("\tΣ f(xi)(両端以外) = %f\n", solution_middle);
  printf("\tf(a) + f(b) + 2 * Σ f(xi)(両端以外) = %f\n", solution_first_last + 2 * solution_middle);
  printf("\th / 2.0 * (f(a) + f(b) + Σ f(xi)(両端以外)) = %f\n\n", solution);

  printf("---- 計算結果の表示 ----\n\n");
  printf("\t積分値は，%fです．\n", solution);

  return;

}