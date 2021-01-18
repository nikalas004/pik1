#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
	srand ( time(NULL) );
	int a, b, n, m;
	printf("Enter n: ");
	scanf("%d", &n);
	printf("Enter m: ");
	scanf("%d", &m);
	printf("Enter a: ");
	scanf("%d", &a);
	printf("Enter b: ");
	scanf("%d", &b);

	int matrix[n][m];
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < n; j++) {
			matrix[i][j] = (rand() % (b - a)) + a;
		}
	}
	
	int multi;
	int num[2] = {0, 0} , direction = 1;
	
	int max = matrix[0][0] * matrix [0][1] * matrix[0][2] * matrix[0][3];
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(j+3 < m) {
				multi = matrix[i][j] * matrix [i][j+1] * matrix[i][j+2] * matrix[i][j+3];
				if(multi > max) {
					num[0] = i+1;
					num[1] = j+1;
					direction = 1;
					max = multi;
				}
			}
		}
	}
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(i+3 < n) {
				multi = matrix[i][j] * matrix [i+1][j] * matrix[i+2][j] * matrix[i+3][j];
				if(multi > max) {
					num[0] = i+1;
					num[1] = j+1;
					direction = 2;
					max = multi;
				}
			}
		}
	}
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			if(i+3 < n && j+3 < m) {
				multi = matrix[i][j] * matrix [i+1][j+1] * matrix[i+2][j+2] * matrix[i+3][j+3];
				if(multi > max) {
					num[0] = i+1;
					num[1] = j+1;
					direction = 3;
					max = multi;
				}
			}
		}
	}
	
	for(int i = n; i > 0; i--) {
		for(int j = m; j > 0; j--) {
			if(i-3 > 0 && j-3 > 0) {
				multi = matrix[i][j] * matrix [i-1][j-1] * matrix[i-2][j-2] * matrix[i-3][j-3];
				if(multi > max) {
					num[0] = i+1;
					num[1] = j+1;
					direction = 4;
					max = multi;
				}
			}
		}
	}
	
	printf("\nGenrated matrix: \n");
	
	for(int i = 0; i < n; i++) {
		for(int j = 0; j < m; j++) {
			printf("%d ", matrix[i][j]);
		}
		printf("\n");
	}
	
	printf("\nPoints: ");
	if(direction == 1) {
		for(int i = 0; i <= 3; i++) {
			printf("%d(%d, %d); ", matrix[num[0]-1][num[1]+i-1], num[0], num[1]+i);	
		}
	} else if(direction == 2) {
		for(int i = 0; i <= 3; i++) {
			printf("%d(%d, %d); ", matrix[num[0]+i-1][num[1]-1], num[0]+i, num[1]);	
	 	}
	} else if(direction == 3) {
		for(int i = 0; i <= 3; i++) {
			printf("%d(%d, %d); ", matrix[num[0]+i-1][num[1]+i-1], num[0]+i, num[1]+i);	
	 	}
	} else {
		for(int i = 0; i <= 3; i++) {
			printf("%d(%d, %d); ", matrix[num[0]+i-1][num[1]+i-1], num[0]+i, num[1]+i);	
	 	}
	}
	printf("\nLargest multiplication: %d\n", max);
	return 0;
}
