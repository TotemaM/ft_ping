/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 20:47:26 by mmichele          #+#    #+#             */
/*   Updated: 2026/06/21 16:49:42 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

#include <stdio.h>				// printf
#include <string.h>				// memset, strlen, bzero, memcpy
#include <netinet/in.h>			// sockaddr_in, INET_ADDRSTRLEN
#include <netinet/ip_icmp.h>	// icmphdr

typedef unsigned int	t_idx;
typedef unsigned char	t_bool;

/* Argument flags */

# define FLAG_VERSION	0	// -V or --version
# define FLAG_HELP		1	// -? or --help
# define FLAG_VERBOSE	2	// -v or --verbose

# define FLAG_SIZE		FLAG_VERBOSE + 1

t_bool	handle_flag_help();
t_bool	handle_flags_version();

/* Program arguments */

typedef struct {
	t_bool	flags[FLAG_SIZE];
	char*	host;
}	t_pargs;

t_bool	pargs_init(t_pargs *pa, const int argc, char **argv);
void	pargs_print(const t_pargs *pa);

/* Main ping context */

typedef struct {
	t_pargs				pargs;					// Program args
	int					sock;					// Socket FD
	struct sockaddr_in	addr;					// Host address structure
	char				ip[INET_ADDRSTRLEN];	// Host IPv4 address
	struct icmphdr		icmp;					// ICMP Header

	unsigned int		seq;					// Packet counter
	unsigned int		interval;
}	t_ping;

t_bool	ping_init(t_ping *ctx, const int argc, char **argv);
void	ping_send(t_ping *ctx);
void	ping_recv(t_ping *ctx);
void	ping_free(t_ping* ctx);

#endif // FT_PING_H