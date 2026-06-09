#include <stdio.h>
#include <stdlib.h>

/******************* 排序 *******************/
typedef struct {
    int value;
    long long mapped;
    int index;
} Item;

long long mappedValue(int *mapping, int num) {
    if (num == 0) {
        return mapping[0];
    }

    long long base = 1;
    long long result = 0;
    while (num > 0) {
        result += (long long)mapping[num % 10] * base;
        base *= 10;
        num /= 10;
    }
    return result;
}

int cmpItem(const void *a, const void *b) {
    const Item *x = (const Item*)a;
    const Item *y = (const Item*)b;

    if (x->mapped < y->mapped) {
        return -1;
    }
    if (x->mapped > y->mapped) {
        return 1;
    }
    return x->index - y->index;
}

void sortJumbled(int *mapping, int *nums, int numsSize) {
    int *res_nums = (int *)malloc(numsSize * sizeof(int));
    Item *items = (Item *)malloc(numsSize * sizeof(Item));

    for (int i = 0; i < numsSize; i++) {
        items[i].value = nums[i];
        items[i].mapped = mappedValue(mapping, nums[i]);
        items[i].index = i;
    }

    qsort(items, numsSize, sizeof(Item), cmpItem);

    for (int i = 0; i < numsSize; i++) {
        res_nums[i] = items[i].value;
    }
    
    for(int i = 0; i < numsSize; i++)
        printf("%d ", res_nums[i]);
    printf("\n");

    free(items);
    free(res_nums);
}
/*****************************************************/

/******************* 读取数据 *******************/
void readInput(int **mapping, int **nums, int *numsSize) {
    scanf("%d", numsSize);

    *mapping = (int *)malloc(10 * sizeof(int));
    for (int i = 0; i < 10; i++) {
        scanf("%d", &((*mapping)[i]));
    }

    *nums = (int *)malloc((*numsSize) * sizeof(int));
    for (int i = 0; i < *numsSize; i++) {
        scanf("%d", &((*nums)[i]));
    }
}
/*****************************************************/

int main() {
    int *mapping, *nums, numsSize;
    readInput(&mapping, &nums, &numsSize);
    sortJumbled(mapping, nums, numsSize);

    return 0;
}
