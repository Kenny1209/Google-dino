#include <iostream>
#include <Windows.h>
#include <time.h>
#include <iomanip>
#define KEY_DOWN(VK_NONAME) ((GetAsyncKeyState(VK_NONAME) & 0x8000) ? 1:0) 
using namespace std;

char map[7][31] = {"------------------------------",//x=0
				    "..............................",//x=1
                    "..............................",//x=2
                    "..............................",//x=3
                    "..............................",//x=4
                    "------------------------------",//x=5
				   };  //y:0~29 
int y=4, x=4;//λ��������� 

int main(){
	
	int jump = 0, time_b;//������Ծ 
	int obs = 10;//�ϰ���֮��ľ���
	bool alive = true;//�ж����� 
	int clocktime = clock();//����ˢ�� 
	int fps;//�������fps 

	
	while (alive){
	
		//�ж����� 
		if (KEY_DOWN('W')){
			if (jump == 0){//���� 
				time_b = clock();
				jump = 1;
			} if (jump == 1){//��Ծ�� 
				if (clock() - time_b <= 200){
					x = 3;
				} else if (clock() - time_b >= 200){
					x = 2;
				}
				if (clock() - time_b >= 1000){
					jump = 2;
					time_b = clock();
				}
			}
		} else {
			if (jump == 1){
				jump = 2;
				time_b = clock();
			}
		} 
		if (jump == 2){//���� 
			if (clock() - time_b <= 100){
				x = 3;
			} else if (clock() - time_b >= 100){
				x = 4;
			}
			if (clock() - time_b >= 200){
				jump = 0;
			}
		}
						
		if (clock() - clocktime >= 50){
			fps = 1000 / (clock() - clocktime);
			clocktime = clock();
			//���Ƴ���
			for (int o=3; o<=4; o++){
				for (int p=0; p<=28; p++){
				map[o][p] = map[o][p+1];
				}
			} 
			
			//�����ϰ��� 
			if (obs){
				obs -= 1;
				map[3][29] = '.';
				map[4][29] = '.';
			} else {//��obs=0ʱ 
				srand(clock());//�������������
				int num = rand()%3;
				if (num == 0){
					map[4][29] = '|';
					obs = 10 + rand()%5;
				} else if (num == 1){
					map[3][29] = '|';
					map[4][29] = '.';
					obs = 7 + rand()%5;
				} else if (num == 2){
					map[3][29] = '|';
					map[4][29] = '|';
					obs = 13 + rand()%7;
				}
			}	
			//�������
			system("cls");
			for(int i=0;i<=6;i++){
				for(int j=0;j<=30;j++){
					if(i==x&&j==y){
						cout<<"@";
					}else{
						cout<<map[i][j];
					}			
				}
				cout<<endl;
			}cout << "score:" << setw(5) << setfill('0') << int(clock() / 100)<<endl;
			 cout << "fps:" << fps;	
				
			//�ж�����
			if (map[x][y] == '|'){
				alive = false;
			}
		}
	}
	Sleep(1000);	
}

