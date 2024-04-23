/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 13:24:21 by dzubkova          #+#    #+#             */
/*   Updated: 2023/12/01 12:47:08 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n);

/*int	main(void)
{
	// Define a buffer with some initial data
    char buffer[] = "abcdefgh";

    // Set up source and destination pointers
    char* src = buffer + 2;  // Points to 'c'
    char* dest = buffer + 4; // Points to 'e'
	printf("%s %s\n", src, dest);

    // Define the number of bytes to move
    //size_t n = 4;

    // Display the initial state
    printf("Initial State: %s\n", buffer);

    // Call your memmove function
    ft_memmove(dest, src, 0);


    // Display the result
    printf("After memmove: %s\n", buffer);
}*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	void	*res;
	char	tmp[1024];
	size_t	idx;
	char	*chsrc;
	char	*chdest;

	if (!src && !dest)
		return (NULL);
	if (n > 1024)
		return (dest);
	res = dest;
	idx = 0;
	chdest = (char *)dest;
	chsrc = (char *)src;
	while (idx < n)
	{
		tmp[idx] = *chsrc++;
		idx++;
	}
	idx = 0;
	while (idx < n)
		*chdest++ = tmp[idx++];
	return (res);
}
