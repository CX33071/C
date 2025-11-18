int search(int* nums, int numsSize, int target) {
    int left = 0;
    int middle = 0;
    int right = numsSize - 1;
    while (left <= right) {
        middle = (right + left) / 2;
        if (nums[middle] > target) {
            right = middle - 1;
        } else if (nums[middle] < target) {
            left = middle + 1;
        } else {
            return middle;
        }
    }
    return -1;
}
//
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
    *returnSize = 2;
    int left = 0;
    int right = numsSize - 1;
    int* arr = (int*)malloc(2 * sizeof(int));
    arr[0] = -1;
    arr[1] = -1;
    while (left <= right) {
        int middle = (left + right) / 2;
        if (nums[middle] > target) {
            right = middle - 1;
        } else if (nums[middle] < target) {
            left = middle + 1;
        } else {
            arr[0] = middle;
            right = middle - 1;
        }
    }
    right = numsSize - 1;
    left = 0;
    while (left <= right) {
        int middle = (right + left) / 2;
        if (nums[middle] > target) {
            right = middle - 1;
        } else if (nums[middle] < target) {
            left = middle + 1;
        } else {
            arr[1] = middle;
            left = middle + 1;
        }
    }
    return arr;
}
//
int searchInsert(int* nums, int numsSize, int target) {
    int left = 0;
    int right = numsSize - 1;
    int middle;
    while (left <= right) {
        middle = (left + right) / 2;
        if (nums[middle] < target) {
            left = middle + 1;
        } else if (nums[middle] > target) {
            right = middle - 1;
        } else {
            return middle;
        }
    }
    return left;
}
//
int maximumCount(int* nums, int numsSize) {
    int pos = 0;
    int neg = 0;
    for (int i = 0; i < numsSize; i++) {
        if (nums[i] > 0) {
            pos++;
        } else if (nums[i] < 0) {
            neg++;
        }
    }
    return pos > neg ? pos : neg;
}
//
char nextGreatestLetter(char* letters, int lettersSize, char target) {
    for (int i = 0; i < lettersSize; i++) {
        if (letters[i] > target) {
            return letters[i];
        }
    }
    return letters[0];
}
//
typedef struct {
    int stackintop;
    int stackouttop;
    int stackin[100];
    int stackout[100];
} MyQueue;

MyQueue* myQueueCreate() {
    MyQueue* deque = (MyQueue*)malloc(sizeof(MyQueue));
    deque->stackintop = 0;
    deque->stackouttop = 0;
    return deque;
}

void myQueuePush(MyQueue* obj, int x) {
    obj->stackin[(obj->stackintop)++] = x;
}

int myQueuePop(MyQueue* obj) {
    int stackintop = obj->stackintop;
    int stackouttop = obj->stackouttop;
    if (stackouttop == 0) {
        while (stackintop > 0) {
            obj->stackout[(stackouttop)++] = obj->stackin[--(stackintop)];
        }
    }
    int top = obj->stackout[--stackouttop];
    while (stackouttop > 0) {
        obj->stackin[(stackintop)++] = obj->stackout[--(stackouttop)];
    }
    obj->stackintop = stackintop;
    obj->stackouttop = stackouttop;
    return top;
}

int myQueuePeek(MyQueue* obj) {
    return obj->stackin[0];
}

bool myQueueEmpty(MyQueue* obj) {
    return (obj->stackintop == 0) && (obj->stackouttop == 0);
}

void myQueueFree(MyQueue* obj) {
    obj->stackintop = 0;
    obj->stackouttop = 0;
}
//
int nomatch(char par, char* stack, int stacktop) {
    switch (par) {
        case ']':
            return stack[stacktop - 1] != '[';
        case '}':
            return stack[stacktop - 1] != '{';
        case ')':
            return stack[stacktop - 1] != '(';
    }
    return 0;
}
bool isValid(char* s) {
    int a = strlen(s);
    char stack[10000];
    int stacktop = 0;
    for (int i = 0; i < a; i++) {
        char par = s[i];
        if (par == '(' || par == '[' || par == '{') {
            stack[stacktop++] = par;
        } else if (stacktop == 0 || nomatch(par, stack, stacktop)) {
            return 0;
        } else {
            stacktop--;
        }
    }
    return !stacktop;
}
//
char* removeDuplicates(char* s) {
    int a = strlen(s);
    char* stack = (char*)malloc(a * sizeof(char) + 1);
    int stacktop = 0;
    int i = 0;
    while (i < a) {
        char par = s[i];
        i++;
        if (stacktop > 0 && par == stack[stacktop - 1]) {
            stacktop--;
        } else {
            stack[stacktop++] = par;
        }
    }
    stack[stacktop] = '\0';
    return stack;
}
//
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
int* successfulPairs(int* spells,
                     int spellsSize,
                     int* potions,
                     int potionsSize,
                     long long success,
                     int* returnSize) {
    qsort(potions, potionsSize, sizeof(int), compare);
    *returnSize = spellsSize;
    int* pairs = (int*)malloc(spellsSize * sizeof(int));

    for (int i = 0; i < spellsSize; i++) {
        int left = 0;
        int right = potionsSize - 1;
        long long s = spells[i];
        long long target = (success + s - 1) / s;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (target > potions[middle]) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
        pairs[i] = potionsSize - left;
    }
    return pairs;
}
//
int findTheDistanceValue(int* arr1,
                         int arr1Size,
                         int* arr2,
                         int arr2Size,
                         int d) {
    int compare(const void* a, const void* b) {
        return *(int*)a - *(int*)b;
    }
    qsort(arr2, arr2Size, sizeof(int), compare);
    int count = 0;
    for (int i = 0; i < arr1Size; i++) {
        int x = arr1[i];
        int left = x - d;
        int right = x + d;
        int left1 = 0;
        int right1 = arr2Size - 1;
        bool exist = false;
        while (left1 <= right1) {
            int middle = left1 + (right1 - left1) / 2;
            int y = arr2[middle];

            if (y >= left && y <= right) {
                exist = true;
                break;
            } else if (y < left) {
                left1 = middle + 1;
            } else {
                right1 = middle - 1;
            }
        }
        if (!exist) {
            count++;
        }
    }
    return count;
}
//
typedef struct {
    int* nums;
    int* prefix;
    int size;
} NumArray;

NumArray* numArrayCreate(int* nums, int numsSize) {
    NumArray* obj = (NumArray*)malloc(sizeof(NumArray));
    obj->size = numsSize;
    obj->nums = (int*)malloc(sizeof(int) * numsSize);
    obj->prefix = (int*)malloc(sizeof(int) * (numsSize + 1));
    obj->prefix[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        obj->nums[i] = nums[i];
    }
    for (int i = 0; i < numsSize; i++) {
        obj->prefix[i + 1] = obj->prefix[i] + obj->nums[i];
    }
    return obj;
}

int numArraySumRange(NumArray* obj, int left, int right) {
    return obj->prefix[right + 1] - obj->prefix[left];
}

void numArrayFree(NumArray* obj) {
    free(obj->prefix);
    free(obj);
}

//
int max(int a, int b) {
    return a > b ? a : b;
}
int subarraySum(int* nums, int numsSize) {
    int* prefix = (int*)malloc(sizeof(int) * (numsSize + 1));
    prefix[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    int* result = (int*)malloc(sizeof(int) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        int start = max(0, i - nums[i]);
        result[i] = prefix[i + 1] - prefix[start];
    }
    int sum = 0;
    for (int i = 0; i < numsSize; i++) {
        sum += result[i];
    }
    free(prefix);
    free(result);
    return sum;
}
//
bool zifuchuan(char c) {
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}
int* vowelStrings(char** words,
                  int wordsSize,
                  int** queries,
                  int queriesSize,
                  int* queriesColSize,
                  int* returnSize) {
    *returnSize = queriesSize;
    int* result = (int*)malloc(sizeof(int) * queriesSize);
    int* mark = (int*)malloc(sizeof(int) * wordsSize);
    for (int i = 0; i < wordsSize; i++) {
        int a = strlen(words[i]);
        if (zifuchuan(words[i][0]) && zifuchuan(words[i][a - 1])) {
            mark[i] = 1;
        } else {
            mark[i] = 0;
        }
    }
    int* prefix = (int*)malloc(sizeof(int) * (wordsSize + 1));
    prefix[0] = 0;
    for (int i = 0; i < wordsSize; i++) {
        prefix[i + 1] = prefix[i] + mark[i];
    }
    for (int i = 0; i < queriesSize; i++) {
        result[i] = prefix[queries[i][1] + 1] - prefix[queries[i][0]];
    }
    free(prefix);
    free(mark);
    return result;
}
//
bool isjiou(int a, int b) {
    if (a % 2 != b % 2) {
        return true;
    } else {
        return false;
    }
}
bool* isArraySpecial(int* nums,
                     int numsSize,
                     int** queries,
                     int queriesSize,
                     int* queriesColSize,
                     int* returnSize) {
    *returnSize = queriesSize;
    bool* answer = (bool*)malloc(sizeof(bool) * queriesSize);
    int* mark = (int*)malloc(sizeof(int) * (numsSize - 1));
    for (int i = 0; i < numsSize - 1; i++) {
        if (isjiou(nums[i], nums[i + 1])) {
            mark[i] = 1;
        } else {
            mark[i] = 0;
        }
    }
    int* prefix = (int*)malloc(sizeof(int) * (numsSize + 1));
    prefix[0] = 0;
    for (int i = 0; i < numsSize - 1; i++) {
        prefix[i + 1] = prefix[i] + mark[i];
    }
    for (int i = 0; i < queriesSize; i++) {
        int need = queries[i][1] - queries[i][0];
        int shiji = prefix[queries[i][1]] - prefix[queries[i][0]];
        answer[i] = (need == shiji);
    }
    free(mark);
    free(prefix);
    return answer;
}
//
int maxAbsoluteSum(int* nums, int numsSize) {
    long long prefix = 0;
    long long max = 0;
    long long min = 0;
    for (int i = 0; i < numsSize; i++) {
        prefix += nums[i];
        max = prefix > max ? prefix : max;
        min = prefix < min ? prefix : min;
    }
    return llabs(max - min);
}
//
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
int* answerQueries(int* nums,
                   int numsSize,
                   int* queries,
                   int queriesSize,
                   int* returnSize) {
    qsort(nums, numsSize, sizeof(int), compare);
    *returnSize = queriesSize;
    int* answer = (int*)malloc(queriesSize * sizeof(int));
    int* prefix = (int*)malloc((numsSize + 1) * sizeof(int));
    prefix[0] = 0;
    for (int i = 0; i < numsSize; i++) {
        prefix[i + 1] = prefix[i] + nums[i];
    }
    for (int i = 0; i < queriesSize; i++) {
        int left = 0;
        int right = numsSize;
        while (left <= right) {
            int middle = left + (right - left) / 2;
            if (prefix[middle] <= queries[i]) {
                left = middle + 1;
            } else {
                right = middle - 1;
            }
        }
        answer[i] = left - 1;
    }
    free(prefix);
    return answer;
}
//
int maxSubArray(int* nums, int numsSize) {
    int max = INT_MIN;
    int left = 0;
    int current = 0;
    for (int right = 0; right < numsSize; right++) {
        current += nums[right];
        max = current > max ? current : max;
        while (current < 0 && left <= right) {
            current -= nums[left];
            left++;
        }
    }
    return max;
}
//
int countOdds(int low, int high) {
    int count = 0;
    for (int i = low; i <= high; i++) {
        if (i % 2 != 0) {
            count++;
        }
    }
    return count;
}
//
int findMaxK(int* nums, int numsSize) {
    int k = 0;
    int num;
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            if (-nums[i] == nums[j]) {
                num = nums[i] > 0 ? nums[i] : nums[j];
                k = num > k ? num : k;
            }
        }
    }
    return k == 0 ? -1 : k;
}
//
int numIdenticalPairs(int* nums, int numsSize) {
    int count = 0;
    for (int i = 0; i < numsSize; i++) {
        for (int j = 0; j < numsSize; j++) {
            if (nums[i] == nums[j] && i < j) {
                count++;
            }
        }
    }
    return count;
}