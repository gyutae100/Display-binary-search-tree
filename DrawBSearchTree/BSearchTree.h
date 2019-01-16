
#pragma once
#include "stdafx.h"

struct TREE_NODE{

	struct TREE_NODE *_left_child;	///<왼쪽 자식 노드
	struct TREE_NODE *_right_child;	///<오른쪽 자식 노드

	int _data;

	TREE_NODE *_parent;		///<부모 노드

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

	//WIN32로 트리 그리는 데 필요한 함수 목록
	void		DisplayTreeByWin32();
	void		SetHwnd(HWND hwnd);
	void		DrawTreeEllise(TREE_NODE * in_node);
	void		DrawTreeLines(TREE_NODE * in_node);

private:

	TREE_NODE * _root_node;			///< 루트 노드.
	int			_total_cnt_node;	///< 총 트리 노드 갯수.

	TREE_NODE * GetRoot();
	void SetRoot(TREE_NODE* root_node);


	//WIN32로 트리 그리는 데 필요한 변수 목록
	HWND _hwnd;

	int _height_tree;			///<트리 높이
	int _depth_tree;			///<현재 방문한 트리 깊이
	int _cnt_draw_tree_node;	///<현재 그린 트리 갯수
	int _radius;				///<원의 반지름
};



