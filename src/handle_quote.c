/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:31:11 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/24 14:09:14 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	check_quotes(const char *input)
{
	t_quote_state	state;

	state = init_quote_state();
	while (*input)
	{
		if (state.escape)
		{
			state.escape = false;
			input++;
			continue ;
		}
		if (*input == '\\' && state.dq)
			state.escape = true;
		else if (*input == '\'' && !state.dq)
			state.sq = !state.sq;
		else if (*input == '"' && !state.sq)
			state.dq = !state.dq;
		input++;
	}
	return (state.sq || state.dq);
}

static void	handle_escape(const char **input, char **dst, t_quote_state *state)
{
	if (state->escape)
	{
		**dst = **input;
		(*dst)++;
		(*input)++;
		state->escape = false;
	}
	else if (**input == '\\' && (state->dq || state->sq))
	{
		state->escape = true;
		**dst = **input;
		(*dst)++;
		(*input)++;
	}
}

static void	handle_quotes(const char **input, char **dst, t_quote_state *state)
{
	while (**input)
	{
		handle_escape(input, dst, state);
		if (**input == '\'' && !state->dq)
		{
			state->sq = !state->sq;
			(*input)++;
			continue ;
		}
		if (**input == '"' && !state->sq)
		{
			state->dq = !state->dq;
			(*input)++;
			continue ;
		}
		**dst = **input;
		(*dst)++;
		(*input)++;
	}
	**dst = '\0';
}

void	process_quotes(t_data *inp)
{
	const char		*input;
	char			*dst;
	t_quote_state	state;
	size_t			input_len;

	input = *inp->pipe.cmd;
	state = init_quote_state();
	input_len = ft_strlen(input);
	if (check_quotes(input))
	{
		printf("Error: Quote still open.\n");
		return ;
	}
	inp->input = malloc(input_len + 1);
	if (inp->input == NULL)
	{
		printf("malloc fail.\n");
		return ;
	}
	dst = inp->input;
	printf("Processing quotes for: %s\n", input);
	handle_quotes(&input, &dst, &state);
}

// void process_quotes_bash_like(t_data *inp) {
//     const char *input = *inp->pipe.cmd;
//     char *dst;
//     t_quote_state state = init_quote_state();
//     size_t input_len = ft_strlen(input);
//
//     if (check_quotes(input)) {
//         printf("Error: Unclosed quote detected.\n");
//         return;
//     }
//
//     inp->input = malloc(input_len + 1);
//     if (!inp->input) {
//         printf("Malloc failed.\n");
//         return;
//     }
//
//     dst = inp->input;
//     while (*input) {
//         if (state.escape) {
//             *dst++ = *input++;
//             state.escape = false;
//             continue;
//         }
//         if (*input == '\\' && !state.sq) {
//             state.escape = true;
//             input++;
//             continue;
//         }
//         if (*input == '\'' && !state.dq) {
//             state.sq = !state.sq;
//             input++;
//             continue;
//         }
//         if (*input == '"' && !state.sq) {
//             state.dq = !state.dq;
//             input++;
//             continue;
//         }
//         *dst++ = *input++;
//     }
//     *dst = '\0';
// }

// int main() {
//     const char *inputs[] = {
//         "echo '\"HELLOUSER\"'",
//         "echo 'Hello ''$USER'''",
//         "echo 'This is a \\ test'",
//         "echo \"This is a \\\" test\"",
//         "echo \"Hello; World\"",
//         "echo 'Unclosed quote''",
//         "echo \"Unclosed quote\"'",
//         "echo \"This is a \\ backslash\"",
//         "echo 'This is a \\ backslash'",
//         "echo \"Closed quote with escape \\\"\"",
//         "echo 'Closed quote with escape \\",
//         "echo \"Outer \\\"Inner\\\"\"",
//         "echo '\"$USER\"'",
//         "echo '\"'\"$USER\"'\"'"
//     };
//
//     size_t input_count = sizeof(inputs) / sizeof(inputs[0]);
//     t_data data;
//     for (size_t i = 0; i < input_count; i++) {
//         printf("Input: %s\n", inputs[i]);
//
//         char *cmd[] = {(char *)inputs[i], NULL};
//         data.pipe.cmd = cmd;
//         data.pipe.num_cmd = 1;
//
//         if (check_quotes(inputs[i])) {
//             printf("Error: Unclosed quotes detected.\n");
//         } else {
//             process_quotes_bash_like(&data);
//             printf("Processed: %s\n", data.input);
//             printf("Bash Output: ");
//             fflush(stdout);
//             system(inputs[i]);
//             printf("\n");
//             free(data.input);
//         }
//         printf("\n");
//     }
//     return 0;
// }
