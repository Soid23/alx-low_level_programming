#include "main.h"

/**
 * read_textfile - reads a text file and prints it to stdout.
 * @filename: pointer to file to read.
 * @letters: no of letters to read.
 * Return: actual number of files read or 0 if failure.
 */

ssize_t read_textfile(const char *filename, size_t letters)
{
	char *buffer;
	ssize_t pfile;
	ssize_t nbletters;
	ssize_t x;

	pfile = open(filename, O_RDONLY);
	if (pfile == -1)
		return (0);

	buffer = malloc(sizeof(char) * letters);
	x = read(pfile, buffer, letters);
	nbletters = write(STDOUT_FILENO, buffer, x);
	free(buffer);
	close(pfile);
	return (nbletters);
}
