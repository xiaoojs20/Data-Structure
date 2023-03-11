#include<cstdio>
#include<cstring>
#include<iostream>
using namespace std;

const int MAX = 10000010;
struct Node{
    int duplicate = 0;
    char name[50];
    Node* next;
};

struct Table{
    Node* NodeList;
};

Table table[9000];

int tableSize = 8737;
int Hash(char *key){
    long hash = 0;
    while(*key !='\0')
        hash += 7*(*key)+(*key++)/7;
    return hash%tableSize;
}

int main(){
    int n;
    scanf("%d", &n);
	// getchar();
	char s[50];
	int i, j;
	int flag = 0;
	while (n--){
		scanf("%s", s);
		flag = 0;
		int hash = Hash(s);
        // cout<<"hash: "<<hash<<endl;
		Node *obj = new Node;
		obj = table[hash].NodeList;
		while (obj){
            // cout<<"s: "<<s<<endl;
            // cout<<"a->name: "<<a->name<<endl;
			if (!strcmp(obj->name, s)){
				flag = 1;
				if (obj->duplicate == 0){
					printf("%s\n", s);
					obj->duplicate = 1;
					break;
				}
			}
			obj = obj->next;
		}
		if (flag) continue;
		Node *p = new Node;
		strcpy(p->name, s);
		p->next = table[hash].NodeList;
		table[hash].NodeList = p;
	}
}

/*Input
 
10
brioche
camembert
cappelletti
savarin
cheddar
cappelletti
tortellni
croissant
brioche
mapotoufu
Output

cappelletti
brioche*/
