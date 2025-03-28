/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_claude.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dchrysov <dchrysov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:47:35 by dchrysov          #+#    #+#             */
/*   Updated: 2025/03/28 14:49:32 by dchrysov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

// Helper function to create a new file node
t_file *create_file_node(const char *filename) {
    t_file *new_node = malloc(sizeof(t_file));
    if (!new_node) return NULL;

    new_node->name = strdup(filename);
    new_node->next = NULL;
    return new_node;
}

// Helper function to add file to the end of the linked list
void add_file_to_list(t_file **head, const char *filename) {
    t_file *new_node = create_file_node(filename);
    if (!new_node) return;

    if (!*head) {
        *head = new_node;
        return;
    }

    t_file *current = *head;
    while (current->next) {
        current = current->next;
    }
    current->next = new_node;
}

// Helper function to check if a token is a redirection operator
bool is_redir_operator(const char *token) {
    return (
        strcmp(token, "<") == 0 ||
        strcmp(token, ">") == 0 ||
        strcmp(token, ">>") == 0 ||
        strcmp(token, "<<") == 0
    );
}

// Helper function to get redirection type
t_redir_type get_redir_type(const char *token) {
    if (strcmp(token, "<") == 0) return REDIR_IN;
    if (strcmp(token, ">") == 0) return REDIR_OUT;
    if (strcmp(token, ">>") == 0) return REDIR_APPEND;
    if (strcmp(token, "<<") == 0) return REDIR_HEREDOC;
    return -1; // Invalid type
}

// Helper function to add redirection to appropriate list
void add_redir_to_list(t_data *inp, t_redir_type type, const char *filename) {
    t_redir_op *redir_op = NULL;

    // Determine which redirection operator to use
    switch (type) {
        case REDIR_IN:
            redir_op = &inp->inp_op;
            break;
        case REDIR_OUT:
            redir_op = &inp->out_op;
            break;
        case REDIR_APPEND:
            redir_op = &inp->app_op;
            break;
        case REDIR_HEREDOC:
            redir_op = &inp->hdoc_op;
            break;
        default:
            return;
    }

    // Add filename to the linked list
    add_file_to_list(&redir_op->filename, filename);
    
    // Increment number of commands
    redir_op->num_cmd++;
}

// Helper function to remove redirection tokens from command
char **remove_redir_from_cmd(char **original_cmd) {
    int read = 0, write = 0;
    bool skip_next = false;

    while (original_cmd[read] != NULL) {
        if (skip_next) {
            skip_next = false;
            read++;
            continue;
        }

        if (is_redir_operator(original_cmd[read])) {
            // Skip redirection operator and its filename
            skip_next = true;
            read++;
            continue;
        }

        // Move non-redirection tokens
        if (read != write) {
            original_cmd[write] = original_cmd[read];
        }
        write++;
        read++;
    }

    // NULL terminate the new command list
    original_cmd[write] = NULL;

    return original_cmd;
}

// Helper function to free file linked list
void free_file_list(t_file *head) {
    while (head) {
        t_file *temp = head;
        head = head->next;
        free(temp->name);
        free(temp);
    }
}

// Main parsing function
void parse_redir(t_data *inp) {
    char **cmd = inp->cmd;
    int i = 0;

    // Check if command is NULL or empty
    if (!cmd || !cmd[0]) return;

    // Reset redirection operator counters and lists
    inp->inp_op.num_cmd = 0;
    inp->out_op.num_cmd = 0;
    inp->app_op.num_cmd = 0;
    inp->hdoc_op.num_cmd = 0;

    inp->inp_op.filename = NULL;
    inp->out_op.filename = NULL;
    inp->app_op.filename = NULL;
    inp->hdoc_op.filename = NULL;

    // Iterate through command tokens
    while (cmd[i] != NULL) {
        // Check if current token is a redirection operator
        if (is_redir_operator(cmd[i])) {
            // Validate that there's a filename after the operator
            if (cmd[i + 1] == NULL) {
                // Handle error: no filename provided
                inp->ret_val = 258; // Syntax error
                return;
            }

            // Get redirection type
            t_redir_type redir_type = get_redir_type(cmd[i]);

            // Add filename to appropriate redirection list
            add_redir_to_list(inp, redir_type, cmd[i + 1]);

            // Move to next token (filename)
            i++;
        }

        i++;
    }

    // Remove redirection tokens from original command
    inp->cmd = remove_redir_from_cmd(cmd);
}

// Cleanup function to free redirection resources
void cleanup_redirections(t_data *inp) {
    free_file_list(inp->inp_op.filename);
    free_file_list(inp->out_op.filename);
    free_file_list(inp->app_op.filename);
    free_file_list(inp->hdoc_op.filename);

    // Reset pointers and counters
    inp->inp_op.filename = NULL;
    inp->out_op.filename = NULL;
    inp->app_op.filename = NULL;
    inp->hdoc_op.filename = NULL;

    inp->inp_op.num_cmd = 0;
    inp->out_op.num_cmd = 0;
    inp->app_op.num_cmd = 0;
    inp->hdoc_op.num_cmd = 0;
}