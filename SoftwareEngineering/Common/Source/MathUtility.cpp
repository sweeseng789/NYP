#include "MathUtility.h"

int factorial(int n)
{
	if (n == 1 || n == 0)
	{
		return 1;
	}
	else if (n < 0)
	{
		return NULL;
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
	//a = first term
	// d = difference
	int AP = 0;
	AP = a + (n - 1) * d;
	return AP;
}

int summationAP(int a, int d, int n)
{
	//S = (n/2) * (2a + (n-1) d)
	int APS = 0;
	APS = (n*(2*a+(n-1)*d))/2;
	//APS = (n/2) * ((2*a) + (n-1) * d);
	return APS;
}

int nTermGP(int a, int r, int n)
{//9, 3, 10
	//term = a * r^n-1
	int term = 0;
	int temp = 0;
	temp = pow((double)r, n -1);
	term = a * temp;
	return term;
}

int summationGP(int a, int r, int n)
{
	//9 ,3, 19
	//a(1 - r^n) / (1 - r)
	int term = 0;
	int temp = 0;
	temp  = pow((double)r, n);
	term = (a * (1-temp)) / (1 - r);
	return term;
}