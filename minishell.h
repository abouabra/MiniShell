/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:30:01 by abouabra          #+#    #+#             */
/*   Updated: 2023/02/23 20:06:07 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>

typedef struct t_fill_info
{
	char *command_path;
	char **command_args;
	
	int quote_type;
	int is_valid_command;

	int is_input;
	char *input_file;
	int is_output;
	char *output_file;
	int is_append;
	char *append_file;
	int is_herdoc;
	char *herdoc_limiter;
	char *herdoc_data;
}	t_fill_info;

//sort < input.txt | uniq -l  -a >> unique_sorted_output.txt > outfile.txt << HEREDOC
typedef struct t_env
{
	char				*env_id;
	char				*env_data;
	struct t_env		*next;
}						t_env;

typedef struct t_command
{
	char *command_path;
	char **command_args;
	
	int quote_type;
	int is_valid_command;

	int is_input;
	char *input_file;
	int is_output;
	char *output_file;
	int is_append;
	char *append_file;
	int is_herdoc;
	char *herdoc_data;
	char *herdoc_limiter;
	struct t_command	*next;
}						t_command;

typedef struct t_args
{
	char				**initial_commands;
	char				**ev;
	int					command_count;
	int					is_quote;
	int					prev_pipefd[2];
	int					next_pipefd[2];
	int					exit_status;
	t_command			*command_head;
	t_env				*env_head;
}						t_args;

void					prepare_commands(t_args *vars, char **commands);
void					parsing_initial_split(t_args *vars, char **commands);
char					**get_path(t_args *vars);
char					*get_command_path(char **path, char *command);

//command linked list stuff
t_command	*ft_last_command(t_command *lst);
void	add_command_in_back(t_command **head, t_command *node);
void	add_command_in_front(t_command **head, t_command *node);
int	ft_command_list_size(t_command **head);
t_command	*ft_new_command(t_fill_info *info);

//env linked list stuff
t_env	*ft_last_env(t_env *lst);
void	add_env_in_back(t_env **head, t_env *node);
void	add_env_in_front(t_env **head, t_env *node);
t_env	*ft_new_env_node(char *env_id, char *env_data);
void    ft_node_remove_if(t_env **head, char *env_id);
int	ft_env_list_size(t_env **head);

//parsing commands;
void					parse_commands(t_args *vars, char *line);
char					**initial_split(t_args *vars, char *s);
char					**split_command(char *s);


void					set_env(t_args *vars);
char					*get_env_data(t_args *vars, char *id);
void					remove_quotes(t_args *vars,t_fill_info *info, char **arr);
char					*get_herdoc_data(char *limiter);
void					parse_redirections(t_fill_info *info, char **commands);
int						count_args(char **commands);
char					**make_new_args(char **commands);
int check_permision(char *command_path, char *name, int arg);

//executing phase

void					execution_phase(t_args *vars);


//builtins
int		is_built_in(char *name);
void					echo(t_command *command);
void					cd(t_args *vars, t_command *command);
void					pwd(void);
void					env_export(t_args *vars, t_command *command);
void					unset(t_args *vars, char *env_id);
void					env(t_args *vars);
void					my_exit(char *arg);

void					print_command(t_command *command);
void					init_signal(t_args *vars);


//extra 
void print_command(t_command *command);
void	debug_menu(t_args *vars);

#endif
