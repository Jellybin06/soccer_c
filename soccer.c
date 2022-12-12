#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE 666
#define SWAP(x, y, temp) ((temp)=(x), (x)=(y), (y)=(temp))

struct member{

   char name[40];

   char team[25];

   int point;

   char position[25];

};

typedef struct Node{
    struct member data;
    struct Node* next;
}Node;

Node* createList(){
    Node *node=(Node*)malloc(sizeof(Node));
    node = NULL;

    return node;
}

Node* insert(Node* head, struct member data){
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = head;
    return node;
}
void printAll(Node* head){
    int i=1;
    Node *p = (Node*)malloc(sizeof(Node));
    p=head;
    while(p){
        printf("\t%d위 : %s\n", i,p->data.name);
        p=p->next;
        i++;
    }
}

int partition(struct member m[], int left, int right){
    int pivot;
    struct member temp;
    int low, high;

    low = left;
    high = right+1;
    pivot = m[left].point;

    do{
        do{
            low++;
        } while(low<=right&&m[low].point<pivot);
        do{
            high--;
        }while(high>=left&&m[high].point>pivot);
        if(low<high) SWAP(m[low], m[high], temp);
    }while(low<high);

    SWAP(m[left], m[high], temp);

    return high;
}
void quick_sort(struct member m[], int left, int right){
    if(left<right){
        int q=partition(m, left, right);
        quick_sort(m, left, q-1);
        quick_sort(m, q+1, right);
    }
}
int main()

{

   struct member m[668];

   int i, choice=1;
   int n = MAX_SIZE;

   FILE *f;

   f=fopen("soccer.text","r");


   for(i=0;i<n;i++)

   fscanf(f,"%s %s %d %s",&m[i].name,&m[i].team, &m[i].point, &m[i].position);

   fclose(f);

   quick_sort(m, 0, n-1);

   Node* head;
   Node* p;
   head = createList();
   for(i=0; i<n; i++){
        head = insert(head, m[i]);
        //printf("%s\n", head->data.name);
   }
   //printf("%s", head->data.name);

   while(choice){
    printf("=============== 메인 ===============\n");
    printf("\n\t1. 전체 순위 보기\n\t2. 선수 검색\n\t3. 포지션별 순위\n\t4. 종료\n");
    printf("\n=====================================\n");
    printf("\n번호를 입력 해주세요 >>> ");
    scanf("%d", &choice);


    printf("\n=====================================\n");
    switch(choice){
        case 1:
            printf("\n============= 전체 순위 =============\n\n");
            printAll(head);
            //for(i=0; i<n; i++) printf("%d위 : %s\n", i+1, m[i].name);
            break;
        case 2:{
            printf("\n============= 선수 정보 =============\n\n");
            char search[100];
            int d=1;
            printf("찾을 선수 이름을 입력하세요 >>> ");
            scanf("%s", search);
            strlwr(search);
            for(p=head; p!=NULL; p=p->next){
                if(strcmp(strlwr(p->data.name), search)==0) {
                    printf("\n\n\t이름 : %s\n\t소속팀 : %s\n\t포인트 : %d\n\t포지션 : %s\n\n", p->data.name, p->data.team, p->data.point, p->data.position);
                    d=0;
                }
            }
            if(d) printf("선수 이름 잘못 입력");

            break;
        }
        case 3:{
            printf("\n=========== 포지션별 순위 ===========\n");
            char s2[100];
            int cnt=1;
            printf("\n찾아볼 포지션을 검색하세요 >>> ");
            scanf("%s", s2);
            strlwr(s2);
            printf("\n\n");
            for(p=head; p!=NULL; p=p->next){
                if(strcmp(strlwr(p->data.position), s2)==0) printf("\t%d위 : %s\n", cnt, p->data.name);
                cnt++;
            }
            break;
        }
        case 4:
            printf("\n=====================================\n\n\n\n");
            printf("\t종료되었습니다.\n\n\n");
            choice = 0;
            break;
        default:
            printf("번호를 다시 입력해주세요.");
            break;
    }
    printf("\n=====================================\n\n");
   }

   /*
   for(i=0;i<n;i++){
        printf("%s %s %d %s\n",m[i].name,m[i].team, m[i].point, m[i].position);
   }*/

   return 0;

}
