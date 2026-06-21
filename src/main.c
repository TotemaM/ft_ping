/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 02:44:36 by mmichele          #+#    #+#             */
/*   Updated: 2026/06/21 17:10:58 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"	// signal, SIGINT, usleep

#include <errno.h>		// errno
#include <signal.h>		// signal, SIGINT, sig_atomic_t
#include <unistd.h>		// sleep

sig_atomic_t running = 1;

void sighandler(int sig) {
	(void)sig;
	running = 0;
}

int main(int argc, char** argv) {
	argc--; argv++;
	t_ping ctx;
	if (!ping_init(&ctx, argc, argv)) {
		perror(0);
		return 1;
	}
	signal(SIGINT, sighandler);
	printf("PING %s (%s): %ld data bytes\n", ctx.pargs.host, ctx.ip, sizeof(ctx.icmp));
	while (running) {
		ping_send(&ctx);
		ping_recv(&ctx);
		sleep(ctx.interval);
	}
	printf("--- %s ping statistics ---\n", ctx.pargs.host);
	ping_free(&ctx);
	return 0;
}
