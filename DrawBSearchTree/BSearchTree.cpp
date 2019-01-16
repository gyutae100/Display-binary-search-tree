
#include "stdafx.h"
#include "BSearchTree.h"


/**
	brief ������.
*/
BSearchTree::BSearchTree() {

	SetRoot( nullptr );
	_total_cnt_node = 0;
}

/**
	brief �Ҹ���.
*/
BSearchTree::~BSearchTree() {


}

/**
	brief ���ο� �����͸� �߰��Ѵ�.
 */
bool		BSearchTree::InsertNode(int data) {

	//------------------------------------------------------
	//���� �� �� ��带 ���� �� �ʱ�ȭ �Ѵ�.
	//------------------------------------------------------
	TREE_NODE *new_node = new TREE_NODE;
	new_node->_left_child = NULL;
	new_node->_right_child = NULL;

	new_node->_parent = NULL;
	new_node->_data = data;

	//------------------------------------------------------
	//Ʈ�� ���ο� ��尡 �������� �ʴ� ��츦 üũ�Ѵ�.
	//------------------------------------------------------
	if (NULL == _root_node) {

		SetRoot(new_node);
		return true;
	}

	//���� �� �ڽ� ��� ��� üũ �뵵.
	BOOL is_left_child_insert = FALSE;
	BOOL is_right_child_insert = FALSE;


	//------------------------------------------------------
	//Ʈ�� ���� Ž���Ѵ�.
	//------------------------------------------------------
	TREE_NODE *search_node = _root_node;

	for (; ;) {

		if (search_node->_data < data) {

			if (NULL == search_node->_right_child) {

				is_right_child_insert = TRUE;
				break;
			}

			search_node = search_node->_right_child;
		}

		else if (search_node->_data > data) {

			if (NULL == search_node->_left_child) {

				is_left_child_insert = TRUE;
				break;
			}

			search_node = search_node->_left_child;
		}

		//------------------------------------------------------
		//���� ���� �����ϴ� ���.
		//------------------------------------------------------
		else if (search_node->_data == data) {

			return FALSE;
		}
	}

	//------------------------------------------------------
	//���� �� �ܸ� ��� ��ġ�� �� �����Ѵ�.
	//------------------------------------------------------
	if (TRUE == is_left_child_insert) {

		search_node->_left_child = new_node;

	}
	else if (TRUE == is_right_child_insert) {


		search_node->_right_child = new_node;


	}

	//�θ� ��带 �����Ѵ�.
	new_node->_parent = search_node;

	//��� ������ �������ش�.
	_total_cnt_node++;

	return TRUE;
}


/**
	brief Ư�� �����͸� �����Ѵ�.
*/
bool		BSearchTree::DeleteNode(int data) {


	TREE_NODE *delete_node = _root_node;
	TREE_NODE *parent_of_delete_node = nullptr;

	//------------------------------------------------------
	//���� �� ��带 Ž���Ѵ�.
	//------------------------------------------------------
	for (; ;) {

		if (delete_node->_data < data) {

			if (NULL == delete_node->_right_child) {

				return false;
			}

			parent_of_delete_node = delete_node;
			delete_node = delete_node->_right_child;
		}

		else if (delete_node->_data > data) {

			if (NULL == delete_node->_left_child) {


				return false;
			}

			parent_of_delete_node = delete_node;
			delete_node = delete_node->_left_child;
		}
		//------------------------------------------------------
		//���� �� ��带 ã�� ���.
		//------------------------------------------------------
		else if (delete_node->_data == data) {

			//------------------------------------------------------
			//���� ��Ʈ ��尡 ���� ��� ����� ��� 
			//parent_of_delete_node�� null�� �����Ѵ�.
			//------------------------------------------------------
			break;
		}
	}

	//------------------------------------------------------
	//���� ��� ��尡 �ڽ��� ���� ��� �б� ó��.
	//------------------------------------------------------
	if (/*  ���� �ڽ��� ���� ��� */NULL == delete_node->_left_child &&
		/*������ �ڽ��� ���� ��� */NULL == delete_node->_right_child) {
		
		//------------------------------------------------------
		//��Ʈ�� �����Ǵ� ���.
		//------------------------------------------------------
		TREE_NODE *root_node = GetRoot();
		if (delete_node == root_node) {

			SetRoot(nullptr);
		}

		//------------------------------------------------------
		//���� ����� �θ� ��忡�� ���� ���� ��ũ ������ ���´�.
		//------------------------------------------------------
		else if (parent_of_delete_node->_left_child == delete_node) {

			parent_of_delete_node->_left_child = NULL;
		}
		else if (parent_of_delete_node->_right_child == delete_node) {

			parent_of_delete_node->_right_child = NULL;
		}

		free(delete_node);

		//�� ��� ���� �����Ѵ�.
		_total_cnt_node--;

		return true;
	}

	//------------------------------------------------------
	//���� ��� ��尡 �ڽ��� �� ���� ��� �б� ó��.
	//------------------------------------------------------
	if ( /*������ �ڽĸ� �����ϴ� ���*/(NULL == delete_node->_left_child && NULL != delete_node->_right_child) ||
		 /*  ���� �ڽĸ� �����ϴ� ���*/(NULL != delete_node->_left_child && NULL == delete_node->_right_child)) {

		// ���� ����� ��ü ���.
		TREE_NODE *succession_node = nullptr;

		//------------------------------------------------------
		//���� ��� ����� �ϳ����� �ڽ� ��� ã�´�.
		//------------------------------------------------------
		if ( NULL != delete_node->_left_child) {

			//------------------------------------------------------
			//���� �ڽĸ� �����ϴ� ���.
			//------------------------------------------------------
			succession_node = delete_node->_left_child;
		}
		else if (NULL != delete_node->_right_child) {

			//------------------------------------------------------
			//������ �ڽĸ� �����ϴ� ���.
			//------------------------------------------------------
			succession_node = delete_node->_right_child;
		}

		//------------------------------------------------------
		//��Ʈ�� �����Ǵ� ���.
		//------------------------------------------------------
		TREE_NODE *root_node = GetRoot();
		if (delete_node == root_node) {

			SetRoot(succession_node);			
		}

		//------------------------------------------------------
		//��Ʈ �̿��� ��尡 �����Ǵ� ���.
		//��� ��尡 ���� ��带 ��ü�Ѵ�.
		//------------------------------------------------------
		else if (parent_of_delete_node->_left_child == delete_node) {

			parent_of_delete_node->_left_child = succession_node;
		}
		else if (parent_of_delete_node->_right_child == delete_node) {

			parent_of_delete_node->_right_child = succession_node;
		}

		free(delete_node);
		return true;
	}

	//------------------------------------------------------
	//���� ��� ����� �ڽ� ��尡 �ΰ��� ���.
	//------------------------------------------------------
	TREE_NODE *parent_of_succession_node = delete_node;
	TREE_NODE *succession_node = delete_node->_left_child;

	//------------------------------------------------------
	//���� ��� ����� ��ü ��带 �˻��Ѵ�.
	//------------------------------------------------------
	for (; ;) {

		if (NULL == succession_node->_right_child) {

			break;
		}

		parent_of_succession_node = succession_node;
		succession_node = succession_node->_right_child;
	}
	//------------------------------------------------------
	// ��Ʈ�� �����Ǵ� ���.
	// ��ü ����� �ڽĳ����� ���� ����� �ڽ� ����� ��ü�Ѵ�.
	//------------------------------------------------------
	TREE_NODE *root_node = GetRoot();
	if (root_node == delete_node) {

		//------------------------------------------------------
		//���� ���� ��� ����� �ٷ� ���� ��尡 �°����� ��츦 üũ�Ѵ�.
		//------------------------------------------------------
		 if (root_node->_left_child == succession_node) {

			//------------------------------------------------------
			//�ڱ� �ڽ��� �ڽ����� ����Ű�� ��츦 �����Ѵ�.
			//------------------------------------------------------
			succession_node->_left_child = NULL;
		}

		//------------------------------------------------------
		//���� �ڽĵ��� ��ü �Ѵ�.
		//------------------------------------------------------
		else if (root_node->_left_child != succession_node) {
			
			succession_node->_left_child = root_node->_left_child;
			parent_of_succession_node->_right_child = NULL;
		}

		succession_node->_right_child = root_node->_right_child;
		SetRoot(succession_node);
	}


	//------------------------------------------------------
	//��Ʈ �̿��� ��尡 �����Ǵ� ���.
	//------------------------------------------------------

	//------------------------------------------------------
	//���� ��� ��尡 ���� �ڽ��� ���.
	//------------------------------------------------------
	else if (delete_node==parent_of_delete_node->_left_child) {

		//------------------------------------------------------
		//��ü ��带 ���� ���� ��ü�Ѵ�.
		//------------------------------------------------------
		parent_of_delete_node->_left_child = succession_node;

		if (succession_node == delete_node->_left_child) {
			
			//------------------------------------------------------
			//�ڱ� �ڽ��� �ڽ����� ����Ű�� ��츦 �����Ѵ�.
			//------------------------------------------------------
			succession_node->_left_child = NULL;
		}
		else {

			succession_node = delete_node->_left_child;
		}

		succession_node->_right_child = delete_node->_right_child;

	}
	//------------------------------------------------------
	//���� ��� ��尡 ������ �ڽ��� ���.
	//------------------------------------------------------
	else if (parent_of_delete_node->_right_child == delete_node) {

		//------------------------------------------------------
		//��ü ��带 ���� ���� ��ü�Ѵ�.
		//------------------------------------------------------
		parent_of_delete_node->_right_child = succession_node;

		if (succession_node == delete_node->_left_child) {

			//------------------------------------------------------
			//�ڱ� �ڽ��� �ڽ����� ����Ű�� ��츦 �����Ѵ�.
			//------------------------------------------------------
			succession_node->_left_child = NULL;
		}
		else {

			succession_node = delete_node->_left_child;
		}

		succession_node->_right_child = delete_node->_right_child;
	}

	return true;
}

/**
	brief  Ư�� �����͸� �˻��Ͽ� ��� �����Ѵ�.
*/
TREE_NODE  *BSearchTree::SearchNode(int data) {

	TREE_NODE *search_node = _root_node;
	for (; ;) {

		if (search_node->_data < data) {

			if (NULL == search_node->_right_child) {

				return nullptr;
			}

			search_node = search_node->_right_child;
		}

		else if (search_node->_data > data) {

			if (NULL == search_node->_left_child) {

				return nullptr;
			}

			search_node = search_node->_left_child;
		}

		//------------------------------------------------------
		//���� ���� �����ϴ� ���.
		//------------------------------------------------------
		else if (search_node->_data == data) {

			return search_node;
		}
	}
}


/**
brief  Ʈ�� ��ü �����Ѵ�.
*/
bool		BSearchTree::ReleaseTree(void) {

	//������ �̿��Ѵ�.
	return true;
}

/**
	brief  ���� ��ȸ ������� ����Ѵ�.
*/
void		BSearchTree::DisplayPreorder() {

	printf("preorder :");
	Preorder(_root_node);
	printf("\n");
}

/**
	brief  �������� ���� ��ȸ.
*/
void BSearchTree::Preorder(TREE_NODE * in_node){

	if (NULL == in_node) {

		return;
	}

	printf("%5d ", in_node->_data);

	Preorder(in_node->_left_child);
	Preorder(in_node->_right_child);
}


TREE_NODE * BSearchTree::GetRoot() {

	return _root_node;
}

void BSearchTree::SetRoot(TREE_NODE* root_node) {

	_root_node = root_node;
}

void BSearchTree::DrawTreeEllise(TREE_NODE * in_node) {


	_depth_tree++;

	//�������� �̿��ؼ� �׷��ش�.
	if (NULL == in_node) {

		_depth_tree--;
		return;
	}



	DrawTreeEllise(in_node->_left_child);


	HDC hdc;
	hdc = GetDC(_hwnd);

	_cnt_draw_tree_node++;

	//���� �׸���.
	int left   = _cnt_draw_tree_node * (_radius);
	int top    = (_radius)+(_height_tree * _depth_tree );
	int right  = left+ (_radius);
	int bottom = top - (_radius);

	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, brush);

	Ellipse(hdc, left, top, right, bottom);

	//ž �����͸� �����Ѵ�.
	in_node->_top_point_x = left + (_radius / 2);
	in_node->_top_point_y = top;


	//���� �����͸� �����Ѵ�.
	in_node->_bottom_point_x = left + (_radius / 2);
	in_node->_bottom_point_y = bottom;
	

	//���ڸ� �����.
	WCHAR value[10];
	_itot_s(in_node->_data, value, 10);

	HPEN pen = CreatePen(PS_SOLID, 3, RGB(0, 0, 0));
	SelectObject(hdc, pen);

	//SetBkMode(hdc, TRANSPARENT);
	TextOutW(hdc, left +(_radius/2), top - (_radius/2), value, wcslen(value));

	ReleaseDC(_hwnd, hdc);

	DrawTreeEllise(in_node->_right_child);

	_depth_tree--;
}


void BSearchTree::DrawTreeLines(TREE_NODE * in_node) {


	//�������� �̿��� �׷��ش�.
	if (NULL == in_node) {

		return;
	}

	DrawTreeLines(in_node->_left_child);
	DrawTreeLines(in_node->_right_child);

	HDC hdc;
	hdc = GetDC(_hwnd);

	//���� �����͸� �����Ѵ�.
	int bottom_point_x;
	int bottom_point_y;
	if (NULL != in_node->_parent) {
	
		bottom_point_x = in_node->_parent->_top_point_x;
		bottom_point_y = in_node->_parent->_top_point_y;
	}

	//ž �����͸� �����Ѵ�.
	int top_point_x = in_node->_bottom_point_x;
	int top_point_y = in_node->_bottom_point_y;

	if (NULL != in_node->_parent) {

		MoveToEx(hdc, bottom_point_x, bottom_point_y, NULL);
		LineTo(hdc, top_point_x, top_point_y);
	}

	ReleaseDC(_hwnd, hdc);


}


void BSearchTree::DisplayTreeByWin32() {

	//���� ��ȸ�� �迭 �� ä���.
	//�迭 �����Ѵ�.

	//�ʱⰪ �����Ѵ�.
	_height_tree = 100;
	_depth_tree = -1;
	_cnt_draw_tree_node = -1;
	_radius = 40;
	 

	DrawTreeEllise(_root_node);
	DrawTreeLines(_root_node);


	//�迭 �����Ѵ�.

}

void BSearchTree::SetHwnd(HWND hwnd) {

	_hwnd = hwnd;
}