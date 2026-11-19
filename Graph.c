#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>

typedef struct {
    int source;
    int destination;
    int weight;
    int idx;
} Edge;

int findRoot(int parent[], int vertex) {
    if (parent[vertex] != vertex)
        parent[vertex] = findRoot(parent, parent[vertex]);
    return parent[vertex];
}

void unionSets(int parent[], int rank[], int a, int b) {
    int ra = findRoot(parent, a);
    int rb = findRoot(parent, b);
    if (ra == rb) return;

    if (rank[ra] < rank[rb])       parent[ra] = rb;
    else if (rank[ra] > rank[rb])  parent[rb] = ra;
    else { parent[rb] = ra; rank[ra]++; }
}

int compareEdges(const void *first, const void *second) {
    const Edge *e1 = (const Edge *) first;
    const Edge *e2 = (const Edge *) second;
    if (e1->weight != e2->weight) return e1->weight - e2->weight;
    return e1->idx - e2->idx;
}

bool isRemoved(Edge e, int ru, int rv) {
    if (ru < 0) return false;
    return (e.source == ru && e.destination == rv) ||
           (e.source == rv && e.destination == ru);
}

void buildMatrix(int n, int g[n][n], Edge edges[], int m, int ru, int rv) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            g[i][j] = 0;

    for (int i = 0; i < m; ++i) {
        if (isRemoved(edges[i], ru, rv)) continue;
        int u = edges[i].source, v = edges[i].destination, w = edges[i].weight;
        if (g[u][v] == 0 || w < g[u][v]) {
            g[u][v] = w;
            g[v][u] = w;
        }
    }
}

int dijkstra(int n, int g[n][n], int src, int dst, int path[], int *len) {
    int dist[n], prev[n];
    bool done[n];

    for (int i = 0; i < n; ++i) {
        dist[i] = INT_MAX;
        prev[i] = -1;
        done[i] = false;
    }
    dist[src] = 0;

    for (int c = 0; c < n; ++c) {
        int u = -1, best = INT_MAX;
        for (int i = 0; i < n; ++i)
            if (!done[i] && dist[i] < best) { best = dist[i]; u = i; }
        if (u == -1) break;
        done[u] = true;

        for (int v = 0; v < n; ++v) {
            if (g[u][v] != 0 && !done[v] && dist[u] + g[u][v] < dist[v]) {
                dist[v] = dist[u] + g[u][v];
                prev[v] = u;
            }
        }
    }

    if (dist[dst] == INT_MAX) return -1;

    int tmp[n], cnt = 0;
    for (int v = dst; v != -1; v = prev[v]) tmp[cnt++] = v;
    *len = cnt;
    for (int i = 0; i < cnt; ++i) path[i] = tmp[cnt - 1 - i];
    return dist[dst];
}

bool kruskal(int n, Edge edges[], int m, int ru, int rv, int tree[n][n]) {
    int parent[n], rank[n];
    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        rank[i] = 0;
        for (int j = 0; j < n; ++j) tree[i][j] = 0;
    }

    Edge *list = malloc(sizeof(Edge) * (m > 0 ? m : 1));
    int cnt = 0;
    for (int i = 0; i < m; ++i)
        if (!isRemoved(edges[i], ru, rv)) list[cnt++] = edges[i];

    qsort(list, cnt, sizeof(Edge), compareEdges);

    int selected = 0;
    for (int i = 0; i < cnt; ++i) {
        Edge e = list[i];
        if (findRoot(parent, e.source) != findRoot(parent, e.destination)) {
            tree[e.source][e.destination] = e.weight;
            tree[e.destination][e.source] = e.weight;
            unionSets(parent, rank, e.source, e.destination);
            selected++;
        }
    }
    free(list);
    return selected == n - 1;
}

int findMinVertex(int n, int minCost[], bool included[]) {
    int minimum = INT_MAX, minVertex = -1;
    for (int v = 0; v < n; ++v)
        if (!included[v] && minCost[v] < minimum) {
            minimum = minCost[v];
            minVertex = v;
        }
    return minVertex;
}

bool primMST(int n, int g[n][n], int tree[n][n]) {
    int parent[n], minCost[n];
    bool included[n];

    for (int i = 0; i < n; ++i) {
        parent[i] = -1;
        minCost[i] = INT_MAX;
        included[i] = false;
        for (int j = 0; j < n; ++j) tree[i][j] = 0;
    }
    minCost[0] = 0;

    for (int c = 0; c < n; ++c) {
        int cur = findMinVertex(n, minCost, included);
        if (cur == -1) return false;
        included[cur] = true;

        for (int nb = 0; nb < n; ++nb) {
            if (g[cur][nb] != 0 && !included[nb] && g[cur][nb] < minCost[nb]) {
                minCost[nb] = g[cur][nb];
                parent[nb] = cur;
            }
        }
    }

    for (int v = 1; v < n; ++v) {
        tree[parent[v]][v] = g[parent[v]][v];
        tree[v][parent[v]] = g[parent[v]][v];
    }
    return true;
}

int pathInTree(int n, int tree[n][n], int src, int dst, int path[], int *len) {
    int prev[n], queue[n], head = 0, tail = 0;
    bool seen[n];
    for (int i = 0; i < n; ++i) { prev[i] = -1; seen[i] = false; }

    queue[tail++] = src;
    seen[src] = true;
    while (head < tail) {
        int u = queue[head++];
        for (int v = 0; v < n; ++v) {
            if (tree[u][v] != 0 && !seen[v]) {
                seen[v] = true;
                prev[v] = u;
                queue[tail++] = v;
            }
        }
    }
    if (!seen[dst]) return -1;

    int tmp[n], cnt = 0, cost = 0;
    for (int v = dst; v != -1; v = prev[v]) {
        tmp[cnt++] = v;
        if (prev[v] != -1) cost += tree[v][prev[v]];
    }
    *len = cnt;
    for (int i = 0; i < cnt; ++i) path[i] = tmp[cnt - 1 - i];
    return cost;
}

void printResult(const char *label, int cost, int path[], int len) {
    printf("%s: ", label);
    if (cost < 0) {
        printf("Not Possible\n");
        return;
    }
    for (int i = 0; i < len; ++i) {
        printf("%d", path[i]);
        if (i != len - 1) printf(" -> ");
    }
    printf(" (Cost: %d)\n", cost);
}

void solve(int n, Edge edges[], int m, int src, int dst, int ru, int rv, bool updated) {
    int g[n][n], kt[n][n], pt[n][n];
    int path[n], len = 0, cost;

    buildMatrix(n, g, edges, m, ru, rv);

    bool kConnected = kruskal(n, edges, m, ru, rv, kt);
    bool pConnected = primMST(n, g, pt);

    cost = dijkstra(n, g, src, dst, path, &len);
    printResult(updated ? "Updated Shortest Path" : "Shortest Path", cost, path, len);

    cost = kConnected ? pathInTree(n, kt, src, dst, path, &len) : -1;
    printResult(updated ? "Updated Kruskal Path" : "Kruskal Path", cost, path, len);

    cost = pConnected ? pathInTree(n, pt, src, dst, path, &len) : -1;
    printResult(updated ? "Updated Prim Path" : "Prim Path", cost, path, len);
}

int main(void) {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Error: inpt.txt\n");
        return 1;
    }

    int n, m;
    fscanf(file, "%d %d", &n, &m);

    Edge *edges = malloc(sizeof(Edge) * (m > 0 ? m : 1));
    for (int i = 0; i < m; ++i) {
        fscanf(file, "%d %d %d", &edges[i].source, &edges[i].destination, &edges[i].weight);
        edges[i].idx = i;
    }

    int src, dst, ru, rv;
    fscanf(file, "%d %d", &src, &dst);
    fscanf(file, "%d %d", &ru, &rv);
    fclose(file);

    solve(n, edges, m, src, dst, -1, -1, false);

    printf("After Removing Edge (%d,%d):\n", ru, rv);
    solve(n, edges, m, src, dst, ru, rv, true);

    free(edges);
    return 0;
}
