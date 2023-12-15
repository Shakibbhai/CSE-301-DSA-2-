#include <stdio.h>
#include <string.h>

int c[100][100];

int minEditDistance(const char *X, const char *Y, char editSteps[][50]) {
    int m = strlen(X);
    int n = strlen(Y);

    for (int i = 0; i <= m; i++) {
        c[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        c[0][j] = j;
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (X[i - 1] == Y[j - 1]) {
                c[i][j] = c[i - 1][j - 1];
            } else {
                c[i][j] = ((c[i - 1][j - 1] < c[i][j - 1]) ?
                           (c[i - 1][j - 1] < c[i - 1][j] ? c[i - 1][j - 1] : c[i - 1][j]) :
                           (c[i][j - 1] < c[i - 1][j] ? c[i][j - 1] : c[i - 1][j])) + 1;
            }
        }
    }

    int i = m, j = n, stepIndex = 0;
    while (i > 0 || j > 0) {
        if (i > 0 && j > 0 && X[i - 1] == Y[j - 1]) {
            i--;
            j--;
        } else if (i > 0 && c[i][j] == c[i - 1][j] + 1) {
            sprintf(editSteps[stepIndex], "Delete: %c", X[i - 1]);
            stepIndex++;
            i--;
        } else if (j > 0 && c[i][j] == c[i][j - 1] + 1) {
            sprintf(editSteps[stepIndex], "Insert: %c", Y[j - 1]);
            stepIndex++;
            j--;
        } else {
            sprintf(editSteps[stepIndex], "substitute %c with: %c", X[i - 1], Y[j - 1]);
            stepIndex++;
            i--;
            j--;
        }
    }

    return c[m][n];
}

int main() {
    const char *X = "cnnect";
    const char *Y = "cmmect";

    char editSteps[100][50];
    int editDistance = minEditDistance(X, Y, editSteps);
    printf("Edit Distance: %d\n", editDistance);

    printf("all Steps:\n");
    for (int i = 0; i < editDistance; i++) {
        printf("%s\n", editSteps[i]);
    }

    return 0;
}
