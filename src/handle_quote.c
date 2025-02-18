/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:36:03 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/18 18:57:57 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	update_split_state(char c, t_quote_state *state)
{
	if (state->escape)
	{
		state->escape = false;
		return ;
	}
	if (c == '\\')
	{
		state->escape = true;
		return ;
	}
	if (c == '\'' && !state->dq)
		state->sq = !state->sq;
	else if (c == '"' && !state->sq)
		state->dq = !state->dq;
}

bool	check_quotes(const char *input)
{
	t_quote_state	state;

	state = init_quote_state();
	while (*input)
	{
		update_split_state(*input, &state);
		input++;
	}
	return (state.sq || state.dq);
}

void	update_quote_state(char **input, char **dst, t_quote_state *state)
{
	if (state->escape)
	{
		
	}
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
		update_quote_state(&input, &state);
	}
	*dst = '\0';
	return (res);
}


int main() {
    const char *input1 = "echo 'Hello World'";
    const char *input2 = "echo \"Hello $USER\"";
    const char *input3 = "echo 'This is a \\ test'";
    const char *input4 = "echo \"This is a \\\" test\"";
    const char *input5 = "echo \"Hello; World\"";
    const char *input6 = "echo 'Unclosed quote";
    const char *input7 = "echo \"Unclosed quote";
    const char *input8 = "echo \"This is a \\ backslash\"";
    const char *input9 = "echo 'This is a \\ backslash'";
    const char *input10 = "echo \"Unclosed quote with escape \\\"";
    const char *input11 = "echo 'Unclosed quote with escape \\'";
    const char *input12 = "echo \"Part1\" | echo \"Part2\"";
    const char *input13 = "echo 'Part1' | echo 'Part2'";
    const char *input14 = "echo \"Outer \\\"Inner\\\"\"";
    const char *input15 = "echo 'Outer \\'Inner\\''";

    const char *inputs[] = {input1, input2, input3, input4, input5, input6, input7, input8, input9, input10, input11, input12, input13, input14, input15};
    size_t input_count = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < input_count; i++) {
        printf("Input: %s\n", inputs[i]);
        if (check_quotes(inputs[i])) {
            printf("Error: Unclosed quotes detected.\n");
        } else {
            char *processed_input = process_quotes((char *)inputs[i]);
            printf("Processed: %s\n", processed_input);
            t_list *commands_list = split_pipes(processed_input);
            t_list *tmp = commands_list;
            while (tmp) {
                printf("Command: %s\n", tmp->str);
                tmp = tmp->next;
            }
            free(processed_input);
            free_list(commands_list);
        }
        printf("\n");
    }

    return 0;
}