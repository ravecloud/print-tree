#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define QUEUE_SIZE 1000

typedef struct Node {
  int value;
  struct Node *right;
  struct Node *left;
} Node;


// Create a new node
Node* create_node(int value) {
  Node *new_node = (Node*)malloc(sizeof(Node));
  if(!new_node) {
    perror("Memory allocation failed");
    exit(EXIT_FAILURE);
  }
  new_node->value = value;
  return new_node;
}

// Allocate array of node for a given level
Node** allocate_level_array(int level) {
  size_t size = (size_t)pow(2, level); // Calculate 2^level
  return (Node**)malloc(size * sizeof(Node*));
}


void store_level_nodes_w_queue(Node* root) {
  if(!root) return;

  // allocate the memory for enough pointers
  Node** queue = malloc(QUEUE_SIZE * sizeof(Node*));
  if(!queue) {
    perror("Queue allocation failed!\n");
    exit(EXIT_FAILURE);
  }

  size_t front = 0, rear = 0; // Front and rear of queues

  // Enqueue the root node
  queue[rear++] = root;

  int level = 0;
  while(front < rear && rear < QUEUE_SIZE) {
    size_t level_size = rear - front;
    printf("Level %d: ", level);

    for(size_t i = 0; i < level_size; i++) {
      Node* current = queue[front++]; // Dequeue the front node
      
      printf("%d ", current->value);

      // enqueue if the node has children
      if(current->left) queue[rear++] = current->left;
      if(current->right) queue[rear++] = current->right;
    }

    printf("\n");
    level++;
  }

  // Free the queeu memory
  free(queue);


}

// Example tree traversal to demonstarte level storage
void store_level_nodes(Node* root) {
  if(!root) return;

  int level = 0;
  Node** current_level = allocate_level_array(level);
  current_level[0] = root;
  printf("Level %d: %d\n", level, current_level[0]->value);
  
  while(1) {
    size_t num_nodes = (size_t)pow(2, level);
    Node** next_level = allocate_level_array(level + 1);
    size_t count = 0;

    for (size_t i = 0; i < num_nodes; i++) {
      if(!current_level[i]) break;
      if(current_level[i]->left) {
        next_level[count++] = current_level[i]->left;
      }
    
      if(current_level[i]->right) {
        next_level[count++] = current_level[i]->right;
      }
    }

    // If no nodes are added, break the loop
    if(count == 0) {
      free(next_level);
      break;
    }

    // Print the next level
    printf("Level %d: ", level + 1);
    for(size_t i = 0; i < count; i++) {
      printf("%d ", next_level[i]->value);
    }
    printf("\n");

    // Free the current level and move to the next level
    free(current_level);
    current_level = next_level;
    level++;

  }

  return;

}

int main() {
  Node *root = create_node(1);
  root->left = create_node(2);
  root->right = create_node(3);
  root->left->left = create_node(4);
  root->left->right = create_node(5);
  root->right->right = create_node(6);

  store_level_nodes(root);
  store_level_nodes_w_queue(root);

  // Free the tree nodes
  free(root->left->left);
  free(root->left->right);
  free(root->left);
  free(root->right->right);
  free(root->right);
  free(root);

  return 0;
}
