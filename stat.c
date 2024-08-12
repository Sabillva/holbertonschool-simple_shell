#include <stdio.h>
#include <sys/stat.h>
/**
 * main - Entry point for checking file existence
 * @argc: Argument count
 * @argv: Argument vector (array of arguments)
 *
 * Return: 0 on success, 1 on failure
 */
int main(int argc, char **argv)
{
	struct stat st;

	if (argc < 2)
	{
		fprintf(stderr, "Usage %s <file>\n", argv[0]);
		return (1);
	}
	if (stat(argv[1], &st) == 0)
	{
		printf("File exists\n");
	}
	else
	{
		perror("stat");
	}
	return (0);
}
