/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_command.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 17:31:17 by abouabra          #+#    #+#             */
/*   Updated: 2023/02/24 17:33:22 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/get_next_line.h"
#include "minishell.h"

static int	count_words(char *s)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;
	int	phrase_count;

	in_single_quote = 0;
	in_double_quote = 0;
	phrase_count = 0;
	i = -1;
	while (++i < ft_strlen(s))
	{
		if (s[i] == ' ' && !in_single_quote && !in_double_quote)
			phrase_count++;
		if (s[i] == '\'')
			if (!in_double_quote)
				in_single_quote = !in_single_quote;
		if (s[i] == '"')
			if (!in_single_quote)
				in_double_quote = !in_double_quote;
	}
	phrase_count++;
	return (phrase_count);
}

char	**split_command(char *s)
{
	int		i;
	int		j;
	int		k;
	int		in_single_quote;
	int		in_double_quote;
	int		phrase_count;
	int		phrase_length;
	int		in_word;
	char	**phrases;

	in_single_quote = 0;
	in_double_quote = 0;
	phrase_length = 0;
	i = 0;
	j = 0;
	k = 0;
	in_word = 0;
	phrase_count = count_words(s);
	phrases = (char **)my_alloc((phrase_count + 1) * sizeof(char *));
	while (i < ft_strlen(s))
	{
		if (s[i] == ' ' && !in_single_quote && !in_double_quote)
		{
			if (in_word)
			{
				phrase_length = i - j;
				phrases[k] = (char *)my_alloc((phrase_length + 1) * sizeof(char));
				ft_memcpy(phrases[k], s + j, phrase_length);
				phrases[k][phrase_length] = '\0';
				k++;
				j = i + 1;
				in_word = 0;
			}
			else
			{
				j++;
			}
		}
		else
		{
			in_word = 1;
			if (s[i] == '\'')
				if (!in_double_quote)
					in_single_quote = !in_single_quote;
			if (s[i] == '"')
				if (!in_single_quote)
					in_double_quote = !in_double_quote;
		}
		i++;
	}

	if (in_word)
	{
		phrase_length = i - j;
		phrases[k] = (char *)my_alloc((phrase_length + 1) * sizeof(char));
		ft_memcpy(phrases[k], s + j, phrase_length);
		phrases[k][phrase_length] = '\0';
		k++;
	}
	phrases[k] = NULL;
	return (phrases);
}