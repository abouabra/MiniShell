/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abouabra < abouabra@student.1337.ma >      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 18:30:46 by abouabra          #+#    #+#             */
/*   Updated: 2023/02/26 18:24:21 by abouabra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void handle_signals(int sig)
{
    if(sig == SIGQUIT)
    {
		return;
    }
    else if(sig == SIGINT)
    {
		return;	
    }
}

void init_signal(void)
{
    struct sigaction sa;

	ft_bzero(&sa, sizeof(struct sigaction));
    sa.sa_handler = handle_signals;
    sigaction(SIGQUIT, &sa, NULL);
    sigaction(SIGINT, &sa, NULL);
}