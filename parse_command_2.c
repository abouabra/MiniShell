/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_command_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 16:27:14 by abouabra          #+#    #+#             */
/*   Updated: 2023/02/23 17:15:36 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(t_args *vars,t_fill_info *info, char **arr)
{
	int i;
	(void) vars;
	i=-1;
	while(arr[++i])
	{
		if(ft_strchr(arr[i], '\''))
		{
			arr[i] = ft_strtrim(arr[i], "'");
			info->quote_type = 1;
		}
		if(ft_strchr(arr[i], '\"'))
		{
			arr[i] = ft_strtrim(arr[i], "\"");
			info->quote_type = 2;
		}
	}
}
char *get_herdoc_data(char *limiter)
{
	char	*str;
	char	*total;

	limiter = ft_strjoin(limiter, "\n");
	total = "";
	while (1)
	{
		ft_dprintf(1, "> ");
		str = get_next_line(0);
		if (!ft_strncmp(str, limiter, -1))
			break;
		total = ft_strjoin(total, str);
	}
	return (total);
}

void parse_redirections(t_fill_info *info, char **commands)
{
	int i;

	i=0;
	while(commands[i])
	{
		if(!ft_strncmp(commands[i], ">", -1))
		{
			check_permision(NULL, commands[i + 1], 3);
			info->is_output = 1;
			info->output_file = commands[i + 1];
			i++;
		}
		if(!ft_strncmp(commands[i], "<", -1))
		{
			check_permision(NULL, commands[i + 1], 2);
			info->is_input = 1;
			info->input_file = commands[i +1];
			i++;
		}
		if(!ft_strncmp(commands[i], ">>", -1))
		{
			check_permision(NULL, commands[i + 1], 3);
			info->is_output = 1;
			info->is_append = 1;
			info->append_file = commands[i +1];
			i++;
		}
		if(!ft_strncmp(commands[i], "<<", -1))
		{
			info->is_herdoc = 1;
			info->herdoc_limiter = commands[i +1];
			info->herdoc_data = get_herdoc_data(info->herdoc_limiter);
			i++;
		}		
		i++;
	}
}

int count_args(char **commands)
{
	int i;
	int counter;
	
	counter = 0;
	while (commands[counter])
		counter++;
	
	i=0;
	while (commands[i])
	{
		if(!ft_strncmp(commands[i], ">", -1)
			|| !ft_strncmp(commands[i], "<", -1)
			||!ft_strncmp(commands[i], ">>", -1)
			|| !ft_strncmp(commands[i], "<<", -1))
		{
			counter -= 2;
			i++;
		}
		i++;
	}
	return counter;
}
char **make_new_args(char **commands)
{
	int counter;
	char **args;
	int i;
	int j;
	
	counter = count_args(commands);
	args = my_alloc((counter + 1) * sizeof(char *));
	
	i = 0;
	j = 0;
	if(!commands)
		return NULL;
	while(commands[i])
	{
		if(!ft_strncmp(commands[i], ">", -1)
			|| !ft_strncmp(commands[i], "<", -1)
			||!ft_strncmp(commands[i], ">>", -1)
			|| !ft_strncmp(commands[i], "<<", -1))
		{
			i++;
		}
		else
		{
			args[j] = commands[i];
			j++;
		}
		i++;
	}
	args[j] = NULL;
	return args;
}