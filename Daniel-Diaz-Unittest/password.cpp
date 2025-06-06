#include <bits/stdc++.h>
#include<gtest/gtest.h>

/*
Unittest demo using Gtest.

Validate password.
- min 8 chars
- min 1 upper
- min 1 lower
- min 1 number
- no spaces

Install gtest in your machine and compile with:
g++ password.cpp -lgtest -lgtest_main -pthread -o password_test
then run: ./password_test
*/

using namespace std;


typedef long double ld;

bool is_valid_password(string password){
int upper = 0, lower = 0, number = 0;
bool nospace = 1;

for (char ch: password){
  upper += isupper(ch);
  lower += islower(ch);
  number += isdigit(ch);
  nospace &= ch != ' ';
}

return password.size() >= 8 &&  upper >= 1 && lower >= 1 && number >= 1 && nospace;
}


struct PasswordComp{
string password;
bool expected;

PasswordComp() : password(""), expected(0){}
PasswordComp(string s, bool e ) : password(s), expected(e){}
};

struct PasswordTest : public ::testing::TestWithParam<PasswordComp> {

};


TEST_P(PasswordTest, PasswordMatchesExpected) {
  PasswordComp test = GetParam(); // gets the current test case
  EXPECT_EQ(is_valid_password(test.password), test.expected);
}

INSTANTIATE_TEST_SUITE_P(AcceptedPasswordCases, PasswordTest, ::testing::Values(
  PasswordComp("Password1", true),           // valid
  PasswordComp("passWord1", true)            // valid
));

INSTANTIATE_TEST_SUITE_P(RejectedPasswordCases, PasswordTest, ::testing::Values(
  PasswordComp("password1", false),          // missing uppercase
  PasswordComp("PASSWORD1", false),          // missing lowercase
  PasswordComp("Password", false),           // missing number
  PasswordComp("Pass 123", false),           // space included
  PasswordComp("Pa1", false),                // too short
  PasswordComp("12345678", false),           // no letters
  PasswordComp("PASS1234", false),           // no lowercase
  PasswordComp("pass1234", false)            // no uppercase
));

int main(int argc, char * argv []){
testing::InitGoogleTest(&argc, argv);
return RUN_ALL_TESTS();
}