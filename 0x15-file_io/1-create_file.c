#include "main.h"

/**
 * create_file - create a text file with content
 * @filename: filename
 * @text_content: text to add to the file
 * Return: 1 on success, -1 on failure.
 */

int create_file(const char *filename, char *text_content)
{
	int fd;
	int letters;
	int WR_RETURN;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);

	if (fd == -1)
		return (-1);

	if (!text_content)
		return (1);

	for (letters = 0; text_content[letters]; letters++);

	WR_RETURN = write(fd, text_content, letters);

	if (WR_RETURN == -1)
		return (-1);

	close(fd);

	return (1);
}
