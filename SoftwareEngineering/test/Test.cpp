#include"gtest\gtest.h"

#include"MathUtility.h"

//Test factorial for zero
TEST(FactorialTest, HandlesZeroInput)
{
	EXPECT_EQ(1, factorial(0));
	EXPECT_EQ(40320, factorial(8));
}

//Test factorial of positive number
TEST(FactorialTest, HandlesPositiveInput)
{
	EXPECT_EQ(1, factorial(1));
	EXPECT_EQ(2, factorial(2));
	EXPECT_EQ(6, factorial(3));
	EXPECT_EQ(40320, factorial(8));
}

//Testing nCr
TEST(nCrTest, NumbersOfCombinations)
{
	EXPECT_EQ(6, nCr(4, 2));
}

//Testing nPr
TEST(nPrTest, NumbersOfCombinations)
{
	EXPECT_EQ(20, nPr(5, 2));
}

//Testing AP
TEST(APTest, TermDifferences)
{
	EXPECT_EQ(83, nTermAP(5, 3, 27));
}

//Testig APS
TEST(APSTest, SummationAP)
{
	EXPECT_EQ(225, summationAP(9, 3, 10));
}

//Testig nTermGP
TEST(nTermGPTest, TermOfGP)
{
	EXPECT_EQ(177147, nTermGP(9, 3, 10));
}

//Testig SumOfGP
TEST(SumOfGPTest, SumOfGP)
{
	EXPECT_EQ(265716, summationGP(9, 3, 10));
}