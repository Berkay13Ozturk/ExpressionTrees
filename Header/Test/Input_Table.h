#ifndef __INPUT_TABLE_H__
#define __INPUT_TABLE_H__

/* Data */
	/* Depth of the tree can be increased by appending another level array at the current end */
static float _Table_Level0;
static float _Table_Level1[_LEVEL1];
static float _Table_Level2[_LEVEL2];
static float _Table_Level3[_LEVEL3];

static float* _ptr_tlvl0;
static float* _ptr_tlvl1;
static float* _ptr_tlvl2;
static float* _ptr_tlvl3;

static uint64_t		_size_table[_MAX_TREE_DEPTH_COUNT];
static uint64_t		_level_count;

/* Function declarations */
void* Init_Table(struct _tree_node** _tree);

#endif // !__INPUT_TABLE_H__

