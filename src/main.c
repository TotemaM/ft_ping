/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 02:44:36 by mmichele          #+#    #+#             */
/*   Updated: 2026/06/21 02:44:37 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

#include <errno.h>	// errno

int main(int argc, char** argv) {
	argc--; argv++;
	t_ping ctx;
	if (!ping_init(&ctx, argc, argv)) {
		perror(0);
		return 1;
	}
	ping_free(&ctx);
	return 0;
}
