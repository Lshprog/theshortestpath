#include "Header.h"

const int X = 8;
const int Y = 8;
int Field[X][Y] = {
	-2, 1, 1, 1, 1, 1, 1, 1,
	-2,-2, 1,-2, 1, 1, 1, 1,
	 1, 1, 1, 0, 1,-2, 1, 1,
	 1,-2,-2,-2,-2,-2,-2, 1,
	 1,-2, 1, 1, 1, 1,-2, 1,
	 1,-2, 1,-2, 1, 1, 1, 1,
	-2,-2, 1,-2, 1,-2,-2,-2,
	-2,-2, 1, 1, 1, 1, 1, 1
};

shortp::Point::Point(int x, int y)
{
	this->x = x;
	this->y = y;
	this->checked = false;
	
}

void shortp::startprog() {
	shortp::AWayOut list = shortp::AWayOut();
	
	for (int j=0 ; j < 8; j++) {
		for (int k=0; k < 8; k++) {
			if (Field[j][k] == 0) {
				shortp::Point sourcep = shortp::Point(j, k);
				list.findpath(&sourcep);
				return;
			}
		}
	}
	
}

shortp::AWayOut::Node::Node(Point* data)
{
	this->data = data;
}

void shortp::AWayOut::findpath(Point* startpos)
{
	

	int checksx[] = { 1,-1,0,0 };
	int checksy[] = { 0,0,1,-1 };

	Point* temp_end = new Point(0,0);

	std::queue<Point*>allv;

	allv.push(startpos);
	
	while (allv.empty() == false) {
		Point* curpos = allv.front();
		for (int i = 0; i < 4; i++) {
			if (Field[curpos->x][curpos->y] == 2 && Field[curpos->x + checksx[i]][curpos->y + checksy[i]] == 1) {
				bool nochange = false;
				for (int j = 0; j < 4; j++) {
					if ((Field[curpos->x + checksx[i] + checksx[j]][curpos->y + checksy[i] + checksy[j]] == 0)&&
						(curpos->x + checksx[i] + checksx[j] > -1 && curpos->y + checksy[i] + checksy[j] > -1 &&
							curpos->y + checksy[i] + checksy[j] < 8 && curpos->x + checksx[i] + checksx[j] < 8)) {

						nochange = true;
					}
				}
				if (nochange) {
					continue;
				}
			}
			if ((Field[curpos->x + checksx[i]][curpos->y + checksy[i]]==1)&&
				(curpos->x + checksx[i] >-1 && curpos->y + checksy[i]>-1 &&
					curpos->y + checksy[i]<8&& curpos->x + checksx[i]<8)) {		

				Field[curpos->x + checksx[i]][curpos->y + checksy[i]] = Field[curpos->x][curpos->y] + 1;
				Point* cheto = new Point(curpos->x + checksx[i], curpos->y + checksy[i]);
				allv.push(cheto);
				if ((cheto->x == 7) && (cheto->y == 7)) {
					temp_end = cheto;
					break;
				}
			}
		}
		
		allv.pop();
	}
	for (int j = 0; j < 8; j++) {
		for (int k = 0; k < 8; k++) {
			if(Field[j][k]<0||Field[j][k]>9)
				std::cout<<" " << Field[j][k] << "  ";
			else
				std::cout << "  " << Field[j][k] << "  ";
		}
		std::cout << "\n";
	}
	while (!allv.empty()) allv.pop();
	
	writepathinside(temp_end);
	return;
}

void shortp::AWayOut::writepathinside(Point* end)
{
	int checksx[] = { 1,-1,0,0 };
	int checksy[] = { 0,0,1,-1 };
	
	Node* curpos = new Node(end);
	tail = curpos;

	while (Field[curpos->data->x][curpos->data->y] != 0) {
		for (int i = 0; i < 4; i++) {
			if ((Field[curpos->data->x - checksx[i]][curpos->data->y - checksy[i]] == Field[curpos->data->x][curpos->data->y]-1)) {
				Point* cheto = new Point(curpos->data->x - checksx[i], curpos->data->y - checksy[i]);
				Node* temp_n = new Node(cheto);
				curpos->prev = temp_n;
				temp_n->next = curpos;
				curpos = temp_n;
			}
		}
	}
	
	head = curpos;
	
	print_out_path();
	return;
}

void shortp::AWayOut::print_out_path()
{
	std::cout << "Test printoutpath";
	Node* temp = head;

	while (true) {
		std::cout << "x - " << temp->data->x << " y - " << temp->data->y<<'\n';
		if (temp == tail)
			break;
		temp = temp->next;
	}
	std::cout << "Total steps - " << Field[tail->data->x][tail->data->y];

	return;
}
