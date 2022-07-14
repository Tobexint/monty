#include "monty.h"
/**
 * _add - adds top of stack and second top of stack
 *
 * @stack: pointer to linked list stack
 * @line_number: number of line opcode occurs on
 */
void _add(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->next == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		error_exit(stack);
	}
	(*stack)->next->n += (*stack)->n;
	_pop(stack, line_number);
}

/**
 * _nop - literally does nothing
 * @stack: pointer to the top of the stack
 * @line_number: the index of the current line
 *
 */
void _nop(__attribute__ ((unused))stack_t **stack,
	  __attribute__ ((unused))unsigned int line_number)
{

}
