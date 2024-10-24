#include "C:\Users\Christopher\OneDrive - University of Florida\Documents\CLASSES WORK\Spring 2024\COP3530 - DSA\Gator AVL Project\src\main.cpp"
#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <string>

/*
	To check output (At the Project1 directory):
		g++ -std=c++14 -Werror -Wuninitialized -o build/test test-unit/test.cpp && build/test
*/

TEST_CASE("BST Insert", "[flag]"){

		BST tree;   // Create a Tree object
		tree.insert("Chris", "12374583");
        tree.insert("Alex", "98765432");
        tree.insert("Jordan", "19283746");
        tree.insert("Taylor", "56473829");
        tree.insert("Morgan", "37482916");
        tree.insert("Casey", "74839201");
        tree.insert("Jamie", "10293847");
        tree.insert("Drew", "65837492");
        tree.insert("Quinn", "29384756");
        tree.insert("Robin", "83746529");
        tree.insert("Kelly", "18273645");
        tree.insert("Riley", "64738291");
        tree.insert("Skyler", "73829164");
        tree.insert("Blair", "82936475");
        tree.insert("Sage", "49283716");
        tree.insert("Charlie", "38192746");

        std::vector<string> actualOutput = tree.inorder();
		std::vector<string> expectedOutput = {"Alex", "Blair", "Casey", "Charlie", "Drew", "Jamie", "Jordan", "Kelly", "Morgan", "Quinn", "Riley", "Robin", "Sage", "Skyler", "Taylor"};
		REQUIRE(expectedOutput.size() == actualOutput.size());
		REQUIRE(actualOutput == expectedOutput);
}