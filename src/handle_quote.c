/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 14:31:11 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/25 19:04:19 by dchrysov         ###   ########.fr       */
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

static int	quote_array(t_data *inp, int start, char **res, bool double_flag)
{
	int		end;

	end = start + 1;
	if (double_flag)
	{
		while (inp->pipe.cmd[0][end] != '"')
			end++;
		inp->quotes.dq = !inp->quotes.dq;
		*res = ft_substr(inp->pipe.cmd[0], start + 1, end - start - 1);
		printf("res: '%s'\n", *res);
		expansion_oper(inp->env, res);
	}
	else
	{
		while (inp->pipe.cmd[0][end] && inp->pipe.cmd[0][end] != '\'')
			end++;
		inp->quotes.sq = !inp->quotes.sq;
		*res = ft_substr(inp->pipe.cmd[0], start + 1, end - start - 1);
	}
	return (end);
}

static void	handle_quotes(t_data *inp)
{
	char	*temp;
	char	*temp_res;
	char	*res;
	int		start;
	int		end;

	res = NULL;
	start = -1;
	while (inp->pipe.cmd[0][++start])
	{
		temp_res = NULL;
		temp = NULL;
		// handle_escape(input, state);
		// if (temp[start] == '\'' && !state->dq)
		// {
		// 	state->sq = !state->sq;
		// 	continue ;
		// }
		if ((inp->pipe.cmd[0][start] == '\'' && inp->quotes.dq_closed) || (inp->pipe.cmd[0][start] == '"' && inp->quotes.sq_closed))
		{
			if (inp->pipe.cmd[0][start] == '\'' && inp->quotes.dq_closed)
				end = quote_array(inp, start, &temp, 0);
			else if (inp->pipe.cmd[0][start] == '"' && inp->quotes.sq_closed)
				end = quote_array(inp, start, &temp, 1);
		}
		else
		{
			temp = safe_malloc(sizeof(char) * 2);
			temp[0] = inp->pipe.cmd[0][start];
			temp[1] = '\0';
			end = start;
		}
		if (res)
		{
			temp_res = ft_strdup(res);
			free(res);
		}
		else
			temp_res = ft_strdup("");
		res = ft_strjoin(temp_res, temp);
		free(temp);
		free(temp_res);
		start = end;
	}
	free(inp->pipe.cmd[0]);
	inp->pipe.cmd[0] = res;
}

int	main(int argc, char **argv, char **env)
{
	t_data	inp;

	(void)argc;
	(void)argv;
	dupl_env(&inp.env, env);
	inp.pipe.cmd = safe_malloc(2 * sizeof(char *));
	inp.pipe.cmd[0] = ft_strdup("\"double: $PWD\"");
	inp.pipe.cmd[1] = NULL;
	inp.quotes = init_quote_state();
	if (check_quotes(&inp))
		return (printf("Error: Quote still open.\n"), 0);
	printf("\nProcessing quotes for: %s\n", *inp.pipe.cmd);
	handle_quotes(&inp);
	printf("Result: '%s'\n\n", *inp.pipe.cmd);
	free_array(inp.pipe.cmd);
	free_array(inp.env);
}

// cc handle_quote.c builtins/cd/*.c utils/*.c ../include/libft/src/*.c -o handle_quote -Wall -Werror -Wextra -lreadline -g


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
