//#include "tests.h"
//
//#include <iostream>
//#include <iomanip>
//#include <string>
//#include <cmath>
//
//
//void RunRaySphereTests();
//void RunRayPolyTests();
//void RunRayCubeTests();
//
//typedef bool (*TestFunc)();
//
//int g_numTests = 0;
//int g_numSuccessful = 0;
//
//void ReportTest(std::string name, bool result);
//
//template<typename T>
//void RunTest(std::string name, T const& testValue, T const& expectedValue)
//{
//	ReportTest(name, testValue == expectedValue);
//}
//
//template<>
//void RunTest<double>(std::string name, double const& testValue, double const& expectedValue)
//{
//	ReportTest(name, (std::abs(testValue-expectedValue) / std::abs(expectedValue)) < 1e-3);
//}
//
//void RunTests()
//{
//	std::cout.sync_with_stdio(true);
//
//	RunRaySphereTests();
//	RunRayPolyTests();
//	RunRayCubeTests();
//
//	std::cout << g_numSuccessful << " of " << g_numTests << " tests successful. ";
//	if(g_numTests == g_numSuccessful)
//	{
//		std::cout << "A winner is you!";
//	}
//	std::cout << std::endl;
//}
//
//const double SQRT_HALF = 0.70710678; // square root of one half
//const double SQRT_TWO = 1.41421356; // figure it out
//
//const double IDENTITY_MATRIX[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
//const double DOUBLE_MATRIX[16] = {2,0,0,0,0,2,0,0,0,0,2,0,0,0,0,1};
//const double BACK5_MATRIX[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,-5,1};
//const double BACK5ANDTURN_MATRIX[16] = {SQRT_HALF,0,-SQRT_HALF,0,0,1,0,0,SQRT_HALF,0,SQRT_HALF,0,0,0,-5,1};
//
//
//const double ZERO_VECTOR[3] = {0,0,0};
//const double HALFX_VECTOR[3] = {0.5,0,0};
//const double THIRDX_VECTOR[3] = {0.33333333333333333,0,0};
//const double NEGX_VECTOR[3] = {-1,0,0};
//const double NEGZ_VECTOR[3] = {0,0,-1};
//const double POSZ_VECTOR[3] = {0,0,1};
//const double POSXPOSZ_VECTOR[3] = {1,0,1};
//const double ZNEGTEN_VECTOR[3] = {0,0,-10};
//const double ZPOSTEN_VECTOR[3] = {0,0,10};
//const double POSXNEGZ_NORM_VECTOR[3] = {SQRT_HALF, 0, -SQRT_HALF};
//const double NEGFIVEOFIVE_VECTOR[3] = {-5,0,5};
//
//const double POINT_N1N10[3] = {-1,-1,0};
//const double POINT_1N10[3] = {1,-1,0};
//const double POINT_010[3] = {0,1,0};
//const double POINT_N2N10[3] = {-2,-1,0};
//const double POINT_2N10[3] = {2,-1,0};
//
//const double TEN_KAZILLION = 1e26;
//
//void RunRaySphereTests()
//{
//	RunTest(
//		"Easy sphere", 
//		Test_RaySphereIntersect(ZERO_VECTOR, NEGZ_VECTOR, BACK5_MATRIX), 
//		4.0);
//
//	RunTest(
//		"Offset a bit",
//		Test_RaySphereIntersect(HALFX_VECTOR, NEGZ_VECTOR, BACK5_MATRIX), 
//		4.13397);
//
//	RunTest(
//		"What sphere",
//		Test_RaySphereIntersect(ZNEGTEN_VECTOR, NEGZ_VECTOR, BACK5_MATRIX),
//		-1.0);
//
//	RunTest(
//		"Looking back",
//		Test_RaySphereIntersect(ZNEGTEN_VECTOR, POSZ_VECTOR, BACK5_MATRIX),
//		4.0); // TODO change this to the right number
//
//	RunTest(
//		"West pole",
//		Test_RaySphereIntersect(ZERO_VECTOR, NEGZ_VECTOR, BACK5ANDTURN_MATRIX), 
//		4.0);
//
//	RunTest(
//		"Another angle",
//		Test_RaySphereIntersect(NEGFIVEOFIVE_VECTOR, POSXNEGZ_NORM_VECTOR, IDENTITY_MATRIX),
//		(5.0 * SQRT_TWO) - 1);
//}
//
//void RunRayPolyTests()
//{
//	RunTest(
//		"Hi, Tri",
//		Test_RayPolyIntersect(POSZ_VECTOR, NEGZ_VECTOR, POINT_N1N10, POINT_1N10, POINT_010, IDENTITY_MATRIX),
//		1.0);
//
//	RunTest(
//		"Bye, Tri",
//		Test_RayPolyIntersect(POSXPOSZ_VECTOR, NEGZ_VECTOR, POINT_N1N10, POINT_1N10, POINT_010, IDENTITY_MATRIX),
//		-1.0);
//
//	RunTest(
//		"Looking back",
//		Test_RayPolyIntersect(POSZ_VECTOR, POSZ_VECTOR, POINT_N1N10, POINT_1N10, POINT_010, IDENTITY_MATRIX),
//		-1.0);
//
//	RunTest(
//		"Flip it good",
//		Test_RayPolyIntersect(POSZ_VECTOR, NEGZ_VECTOR, POINT_010, POINT_1N10, POINT_N1N10, IDENTITY_MATRIX),
//		1.0);
//
//	RunTest(
//		"It moves",
//		Test_RayPolyIntersect(ZERO_VECTOR, NEGZ_VECTOR, POINT_N1N10, POINT_1N10, POINT_010, BACK5ANDTURN_MATRIX),
//		5.0);
//
//	RunTest(
//		"And turns",
//		Test_RayPolyIntersect(HALFX_VECTOR, NEGZ_VECTOR, POINT_N2N10, POINT_2N10, POINT_010, BACK5ANDTURN_MATRIX),
//		5.5); // TODO change this to the right number
//}
//
//void RunRayCubeTests()
//{
//	RunTest(
//		"Behold the cube",
//		Test_RayCubeIntersect(ZERO_VECTOR, NEGZ_VECTOR, BACK5_MATRIX),
//		4.5);
//
//	RunTest(
//		"The cube abides",
//		Test_RayCubeIntersect(THIRDX_VECTOR, NEGZ_VECTOR, BACK5_MATRIX),
//		4.5);
//
//	RunTest(
//		"Cuuuube!",
//		Test_RayCubeIntersect(NEGX_VECTOR, NEGZ_VECTOR, BACK5_MATRIX),
//		-1.0);
//
//	RunTest(
//		"Looking sharp, edge",
//		Test_RayCubeIntersect(ZERO_VECTOR, NEGZ_VECTOR, BACK5ANDTURN_MATRIX),
//		5.0 - SQRT_HALF);
//
//	RunTest(
//		"Big cube",
//		Test_RayCubeIntersect(ZPOSTEN_VECTOR, NEGZ_VECTOR, DOUBLE_MATRIX),
//		9.0);
//
//	RunTest(
//		"Strafing the cube",
//		Test_RayCubeIntersect(NEGFIVEOFIVE_VECTOR, POSXNEGZ_NORM_VECTOR, IDENTITY_MATRIX),
//		6.363961); // TODO change this to the right number
//}
//
//void ReportTest(std::string name, bool result)
//{
//	std::cout << std::setfill('.') << std::setw(50) << std::left << name;
//	std::cout << (result ? "SUCCESS" : "**FAILURE**") << std::endl;
//	g_numTests++;
//	if(result) 
//	{
//		g_numSuccessful++;
//	}
//	else
//	{
//		// It can be very useful to put a breakpoint here
//	}
//
//}
