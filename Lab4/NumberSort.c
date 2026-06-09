#include <stdio.h>
#include <stdlib.h>

/******************* 排序 *******************/
void sortJumbled(int *mapping, int *nums, int numsSize) {
    int *res_nums = (int *)malloc(numsSize * sizeof(int));
    // TODO

    
    for(int i = 0; i < numsSize; i++)
        printf("%d ", res_nums[i]);
    printf("\n");
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