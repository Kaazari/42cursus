all:
	cd srcs && docker-compose up -d --build

down:
	cd srcs && docker-compose down

clean:
	cd srcs && docker-compose down -v

fclean: clean
	docker system prune -af

re: fclean all

.PHONY: all down clean fclean re
