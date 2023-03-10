/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdapurif <cdapurif@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 17:37:02 by cdapurif          #+#    #+#             */
/*   Updated: 2023/02/10 17:34:15 by cdapurif         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

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
    std::string toSend;
    std::string channelName;

	//check parameters
    if (user->receivedmsg.front().getParams().empty())
    {
        user->tosendmsg.push_back(Message(std::string(ERR_NEEDMOREPARAMS) + " JOIN :Syntax error"));
        return ;
    }
    channelName = (user->receivedmsg.front().getParams())[0];
    if (invalidChannelName(channelName))
    {
        std::cout << "Invalid channel name" << std::endl;
        user->tosendmsg.push_back(Message(std::string(ERR_NOSUCHCHANNEL) + " " + channelName + " :No such channel"));
        return ;
    }

    std::cout << "user " << user->getNickname() << " wants to join/create channel " << channelName << std::endl;

    //check if channel exist or create it
    std::map<std::string, Channel>::iterator    chan = _channels.find(channelName);
    if (chan == _channels.end())
    {
        std::cout << "channel " << channelName << " didn't exist, so " << user->getNickname() << " creates it join as operator" << std::endl;
        _channels.insert(std::make_pair(channelName, Channel(channelName)));
        chan = _channels.find(channelName);
        chan->second.addUser(user->getNickname(), OPERATOR | VOICE | INVITE | TOPIC);
    }
    else
    {
        //check if user is already on the channel
        if (chan->second.isUserOnChannel(user->getNickname()))
            return ;
        //check if user is banned
        if (chan->second.isUserBan(user->getNickname()))
        {
            user->tosendmsg.push_back(Message(ERR_BANNEDFROMCHAN + channelName + " :Cannot join channel (+b)"));
            return ;
        }
        std::cout << user->getNickname() << " join channel " << channelName << " as normal user" << std::endl;
        chan->second.addUser(user->getNickname());
    }
    //join message should be sent to all channel members
    toSend = std::string(":") + user->getNickname() + "!~" + user->getUsername() + "@hostname JOIN :" + channelName;
    sendMessageToAllChan(&(chan->second), _users.begin(), _users.end(),toSend);
    //user->tosendmsg.push_back(Message(std::string(":") + user->getNickname() + "!~" + user->getUsername() + "@hostname JOIN :" + channelName));
    user->tosendmsg.push_back(Message(chan->second.listUsersOnChannel()));
    user->tosendmsg.push_back(Message(std::string(RPL_ENDOFNAMES) + channelName + " :End of NAMES list"));
    if (chan->second.getTopic().empty() == false)
        user->tosendmsg.push_back(Message(std::string(RPL_TOPIC) + channelName + " :" + chan->second.getTopic()));
}