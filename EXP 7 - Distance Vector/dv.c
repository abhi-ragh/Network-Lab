#include <stdio.h>

struct node {
    unsigned dist[20];
    unsigned from[20];
} rt[10];

int main() {
    int costmat[20][20];
    int nodes, i, j, k, count = 0;

    printf("\nEnter The Number of nodes: \n");
    scanf("%d", &nodes);

    // Inputting the cost matrix and initializing routing table
    for (i = 0; i < nodes; i++) {
        for (j = 0; j < nodes; j++) {
            printf("\nEnter The Cost Matrix [%d][%d]: ", i, j);
            scanf("%d", &costmat[i][j]);
            rt[i].dist[j] = costmat[i][j];
            rt[i].from[j] = j;
        }
    }

    // Distance Vector Algorithm
    do {
        count = 0;
        for (i = 0; i < nodes; i++) {     // for each node i
            for (j = 0; j < nodes; j++) { // for each node j
                for (k = 0; k < nodes; k++) { // for each node k
                    if (rt[i].dist[j] > costmat[i][k] + costmat[k][j]) {
                        rt[i].dist[j] = costmat[i][k] + costmat[k][j];
                        rt[i].from[j] = k;
                        count++;
                    }
                }
            }
        }
    } while (count != 0);

    // Printing the routing table
    for (i = 0; i < nodes; i++) {
        printf("\n\nfor router %d\n", i + 1);
        for (j = 0; j < nodes; j++) {
            printf("\tnode %d via %d distance %d\n", j + 1, rt[i].from[j] + 1, rt[i].dist[j]);
        }
    }

    printf("\n");

    return 0;
}
