/**/
#include <stdio.h>
#include <stdint.h>
#include <float.h>
#include <stdlib.h>

#include "Common/Common.h"
#include "Trees/Basics.h"
#include "Trees/Evaluation.h"
#include "Trees/Traversal_Methods.h"
#include "Test/Input_Table.h"

/* Coding exercise 1 test(s) */
	/* Test 1
	* 
	*  Supply a pre-calculated tree
	*	Input: Predefined unbalanced tree with an expected output of: [490.0]
	* 
	*   Output should be the same as the expected output
	*   Tree can be modified and _pre_calc_result can be updated to the expected value to test it with different expression trees
	*/
uint8_t UT_Eval_Case1_1(void)
{
	static struct _tree_node* _tree = NULL;
	static uint8_t _evaluate		= TRUE;
	static uint8_t _simplify		= FALSE;
	auto uint64_t  _level			= 0;
	const uint8_t  _test_no			= 1U;
	auto uint64_t  _index;
	auto float	   _result;
	const float	   _pre_calc_result = 490.0f;
	auto uint8_t   _ret_val			= FALSE;

	/* Tree to be constructed */
	auto float _Tree[]				= { SUB,										\
										MULTIPLY, 10,								\
										SUB, ADD, BLANK, BLANK,						\
										15, 5, 20, 30, BLANK, BLANK, BLANK, BLANK	\
									  };
	/* Depth: 0 */
	_Table_Level0 = _Tree[0];

	/* Depth: [1 to _MAX_TREE_DEPTH_COUNT] */
	auto uint64_t _level1 = _LEVEL1 - 1U, _level2 = _LEVEL2 - 1U, _level3 = _LEVEL3 - 1U;
	for (_index = 0; _index < _MAX_NODE; _index++)
	{
		/* 1 */
		if ((_index >= _level1) && (_index < _level2))
		{
			_Table_Level1[_index - _level1] = _Tree[_index];
		}
		/* 2 */
		else if ((_index >= _level2) && (_index < _level3))
		{
			_Table_Level2[_index - _level2] = _Tree[_index];
		}
		/* 3 */
		else if (_index >= _level3)
		{
			_Table_Level3[_index - _level3] = _Tree[_index];
		}
	}

	_ptr_tlvl0 = &_Table_Level0;
	_ptr_tlvl1 = _Table_Level1;
	_ptr_tlvl2 = _Table_Level2;
	_ptr_tlvl3 = _Table_Level3;

	float* _table_list[]			= { _ptr_tlvl0, _ptr_tlvl1, _ptr_tlvl2, _ptr_tlvl3 };

	_size_table[_level]				= 1U;
	_size_table[++_level]			= _countof(_Table_Level1);
	_size_table[++_level]			= _countof(_Table_Level2);
	_size_table[++_level]			= _countof(_Table_Level3);
	_level_count					= ++_level;

	/* Start */
	printf("\n\n/********** Test[%u] START **********/", _test_no);

	/* Tree creation */
	Tree_Create_from_Node_Groups(&_tree, _table_list, _size_table, _level_count);
	
	/* Expression evaluation */
	_result = Tree_Post_Order_Traversal(_tree, TRUE, FALSE);
	printf("\n\n\tExpected result: %f\n\n\tResult of the expression tree: %f", _pre_calc_result, _result);
	
	/* PASS */
	if ((_pre_calc_result >= (_result - TEST_TOLERANCE)) && (_pre_calc_result <= (_result + TEST_TOLERANCE)))
	{
		printf("\n\n\tTest[%u] status: [PASS]", _test_no);
		_ret_val = TRUE;
	}
	/* FAIL */
	else
	{
		printf("\n\n\tTest[%u] status: [FAIL]", _test_no);
		_ret_val = FALSE;
	}

	/* End */
	printf("\n\n/********** Test[%u] END **********/", _test_no);

	free(_tree);
	/* To prevent dangling pointer(s)*/
	_tree = NULL;
	
	return _ret_val;
}

/* Test 2
* 
*  Division by zero test
*	Input: 0 is provided as a denominator somewhere in the tree
*          Based on the application's relaxed error handling policy, the division operation should ignore the right operand and inform the user
*          Left operand value is returned as the division result
* 
*   Output should be the same as the expected output
*   Tree can be modified and _pre_calc_result can be updated to the expected value to test it with different expression trees
*/
uint8_t UT_Eval_Case1_2(void)
{
	static struct _tree_node* _tree = NULL;
	static uint8_t _evaluate		= TRUE;
	static uint8_t _simplify		= FALSE;
	auto uint64_t  _level			= 0;
	const uint8_t  _test_no			= 2U;
	auto uint64_t  _index;
	auto float	   _result;
	const float	   _pre_calc_result = 101.5f;
	auto uint8_t   _ret_val			= FALSE;

	/* Tree to be constructed */
	auto float _Tree[]				= { ADD,												\
										SQUARE, DIVIDE,										\
										-4, BLANK, MULTIPLY, 0,								\
										BLANK, BLANK, BLANK, BLANK, 45, 1.9, BLANK, BLANK	\
									  };
	/* Depth: 0 */
	_Table_Level0 = _Tree[0];

	/* Depth: [1 to _MAX_TREE_DEPTH_COUNT] */
	auto uint64_t _level1 = _LEVEL1 - 1U, _level2 = _LEVEL2 - 1U, _level3 = _LEVEL3 - 1U;
	for (_index = 0; _index < _MAX_NODE; _index++)
	{
		/* 1 */
		if ((_index >= _level1) && (_index < _level2))
		{
			_Table_Level1[_index - _level1] = _Tree[_index];
		}
		/* 2 */
		else if ((_index >= _level2) && (_index < _level3))
		{
			_Table_Level2[_index - _level2] = _Tree[_index];
		}
		/* 3 */
		else if (_index >= _level3)
		{
			_Table_Level3[_index - _level3] = _Tree[_index];
		}
	}

	_ptr_tlvl0 = &_Table_Level0;
	_ptr_tlvl1 = _Table_Level1;
	_ptr_tlvl2 = _Table_Level2;
	_ptr_tlvl3 = _Table_Level3;

	float* _table_list[]			= { _ptr_tlvl0, _ptr_tlvl1, _ptr_tlvl2, _ptr_tlvl3 };

	_size_table[_level]				= 1U;
	_size_table[++_level]			= _countof(_Table_Level1);
	_size_table[++_level]			= _countof(_Table_Level2);
	_size_table[++_level]			= _countof(_Table_Level3);
	_level_count					= ++_level;

	/* Start */
	printf("\n\n/********** Test[%u] START **********/", _test_no);

	/* Tree creation */
	Tree_Create_from_Node_Groups(&_tree, _table_list, _size_table, _level_count);
	
	/* Expression evaluation */
	_result = Tree_Post_Order_Traversal(_tree, TRUE, FALSE);
	printf("\n\n\tExpected result: %f\n\n\tResult of the expression tree: %f", _pre_calc_result, _result);
	
	/* PASS */
	if ((_pre_calc_result >= (_result - TEST_TOLERANCE)) && (_pre_calc_result <= (_result + TEST_TOLERANCE)))
	{
		printf("\n\n\tTest[%u] status: [PASS]", _test_no);
		_ret_val = TRUE;
	}
	/* FAIL */
	else
	{
		printf("\n\n\tTest[%u] status: [FAIL]", _test_no);
		_ret_val = FALSE;
	}

	/* End */
	printf("\n\n/********** Test[%u] END **********/", _test_no);

	free(_tree);
	/* To prevent dangling pointer(s)*/
	_tree = NULL;
	
	return _ret_val;
}

/* Test 3
*
*  Nonsense tree test
*	Input: A tree with only operator(s) and/or operand(s) provided
*		   Can be full of operands, full of operators, or mixed in a way that wouldn't make any sense mathematically
*          Expected result is BLANK
*
*   Output should be the same as the expected output
*   Tree can be modified and _pre_calc_result can be updated to the expected value to test it with different expression trees
*/
uint8_t UT_Eval_Case1_3(void)
{
	static struct _tree_node* _tree = NULL;
	static uint8_t _evaluate		= TRUE;
	static uint8_t _simplify		= FALSE;
	auto uint64_t  _level			= 0;
	const uint8_t  _test_no			= 3U;
	auto uint64_t  _index;
	auto float	   _result;
	const float	   _pre_calc_result = BLANK;
	auto uint8_t   _ret_val			= FALSE;

	/* Tree to be constructed */
	auto float _Tree[]				= { 6,														\
										SQUARE, DIVIDE,											\
										DIVIDE, BLANK, MULTIPLY, DIVIDE,						\
										BLANK, BLANK, BLANK, BLANK, DIVIDE, CUBE, BLANK, BLANK	\
									  };
	/* Depth: 0 */
	_Table_Level0 = _Tree[0];

	/* Depth: [1 to _MAX_TREE_DEPTH_COUNT] */
	auto uint64_t _level1 = _LEVEL1 - 1U, _level2 = _LEVEL2 - 1U, _level3 = _LEVEL3 - 1U;
	for (_index = 0; _index < _MAX_NODE; _index++)
	{
		/* 1 */
		if ((_index >= _level1) && (_index < _level2))
		{
			_Table_Level1[_index - _level1] = _Tree[_index];
		}
		/* 2 */
		else if ((_index >= _level2) && (_index < _level3))
		{
			_Table_Level2[_index - _level2] = _Tree[_index];
		}
		/* 3 */
		else if (_index >= _level3)
		{
			_Table_Level3[_index - _level3] = _Tree[_index];
		}
	}

	_ptr_tlvl0 = &_Table_Level0;
	_ptr_tlvl1 = _Table_Level1;
	_ptr_tlvl2 = _Table_Level2;
	_ptr_tlvl3 = _Table_Level3;

	float* _table_list[]			= { _ptr_tlvl0, _ptr_tlvl1, _ptr_tlvl2, _ptr_tlvl3 };

	_size_table[_level]				= 1U;
	_size_table[++_level]			= _countof(_Table_Level1);
	_size_table[++_level]			= _countof(_Table_Level2);
	_size_table[++_level]			= _countof(_Table_Level3);
	_level_count					= ++_level;

	/* Start */
	printf("\n\n/********** Test[%u] START **********/", _test_no);

	/* Tree creation */
	Tree_Create_from_Node_Groups(&_tree, _table_list, _size_table, _level_count);
	
	/* Expression evaluation */
	_result = Tree_Post_Order_Traversal(_tree, TRUE, FALSE);
	printf("\n\n\tExpected result: %f\n\n\tResult of the expression tree: %f", _pre_calc_result, _result);
	
	/* PASS */
	if ((_pre_calc_result >= (_result - TEST_TOLERANCE)) && (_pre_calc_result <= (_result + TEST_TOLERANCE)))
	{
		printf("\n\n\tTest[%u] status: [PASS]", _test_no);
		_ret_val = TRUE;
	}
	/* FAIL */
	else
	{
		printf("\n\n\tTest[%u] status: [FAIL]", _test_no);
		_ret_val = FALSE;
	}

	/* End */
	printf("\n\n/********** Test[%u] END **********/", _test_no);

	free(_tree);
	/* To prevent dangling pointer(s)*/
	_tree = NULL;
	
	return _ret_val;
}

/* Test 4
*
*  Root only tree
*	Input: Shall return the root
*		   Algorithm will still return the root, if the sub-tree isn't making any sense mathematically
*		   Either a root with a blank su-tree, or the sub-tree is nonsense
* 
*   Output should be the same as the expected output
*   Tree can be modified and _pre_calc_result can be updated to the expected value to test it with different expression trees
*/
uint8_t UT_Eval_Case1_4(void)
{
	static struct _tree_node* _tree = NULL;
	static uint8_t _evaluate		= TRUE;
	static uint8_t _simplify		= FALSE;
	auto uint64_t  _level			= 0;
	const uint8_t  _test_no			= 4U;
	auto uint64_t  _index;
	auto float	   _result;
	const float	   _pre_calc_result = -758.915;
	auto uint8_t   _ret_val			= FALSE;

	/* Tree to be constructed */
	auto float _Tree[]				= { -758.915,													\
										BLANK, BLANK,												\
										SUB, BLANK, ADD, BLANK,										\
										BLANK, CUBE, BLANK, SQUARE, BLANK, BLANK, BLANK, BLANK,		\
									  };
	/* Depth: 0 */
	_Table_Level0 = _Tree[0];

	/* Depth: [1 to _MAX_TREE_DEPTH_COUNT] */
	auto uint64_t _level1 = _LEVEL1 - 1U, _level2 = _LEVEL2 - 1U, _level3 = _LEVEL3 - 1U;
	for (_index = 0; _index < _MAX_NODE; _index++)
	{
		/* 1 */
		if ((_index >= _level1) && (_index < _level2))
		{
			_Table_Level1[_index - _level1] = _Tree[_index];
		}
		/* 2 */
		else if ((_index >= _level2) && (_index < _level3))
		{
			_Table_Level2[_index - _level2] = _Tree[_index];
		}
		/* 3 */
		else if (_index >= _level3)
		{
			_Table_Level3[_index - _level3] = _Tree[_index];
		}
	}

	_ptr_tlvl0 = &_Table_Level0;
	_ptr_tlvl1 = _Table_Level1;
	_ptr_tlvl2 = _Table_Level2;
	_ptr_tlvl3 = _Table_Level3;

	float* _table_list[]			= { _ptr_tlvl0, _ptr_tlvl1, _ptr_tlvl2, _ptr_tlvl3 };

	_size_table[_level]				= 1U;
	_size_table[++_level]			= _countof(_Table_Level1);
	_size_table[++_level]			= _countof(_Table_Level2);
	_size_table[++_level]			= _countof(_Table_Level3);
	_level_count					= ++_level;

	/* Start */
	printf("\n\n/********** Test[%u] START **********/", _test_no);

	/* Tree creation */
	Tree_Create_from_Node_Groups(&_tree, _table_list, _size_table, _level_count);
	
	/* Expression evaluation */
	_result = Tree_Post_Order_Traversal(_tree, TRUE, FALSE);
	printf("\n\n\tExpected result: %f\n\n\tResult of the expression tree: %f", _pre_calc_result, _result);
	
	/* PASS */
	if ((_pre_calc_result >= (_result - TEST_TOLERANCE)) && (_pre_calc_result <= (_result + TEST_TOLERANCE)))
	{
		printf("\n\n\tTest[%u] status: [PASS]", _test_no);
		_ret_val = TRUE;
	}
	/* FAIL */
	else
	{
		printf("\n\n\tTest[%u] status: [FAIL]", _test_no);
		_ret_val = FALSE;
	}

	/* End */
	printf("\n\n/********** Test[%u] END **********/", _test_no);

	free(_tree);
	/* To prevent dangling pointer(s)*/
	_tree = NULL;
	
	return _ret_val;
}


/* Coding exercise 2 test(s) */
	/* Test 5
	* 
	*  Supply a pre-calculated tree
	*	Input: Predefined unbalanced tree with an expected output of: [7279.16]
	*		   Construct a tree containing unary operators, then simplify it
	*		   After simplification, evaluate the expression
	*		   Unary operator depth = 1
	* 
	*   Output should be the same as the expected output
	*   Tree can be modified and _pre_calc_result can be updated to the expected value to test it with different expression trees
	*/
uint8_t UT_Eval_Case2_1(void)
{
	static struct _tree_node* _tree = NULL;
	static uint8_t _evaluate		= TRUE;
	static uint8_t _simplify		= FALSE;
	auto uint64_t  _level			= 0;
	const uint8_t  _test_no			= 5U;
	auto uint64_t  _index;
	auto float	   _result;
	const float	   _pre_calc_result = 7279.16f;
	auto uint8_t   _ret_val			= FALSE;

	/* Tree to be constructed */
	auto float _Tree[]				= { SUB,													\
										ADD, MULTIPLY,											\
										SQUARE, BLANK, -3.5, -4,								\
										85.4, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK	\
									  };
	/* Depth: 0 */
	_Table_Level0 = _Tree[0];

	/* Depth: [1 to _MAX_TREE_DEPTH_COUNT] */
	auto uint64_t _level1 = _LEVEL1 - 1U, _level2 = _LEVEL2 - 1U, _level3 = _LEVEL3 - 1U;
	for (_index = 0; _index < _MAX_NODE; _index++)
	{
		/* 1 */
		if ((_index >= _level1) && (_index < _level2))
		{
			_Table_Level1[_index - _level1] = _Tree[_index];
		}
		/* 2 */
		else if ((_index >= _level2) && (_index < _level3))
		{
			_Table_Level2[_index - _level2] = _Tree[_index];
		}
		/* 3 */
		else if (_index >= _level3)
		{
			_Table_Level3[_index - _level3] = _Tree[_index];
		}
	}

	_ptr_tlvl0 = &_Table_Level0;
	_ptr_tlvl1 = _Table_Level1;
	_ptr_tlvl2 = _Table_Level2;
	_ptr_tlvl3 = _Table_Level3;

	float* _table_list[]			= { _ptr_tlvl0, _ptr_tlvl1, _ptr_tlvl2, _ptr_tlvl3 };

	_size_table[_level]				= 1U;
	_size_table[++_level]			= _countof(_Table_Level1);
	_size_table[++_level]			= _countof(_Table_Level2);
	_size_table[++_level]			= _countof(_Table_Level3);
	_level_count					= ++_level;

	/* Start */
	printf("\n\n/********** Test[%u] START **********/", _test_no);

	/* Tree creation */
	Tree_Create_from_Node_Groups(&_tree, _table_list, _size_table, _level_count);
	
	/* Simplify the tree and print it */
	(void)Tree_Post_Order_Traversal(_tree, FALSE, TRUE);
	printf("\n\n/********** Level order traversal of the simplified tree **********/");
	Tree_Level_Order_Traversal(_tree);

	/* Evaluate the simplified tree */
	_result = Tree_Post_Order_Traversal(_tree, TRUE, FALSE);
	printf("\n\n\tExpected result: %f\n\n\tResult of the simplified expression tree: %f", _pre_calc_result, _result);
	
	/* PASS */
	if ((_pre_calc_result >= (_result - TEST_TOLERANCE)) && (_pre_calc_result <= (_result + TEST_TOLERANCE)))
	{
		printf("\n\n\tTest[%u] status: [PASS]", _test_no);
		_ret_val = TRUE;
	}
	/* FAIL */
	else
	{
		printf("\n\n\tTest[%u] status: [FAIL]", _test_no);
		_ret_val = FALSE;
	}

	/* End */
	printf("\n\n/********** Test[%u] END **********/", _test_no);

	free(_tree);
	/* To prevent dangling pointer(s)*/
	_tree = NULL;
	
	return _ret_val;
}

/* Test 6
* 
*  Supply a pre-calculated tree
*	Input: Predefined unbalanced tree with an expected output of: [8303]
*		   Construct a tree containing unary operators, then simplify it
*		   After simplification, evaluate the expression
*		   Unary operator depth > 1
*
*   Output should be the same as the expected output
*   Tree can be modified and _pre_calc_result can be updated to the expected value to test it with different expression trees
*/
uint8_t UT_Eval_Case2_2(void)
{
	static struct _tree_node* _tree = NULL;
	static uint8_t _evaluate		= TRUE;
	static uint8_t _simplify		= FALSE;
	auto uint64_t  _level			= 0;
	const uint8_t  _test_no			= 6U;
	auto uint64_t  _index;
	auto float	   _result;
	const float	   _pre_calc_result = 8303;
	auto uint8_t   _ret_val			= FALSE;

	/* Tree to be constructed */
	auto float _Tree[]				= { ADD,													\
										CUBE, -0.765625,										\
										SQUARE, BLANK, BLANK, BLANK,							\
										4.5, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK	\
									  };
	/* Depth: 0 */
	_Table_Level0 = _Tree[0];

	/* Depth: [1 to _MAX_TREE_DEPTH_COUNT] */
	auto uint64_t _level1 = _LEVEL1 - 1U, _level2 = _LEVEL2 - 1U, _level3 = _LEVEL3 - 1U;
	for (_index = 0; _index < _MAX_NODE; _index++)
	{
		/* 1 */
		if ((_index >= _level1) && (_index < _level2))
		{
			_Table_Level1[_index - _level1] = _Tree[_index];
		}
		/* 2 */
		else if ((_index >= _level2) && (_index < _level3))
		{
			_Table_Level2[_index - _level2] = _Tree[_index];
		}
		/* 3 */
		else if (_index >= _level3)
		{
			_Table_Level3[_index - _level3] = _Tree[_index];
		}
	}

	_ptr_tlvl0 = &_Table_Level0;
	_ptr_tlvl1 = _Table_Level1;
	_ptr_tlvl2 = _Table_Level2;
	_ptr_tlvl3 = _Table_Level3;

	float* _table_list[]			= { _ptr_tlvl0, _ptr_tlvl1, _ptr_tlvl2, _ptr_tlvl3 };

	_size_table[_level]				= 1U;
	_size_table[++_level]			= _countof(_Table_Level1);
	_size_table[++_level]			= _countof(_Table_Level2);
	_size_table[++_level]			= _countof(_Table_Level3);
	_level_count					= ++_level;

	/* Start */
	printf("\n\n/********** Test[%u] START **********/", _test_no);

	/* Tree creation */
	Tree_Create_from_Node_Groups(&_tree, _table_list, _size_table, _level_count);
	
	/* Simplify the tree and print it */
	(void)Tree_Post_Order_Traversal(_tree, FALSE, TRUE);
	printf("\n\n/********** Level order traversal of the simplified tree **********/");
	Tree_Level_Order_Traversal(_tree);

	/* Evaluate the simplified tree */
	_result = Tree_Post_Order_Traversal(_tree, TRUE, FALSE);
	printf("\n\n\tExpected result: %f\n\n\tResult of the simplified expression tree: %f", _pre_calc_result, _result);
	
	/* PASS */
	if ((_pre_calc_result >= (_result - TEST_TOLERANCE)) && (_pre_calc_result <= (_result + TEST_TOLERANCE)))
	{
		printf("\n\n\tTest[%u] status: [PASS]", _test_no);
		_ret_val = TRUE;
	}
	/* FAIL */
	else
	{
		printf("\n\n\tTest[%u] status: [FAIL]", _test_no);
		_ret_val = FALSE;
	}

	/* End */
	printf("\n\n/********** Test[%u] END **********/", _test_no);

	free(_tree);
	/* To prevent dangling pointer(s)*/
	_tree = NULL;
	
	return _ret_val;
}

/* Test 7
* 
*  Wrong input test
*	Input: Predefined unbalanced tree with an expected output of: [-0.765030176679]
*		   More than one node is provided as a child to a unary operator node
*		   Application will ignore the right node when calculating the result of the unary operation and inform the user
*
*   Output should be the same as the expected output
*   Tree can be modified and _pre_calc_result can be updated to the expected value to test it with different expression trees
*/
uint8_t UT_Eval_Case2_3(void)
{
	static struct _tree_node* _tree = NULL;
	static uint8_t _evaluate		= TRUE;
	static uint8_t _simplify		= FALSE;
	auto uint64_t  _level			= 0;
	const uint8_t  _test_no			= 7U;
	auto uint64_t  _index;
	auto float	   _result;
	const float	   _pre_calc_result = -0.765030176679;
	auto uint8_t   _ret_val			= FALSE;

	/* Tree to be constructed */
	auto float _Tree[]				= { ADD,													\
										CUBE, -0.765625,										\
										SQUARE, -784.68, BLANK, BLANK,							\
										0.29, 0.005, BLANK, BLANK, BLANK, BLANK, BLANK, BLANK	\
									  };
	/* Depth: 0 */
	_Table_Level0 = _Tree[0];

	/* Depth: [1 to _MAX_TREE_DEPTH_COUNT] */
	auto uint64_t _level1 = _LEVEL1 - 1U, _level2 = _LEVEL2 - 1U, _level3 = _LEVEL3 - 1U;
	for (_index = 0; _index < _MAX_NODE; _index++)
	{
		/* 1 */
		if ((_index >= _level1) && (_index < _level2))
		{
			_Table_Level1[_index - _level1] = _Tree[_index];
		}
		/* 2 */
		else if ((_index >= _level2) && (_index < _level3))
		{
			_Table_Level2[_index - _level2] = _Tree[_index];
		}
		/* 3 */
		else if (_index >= _level3)
		{
			_Table_Level3[_index - _level3] = _Tree[_index];
		}
	}

	_ptr_tlvl0 = &_Table_Level0;
	_ptr_tlvl1 = _Table_Level1;
	_ptr_tlvl2 = _Table_Level2;
	_ptr_tlvl3 = _Table_Level3;

	float* _table_list[]			= { _ptr_tlvl0, _ptr_tlvl1, _ptr_tlvl2, _ptr_tlvl3 };

	_size_table[_level]				= 1U;
	_size_table[++_level]			= _countof(_Table_Level1);
	_size_table[++_level]			= _countof(_Table_Level2);
	_size_table[++_level]			= _countof(_Table_Level3);
	_level_count					= ++_level;

	/* Start */
	printf("\n\n/********** Test[%u] START **********/", _test_no);

	/* Tree creation */
	Tree_Create_from_Node_Groups(&_tree, _table_list, _size_table, _level_count);
	
	/* Simplify the tree and print it */
	(void)Tree_Post_Order_Traversal(_tree, FALSE, TRUE);
	printf("\n\n/********** Level order traversal of the simplified tree **********/");
	Tree_Level_Order_Traversal(_tree);

	/* Evaluate the simplified tree */
	_result = Tree_Post_Order_Traversal(_tree, TRUE, FALSE);
	printf("\n\n\tExpected result: %f\n\n\tResult of the simplified expression tree: %f", _pre_calc_result, _result);
	
	/* PASS */
	if ((_pre_calc_result >= (_result - TEST_TOLERANCE)) && (_pre_calc_result <= (_result + TEST_TOLERANCE)))
	{
		printf("\n\n\tTest[%u] status: [PASS]", _test_no);
		_ret_val = TRUE;
	}
	/* FAIL */
	else
	{
		printf("\n\n\tTest[%u] status: [FAIL]", _test_no);
		_ret_val = FALSE;
	}

	/* End */
	printf("\n\n/********** Test[%u] END **********/", _test_no);

	free(_tree);
	/* To prevent dangling pointer(s)*/
	_tree = NULL;
	
	return _ret_val;
}