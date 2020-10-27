node* getParent(node* tree, node* child) 
{
	if(tree!=NULL)
	{
		if(tree->left==child || tree->right==child)
			return tree;
		else
		{
			if(tree->val<child->val)
				return getParent(tree->right,child);
			else
				if(tree->val>child->val)
					return getParent(tree->left,child);
		}
	}
}
void deleteLeaf(node** tree, int value)
{
	node *tmp=search(*tree, value);
	if(tmp!=NULL)
	{
		node *p=getParent(*tree,tmp);
		if(isLeaf(tmp)==1)
		{
			if(p->left==tmp)
			{	
				//free(p->left);
				p->left=NULL;
			}
			else if(p->right==tmp)
			{
				//free(p->right);
				p->right=NULL;
			}
		}
	}
}
