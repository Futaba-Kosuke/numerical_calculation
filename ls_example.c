#include<stdio.h>
#include<math.h>

#define N 10
#define FN 2

double ffv (int p, double a) {
  switch (p) {
    case 0: return 1.0;
    case 1: return a;
    default: return a;
  }
}

int main(void) {
  int n;
  int i, j, k;
  double x, y, p, a[N][FN + 1], c[FN][FN + 1];
  char z;

  do {
    scanf("%d%*c", &n);
    if (n <= 1 || N < n) continue;

    for (i = 0; i < n; i++) {
      scanf("%lf", &x);
      for (j = 0; j < FN; j++) {
	a[i][j] = ffv(j, x);
      }
      scanf("%lf%*c", &y);
      a[i][FN] = logl(y);
    }
    printf("正しく入力しましたか (y / n) ");
    scanf("%c", &z);
  } while(z != 'y');

  for (i = 0; i < N; i++) {
    for (j = 0; j < FN + 1; j++) {
      printf("%f ", a[i][j]);
    }
    printf("\n");
  }
  printf("\n");

  for (i = 0; i < FN; i++) {
    for (j = 0; j < FN + 1; j++) {
      c[i][j] = 0;
      for (k = 0; k < n; k++) {
        c[i][j] += a[k][i] * a[k][j];
	printf("%f += %f * %f\n", c[i][j], a[k][i], a[k][j]);
      }
      printf("\n");
    }
  }

  for (i = 0; i < FN; i++) {
    for (j = 0; j < FN + 1; j++) {
      printf("%f ", c[i][j]);
    }
    printf("\n");
  }

  for (i = 0; i < FN; i++) {
    for (j = FN; j >= i; j--) {
      c[i][j] /= c[i][i];
    }

    for (j = 0; j < FN; j++) {
      for (k = 0; k < FN + 1; k++) {
        printf("%f ", c[j][k]);
      }
      printf("\n");
    }
    printf("\n");

    for (j = 0; j < FN; j++) {
      if (i == j) continue;
      for (k = FN; k >= i; k--) {
        c[j][k] -= c[i][k] * c[j][i];
      }
    } 
  }

  for (i = 0; i < FN; i++) {
    for (j = 0; j < FN + 1; j++) {
      printf("%f ", c[i][j]);
    }
    printf("\n");
  }

  printf("%f, %f\n", (float)expl(c[0][FN]), c[1][FN]);

  return 0;
}
