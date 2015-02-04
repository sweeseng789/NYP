#include "MathUtility.h"

int factorial(int n)
{
	if (n == 1 || n == 0)
	{
		return 1;
	}
	else
	{
		return n * factorial(n - 1);	
	}
}

int nCr(int n, int r)
{
	if (n == r)
	{
		return 1;
	}
	if (r == 1)
	{
		return n;
	}
	if (r == 0)
	{
		return 1;
	}

	return nCr(n - 1, r) + nCr(n - 1, r - 1);
}

int nPr(int n, int r)
{
	long long findings;
	findings = factorial(n)/ factorial(n - r);
	return findings;
}

int nTermAP(int a, int d, int n)
{
	return 0;
}

int summationAP(int a, int d, int n)
{
	return 0;
}

int nTermGP(int a, int r, int n)
{
	return 0;
}

int summationGP(int a, int r, int n)
{
	return 0;
}