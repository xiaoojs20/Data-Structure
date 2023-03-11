#include<iostream>
#include<cstdio>

class ListNode{
public:
    int id;
    ListNode* pred;
    ListNode* succ;

    ListNode(){}
    ListNode(int id): id(id), pred(this), succ(this){}
    // 双向列表，初始化时前后节点应该都为自己
};
class List{
public:
    int size;
    ListNode* last;
    List(){last = nullptr;}
    ListNode* insertAsSucc(ListNode *nowNode, int id){
        ListNode* newNode = new ListNode(id);
        newNode->pred = nowNode;
        newNode->succ = nowNode->succ;
        nowNode->succ->pred = newNode;
        nowNode->succ = newNode;
        return newNode;
    }
    void insert(int m, int id){
        if(last == nullptr){
            ListNode* first = new ListNode(id);
            last = first;
        }
        else{
            ListNode* lastm = last;
            for(int i = 1; i < m; i++){
               lastm = lastm->succ;
            }
            last = insertAsSucc(lastm, id); // after insert, newNode is last.
        }
    }
    void print(){
        ListNode* node = last;
		do
		{
			printf("%d ",node->id);
			node = node->pred;
		}
        while (node != last);

    }
};

int main(){
    int n, m;
    int id;
    List myList;
	scanf("%d%d",&n,&m);
	for (int i = 0; i < n; i++)
	{
		scanf("%d",&id);
		myList.insert(m,id);
	}
	myList.print();
    return 0;
}

/*input
3 2
8 9 10

output
10 8 9*/
