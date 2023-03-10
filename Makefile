NAME	= ircserv

CXX		= c++

CXXFLAGS	= -Wall -Wextra -Werror -MMD -std=c++98 -g3

SRCS	=	Server.cpp \
			main.cpp \
			User.cpp \
			Message.cpp \
			utils.cpp \
			signal.cpp \
			nick_cmd.cpp \
			user_cmd.cpp \
			Channel.cpp \
			quit.cpp \
			mode_cmd.cpp \
			join.cpp \
			part.cpp \
			topic.cpp \
			oper_cmd.cpp \
			names.cpp \
			list.cpp\
			pong.cpp \
			cmd_notice.cpp \
			cmd_privmsg.cpp \
			kick.cpp \
			die_cmd.cpp \
			kill_cmd.cpp

OBJS	= $(addprefix src/, $(SRCS:.cpp=.o))

DEPS	= $(OBJS:.o=.d)

IFLAGS	= -Iincludes

all		:	$(NAME)

$(NAME)	:	$(OBJS)
			$(CXX) $(CXXFLAGS) $(IFLAGS) -o $@ $^

%.o		:	%.cpp
			$(CXX) $(CXXFLAGS) $(IFLAGS) -c $< -o $@

clean	:
			$(RM) $(DEPS)
			$(RM) $(OBJS)

fclean	:	clean
			$(RM) $(NAME)

re		:	fclean all

-include $(DEPS)

.PHONY	:	all fclean clean re
