#include <stdint.h>
#include <stdio.h>

struct node {
  struct node* parent;
  int size;  
};

enum { max_nodes = 100000 };
struct node nodes[max_nodes];
int64_t sums[2][max_nodes];

void init() {
  for (int i = 0; i < max_nodes; i++) {
    nodes[i].parent = &nodes[i];
    nodes[i].size = 1;
  }
}

struct node* find(struct node* node) {
  while (node->parent != node) {
    struct node* parent = node->parent;
    node->parent = parent->parent;
    node = parent;
  }
  return node;
}

struct node* merge(struct node* l, struct node* r) {
  l = find(l);
  r = find(r);
  if (l == r) return l;
  // Rearrange such that l is the larger of the two.
  if (l->size < r->size) {
    struct node* temp = l;
    l = r;
    r = temp;
  }
  r->parent = l;
  l->size += r->size;
  return l;
}

int main() {
  init();
  
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    int a, b;
    char c;
    scanf("%d %d %c", &a, &b, &c);
    if (c == 'b') merge(&nodes[a - 1], &nodes[b - 1]);
  }
  // Remove all nodes which aren't roots.
  int j = 0;
  for (int i = 0; i < n; i++) {
    if (nodes[i].parent == &nodes[i]) {
      nodes[j].size = nodes[i].size;
      nodes[j].parent = &nodes[j];
      j++;
    }
  }
  const int num_clusters = j;
  // For each i in [0..num_clusters), compute the sum of sizes[i..num_clusters).
  sums[0][num_clusters] = 0;
  for (int i = num_clusters - 1; i >= 0; i--) {
    sums[0][i] = sums[0][i + 1] + nodes[i].size;
  }
  sums[1][num_clusters] = 0;
  for (int i = num_clusters - 1; i >= 0; i--) {
    sums[1][i] = sums[1][i + 1] + sums[0][i + 1] * nodes[i].size;
  }
  // Iterate over triplets of clusters and count the number of triplets that
  // can be constructed from that triplet of clusters.
  int64_t total = 0;
  for (int a = 0; a < num_clusters; a++) {
    total += sums[1][a + 1] * nodes[a].size;
  }
  printf("%dn", (int)(total % 1000000007));
}