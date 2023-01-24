#include <thread>
#include <sys/socket.h>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <string.h>
#include <stdio.h>
#include <fcntl.h>

int	main()
{
	int sock;
	struct sockaddr_in	client;
	char	buffer[50];
	std::string	s;

	sock = socket(AF_INET, SOCK_STREAM, 0);
	fcntl(_socketServer, F_SETFL, O_NONBLOCK);
	client.sin_family = AF_INET;
	client.sin_addr.s_addr = htonl(INADDR_ANY);
	client.sin_port = htons(6667);
	connect(sock, (struct sockaddr *)&client, sizeof(client));
	std::cout << recv(sock, buffer, 50, 0) << std::endl;
	std::cout << buffer << std::endl;
	while (1)
	{
		s.clear();
		while (s.size() == 0)
		{
			if (std::getline(std::cin, s).eof())
				std::cout << "EOF reached" << std::endl;
		}
		send(sock, s.c_str(), s.size() + 1, 0);
	}
}
