#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;
// 8!=40320    
const int Max_state = 40325;
const int factorial[8] = {1,1,2,6,24,120,720,5040};
const char init_str[9] = "12348765";
int state[Max_state]; // 维护所有状态回到初始的次数

struct Cube{
    int pre; // 上一状态
    int _contor_num;  // Hash
    char state_str[9];
    void Contor();
}cube[2*Max_state],obj;

// 共有2*4!+1*3!+2*2!+0*1!+0*0!=58个比3 2 5 1 4更小的排列，因此它的序号是59。
// 比如1是固定第一位为3，还有1个数比2小，也就是和第二位之后的比较
void Cube::Contor(){
    int contor_num = 0;
    for(int i=0; i<8; i++){
        int bigger = 0;
        for(int j=i+1; j<8; j++){
            if(this->state_str[i]>this->state_str[j]){
                ++bigger;
            }
        }
        contor_num+=bigger*factorial[7-i];
        bigger=0;
    }
    this->_contor_num = contor_num;
}

// 执行三种操作
// 初始状态的
void operate(){
    int cur = 0;
    int tail = 1;
    strcpy(cube[0].state_str, init_str);
    cube[0].Contor();
    while(cur<tail){
        if(state[cube[cur]._contor_num]){
            cur++;
            continue;
        }
        state[cube[cur]._contor_num] = state[cube[cube[cur].pre]._contor_num] + 1;
        
        // Exchange the upper and lower lines
        for(int i=0; i<8; i++){
            cube[tail].state_str[(i+4)%8] = cube[cur].state_str[i];
        }
        cube[tail].Contor();
        if(!state[cube[tail]._contor_num]){
            cube[tail].pre=cur;
            tail++;
        }

        // Loop (not right)-->left! shift
        for(int i=0; i<4; i++){
            cube[tail].state_str[i] = cube[cur].state_str[(i+1)%4];
            cube[tail].state_str[i+4] = cube[cur].state_str[(i+4+1)%4+4];
        }
        cube[tail].Contor();
        if(!state[cube[tail]._contor_num]){
            cube[tail].pre=cur;
            tail++;
        }

        // The center rotates counterclockwise not clockwise.
        // 2->1, 6->2, 1->5, 5->6
        strcpy(cube[tail].state_str, cube[cur].state_str);
        cube[tail].state_str[1] = cube[cur].state_str[2];
        cube[tail].state_str[2] = cube[cur].state_str[6];
        cube[tail].state_str[5] = cube[cur].state_str[1];
        cube[tail].state_str[6] = cube[cur].state_str[5];
        cube[tail].Contor();
        if(!state[cube[tail]._contor_num]){
            cube[tail].pre=cur;
            tail++;
        }
        cur++;
    }
}


int main()
{
    operate();
	int n;
	scanf("%d",&n);
    // cout<<"*";
    while(n--){
        int input_str;
        for(int i=0; i<4; i++){
            scanf("%d",&input_str);
            obj.state_str[i] = input_str+'0';
        }
        // cout<<"**";
        for(int i=0; i<4; i++){
             scanf("%d",&input_str);
            obj.state_str[7-i] = input_str+'0';
        }
        // cout<<"***";
        obj.Contor();
        printf("%d\n", state[obj._contor_num] - 1);
    }
	return 0;
} 

/*Input

2
1 2 3 4 5 6 7 8
8 6 3 5 4 2 7 1
Output

0
2*/



