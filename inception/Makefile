all:
	cd srcs && docker-compose up -d --build

down:
	cd srcs && docker-compose down

clean:
	cd srcs && docker-compose down -v

fclean: clean
	cd srcs && docker-compose down --rmi all

re: clean all

.PHONY: all down clean fclean re
