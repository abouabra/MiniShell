/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:55:49 by abouabra          #+#    #+#             */
/*   Updated: 2023/02/23 20:02:20 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/ft_dprintf.h"
#include "libft/get_next_line.h"
#include "libft/libft.h"
#include "minishell.h"

void	cd(t_args *vars, t_command *command)
{	
	t_env *search;
	char *data;
	int ofsset;
	char *new;
	
	if(!command->command_args[1])
		command->command_args[1] = get_env_data(vars, "HOME");
	else if(ft_strchr(command->command_args[1], '~'))
	{
		data = get_env_data(vars, "HOME");
		ofsset  = ft_strchr_num(command->command_args[1], '~');
		new = ft_substr(command->command_args[1], ofsset +1, ft_strlen(command->command_args[1]));
		command->command_args[1] = ft_strjoin(data, new);
	}
	else if(access(command->command_args[1], F_OK))
	{
		ft_dprintf(2, "minishell: cd: %s: No such file or directory\n",command->command_args[1]);
		return;
	}
	chdir(command->command_args[1]);
	search = vars->env_head;
	while(search)
	{
		if(!ft_strncmp(search->env_id, "PWD", -1))
		{
			search->env_data = getcwd(NULL ,-1);
			break;
		}
		search = search->next;
	}
}


void	echo(t_command *command)
{
	int is_arg;
	int i;
	
	is_arg = 1;
	i = 0;
	if(!ft_strncmp("-n", command->command_args[1], -1))
	{
		is_arg = 0;
		i++;
	}
	while(command->command_args[++i])
		printf("%s",command->command_args[i]);
	if(is_arg)
		printf("\n");
}

void	my_exit(char *arg)
{
	int status;
	
	if(!arg)
		status = 0;
	else
		status = ft_atoi(arg);
	printf("exit\n");
	exit(status);
}

void	pwd(void)
{
	printf("%s\n",getcwd(NULL ,-1));
}

// int main(int ac,char **av, char **ev)
// {
// 	if(ac != 2)
// 		return 0;
// 	(void)av;
	
// 	t_args *vars;
// 	vars = ft_calloc(1, sizeof(t_args));
// 	if(!vars)
// 		return 0;
// 	vars->ev = ev;
// 	set_env(vars);
// 	cd(vars, av[1]);
// 	pwd();
// 	printf("%s\n",get_env_data(vars, "PWD"));
// 	echo("HELLO World", 0);
// 	my_exit(0);
// }