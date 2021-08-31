#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <float.h>

#include "Common/Common.h"
#include "Header/Trees/Basics.h"
#include "Test/Input_Table.h"
#include "Trees/Traversal_Methods.h"
#include "Test/Unit_Test_Trees.h"
#include "Test/Unit_Test_Evaluation.h"

int main(int argc, char* argv[])
{
	static struct _tree_node* _tree		= NULL;
	static uint8_t _evaluate			= FALSE;
	static uint8_t _simplify			= FALSE;
	auto uint32_t _test_pass_fail_count = 0;

	printf("\n\n/********** START **********/\n\n");

	/*
	*  Construct an example tree and show few traversal methods
	*/
	printf("/********** Example Tree Start **********/");

	/* Create and initialize the tree */
	Init_Table(&_tree);

	/* Level order traversal */
	printf("\n\n/********** Level order traversal **********/");
	Tree_Level_Order_Traversal(_tree);

	/* Pre order traversal */
	printf("\n\n/********** Pre order traversal **********/");
	Tree_Pre_Order_Traversal(_tree);

	/* In order traversal */
	printf("\n\n/********** In order traversal **********/");
	Tree_In_Order_Traversal(_tree);

	/* Post order traversal */
	printf("\n\n/********** Post order traversal **********/");
	(void)Tree_Post_Order_Traversal(_tree, _evaluate, _simplify);

	printf("\n\n/********** Example Tree End **********/");

	/*
	*  Test Case(s)
	*/

	/* Expression tree evaluation test(s)*/
	printf("\n\nTest tolerance: [-%f  +%f]", TEST_TOLERANCE, TEST_TOLERANCE);
		/* Predefined expression tree evaluation test */
	_test_pass_fail_count += UT_Eval_Case1_1();
		/* Divison by zero test */
	_test_pass_fail_count += UT_Eval_Case1_2();
		/* Nonsense tree test */
	_test_pass_fail_count += UT_Eval_Case1_3();
		/* Corrupted tree test */
	_test_pass_fail_count += UT_Eval_Case1_4();

	/* Tree simplification test */
		/* Unary operator depth = 1 */
	_test_pass_fail_count += UT_Eval_Case2_1();
		/* Unary operator depth > 1 */
	_test_pass_fail_count += UT_Eval_Case2_2();
		/* Multiple child node under a unary operator test*/
	_test_pass_fail_count += UT_Eval_Case2_3();

	/* All test cases passed */
	if (TEST_CASE_COUNT == _test_pass_fail_count)
	{
		printf("\n\nCongratulations!\n\tAll test cases are passed!\n\tNumber of test cases passed: [%u / %u]", _test_pass_fail_count, TEST_CASE_COUNT);
	}
	/* At least one of the test(s) are failed */
	else
	{
		printf("\n\nOoops!\n\tAt least one of the test cases are failed!\n\tNumber of test cases passed: [%u / %u]", _test_pass_fail_count, TEST_CASE_COUNT);
	}

	free(_tree);
	/* To prevent dangling pointer(s) */
	_tree = NULL;

	printf("\n\n/********** END **********/\n\n");
	return(0);
}

