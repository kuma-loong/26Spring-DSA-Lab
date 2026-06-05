#include <stdio.h>
#include <stdlib.h>

// 信封结构体
typedef struct {
    int width;
    int height;
} Envelope;

int cmpEnvelope(const void* a, const void* b) {
    Envelope* x = (Envelope*)a;
    Envelope* y = (Envelope*)b;
    if (x->width != y->width) {
        return x->width - y->width;
    }
    return y->height - x->height;
}

int lowerBound(int* arr, int len, int target) {
    int left = 0, right = len;
    while (left < right) {
        int mid = (left + right) / 2;
        if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid;
        }
    }
    return left;
}

int maxEnvelopes(Envelope* envelopes, int n) {
    if (n == 0) {
        return 0;
    }

    qsort(envelopes, n, sizeof(Envelope), cmpEnvelope);

    int* dp = (int*)malloc(n * sizeof(int));
    int len = 0;
    for (int i = 0; i < n; i++) {
        int pos = lowerBound(dp, len, envelopes[i].height);
        dp[pos] = envelopes[i].height;
        if (pos == len) {
            len++;
        }
    }

    free(dp);
    return len;
}

int main() {
    int n;
    scanf("%d", &n);
    
    Envelope* envelopes = (Envelope*)malloc(n * sizeof(Envelope));
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &envelopes[i].width, &envelopes[i].height);
    }
    
    int result = maxEnvelopes(envelopes, n);
    printf("%d\n", result);
    
    free(envelopes);
    return 0;
}
