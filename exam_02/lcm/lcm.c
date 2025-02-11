
unsigned int	lcm(unsigned int a, unsigned int b)
{
	if (a == 0 || b == 0)
		return (0);

	int lcm = 0;
	int max = 0;
	if (a > b)
		max = a;
	else
		max = b;
	lcm = max;
	while (lcm % a != 0 || lcm % b != 0)
	{
		lcm += max;
	}
	return (lcm);
}
