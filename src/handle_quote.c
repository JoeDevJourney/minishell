/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 11:36:03 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/19 18:13:18 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

bool	check_quotes(const char *input)
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
		if (state.escape)
		{
			*dst++ = *input++;
			state.escape = false;
			continue ;
		}
		if (*input == '\\' && state.dq)
		{
			state.escape = true;
			*dst++ = *input++;
			continue ;
		}
		if (*input == '\\' && !state.sq && !state.dq)
		{
			*dst++ = *input++;
			continue ;
		}
		if (*input == '\'' && !state.dq)
		{
			state.sq = !state.sq;
			input++;
			continue ;
		}
		if (*input == '"' && !state.sq)
		{
			state.dq = !state.dq;
			input++;
			continue ;
		}
		*dst++ = *input++;
	}
	*dst = '\0';
	return (res);
}

int main() {
    const char *inputs[] = {
        "echo 'Hello World'",
        "echo \"Hello $USER\"",
        "echo 'This is a \\ test'",
        "echo \"This is a \\\" test\"",
        "echo \"Hello; World\"",
        "echo 'Unclosed quote",
        "echo \"Unclosed quote",
        "echo \"This is a \\ backslash\"",
        "echo 'This is a \\ backslash'",
        "echo \"Closed quote with escape \\\"\"",
        "echo 'Closed quote with escape \\,',",
        "echo \"Part1\" | echo \"Part2\"",
        "echo 'Part1' | echo 'Part2'",
        "echo \"Outer \\\"Inner\\\"\"",
        "echo 'Outer \\\'Inner\\\''",
        "awk 'BEGIN {print \"Hello World\"}'",
        "export VAR=\"Value with spaces\"",
        "grep \"pattern\" file.txt | awk '{print $1}'",
        "find . -name \"*.c\" -exec gcc -o program {} \\\\;",
        "sed 's/old/new/g' file.txt",
        "printf '%s\\n' \"String with space\""
    };
    size_t input_count = sizeof(inputs) / sizeof(inputs[0]);

    for (size_t i = 0; i < input_count; i++) {
        printf("Input: %s\n", inputs[i]);
        if (check_quotes(inputs[i])) {
            printf("Error: Unclosed quotes detected.\n");
        } else {
            char *processed_input = process_quotes((char *)inputs[i]);
            printf("Processed: %s\n", processed_input);
            free(processed_input);
        }
        printf("\n");
    }
    return 0;
}
