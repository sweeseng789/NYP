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