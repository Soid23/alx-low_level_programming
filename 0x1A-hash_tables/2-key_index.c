#include "hash_tables.h"
/**
 * key_index - Get the index at which a key/value pair should be stored.
 * @key: The key to get index
 * @size: Size of array of hash table.
 * Return: Index of the key.
 * Descri: use djb2 algorithm.
 */
unsigned long int key_index(const unsigned char *key, unsigned long int size)
{
	return (hash_djb2(key) % size);
}
