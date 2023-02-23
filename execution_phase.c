/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_phase.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:08:47 by abouabra          #+#    #+#             */
/*   Updated: 2023/02/23 17:15:33 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_dprintf.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"
#include "minishell.h"
#include <stdio.h>
#include <sys/fcntl.h>

// void execute_built_in(t_args *vars, t_command *command)
// {
// 	if(!ft_strncmp("cd", command->command_args[0], -1))
// 		cd(vars, command);
// 	if(!ft_strncmp("pwd", command->command_args[0], -1))
// 		pwd();
// 	if(!ft_strncmp("env", command->command_args[0], -1))
// 		env(vars);
// 	if(!ft_strncmp("exit", command->command_args[0], -1))
// 		my_exit(command->command_args[0]);
// 	if(!ft_strncmp("export", command->command_args[0], -1))
// 		env_export(vars, command);
// 	if(!ft_strncmp("unset", command->command_args[0], -1))
// 		unset(vars, command->command_args[1]);
// }
char **convert_env_to_arr(t_env *head)
{
	char **arr;
	char *tmp;
	int env_count;
	int i;
	t_env *env;
	
	env = head;
	env_count = ft_env_list_size(&head);
	arr = my_alloc((env_count + 1) * sizeof(char *));
	i=0;
	while(env)
	{
		tmp = ft_strjoin(env->env_id, "=");
		arr[i] = ft_strjoin(tmp, env->env_data);
		i++;
		env = env->next;
	}
	arr[i] = NULL;
	return arr;
}

void execute_the_commands(t_args *vars, t_command *tmp, int i)
{
	pid_t pid;
	int fd;
	int status;
	
	if (i < vars->command_count - 1)
		pipe(vars->next_pipefd);
	pid = fork();
	if (pid == -1)
		return;
	if (pid == 0)
	{
		if(tmp->is_valid_command == 0)
			exit(127);
		if (i > 0)
		{
			dup2(vars->prev_pipefd[0], 0);
			close(vars->prev_pipefd[0]);
			close(vars->prev_pipefd[1]);
		}
		if (i < vars->command_count - 1)
		{
			dup2(vars->next_pipefd[1], 1);
			close(vars->next_pipefd[0]);
			close(vars->next_pipefd[1]);
		}
		if (tmp->is_input)
		{
			fd = open(tmp->input_file, O_RDONLY);
			if(fd  == -1)
				exit(1);
			dup2(fd, 0);
			close(fd);
		}
		if (tmp->is_output)
		{
			if (tmp->is_append)
				fd = open(tmp->append_file, O_RDWR | O_APPEND | O_CREAT, 0644);
			else
				fd = open(tmp->output_file, O_WRONLY | O_TRUNC | O_CREAT, 0644);
			if(fd  == -1)
				exit(1);
			dup2(fd, 1);
			close(fd);
		}
		if (tmp->is_herdoc)
		{
			fd = open("/tmp/herdoc_data", O_WRONLY | O_TRUNC | O_CREAT, 0644);
			write(fd, tmp->herdoc_data, ft_strlen(tmp->herdoc_data));
			close(fd);
			fd = open("/tmp/herdoc_data", O_RDONLY);
			dup2(fd, 0);
			close(fd);
		}
		// if (!ft_strncmp("echo", tmp->command_args[0], -1))
		// 	echo(vars, tmp);
		// else
			execve(tmp->command_path, tmp->command_args, convert_env_to_arr(vars->env_head));
			exit(1);
		
	}
	if (i > 0)
	{
		close(vars->prev_pipefd[0]);
		close(vars->prev_pipefd[1]);
	}
	if (i < vars->command_count - 1)
	{
		vars->prev_pipefd[0] = vars->next_pipefd[0];
		vars->prev_pipefd[1] = vars->next_pipefd[1];
	}
	waitpid(pid, &status, 0);
	int exit_status = WEXITSTATUS(status);
	dprintf(1, "EXIT_CODE: %d\n",exit_status);
}

// int is_built_in(t_command *command,char **built_in)
// {
// 	int i;

// 	i = -1;
//     while (built_in[++i])
// 		if(!ft_strncmp(command->command_args[0], built_in[i], -1))
// 			return 1;
// 	return 0;
// }

void execution_phase(t_args *vars)
{
	t_command *tmp;
	
    tmp = vars->command_head;
	// char *built_in = "cd|echo|pwd|export|unset|env|exit";
	// char **arr = ft_split(built_in, '|');
    int i  = -1;
    while (++i <  vars->command_count)
    {
		// if (is_built_in(tmp,arr) && ft_strncmp("echo", tmp->command_args[0], -1))
		// 	execute_built_in(vars, tmp);
		// else
		// {
        	execute_the_commands(vars, tmp, i);
			
			// wait(NULL);
		// }
		tmp = tmp->next;
    }
	// free(built_in);
}


