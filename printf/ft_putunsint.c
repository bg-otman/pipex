/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 09:10:52 by obouizi           #+#    #+#             */
/*   Updated: 2025/01/30 15:10:18 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putunsint(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb >= 10)
		count += ft_putunsint(nb / 10);
	count += ft_putchar((nb % 10) + '0');
	return (count);
}
