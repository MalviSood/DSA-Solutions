#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

struct Node
{
    int64_t sum; // sum of all node in this tree.
    int64_t testSum;
    int data;
    int parent;
    int *child;
    int childCnt;
};
typedef struct Node Node;

void sumTree(Node *root, int index)
{
    int i;
    root[index].sum = root[index].data;
    for (i = 0; i < root[index].childCnt; i++)
    {
        int child = root[index].child[i];
        if (child == root[index].parent) continue;
        sumTree(root, child);
        root[index].sum += root[child].sum;
    }
    root[index].testSum = root[index].sum;
}

void updateTree(Node *tree, int root, int parent)
{
    tree[root].parent = parent;
    int i;
    for (i = 0; i < tree[root].childCnt; i++)
    {
        if (tree[root].child[i] == parent) continue;
        updateTree(tree, tree[root].child[i], root);
    }
}

int64_t childSum(Node *tree, int root, int  branch_root, int64_t targetSum, bool *bFound)
{
    int i;
    int64_t currSum = 0;

    if (tree[root].testSum < targetSum) return tree[root].testSum;

    for (i = 0; (i < tree[root].childCnt) && (*bFound==0); i++)
    {
        int child = tree[root].child[i];
        if (child == tree[root].parent) continue;
        if (child == branch_root) continue;
        int64_t chSum = childSum(tree, child, branch_root, targetSum, bFound);

        if (chSum == targetSum)
        {
            *bFound = 1;
            break;
        }

        currSum += chSum;
    }
    return currSum + tree[root].data;
}

// Complete the balancedForest function below.
int64_t balancedForest(int c_count, int* c, int edges_rows, int edges_columns, int** edges) {
    int i, j;
    // build tree.
    Node *tree = (Node *)calloc(c_count, sizeof(Node));
    for (i = 0; i < c_count; i++)
    {
        tree[i].data = c[i];
        tree[i].childCnt = 0;
        tree[i].child = NULL;
        tree[i].parent = -1;
        tree[i].sum = 0;
    }
    for (i = 0; i < edges_rows; i++)
    {
        int pa = edges[i][0] - 1;
        int ch = edges[i][1] - 1;
        tree[pa].child = (int *)realloc(tree[pa].child, (1 + tree[pa].childCnt) * sizeof(int));
        tree[pa].child[tree[pa].childCnt] = ch;
        tree[pa].childCnt++;
        tree[ch].child = (int *)realloc(tree[ch].child, (1 + tree[ch].childCnt) * sizeof(int));
        tree[ch].child[tree[ch].childCnt] = pa;
        tree[ch].childCnt++;
    }
    // Now update the parent_node;
    int root = 0; // pick the first one as root.
    updateTree(tree, root, -1);
    sumTree(tree, root);

    int64_t treeSum = 0;
    treeSum = tree[root].sum;
    
    int64_t maxSum = (treeSum - 1) / 2 + 1;
    int64_t minSum = treeSum / 3 - 1;
    int64_t minW = -1;
    for (i = 0; i < c_count; i++)
    {
        if (i == root) continue;

        //if (tree[i].sum >= minSum && tree[i].sum <= maxSum)
        {
            int64_t sumI = tree[i].sum;

            // Check for special case.
            int64_t sumJ = treeSum - sumI;

            if (sumI == sumJ)
            {
                if (minW<0 || minW>sumI) minW = sumI;
            }
            else
            {
                bool bFound = 0;
                int64_t targetSum;
                int searchRoot = root;
                int branchRoot = i;
                int64_t w = 0;
                if (sumI > sumJ)
                {
                    targetSum = sumI;
                    sumI = sumJ;
                    sumJ = targetSum;
                    searchRoot = i;
                    branchRoot = root;
                }
                if ((sumI << 1) < sumJ)
                {
                    targetSum = sumJ >> 1;
                    if (sumJ - targetSum != targetSum) continue;
                    w = targetSum - sumI;
                }
                else
                {
                    targetSum = sumI;
                    w = targetSum - (sumJ - sumI);
                }

                if (minW >= 0 && minW < w) continue;

                // search in the main tree
                
                // first, update the testSum;
                if (searchRoot == root)
                {
                    int curr = tree[branchRoot].parent;
                    int64_t branchSum = tree[branchRoot].sum;
                    while (curr != -1)
                    {
                        tree[curr].testSum -= branchSum;
                        curr = tree[curr].parent;
                    }
                }

                childSum(tree, searchRoot, branchRoot, targetSum, &bFound);
                if (bFound)
                {
                    if (minW == -1 || minW > w) minW = w;
                }

                // last, restore the testSum
                if (searchRoot == root)
                {
                    int curr = tree[branchRoot].parent;
                    while (curr != -1)
                    {
                        tree[curr].testSum = tree[curr].sum;
                        curr = tree[curr].parent;
                    }
                }
            }
        }
    }
    return minW;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char* q_endptr;
    char* q_str = readline();
    int q = strtol(q_str, &q_endptr, 10);

    if (q_endptr == q_str || *q_endptr != '') { exit(EXIT_FAILURE); }

    for (int q_itr = 0; q_itr < q; q_itr++) {
        char* n_endptr;
        char* n_str = readline();
        int n = strtol(n_str, &n_endptr, 10);

        if (n_endptr == n_str || *n_endptr != '') { exit(EXIT_FAILURE); }

        char** c_temp = split_string(readline());

        int* c = malloc(n * sizeof(int));

        for (int i = 0; i < n; i++) {
            char* c_item_endptr;
            char* c_item_str = *(c_temp + i);
            int c_item = strtol(c_item_str, &c_item_endptr, 10);

            if (c_item_endptr == c_item_str || *c_item_endptr != '') { exit(EXIT_FAILURE); }

            *(c + i) = c_item;
        }

        int c_count = n;

        int** edges = malloc((n - 1) * sizeof(int*));

        for (int i = 0; i < n - 1; i++) {
            *(edges + i) = malloc(2 * (sizeof(int)));

            char** edges_item_temp = split_string(readline());

            for (int j = 0; j < 2; j++) {
                char* edges_item_endptr;
                char* edges_item_str = *(edges_item_temp + j);
                int edges_item = strtol(edges_item_str, &edges_item_endptr, 10);

                if (edges_item_endptr == edges_item_str || *edges_item_endptr != '') { exit(EXIT_FAILURE); }

                *(*(edges + i) + j) = edges_item;
            }
        }

        int edges_rows = n - 1;
        int edges_columns = 2;

        int64_t result = balancedForest(c_count, c, edges_rows, edges_columns, edges);

        fprintf(fptr, "%lldn", result);
    }

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) {
            break;
        }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == 'n') {
            break;
        }

        alloc_length <<= 1;

        data = realloc(data, alloc_length);

        if (!line) {
            break;
        }
    }

    if (data[data_length - 1] == 'n') {
        data[data_length - 1] = '';

        data = realloc(data, data_length);
    } else {
        data = realloc(data, data_length + 1);

        data[data_length] = '';
    }

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);

        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}