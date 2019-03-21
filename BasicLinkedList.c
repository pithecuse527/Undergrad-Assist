#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define _CRT_SECURE_NO_WARNINGS
#define MALLOC(mem, type, size)  if( !(mem = (type*)malloc(size)) ){\
                            fprintf(stderr, "Insufficient memory!");\
                            exit(EXIT_FAILURE);\
                            }
#define EMPTY_LIST(ptr) ((ptr) -> next == NULL ? 1 : 0)
#define RECAL_LIST_SIZE(header, t) ((t) == '+' ? ((header) -> value)++ : ((header) -> value)--)

typedef struct _node *node_ptr;
typedef struct _node {
   int value;
   node_ptr next;
} node;


void addNodeToList(int data, node_ptr header);       // addList를 addNodeToList 이름을 바꿈
void insertNodeToList(int data, int index, node_ptr header);
void delNode(int index, node_ptr header);
int accessToList(int index, node_ptr header);         // 함수의 이름은 항상 문장화 하는걸 권장 (좀 더 가식화)

int main()

{
   node_ptr header;              // header의 주솟값을 절!대! 건들지 말 것!
   MALLOC(header, node, sizeof(node));
   node_ptr tmp = header;        // 5번 메뉴에서 사용할 임시 포인터

   header -> next = NULL;        // Initialize 할 때는 항상 NULL을 가리키게끔 하는걸 권장
   header -> value = 0;

   int select;
   int data;
   int index;
   
   while(TRUE)
   {
      printf("select a choice (1.add 2.inserst 3.delete 4.access 5.printAll 6.exit) : ");
      scanf("%d", &select);

      if(select == 6) break;     // basis level
      
      switch (select)
      {
         case 1:
            printf("type data : ");
            scanf("%d", &data);
            addNodeToList(data, header);
            break;

         case 2:
            if(EMPTY_LIST(header))              // 이보시오...? 거기 누구 없소.....?
            {
               printf("List is empty...\n");
               break;
            }
            printf("type index and data: ");
            scanf("%d %d", &index, &data);
            insertNodeToList(data, index, header);
            break;

         case 3: 
            if(EMPTY_LIST(header))              // 이보시오...? 거기 누구 없소.....?
            {
               printf("List is empty...\n");
               break;
            }
            
            printf("type index : ");
            scanf("%d", &index);
            delNode(index, header);
            break;

         case 4:
            if(EMPTY_LIST(header))              // 이보시오...? 거기 누구 없소.....?
            {
               printf("List is empty...\n");
               break;
            }
            printf("type index: ");
            scanf("%d", &index);
            if(accessToList(index, header) > 0)
               printf("%d's number is %d\n", index, accessToList(index, header));
            break;
            
         case 5:
            if(EMPTY_LIST(header))              // 이보시오...? 거기 누구 없소.....?
            {
               printf("List is empty...\n");
               break;
            }
            
            printf("Stat : ");
            
            tmp = tmp -> next;      // header 노드는 제끼자
            
            while(tmp -> next)
            {
               printf("%d ", tmp -> value);
               if(tmp -> next) printf("-> ");
               tmp = tmp -> next;
            }
            printf("%d", tmp -> value);
            printf("\n");
            
            tmp = header;           // 원래대로...
            break;
            
         default:
         printf("Wrong Access");
      }
      
      printf("\nsize : %d\n", header -> value);
   } // while end
      
   return 0;

}

void addNodeToList(int data, node_ptr header) {
   
// ----------------------이전에 너가 만든 코드---------------------------- //
   // node_ptr new = malloc(sizeof(node));
   // new->value = data;

   // new->next = NULL;

   // header->next = new;
   // header->value++;
   //           ^ 이 코드는 어떤 의도인지 잘 모르겠음 일단 아래와 같이 수정...
   
// -------------------------------------------------- //   
   
   
   node_ptr new_node;         // new는 컴파일러에 따라 c에서 사용하는 사전 정의어임 따라서 new_node로 수정
   MALLOC(new_node, node, sizeof(node));
   
   new_node -> value = data;
   new_node -> next = NULL;
   
   // 먼저 연결리스트의 끝 부분으로 이동해야됨. 생각을 좀 더 쉽게하기 위해 새로운 연결리스트의 포인터를 하나 더 정의 (tmp)
   node_ptr tmp = header;
   
   while(tmp -> next) 
      tmp = tmp -> next;      // 마지막 노드까지 포인터 전진
   
   tmp -> next = new_node;
   
   RECAL_LIST_SIZE(header, '+');
}


void insertNodeToList(int data, int index, node_ptr header)
{
   // ----------------------이전에 너가 만든 코드 ---------------------------- //
   
   // node *new = malloc(sizeof(node));
   // node *temp = malloc(sizeof(node));

   // temp->next = header;

   // for (int i = 1; i < index; i++) {
   //    temp = temp->next;
   // }

   // new->value = data;
   // new->next = temp->next;
   // temp->next = new;

   // free(temp);    
   // ----------------------------------------------------------------------- //
   
   node_ptr new_node;
   MALLOC(new_node, node, sizeof(node));
   
   node_ptr tmp = header;                 // 이 함수의 역할을 알고나니 malloc을 할 필요가 없음을 알게되었다
   
   int i;
   
   if(index == header -> value)        // 인덱스가 연결리스트의 마지막인 경우 addNodeToList함수 호출
   {
      addNodeToList(data, header);
      return;
   }
   
   if(index > header -> value)                                    // 인덱스가 연결리스트의 길이를 초과한 경우
   {
      printf("You typed wrong index...\n");
      return;
   }
   
   for(i = 0; i < index; i++) tmp = tmp -> next;

   new_node -> value = data;
   new_node -> next = tmp -> next;
   tmp -> next = new_node;
   
   RECAL_LIST_SIZE(header, '+');
}

void delNode(int index, node_ptr header)        // 교과서에 나오는 방법은 아님 교과서 방식대로 하는걸 추천
{
   if(index > header -> value)                                    // 인덱스가 연결리스트의 길이를 초과한 경우
   {
      printf("You typed wrong index...\n");
      return;
   }

   node_ptr to_be_deleted_one;          // 삭제할 노드의 포인터
   node_ptr prev = header;              // 삭제할 노드의 이전 노드의 포인터
   
   int i;
   for(i = 0; i < index - 1; i++) prev = prev -> next;       // prev를 기준으로 삭제될 노드의 이전까지 이동
                                                             // 그림을 그려보면서 따라가는 걸 추천
   
   to_be_deleted_one = prev -> next;
   prev -> next = to_be_deleted_one -> next;
   free(to_be_deleted_one);
   
   RECAL_LIST_SIZE(header, '-');
}

int accessToList(int index, node_ptr header)
{
   if(index > header -> value)                      // 인덱스가 연결리스트의 길이를 초과할 경우
   {
      printf("You typed wrong index...\n");
      return -1;
   }
      
   node_ptr tmp = header;

   // for (int i = 0; i < index; i++) {         // C 코딩 할 때 C++ 형식은 비추 (그리고 파일의 확장자도 .c이므로)
   //    tmp = tmp->next;
   // }
   
   int i;
   for (i = 0; i < index; i++)                  // Strict C version
   {
      tmp = tmp -> next;
      
   }
   
   return tmp -> value;
}