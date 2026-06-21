/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pargs.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 15:20:50 by mmichele          #+#    #+#             */
/*   Updated: 2026/06/21 02:45:40 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"	// bzero

t_bool pargs_init(t_pargs* pa, const int argc, char** argv) {
	bzero(pa->flags, FLAG_SIZE * sizeof(t_bool));
	pa->host = 0;
	for (int i = 0; i < argc; i++) {
		if (strcmp(argv[i], "-v") == 0 || strcmp(argv[i], "--verbose") == 0)
			pa->flags[FLAG_VERBOSE] = 1;
		else if (strcmp(argv[i], "-?") == 0 || strcmp(argv[i], "--help") == 0)
			return handle_flag_help();
		else if (strcmp(argv[i], "-V") == 0 || strcmp(argv[i], "--version") == 0)
			return handle_flags_version();
		else if (pa->host == 0)
			pa->host = argv[i];
	}
	return 1;
}

static char* get_flag_name(const unsigned int i) {
	switch (i) {
		case 0: return "Version";
		case 1: return "Help   ";
		case 2: return "Verbose";
	}
	return 0;
}

void pargs_print(const t_pargs *pa) {
	for (unsigned int i = 0; i < FLAG_SIZE; i++) {
		printf("%s : %d\n", get_flag_name(i), pa->flags[i]);
	}
	printf("\nhost    : %s\n", pa->host);
}
