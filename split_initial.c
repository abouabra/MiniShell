/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_initial.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:31:10 by abouabra          #+#    #+#             */
/*   Updated: 2023/02/24 17:33:28 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int count_words(char *s)
{
	int		i;
	int		phrase_count;

	i = -1;
	phrase_count = 0;
	while (++i < ft_strlen(s))
	{
		if (s[i] == '|' && s[i + 1] != '|')
			phrase_count++;
		else if (s[i] == '&' && s[i + 1] == '&')
		{
			phrase_count++;
			i++;
		}
		else if (s[i] == '|' && s[i + 1] == '|')
		{
			phrase_count++;
			i++;
		}
	}
	phrase_count++;
	return phrase_count;
}

char	**initial_split(t_args *vars, char *s)
{
	int		i;
	int		j;
	int		k;
	int		phrase_count;
	int		phrase_length;
	char	**phrases;

	i = -1;
	j = 0;
	k = 0;
	phrase_length = 0;

	phrase_count = count_words(s);
	vars->command_count = phrase_count;
	phrases = (char **)my_alloc((phrase_count + 1) * sizeof(char *));
	while (++i < ft_strlen(s))
	{
		if (s[i] == '|' && s[i + 1] != '|')
		{
			phrase_length = i - j;
			phrases[k] = (char *)my_alloc((phrase_length + 1) * sizeof(char));
			ft_memcpy(phrases[k], s + j, phrase_length);
			phrases[k][phrase_length] = '\0';
			k++;
			j = i + 1;
		}
		else if (s[i] == '&' && s[i + 1] == '&')
		{
			phrase_length = i - j;
			phrases[k] = (char *)my_alloc((phrase_length + 1) * sizeof(char));
			ft_memcpy(phrases[k], s + j, phrase_length);
			phrases[k][phrase_length] = '\0';
			k++;
			j = i + 2;
			i++;
		}
		else if (s[i] == '|' && s[i + 1] == '|')
		{
			phrase_length = i - j;
			phrases[k] = (char *)my_alloc((phrase_length + 1) * sizeof(char));
			ft_memcpy(phrases[k], s + j, phrase_length);
			phrases[k][phrase_length] = '\0';
			k++;
			j = i + 2;
			i++;
		}
	}
	phrase_length = i - j;
	phrases[k] = (char *)my_alloc((phrase_length + 1) * sizeof(char));
	ft_memcpy(phrases[k], s + j, phrase_length);
	phrases[k][phrase_length] = '\0';
	k++;
	phrases[k] = NULL;
	return (phrases);
}

// int main()
// {
// 	char **arr;
// 	int i;
// 	i = -1;
// 	char *str = "    export TEST_VAR=\"Hello World\"";
//     arr = initial_split(str);
// 	while(arr[++i])
// 	{
// 		printf("%s\n",arr[i]);
// 	}
// 	return (0);
// }
