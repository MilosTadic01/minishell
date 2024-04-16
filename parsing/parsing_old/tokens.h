/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dzubkova <dzubkova@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:07:22 by dzubkova          #+#    #+#             */
/*   Updated: 2024/04/10 11:43:47 by dzubkova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H

# define PIPE 0
# define DOLLAR 1
# define DOUBLE_QUOTE 2
# define SINGLE_QUOTE 3
# define REDIRECT_IN 4
# define REDIRECT_OUT 5
# define EQUALS 6

# define REDIRECT_OUT_OUT 10
# define REDIRECT_IN_IN 11
# define AND 12
# define OR 13
# define EXIT_STATUS 14

# define ECHO 100
# define CD 101
# define PWD 102
# define EXPORT 103
# define UNSET 104
# define ENV 105
# define EXIT 106

# define LITERAL 200
# define VARIABLE 201
# define FLAG 202

#endif