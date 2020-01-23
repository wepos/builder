NAME = builder

all:
	g++ -std=c++1z -O3 -o $(NAME) src/*.cpp -Iinclude/

clean:
	rm -rf *.o

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
