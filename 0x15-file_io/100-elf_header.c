#include "main.h"
#include <elf.h>

void print_magic(const Elf64_Ehdr *header);
void print_class(const Elf64_Ehdr *header);
void print_data(const Elf64_Ehdr *header);
void print_version(const Elf64_Ehdr *header);
void print_os_abi(const Elf64_Ehdr *header);
void print_abi_version(const Elf64_Ehdr *header);
void print_type(const Elf64_Ehdr *header);
void print_entry_point(const Elf64_Ehdr *header);
int is_elf_file(const char *filename);

/**
 * print_magic - Print the magic number of the ELF header.
 * @header: Pointer to the ELF header structure.
 */
void print_magic(const Elf64_Ehdr *header)
{
	int i;

	printf("  Magic:\t");
	for (i = 0; i < EI_NIDENT; i++)
	{
		printf("%02x", header->e_ident[i]);
		if (i < EI_NIDENT - 1)
			printf(" ");
	}
	printf("\n");
}

/**
 * print_class - Print the class of the ELF header.
 * @header: Pointer to the ELF header structure.
 */
void print_class(const Elf64_Ehdr *header)
{
	printf("Class:\t\t\t");
	switch (header->e_ident[EI_CLASS])
	{
	case ELFCLASS32:
		printf("ELF32\n");
		break;
	case ELFCLASS64:
		printf("ELF64\n");
		break;
	default:
		printf("<unknown>\n");
	}
}

/**
 * print_data - Print the data encoding of the ELF header.
 * @header: Pointer to the ELF header structure.
 */
void print_data(const Elf64_Ehdr *header)
{
	printf("Data:\t\t\t");
	switch (header->e_ident[EI_DATA])
	{
	case ELFDATA2LSB:
		printf("2's complement, little endian\n");
		break;
	case ELFDATA2MSB:
		printf("2's complement, big endian\n");
		break;
	default:
		printf("<unknown>\n");
	}
}

/**
 * print_version - Print the version of the ELF header.
 * @header: Pointer to the ELF header structure.
 */
void print_version(const Elf64_Ehdr *header)
{
	printf("Version:\t\t%u (current)\n", header->e_ident[EI_VERSION]);
}

/**
 * print_os_abi - Print the OS/ABI of the ELF header.
 * @header: Pointer to the ELF header structure.
 */
void print_os_abi(const Elf64_Ehdr *header)
{
	printf("OS/ABI:\t\t");
	switch (header->e_ident[EI_OSABI])
	{
	case ELFOSABI_SYSV:
		printf("UNIX - System V\n");
		break;
	case ELFOSABI_NETBSD:
		printf("UNIX - NetBSD\n");
		break;
	case ELFOSABI_SOLARIS:
		printf("UNIX - Solaris\n");
		break;
	case ELFOSABI_LINUX:
		printf("UNIX - Linux\n");
		break;
	default:
		printf("<unknown: %u>\n", header->e_ident[EI_OSABI]);
	}
}

/**
 * print_abi_version - Print the ABI version of the ELF header.
 * @header: Pointer to the ELF header structure.
 */
void print_abi_version(const Elf64_Ehdr *header)
{
	printf("ABI Version:\t\t%u\n", header->e_ident[EI_ABIVERSION]);
}

/**
 * print_type - Print the type of the ELF header.
 * @header: Pointer to the ELF header structure.
 */
void print_type(const Elf64_Ehdr *header)
{
	printf("Type:\t\t\t");
	switch (header->e_type)
	{
	case ET_EXEC:
		printf("EXEC (Executable file)\n");
		break;
	case ET_DYN:
		printf("DYN (Shared object file)\n");
		break;
	default:
		printf("<unknown>\n");
	}
}

/**
 * print_entry_point - Print the entry point address of the ELF header.
 * @header: Pointer to the ELF header structure.
 */
void print_entry_point(const Elf64_Ehdr *header)
{
	printf("Entry point address:\t0x%lx\n", (unsigned long)header->e_entry);
}

/**
 * is_elf_file - Check if the given file is an ELF file.
 * @filename: Name of the file to check.
 *
 * Return: 1 if the file is an ELF file, 0 otherwise.
 */
int is_elf_file(const char *filename)
{
	int fd;
	ssize_t bytes_d;
	Elf64_Ehdr header;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (0);
	}

	bytes_d = read(fd, &header, sizeof(header));
	if (bytes_d == -1)
	{
		perror("read");
		close(fd);
		return (0);
	}

	if (bytes_d != sizeof(header) || memcmp(header.e_ident, ELFMAG, SELFMAG) != 0)
	{
		close(fd);
		return (0);
	}

	close(fd);
	return (1);
}

/**
 * main - Entry point of the program.
 * @argc: Number of command-line arguments.
 * @argv: Array of command-line argument strings.
 *
 * Return: 0 on success, 98 on error.
 */
int main(int argc, char *argv[])
{
	const char *filename;
	int fd;
	ssize_t bytes_read;
	Elf64_Ehdr header;

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
		return (98);
	}

	filename = argv[1];

	if (!is_elf_file(filename))
	{
		fprintf(stderr, "%s is not an ELF file\n", filename);
		return (98);
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return (98);
	}

	bytes_read = read(fd, &header, sizeof(header));
	if (bytes_read == -1)
	{
		perror("read");
		close(fd);
		return (98);
	}

	print_magic(&header);
	print_class(&header);
	print_data(&header);
	print_version(&header);
	print_os_abi(&header);
	print_abi_version(&header);
	print_type(&header);
	print_entry_point(&header);

	close(fd);
	return (0);
}
