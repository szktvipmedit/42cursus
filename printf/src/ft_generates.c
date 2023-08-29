/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_generates.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: string <string>                            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:14:39 by kousuzuk          #+#    #+#             */
/*   Updated: 2023/08/29 15:25:16 by kousuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"
#include "../libft/libft.h"
#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>

size_t	gen_c(t_format forminfo, va_list ap)
{
	char	c;

	if (forminfo.spec == '%')
	{
		write(1, "%", 1);
		return (1);
	}
	c = va_arg(ap, int);
	ft_putchar_fd(c, 1);
	return (1);
}

size_t	gen_s(va_list ap)
{
	size_t	count;
	char	*str;
	int		ismalloc;

	ismalloc = 0;
	str = va_arg(ap, char *);
	if (!str)
	{
		str = malloc(sizeof(char) * 7);
		ft_strlcpy(str, "(null)", 7);
		ismalloc = 1;
	}
	count = ft_strlen(str);
	ft_putstr_fd(str, 1);
	if (ismalloc)
		free(str);
	return (count);
}

size_t	gen_diu(t_format forminfo, va_list ap)
{
	size_t	print_nbr;
	int		nb;
	char	*str;

	print_nbr = 0;
	nb = va_arg(ap, int);
	if (nb >= 0 && forminfo.plus)
		print_nbr = write(1, "+", 1);
	else if (nb >= 0 && forminfo.space)
		print_nbr = write(1, " ", 1);
	if (forminfo.spec == 'u')
		str = ft_utoa((unsigned int)nb);
	else
		str = ft_itoa(nb);
	print_nbr += ft_strlen(str);
	ft_putstr_fd(str, 1);
	free(str);
	return (print_nbr);
}

size_t	gen_p(va_list ap)
{
	size_t	print_nbr;
	size_t	p;

	p = va_arg(ap, size_t);
	print_nbr = write(1, "0x", 2);
	if (p == 0)
	{
		write(1, "0", 1);
		return (print_nbr + 1);
	}
	recursive_hex_p(p, &print_nbr);
	return (print_nbr);
}

size_t	gen_xlx(t_format forminfo, va_list ap)
{
	size_t			print_nbr;
	unsigned int	nb;

	nb = va_arg(ap, unsigned int);
	print_nbr = 0;
	if (nb == 0)
		return (write(1, "0", 1));
	if (forminfo.spec == 'X')
	{
		if (forminfo.sharp)
			print_nbr = write(1, "0X", 2);
		recursive_hex_xlx(nb, forminfo, &print_nbr);
	}
	else
	{
		if (forminfo.sharp)
			print_nbr = write(1, "0x", 2);
		recursive_hex_xlx(nb, forminfo, &print_nbr);
	}
	return (print_nbr);
}
