/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ss.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kohkubo <kohkubo@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 20:55:43 by kohkubo           #+#    #+#             */
/*   Updated: 2021/02/26 20:55:52 by kohkubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libex.h"


void	free_ss(char ***sss)
{
	char **head;
	char **ss;

	ss = *sss;
	head = ss;
	while (*ss)
	{
		SAFE_FREE(*ss);
		ss++;
	}
	SAFE_FREE(head);
}
