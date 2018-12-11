#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include "get_next_line.h"

int main(int argc, char **argv)
{
	int fd;
	// int fd2;
	char *line;
	int res;
	int count_lines;

	printf("test 1: %lu\n", sizeof(char*));
	printf("test 2: %lu + %lu\n", sizeof(t_list), sizeof(t_rest_fd));

	if (argc > 1)
	{
		count_lines = 0;
		
		// system("mkdir -p sandbox");
		// system("openssl rand -base64 $((30 * 1000 * 3/4)) | tr -d '\n' | tr -d '\r' > sandbox/one_big_fat_line.txt");
		// system("echo '\n' >> sandbox/one_big_fat_line.txt");

		// fd = open("sandbox/one_big_fat_line.txt", O_RDONLY);
		// fd2 = open("sandbox/one_big_fat_line.txt.mine", O_CREAT | O_RDWR | O_TRUNC, 0755);

		// while (get_next_line(fd, &line) == 1)
		// {
		// 	write(fd2, line, strlen(line));
		// 	write(fd2, "\n", 1);
		// }
		// if (line)
		// 	write(fd2, line, strlen(line));
		// close(fd);
		// close(fd2);

		if ((fd = open(argv[1], O_RDONLY)) != -1)
		{
			while ((res = get_next_line(fd, &line)) > 0)
			{
				printf("%s\n", line);
				count_lines++;
			}
			printf("%d\n", count_lines);
		}
		close(fd);
	}
}
