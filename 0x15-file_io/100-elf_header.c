#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#define ELF_MAGIC_SIZE 16

typedef struct
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
}

Elf64_Ehdr;

void exitWithError(const char *message)
{
	fprintf(stderr, "Error: %s\n", message);
	exit(98);
}

void print_elf_header(const Elf64_Ehdr *header)
{
	printf("  Magic:   ");
	for (int i = 0; i < ELF_MAGIC_SIZE; ++i)
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
	unsigned char osabi = header->e_ident[7];
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

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s elf_filename\n", argv[0]);
		return (98);
	}

	const char *filename = argv[1];
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		exitWithError("Could not open the file");
	}

	Elf64_Ehdr header;
	ssize_t bytes_read = read(fd, &header, sizeof(header));
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
