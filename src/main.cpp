#include "Server.hpp"
#include <stdlib.h>

/*int		printErr(int ret)
{
	ret = std::abs(ret);

	switch (ret)
	{
		case 1: std::cerr << "Server init : socket problem " << std::endl; break ;
		case 2: std::cerr << "Server init : fcntl problem " << std::endl; break ;
		case 3: std::cerr << "Server init : bind problem " << std::endl; break ;
		case 4: std::cerr << "Server init : listen problem " << std::endl; break ;
		case 5: std::cerr << "Server problem : recv " << std::endl; break ;
		case 6: std::cerr << "Server problem : send " << std::endl; break ;
		case 7: std::cerr << "invalid port number/argument" << std::endl; break ;
		default: std::cerr << "unknown error" << std::endl;
	}	
	return (ret);
}*/

int		printErr(int ret)
{
	ret = std::abs(ret);

	switch (ret)
	{
		case 1: perror("Server init : socket problem "); break ;
		case 2: perror("Server init : fcntl problem "); break ;
		case 3: perror("Server init : bind problem "); break ;
		case 4: perror("Server init : listen problem "); break ;
		case 5: perror("Server problem : recv "); break ;
		case 6: perror("Server problem : send "); break ;
		case 7: perror("invalid port number/argument "); break ;
		case 8: perror("error: setsockopt for SO_REUSADDR "); break ;
		case 9: perror("error: setsockopt for IPV6_V6ONLY "); break ;
		default: perror("unknown error");
	}	
	return (ret);
}

int		main(int ac, char **av)
{
	Server	server;
	int		ret;

	if (ac != 3)
	{
		std::cerr << "Error" << std::endl << "usage: ./ircserv <port> <password>" << std::endl;
		return (EXIT_FAILURE);
	}
	ret = server.init( atoi(av[1]) );
	if (ret)
		return ( printErr(ret) );
	ret = server.start();
	if (ret)
		return ( printErr(ret) );

	return (EXIT_SUCCESS);
}