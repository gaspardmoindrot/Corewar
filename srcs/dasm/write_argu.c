/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_argu.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmoindro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 12:37:57 by gmoindro          #+#    #+#             */
/*   Updated: 2020/02/04 17:29:51 by gmoindro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/dasm.h"

void	ft_putnbr_dasm(int n, t_dasm *dasm, int *j)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648");
		return ;
	}
	if (n < 0)
	{
		n = -n;
		dasm->tab[dasm->nb_tab][*j] = '-';
		*j = *j + 1;
	}
	if (n <= 9)
	{
		dasm->tab[dasm->nb_tab][*j] = n + '0';
		*j = *j + 1;
	}
	else
	{
		ft_putnbr_dasm(n / 10, dasm, j);
		ft_putnbr_dasm(n % 10, dasm, j);
	}
}

int		write_reg(t_dasm *dasm, int j, int i)
{
	unsigned int	nb;

	nb = dasm->buf[i];
	if (nb > 127)
		nb = nb - 256;
	dasm->tab[dasm->nb_tab][j] = 'r';
	j++;
	ft_putnbr_dasm(nb, dasm, &j);
	return (j);
}

int		write_dir(t_dasm *dasm, int j, int i, int opcode)
{
	unsigned int	nb;

	dasm->tab[dasm->nb_tab][j] = DIRECT_CHAR;
	j++;
	if (op_tab[opcode - 1].label == 1)
	{
		nb = dasm->buf[i] * 256 + dasm->buf[i + 1];
		if (nb > 32767)
			nb = nb - 65536;
		ft_putnbr_dasm(nb, dasm, &j);
	}
	else
	{
		nb = dasm->buf[i] * 16777216 + dasm->buf[i + 1] * 65536
			+ dasm->buf[i + 2] * 256 + dasm->buf[i + 3];
		ft_putnbr_dasm(nb, dasm, &j);
	}
	return (j);
}

int		write_ind(t_dasm *dasm, int j, int i)
{
	unsigned int	nb;

	nb = dasm->buf[i] * 16 * 16 + dasm->buf[i + 1];
	if (nb > 32767)
		nb = nb - 65536;
	ft_putnbr_dasm(nb, dasm, &j);
	return (j);
}
