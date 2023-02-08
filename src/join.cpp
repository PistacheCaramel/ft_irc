/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <cdapurif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:37:02 by cdapurif          #+#    #+#             */
/*   Updated: 2023/02/08 17:51:16 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"
#include "Replies.hpp"
#include "Message.hpp"

bool    invalidChannelName(const std::string& channelName)
{
    if (channelName[0] != '#' && channelName[0] != '&')
        return (true);
    if (channelName.find_first_of(" ,") != std::string::npos || channelName.find(7) != std::string::npos)
        return (true);
    return (false);
}

void	Server::_join(User *user)
{
    std::string to_send;
    std::string channelName;

    std::cout << "coucou" << std::endl;

	//check parameters
    if (user->receivedmsg.front().getParams().empty() == true)
    {
        user->tosendmsg.push_back(Message(ERR_NEEDMOREPARAMS + user->getNickname() + " JOIN :Syntax error\r\n"));
        return ;
    }
    channelName = (user->receivedmsg.front().getParams())[0];
    std::cout << "user " << user->getNickname() << " wants to join/create channel " << channelName << std::endl;
    if (invalidChannelName(channelName))
    {
        std::cout << "Invalid channel name" << std::endl;
        user->tosendmsg.push_back(Message(ERR_NOSUCHCHANNEL + user->getNickname() + " " + channelName + " :No such channel\r\n"));
        return ;
    }

    //check if channel exist or create it
    std::map<std::string, Channel>::iterator    chan = _channels.find(channelName);
    if (chan == _channels.end())
    {
        _channels.insert(std::make_pair(channelName, Channel(channelName)));
        chan = _channels.find(channelName);
        chan->second.addUser(user->getNickname(), OPERATOR | VOICE | INVITE | TOPIC);
    }
    else
    {
        //check user modes first
        //HERE 
        chan->second.addUser(user->getNickname());
    }
}