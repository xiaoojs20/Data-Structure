#include<iostream>
#include<cstdio>

class MyStack{
public:
    int size;
    int capacity; //m
    int trainNum; //n
    int* elem;
    int* ops;
    int nextTrain; // 1~n, 代入列火车的编号 
    int opTimes; // 目前的push pop 总次数, opTimes <=20;
    MyStack(){}
    MyStack(int trainNum,int capacity):capacity(capacity),trainNum(trainNum),
    size(0),nextTrain(1),opTimes(0){
        elem = new int[capacity];
        // ops = new int[capacity<<1]; // 原先写错了导致越界..
        ops = new int[trainNum<<1]; 
    }
    bool empty(){
        return size == 0;
    }
    int push(int newTrain){ // A -> S
        // stack is full or A is empty, return -1
        if(size == capacity || opTimes == trainNum<<1 || newTrain == 0) return -1; 
        elem[size] = newTrain;
        size++;
        ops[opTimes] = 1;
        opTimes++;
        if(newTrain == trainNum)
            nextTrain = 0;
        else    
            nextTrain++;   
        // std::cout<<"push:"<<newTrain<<std::endl;
        return 0;
    }
    int pop(){  // S -> B
        if(size == 0 || opTimes == trainNum<<1) return -1;
        int del = elem[size-1];
        size--;
        ops[opTimes] = 0;
        opTimes++;
        // std::cout<<"pop:"<<del<<std::endl;
        return del;    
    }
    int top(){
        if(size == 0) return -1;
        else return elem[size-1];
    }
    // 如果此时栈顶不是所要的，但是火车已经都进完了，就不能再push了，否则会错误
    int check(int nowTrain){
        if(nextTrain <= trainNum){
            if(size == 0){
                push(nextTrain);
            }
            while(top()!=nowTrain){
                if(nextTrain == 0) return -1;
                if(push(nextTrain)==-1) return -1; // stack is full
            }
            pop(); // 弹出栈顶, check数量+1
        }
        return 0;
    }
    
    void print(){
        for(int i = 0; i < trainNum<<1; i++){
            if(ops[i]==1)
                printf("push\n");
            else
                printf("pop\n");
        }
    }
};

int main(){
    int n, m;
    int nTrain; // 下一个要出栈的火车
    scanf("%d%d",&n, &m);
    MyStack trainStack(n, m);
    for(int i = 0; i < n; i++){
        scanf("%d",&nTrain);
        // printf("%d\n",nTrain);
        // int checkT = trainStack.check(nTrain);
        if(trainStack.check(nTrain) == -1){
            printf("No\n");
            return 0;
        }
    }
    trainStack.print();
    return 0;
}

// 8个就报错???
/*8 2
2 1 3 4 5 6 8 7*/

/*10 3
2 1 3 4 5 6 8 9 7 10
*/
