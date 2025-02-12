/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obouizi <obouizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:46:13 by obouizi           #+#    #+#             */
/*   Updated: 2025/01/30 15:10:18 by obouizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int	handle_character(const char *str, int *i)
{
	int	len;

	len = ft_putchar(str[*i]);
	(*i)++;
	return (len);
}

static	int	handle_percent(const char *str, int *i, va_list args)
{
	if (is_valid_specifier(str[*i + 1]))
	{
		(*i)++;
		return (check_specifier(str[*i], args));
	}
	return (handle_character(str, i));
}

static	int	process_format(const char *str, int *i, va_list args)
{
	int	temp;

	if (str[*i] == '%')
	{
		temp = handle_percent(str, i, args);
		if (temp == -1)
			return (-1);
		(*i)++;
		return (temp);
	}
	else
		return (handle_character(str, i));
}

static	int	process_string(const char *str, int *i, va_list args, int *printlen)
{
	int	temp;

	temp = process_format(str, i, args);
	if (temp == -1)
		return (-1);
	*printlen += temp;
	return (0);
}

int	ft_printf(const char *str, ...)
{
	int		printlen;
	int		i;
	va_list	args;
	int		temp;

	if (!str)
		return (-1);
	va_start(args, str);
	printlen = 0;
	i = 0;
	temp = 0;
	while (str[i])
	{
		temp = process_string(str, &i, args, &printlen);
		if (temp == -1)
		{
			va_end(args);
			return (-1);
		}
	}
	va_end(args);
	return (printlen);
}
