#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define BUFFER_SIZE 1024

/* exitWithError - print error code and message
 * @code: error code
 * @arg: error string
 * Return: void.
 */

void exitWithError(int code, const char *message, const char *arg)
{
	dprintf(STDERR_FILENO, message, arg);
	exit(code);
}

/* main - copy a file to another and handle errors
 * @argc: arguments counter
 * @argv: arguments vector
 * Return: if SUCCESS 0, if not error code.
 */

int main(int argc, char *argv[])
{
	if (argc != 3)
    	{
        	exitWithError(97, "Usage: cp file_from file_to\n", "");
    	}

    	const char *file_from = argv[1];
    	const char *file_to = argv[2];

    	int fd_from = open(file_from, O_RDONLY);
    	if (fd_from == -1)
    	{
        	exitWithError(98, "Error: Can't read from file %s\n", file_from);
    	}

    	int fd_to = open(file_to, O_WRONLY | O_CREAT | O_TRUNC, 0664);
    	if (fd_to == -1)
    	{
        	exitWithError(99, "Error: Can't write to %s\n", file_to);
    	}

    	char buffer[BUFFER_SIZE];
    	ssize_t bytes_read, bytes_written;

    	while ((bytes_read = read(fd_from, buffer, BUFFER_SIZE)) > 0)
    	{
		bytes_written = write(fd_to, buffer, bytes_read);
        
		if (bytes_written == -1 || bytes_written != bytes_read)
        	{
			exitWithError(99, "Error: Can't write to %s\n", file_to);
        	}
    	}

    	if (bytes_read == -1)
    	{
		exitWithError(98, "Error: Can't read from file %s\n", file_from);
    	}

    	if (close(fd_from) == -1)
    	{
		sprintf(buffer, "%i", fd_from);
	    	exitWithError(100, "Error: Can't close fd %s\n", buffer);
    	}

    	if (close(fd_to) == -1)
    	{
		sprintf(buffer, "%i", fd_to);
	    	exitWithError(100, "Error: Can't close fd %s\n", buffer);
    	}

    	return 0;
}

