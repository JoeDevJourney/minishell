/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:36:03 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/14 15:54:22 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

bool	check_quotes(const char *input)
{
	bool	sq;
	bool	dq;
	bool	escape;

	sq = false;
	dq = false;
	escape = false;
	while (*input)
	{
		
	}
	return (sq || dq);
}

char	*process_quotes(char *input)
{
    char			*res;
    char			*dst;
    t_quote_state	state;

	res = malloc(ft_strlen(input) + 1);
	dst = res;
	state = init_quote_state();
	while (*input)
	{
		if (!state.sq && *input == '\\' && !state.escape)
		{
			if (state.dq || (!state.dq && !state.sq))
			{
				state.escape = true;
				input++;
				continue ;
			}
		}
		if (!state.escape)
		{
			if (*input == '\'' && !state.dq)
				state.sq = !state.sq;
			else if (*input == '"' && !state.sq)
				state.dq = !state.dq;
		}
		if ((state.sq && *input == '\\') || state.escape)
		{
			*dst++ = '\\';
			state.escape = false;
		}
		if (!((state.sq || state.dq) && (*input == '\'' || *input == '"')))
			*dst++ = *input;
		state.escape = (*input == '\\' && !state.escape && state.dq);
		input++;
	}
	*dst = '\0';
	return (res);
}

void	update_split_state(char c, t_split_state *state)
{
	if (state->escape)
	{
		state->escape = false;
		return ;
	}
	if (c == '\\' && !state->sq)
	{
		state->escape = true;
		return ;
	}
	if (c == '\'' && !state->dq)
		state->sq = !state->sq;
	if (c == '"' && !state->sq)
		state->dq = !state->dq;
}

t_list	*split_pipes(char *str)
{
	t_list			*list;
	t_split_state	state;

	list = NULL;
	init_split_state(&state, str);
	while (*state.ptr)
	{
		update_split_state(*state.ptr, &state);
		if (*state.ptr == '|' && !state.sq && !state.dq && !state.escape)
			add_command(&list, &state);
		state.ptr++;
	}
	add_command(&list, &state);
	return (list);
}

unsigned long	ft_strlen(const char str[])
{
	const char		*ptr;
	unsigned long	len;

	if (!str)
		return (0);
	ptr = str;
	len = 0;
	if (str)
	{
		while (*ptr)
		{
			len++;
			ptr++;
		}
	}
	return (len);
}


// int main() {
//     const char *input1 = "echo 'Hello World'";
//     const char *input2 = "echo \"Hello $USER\"";
//     const char *input3 = "echo 'This is a \\ test'";
//     const char *input4 = "echo \"This is a \\\" test\"";
//     const char *input5 = "echo \"Hello; World\"";
//     const char *input6 = "echo 'Unclosed quote";
//     const char *input7 = "echo \"Unclosed quote";

//     // Test 1
//     printf("Input: %s\n", input1);
//     if (check_quotes(input1)) {
//         printf("Error: Unclosed quotes detected.\n");
//     } else {
//         char *processed_input = process_quotes((char *)input1);
//         printf("Processed: %s\n", processed_input);
//         t_list *commands_list = split_pipes(processed_input);
//         t_list *tmp = commands_list;
//         while (tmp) {
//             printf("Command: %s\n", tmp->str);
//             tmp = tmp->next;
//         }
//         free(processed_input);
//         free_list(commands_list);
//     }
//     printf("\n");

//     // Test 2
//     printf("Input: %s\n", input2);
//     if (check_quotes(input2)) {
//         printf("Error: Unclosed quotes detected.\n");
//     } else {
//         char *processed_input = process_quotes((char *)input2);
//         printf("Processed: %s\n", processed_input);
//         t_list *commands_list = split_pipes(processed_input);
//         t_list *tmp = commands_list;
//         while (tmp) {
//             printf("Command: %s\n", tmp->str);
//             tmp = tmp->next;
//         }
//         free(processed_input);
//         free_list(commands_list);
//     }
//     printf("\n");

//     // Test 3
//     printf("Input: %s\n", input3);
//     if (check_quotes(input3)) {
//         printf("Error: Unclosed quotes detected.\n");
//     } else {
//         char *processed_input = process_quotes((char *)input3);
//         printf("Processed: %s\n", processed_input);
//         t_list *commands_list = split_pipes(processed_input);
//         t_list *tmp = commands_list;
//         while (tmp) {
//             printf("Command: %s\n", tmp->str);
//             tmp = tmp->next;
//         }
//         free(processed_input);
//         free_list(commands_list);
//     }
//     printf("\n");

//     // Test 4
//     printf("Input: %s\n", input4);
//     if (check_quotes(input4)) {
//         printf("Error: Unclosed quotes detected.\n");
//     } else {
//         char *processed_input = process_quotes((char *)input4);
//         printf("Processed: %s\n", processed_input);
//         t_list *commands_list = split_pipes(processed_input);
//         t_list *tmp = commands_list;
//         while (tmp) {
//             printf("Command: %s\n", tmp->str);
//             tmp = tmp->next;
//         }
//         free(processed_input);
//         free_list(commands_list);
//     }
//     printf("\n");

//     // Test 5
//     printf("Input: %s\n", input5);
//     if (check_quotes(input5)) {
//         printf("Error: Unclosed quotes detected.\n");
//     } else {
//         char *processed_input = process_quotes((char *)input5);
//         printf("Processed: %s\n", processed_input);
//         t_list *commands_list = split_pipes(processed_input);
//         t_list *tmp = commands_list;
//         while (tmp) {
//             printf("Command: %s\n", tmp->str);
//             tmp = tmp->next;
//         }
//         free(processed_input);
//         free_list(commands_list);
//     }
//     printf("\n");

//     // Test 6
//     printf("Input: %s\n", input6);
//     if (check_quotes(input6)) {
//         printf("Error: Unclosed quotes detected.\n");
//     } else {
//         char *processed_input = process_quotes((char *)input6);
//         printf("Processed: %s\n", processed_input);
//         t_list *commands_list = split_pipes(processed_input);
//         t_list *tmp = commands_list;
//         while (tmp) {
//             printf("Command: %s\n", tmp->str);
//             tmp = tmp->next;
//         }
//         free(processed_input);
//         free_list(commands_list);
//     }
//     printf("\n");

//     // Test 7
//     printf("Input: %s\n", input7);
//     if (check_quotes(input7)) {
//         printf("Error: Unclosed quotes detected.\n");
//     } else {
//         char *processed_input = process_quotes((char *)input7);
//         printf("Processed: %s\n", processed_input);
//         t_list *commands_list = split_pipes(processed_input);
//         t_list *tmp = commands_list;
//         while (tmp) {
//             printf("Command: %s\n", tmp->str);
//             tmp = tmp->next;
//         }
//         free(processed_input);
//         free_list(commands_list);
//     }
//     printf("\n");

//     return 0;
// }