/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_specifier.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 11:30:51 by obouizi           #+#    #+#             */
/*   Updated: 2025/01/30 15:10:18 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	check_specifier(char c, va_list args)
{
	int	len;

	len = 0;
	if (c == 's')
		len = ft_putstr(va_arg(args, char *));
	else if (c == 'd' || c == 'i')
		len = ft_putnbr(va_arg(args, int));
	else if (c == 'c')
		len = ft_putchar((char) va_arg(args, int));
	else if (c == 'x')
		len = ft_puthex(va_arg(args, unsigned int), "0123456789abcdef");
	else if (c == 'X')
		len = ft_puthex(va_arg(args, unsigned int), "0123456789ABCDEF");
	else if (c == 'u')
		len = ft_putunsint((va_arg(args, unsigned int)));
	else if (c == 'p')
		len = ft_putadresse((va_arg(args, unsigned long long)));
	else if (c == '%')
		len = ft_putchar('%');
	return (len);
}
