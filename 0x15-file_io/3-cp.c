#include "main.h"

/**
 * exitWithError - print error code and message
 * @code: error code
 * @message: error string
 * @arg: string arguments
 * Return: void.
 */

void exitWithError(int code, const char *message, const char *arg)
{
	dprintf(STDERR_FILENO, message, arg);
	exit(code);
}

/**
 * main - copy a file to another and handle errors
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

    	int fd_from = open(argv[1], O_RDONLY);
    	if (fd_from == -1)
    	{
        	exitWithError(98, "Error: Can't read from file %s\n", argv[1]);
    	}

    	int fd_to = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0664);
    	if (fd_to == -1)
    	{
        	exitWithError(99, "Error: Can't write to %s\n", argv[2]);
    	}

    	char buffer[1024];
    	ssize_t bytes_read, bytes_written;

    	while ((bytes_read = read(fd_from, buffer, 1024)) > 0)
    	{
		bytes_written = write(fd_to, buffer, bytes_read);
        
		if (bytes_written == -1 || bytes_written != bytes_read)
        	{
			exitWithError(99, "Error: Can't write to %s\n", argv[2]);
        	}
    	}

    	if (bytes_read == -1)
    	{
		exitWithError(98, "Error: Can't read from file %s\n", argv[1]);
    	}

    	if (close(fd_from) == -1)
    	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_from);
        	exit(100);
    	}

    	if (close(fd_to) == -1)
    	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd_to);
                exit(100);
    	}

    	return 0;
}

