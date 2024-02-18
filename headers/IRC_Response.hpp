/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IRC_Response.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pcosta-j <pcosta-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 19:10:11 by pcosta-j          #+#    #+#             */
/*   Updated: 2024/02/18 19:10:13 by pcosta-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IRC_RESPONSE_HPP
# define IRC_RESPONSE_HPP

enum IRC_Response
{
	NONE,
	SUCCESS,
	NICK_IN_USE,
	NOT_IN_CHANNEL,
	ALREADY_IN_CHANNEL,
	ERRONEOUS_NICK,
	CHANNEL_KEY_MISMATCH,
	CHANNEL_IS_FULL,
	INVITE_ONLY,
	USER_BANNED
};

#endif
