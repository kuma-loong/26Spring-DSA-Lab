#include <stdio.h>
#include <stdlib.h>

int main() {
    int c, n;

    scanf("%d %d", &c, &n);
    int* dp = (int*)calloc(c + 1, sizeof(int));
    for (int i = 0; i < n; i++) {
        int time, value;
        scanf("%d %d", &time, &value);
        for (int j = time; j <= c; j++) {
            if (dp[j] < dp[j - time] + value) {
                dp[j] = dp[j - time] + value;
            }
        }
    }

    printf("%d\n", dp[c]);
    free(dp);
    return 0;
}
