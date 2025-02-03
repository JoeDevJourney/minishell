/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbrandt <jbrandt@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 14:33:43 by jbrandt           #+#    #+#             */
/*   Updated: 2025/02/03 18:32:37 by jbrandt          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char	**environ;

char	*create_env_entry(const char *name, const char *value)
{
	char	*new_entry;
	size_t	len;

	len = ft_strlen(name) + ft_strlen(value) + 2;
	new_entry = malloc(len);
	if (!new_entry)
	{
		ft_write_error("cd: malloc failed\n");
		return (NULL);
	}
	ft_strcpy(new_entry, name);
	ft_strcat(new_entry, "=");
	ft_strcat(new_entry, value);
	return (new_entry);
}

int	replace_env_var(const char *name, char *new_entry)
{
	int	i;

	i = 0;
	while (environ[i] != NULL)
	{
		if (ft_strncmp(environ[i], name, ft_strlen(name)) == 0 && environ[i][ft_strlen(name)] == '=')
		{
			free(environ[i]);
			environ[i] = new_entry;
			return (0);
		}
		i++;
	}
	return (-1);
}

int	update_env_var(const char *name, const char *value)
{
	char	*new_entry;

	new_entry = create_env_entry(name, value);
	if (!new_entry)
		return (1);
	if (replace_env_var(name, new_entry) == 0)
		return (0);
	if (add_env_var(new_entry) != 0)
		return (1);
	return (0);
}

int	ft_cd(char **args)
{
	char	*dir;
	char	*oldpwd;

	oldpwd = getenv("PWD");
	dir = get_target_dir(args);
	if (!dir)
		return (1);
	if (chdir(dir) != 0)
	{
		perror("cd");
		return (1);
	}
	if (update_pwd_vars(oldpwd) != 0)
		return (1);
	return (0);
}


// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>

// // Füge die Header-Deklarationen deiner Funktionen hier ein
// extern char **environ;
// int ft_cd(char **args);
// void print_env_vars();

// int main(void) {
//     char input[256];
//     char *args[10];
//     char *token;
//     int i;

//     printf("=== Test-Suite für cd ===\n");

//     // Testfall 1: cd ohne Argument (sollte HOME verwenden)
//     printf("\nTest 1: cd (kein Argument)\n");
//     char *test1[] = {"cd", NULL};
//     ft_cd(test1);
//     printf("Aktuelles Verzeichnis: %s\n", getcwd(NULL, 0));
//     print_env_vars();

//     // Testfall 2: cd mit gültigem Verzeichnis
//     printf("\nTest 2: cd include/\n");
//     char *test2[] = {"cd", "include", NULL};
//     ft_cd(test2);
//     printf("Aktuelles Verzeichnis: %s\n", getcwd(NULL, 0));
//     print_env_vars();

//     // Testfall 3: cd - (zurück zu OLDPWD)
//     printf("\nTest 3: cd -\n");
//     char *test3[] = {"cd", "-", NULL};
//     ft_cd(test3);
//     printf("Aktuelles Verzeichnis: %s\n", getcwd(NULL, 0));
//     print_env_vars();

//     // Testfall 4: cd mit ungültigem Verzeichnis
//     printf("\nTest 4: cd invalid_dir/\n");
//     char *test4[] = {"cd", "invalid_dir", NULL};
//     ft_cd(test4);
//     printf("Aktuelles Verzeichnis: %s\n", getcwd(NULL, 0));
//     print_env_vars();

//     // Interaktiver Modus
//     printf("\n=== Interaktiver Modus (exit zum Beenden) ===\n");
//     while (1) {
//         printf("\nminishell-test> ");
//         fgets(input, sizeof(input), stdin);
//         input[strcspn(input, "\n")] = 0; // Newline entfernen

//         if (strcmp(input, "exit") == 0) break;

//         // Parse Eingabe in Argumente
//         i = 0;
//         token = strtok(input, " ");
//         while (token != NULL && i < 9) {
//             args[i++] = token;
//             token = strtok(NULL, " ");
//         }
//         args[i] = NULL;

//         // Führe cd aus
//         int result = ft_cd(args);
//         printf("Return-Code: %d\n", result);
//         printf("Aktuelles Verzeichnis: %s\n", getcwd(NULL, 0));
//         print_env_vars();
//     }

//     return 0;
// }

// void print_env_vars() {
//     printf("Umgebungsvariablen:\n");
//     printf("PWD:    %s\n", getenv("PWD"));
//     printf("OLDPWD: %s\n", getenv("OLDPWD"));
//     printf("----------------------------\n");
// }