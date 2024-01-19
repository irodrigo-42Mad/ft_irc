NAME 			= 	libconsole.a

SRCS 			= 	./src/console.cpp 			\
					./src/terminal.cpp 			\
					./src/custom_buffer.cpp 	\

OBJS 			= 	$(SRCS:.cpp=.o)

DEPS 			= 	$(SRCS:.cpp=.d)

RM 				= 	rm -f

CXX 			= 	clang++

AR 				= 	ar rcs

INCLUDES 		= 	-I ./inc

CXXFLAGS 		= 	$(WARNFLAGS) $(INCLUDES) $(DEPFLAGS) $(SANITIZE) $(SYMBOLS)

WARNFLAGS 		= 	-Wextra -Wall -Werror

DEPFLAGS 		= 	-MMD

SANITIZE 		= 	-fsanitize=address

SYMBOLS 		= 	-g3

all: 		$(NAME)

$(NAME): 	$(OBJS)
	$(AR) $@ $?

fclean: 	clean
	$(RM) $(NAME)

clean:
	$(RM) $(OBJS) $(DEPS)

re: 		fclean all

-include 	$(DEPS)

.SILENT: 	fclean clean
.PHONY: 	all fclean clean re
