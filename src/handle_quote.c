/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:31:11 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/24 21:53:53 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static t_quote_state	init_quote_state(void)
{
	return ((t_quote_state){false, false, false, true, true});
}

static bool	check_quotes(t_data *inp)
{
	int	i;

	inp->quotes = init_quote_state();
	i = -1;
	while (inp->pipe.cmd[0][++i])
	{
		if (inp->quotes.escape)
		{
			inp->quotes.escape = false;
			continue ;
		}
		if (inp->pipe.cmd[0][i] == '\\' && inp->quotes.dq)
			inp->quotes.escape = true;
		else if (inp->pipe.cmd[0][i] == '\'' && !inp->quotes.dq)
			inp->quotes.sq = !inp->quotes.sq;
		else if (inp->pipe.cmd[0][i] == '"' && !inp->quotes.sq)
			inp->quotes.dq = !inp->quotes.dq;
	}
	return (inp->quotes.sq || inp->quotes.dq);
}

// static void	handle_escape(char **input, t_quote_state *state)
// {
// 	if (state->escape)
// 	{
// 		(*input)++;
// 		state->escape = false;
// 	}
// 	else if (**input == '\\' && (state->dq || state->sq))
// 	{
// 		state->escape = true;
// 		(*input)++;
// 	}
// }

static void	handle_quotes(char **input, t_quote_state *state)
{
	char 	*temp1;
	char	*temp;
	char	*res;
	int		start;
	int		end;

	start = -1;
	temp = ft_strdup(input[0]);
	free(input[0]);
	input[0] = NULL;
	temp1 = NULL;
	res = NULL;
	while (temp[++start])
	{
		// handle_escape(input, state);
		// if (temp[start] == '\'' && !state->dq)
		// {
		// 	state->sq = !state->sq;
		// 	continue ;
		// }
		if (temp[start] == '\'' && !state->dq)
		{
			end = start + 1;
			while (temp[end] != '\'')
				end++;
			if (res)
				free(res);
			res = ft_substr(temp, start + 1, end - start - 1);
			if (input[0])
				temp1 = ft_strdup(input[0]);
			else
				temp1 = ft_strdup("");
			free(input[0]);
			input[0] = ft_strjoin(temp1, res);
			free(temp1);
			start = end;
			state->dq = !state->dq;
		}
		if (temp[start] == '"' && !state->sq)
		{
			end = start + 1;
			while (temp[end] != '"')
				end++;
			if (res)
				free(res);
			res = ft_substr(temp, start + 1, end - start - 1);
			state->dq = !state->dq;
			if (input[0])
				temp1 = ft_strdup(input[0]);
			else
				temp1 = ft_strdup("");
			free(input[0]);
			input[0] = ft_strjoin(temp1, res);
			free(temp1);
			start = end;
		}
	}
}

void	process_quotes(t_data *inp)
{
	inp->quotes = init_quote_state();
	if (check_quotes(inp))
	{
		printf("Error: Quote still open.\n");
		return ;
	}
	printf("Processing quotes for: %s\n", *inp->pipe.cmd);
	handle_quotes(inp->pipe.cmd, &inp->quotes);
}

int	main()
{
	t_data	inp;

	inp.pipe.cmd = safe_malloc(2 * sizeof(char *));
	inp.pipe.cmd[0] = ft_strdup("\"Hello World\" 'single '");
	inp.pipe.cmd[1] = NULL;
	process_quotes(&inp);
	printf("Result: '%s'\n", *inp.pipe.cmd);
}

// cc handle_quote.c utils/*.c ../include/libft/src/*.c -o handle_quote -Wall -Werror -Wextra -lreadline -g


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
