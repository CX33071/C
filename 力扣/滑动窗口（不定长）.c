// long long maxSum(int* nums, int numsSize, int m, int k) {
long long sum = 0;
long long maxsum = 0;
long long count = 0;
int* arr = (int*)calloc(1000000001, sizeof(int));
if (arr == NULL) {
    return 0;
}
for (int i = 0; i < k; i++) {
    sum += nums[i];
    if (arr[nums[i]] == 0) {
        count++;
    }
    arr[nums[i]]++;
}
if (count >= m) {
    maxsum = sum;
}
for (int i = k; i < numsSize; i++) {
    int left = i - k;
    arr[nums[left]]--;
    if (arr[nums[left]] == 0) {
        count--;
    }
    if (arr[nums[i]] == 0) {
        count++;
    }
    arr[nums[i]]++;
    sum = sum + nums[i] - nums[left];
    if (count >= m) {
        maxsum = maxsum > sum ? maxsum : sum;
    }
}
free(arr);
return maxsum;
}
//
long long maximumSubarraySum(int* nums, int numsSize, int k) {
    long long sum = 0;
    long long maxsum = 0;
    long long count = 0;
    int* arr = (int*)calloc(100001, sizeof(int));
    for (int i = 0; i < k; i++) {
        sum += nums[i];
        if (arr[nums[i]] == 0) {
            count++;
        }
        arr[nums[i]]++;
    }
    if (count == k) {
        maxsum = sum;
    }
    for (int i = k; i < numsSize; i++) {
        int left = i - k;
        arr[nums[left]]--;
        if (arr[nums[left]] == 0) {
            count--;
        }
        if (arr[nums[i]] == 0) {
            count++;
        }
        arr[nums[i]]++;
        sum = sum - nums[left] + nums[i];
        if (count == k) {
            maxsum = maxsum > sum ? maxsum : sum;
        }
    }
    free(arr);
    return maxsum;
}
//
int lengthOfLongestSubstring(char* s) {
    int a = strlen(s);
    int* lastposition = (int*)malloc(128 * sizeof(int));
    memset(lastposition, -1, 128 * sizeof(int));
    int maxlength = 0;
    int length = 0;
    int left = 0;
    for (int right = 0; right < a; right++) {
        char c = s[right];
        if (lastposition[c] != -1 && lastposition[c] >= left) {
            left = lastposition[c] + 1;
        }
        lastposition[c] = right;
        int nowlength = right - left + 1;
        maxlength = maxlength > nowlength ? maxlength : nowlength;
    }
    free(lastposition);
    return maxlength;
}
//
int maximumLengthSubstring(char* s) {
    int a = strlen(s);
    int left = 0;
    int length = 0;
    int maxlength = 0;
    int* count = (int*)calloc(128, sizeof(int));
    for (int right = 0; right < a; right++) {
        count[s[right]]++;
        while (count[s[right]] > 2) {
            count[s[left]]--;
            left++;
        }
        length = right - left + 1;
        maxlength = maxlength > length ? maxlength : length;
    }
    return maxlength;
}
//
int longestSubarray(int* nums, int numsSize) {
    int count = 0;
    int left = 0;
    int length = 0;
    int maxlength = 0;
    for (int right = 0; right < numsSize; right++) {
        if (nums[right] == 0) {
            count++;
        }
        while (count > 1) {
            if (nums[left] == 0) {
                count--;
            }
            left++;
        }
        length = right - left;
        maxlength = maxlength > length ? maxlength : length;
    }
    return maxlength;
}
//
int lengthOfLongestSubstring(char* s) {
    int a = strlen(s);
    int* lastposition = (int*)malloc(128 * sizeof(int));
    memset(lastposition, -1, 128 * sizeof(int));
    int maxlength = 0;
    int length = 0;
    int left = 0;
    for (int right = 0; right < a; right++) {
        char c = s[right];
        if (lastposition[c] != -1 && lastposition[c] >= left) {
            left = lastposition[c] + 1;
        }
        lastposition[c] = right;
        int nowlength = right - left + 1;
        maxlength = maxlength > nowlength ? maxlength : nowlength;
    }
    free(lastposition);
    return maxlength;
}
//
int minRemoval(int* nums, int numsSize, int k) {
    if (numsSize == 1) {
        return 0;
    }
    int compare(const void* a, const void* b) {
        return *(int*)a - *(int*)b;
    }
    qsort(nums, numsSize, sizeof(int), compare);
    int length = 0;
    int maxlength = 1;
    int left = 0;
    for (int right = 0; right < numsSize; right++) {
        while ((long long)nums[right] > (long long)nums[left] * k) {
            left++;
        }
        length = right - left + 1;
        maxlength = maxlength > length ? maxlength : length;
    }
    return numsSize - maxlength;
}
//
int equalSubstring(char* s, char* t, int maxCost) {
    int a = strlen(s);
    int maxlength = 0;
    int length = 0;
    int left = 0;
    int sum = 0;
    for (int right = 0; right < a; right++) {
        sum += abs(s[right] - t[right]);
        while (sum > maxCost) {
            sum = sum - abs(s[left] - t[left]);
            left++;
        }
        length = right - left + 1;
        maxlength = maxlength > length ? maxlength : length;
    }
    return maxlength;
}
//
int totalFruit(int* fruits, int fruitsSize) {
    int maxcount = 0;
    int* arr = (int*)calloc(100001, sizeof(int));
    int currentcount = 0;
    int left = 0;
    int type = 0;
    for (int right = 0; right < fruitsSize; right++) {
        if (arr[fruits[right]] == 0) {
            type++;
        }
        arr[fruits[right]]++;
        currentcount++;
        while (type > 2) {
            arr[fruits[left]]--;
            currentcount--;
            if (arr[fruits[left]] == 0) {
                type--;
            }
            left++;
        }
        maxcount = maxcount > currentcount ? maxcount : currentcount;
    }
    free(arr);
    return maxcount;
}