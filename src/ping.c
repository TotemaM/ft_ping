/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ping.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 02:45:06 by mmichele          #+#    #+#             */
/*   Updated: 2026/06/21 23:42:19 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"			// memset, sockaddr_in, memcpy, icmphdr

#include <sys/socket.h>			// socket, AF_INET, SOCK_RAW
#include <arpa/inet.h>			// IPPROTO_COMP, inet_ntop
#include <netdb.h>				// getaddrinfo, freeaddrinfo
#include <unistd.h>				// close, usleep

t_bool ping_init(t_ping* ctx, const int argc, char** argv) {
	if (!pargs_init(&ctx->pargs, argc, argv))
		return 0;
	// pargs_print(&ctx->pargs);

	/* Resolve hostname to IPv4 address struct */
	struct addrinfo hints;
	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	struct addrinfo *res;
	if (getaddrinfo(ctx->pargs.host, 0, &hints, &res) != 0) {
		return 0;
	}

	memcpy(&ctx->addr, res->ai_addr, sizeof(struct sockaddr_in));
	freeaddrinfo(res);

	/* Converting IPv4 readable address from IPv4 struct */
	inet_ntop(AF_INET, &ctx->addr.sin_addr, ctx->ip, sizeof(ctx->ip));

	/* Creating the socket */
	ctx->sock = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
	if (ctx->sock < 0)
		return 0;
		
	ctx->seq = 0;
	ctx->interval = 1;
	return 1;
}

unsigned int compute_checksum(uint16_t *hdr, unsigned int len) {
	unsigned long int	sum = 0;
	unsigned int		i = 0;

	while (i < len / 2) {
		sum += hdr[i];
		i++;
	}
	if (len % 2)
		sum += ((unsigned char *)hdr)[len - 1];
	while (sum >> 16)
		sum = (sum & 0xFFFF) + (sum >> 16);
	return ~sum;
}


void ping_send(t_ping *ctx) {
	memset(&ctx->icmp, 0, sizeof(ctx->icmp));

	ctx->icmp.type = ICMP_ECHO;
	ctx->icmp.code = 0;
	ctx->icmp.un.echo.id = htons(getpid() & 0xFFFF);

	ctx->icmp.un.echo.sequence = htons(ctx->seq);
	ctx->seq++;

	ctx->icmp.checksum = 0;
	ctx->icmp.checksum = compute_checksum((uint16_t *)&ctx->icmp, sizeof(struct icmphdr));
	sendto(ctx->sock, &ctx->icmp, sizeof(ctx->icmp), 0, (struct sockaddr *)&ctx->addr, sizeof(ctx->addr));
}

void ping_recv(t_ping *ctx) {
	char buffer[1500];
	struct iphdr *ip;
	struct icmphdr *icmp;
	ssize_t bytes;

	do {
		bytes = recvfrom(ctx->sock, buffer, sizeof(buffer), 0, NULL, NULL);
		if (bytes <= 0)
			return;
		ip = (struct iphdr *)buffer;
		icmp = (struct icmphdr *)(buffer + (ip->ihl * 4));
	} while (icmp->type != ICMP_ECHOREPLY || icmp->un.echo.id != htons(getpid() & 0xFFFF));
	printf("%ld bytes from %s: icmp_seq=%d\n", bytes, ctx->ip, ntohs(icmp->un.echo.sequence));
}

void ping_free(t_ping* ctx) {
	close(ctx->sock);
}
