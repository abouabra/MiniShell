/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:27:14 by abouabra          #+#    #+#             */
/*   Updated: 2023/02/23 17:27:00 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/get_next_line.h"
#include "minishell.h"

int check_permision(char *command_path, char *name, int arg)
{
	
	if(arg == 1)
	{
		if (!command_path)
		{	
			ft_dprintf(2, "minishell: %s: command not found\n", name);
			return 1;
		}
		else if (command_path && access(command_path, X_OK) == -1)
		{
			ft_dprintf(2, "minishell: %s: Permission denied\n", name);
			return 1;
		}
	}	
	if(arg == 2)
	{
		if(access(name, F_OK) == -1)
		{
			ft_dprintf(2, "minishell: %s: No such file or directory\n", name);
			return 1;
		}
		else if (access(name, R_OK) == -1)
		{
			ft_dprintf(2, "minishell: %s: Permission denied\n", name);
			return 1;
		}
	}
	if(arg == 3)
	{
		if (access(name, F_OK) != -1 && access(name, W_OK) == -1)
		{
			ft_dprintf(2, "minishell: %s: Permission denied\n", name);
			return 1;
		}
	}
	return 0;
}

void expand_variables(t_args *vars, t_fill_info *info, char **args)
{
	int i;
	char *data;

	i= -1;
	while(args[++i])
	{
		if(ft_strchr(args[i], '$') && info->quote_type != 1)
		{
			data = get_env_data(vars, ++args[i]);
			if(data)
				args[i] = ft_strdup(data);
			else
				args[i] = ft_strdup(" ");
		}
	}
}
void parsing_commands(t_args *vars, char **commands)
{
	int i;
	t_command *node;
	t_fill_info *info;
	char **arr;
	char **args;
	char *command_path;
	char **path;
	
	info = my_alloc(sizeof(t_fill_info));
	i=-1;
	path = get_path(vars);
	while(commands[++i])
	{
		ft_memset(info, 0, sizeof(t_fill_info));
		arr = split_command(commands[i]);
		remove_quotes(vars, info,  arr);

		parse_redirections(info, arr);
		args = make_new_args(arr);
		
		command_path = get_command_path(path,args[0]);
		if(args && args[0])
		{
			if(check_permision(command_path, args[0], 1))
				info->is_valid_command = 0;
			else
				info->is_valid_command = 1;
		}
		expand_variables(vars, info, args);
		
		info->command_path = command_path;
		info->command_args = args;

		node = ft_new_command(info);
		add_command_in_back(&vars->command_head, node);
	}
}

void remove_spaces_in_between(t_args *vars)
{
	int i;
	
	i=-1;
	while(vars->initial_commands[++i])
		vars->initial_commands[i] = ft_strtrim(vars->initial_commands[i], " ");
}

void	parse_commands(t_args *vars, char *line)
{
	vars->initial_commands = initial_split(vars, line);
	remove_spaces_in_between(vars);
	parsing_commands(vars, vars->initial_commands);
}