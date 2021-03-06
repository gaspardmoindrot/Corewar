/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbeaufre <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:17:39 by rbeaufre          #+#    #+#             */
/*   Updated: 2019/09/11 03:20:07 by rbeaufre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_put_space(t_data *data, long long nb)
{
	if (nb >= 0)
		if (data->space == 1 && data->plus != 1)
			ft_fill_buffer(data, " ", 1);
}
