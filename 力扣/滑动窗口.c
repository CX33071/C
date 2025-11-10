//
int minSubArrayLen(int target, int* nums, int numsSize) {
    int result = INT32_MAX;
    int i = 0;
    int length = 0;
    int sum = 0;
    for (int j = 0; j < numsSize; j++) {
        sum += nums[j];
        while (sum >= target) {
            length = (j - i + 1);
            result = result > length ? length : result;
            sum -= nums[i];
            i++;
        }
    }
    return result == INT32_MAX ? 0 : result;
}
//
int maxVowels(char* s, int k) {
    int count = 0;
    int num = 0;
    int result = 0;
    int a = strlen(s);
    for (int j = 0; j < a; j++) {
        if (s[j] == 'a' || s[j] == 'e' || s[j] == 'i' || s[j] == 'o' ||
            s[j] == 'u') {
            count++;
        }
        int left = j - k + 1;
        if (left < 0) {
            continue;
        }
        result = result < count ? count : result;
        if (s[left] == 'a' || s[left] == 'e' || s[left] == 'i' ||
            s[left] == 'o' || s[left] == 'u') {
            count--;
        }
    }
    return result;
}
//
double findMaxAverage(int* nums, int numsSize, int k) {
    double sum = 0;
    double aver;
    for (int i = 0; i < k; i++) {
        sum += nums[i];
    }
    double max = sum;
    for (int i = k; i < numsSize; i++) {
        sum = sum - nums[i - k] + nums[i];
        max = max < sum ? sum : max;
    }
    aver = max / k;
    return aver;
}
//
int numOfSubarrays(int* arr, int arrSize, int k, int threshold) {
    int count = 0;
    double sum = 0;
    double aver = 0;
    for (int i = 0; i < k; i++) {
        sum += arr[i];
        aver = sum / k;
    }
    if (aver >= threshold) {
        count++;
    }
    for (int i = k; i < arrSize; i++) {
        sum = sum - arr[i - k] + arr[i];
        aver = sum / k;
        if (aver >= threshold) {
            count++;
        }
    }
    return count;
}
//
/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* getAverages(int* nums, int numsSize, int k, int* returnSize) {
    *returnSize = numsSize;
    int* avgs = (int*)malloc(sizeof(int) * numsSize);
    for (int i = 0; i < numsSize; i++) {
        avgs[i] = -1;
    }
    if ((2 * k + 1) > numsSize) {
        return avgs;
    }
    long long sum = 0;
    for (int i = 0; i < 2 * k + 1; i++) {
        sum += nums[i];
    }
    avgs[k] = sum / (2 * k + 1);
    for (int j = k + 1; j <= numsSize - k - 1; j++) {
        sum = sum - nums[j - k - 1] + nums[j + k];
        avgs[j] = sum / (2 * k + 1);
    }
    return avgs;
}
//
int minimumRecolors(char* blocks, int k) {
    int count = 0;
    int firstcount = 0;
    for (int i = 0; i < k; i++) {
        if (blocks[i] == 'W') {
            count++;
        }
    }
    firstcount = count;
    int a = strlen(blocks);
    for (int j = k; j < a; j++) {
        if (blocks[j] == 'W') {
            count++;
        }
        if (blocks[j - k] == 'W') {
            count--;
        }
        firstcount = firstcount < count ? firstcount : count;
    }
    return firstcount;
}
