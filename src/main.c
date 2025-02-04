/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:45:20 by dchrysov          #+#    #+#             */
/*   Updated: 2025/02/04 18:19:11 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// static char *read_input()
// {
// 	char	*str;

// 	printf("%s%s@%s %s%% ", GRN, getenv("USER"), relative_wd(getenv("PWD")), RST);
// 	str = readline("");
// 	while (!*str)
// 	{
// 		printf("%s%s@%s %s%% ", GRN, getenv("USER"), relative_wd(getenv("PWD")), RST);
// 		str = readline("");
// 	}
// 	add_history(str);
// 	return(str);
// }

// int	main(void)
// {
// 	t_data	inp;

// 	printf("Welcome\n");
// 	inp.str = read_input();
// 	while (strncmp(inp.str, "exit", 4) != 0)
// 	{
// 		inp.and.cmd = ft_split2(inp.str, "&&");
// 		inp.and.num_cmd = count_substr(inp.str, "&&");
// 		while (*inp.and.cmd)
// 		{
// 			inp.or.cmd = ft_split2(*inp.and.cmd, "||");
// 			inp.or.num_cmd = count_substr(*inp.and.cmd, "||");
// 			while (*inp.or.cmd)
// 			{
// 				inp.pipe.cmd = ft_split2(*inp.or.cmd, "|");
// 				inp.pipe.num_cmd = count_substr(*inp.or.cmd, "|");
// 				if (is_builtin(inp.pipe.cmd[0]))
// 					inp.pipe.ret_val = execute_builtin(inp.pipe.cmd);
// 				else
// 					inp.pipe.ret_val = exec_pipes(inp.pipe.num_cmd, inp.pipe.cmd);
// 				safe_free(inp.pipe.cmd);
// 				inp.or.ret_val = inp.pipe.ret_val;
// 				if (!inp.or.ret_val)
// 					break ;
// 				inp.or.cmd++;
// 			}
// 			safe_free(inp.or.cmd);
// 			inp.and.ret_val = inp.or.ret_val;
// 			if (inp.and.ret_val)
// 				break ;
// 			inp.and.cmd++;
// 		}
// 		safe_free(inp.and.cmd);
// 		safe_free(inp.str);
// 	}
// 	// safe_free()
// 	return (0);
// }

// ls -l | grep "\.c" > output.txt
// cat < in.txt | grep "pattern" > med.txt || cat < in1.txt | grep "pattern" > med.txt && sort med.txt >> output.txt
// ls > temp.txt | cat < temp.txt
// ls -1 | cat -n
// echo This is a text | cat -n
// cat src/pipes/infile | cat -e

// Simuliere read_input (liest eine Zeile vom Benutzer)
char *read_input(void) {
    char *input = NULL;
    size_t len = 0;
    ssize_t read;

    printf("minishell-test> ");
    read = getline(&input, &len, stdin);
    if (read == -1) {
        free(input);
        return NULL;
    }
    input[read - 1] = '\0'; // Entferne das Newline-Zeichen
    return input;
}

// Zeige das aktuelle Verzeichnis und Umgebungsvariablen an
void print_env_vars(void) {
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Aktuelles Verzeichnis: %s\n", cwd);
    } else {
        perror("getcwd");
    }
    printf("PWD:    %s\n", getenv("PWD"));
    printf("OLDPWD: %s\n", getenv("OLDPWD"));
    printf("----------------------------\n");
}

// int main(void) {
//     char *input;
//     char *args[10]; // Array für Argumente
//     char *token;
//     int i;

//     printf("=== Test-Suite für cd ===\n");

//     while (1) {
//         input = read_input();
//         if (!input || strcmp(input, "exit") == 0) {
//             safe_free(input);
//             break;
//         }

//         // Parse die Eingabe in Argumente
//         i = 0;
//         token = strtok(input, " ");
//         while (token != NULL && i < 9) {
//             args[i++] = token;
//             token = strtok(NULL, " ");
//         }
//         args[i] = NULL;

//         // Führe cd aus
//         if (args[0] && strcmp(args[0], "cd") == 0) {
//             int ret = ft_cd(args);
//             printf("Return-Code: %d\n", ret);
//             print_env_vars();
//         } else {
//             printf("Unbekannter Befehl: %s\n", args[0]);
//         }

//         safe_free(input);
//     }

//     printf("Test beendet.\n");
//     return 0;
// }
