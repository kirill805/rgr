#define _CRT_SECURE_NO_WARNINGS

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <cmath>

#include "Node.h" //����� ������
#include "Link.h" //����� ����

using namespace sf;
using namespace std;

bool MouseOnNode(CircleShape &param,RenderWindow &window) { //������� ������������ ������� �� ����
	int mouseX = Mouse::getPosition(window).x;
	int mouseY = Mouse::getPosition(window).y;

	if ((mouseX > param.getPosition().x && mouseY > param.getPosition().y) && (mouseX < (param.getPosition().x + param.getGlobalBounds().width)) && (mouseY < (param.getPosition().y + param.getGlobalBounds().height))) {
		return true;
	} else {
		return false;
	}
}

int MOF(int _i,int _s,int *H,int *T,int*F,int M) { //max of flow - ������� ����������� ������������� ������ ������
	
	int tH = _i, tT = _s, tF = 0;

	if (_i != _s) {
		for (int i = 0; i < M; ++i) {
			if (H[i] == tH && T[i] == _s) { return F[i]; }
		}

		for (int i = 0; i < M; ++i) {
			if (H[i] == tH) { 
				tH = H[i]; tT = T[i]; 
				
				tF = F[i]; 
				
				cout << tH << " " << tT << " " << tF << endl;
				break; 
			}
		}

		for (int j = 0; j < M; ++j) {

			for (int i = 0; i < M; ++i) {
				if (H[i] == tT && T[i] == _s) { 
					if (tF < F[i]) {
						return tF;
					}else{ 
						return F[i];
					}
				
				}
			}

			for (int i = 0; i < M; ++i) {
				if (H[i] == tT) {
					tH = H[i]; tT = T[i];

					if (F[i] < tF)
						tF = F[i];

					cout << tH << " " << tT << " " << tF << endl;
					break;
				}
			}

		}
		//return tF;
	} else {
		return -1;
	}
	cout << endl;
	return 0;
}

int main() {
	/* -------------------- ��������� �� ����� ������ � ����� ------------------------*/

	int N; //����� ������
	int M; //����� ����

	string info; //���������� ���������� � ��������� �� ������

	ifstream f; //������� ����� ��� ���������� ������ �� topology.txt
	f.open("topology.txt"); //��������� �����
	f >> N; //��������� ����� ������
	info += to_string(N) + " nodes\n\n";  

	Node* Nodes = new Node[N]; //������ N ������

	for (int i = 0; i < N; i++) { //�������� ������� �������
		Nodes[i].N = i + 1; //������������� �������
		f >> Nodes[i].x; //�����-�
		f >> Nodes[i].y; //�����-�

		info += "(" + to_string(Nodes[i].N) + ") [" + to_string(Nodes[i].x) + ";" + to_string(Nodes[i].y) + "]\n";
	}

	f >> M; //��������� ����� ����
	info += "\n" + to_string(M) + " links\n\n";

	Link* Links = new Link[M]; //������ M ����

	int A, B; //�����������
	int *H = new int[M]; //��� ���������
	int* T = new int[M];
	int* F = new int[M];

	for (int i = 0; i < M; i++) { //�������� ���� �������
		Links[i].M = i + 1; //������������� �����

		f >> A; //������ �����
		H[i] = A;
		A--; //�������������
		Links[i].A = Nodes[A];

		f >> B; //����� �����
		T[i] = B;
		B--; //�������������
		Links[i].B = Nodes[B];

		f >> Links[i].F; //���������� ����������� �����
		F[i] = Links[i].F;

		info += "(" + to_string(Links[i].M) + ") [" + to_string(Nodes[A].N) + ";" + to_string(Nodes[B].N) + "] = " + to_string(Links[i].F) + "\n";
	}

	f.close(); //��������� ����� ������

	/* -------------------- ������������ ��������� ���� ------------------------*/

	Font font; //���������� ������
	font.loadFromFile("arial.ttf"); //���������� ����� �� ��������

	Text infoText; //���������� � ��������� �� ������
	infoText.setCharacterSize(12); //������ ������
	infoText.setFillColor(Color::White); //����� ���� ������
	infoText.setFont(font); //��������� ������������ �����
	infoText.setPosition(20,20); //������������� ������ �� �����
	infoText.setString(info); //����� ��������� �����

	Text istok; //���������� �� ������
	istok.setCharacterSize(12);
	istok.setFillColor(Color::White);
	istok.setFont(font);
	istok.setPosition(190, 20);
	istok.setString("istok: ");

	Text stok; //���������� � �����
	stok.setCharacterSize(12);
	stok.setFillColor(Color::White);
	stok.setFont(font);
	stok.setPosition(190, 40);
	stok.setString("stok: ");

	Text answer;  //���������� � ������������ ������ ������
	answer.setCharacterSize(12);
	answer.setFillColor(Color::White);
	answer.setFont(font);
	answer.setPosition(190, 60);
	answer.setString("Max flow: ");

	/* -------------------- ������������ ���� ��������� ------------------------*/

	Nodes->GraphicNodes = new CircleShape[N]; //���� �������
	Text* TextNodes = new Text[N]; //������ ������

	for (int i = 0; i < N; i++) { //���������� �������
		Nodes->GraphicNodes[i].setFillColor(Color::Red); //����� ���� �������
		Nodes->GraphicNodes[i].setRadius(8); //����� ������ �������
		Nodes->GraphicNodes[i].setPosition((Nodes[i].x * 12) + 500, (Nodes[i].y * 12)+ 150); //���������������� �������

		TextNodes[i].setCharacterSize(10);
		TextNodes[i].setFillColor(Color::White);
		TextNodes[i].setFont(font);
		TextNodes[i].setPosition((Nodes[i].x * 12) + 505, (Nodes[i].y * 12) + 153);
		TextNodes[i].setString(to_string(i+1));
	}

	/* -------------------- ������������ Ш��� ��������� ------------------------*/

	RectangleShape* GraphicLinks = new RectangleShape[M]; //������������� ��� ��������� �����
	
	for (int i = 0; i < M; i++) { //���������� ����
		GraphicLinks[i].setFillColor(Color::White);
		float width = sqrtf(powf(Links[i].B.x - Links[i].A.x,2)+ powf(Links[i].B.y - Links[i].A.y, 2)) * 12; //��������� ����������
		GraphicLinks[i].setSize(Vector2f(width-20, 4)); //����� �����
		float katet = sqrtf(powf(Links[i].B.x - Links[i].A.x, 2) + powf(Links[i].A.y - Links[i].A.y, 2)) * 12; //����� ������
		float angle;
		if ((Links[i].B.x >= Links[i].A.x) && (Links[i].B.y >= Links[i].A.y)) { //4 ������������ ��������
			angle = acosf(katet / width) * 180 / 3.14; //��������� ����
			GraphicLinks[i].rotate(angle); //����� ����
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160); //�������������
		} else if ((Links[i].B.x <= Links[i].A.x) && (Links[i].B.y >= Links[i].A.y)) {
			angle = 180 - acosf(katet / width) * 180 / 3.14;
			GraphicLinks[i].rotate(angle);
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160);
		} else if ((Links[i].B.x >= Links[i].A.x) && (Links[i].B.y <= Links[i].A.y)) {
			angle = 360 - acosf(katet / width) * 180 / 3.14;
			GraphicLinks[i].rotate(angle);
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160);
		} else if ((Links[i].B.x <= Links[i].A.x) && (Links[i].B.y <= Links[i].A.y)) {
			angle = 270 - acosf(katet / width) * 180 / 3.14;
			GraphicLinks[i].rotate(angle);
			GraphicLinks[i].setPosition((Links[i].A.x * 12) + 510, (Links[i].A.y * 12) + 160);
		}
	}

	/* -------------------- ������������ ������� ���� ------------------------*/

	RenderWindow window(VideoMode(900, 450), "MWS", Style::Titlebar); //���������� ����, ����� ������ � �������� ����
	int clicks = 0; //��� ������ ������ � �����
	int I_istok, I_stok; //������� ����� � ����

	while (window.isOpen()) { //���� ���� �������

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed)
				window.close();
			if (Keyboard::isKeyPressed(Keyboard::Escape)) {  //��������� ���� �� Esc
				window.close();
			}
			if (event.type == event.MouseButtonReleased && event.mouseButton.button == Mouse::Left) { //��������� ������� �� �������
				Node* clicableNode = NULL; //��������� ����������
				for (int i = 0; i < N; ++i) {
					if (MouseOnNode(Nodes->GraphicNodes[i], window) && Nodes->GraphicNodes[i].getFillColor() == Color::Red) {
						Nodes->GraphicNodes[i].setFillColor(Color::Blue);
						clicableNode = &Nodes[i];
						if (clicks == 0) {
							istok.setString("istok: " + to_string(clicableNode->N)); //������� �����
							I_istok = clicableNode->N;
						}else if (clicks == 1) {
							stok.setString("stok: " + to_string(clicableNode->N)); //������� ����
							I_stok = clicableNode->N;
							clicks = -1;

							string s = "Max flow: " + to_string(MOF(I_istok,I_stok,H,T,F,M)); //��������� ���������� ����������� ������
							answer.setString(s);
						}
						++clicks;
					} else if(MouseOnNode(Nodes->GraphicNodes[i], window) && Nodes->GraphicNodes[i].getFillColor() == Color::Blue){ //��������� ������� �� �������� �������
						Nodes->GraphicNodes[i].setFillColor(Color::Red);
						istok.setString("istok: " + to_string(0));
						stok.setString("stok: " + to_string(0));
						answer.setString("Max flow: infinity");
					} else {
						Nodes->GraphicNodes[i].setFillColor(Color::Red);
					}
				}
			}
		}
		//������������ ��

		window.clear(); //������� �����

		for (int i = 0; i < M; i++) { //������������ �����
			window.draw(GraphicLinks[i]);
		}

		for (int i = 0; i < N; i++) { //������������ ����
			window.draw(Nodes->GraphicNodes[i]);
			window.draw(TextNodes[i]);
		}

		window.draw(istok); //������������ �����
		window.draw(stok);
		window.draw(infoText);
		window.draw(answer);

		window.display();
	}

	delete Nodes; //����������� ����������� ���������� ������
	delete Links;

	return 0;
}