#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct {
    ElemType *elem;    // 空间基地址，空间存放纸牌正反面状态值,正/反分别用1/0表示
    int length;        // 存放纸牌数
    int listsize;      // 存放空间的容量
} SqList;

void InitList(SqList *L, int n) {
    // 创建大小为 n+1 的连续存储空间，含头指针
    L->elem = (ElemType *)malloc((n + 1) * sizeof(ElemType));
    if (L->elem == NULL) {
        printf("内存分配失败\n");
        exit(1);
    }
    L->length = n;
    L->listsize = n + 1;
    
    // 将 1~n 号空间赋值为 1，表示纸牌正面朝上
    for (int i = 1; i <= n; i++) {
        L->elem[i] = 1;
    }
}

void PlayGame(SqList *L) {
    int n = L->length;
    // 外循环控制翻牌基数，从2开始到n结束
    for (int i = 2; i <= n; i++) {
        // 内循环完成以基数开始，依次对编号为基数倍数的纸牌翻牌，直到最后一张编号为n的牌结束
        for (int j = i; j <= n; j += i) {
            // 翻牌一次的操作：1翻为0，0翻为1
            if (L->elem[j] == 1) {
                L->elem[j] = 0;
            } else {
                L->elem[j] = 1;
            }
        }
    }
}

// 输出正面朝上的所有纸牌编号和纸牌张数
void PrintResult(SqList *L) {
    int count = 0;
    for (int i = 1; i <= L->length; i++) {
        if (L->elem[i] == 1) {
            printf("%d ", i);
            count++;
        }
    }
    printf("\n%d\n", count);
}

int main() {
    SqList cardList;
    int n;           // 纸牌总数
    scanf("%d", &n);
    
    InitList(&cardList, n);
    PlayGame(&cardList);
    PrintResult(&cardList);
    
    // 释放申请的内存
    free(cardList.elem);
    cardList.elem = NULL;
    
    return 0;
}
