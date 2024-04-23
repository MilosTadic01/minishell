/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:00:45 by dzubkova          #+#    #+#             */
/*   Updated: 2023/11/23 14:35:07 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*int	main(void)
{
	void *p = ft_calloc(-5, -5);
	//void *r = calloc(SIZE_MAX, SIZE_MAX);
	printf("%d\n", (p == NULL));
	return (0);
}*/

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = nmemb * size;
	if (total_size > SIZE_MAX || (nmemb >= SIZE_MAX && size > 0)
		|| (size >= SIZE_MAX && nmemb > 0))
		return (NULL);
	if (((int)nmemb < 0 && (int)size != 0)
		|| ((int)size < 0 && (int)nmemb != 0))
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, total_size);
	return (ptr);
}
