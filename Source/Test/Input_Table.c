/**/
#include <stdint.h>
#include <stddef.h>
#include <float.h>

#include "Common/Common.h"
#include "Error/Error.h"
#include "Trees/Basics.h"
#include "Test/Input_Table.h"

/* Tree information, level by level (depth or height)
 *
 * Following operators are allowed:
 *  Floating point values:	All values, except between		[FLT_EPSILON to (FLT_EPSILON * _MAX_OPERATOR_COUNT)]
 *								Above values are used as operands as seen below
 *	Binary operators:		ADD,    SUB, DIVIDE, MULTIPLY
 *  Unary  operators:		SQUARE, CUBE 
 */
static float _Table_Level0		=	DIVIDE;
static float _Table_Level1[]	= { MULTIPLY, 8.75 };
static float _Table_Level2[]	= { SUB, ADD, BLANK, BLANK };
static float _Table_Level3[]	= { 375.49, -87.06, 0.05, 0.0068, BLANK, BLANK, BLANK, BLANK };

static float* _ptr_tlvl0		= &_Table_Level0;
static float* _ptr_tlvl1		= _Table_Level1;
static float* _ptr_tlvl2		= _Table_Level2;
static float* _ptr_tlvl3		= _Table_Level3;

/* 
 * Initialize the data based on the architecture, then create the table based on the levels provided
 * Feel free to add / delete / modify the table and/or the table list
 */
void* Init_Table(struct _tree_node** _tree)
{
	auto uint64_t _level	= 0;
	uint8_t* _ret_val		= NULL;
	float* _table_list[]	= { _ptr_tlvl0, _ptr_tlvl1, _ptr_tlvl2, _ptr_tlvl3 };

	_size_table[_level]		= 1U;
	_size_table[++_level]	= _countof(_Table_Level1);
	_size_table[++_level]	= _countof(_Table_Level2);
	_size_table[++_level]	= _countof(_Table_Level3);

	_level_count			= ++_level;

	return(Tree_Create_from_Node_Groups(_tree, _table_list, _size_table, _level_count));
}