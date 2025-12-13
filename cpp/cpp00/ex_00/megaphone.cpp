#include <iostream>
#include <cctype>

int	main(int ac, char **av) {
	if (ac != 1)
	{
		int i = 0;
		while (av[1][i])
			std::cout << toupper(av[1][i++]) << std::endl;
	}
}
