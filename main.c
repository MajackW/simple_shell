#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <sys/types.h>
#include "main.h"

/**
 * main - entry point
 * Return: integer
 */
int main(void)
{
	size_t len;
	int n;
	ssize_t t;
	char *line;

	while (1)
	{
		printf("$ ");
		t = getline(&line, &len, stdin);
		if (t == -1)
		{
			printf("error reading line\n");
			free(line);
			exit(98);
		}
		n = strcmp(line, "exit\n");
		if (n == 0)
		{
			printf("exit\n");
			free(line);
			exit(98);
		}
		exe(line);
	}
	free(line);
	return (0);
}
/**
 * exe - executes command
 * @com: command to execute
 * Return: void
 */
void exe(char *com)
{
	pid_t c;
	char *com1;
	const char *argv[] = {"/bin/sh", "-c", NULL, NULL};
	const char *env[] = {NULL};
	int status;

	com1 = com;

	while (1)
	{
		if (*com1 == '\n')
		{
			*com1 = '\0';
			break;
		}
		com1++;
	}
	c = fork();
	if (c == 0)
	{
		argv[2] = com;
		if (execve("/bin/sh", (char *const *)argv, (char *const *)env) == -1)
		{
			perror("main");
			exit(EXIT_FAILURE);
		}
	}
	else if (c < 0)
		perror("main");
	else
	{
		wait(&status);
	}
	return;

}
