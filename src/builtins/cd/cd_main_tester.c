/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/05 14:30:31 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

static char *read_input()
{
	char	*str;

	printf("%s%s@%s %s%% ", GRN, getenv("USER"), relative_wd(getenv("PWD")), RST);
	str = readline("");
	while (!*str)
	{
		printf("%s%s@%s %s%% ", GRN, getenv("USER"), relative_wd(getenv("PWD")), RST);
		str = readline("");
	}
	add_history(str);
	return(str);
}

static char **copy_environment(char **environ)
{
    char **env_copy;
    int count = 0;
    
    while (environ[count]) count++;
    env_copy = malloc((count + 1) * sizeof(char *));
    if (!env_copy)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < count; i++)
        env_copy[i] = strdup(environ[i]);
    env_copy[count] = NULL;
    return env_copy;
}

static void print_env_vars(char **env)
{
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) == NULL)
        perror("getcwd");
    for (int i = 0; env[i]; i++) {
        if (strncmp(env[i], "PWD=", 4) == 0 || strncmp(env[i], "OLDPWD=", 7) == 0) {
            printf("%s\n", env[i]);
        }
    }
    printf("----------------------------\n");
}

int main(int argc, char **argv, char **environ) {
    (void)argc;
    (void)argv;
    char *input;
    char *args[10];
    char *token;
    int i;
    char **env = copy_environment(environ);

    printf("=== Test-Suite ===\n");

    while (1) {
        input = read_input();
        if (!input || strcmp(input, "exit") == 0) {
            safe_free(input);
            break;
        }
        i = 0;
        token = strtok(input, " ");
        while (token != NULL && i < 9) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        // Führe cd aus
        if (args[0] && strcmp(args[0], "cd") == 0) {
            int ret = ft_cd(env, args);
            printf("Return-Code: %d\n", ret);
            print_env_vars(env);
        } else {
            printf("Unknown command: %s\n", args[0]);
        }

        safe_free(input);
    }
    for (int i = 0; env[i]; i++)
        free(env[i]);
    free(env);
    return 0;
}
