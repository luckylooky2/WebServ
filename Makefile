NAME 		= webserv
CXX 		= c++
#CXXFLAGS 	= -Wall -Wextra -Werror -std=c++98
RM 			= rm -f
INCS 		= -I
SRCS 		= srcs/main.cpp srcs/log/LogFactory.cpp srcs/log/Logger.cpp \
				srcs/exception/Exception.cpp srcs/exception/RuntimeException.cpp srcs/exception/IOException.cpp srcs/exception/IllegalStateException.cpp srcs/exception/IllegalArgumentException.cpp srcs/exception/NullPointerException.cpp \
				srcs/file/FileDescriptor.cpp \
				srcs/config/block/RootBlock.cpp srcs/config/block/ServerBlock.cpp srcs/config/block/LocationBlock.cpp \
				srcs/http/server/Server.cpp srcs/http/server/Socket.cpp \
				srcs/http/server/Client.cpp srcs/http/server/RWCallback.cpp srcs/http/Webserv.cpp \
				srcs/iom/KqueueManage.cpp \
				srcs/address/InetAddress.cpp \
				srcs/util/Storage.cpp srcs/http/server/SocketStorage.cpp
OBJS 		= $(SRCS:.cpp=.o)
.c.o :
	$(CXX) $(CXXFLAGS) -c $< -o $@
all : $(NAME)
$(NAME) : $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $@
clean:
	$(RM) $(OBJS)
fclean: clean
	$(RM) $(NAME)
re:
	make fclean
	make all
.PHONY: all clean fclean re