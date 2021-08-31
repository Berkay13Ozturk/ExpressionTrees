#ifndef __BASICS_H__
#define __BASICS_H__

/* Data types */
struct _tree_node
{
	/* Value */
	float _data;
	/* Height */
	uint64_t _height;
	/* Total Node Count at that Depth Level */
	uint64_t _node_count_depth;
	/* Node Count at the Depth Level */
	uint64_t _node_count_level;
	/* Node's ID */
	uint64_t _node_ID;
	/* Parent Node */
	struct  _tree_node* _parent;
	/* Children Nodes */
	struct  _tree_node* _right;
	struct  _tree_node* _left;
};

/* Function declarations */
extern void* Tree_Create_from_Node_Groups(struct _tree_node** _tree, float** _table_list, uint64_t* _data_size_list, const uint64_t _level_count);

#endif // !__BASICS_H__

