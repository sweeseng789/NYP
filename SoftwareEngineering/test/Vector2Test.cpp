#include "gtest\gtest.h"
#include "Vector2.h"
#include "MyMath.h"

//Testing Oveloaded Constructor 1.0
TEST(Vector2Test, Constructor) //20
{
	Vector2 v1(0, 0);
	EXPECT_NEAR(0, v1.x, Math::EPSILON);
	EXPECT_NEAR(0, v1.y, Math::EPSILON);

	Vector2 v2(1, 1);
	EXPECT_NEAR(1, v2.x, Math::EPSILON);
	EXPECT_NEAR(1, v2.y, Math::EPSILON);

	Vector2 v3(2, 2);
	EXPECT_NEAR(2, v3.x, Math::EPSILON);
	EXPECT_NEAR(2, v3.y, Math::EPSILON);

	Vector2 v4(3, 3);
	EXPECT_NEAR(3, v4.x, Math::EPSILON);
	EXPECT_NEAR(3, v4.y, Math::EPSILON);

	Vector2 v5(4, 4);
	EXPECT_NEAR(4, v5.x, Math::EPSILON);
	EXPECT_NEAR(4, v5.y, Math::EPSILON);

	Vector2 v6(5, 5);
	EXPECT_NEAR(5, v6.x, Math::EPSILON);
	EXPECT_NEAR(5, v6.y, Math::EPSILON);

	Vector2 v7(6, 6);
	EXPECT_NEAR(6, v7.x, Math::EPSILON);
	EXPECT_NEAR(6, v7.y, Math::EPSILON);

	Vector2 v8(7, 7);
	EXPECT_NEAR(7, v8.x, Math::EPSILON);
	EXPECT_NEAR(7, v8.y, Math::EPSILON);

	Vector2 v9(8, 8);
	EXPECT_NEAR(8, v9.x, Math::EPSILON);
	EXPECT_NEAR(8, v9.y, Math::EPSILON);

	Vector2 v10(9, 9);
	EXPECT_NEAR(9, v10.x, Math::EPSILON);
	EXPECT_NEAR(9, v10.y, Math::EPSILON);

	Vector2 v11(-1, -1);
	EXPECT_NEAR(-1, v11.x, Math::EPSILON);
	EXPECT_NEAR(-1, v11.y, Math::EPSILON);

	Vector2 v12(-2, -2);
	EXPECT_NEAR(-2, v12.x, Math::EPSILON);
	EXPECT_NEAR(-2, v12.y, Math::EPSILON);

	Vector2 v13(-3, -3);
	EXPECT_NEAR(-3, v13.x, Math::EPSILON);
	EXPECT_NEAR(-3, v13.y, Math::EPSILON);

	Vector2 v14(-4, -4);
	EXPECT_NEAR(-4, v14.x, Math::EPSILON);
	EXPECT_NEAR(-4, v14.y, Math::EPSILON);

	Vector2 v15(-5, -5);
	EXPECT_NEAR(-5, v15.x, Math::EPSILON);
	EXPECT_NEAR(-5, v15.y, Math::EPSILON);

	Vector2 v16(-6, -6);
	EXPECT_NEAR(-6, v16.x, Math::EPSILON);
	EXPECT_NEAR(-6, v16.y, Math::EPSILON);

	Vector2 v17(-7, -7);
	EXPECT_NEAR(-7, v17.x, Math::EPSILON);
	EXPECT_NEAR(-7, v17.y, Math::EPSILON);

	Vector2 v18(-8, -8);
	EXPECT_NEAR(-8, v18.x, Math::EPSILON);
	EXPECT_NEAR(-8, v18.y, Math::EPSILON);

	Vector2 v19(-9, -9);
	EXPECT_NEAR(-9, v19.x, Math::EPSILON);
	EXPECT_NEAR(-9, v19.y, Math::EPSILON);

	Vector2 v20(-10, -10);
	EXPECT_NEAR(-10, v20.x, Math::EPSILON);
	EXPECT_NEAR(-10, v20.y, Math::EPSILON);
}

//Testing Overloaded Constructor 2.0
TEST(Vector2TestOC, ConstructorAgain) //20
{
	Vector2 v1(1, 1);
	Vector2 v2(v1);
	EXPECT_NEAR(v1.x, v2.x, Math::EPSILON);
	EXPECT_NEAR(v1.y, v2.y, Math::EPSILON);

	Vector2 v3(2, 2);
	Vector2 v4(v3);
	EXPECT_NEAR(v3.x, v4.x, Math::EPSILON);
	EXPECT_NEAR(v3.y, v4.y, Math::EPSILON);

	Vector2 v5(3, 3);
	Vector2 v6(v5);
	EXPECT_NEAR(v5.x, v6.x, Math::EPSILON);
	EXPECT_NEAR(v5.y, v6.y, Math::EPSILON);

	Vector2 v7(4, 4);
	Vector2 v8(v7);
	EXPECT_NEAR(v7.x, v8.x, Math::EPSILON);
	EXPECT_NEAR(v7.y, v8.y, Math::EPSILON);

	Vector2 v9(5, 5);
	Vector2 v10(v9);
	EXPECT_NEAR(v9.x, v10.x, Math::EPSILON);
	EXPECT_NEAR(v9.y, v10.y, Math::EPSILON);

	Vector2 v11(6, 6);
	Vector2 v12(v11);
	EXPECT_NEAR(v11.x, v12.x, Math::EPSILON);
	EXPECT_NEAR(v11.y, v12.y, Math::EPSILON);

	Vector2 v13(7, 7);
	Vector2 v14(v13);
	EXPECT_NEAR(v13.x, v14.x, Math::EPSILON);
	EXPECT_NEAR(v13.y, v14.y, Math::EPSILON);

	Vector2 v15(8, 8);
	Vector2 v16(v15);
	EXPECT_NEAR(v15.x, v16.x, Math::EPSILON);
	EXPECT_NEAR(v15.y, v16.y, Math::EPSILON);

	Vector2 v17(9, 9);
	Vector2 v18(v17);
	EXPECT_NEAR(v17.x, v18.x, Math::EPSILON);
	EXPECT_NEAR(v17.y, v18.y, Math::EPSILON);

	Vector2 v19(10, 10);
	Vector2 v20(v19);
	EXPECT_NEAR(v19.x, v20.x, Math::EPSILON);
	EXPECT_NEAR(v19.y, v20.y, Math::EPSILON);

	Vector2 v21(-1, -1);
	Vector2 v22(v21);
	EXPECT_NEAR(v21.x, v22.x, Math::EPSILON);
	EXPECT_NEAR(v21.y, v22.y, Math::EPSILON);

	Vector2 v23(-2, -2);
	Vector2 v24(v23);
	EXPECT_NEAR(v23.x, v24.x, Math::EPSILON);
	EXPECT_NEAR(v23.y, v24.y, Math::EPSILON);

	Vector2 v25(-3, -3);
	Vector2 v26(v25);
	EXPECT_NEAR(v25.x, v26.x, Math::EPSILON);
	EXPECT_NEAR(v25.y, v26.y, Math::EPSILON);

	Vector2 v27(-4, -4);
	Vector2 v28(v27);
	EXPECT_NEAR(v27.x, v28.x, Math::EPSILON);
	EXPECT_NEAR(v27.y, v28.y, Math::EPSILON);

	Vector2 v29(-5, -5);
	Vector2 v30(v29);
	EXPECT_NEAR(v29.x, v30.x, Math::EPSILON);
	EXPECT_NEAR(v29.y, v30.y, Math::EPSILON);

	Vector2 v31(-6, -6);
	Vector2 v32(v31);
	EXPECT_NEAR(v31.x, v32.x, Math::EPSILON);
	EXPECT_NEAR(v31.y, v32.y, Math::EPSILON);

	Vector2 v33(-7, -7);
	Vector2 v34(v33);
	EXPECT_NEAR(v33.x, v34.x, Math::EPSILON);
	EXPECT_NEAR(v33.y, v34.y, Math::EPSILON);

	Vector2 v35(-8, -8);
	Vector2 v36(v35);
	EXPECT_NEAR(v35.x, v36.x, Math::EPSILON);
	EXPECT_NEAR(v35.y, v36.y, Math::EPSILON);

	Vector2 v37(-9, -9);
	Vector2 v38(v37);
	EXPECT_NEAR(v37.x, v38.x, Math::EPSILON);
	EXPECT_NEAR(v37.y, v38.y, Math::EPSILON);

	Vector2 v39(-10, -10);
	Vector2 v40(v39);
	EXPECT_NEAR(v39.x, v40.x, Math::EPSILON);
	EXPECT_NEAR(v39.y, v40.y, Math::EPSILON);
}

//Testing Operator - Adding
TEST(Vector2TestOperator, Adding) //10
{
	Vector2 v1(1, 1);
	Vector2 v2(2, 2);
	EXPECT_NEAR(3, v2.operator+(v1).x, Math::EPSILON);
	EXPECT_NEAR(3, v2.operator+(v1).y, Math::EPSILON);

	Vector2 v3(3, 3);
	Vector2 v4(3, 3);
	EXPECT_NEAR(6, v4.operator+(v3).x, Math::EPSILON);
	EXPECT_NEAR(6, v4.operator+(v3).y, Math::EPSILON);

	Vector2 v5(9, 3);
	Vector2 v6(3, 3);
	EXPECT_NEAR(12, v6.operator+(v5).x, Math::EPSILON);
	EXPECT_NEAR(6, v6.operator+(v5).y, Math::EPSILON);

	Vector2 v7(4, 1);
	Vector2 v8(0, 7);
	EXPECT_NEAR(4, v8.operator+(v7).x, Math::EPSILON);
	EXPECT_NEAR(8, v8.operator+(v7).y, Math::EPSILON);

	Vector2 v9(13, 84);
	Vector2 v10(32, 73);
	EXPECT_NEAR(45, v10.operator+(v9).x, Math::EPSILON);
	EXPECT_NEAR(157, v10.operator+(v9).y, Math::EPSILON);

	Vector2 v11(23523, 432);
	Vector2 v12(24, 53445);
	EXPECT_NEAR(23547, v12.operator+(v11).x, Math::EPSILON);
	EXPECT_NEAR(53877, v12.operator+(v11).y, Math::EPSILON);

	Vector2 v13(-235, 56);
	Vector2 v14(24, -53);
	EXPECT_NEAR(-211, v14.operator+(v13).x, Math::EPSILON);
	EXPECT_NEAR(3, v14.operator+(v13).y, Math::EPSILON);

	Vector2 v15(-25, -45);
	Vector2 v16(-5, -33);
	EXPECT_NEAR(-30, v16.operator+(v15).x, Math::EPSILON);
	EXPECT_NEAR(-78, v16.operator+(v15).y, Math::EPSILON);

	Vector2 v17(-1, -1);
	Vector2 v18(-1, -1);
	EXPECT_NEAR(-2, v18.operator+(v17).x, Math::EPSILON);
	EXPECT_NEAR(-2, v18.operator+(v17).y, Math::EPSILON);

	Vector2 v19(-3, -90);
	Vector2 v20(-5, -32);
	EXPECT_NEAR(-8, v20.operator+(v19).x, Math::EPSILON);
	EXPECT_NEAR(-122, v20.operator+(v19).y, Math::EPSILON);
}

//Testing Operator - Minus
TEST(Vector2TestOperator, Minus) //10
{
	Vector2 v1(1, 1);
	Vector2 v2(2, 2);
	EXPECT_NEAR(1, v2.operator-(v1).x, Math::EPSILON);
	EXPECT_NEAR(1, v2.operator-(v1).y, Math::EPSILON);

	Vector2 v3(3, 3);
	Vector2 v4(3, 3);
	EXPECT_NEAR(0, v4.operator-(v3).x, Math::EPSILON);
	EXPECT_NEAR(0, v4.operator-(v3).y, Math::EPSILON);

	Vector2 v5(9, 3);
	Vector2 v6(3, 3);
	EXPECT_NEAR(-6, v6.operator-(v5).x, Math::EPSILON);
	EXPECT_NEAR(0, v6.operator-(v5).y, Math::EPSILON);

	Vector2 v7(4, 1);
	Vector2 v8(0, 7);
	EXPECT_NEAR(-4, v8.operator-(v7).x, Math::EPSILON);
	EXPECT_NEAR(6, v8.operator-(v7).y, Math::EPSILON);

	Vector2 v9(13, 84);
	Vector2 v10(32, 73);
	EXPECT_NEAR(19, v10.operator-(v9).x, Math::EPSILON);
	EXPECT_NEAR(-11, v10.operator-(v9).y, Math::EPSILON);

	Vector2 v11(23523, 432);
	Vector2 v12(24, 53445);
	EXPECT_NEAR(-23499, v12.operator-(v11).x, Math::EPSILON);
	EXPECT_NEAR(53013, v12.operator-(v11).y, Math::EPSILON);

	Vector2 v13(-235, 56);
	Vector2 v14(24, -53);
	EXPECT_NEAR(259, v14.operator-(v13).x, Math::EPSILON);
	EXPECT_NEAR(-109, v14.operator-(v13).y, Math::EPSILON);

	Vector2 v15(-25, -45);
	Vector2 v16(-5, -33);
	EXPECT_NEAR(20, v16.operator-(v15).x, Math::EPSILON);
	EXPECT_NEAR(12, v16.operator-(v15).y, Math::EPSILON);

	Vector2 v17(-1, -1);
	Vector2 v18(-1, -1);
	EXPECT_NEAR(0, v18.operator-(v17).x, Math::EPSILON);
	EXPECT_NEAR(0, v18.operator-(v17).y, Math::EPSILON);

	Vector2 v19(-3, -90);
	Vector2 v20(-5, -32);
	EXPECT_NEAR(-2, v20.operator-(v19).x, Math::EPSILON);
	EXPECT_NEAR(58, v20.operator-(v19).y, Math::EPSILON);
}

//Testing Operator - Minus Test 2
TEST(Vector2TestOperator, Minus2) //10
{
	Vector2 v1(1, 1);
	EXPECT_NEAR(-1, v1.operator-().x, Math::EPSILON);
	EXPECT_NEAR(-1, v1.operator-().y, Math::EPSILON);

	Vector2 v2(3, 3);
	EXPECT_NEAR(-3, v2.operator-().x, Math::EPSILON);
	EXPECT_NEAR(-3, v2.operator-().y, Math::EPSILON);

	Vector2 v3(9, 3);
	EXPECT_NEAR(-9, v3.operator-().x, Math::EPSILON);
	EXPECT_NEAR(-3, v3.operator-().y, Math::EPSILON);

	Vector2 v4(4, 1);
	EXPECT_NEAR(-4, v4.operator-().x, Math::EPSILON);
	EXPECT_NEAR(-1, v4.operator-().y, Math::EPSILON);

	Vector2 v5(13, 84);
	EXPECT_NEAR(-13, v5.operator-().x, Math::EPSILON);
	EXPECT_NEAR(-84, v5.operator-().y, Math::EPSILON);

	Vector2 v6(23523, 432);
	EXPECT_NEAR(-23523, v6.operator-().x, Math::EPSILON);
	EXPECT_NEAR(-432, v6.operator-().y, Math::EPSILON);

	Vector2 v7(-235, 56);
	EXPECT_NEAR(235, v7.operator-().x, Math::EPSILON);
	EXPECT_NEAR(-56, v7.operator-().y, Math::EPSILON);

	Vector2 v8(-25, -45);
	EXPECT_NEAR(25, v8.operator-().x, Math::EPSILON);
	EXPECT_NEAR(45, v8.operator-().y, Math::EPSILON);

	Vector2 v9(-1, -1);
	EXPECT_NEAR(1, v9.operator-().x, Math::EPSILON);
	EXPECT_NEAR(1, v9.operator-().y, Math::EPSILON);

	Vector2 v10(-3, -90);
	EXPECT_NEAR(3, v10.operator-().x, Math::EPSILON);
	EXPECT_NEAR(90, v10.operator-().y, Math::EPSILON);
}

//Testing Operator - Scalar
TEST(Vector2TestOperator, Scalar) //10
{
	Vector2 v1(1, 1);
	EXPECT_NEAR(2, v1.operator*(2).x, Math::EPSILON);
	EXPECT_NEAR(2, v1.operator*(2).y, Math::EPSILON);

	Vector2 v2(3, 3);
	EXPECT_NEAR(18, v2.operator*(6).x, Math::EPSILON);
	EXPECT_NEAR(6, v2.operator*(2).y, Math::EPSILON);

	Vector2 v3(9, 3);
	EXPECT_NEAR(81, v3.operator*(9).x, Math::EPSILON);
	EXPECT_NEAR(9, v3.operator*(3).y, Math::EPSILON);

	Vector2 v4(4, 1);
	EXPECT_NEAR(21692, v4.operator*(5423).x, Math::EPSILON);
	EXPECT_NEAR(324, v4.operator*(324).y, Math::EPSILON);

	Vector2 v5(13, 84);
	EXPECT_NEAR(702, v5.operator*(54).x, Math::EPSILON);
	EXPECT_NEAR(5376, v5.operator*(64).y, Math::EPSILON);

	Vector2 v6(23523, 432);
	EXPECT_NEAR(823305, v6.operator*(35).x, Math::EPSILON);
	EXPECT_NEAR(18576, v6.operator*(43).y, Math::EPSILON);

	Vector2 v7(-235, 56);
	EXPECT_NEAR(-7990, v7.operator*(34).x, Math::EPSILON);
	EXPECT_NEAR(317632, v7.operator*(5672).y, Math::EPSILON);

	Vector2 v8(-25, -45);
	EXPECT_NEAR(1050, v8.operator*(-42).x, Math::EPSILON);
	EXPECT_NEAR(90, v8.operator*(-2).y, Math::EPSILON);

	Vector2 v9(-1, -1);
	EXPECT_NEAR(0, v9.operator*(0).x, Math::EPSILON);
	EXPECT_NEAR(0, v9.operator*(0).y, Math::EPSILON);

	Vector2 v10(-3, -90);
	EXPECT_NEAR(153, v10.operator*(-51).x, Math::EPSILON);
	EXPECT_NEAR(4860, v10.operator*(-54).y, Math::EPSILON);
}

//Testing Length
TEST(Vector2TestLength, Length)//10
{
	Vector2 v1(1, 1);
	EXPECT_NEAR(1.414213562, v1.Length(), Math::EPSILON);

	Vector2 v2(3, 3);
	EXPECT_NEAR(4.242640687, v2.Length(), Math::EPSILON);

	Vector2 v3(9, 3);
	EXPECT_NEAR(9.486832981, v3.Length(), Math::EPSILON);

	Vector2 v4(4, 1);
	EXPECT_NEAR(4.123105626, v4.Length(), Math::EPSILON);

	Vector2 v5(13, 84);
	EXPECT_NEAR(85, v5.Length(), Math::EPSILON);

	Vector2 v6(4, 0);
	EXPECT_NEAR(4, v6.Length(), Math::EPSILON);

	Vector2 v7(235, 56);
	EXPECT_NEAR(241.5802144, v7.Length(), Math::EPSILON);

	Vector2 v8(20, 30);
	EXPECT_NEAR(36.05551275, v8.Length(), Math::EPSILON);

	Vector2 v9(0, 0);
	EXPECT_NEAR(0, v9.Length(), Math::EPSILON);

	Vector2 v10(3, 90);
	EXPECT_NEAR(90.04998612, v10.Length(), Math::EPSILON);
}

//Testing Operator - Dot Product
TEST(Vector2TestDotProduct, DotProduct)//10
{
	Vector2 v1(1, 1);
	Vector2 v2(2, 2);
	EXPECT_NEAR(4, v2.Dot(v1), Math::EPSILON);

	Vector2 v3(3, 3);
	Vector2 v4(3, 3);
	EXPECT_NEAR(18, v4.Dot(v3), Math::EPSILON);

	Vector2 v5(9, 3);
	Vector2 v6(3, 3);
	EXPECT_NEAR(36, v6.Dot(v5), Math::EPSILON);

	Vector2 v7(4, 1);
	Vector2 v8(0, 7);
	EXPECT_NEAR(7, v8.Dot(v7), Math::EPSILON);

	Vector2 v9(13, 84);
	Vector2 v10(32, 73);
	EXPECT_NEAR(6548, v10.Dot(v9), Math::EPSILON);

	Vector2 v11(23523, 432);
	Vector2 v12(24, 53445);
	EXPECT_NEAR(23652792, v12.Dot(v11), Math::EPSILON);

	Vector2 v13(-235, 56);
	Vector2 v14(24, -53);
	EXPECT_NEAR(-8608, v14.Dot(v13), Math::EPSILON);

	Vector2 v15(-25, -45);
	Vector2 v16(-5, -33);
	EXPECT_NEAR(1610, v16.Dot(v15), Math::EPSILON);

	Vector2 v17(-1, -1);
	Vector2 v18(-1, -1);
	EXPECT_NEAR(2, v18.Dot(v17), Math::EPSILON);

	Vector2 v19(-3, -90);
	Vector2 v20(-5, -32);
	EXPECT_NEAR(2895, v20.Dot(v19), Math::EPSILON);
}

//Testing Normalized
TEST(Vector2TestNormalized, Normalized) //10
{
	Vector2 v1(1, 1);
	EXPECT_NEAR(-1, v1.Normalized().x, Math::EPSILON);
	EXPECT_NEAR(1, v1.Normalized().y, Math::EPSILON);

	Vector2 v2(3, 3);
	EXPECT_NEAR(-3, v2.Normalized().x, Math::EPSILON);
	EXPECT_NEAR(3, v2.Normalized().y, Math::EPSILON);

	Vector2 v3(9, 3);
	EXPECT_NEAR(-3, v3.Normalized().x, Math::EPSILON);
	EXPECT_NEAR(9, v3.Normalized().y, Math::EPSILON);

	Vector2 v4(4, 1);
	EXPECT_NEAR(-1, v4.Normalized().x, Math::EPSILON);
	EXPECT_NEAR(4, v4.Normalized().y, Math::EPSILON);

	Vector2 v5(13, 84);
	EXPECT_NEAR(-84, v5.Normalized().x, Math::EPSILON);
	EXPECT_NEAR(13, v5.Normalized().y, Math::EPSILON);

	Vector2 v6(4, 0);
	EXPECT_NEAR(0, v6.Normalized().x, Math::EPSILON);
	EXPECT_NEAR(4, v6.Normalized().y, Math::EPSILON);

	Vector2 v7(235, 56);
	EXPECT_NEAR(-56, v7.Normalized().x, Math::EPSILON);
	EXPECT_NEAR(235, v7.Normalized().y, Math::EPSILON);

	Vector2 v8(20, 30);
	EXPECT_NEAR(-30, v8.Normalized().x, Math::EPSILON);
	EXPECT_NEAR(20, v8.Normalized().y, Math::EPSILON);

	Vector2 v9(0, 0);
	EXPECT_NEAR(0, v9.Normalized().x, Math::EPSILON);
	EXPECT_NEAR(0, v9.Normalized().y, Math::EPSILON);

	Vector2 v10(3, 90);
	EXPECT_NEAR(-90, v10.Normalized().x, Math::EPSILON);
	EXPECT_NEAR(3, v10.Normalized().y, Math::EPSILON);
}