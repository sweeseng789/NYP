#include"gtest\gtest.h"

#include"MathUtility.h"

//Test factorial for zero
TEST(FactorialTest, HandlesZeroInput)
{
	EXPECT_EQ(1, factorial(0));
	EXPECT_EQ(40320, factorial(8));
}

//Test factorial for Negative Value
TEST(FactorialTest, HandlesNegativeInput)
{
	EXPECT_EQ(NULL, factorial(-1));
}

//Test factorial of positive number
TEST(FactorialTest, HandlesPositiveInput) //10
{
	EXPECT_EQ(1, factorial(1));
	EXPECT_EQ(2, factorial(2));
	EXPECT_EQ(6, factorial(3));
	EXPECT_EQ(24, factorial(4));
	EXPECT_EQ(120, factorial(5));
	EXPECT_EQ(720, factorial(6));
	EXPECT_EQ(5040, factorial(7));
	EXPECT_EQ(40320, factorial(8));
	EXPECT_EQ(362880, factorial(9));
	EXPECT_EQ(3628800, factorial(10));
}

//Testing nCr
TEST(nCrTest, NumbersOfCombinations) //10
{
	EXPECT_EQ(6, nCr(4, 2));
	EXPECT_EQ(2598960, nCr(52, 5));
	EXPECT_EQ(45, nCr(10, 8));
	EXPECT_EQ(9139, nCr(39, 3));
	EXPECT_EQ(123410, nCr(43, 4));
	EXPECT_EQ(23, nCr(23, 1));
	EXPECT_EQ(201376, nCr(32, 5));
	EXPECT_EQ(9, nCr(9, 8));
	EXPECT_EQ(15, nCr(6, 2));
	EXPECT_EQ(1953, nCr(63, 2));
}

//Testing nPr
TEST(nPrTest, NumbersOfCombinations) //8
{
	EXPECT_EQ(20, nPr(5, 2));
	EXPECT_EQ(604800, nPr(10, 7));
	EXPECT_EQ(336, nPr(8, 3));
	EXPECT_EQ(60480, nPr(9, 6));
	EXPECT_EQ(20, nPr(5, 2));
	EXPECT_EQ(151200, nPr(10, 6));
	EXPECT_EQ(1, nPr(1, 1));
}

//Testing AP
TEST(APTest, TermDifferences) //10
{
	EXPECT_EQ(83, nTermAP(5, 3, 27));
	EXPECT_EQ(199, nTermAP(1, 2, 100));
	EXPECT_EQ(142, nTermAP(9, 7, 20));
	EXPECT_EQ(1797, nTermAP(6, 9, 200));
	EXPECT_EQ(94, nTermAP(6, 2, 45));
	EXPECT_EQ(203, nTermAP(9, 2, 98));
	EXPECT_EQ(969, nTermAP(78, 9, 100));
	EXPECT_EQ(576, nTermAP(100, 4, 120));
	EXPECT_EQ(440, nTermAP(56, 4, 97));
	EXPECT_EQ(512, nTermAP(8, 6, 85));
	EXPECT_EQ(24, nTermAP(8, 2, 9));
	EXPECT_EQ(11, nTermAP(8, 3, 2));
	EXPECT_EQ(689, nTermAP(354, 67, 6));
	EXPECT_EQ(354, nTermAP(354, 78, 1));
	EXPECT_EQ(1650, nTermAP(804, 423, 3));
	EXPECT_EQ(32529, nTermAP(804, 423, 76));
	EXPECT_EQ(2767, nTermAP(-23, 90, 32));
	EXPECT_EQ(280, nTermAP(-23, -3, -100));
	EXPECT_EQ(-320, nTermAP(-23, -3, 100));
	EXPECT_EQ(0, nTermAP(0, 0, 0));
	EXPECT_EQ(-223, nTermAP(-27, 98, -1));
}

//Testig APS
TEST(APSTest, SummationAP) //10
{
	EXPECT_EQ(225, summationAP(9, 3, 10));
	EXPECT_EQ(10000, summationAP(1, 2, 100));
	EXPECT_EQ(1510, summationAP(9, 7, 20));
	EXPECT_EQ(180300, summationAP(6, 9, 200));
	EXPECT_EQ(10388, summationAP(9, 2, 98));
	EXPECT_EQ(52350, summationAP(78, 9, 100));
	EXPECT_EQ(40560, summationAP(100, 4, 120));
	EXPECT_EQ(24056, summationAP(56, 4, 97));
	EXPECT_EQ(22618, summationAP(8, 6, 86));
	EXPECT_EQ(144, summationAP(8, 2, 9));
	EXPECT_EQ(19, summationAP(8, 3, 2));
	EXPECT_EQ(3129, summationAP(354, 67, 6));
	EXPECT_EQ(354, summationAP(354, 78, 1));
	EXPECT_EQ(3681, summationAP(804, 423, 3));
	EXPECT_EQ(1266654, summationAP(804, 423, 76));
	EXPECT_EQ(43904, summationAP(-23, 90, 32));
	EXPECT_EQ(-12850, summationAP(-23, -3, -100));
	EXPECT_EQ(-17150, summationAP(-23, -3, 100));
	EXPECT_EQ(0, summationAP(0, 0, 0));
	EXPECT_EQ(125, summationAP(-27, 98, -1));
}

//Testig nTermGP
TEST(nTermGPTest, TermOfGP)//10
{
	EXPECT_EQ(177147, nTermGP(9, 3, 10));
	EXPECT_EQ(512, nTermGP(1, 2, 10));
	EXPECT_EQ(189, nTermGP(7, 3, 4));
	EXPECT_EQ(2734375, nTermGP(7, 5, 9));
	EXPECT_EQ(324, nTermGP(4, 9, 3));
	EXPECT_EQ(486, nTermGP(6, 9, 3));
	EXPECT_EQ(45927, nTermGP(7, 3, 9));
	EXPECT_EQ(92, nTermGP(2, 46, 2));
	EXPECT_EQ(354294, nTermGP(54, 3, 9));
	EXPECT_EQ(5750, nTermGP(46, 5, 4));
	EXPECT_EQ(-65610, nTermGP(-10, 3, 9));
	EXPECT_EQ(0, nTermGP(-100, 6, -10));
	EXPECT_EQ(0, nTermGP(-100, -3, -10));
	EXPECT_EQ(112132, nTermGP(97, 34, 3));
	EXPECT_EQ(16384, nTermGP(4, 8, 5));
	EXPECT_EQ(405, nTermGP(5, 3, 5));
	EXPECT_EQ(12816, nTermGP(89, 12, 3));
	EXPECT_EQ(1152, nTermGP(8, 12, 3));
	EXPECT_EQ(8, nTermGP(8, 1, 3));
	EXPECT_EQ(1, nTermGP(1, 0, 1));
}

//Testig SumOfGP
TEST(SumOfGPTest, SumOfGP) //10
{
	EXPECT_EQ(265716, summationGP(9, 3, 10));
	EXPECT_EQ(1023, summationGP(1, 2, 10));
	EXPECT_EQ(280, summationGP(7, 3, 4));
	EXPECT_EQ(3417967, summationGP(7, 5, 9));
	EXPECT_EQ(4681, summationGP(1, 8, 5));
	EXPECT_EQ(546, summationGP(6, 9, 3));
	EXPECT_EQ(68887, summationGP(7, 3, 9));
	EXPECT_EQ(94, summationGP(2, 46, 2));
	EXPECT_EQ(531414, summationGP(54, 3, 9));
	EXPECT_EQ(7176, summationGP(46, 5, 4));
	EXPECT_EQ(-98410, summationGP(-10, 3, 9));
	EXPECT_EQ(20, summationGP(-100, 6, -10));
	EXPECT_EQ(-25, summationGP(-100, -3, -10));
	EXPECT_EQ(115527, summationGP(97, 34, 3));
	EXPECT_EQ(37449, summationGP(1, 8, 6));
	EXPECT_EQ(605, summationGP(5, 3, 5));
	EXPECT_EQ(13973, summationGP(89, 12, 3));
	EXPECT_EQ(1256, summationGP(8, 12, 3));
	EXPECT_EQ(56, summationGP(8, 2, 3));
	EXPECT_EQ(1, summationGP(1, 0, 1));
}