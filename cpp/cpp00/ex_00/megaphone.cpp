#include <iostream>
#include <cctype>
#include <string>

int	main(int ac, char **av) {
	if (ac != 1)
	{
		int i = 1;
		while (av[i])
		{
			int j = 0;
			std::string str = av[i];
			while (j < str.length())
				std::cout << (char)toupper(str[j++]);
			i++;
		}
		std::cout << std::endl;
		return (0);
	}
	std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
	return (1);
}
