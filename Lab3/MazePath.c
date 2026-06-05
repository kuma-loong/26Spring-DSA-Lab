#include <stdio.h>

int m, n;
int maze[10][10], visited[10][10];
long long ans = 0;
int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void dfs(int x, int y) {
    if (x == m - 1 && y == n - 1) {
        ans++;
        return;
    }

    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < m && ny >= 0 && ny < n && !maze[nx][ny] && !visited[nx][ny]) {
            visited[nx][ny] = 1;
            dfs(nx, ny);
            visited[nx][ny] = 0;
        }
    }
}

int main() {
    scanf("%d %d", &m, &n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &maze[i][j]);
        }
    }

    if (!maze[0][0] && !maze[m - 1][n - 1]) {
        visited[0][0] = 1;
        dfs(0, 0);
    }

    printf("%lld\n", ans);
    return 0;
}
