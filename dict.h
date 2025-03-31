#ifndef DICT_H
#define DICT_H
#include "dict_adt.h"
#define ALPHABET_SIZE 26  // Number of lowercase English letters

// Structure representing a trie node
typedef struct trie_node {
    struct trie_node *children[ALPHABET_SIZE];  // Pointers to child nodes
    int is_end_of_word;                         // Marks the end of a key
    int value;                                  // Stores value if it's a valid key
} trie_node;

// Structure representing the dictionary (Trie-based)
typedef struct trie_dict {
    trie_node *root;  // Root of the trie
} trie_dict;

#endif