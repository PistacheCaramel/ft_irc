#ifndef SERVER_HPP
# define SERVER_HPP

#include <arpa/inet.h>
#include <string>
#include <algorithm>
#include <netinet/in.h>
#include <vector>
#include <utility>
#include <map>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "User.hpp"
#include "Replies.hpp"
#include "Message.hpp"
#include "signal.hpp"
#include "Channel.hpp"

#define MAX_USER 10
#define MAX_CONN 12


class	Server
{

	public:

		/*types*/
			typedef std::map<std::string, User>::iterator	iterator; //should change name if we gonna use other containers with iterator
			typedef void (Server::*func_ptr)(User *);
			std::map<std::string, func_ptr> cmd_map;

			Server(void);
			~Server(void);
	
			int		init(int port, std::string pass);
			int		start(void);
			
			/*getters ; faire un get channel*/

			std::map<std::string, User>::iterator	getUser(std::string);

	private :

//			int		handleClient(void);

			/*functions*/
			void								_initSocket(void);
			int							_initClient(int index);
			void							_pollfunction(void);
			void							_checkUser(void);
			void							_handleMessage(void);
			void							_execute(User *user);
			void							_notice(User *user);
			void							_privMsg(User *user);
			void	_whoIs(User *user);
			iterator						_findUserByFd(int fd);
			void							_unrgUser(int index, std::string buffer);
			void							_join(User *user);
			void							_disconnectClient(pollfd& client);
			void							_quit(User *user);
			void							_ft_Pollin(unsigned int i, iterator it);
			void							_ft_Pollout(unsigned int i, iterator it);
			void							_part(User *user);
			void							_topic(User *user);
			void							_removeUserFromChannels(const std::string& nickname);
			void							_names(User *user);
			void							_list(User *user);
			void    						_listAllChannels(User *user);
			void							_pong(User *user);
			void    						_channelsList(User *user);
			void							_kick(User *user);
			void							_handlePass(int index, Message msg);

			/*tmp commands stash*/

			std::string	nick_cmd(std::string nick, std::string oldnick = "",
					struct pollfd * fd = NULL, struct sockaddr * addr = NULL);
			void	cmd_user(User * user);
			void	kill_cmd(User * user);
			void	mode_cmd(User * user);
			void	who_cmd(User * user);
			void	get_mode(User * user);
			void	oper_cmd(User * user);
			void	die_cmd(User * user);
			User	*nick_holder(User * user);
			

			/*server infos*/
			std::string						_pass;
			struct sockaddr_in6				_addrServer;
			char							_domainName[16];
			int								_ret;


			/*users mayhem*/
			socklen_t						_clientSize;
			struct sockaddr					_addrInfo[MAX_CONN];
			struct pollfd					_pollTab[MAX_CONN];
			std::string						_tempRpl[MAX_CONN];
			std::string						_leftover[MAX_CONN];
			bool							_passTab[MAX_CONN];

			std::map<std::string, User>		_users;
			std::map<std::string, Channel>	_channels;
			int								_nbUsers;
			nfds_t							_nbSock;

			/*socket options utils*/
			int								_on;
			int								_off;

};

std::string	findNick(std::string buffer);
std::string	gnm(std::string & buff, std::string & s);
void		readySendy(std::string &str, std::string domain, std::string nick);
bool    	invalidChannelName(const std::string& channelName);
void		sendMessagetochan(User *user, Channel *channel, std::map<std::string, User>::iterator users, std::map<std::string, User>::iterator end, char *domainName);
void		sendMessageToAllChan(Channel *channel, std::map<std::string, User>::iterator users, std::map<std::string, User>::iterator end, std::string message);
void		sendMessage(User *user, User *receiver, char *domainName);

#endif
