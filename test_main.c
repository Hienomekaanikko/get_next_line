#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

//compile with  cc -D BUFFER_SIZE=42(or anything) get_next_line.c get_next_line_utils.c test_main.c -o test
int main(int argc, char **argv)
{
	int		fd = open(argv[1], O_RDONLY);
	char	*line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return 0;
}
