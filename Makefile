CXX = gcc -g3  

CXXFLAGS = -Wall -Wextra -Werror -Wpedantic -I ./

SRCS =	main.c \
		book_utilities.c \
		library_utilities.c \
		tests.c

OBJS = $(SRCS:.c=.o)

TARGET = library_program

all: $(TARGET)

$(TARGET): $(OBJS)
	@echo "Linking the object files to create the executable..."
	@$(CXX) $(CXXFLAGS) -o $@ $^

%.o: %.cpp
	@echo "Compiling the source file $< into the object file $@..."
	@$(CXX) $(CXXFLAGS) -c $^ -o $@

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
