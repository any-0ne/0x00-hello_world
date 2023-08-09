#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define ELF_MAGIC_SIZE 16

/**
 * Elf64_Ehdr - Typedef for struct Elf64
 */

typedef struct Elf64_Ehdr Elf64_Ehdr;

/**
 * struct Elf64_Ehdr - struct that stores ELF informations
 * @e_ident: store ident
 * @e_type: store type
 * @e_machine: store machine
 *
 * Description:  stores ELF informations.
 */

struct Elf64_Ehdr
{
	unsigned char e_ident[ELF_MAGIC_SIZE];
	uint16_t e_type;
	uint16_t e_machine;
	uint32_t e_version;
	uint64_t e_entry;
	uint64_t e_phoff;
	uint64_t e_shoff;
	uint32_t e_flags;
	uint16_t e_ehsize;
	uint16_t e_phentsize;
	uint16_t e_phnum;
	uint16_t e_shentsize;
	uint16_t e_shnum;
	uint16_t e_shstrndx;
};

/**
 * exitWithError - print error message and exit with code
 * @message: string error
 * Return: void.
 */

void exitWithError(const char *message)
{
	dprintf(STDERR_FILENO, "Error: %s\n", message);
	exit(98);
}

/**
 * print_elf_header - peint ELF information
 * @header: Elf64 struct to print
 * Return: void.
 */

void print_elf_header(const Elf64_Ehdr *header)
{
	unsigned char osabi = header->e_ident[7];
	int i;
	
	printf("  Magic:   ");
	for (i = 0; i < ELF_MAGIC_SIZE; ++i)
	{
		printf("%02x ", header->e_ident[i]);
	}

	printf("\n");

	printf("  Class:                             ");
	switch (header->e_ident[4])
	{
		case 1:
			printf("ELF32\n");
			break;
		case 2:
			printf("ELF64\n");
			break;
		default:
			printf("<unknown: %02x>\n", header->e_ident[4]);
	}

	printf("  Data:                              ");
	switch (header->e_ident[5])
	{
		case 1:
			printf("2's complement, little endian\n");
			break;
		case 2:
			printf("2's complement, big endian\n");
			break;
		default:
			printf("<unknown: %02x>\n", header->e_ident[5]);
	}

	printf("  Version:                           %d (current)\n", header->e_ident[6]);

	printf("  OS/ABI:                            ");
	
	if (osabi == 0)
		printf("UNIX - System V\n");
	else if (osabi == 2)
		printf("UNIX - NetBSD\n");
	else if (osabi == 6)
		printf("UNIX - Solaris\n");
	else
		printf("<unknown: %x>\n", osabi);

	printf("  ABI Version:                       %d\n", header->e_ident[8]);

	printf("  Type:                              ");
	switch (header->e_type)
	{
		case 1:
			printf("REL (Relocatable file)\n");
			break;
		case 2:
			printf("EXEC (Executable file)\n");
			break;
		case 3:
			printf("DYN (Shared object file)\n");
			break;
		case 4:
			printf("CORE (Core file)\n");
			break;
		default:
			printf("<unknown: %04x>\n", header->e_type);
	}

	printf("  Entry point address:               0x%lx\n", (unsigned long) header->e_entry);
}

/**
 * main - main function for checking file and print ELF info
 * @argc: argument count
 * @argv: argument vector
 * Return: if SUCCESS 0, if not ERROR CODE.
 */

int main(int argc, char *argv[])
{
	int fd;
	ssize_t bytes_read;
	Elf64_Ehdr header;

	if (argc != 2)
	{
		dprintf(STDERR_FILENO, "Usage: %s elf_filename\n", argv[0]);
		return (98);
	}

	fd = open(argv[1], O_RDONLY);

	if (fd == -1)
	{
		exitWithError("Could not open the file");
	}

	bytes_read = read(fd, &header, sizeof(header));
	if (bytes_read != sizeof(header))
	{
		close(fd);
		exitWithError("Error reading ELF header");
	}

	if (memcmp(header.e_ident, "\x7f\x45\x4c\x46", 4) != 0)
	{
		close(fd);
		exitWithError("Not an ELF file");
	}

	close(fd);

	print_elf_header(&header);

	return (0);
}
