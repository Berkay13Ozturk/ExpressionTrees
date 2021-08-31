#ifndef __COMMON_H__
#define __COMMON_H__

#define FALSE					((uint8_t)0)
#define TRUE					((uint8_t)1U)

/* DEBUG */
#define _DEBUG_					TRUE

/* Increase and/or decrease this number if new test cases are added and/or removed */
#define TEST_CASE_COUNT			((uint32_t)7U)

#define _MAX_OPERATOR_STR_LEN	((uint8_t)10U)
#define _MAX_TREE_DEPTH_COUNT	((uint64_t)100U)

/* Depth of the tree, can be expanded by a similar approach */
#define _LEVEL0					(1U)
#define _LEVEL1					(2U)
#define _LEVEL2					(_LEVEL1 * _LEVEL1)
#define _LEVEL3					(_LEVEL2 * _LEVEL1)

#define _MAX_LEVEL				_LEVEL3
#define _MAX_NODE				(_LEVEL0 + _LEVEL1 + _LEVEL2 + _LEVEL3)

#ifndef  _countof
# define _countof(array) (sizeof(array) / sizeof(array[0]))
#endif

/*
* Reserved keywords
* To maximize the input range [(FLT_EPSILON * 7) to (FLT_MAX)]
* 
* You can append new operands (if you like to add) starting from the bottom of the list
*/
#define _MAX_OPERATOR_COUNT		((float)8.0f)

#define _MUL_START_ADDR			((float)2.0f)
#define _DIV_START_ADDR			((float)3.0f)
#define _ADD_START_ADDR			((float)4.0f)
#define _SUB_START_ADDR			((float)5.0f)
#define _CUB_START_ADDR			((float)6.0f)
#define _SUQ_START_ADDR			((float)7.0f)

#define BLANK					((float)(FLT_EPSILON))							/* Blank, if you would like to construct an unbalanced binary tree */
	/* Binary operations */
#define MULTIPLY				((float)(FLT_EPSILON * _MUL_START_ADDR))		/* Multiplication */
#define DIVIDE					((float)(FLT_EPSILON * _DIV_START_ADDR))		/* Division */
#define ADD						((float)(FLT_EPSILON * _ADD_START_ADDR))		/* Addition */
#define SUB						((float)(FLT_EPSILON * _SUB_START_ADDR))		/* Subtraction */
	/* Unary operations */
#define CUBE					((float)(FLT_EPSILON * _CUB_START_ADDR))		/* Cube */
#define SQUARE					((float)(FLT_EPSILON * _SUQ_START_ADDR))		/* Square */

#define OPERATOR_RANGE			((float)(_MAX_OPERATOR_COUNT * (float)FLT_EPSILON))
/* Test case tolerance */
#define TEST_TOLERANCE			OPERATOR_RANGE

#endif // !__COMMON_H__
