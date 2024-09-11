CXX = gcc -g3

CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -I ./includes/

SRCS =	src/main.c \
	src/book_utilities.c \
	src/library_utilities.c \
	src/tests/tests.c

OBJS = $(SRCS:.c=.o)

TARGET = library_program

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking the object files to create the executable..."
	@$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.c
	@echo "Compiling the source file $< into the object file $@..."
	@$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	@echo "Removing the object files..."
	@rm -f $(OBJS) *.gch

fclean: clean
	@echo "Removing the executable..."
	@rm -f $(TARGET)

re: fclean all

test: $(TARGET)
	@echo "Running the program..."
	@./$(TARGET)

memory: $(TARGET)
	@echo "Running the program with valgrind..."
	@valgrind -s ./$(TARGET)

.PHONY: all clean fclean re test memory
