SRC = *.cpp
NAME = $(shell basename $(SRC) .cpp).out

$(NAME): $(SRC)
	g++ $(SRC) -o $(NAME)

clean:
	rm -f $(NAME)
