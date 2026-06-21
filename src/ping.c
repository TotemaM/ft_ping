/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 02:45:06 by mmichele          #+#    #+#             */
/*   Updated: 2026/06/21 02:45:23 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"	// memset, sockaddr_in, memcpy

#include <sys/socket.h>	// socket, AF_INET, SOCK_RAW
#include <arpa/inet.h>	// IPPROTO_COMP, inet_ntop
#include <netdb.h>		// getaddrinfo, freeaddrinfo
#include <unistd.h>		// close

t_bool ping_init(t_ping* ctx, const int argc, char** argv) {
	if (!pargs_init(&ctx->pargs, argc, argv))
		return 0;
	pargs_print(&ctx->pargs);
	
	ctx->sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (ctx->sock < 0)
		return 0;

	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	struct addrinfo *res;
	if (getaddrinfo(ctx->pargs.host, 0, &hints, &res) != 0) {
		return 0;
	}

	memcpy(&ctx->addr, res->ai_addr, sizeof(struct sockaddr_in));
	freeaddrinfo(res);
	
	inet_ntop(AF_INET, &ctx->addr.sin_addr, ctx->ip, sizeof(ctx->ip));
	printf("%s\n", ctx->ip);

	return 1;
}

void	ping_send(t_ping *ctx) {
	(void) ctx;
	//sendto(ctx->sock, packet, packet_size, 0, (struct sockaddr *)&ctx->addr, sizeof(ctx->addr));
}

void ping_free(t_ping* ctx) {
	close(ctx->sock);
}
