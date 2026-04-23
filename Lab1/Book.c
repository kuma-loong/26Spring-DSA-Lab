#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义图书信息结构体
typedef struct {
    char bookId[20]; // 书号
    char title[100]; // 书名
    char author[50]; // 作者
    int stock;       // 库存数量
} Book;

// 定义链表节点结构体
typedef struct Node {
    Book book;
    struct Node *next;
} Node;

// 创建新节点
Node* CreateNode(Book book) {
    Node *newnode = (Node*)malloc(sizeof(Node));
    if (newnode != NULL) {
        newnode->book = book;
        newnode->next = NULL;
    }
    return newnode;
}


// 在链表尾部插入图书信息
void InsertBook(Node **head, Book book) {
    Node *newNode = CreateNode(book);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *current = *head;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    
}

// 根据书号删除图书信息
int DeleteBook(Node **head, char bookId[]) {
    if (head == NULL || *head == NULL) {
        return 0; // 链表为空
    }

    Node *current = *head;
    Node *prev = NULL;

    // 如果要删除的是头节点
    if (strcmp(current->book.bookId, bookId) == 0) {
        *head = current->next;
        printf("图书%s删除成功!\n", bookId);
        free(current);
        return 1;
    }

    // 查找要删除的节点
    while (current != NULL && strcmp(current->book.bookId, bookId) != 0) {
        prev = current;
        current = current->next;
    }

    // 没找到该节点
    if (current == NULL) {
        return 0;
    }

    // 删除节点并释放内存
    prev->next = current->next;
    printf("图书%s删除成功!\n", bookId);
    free(current);
    return 1;
}

// 根据书号查找图书信息
Node* FindBook(Node *head, char bookId[]) {
    Node *current = head;
    while (current != NULL) {
        if (strcmp(current->book.bookId, bookId) == 0) {
            return current; // 找到了，返回节点指针
        }
        current = current->next;
    }
    return NULL; // 没找到
}

// 根据书号修改图书库存数量
int UpdateStock(Node *head, char bookId[], int newStock) {
    Node *target = FindBook(head, bookId);
    if (target != NULL) {
        target->book.stock = newStock;
        printf("图书%s的库存数量已修改为%d!\n", bookId, newStock);
        return 1;    
    } 
    return 0;
}

// 遍历并输出所有图书信息
void TraverseList(Node *head) {
    if (head == NULL) {
        printf("图书列表为空!\n");
        return;
    }
    Node *current = head;
    printf("图书列表:\n");
    while(current != NULL) {
        printf("书号:%s,书名:%s,作者:%s,库存:%d\n", 
               current->book.bookId, current->book.title, 
               current->book.author, current->book.stock);
        current = current->next;
    }
}

// 主函数
int main() {
    Node *head = NULL; // 链表头节点
    char bookId_find[4], bookId_update[4], bookId_delete[4];
    int num;
    scanf("%s", bookId_find);
    scanf("%s", bookId_update);
    scanf("%d", &num);
    scanf("%s", bookId_delete);

    // 添加图书信息
    Book book1 = {"001", "C程序设计", "谭浩强", 10};
    Book book2 = {"002", "数据结构", "严蔚敏", 5};
    Book book3 = {"003", "算法导论", "Thomas H. Cormen", 3};
    InsertBook(&head, book1);
    InsertBook(&head, book2);
    InsertBook(&head, book3);

    // 查找图书信息
    Node *foundBook = FindBook(head, bookId_find);
    if (foundBook != NULL) {
        printf("查找的图书信息:\n");
        printf("书号:%s,书名:%s,作者:%s,库存:%d\n", 
               foundBook->book.bookId, foundBook->book.title, 
               foundBook->book.author, foundBook->book.stock);
    }

    // 修改图书库存数量
    UpdateStock(head, bookId_update, num);

    // 删除图书信息
    DeleteBook(&head, bookId_delete);

    // 遍历输出图书列表
    TraverseList(head);

    return 0;
}