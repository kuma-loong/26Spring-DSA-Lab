#include <stdio.h>
#include <string.h>

#define MAXN 205
#define MAXM 1005
#define MAXC 505
#define NEG -1000000000

typedef struct {
    int to;
    int cost;
    int next;
} Edge;

int main() {
    int n, m, c, s, t;
    int value[MAXN], indeg[MAXN] = {0}, head[MAXN], queue[MAXN];
    int dp[MAXN][MAXC];
    Edge edges[MAXM];

    scanf("%d %d %d", &n, &m, &c);
    scanf("%d %d", &s, &t);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &value[i]);
    }

    for (int i = 1; i <= n; i++) {
        head[i] = -1;
    }

    for (int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[i].to = v;
        edges[i].cost = w;
        edges[i].next = head[u];
        head[u] = i;
        indeg[v]++;
    }

    int front = 0, rear = 0;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] == 0) {
            queue[rear++] = i;
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= c; j++) {
            dp[i][j] = NEG;
        }
    }
    dp[s][0] = value[s];

    while (front < rear) {
        int u = queue[front++];
        for (int e = head[u]; e != -1; e = edges[e].next) {
            int v = edges[e].to;
            int w = edges[e].cost;
            for (int cost = 0; cost + w <= c; cost++) {
                if (dp[u][cost] != NEG && dp[v][cost + w] < dp[u][cost] + value[v]) {
                    dp[v][cost + w] = dp[u][cost] + value[v];
                }
            }
            if (--indeg[v] == 0) {
                queue[rear++] = v;
            }
        }
    }

    int ans = -1;
    for (int cost = 0; cost <= c; cost++) {
        if (dp[t][cost] > ans) {
            ans = dp[t][cost];
        }
    }
    printf("%d\n", ans);

    return 0;
}
