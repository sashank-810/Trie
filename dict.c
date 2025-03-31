#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dictio.h"

// Function to create a new trie node
trie_node *make_trie_node() {
    trie_node *node = (trie_node *)malloc(sizeof(trie_node));
    if (node) {
        node->is_end_of_word = 0;
        node->value = 0;
        memset(node->children, 0, sizeof(node->children));
    }
    return node;
}

// Create an empty Dict (Trie)
Dict make_dict() {
    trie_dict *dict = (trie_dict *)malloc(sizeof(trie_dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->root = make_trie_node();
    if (dict->root == NULL) {
        free(dict);
        return NULL;
    }
    return (Dict)dict;
}

// Recursive helper function to free all nodes in the trie
void free_trie_node(trie_node *node) {
    if (node == NULL) return;

    // Free all children
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (node->children[i] != NULL) {
            free_trie_node(node->children[i]);
        }
    }
    // Free the current node
    free(node);
}

// Free all memory allocated to a Dict (Trie)
void free_dict(Dict dict_adt) {
    if (dict_adt == NULL) return;
    trie_dict *dict = (trie_dict *)dict_adt;
    free_trie_node(dict->root);
    free(dict);
}

// Get a pointer to the value associated with key (returns NULL if not found)
int *get(Dict dict_adt, const char *key) {
    if (dict_adt == NULL || key == NULL) return NULL;

    trie_dict *dict = (trie_dict *)dict_adt;
    trie_node *node = dict->root;

    // Traverse the trie character by character
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';  // Get the index for the character
        if (node->children[index] == NULL) {
            return NULL;  // Key not found
        }
        node = node->children[index];
    }

    // Check if the key marks the end of a word
    if (node != NULL && node->is_end_of_word) {
        return &node->value;  // Return pointer to the value
    }
    return NULL;
}

// Set the value associated with key (returns 1 if successful, 0 if allocation fails)
int set(Dict dict_adt, const char *key, int value) {
    if (dict_adt == NULL || key == NULL) return 0;

    trie_dict *dict = (trie_dict *)dict_adt;
    trie_node *node = dict->root;

    // Traverse the trie, creating nodes as necessary
    for (int i = 0; key[i] != '\0'; i++) {
        int index = key[i] - 'a';  // Get the index for the character

        // If no child exists for the character, create a new trie node
        if (node->children[index] == NULL) {
            node->children[index] = make_trie_node();
            if (node->children[index] == NULL) {
                return 0;  // Memory allocation failed
            }
        }
        node = node->children[index];
    }

    // Mark the end of the word and set the value
    node->is_end_of_word = 1;
    node->value = value;
    return 1;
}

// Recursive helper to print the contents of the trie
void print_trie(trie_node *node, char *prefix, int length) {
    if (node == NULL) return;

    // If the current node is the end of a word, print the key-value pair
    if (node->is_end_of_word) {
        prefix[length] = '\0';  // Null-terminate the string
        printf("%s: %d\n", prefix, node->value);
    }

    // Recurse for all possible children
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        trie_node *child = node->children[i];
        if (child != NULL) {
            prefix[length] = 'a' + i;  // Add the character to the prefix
            print_trie(child, prefix, length + 1);
        }
    }
}

// Print the contents of the dictionary
void print_dict(Dict dict_adt) {
    if (dict_adt == NULL) return;

    trie_dict *dict = (trie_dict *)dict_adt;
    char prefix[MAX_KEY_LENGTH + 1];  // Buffer to hold the key during recursion
    print_trie(dict->root, prefix, 0);
}