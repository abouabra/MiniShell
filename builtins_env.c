/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 12:03:37 by abouabra          #+#    #+#             */
/*   Updated: 2023/02/23 20:09:44 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_export(t_args *vars, t_command *command)
{
	t_env *new_env;
	t_env *search;
	t_env *env;
	char **args;

	if(!command->command_args[1])
	{
		env = vars->env_head;
		while(env)
		{
			printf("declare -x %s=\"%s\"\n",env->env_id,env->env_data);
			env = env->next;
		}	
		return;	
	}
	args = ft_split(command->command_args[1], '=');
	search = vars->env_head;
	while(search)
	{
		if(!ft_strncmp(search->env_id, args[0], -1))
		{
			search->env_data = args[1];
			break;
		}
		search = search->next;
	}
	if(!search)
	{
		new_env = ft_new_env_node(args[0], args[1]);
		add_env_in_back(&vars->env_head, new_env);
	}
}

void	env(t_args *vars)
{
	t_env *env;

	env = vars->env_head;
	while(env)
	{
		printf("%s=%s\n",env->env_id,env->env_data);
		env = env->next;
	}	
}

void	unset(t_args *vars, char *env_id)
{
	t_env *env;

	env = vars->env_head;
	while(env)
	{
		if(!ft_strncmp(env_id, env->env_id, -1))
			break;
		env = env->next;
	}
	ft_node_remove_if(&vars->env_head, env_id);
}

// int main(int ac, char **av, char **ev)
// {
// 	char *line;
// 	(void)ac;
// 	(void)av;
	
// 	t_args *vars;
// 	vars = ft_calloc(1, sizeof(t_args));
// 	if(!vars)
// 		return 0;
// 	vars->ev = ev;
// 	set_env(vars);
// 	env(vars);
// 	env_export(vars, "VAR", "10");
// 	env(vars);
// 	env_export(vars, "VAR", "20");
// 	env(vars);
// 	unset(vars, "GG");
// 	// env(vars);
// 	return 0;
// }