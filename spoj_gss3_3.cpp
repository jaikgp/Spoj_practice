#include <iostream>
#include <stdio.h> 
#define negmin -645643
using namespace std;

struct tree_node 
{
	int sum,max,right,left;
};

int maxs(int a,int b)
	{
		return (a>b)?a:b;
	}

void init_tree(int a[],tree_node tree[],int start,int end,int index)
	{
		if(start==end)
			{
				tree[index].max=tree[index].sum=
				tree[index].left=tree[index].right
				=a[start];
				return;
			}

		int mid=(start+end)/2;
		if(tree[2*index+1].max==negmin)
			init_tree(a,tree,start,mid,2*index+1);
		if(tree[2*index+2].max==negmin)
			init_tree(a,tree,mid+1,end,2*index+2);

		tree[index].left=maxs(tree[2*index+1].sum+
			tree[2*index+2].left,tree[2*index+1].left);
		tree[index].right=maxs(tree[2*index+2].sum+
			tree[2*index+1].right,tree[2*index+2].right);
		tree[index].sum=tree[2*index+1].sum+tree[2*
			index+2].sum;
		tree[index].max=maxs(maxs(tree[2*index+1].max,tree[2*index
			+2].max),tree[2*index+1].right+tree[2*index+2]
			.left);
		return;		
	}

void interval(tree_node &residual,tree_node tree[],int start,int end,int i,int j,int index)
	{
		//cout << "enters" << endl;
		if(start==i&&end==j)
			{
				residual=tree[index];
				return;
			}
		/*if(start>j||end<i)
			{
				residual.max=residual.left=residual.right=
				residual.sum=negmin;
				return;
			}*/
		int mid=(start+end)/2;
		if(j<=mid)
			return interval(residual,tree,start,mid,i,j,2*index+1);
		else if(i>mid)
			return interval(residual,tree,mid+1,end,i,j,2*index+2);
		else
			{
				tree_node right_node,left_node;
				interval(left_node,tree,start,mid,i,mid,2*index+1);
				interval(right_node,tree,mid+1,end,mid+1,j,2*index+2);
				residual.right=maxs(right_node.sum+
					left_node.right,right_node.right);
				residual.left=maxs(left_node.sum+
					right_node.left,left_node.left);
				residual.sum=right_node.sum+left_node.sum;
				residual.max=maxs(maxs(left_node.max,right_node.max)
					,left_node.right+right_node
					.left);
			}
		return;

	}

void update(tree_node tree[],int x,int y,int start,int end,int index)
	{
		if(start==end&&x==start)
			{
				tree[index].right=tree[index].left=tree[index].sum=tree[index].max=y;
				return;
			}
		int mid=(start+end)/2;
		if(x<=mid)
			update(tree,x,y,start,mid,2*index+1);
		else
			update(tree,x,y,mid+1,end,2*index+2);

		tree[index].left=maxs(tree[2*index+1].sum+
			tree[2*index+2].left,tree[2*index+1].left);
		tree[index].right=maxs(tree[2*index+2].sum+
			tree[2*index+1].right,tree[2*index+2].right);
		tree[index].sum=tree[2*index+1].sum+tree[2*
			index+2].sum;
		tree[index].max=maxs(maxs(tree[2*index+1].max,tree[2*index
			+2].max),tree[2*index+1].right+tree[2*index+2]
			.left);
		return;

	}
int main()
	{
		int n;
		scanf("%d",&n);
		tree_node tree[4*n];
		int m,a[n];
		for(int i=0;i<n;i++)
			scanf("%d",&a[i]);
		for(int i=0;i<4*n;i++)
			tree[i].max=tree[i].left=
			tree[i].sum=tree[i].right=negmin;

		init_tree(a,tree,0,n-1,0);
		/*for(int index=0;index<4*n;index++)
			cout << "left=" << tree[index].left << 
			" right=" << tree[index].right <<
			" sum=" << tree[index].sum << 
			" max=" << tree[index].max << endl;
		*/scanf("%d",&m);
		int result[m+1];
		int k=0;
		while(m--)
			{
				int z,x,y;
				scanf("%d %d %d",&z,&x,&y);
				tree_node residual;
				if(z==0)
					update(tree,x-1,y,0,n-1,0);
				else
				    {
				    	interval(residual,tree,0,n-1,x-1,y-1,0);
						result[k++]=residual.max;
					}
			}
		for(int i=0;i<k;i++)
			printf("%d\n",result[i]);
 	}	