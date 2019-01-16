
#pragma once
#include "stdafx.h"

struct TREE_NODE{

	struct TREE_NODE *_left_child;	///<���� �ڽ� ���
	struct TREE_NODE *_right_child;	///<������ �ڽ� ���

	int _data;

	TREE_NODE *_parent;		///<�θ� ���

	int _top_point_x;
	int _top_point_y;

	int _bottom_point_x;
	int _bottom_point_y;
};

class BSearchTree{

public:

	BSearchTree();
	~BSearchTree();

	bool		InsertNode(int data);
	bool		DeleteNode(int data);

	TREE_NODE  *SearchNode(int data);

	bool		ReleaseTree(void);

	void		DisplayPreorder();
	void        Preorder(TREE_NODE * in_node);

	//WIN32�� Ʈ�� �׸��� �� �ʿ��� �Լ� ���
	void		DisplayTreeByWin32();
	void		SetHwnd(HWND hwnd);
	void		DrawTreeEllise(TREE_NODE * in_node);
	void		DrawTreeLines(TREE_NODE * in_node);

private:

	TREE_NODE * _root_node;			///< ��Ʈ ���.
	int			_total_cnt_node;	///< �� Ʈ�� ��� ����.

	TREE_NODE * GetRoot();
	void SetRoot(TREE_NODE* root_node);


	//WIN32�� Ʈ�� �׸��� �� �ʿ��� ���� ���
	HWND _hwnd;

	int _height_tree;			///<Ʈ�� ����
	int _depth_tree;			///<���� �湮�� Ʈ�� ����
	int _cnt_draw_tree_node;	///<���� �׸� Ʈ�� ����
	int _radius;				///<���� ������
};



