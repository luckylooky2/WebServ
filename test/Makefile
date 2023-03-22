NAME 		= test
CXX 		= c++
#CXXFLAGS 	= -Wall -Wextra -Werror -std=c++98
RM 			= rm -f
SRCS 		=  ../srcs/log/LogFactory.cpp ../srcs/log/Logger.cpp \
				test_logger.cpp test.cpp
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