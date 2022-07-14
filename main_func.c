#define _GNU_SOURCE
#include "monty.h"

void read_file(char *filename, stack_t **stack)
{
	char *buffer = NULL;
	char *line;
	size_t buf_size = 0;
	int line_count = 1;
	instruct_func s;
	int check;
	int read;
	FILE *file = fopen(filename, "r");

	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		error_exit(stack);
	}

	while ((read = getline(&buffer, &buf_size, file)) != -1)
	{
		line = get_cmd(buffer);
		if (line == NULL || line[0] == '#')
		{
			line_count++;
			continue;
		}

		s = exe_func(line);
		if (s == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n",line_count, line);
			error_exit(stack);
		}
		s(stack, line_count);
		line_count++;
	}
	free(buffer);
	check = fclose(file);
	if (check == -1)
		exit(-1);
}

/**
 * exe_func -  checks opcode and returns the correct function
 * @str: the opcode
 *
 * Return: returns a function, or NULL on failure
 */
instruct_func exe_func(char *str)
{
	int i = 0;
	instruction_t op_int[] = {
		{"push", _push},{"pall", _pall},
		{"pint", _pint}, {"pop", _pop},
		{"swap", _swap}, {"add", _add},
		{"nop", _nop}, {NULL, NULL},
	};

	while (op_int[i].f != NULL && strcmp(op_int[i].opcode, str) != 0)
		i++;
	return (op_int[i].f);

}

/**
 * get_cmd - parses a line for an opcode and arguments
 * @line: the line to be parsed
 *
 * Return: returns the opcode or null on failure
 */
char *get_cmd(char *line)
{
	char *op_code;
	op_code = strtok(line, "\n ");
	if (op_code == NULL)
		return (NULL);
	return (op_code);
}
