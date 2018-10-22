// References:
//   Unit testing based on Catch framework: https://github.com/catchorg/Catch2
//   Catch tutorial: https://github.com/catchorg/Catch2/blob/master/docs/tutorial.md#top
//   install:     sudo apt-get install catch
//   compilation: g++ -std=c++11 -Wall -o main.exe main.cpp
//   execution:   ./main.exe
//

// let Catch provide main():
#define CATCH_CONFIG_MAIN

// gain access to Catch framework:
#include "catch.hpp"

// our Counter class:
#include "counter.h"
#include <string>

// *****************************************************************
//
// Test cases:
// 
// *****************************************************************

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;


TEST_CASE( "empty Counter<int>", "[Counter]" ) 
{
  Counter<int> C;

  REQUIRE(C.empty() == true);
  REQUIRE(C.size() == 0);
}//test


 /*TEST_CASE( "Counter<int> with 7 element", "[Counter]" ) 
 {
   Counter<int> C;
   Counter<int> C2;
   Counter<int> C3;

 
   REQUIRE(C.size() == 0);
   REQUIRE(C.empty() == true);
   
   SECTION("inserting element")
   {
	   C.insert(1000);
	   C.insert(100);
	   C.insert(50);
	   
	  

	   REQUIRE(C.size() == 2);
	   REQUIRE(!C.empty());

	   SECTION("inserting more elements") {
	   C.insert(60);
	   C.insert(600);
	   C2.insert(6000);
	   C2.insert(600);
	   C2.insert(100);
	   C2.insert(100);
	   bool a = C[50];
	   bool b = C[600];
	   bool c = C[6000];
	   bool d = C[1600];
	   
	   int e = C(600);
	   int f = C(100);
	   int g = C(1600);
	   int h = C(60);


	   C.print();
	   cout << endl;

	   C2.print();
	   cout << endl;

	   C3.print();
	   cout << endl;
	  
	   C = C3;
	   cout << "C: " << endl;
	   C.print();
	   

	   auto  iter = C.begin(); 
	   while (iter != C.end()) { 
		   cout << *iter << endl;
		   ++iter; 
	   }

	   auto iter2 = C.end();
	   cout << *iter2 << endl;

	   for (auto e : C)
		   cout << e << endl;

	   REQUIRE(C.size() == 6);
	   REQUIRE(!C.empty());
	}

   }
 }//test */



class Student
{
private:
	int UIN, Mid, Fnl;

public:
	Student()
		: UIN(-1), Mid(-1), Fnl(-1)
	{ }

	Student(int uin, int mid, int fnl)
		: UIN(uin), Mid(mid), Fnl(fnl)
	{ }

	int getUIN() const
	{
		return UIN;
	}

	double getExamAvg() const
	{
		return (Mid + Fnl) / 2.0;
	}

	//
	// lhs < rhs
	//
	// returns true if lhs < rhs, false otherwise.
	//
	bool operator<(const Student& other) const
	{
		//
		// NOTE: lhs is "this" object.
		// 
		if (this->UIN < other.UIN)
			return true;
		else
			return false;
	}
};

TEST_CASE("Counter<Student> with 1 element", "[Counter]")
{
	Counter<Student> C;

	REQUIRE(C.size() == 0);
	REQUIRE(C.empty() == true);

	SECTION("inserting 1 studnet")
	{
		Student S(123456, 100, 88);

		C.insert(S);

		REQUIRE(C.size() == 1);
		REQUIRE(!C.empty());

		SECTION("element contains")
		{
			Student S2(123456, 0, 0);  // create a student with matching UIN:

			REQUIRE(C[S2] == true);
		}

		SECTION("element count")
		{
			Student S2(123456, 0, 0);  // create a student with matching UIN:

			REQUIRE(C(S2) == 1);
		}

		SECTION("unknown elements not contained")
		{
			Student S3(010100, 0, 0);  // student #1 that doesn't match:
			Student S4(999999, 0, 0);  // student #2
			Student S5(1234567, 0, 0);  // student #3

			REQUIRE(!C[S3]);
			REQUIRE(!C[S4]);
			REQUIRE(!C[S5]);
		}

		SECTION("unknown element counts")
		{
			Student S3(010100, 0, 0);  // student #1 that doesn't match:
			Student S4(999999, 0, 0);  // student #2
			Student S5(1234567, 0, 0);  // student #3

			REQUIRE(C(S3) == -1);
			REQUIRE(C(S4) == -1);
			REQUIRE(C(S5) == -1);
		}
	}
}//test

TEST_CASE("Counter<int> copy constructor 2.0", "[Counter]")
{
	Counter<int> C1;
	// Insert 3 values into C1
	C1 += 5; C1 += 5;          // 2 copies
	C1 += 4;
	C1 += 6; C1 += 6; C1 += 6; // 3 copies
							   // Test the copy constructor
	SECTION("copy construct C2 from C1")
	{	// Copy construct C2 from C1
		Counter<int> C2(C1);
		// Test that the sizes are correct
		REQUIRE(C1.size() == 3);
		REQUIRE(C2.size() == C1.size());
		// Test that C1 still has the correct values
		REQUIRE((C1[5] == true && C1(5) == 2));
		REQUIRE((C1[4] == true && C1(4) == 1));
		REQUIRE((C1[6] == true && C1(6) == 3));
		// Test that C2 copied the values from C1
		SECTION("check that C2 copied the values from C1")
		{
			REQUIRE(C2[5] == true);
			REQUIRE(C2[4] == true);
			REQUIRE(C2[6] == true);
		}
		// Test that C2 copied the counts from C1
		SECTION("check that C2 copied the counts from C1")
		{
			REQUIRE(C2(5) == C1(5));
			REQUIRE(C2(4) == C1(4));
			REQUIRE(C2(6) == C1(6));
		}
		// Test that C1 and C2 are independent (in memory)
		SECTION("check that C1 and C2 are independent")
		{	// Insert 1 new value into C1
			C1 += 7;
			// Insert 2 new values into C2
			C2 += 3;
			C2 += 2;
			// Test that C1 size has been updated
			// and new value was inserted
			REQUIRE(C1.size() == 4);
			REQUIRE((C1[7] == true && C1(7) == 1));
			// Test that C2 size has been updated
			// and new values were inserted
			REQUIRE(C2.size() == 5);
			REQUIRE((C2[3] == true && C2(3) == 1));
			REQUIRE((C2[2] == true && C2(2) == 1));
			// Test that C1 does not have values from C2
			SECTION("check that C1 does not have values from C2")
			{
				REQUIRE((C1[3] == false && C1(3) == -1));
				REQUIRE((C1[2] == false && C1(2) == -1));
			}
			// Test that C2 does not have values from C1
			SECTION("check that C2 does not have values from C1")
			{
				REQUIRE((C2[7] == false && C2(7) == -1));
			}
			// Test that C1 has correct order (unaffected by C2)
			SECTION("check that C1 ordering is correct")
			{
				// Correct order: 4, 5, 6, 7
				auto iter = C1.begin();
				cout << *iter << endl;
				// Test order
				REQUIRE((*iter == 4));
				REQUIRE((*++iter == 5));
				REQUIRE((*++iter == 6));
				REQUIRE((*++iter == 7));
				// Test for end of sequence
				REQUIRE(!(++iter != C1.end()));
			}
			// Test that C2 has correct order (unaffected by C1)
			SECTION("check that C2 ordering is correct")
			{
				// Correct order: 2, 3, 4, 5, 6
				auto iter = C2.begin();
				// Test order
				REQUIRE((*iter == 2));
				REQUIRE((*++iter == 3));
				REQUIRE((*++iter == 4));
				REQUIRE((*++iter == 5));
				REQUIRE((*++iter == 6));
				// Test for end of sequence
				REQUIRE(!(++iter != C2.end()));
			}

		}
	}

}// test















///////////////////////////////////////INT TESTS//////////////////////////////////////////

//4 cap
 
TEST_CASE("Counter<int> add elements in order (4 capacity)", "[Counter]")
 {
	 Counter<int> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(1);
		 C.insert(2);
		 C.insert(3);
		 C.insert(4);
		 

		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty()); 
		 }
	 }


 TEST_CASE("Counter<int> add elements not in order (4 capacity)", "[Counter]")
 {
	 Counter<int> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(4);
		 C.insert(2);
		 C.insert(3);
		 C.insert(1);
		 

		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty());
	 }
 }

 
 //8 cap
 TEST_CASE("Counter<int> add elements in order (8 capacity)", "[Counter]")
 {
	 Counter<int> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(1);
		 C.insert(2);
		 C.insert(3);
		 C.insert(4);
		 C.insert(5);
		 C.insert(6);
		 C.insert(7);
		 C.insert(8);
		

		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());
	 }
 }

 TEST_CASE("Counter<int> add elements not in order (8 capacity)", "[Counter]")
 {
	 Counter<int> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(4);
		 C.insert(2);
		 C.insert(3);
		 C.insert(1);
		 C.insert(8);
		 C.insert(5);
		 C.insert(6);
		 C.insert(7);


		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());
	 }
 }
 

 //BIG cap
 TEST_CASE("Counter<int> add elements in order (5000 capacity)", "[Counter]")
 {
	 Counter<int> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		
		 for (int i = 0; i < 5000; i++) {
			 C.insert(i);
		 }

		 REQUIRE(C.size() == 5000);
		 REQUIRE(!C.empty());
	 }
 }

 
//contains[]//

 TEST_CASE("Counter<int> contains[]", "[Counter]")
 {
	 Counter<int> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(7);
		 C.insert(67);
		 C.insert(9989);
		 C.insert(15);


		 REQUIRE(C.size() == 4);
		 REQUIRE(C[67] == true);
		 REQUIRE(C[9989] == true);
		 REQUIRE(C[0] == false);
		 REQUIRE(C[1] == false);

		 REQUIRE(!C.empty());
	 }
 }


 //count()//
 TEST_CASE("Counter<int> count()", "[Counter]")
 {
	 Counter<int> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 int i, j, k, l;

		 for (i = 0; i < 7; i++) {
			 C.insert(1);
		 }
		 for (j = 0; j < 3; j++) {
			 C.insert(6);
		 }
		 for (k = 0; k < 90; k++) {
			 C.insert(4);
		 }
		 for (l = 0; l < 6; l++) {
			 C.insert(10);
		 }
		 C.insert(100);



		 REQUIRE(C.size() == 5);
		 REQUIRE(C(1) == 7);
		 REQUIRE(C(6) == 3);
		 REQUIRE(C(4) == 90);
		 REQUIRE(C(10) == 6);
		 REQUIRE(C(8) == -1);
		 REQUIRE(C(100) == 1);

		 REQUIRE(!C.empty());

	 }
 }


 //+=//
 TEST_CASE("Counter<int> +=", "[Counter]")
 {
	 Counter<int> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(1);
		 C.insert(2);
		 C.insert(3);
		 C.insert(4);
		 C += 5;
		 C += 6;
		 C += 7;
		 C += 7;

		 REQUIRE(C(7) == 2);
		 REQUIRE(C[7] == true);
		 REQUIRE(C.size() == 7);
		 REQUIRE(!C.empty());

		 
	 }
 }

 //=//
 TEST_CASE("Counter<int> =", "[Counter]")
 {
	 Counter<int> C;
	 Counter<int > C2;
	 Counter<int> C3;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(1);
		 C.insert(2);
		 C.insert(3);
		 C.insert(4);

		 C2.insert(5);
		 C2.insert(6);
		 C2.insert(7);

		 C2 = C;
		 C = C3;
		 C3 = C2;
		 
		 REQUIRE(C.empty() == true);
		 REQUIRE(C2.size() == 4);
		 REQUIRE(C3.size() == 4);
		


	 }
 }

 //copy constructor//
 TEST_CASE("Counter<int> copy constructor", "[Counter]")
 {
	 Counter<int> C;
	
		 
	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(1);
		 C.insert(2);
		 C.insert(3);
		 C.insert(4);

		 Counter<int> C2(C);

		 REQUIRE(C2.size() == 4);
		 REQUIRE(C.size() == 4);
		 
	 }
 }

 TEST_CASE("Counter<int> empty copy constructor", "[Counter]")
 {
	
	 Counter<int> C3;

	 REQUIRE(C3.size() == 0);
	 REQUIRE(C3.empty() == true);

	 SECTION("inserting element")
	 {
		 Counter<int> C4(C3);

		 REQUIRE(C4.size() == 0);
		 REQUIRE(C3.size() == 0);

	 }
 }

 //iter//
 TEST_CASE("Counter<int> iter", "[Counter]")
 {
	 Counter<int> C;
	 C.insert(1);

	 for (auto e : C) {
		 REQUIRE(C[e] == true);
	 }

	
 }

 TEST_CASE("Counter<int> empty iter", "[Counter]")
 {
	 Counter<int> C;
	 for (auto e : C) {
		 REQUIRE(false);
	 }


 }

 TEST_CASE("Counter<int> iter begin end check", "[Counter]")
 {
	 Counter<int> C;
	 auto iter = C.begin();
	 auto iter2 = C.end();
	 
	 REQUIRE((iter != iter2) == false);

	 


 }

 TEST_CASE("Counter<int> empty iter with begin end", "[Counter]")
 {

	 Counter<int> C;
	 auto iter = C.begin();
	 while (iter != C.end()) {
		 REQUIRE(false);
	 }
 }

 TEST_CASE("Counter<int> empty iter with begin pass through end", "[Counter]")
 {

	 Counter<int> C;
	 C += 4; C += 9; C += 12;
	 auto iter = C.begin();
	 ++iter;
	 ++iter;
	 ++iter;
	 ++iter;
	 ++iter;
	 REQUIRE(!(iter != C.end()));
	 REQUIRE((*iter == NULL));
 }



 
///////////////////////////////////////////STRING TESTS////////////////////////////////////
 
 //4 cap lower
 TEST_CASE("Counter<string> add elements in order (4 capacity), (lowercase)", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("some");
		 C.insert("strings");
		 C.insert("are");
		 C.insert("added");
		 

		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty());
		 
	 }
 }
 
 TEST_CASE("Counter<string> add elements not in order (4 capacity), (lowercase)", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("bbb");
		 C.insert("ddd");
		 C.insert("aaa");
		 C.insert("ccc");
		 

		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty());

	 }
 }
 
 
 //4 cap upper
 TEST_CASE("Counter<string> add elements in order (4 capacity), (uppercase)", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("AAA");
		 C.insert("BBB");
		 C.insert("CCC");
		 C.insert("DDD");
		 

		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty());

	 }
 }

 TEST_CASE("Counter<string> add elements not in order (4 capacity), (uppercase)", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("GNU");
		 C.insert("GND");
		 C.insert("VIM");
		 C.insert("NANO");
		 

		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty());

	 }
 }

 //8 cap lower
 TEST_CASE("Counter<string> add elements in order (8 capacity), (lowercase)", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("some");
		 C.insert("strings");
		 C.insert("are");
		 C.insert("added");
		 C.insert("yes");
		 C.insert("indeed");
		 C.insert("they");
		 C.insert("have");
		 

		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }

 TEST_CASE("Counter<string> add elements not in order (8 capacity), (lowercase)", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("bbb");
		 C.insert("ddd");
		 C.insert("aaa");
		 C.insert("ccc");
		 C.insert("ggg");
		 C.insert("qqq");
		 C.insert("zzz");
		 C.insert("ppp");
		 

		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }

 //8 cap upper
 TEST_CASE("Counter<string> add elements in order (8 capacity), (uppercase)", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("AAA");
		 C.insert("BBB");
		 C.insert("CCC");
		 C.insert("DDD");
		 C.insert("SSS");
		 C.insert("WWW");
		 C.insert("XXX");
		 C.insert("ZZZ");
		 

		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }

 TEST_CASE("Counter<string> add elements not in order (8 capacity), (uppercase)", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("GNU");
		 C.insert("GND");
		 C.insert("VIM");
		 C.insert("NANO");
		 C.insert("GIT");
		 C.insert("CPP");
		 C.insert("ROR");
		 C.insert("BASH");
		 

		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }

 //8 cap lower + upper
 TEST_CASE("Counter<string> add elements in order (8 capacity), (uppercase + lowercase)", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("AAA");
		 C.insert("bbb");
		 C.insert("CCC");
		 C.insert("ddd");
		 C.insert("SSS");
		 C.insert("www");
		 C.insert("XXX");
		 C.insert("zzz");


		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }

 TEST_CASE("Counter<string> add elements not in order (8 capacity), (uppercase + lowercase)", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("GNU");
		 C.insert("GND");
		 C.insert("vim");
		 C.insert("NANO");
		 C.insert("GIT");
		 C.insert("cpp");
		 C.insert("ROR");
		 C.insert("bash");


		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }

 //BIG cap
 TEST_CASE("Counter<string> add elements in order (5000 capacity)", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {

		 for (int i = 0; i < 5000; i++) {
			 C.insert(to_string(i));
		 }

		 REQUIRE(C.size() == 5000);
		 REQUIRE(!C.empty());
	 }
 }


 //contains[]//
 TEST_CASE("Counter<string> contains[]", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("some");
		 C.insert("strings");
		 C.insert("are");
		 C.insert("added");


		 REQUIRE(C.size() == 4);
		 REQUIRE(C["some"] == true);
		 REQUIRE(C["added"] == true);
		 REQUIRE(C["cs341"] == false);
		 REQUIRE(C["Some"] == false);
		 REQUIRE(C["SOME"] == false);
		 REQUIRE(!C.empty());

	 }
 }


 //count()//
 TEST_CASE("Counter<string> count()", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 int i, j, k, l;

		 for (i = 0; i < 7; i++) {
			 C.insert("cs341");
		 }
		 for (j = 0; j < 3; j++) {
			 C.insert("cs251");
		 }
		 for (k = 0; k < 40; k++) {
			 C.insert("cs151");
		 }
		 for (l = 0; l < 6; l++) {
			 C.insert("cs261");
		 }
		 C.insert("CS151");



		 REQUIRE(C.size() == 5);
		 REQUIRE(C("CS151") == 1);
		 REQUIRE(C("cs261") == 6);
		 REQUIRE(C("cs251") == 3);
		 REQUIRE(C("cs341") == 7);
		 REQUIRE(C("cs151") == 40);
		 REQUIRE(C("cs111") == -1);

		 REQUIRE(!C.empty());

	 }
 }

 //+=//
 TEST_CASE("Counter<string> +=", "[Counter]")
 {
	 Counter<string> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("aaa");
		 C.insert("bbb");
		 C.insert("ccc");
		 C.insert("ddd");
		 C += "ddd";
		 C += "www";

		 for (int i = 0; i < 10; i++) {
			 C += "zzz";
		 }
		 

		 REQUIRE(C("zzz") == 10);
		 REQUIRE(C["zzz"] == true);
		 REQUIRE(C.size() == 6);
		 REQUIRE(!C.empty());


	 }
 }

 
 //=//
 TEST_CASE("Counter<string> ==", "[Counter]")
 {
	 Counter<string> C;
	 Counter<string> C2;
	 Counter<string> C3;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("a");
		 C.insert("b");
		 C.insert("c");
		 C.insert("d");

		 C2.insert("aa");
		 C2.insert("bb");
		 C2.insert("cc");

		 C2 = C;
		 C = C3;
		 C3 = C2;

		 REQUIRE(C.empty() == true);
		 REQUIRE(C2.size() == 4);
		 REQUIRE(C3.size() == 4);



	 }
 }

 //copy constructor//
 TEST_CASE("Counter<string> copy constructor", "[Counter]")
 {
	 Counter<string> C;


	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert("a");
		 C.insert("b");
		 C.insert("c");
		 C.insert("d");

		 Counter<string> C2(C);

		 REQUIRE(C2.size() == 4);
		 REQUIRE(C.size() == 4);

	 }
 }

 TEST_CASE("Counter<string> empty copy constructor", "[Counter]")
 {

	 Counter<string> C3;

	 REQUIRE(C3.size() == 0);
	 REQUIRE(C3.empty() == true);

	 SECTION("inserting element")
	 {
		 Counter<string> C4(C3);

		 REQUIRE(C4.size() == 0);
		 REQUIRE(C3.size() == 0);

	 }
 }



 /////////////////////////////////////////////DOUBLE TESTS/////////////////////////////////////
 
 //4 cap
 TEST_CASE("Counter<double> add elements in order (4 capacity)", "[Counter]")
 {
	 Counter<double> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(2.6);
		 C.insert(9.0);
		 C.insert(100.0);
		 C.insert(200);
		

		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty());

	 }
 }

 
 TEST_CASE("Counter<double> add elements not in order (4 capacity)", "[Counter]")
 {
	 Counter<double> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(54.6);
		 C.insert(2.2222);
		 C.insert(0.0);
		 C.insert(34);
		

		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty());

	 }
 }

 //8 cap
 TEST_CASE("Counter<double> add elements in order (8 capacity)", "[Counter]")
 {
	 Counter<double> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(2.6);
		 C.insert(9.0);
		 C.insert(100.0);
		 C.insert(200);
		 C.insert(350.9);
		 C.insert(365.5);
		 C.insert(720.0);
		 C.insert(2000);

		 

		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }

 TEST_CASE("Counter<double> add elements not in order (8 capacity)", "[Counter]")
 {
	 Counter<double> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(54.6);
		 C.insert(2.2222);
		 C.insert(0.0);
		 C.insert(34);
		 C.insert(546.0);
		 C.insert(222.2);
		 C.insert(0.09);
		 C.insert(120);
		 

		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }

 //contains[]//
 TEST_CASE("Counter<double> contains[]", "[Counter]")
 {
	 Counter<double> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(2.6);
		 C.insert(9.0);
		 C.insert(100.0);
		 C.insert(200);


		 REQUIRE(C.size() == 4);
		 REQUIRE(C[9.0] == true);
		 REQUIRE(C[200] == true);
		 REQUIRE(C[900] == false);
		 REQUIRE(C[6969] == false);
		 REQUIRE(!C.empty());

	 }
 }

 //copy constructor//
 TEST_CASE("Counter<double> copy constructor", "[Counter]")
 {
	 Counter<double> C;


	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(1);
		 C.insert(2);
		 C.insert(3);
		 C.insert(4);

		 Counter<double> C2(C);

		 REQUIRE(C2.size() == 4);
		 REQUIRE(C.size() == 4);

	 }
 }

 TEST_CASE("Counter<double> empty copy constructor", "[Counter]")
 {

	 Counter<double> C3;

	 REQUIRE(C3.size() == 0);
	 REQUIRE(C3.empty() == true);

	 SECTION("inserting element")
	 {
		 Counter<double> C4(C3);

		 REQUIRE(C4.size() == 0);
		 REQUIRE(C3.size() == 0);

	 }
 }

 //BIG cap
 TEST_CASE("Counter<double> add elements in order (5000 capacity)", "[Counter]")
 {
	 Counter<double> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {

		 for (int i = 0; i < 5000; i++) {
			 C.insert(i);
		 }

		 REQUIRE(C.size() == 5000);
		 REQUIRE(!C.empty());
	 }
 }







 ////////////////////////////////////////BOOL TESTS//////////////////////////////////////////

 //4 cap
 TEST_CASE("Counter<bool> add elements in order (4 capacity)", "[Counter]")
 {
	 Counter<bool> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(true);
		 C.insert(true);
		 C.insert(false);
		 C.insert(false);

		 REQUIRE(C.size() == 2);
		 REQUIRE(!C.empty());

	 }
 }

 
 TEST_CASE("Counter<bool> add elements not in order (4 capacity)", "[Counter]")
 {
	 Counter<bool> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(false);
		 C.insert(true);
		 C.insert(true);
		 C.insert(false);
		 

		 REQUIRE(C.size() == 2);
		 REQUIRE(!C.empty());

	 }
 }

 //8 cap
 TEST_CASE("Counter<bool> add elements in order (8 capacity)", "[Counter]")
 {
	 Counter<bool> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(true);
		 C.insert(true);
		 C.insert(true);
		 C.insert(true);
		 C.insert(false);
		 C.insert(false);
		 C.insert(false);
		 C.insert(false);
		

		 REQUIRE(C.size() == 2);
		 REQUIRE(!C.empty());

	 }
 }

 TEST_CASE("Counter<bool> add elements not in order (8 capacity)", "[Counter]")
 {
	 Counter<bool> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(false);
		 C.insert(true);
		 C.insert(true);
		 C.insert(false);
		 C.insert(false);
		 C.insert(true);
		 C.insert(false);
		 C.insert(true);
		 

		 REQUIRE(C.size() == 2);
		 REQUIRE(!C.empty());

	 }
 }

 //contains[]//
 TEST_CASE("Counter<bool> contains[]", "[Counter]")
 {
	 Counter<bool> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(true);
		 C.insert(true);
		 C.insert(true);
		 C.insert(true);

		 REQUIRE(C.size() == 1);
		 REQUIRE(C[true]== true);
		 REQUIRE(C[false] == false);
		 REQUIRE(!C.empty());

	 }
 }

 //BIG cap
 TEST_CASE("Counter<bool> add elements in order (5000 capacity)", "[Counter]")
 {
	 Counter<bool> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {

		 for (int i = 0; i < 5000; i++) {
			 C.insert(true);
		 }

		 REQUIRE(C.size() == 1);
		 REQUIRE(!C.empty());
	 }
 }










 
 /////////////////////////////////////////FLOAT TESTS///////////////////////////////////

 //4 cap
 TEST_CASE("Counter<float> add elements in order (4 capacity)", "[Counter]")
 {
	 Counter<float> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(4.5);
		 C.insert(4.6);
		 C.insert(123.5);
		 C.insert(900.8);
		 

		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty());

	 }
 }

 TEST_CASE("Counter<float> add elements not in order (4 capacity)", "[Counter]")
 {
	 Counter<float> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(45.3);
		 C.insert(100.9);
		 C.insert(0.9);
		 C.insert(3.2);
		 

		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty());

	 }
 }

 //8 cap
 TEST_CASE("Counter<float> add elements in order (8 capacity)", "[Counter]")
 {
	 Counter<float> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(4.5);
		 C.insert(4.6);
		 C.insert(123.5);
		 C.insert(900.8);
		 C.insert(4500.0);
		 C.insert(5000.9);
		 C.insert(10000.89);
		 C.insert(9999999.9);
		 

		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }

 TEST_CASE("Counter<float> add elements not in order (8 capacity)", "[Counter]")
 {
	 Counter<float> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(45.3);
		 C.insert(100.9);
		 C.insert(0.9);
		 C.insert(3.2);
		 C.insert(45.56);
		 C.insert(100.909);
		 C.insert(6.9);
		 C.insert(36.2);
		 

		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }
 
 //contains[]//
 TEST_CASE("Counter<float> contains[]", "[Counter]")
 {
	 Counter<float> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert(4.5);
		 C.insert(4.6);
		 C.insert(123.5);
		 C.insert(900.8);


		 REQUIRE(C.size() == 4);
		 REQUIRE(C[4.5] == true);
		 REQUIRE(C[900.8] == true);
		 REQUIRE(C[0] == false);
		 REQUIRE(C[4.55] == false);
		 REQUIRE(!C.empty());

	 }
 }

 //count()//
 TEST_CASE("Counter<float> count()", "[Counter]")
 {
	 Counter<float> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 int i, j, k, l;

		 for (i = 0; i < 7; i++) {
			 C.insert(1.2);
		 }
		 for (j = 0; j < 3; j++) {
			 C.insert(6.66);
		 }
		 for (k = 0; k < 90; k++) {
			 C.insert(4.5);
		 }
		 for (l = 0; l < 6; l++) {
			 C.insert(10.05);
		 }
		 C.insert(1.0);



		 REQUIRE(C.size() == 5);
		 REQUIRE(C(1.0) == 1);
		 REQUIRE(C(10.05) == 6);
		 REQUIRE(C(1.2) == 7);
		 REQUIRE(C(4.5) == 90);
		 REQUIRE(C(6.66) == 3);
		 REQUIRE(C(7.7) == -1);

		 REQUIRE(!C.empty());

	 }
 }

 //BIG cap
 TEST_CASE("Counter<float> add elements in order (5000 capacity)", "[Counter]")
 {
	 Counter<float> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {

		 for (int i = 0; i < 5000; i++) {
			 C.insert(i);
		 }

		 REQUIRE(C.size() == 5000);
		 REQUIRE(!C.empty());
	 }
 }





 //////////////////////////////////////////////CHAR TESTS///////////////////////////////////////////

 //4 cap
 TEST_CASE("Counter<char> add elements in order (4 capacity)", "[Counter]")
 {
	 Counter<char> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert('a');
		 C.insert('d');
		 C.insert('f');
		 C.insert('v');
		 

		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty());

	 }
 }

 TEST_CASE("Counter<char> add elements not in order (4 capacity)", "[Counter]")
 {
	 Counter<char> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert('e');
		 C.insert('a');
		 C.insert('t');
		 C.insert('b');
		 
		 REQUIRE(C.size() == 4);
		 REQUIRE(!C.empty());

	 }
 }

 //8 cap
 TEST_CASE("Counter<char> add elements in order (8 capacity)", "[Counter]")
 {
	 Counter<char> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert('a');
		 C.insert('d');
		 C.insert('f');
		 C.insert('g');
		 C.insert('j');
		 C.insert('k');
		 C.insert('q');
		 C.insert('v');
		 

		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }

 TEST_CASE("Counter<char> add elements not in order (8 capacity)", "[Counter]")
 {
	 Counter<char> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert('e');
		 C.insert('a');
		 C.insert('t');
		 C.insert('b');
		 C.insert('c');
		 C.insert('u');
		 C.insert('m');
		 C.insert('n');
		 

		 REQUIRE(C.size() == 8);
		 REQUIRE(!C.empty());

	 }
 }
 
 //contains[]//
 TEST_CASE("Counter<char> contains[]", "[Counter]")
 {
	 Counter<char> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert('a');
		 C.insert('d');
		 C.insert('f');
		 C.insert('v');


		 REQUIRE(C.size() == 4);
		 REQUIRE(C['v'] == true);
		 REQUIRE(C['f'] == true);
		 REQUIRE(C['c'] == false);
		 REQUIRE(C['z'] == false);
		 REQUIRE(!C.empty());

	 }
 }

 //count()//
 TEST_CASE("Counter<char> count()", "[Counter]")
 {
	 Counter<char> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 int i, j, k, l;
		 
		 for (i = 0; i < 4; i++) {
			 C.insert('i');
		 }
		 for (j = 0; j < 2; j++) {
			 C.insert('v');
		 }
		 for (k = 0; k < 7; k++) {
			 C.insert('w');
		 }
		 for (l = 0; l < 10; l++) {
			 C.insert('a');
		 }
		 C.insert('d');
		 


		 REQUIRE(C.size() == 5);
		 REQUIRE(C('d') == 1);
		 REQUIRE(C('i') == 4);
		 REQUIRE(C('v') == 2);
		 REQUIRE(C('w') == 7);
		 REQUIRE(C('a') == 10);
		 REQUIRE(C('o') == -1);

		 REQUIRE(!C.empty());

	 }
 }

 //+=//
 TEST_CASE("Counter<char> +=", "[Counter]")
 {
	 Counter<char> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert('a');
		 C.insert('b');
		 C.insert('c');
		 C.insert('d');
		 C += 'd';
		 C += 'w';

		 for (int i = 0; i < 10; i++) {
			 C += 'z';
		 }


		 REQUIRE(C('z') == 10);
		 REQUIRE(C['z'] == true);
		 REQUIRE(C.size() == 6);
		 REQUIRE(!C.empty());


	 }
 }
 //=//
 TEST_CASE("Counter<char> ==", "[Counter]")
 {
	 Counter<char> C;
	 Counter<char> C2;
	 Counter<char> C3;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert('a');
		 C.insert('b');
		 C.insert('c');
		 C.insert('d');

		 C2.insert('d');
		 C2.insert('e');
		 C2.insert('f');

		 C2 = C;
		 C = C3;
		 C3 = C2;

		 REQUIRE(C.empty() == true);
		 REQUIRE(C2.size() == 4);
		 REQUIRE(C3.size() == 4);



	 }
 }

 //copy constructor//
 TEST_CASE("Counter<char> copy constructor", "[Counter]")
 {
	 Counter<char> C;


	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {
		 C.insert('a');
		 C.insert('b');
		 C.insert('c');
		 C.insert('d');

		 Counter<char> C2(C);

		 REQUIRE(C2.size() == 4);
		 REQUIRE(C.size() == 4);

	 }
 }

 TEST_CASE("Counter<char> empty copy constructor", "[Counter]")
 {

	 Counter<char> C3;

	 REQUIRE(C3.size() == 0);
	 REQUIRE(C3.empty() == true);

	 SECTION("inserting element")
	 {
		 Counter<char> C4(C3);

		 REQUIRE(C4.size() == 0);
		 REQUIRE(C3.size() == 0);

	 }
 }

 //BIG cap
 TEST_CASE("Counter<char> add elements in order (5000 capacity)", "[Counter]")
 {
	 Counter<char> C;

	 REQUIRE(C.size() == 0);
	 REQUIRE(C.empty() == true);

	 SECTION("inserting element")
	 {

		 for (int i = 0; i < 2500; i++) {
			 C.insert('a');
			 C.insert('b');
		 }

		 REQUIRE(C.size() == 2);
		 REQUIRE(!C.empty());
	 }
 }













TEST_CASE( "Counter<string> with 4 elements", "[Counter]" ) 
{
  Counter<string> C;
  
  REQUIRE(C.size() == 0);
  REQUIRE(C.empty() == true);
 
  //C += "10AM"; 
  //C += "4PM";
  //for ( const string& e : C) {
	 // cout << e << endl;
  //}

  //auto iter = C.begin();
  //++iter;
  //++iter;
  //++iter;
  //++iter;

  //string val = *iter;
  //cout << val <<  endl;
  C.print();
 
}//test
