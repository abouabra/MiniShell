/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 12:30:57 by abouabra          #+#    #+#             */
/*   Updated: 2023/02/26 18:27:11 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/get_next_line.h"
#include "libft/libft.h"
#include "minishell.h"

char *set_ps1(t_args *vars)
{
	char *ps1;
	// char *user;
	// char *pwd;
	// char *hostname;
	(void) vars;
	

	// ps1 = "───[\e[1;34mroot\e[0m]──[\e[1;31mls\e[0m]\n─>";
	
	// user =get_env_data(vars, "USER");
	// pwd =get_env_data(vars, "PWD");
	// ps1 = ft_strjoin("───[\e[1;34m", user);
	// ps1 = ft_strjoin(ps1, "\e[0m]──[\e[1;31m");
	// ps1 = ft_strjoin(ps1, pwd);
	// ps1 = ft_strjoin(ps1, "\e[0m]\n─>");
	// char *ps1 = "minishell> ";
	// ps1 ="[\e[1;32muser\e[0m@\e[1;33mhost\e[0m:\e[1;35m~\e[0m]$";

	
	// user =get_env_data(vars, "USER");
	// hostname =get_env_data(vars, "HOSTNAME");
	// pwd =get_env_data(vars, "PWD");
	// ps1 = ft_strjoin("\e[1;33m", user);
	// ps1 = ft_strjoin(ps1, "\e[0m@\e[1;32m");
	// ps1 = ft_strjoin(ps1, hostname);
	// ps1 = ft_strjoin(ps1, "\e[0m:\e[1;31m");
	// ps1 = ft_strjoin(ps1, pwd);
	// ps1 = ft_strjoin(ps1, " $\e[0m ");
	ps1 = "minishell> ";
	return ps1;
}

int main(int ac, char **av, char **ev)
{
	t_args *vars;
	char *line;
	char *ps1;
	(void)ac;
	(void)av;
	
	vars = my_alloc(sizeof(t_args));
	if(!vars)
		return 0;
	vars->ev = ev;
	set_env(vars);
	init_signal();
	while(1)
	{
		ps1 = set_ps1(vars);
		line = readline(ps1);
		if(!line)
		{
			dprintf(1, "\n");
			custom_exit(vars->exit_status);
		}
		if(line && line[0])
		{
			add_history(line);
			parse_commands(vars, line);
			execution_phase(vars);
			// debug_menu(vars);
			vars->command_head = NULL;
		}
	}
	custom_exit(0);
	return 0;
}