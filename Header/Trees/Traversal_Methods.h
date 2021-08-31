#ifndef __TRAVERSAL_METHODS_H__
#define __TRAVERSAL_METHODS_H__

/* Depth First Traversal Methods */
extern void  Tree_Pre_Order_Traversal  (struct _tree_node* _tree);
extern void  Tree_In_Order_Traversal   (struct _tree_node* _tree);
extern float Tree_Post_Order_Traversal(struct _tree_node* _tree, uint8_t _evaluate, uint8_t _simplify);

/* Breadth First / Level Order Traversal Methods */
extern void  Tree_Level_Order_Traversal(struct _tree_node* _tree);

/* Helper function to print the tree */
extern void  Tree_Print_Node_Value(struct _tree_node* _tree);

#endif // !__TRAVERSAL_METHODS_H__
