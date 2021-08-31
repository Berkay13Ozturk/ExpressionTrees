/*
* 
*  Depth First Traversal Methods
* 
*/
#include <stdio.h>
#include <stdint.h>
#include <float.h>

#include "Common/Common.h"
#include "Error/Error.h"
#include "Trees/Basics.h"
#include "Trees/Evaluation.h"
#include "Trees/Traversal_Methods.h"

/* Function Declarations */
static uint64_t			Tree_Height					(struct _tree_node* _tree);
static void				Tree_Current_Level_Traversal(struct _tree_node* _tree, uint64_t _level);

/* Pre-Order Traversal */
void Tree_Pre_Order_Traversal(struct _tree_node* _tree)
{
	/* Data error or root node */
	if (NULL == _tree)
	{
		return;
	}

#ifdef _DEBUG_
	Tree_Print_Node_Value(_tree);
#endif // _DEBUG_

	/* Recursive Traversal */
		/* Any given node is visited before its children is visited. 
		*  First visited node is the root.
		*  Visits the parent first and then left and right children.
		*/
	Tree_Pre_Order_Traversal(_tree->_left);
	Tree_Pre_Order_Traversal(_tree->_right);
}

/* In-Order Traversal */
void Tree_In_Order_Traversal(struct _tree_node* _tree)
{
	/* Data error or root node */
	if (NULL == _tree)
	{
		return;
	}

	/* Recursive Traversal */
		/* First the left child including its entire subtree is visited, then the node is visited,
		*  and finally the right child including its entire subtree is visited. 
		*  Visits the left child, then the parent and the right child.
		*/
	Tree_In_Order_Traversal(_tree->_left);

#ifdef _DEBUG_
	Tree_Print_Node_Value(_tree);
#endif // _DEBUG_

	Tree_In_Order_Traversal(_tree->_right);
}

/* Post-Order Traversal */
float Tree_Post_Order_Traversal(struct _tree_node* _tree, uint8_t _evaluate, uint8_t _simplify)
{
	/* Data error or root node */
	if (NULL == _tree)
	{
		return BLANK;
	}
	/* Leaf - Blank - Redundant node detection, to prevent evaluation of a corrupted tree */
	else if (_evaluate && (!_simplify)																												\

			&& (((_tree->_left    == NULL)					  && (_tree->_right == NULL))															\

			|| (((_tree->_left)   && ((_tree->_right)		  && (_tree->_left->_data == BLANK))	&& (_tree->_right->_data == BLANK)))			\

			|| ((!((_tree->_data  < (OPERATOR_RANGE))		  && (_tree->_data > FLT_EPSILON)))														\

			&& (((_tree->_left)   && (!((_tree->_left->_data  < (OPERATOR_RANGE))					&& (_tree->_left->_data > FLT_EPSILON))))		\

			|| ((_tree->_right)   && (!((_tree->_right->_data < (OPERATOR_RANGE))					&& (_tree->_right->_data > FLT_EPSILON))))))))
	{
		return _tree->_data;
	}
	/* Simplify the tree by pruning the redundant unary operator(s)
	 * 
	 * Condition:
	 *	1 - Node is a unary operator
	 *  2 - Node's child is a leaf
	 *  3 - Node has more than one child node				 (Right node is discarded in this case)
	 *  4 - One of the child node's are not a unary operator (If one of them is a unary operator, depth is increased by one until the child node is of a constant value)
	 */
	else if ((!_evaluate) && _simplify	\

			&& ((_tree->_data	  >= (CUBE)) && (_tree->_data	<= (SQUARE)))																\

			&& (((_tree->_left	  == NULL)	 && (_tree->_right	== NULL))																	\

			|| (((_tree->_left)	  && ((_tree->_left->_data		== BLANK))) || ((_tree->_right))		&& (_tree->_right->_data == BLANK))	\
				
			|| ((_tree->_left)	  && (_tree->_right)))																						\

			&& ((!((_tree->_left) && (_tree->_left->_data		>= (CUBE))	&& (_tree->_left->_data		<= (SQUARE))))						\

			&& (!((_tree->_right) && (_tree->_right->_data		>= (CUBE))	&& (_tree->_right->_data	<= (SQUARE))))))
	{
		/* Evaluate and prune until the parent is no longer a unary operator
		*  If the tree is wrongfully constructed by the user and there will be more than one operands when a parent is a unary operator, the right child will be discarded
		*  Loops until the root node in worst-case
		*/
		auto uint8_t _is_root_processed = FALSE;
		while (((CUBE) == _tree->_data) || ((SQUARE) == _tree->_data))
		{
			/* Left child */
			if ((_tree->_left)	&& (_tree->_left->_data		!= BLANK))
			{
				_tree->_data	= ((CUBE) == _tree->_data)	? (_tree->_left->_data * _tree->_left->_data * _tree->_left->_data)		\
															: (_tree->_left->_data * _tree->_left->_data);
			}
			/* Right child */
			else if ((_tree->_right) && (_tree->_right->_data != BLANK))
			{
				_tree->_data	= ((CUBE) == _tree->_data)	? (_tree->_right->_data * _tree->_right->_data * _tree->_right->_data)	\
															: (_tree->_right->_data * _tree->_right->_data);
			}
			/* Blank children */
			else
			{
				_tree->_data	= BLANK;
			}
			_tree->_left		= _tree->_right = (struct _tree_node*)NULL;
			_tree = _tree->_parent;

			/* Process up to root node */
			if (!(_tree->_height))
			{
				if (_is_root_processed)
				{
					break;
				}
				_is_root_processed = TRUE;
			}
		}
	}

	/* Recursive Traversal */
		/* Any given node is visited after its children is visited.
		*  Visits left child, then the right child and then the parent.
		*/
	auto float _left  = Tree_Post_Order_Traversal(_tree->_left,  _evaluate, _simplify);
	auto float _right = Tree_Post_Order_Traversal(_tree->_right, _evaluate, _simplify);

#ifdef _DEBUG_
	if ((!_evaluate) && (!_simplify))
	{
		Tree_Print_Node_Value(_tree);
	}
#endif // _DEBUG_

	return Evaluate_Operator(_tree->_data, _left, _right);
}

/*
*
*  Breadth First / Level Order Traversal Methods
*
*/

/* Level-Order Traversal */
	/* Height of the Tree */
uint64_t Tree_Height(struct _tree_node* _tree)
{
	/* Data error or root node */
	if (NULL == _tree)
	{
		return 0;
	}
	else
	{
		auto uint64_t _left_height  = Tree_Height(_tree->_left);
		auto uint64_t _right_height = Tree_Height(_tree->_right);

		/* Use whichever is bigger */
		return ((_right_height > _left_height) ? (++_right_height) : (++_left_height));
	}
}

	/* Current Level of the Tree */
static void Tree_Current_Level_Traversal(struct _tree_node* _tree, uint64_t _level)
{
	/* Data error or root node */
	if ((NULL == _tree) || (0 > _level))
	{
		return;
	}

	/* Check the level */
	if (!_level)
	{
#ifdef _DEBUG_
		Tree_Print_Node_Value(_tree);
#endif // _DEBUG_
	}
	else
	{
		auto uint64_t _temp_level = _level - 1U;
		Tree_Current_Level_Traversal(_tree->_left,  _temp_level);
		Tree_Current_Level_Traversal(_tree->_right, _temp_level);
	}

	return;
}

	/* Whole Tree */
void Tree_Level_Order_Traversal(struct _tree_node* _tree)
{
	auto uint64_t _tree_height = Tree_Height(_tree);

	/*
	* Level order traversal processes the nodes level by level.
	* It first processes the root, and then its children, then its grandchildren, and so on.
	* Unlike the other traversal methods, a recursive version does not exist.
	*/

	/* O(n log(n)) */
	for (auto uint64_t _index = 0; _index < _tree_height; _index++)
	{
		Tree_Current_Level_Traversal(_tree, _index);
	}

	return;
}

/* Prints the node values */
void Tree_Print_Node_Value(struct _tree_node* _tree)
{
	if (10U < _tree->_node_ID)
	{
		printf("\n\tNode[%llu]'s Address: %p", _tree->_node_ID, &_tree);
	}
	else
	{
		printf("\n\tNode[%llu]'s  Address: %p", _tree->_node_ID, &_tree);
	}

	/* Floating point value - Operand */
	if ((_tree->_data < BLANK) || (_tree->_data > (OPERATOR_RANGE)))
	{
		printf("\n\t\t   Value:   %f", _tree->_data);
	}
	/* Operator */
	else
	{
		/* Blank */
		if (BLANK == _tree->_data)
		{
			printf("\n\t\t   Value:   \" \"");
		}
		/* Binary operator(s) */
			/* Multiply */
		else if (MULTIPLY == _tree->_data)
		{
			printf("\n\t\t   Value:   \"*\"");
		}
			/* Division */
		else if (DIVIDE == _tree->_data)
		{
			printf("\n\t\t   Value:   \"/\"");
		}
			/* Addition */
		else if (ADD == _tree->_data)
		{
			printf("\n\t\t   Value:   \"+\"");
		}
			/* Subtraction */
		else if (SUB == _tree->_data)
		{
			printf("\n\t\t   Value:   \"-\"");
		}
		/* Unary operator(s) */
			/* Cube */
		else if (CUBE == _tree->_data)
		{
			printf("\n\t\t   Value:   \"Cube\"");
		}
			/* Square */
		else if (SQUARE == _tree->_data)
		{
			printf("\n\t\t   Value:   \"Square\"");
		}
		/* Undefined operator */
		else
		{
			printf("\n\t\t   Value:   \"Undefined!\"");
		}
	}
}