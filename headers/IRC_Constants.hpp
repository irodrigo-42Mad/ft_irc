/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Constants.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: icastell <icastell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 19:22:13 by icastell          #+#    #+#             */
/*   Updated: 2023/09/07 19:33:50 by icastell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// common sockect constants
#define SERV_PORT "4242"	//Port we are listening on
#define SERV_ADDR "0.0.0.0"	//Local host
#define BUF_SIZE 100		//Socket receive buffer size
#define	BACKLOG 5			//Number of incoming connections that can be queued for acceptance