
#include "stdafx.h"
#include "BSearchTree.h"


/**
	brief 생성자.
*/
BSearchTree::BSearchTree() {

	SetRoot( nullptr );
	_total_cnt_node = 0;
}

/**
	brief 소멸자.
*/
BSearchTree::~BSearchTree() {


}

/**
	brief 새로운 데이터를 추가한다.
 */
bool		BSearchTree::InsertNode(int data) {

	//------------------------------------------------------
	//삽입 할 새 노드를 생성 및 초기화 한다.
	//------------------------------------------------------
	TREE_NODE *new_node = new TREE_NODE;
	new_node->_left_child = NULL;
	new_node->_right_child = NULL;

	new_node->_parent = NULL;
	new_node->_data = data;

	//------------------------------------------------------
	//트리 내부에 노드가 존재하지 않는 경우를 체크한다.
	//------------------------------------------------------
	if (NULL == _root_node) {

		SetRoot(new_node);
		return true;
	}

	//삽입 할 자식 노드 경로 체크 용도.
	BOOL is_left_child_insert = FALSE;
	BOOL is_right_child_insert = FALSE;


	//------------------------------------------------------
	//트리 내부 탐색한다.
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
		//같은 값이 존재하는 경우.
		//------------------------------------------------------
		else if (search_node->_data == data) {

			return FALSE;
		}
	}

	//------------------------------------------------------
	//삽입 할 단말 노드 위치에 새 삽입한다.
	//------------------------------------------------------
	if (TRUE == is_left_child_insert) {

		search_node->_left_child = new_node;

	}
	else if (TRUE == is_right_child_insert) {


		search_node->_right_child = new_node;


	}

	//부모 노드를 설정한다.
	new_node->_parent = search_node;

	//노드 갯수를 증가해준다.
	_total_cnt_node++;

	return TRUE;
}


/**
	brief 특정 데이터를 삭제한다.
*/
bool		BSearchTree::DeleteNode(int data) {


	TREE_NODE *delete_node = _root_node;
	TREE_NODE *parent_of_delete_node = nullptr;

	//------------------------------------------------------
	//삭제 할 노드를 탐색한다.
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
		//삭제 할 노드를 찾은 경우.
		//------------------------------------------------------
		else if (delete_node->_data == data) {

			//------------------------------------------------------
			//만일 루트 노드가 삭제 대상 노드인 경우 
			//parent_of_delete_node는 null로 존재한다.
			//------------------------------------------------------
			break;
		}
	}

	//------------------------------------------------------
	//삭제 대상 노드가 자식이 없는 경우 분기 처리.
	//------------------------------------------------------
	if (/*  왼쪽 자식이 없는 경우 */NULL == delete_node->_left_child &&
		/*오른쪽 자식이 없는 경우 */NULL == delete_node->_right_child) {
		
		//------------------------------------------------------
		//루트가 삭제되는 경우.
		//------------------------------------------------------
		TREE_NODE *root_node = GetRoot();
		if (delete_node == root_node) {

			SetRoot(nullptr);
		}

		//------------------------------------------------------
		//삭제 노드의 부모 노드에서 삭제 노드와 링크 연결을 끊는다.
		//------------------------------------------------------
		else if (parent_of_delete_node->_left_child == delete_node) {

			parent_of_delete_node->_left_child = NULL;
		}
		else if (parent_of_delete_node->_right_child == delete_node) {

			parent_of_delete_node->_right_child = NULL;
		}

		free(delete_node);

		//총 노드 갯수 감소한다.
		_total_cnt_node--;

		return true;
	}

	//------------------------------------------------------
	//삭제 대상 노드가 자식이 한 개인 경우 분기 처리.
	//------------------------------------------------------
	if ( /*오른쪽 자식만 존재하는 경우*/(NULL == delete_node->_left_child && NULL != delete_node->_right_child) ||
		 /*  왼쪽 자식만 존재하는 경우*/(NULL != delete_node->_left_child && NULL == delete_node->_right_child)) {

		// 삭제 노드의 대체 노드.
		TREE_NODE *succession_node = nullptr;

		//------------------------------------------------------
		//삭제 대상 노드의 하나뿐인 자식 노드 찾는다.
		//------------------------------------------------------
		if ( NULL != delete_node->_left_child) {

			//------------------------------------------------------
			//왼쪽 자식만 존재하는 경우.
			//------------------------------------------------------
			succession_node = delete_node->_left_child;
		}
		else if (NULL != delete_node->_right_child) {

			//------------------------------------------------------
			//오른쪽 자식만 존재하는 경우.
			//------------------------------------------------------
			succession_node = delete_node->_right_child;
		}

		//------------------------------------------------------
		//루트가 삭제되는 경우.
		//------------------------------------------------------
		TREE_NODE *root_node = GetRoot();
		if (delete_node == root_node) {

			SetRoot(succession_node);			
		}

		//------------------------------------------------------
		//루트 이외의 노드가 삭제되는 경우.
		//계승 노드가 삭제 노드를 대체한다.
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
	//삭제 대상 노드의 자식 노드가 두개인 경우.
	//------------------------------------------------------
	TREE_NODE *parent_of_succession_node = delete_node;
	TREE_NODE *succession_node = delete_node->_left_child;

	//------------------------------------------------------
	//삭제 대상 노드의 대체 노드를 검색한다.
	//------------------------------------------------------
	for (; ;) {

		if (NULL == succession_node->_right_child) {

			break;
		}

		parent_of_succession_node = succession_node;
		succession_node = succession_node->_right_child;
	}
	//------------------------------------------------------
	// 루트가 삭제되는 경우.
	// 대체 노드의 자식노드들을 삭제 노드의 자식 노드들로 대체한다.
	//------------------------------------------------------
	TREE_NODE *root_node = GetRoot();
	if (root_node == delete_node) {

		//------------------------------------------------------
		//만일 삭제 대상 노드의 바로 왼쪽 노드가 승계노드인 경우를 체크한다.
		//------------------------------------------------------
		 if (root_node->_left_child == succession_node) {

			//------------------------------------------------------
			//자기 자신을 자식으로 가리키는 경우를 차단한다.
			//------------------------------------------------------
			succession_node->_left_child = NULL;
		}

		//------------------------------------------------------
		//왼쪽 자식들을 대체 한다.
		//------------------------------------------------------
		else if (root_node->_left_child != succession_node) {
			
			succession_node->_left_child = root_node->_left_child;
			parent_of_succession_node->_right_child = NULL;
		}

		succession_node->_right_child = root_node->_right_child;
		SetRoot(succession_node);
	}


	//------------------------------------------------------
	//루트 이외의 노드가 삭제되는 경우.
	//------------------------------------------------------

	//------------------------------------------------------
	//삭제 대상 노드가 왼쪽 자식인 경우.
	//------------------------------------------------------
	else if (delete_node==parent_of_delete_node->_left_child) {

		//------------------------------------------------------
		//대체 노드를 삭제 노드와 대체한다.
		//------------------------------------------------------
		parent_of_delete_node->_left_child = succession_node;

		if (succession_node == delete_node->_left_child) {
			
			//------------------------------------------------------
			//자기 자신을 자식으로 가리키는 경우를 차단한다.
			//------------------------------------------------------
			succession_node->_left_child = NULL;
		}
		else {

			succession_node = delete_node->_left_child;
		}

		succession_node->_right_child = delete_node->_right_child;

	}
	//------------------------------------------------------
	//삭제 대상 노드가 오른쪽 자식인 경우.
	//------------------------------------------------------
	else if (parent_of_delete_node->_right_child == delete_node) {

		//------------------------------------------------------
		//대체 노드를 삭제 노드와 대체한다.
		//------------------------------------------------------
		parent_of_delete_node->_right_child = succession_node;

		if (succession_node == delete_node->_left_child) {

			//------------------------------------------------------
			//자기 자신을 자식으로 가리키는 경우를 차단한다.
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
	brief  특정 데이터를 검색하여 노드 리턴한다.
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
		//같은 값이 존재하는 경우.
		//------------------------------------------------------
		else if (search_node->_data == data) {

			return search_node;
		}
	}
}


/**
brief  트리 전체 삭제한다.
*/
bool		BSearchTree::ReleaseTree(void) {

	//후위식 이용한다.
	return true;
}

/**
	brief  전위 순회 방식으로 출력한다.
*/
void		BSearchTree::DisplayPreorder() {

	printf("preorder :");
	Preorder(_root_node);
	printf("\n");
}

/**
	brief  실질적인 전위 순회.
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

	//중위식을 이용해서 그려준다.
	if (NULL == in_node) {

		_depth_tree--;
		return;
	}



	DrawTreeEllise(in_node->_left_child);


	HDC hdc;
	hdc = GetDC(_hwnd);

	_cnt_draw_tree_node++;

	//원을 그린다.
	int left   = _cnt_draw_tree_node * (_radius);
	int top    = (_radius)+(_height_tree * _depth_tree );
	int right  = left+ (_radius);
	int bottom = top - (_radius);

	HBRUSH brush = CreateSolidBrush(RGB(0, 0, 0));
	SelectObject(hdc, brush);

	Ellipse(hdc, left, top, right, bottom);

	//탑 포인터를 설정한다.
	in_node->_top_point_x = left + (_radius / 2);
	in_node->_top_point_y = top;


	//바텀 포인터를 설정한다.
	in_node->_bottom_point_x = left + (_radius / 2);
	in_node->_bottom_point_y = bottom;
	

	//숫자를 세긴다.
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


	//후위식을 이용해 그려준다.
	if (NULL == in_node) {

		return;
	}

	DrawTreeLines(in_node->_left_child);
	DrawTreeLines(in_node->_right_child);

	HDC hdc;
	hdc = GetDC(_hwnd);

	//바텀 포인터를 설정한다.
	int bottom_point_x;
	int bottom_point_y;
	if (NULL != in_node->_parent) {
	
		bottom_point_x = in_node->_parent->_top_point_x;
		bottom_point_y = in_node->_parent->_top_point_y;
	}

	//탑 포인터를 설정한다.
	int top_point_x = in_node->_bottom_point_x;
	int top_point_y = in_node->_bottom_point_y;

	if (NULL != in_node->_parent) {

		MoveToEx(hdc, bottom_point_x, bottom_point_y, NULL);
		LineTo(hdc, top_point_x, top_point_y);
	}

	ReleaseDC(_hwnd, hdc);


}


void BSearchTree::DisplayTreeByWin32() {

	//레벨 순회로 배열 값 채운다.
	//배열 생성한다.

	//초기값 세팅한다.
	_height_tree = 100;
	_depth_tree = -1;
	_cnt_draw_tree_node = -1;
	_radius = 40;
	 

	DrawTreeEllise(_root_node);
	DrawTreeLines(_root_node);


	//배열 삭제한다.

}

void BSearchTree::SetHwnd(HWND hwnd) {

	_hwnd = hwnd;
}