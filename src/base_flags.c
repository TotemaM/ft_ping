/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base_flags.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmichele <mmichele@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/21 02:44:51 by mmichele          #+#    #+#             */
/*   Updated: 2026/06/21 02:44:56 by mmichele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

t_bool handle_flag_help() {
	printf("Usage : ping [OPTION ...] HOST ...\n");
	printf("Send ICMP ECHO_REQUEST packets to network hosts.\n");
	printf("\n");
	printf("  -?, --help                 give this help list\n");
	printf("  -V, --version              print program version\n");
	return 0;
}

t_bool handle_flags_version() {
	printf("ft_ping\n");
	printf("This project is part of the 42 advanced curriculum.\n");
	printf("\n");
	printf("Written by MICHELETTI Matteo\n");
	return 0;
}
