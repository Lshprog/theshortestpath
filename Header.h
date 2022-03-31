#pragma once
#include <iostream>
#include <queue>

namespace shortp {
	struct Point {
		int x, y;
		bool checked;
		int value;
		Point(int x,int y);
	};
	struct AWayOut {
	private:
		struct Node {
			Point* data;
			Node* next=nullptr;
			Node* prev=nullptr;
			Node(Point* data);
		};
		Node* head=nullptr;
		Node* tail=nullptr;
	public:
		void findpath(Point* startpos);
		void writepathinside(Point* end);
		void print_out_path();
	};
	void startprog();
}