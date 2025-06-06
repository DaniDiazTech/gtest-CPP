#include <bits/stdc++.h>
#include<gtest/gtest.h>

/*
  Unittest demo using Gtest.

  Calculate 2d distance.

  Install gtest in your machine and compile with:
  g++ distance.cpp -lgtest -lgtest_main -pthread -o distance_test
  then run: ./distance_test
*/

using namespace std;


typedef long double ld;


const ld EPS = 1e-5;

struct Point{
  ld x, y;

  Point(): x(0), y(0){
  }
  Point(ld xx, ld yy) : x(xx), y(yy){
  }
};


ld calculate_distance(Point p1, Point p2){
  return sqrt( (p1.x - p2.x) * (p1.x - p2.x) +  (p1.y - p2.y) * (p1.y - p2.y)); 
}


struct PointDistanceComp{
  Point p1, p2;
  ld expected;
  PointDistanceComp() : p1({0,0}), p2({0,0}), expected(0){}

  PointDistanceComp(Point a, Point b, ld e) : p1(a), p2(b), expected(e) {}

};


class DistanceTest : public ::testing::TestWithParam<PointDistanceComp> {
protected:
  const ld EPS = 1e-5;
};

TEST_P(DistanceTest, DistanceMatchesExpected) {
  PointDistanceComp test = GetParam(); // gets the current test case
  EXPECT_NEAR(calculate_distance(test.p1, test.p2), test.expected, EPS);
}

INSTANTIATE_TEST_SUITE_P(PositiveCases, DistanceTest, ::testing::Values(
  PointDistanceComp{{1, 1}, {2, 2}, 1.4142136},
  PointDistanceComp{{21, 89}, {12, 2}, 87.464278}
));

INSTANTIATE_TEST_SUITE_P(NegativeCases, DistanceTest, ::testing::Values(
  PointDistanceComp{{-1, -1}, {-2, -2}, 1.4142136},
  PointDistanceComp{{-19, -2}, {-21, -32}, 30.066593}
));

INSTANTIATE_TEST_SUITE_P(MixedCases, DistanceTest, ::testing::Values(
  PointDistanceComp{{-1, -1}, {1, 1}, 2.8284271},
  PointDistanceComp{{12, -53}, {-21, 100}, 156.51837}
));

int main(int argc, char * argv []){
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}