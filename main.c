#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int fd;
	char *line;
	int res;

	if (argc > 1)
	{
		if ((fd = open(argv[1], O_RDONLY)) != -1)
		{
			while ((res = get_next_line(fd, &line) != -1))
			{
				printf("%s\n", line);
				if (res == 0)
					break ;
			}
		}
		close(fd);
	}
}
