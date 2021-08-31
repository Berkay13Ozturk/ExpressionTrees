/* Tree basics */
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <inttypes.h>
#include <string.h>

#include "Common/Common.h"
#include "Error/Error.h"
#include "Trees/Basics.h"
#include "Trees/Traversal_Methods.h"

/*
*	New Node - Insert a new node to either as a left child or a right child
*
*	Input:	One of;
*				Unary operator		[Square, Cube]
*				Binary operator		[Plus, Minus, Multiply, Divide]
*				Constant data
* 
*	Return:
*			Fail:		_ERROR_INSUFFICIENT_MEMORY
*			Success:	Pointer to the root node
*/
void* Tree_Create_from_Node_Groups(struct _tree_node** _tree, float** _table_list, uint64_t* _data_size_list, const uint64_t _level_count)
{
	/* Keep track of the insertions */
	static float _root_data;
	static uint64_t _max_node_count;
	static uint64_t _prev_max_node_count	= 1U;
	static const uint8_t _level2_node_count = 1U;
	static const uint8_t _max_node_count_lvl2 = 3U;

	/* Sanity check */
	if ((NULL == _table_list) || (NULL == _data_size_list) || (_level_count < 0))
	{
		return _ERROR_DATA_PTR;
	}
	/* Create */
	else
	{
		/* Tree depth management */
		_max_node_count = ((_level_count > 1U) ? ((uint64_t)pow((uint8_t)2U, (_level_count)) - 1U) : ((uint64_t)1U));

		/* Allocate memory */
		struct _tree_node* new_node = (struct _tree_node*)realloc(*_tree, (sizeof(struct _tree_node) * (_max_node_count)));
			/* Insufficient memory */
		if (_ERROR_INSUFFICIENT_MEMORY == new_node)
		{
			free(*_tree);
			/* To prevent dangling pointer(s)*/
			*_tree = NULL;
			return _ERROR_INSUFFICIENT_MEMORY;
		}
		else
		{
			/* Root only */
			if (1U == _max_node_count)
			{
				/* Root properties */
				new_node->_data					= **_table_list;
				new_node->_height				= 0;
				new_node->_node_ID				= new_node->_node_count_level	= new_node->_node_count_depth	= 1U;
				new_node->_parent				= new_node;
				new_node->_left					= (struct _tree_node*)NULL;
				new_node->_right				= (struct _tree_node*)NULL;
			}
			else
			{
				/* Append each level */
				for (auto uint64_t _level_index = 1; _level_index < _level_count; _level_index++)
				{
					auto uint64_t _max_node_count_level = (uint64_t)pow((uint8_t)2U, (_level_index));
					/* Sanity check */
					if (((_level_index != 1U) && ((_data_size_list[_level_index]) != _max_node_count_level)) \
						|| ((_level_index == 1U) && (_data_size_list[0] != 1U)))
					{
						return _ERROR_DATA_PTR;
					}
#ifdef _DEBUG_
					printf("\n\nTree level: %llu", _level_index);

#endif // _DEBUG_
					/* Root */
					if (_level_index == 1U)
					{
						/* Root properties */
						new_node->_data						= **_table_list;
						new_node->_height					= 0;
						new_node->_node_ID					= new_node->_node_count_level			= new_node->_node_count_depth	= 1U;
						new_node->_parent					= new_node;
						new_node->_left						= (new_node + 1U);
						new_node->_right					= (new_node + 2U);

						/* Children properties */
						(new_node + 1U)->_parent			= new_node;
						(new_node + 2U)->_parent			= new_node;

						(new_node + 1U)->_data				= *(*(&_table_list[1U]));
						(new_node + 2U)->_data				= (*(&(*(&_table_list[1U]))[1U]));

						(new_node + 1U)->_node_ID			= 2U;
						(new_node + 2U)->_node_ID			= 3U;

						(new_node + 1U)->_left				= (new_node + 2U)->_left				= (struct _tree_node*)NULL;
						(new_node + 1U)->_right				= (new_node + 2U)->_right				= (struct _tree_node*)NULL;

						(new_node + 1U)->_height			= (new_node + 2U)->_height				= 1U;
						(new_node + 1U)->_node_count_depth  = (new_node + 2U)->_node_count_depth	= 3U;
						(new_node + 1U)->_node_count_level	= (new_node + 2U)->_node_count_level	= _max_node_count_lvl2;

#ifdef _DEBUG_
						for (auto uint64_t _debug_index = 0; _debug_index < _max_node_count_lvl2; _debug_index++)
						{
							printf("\n\n\tNode parent index: %u\n\tNode child index:  %llu", 0, _debug_index);
							Tree_Print_Node_Value((new_node + _debug_index));
							printf("\n\tNode[%llu]'s Left Child Addr: %p\n\tNode[%llu]'s Right Child Addr: %p", \
								_debug_index, (new_node + _debug_index)->_left, _debug_index, (new_node + _debug_index)->_right);
							fflush(stdout);
						}
#endif // _DEBUG_	
					}
					else
					{
						/* Level >= 1 */
						/* O(n) */
						auto uint64_t _temp  = _max_node_count_level - 1U, _temp1 = (uint64_t)pow((uint8_t)2U, (_level_index - 1U)) - 1U,	\
									  _temp2 = (uint64_t)pow((uint8_t)2U, (_level_index + 1U)) - 1U;
						for (auto uint64_t _index2 = _temp1, _index = 0; _index < _max_node_count_level; _index++)
						{
							/* New node assignments, leaf by default */
							(new_node + _temp + _index)->_height			= _level_index;
							(new_node + _temp + _index)->_node_ID			= _index + _max_node_count_level;
							(new_node + _temp + _index)->_node_count_level	= _max_node_count_level;
							(new_node + _temp + _index)->_node_count_depth  = _temp2;
							(new_node + _temp + _index)->_data				= (*((_table_list[_level_index]) + _index));
							(new_node + _temp + _index)->_left				= (struct _tree_node*)NULL;
							(new_node + _temp + _index)->_right				= (struct _tree_node*)NULL;
#ifdef _DEBUG_
							printf("\n\n\tNode parent index: %llu\n\tNode child index:  %llu", _index2, _temp + _index);
							Tree_Print_Node_Value((new_node + _temp + _index));
							fflush(stdout);
#endif // _DEBUG_
							/* Assignment of children nodes to the parent(s) */
							if (!(_index % 2U))
							{
								/* Left node */
								(new_node + _temp + _index)->_parent = (new_node + _index2);
								(new_node + _index2)->_left			 = (new_node + _temp + _index);
#ifdef _DEBUG_
								printf("\n\tNode[%llu]'s Left Child Addr: %p", _index2, (new_node + _index2)->_left);
								fflush(stdout);
#endif // _DEBUG_
							}
							else
							{
								/* Right node */
								(new_node + _temp + _index)->_parent = (new_node + _index2);
								(new_node + _index2)->_right		 = (new_node + _temp + _index);
#ifdef _DEBUG_
								printf("\n\tNode[%llu]'s Right Child Addr: %p", _index2, (new_node + _index2)->_right);
								fflush(stdout);
#endif // _DEBUG_
								_index2++;
							}
						}
					}
					(*_tree) = new_node;
				}
			}
		}
	}
	return _SUCCESS_PTR;
}