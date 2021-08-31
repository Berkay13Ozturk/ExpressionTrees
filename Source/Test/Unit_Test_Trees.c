/**/
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#include "Common/Common.h"
#include "Error/Error.h"
#include "Trees/Basics.h"
#include "Test/Input_Table.h"

/* Test 1
*
*  Corrupted tree
*	Input: Non-binary tree input
*		   For simplicity reasons only binary trees are evaluated with this application
*		   Following input(s) shall be detected by the application
*			- More than 2 nodes per parent	(Multiway trees)
*			- Accidental data input			(More than the level can provide, e.g level 'n' can have a maximum of 2 ^ n nodes)
*			- Wrongful tree construction
*			- Illegal pointer references
*
*   Output should be the same as the expected output
*   Tree can be modified and _pre_calc_result can be updated to the expected value to test it with different expression trees
*/
void* UT_Case(struct _tree_node** _tree, uint64_t _level, float* _data, uint64_t _size)
{
	return NULL;
}