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
//
int maximumUniqueSubarray(int* nums, int numsSize) {
    int* arr = (int*)calloc(100001, sizeof(int));
    int maxscore = 0;
    int left = 0;
    int score = 0;
    for (int right = 0; right < numsSize; right++) {
        arr[nums[right]]++;
        score += nums[right];
        while (arr[nums[right]] > 1) {
            score -= nums[left];
            arr[nums[left]]--;
            left++;
        }
        maxscore = maxscore > score ? maxscore : score;
    }
    return maxscore;
}
//
int maxSubarrayLength(int* nums, int numsSize, int k) {
    int maxlength = 0;
    int length = 0;
    long long* arr = (long long*)calloc(1000000001, sizeof(long long));
    int left = 0;
    for (int right = 0; right < numsSize; right++) {
        arr[nums[right]]++;
        while (arr[nums[right]] > k) {
            arr[nums[left]]--;
            left++;
        }
        length = right - left + 1;
        maxlength = maxlength > length ? maxlength : length;
    }
    return maxlength;
}
//
int maxConsecutiveAnswers(char* answerKey, int k) {
    int a = strlen(answerKey);
    int count1 = 0;
    int count2 = 0;
    int maxcount = 0;
    int maxcount1 = 0;
    int len1 = 0;
    int len2 = 0;
    int maxcount2 = 0;
    int left1 = 0;
    int left2 = 0;
    for (int right = 0; right < a; right++) {
        if (answerKey[right] != 'T') {
            count1++;
        }
        while (count1 > k) {
            if (answerKey[left1] == 'F') {
                count1--;
            }
            left1++;
        }
        len1 = right - left1 + 1;
        maxcount1 = maxcount1 > len1 ? maxcount1 : len1;

        if (answerKey[right] != 'F') {
            count2++;
        }
        while (count2 > k) {
            if (answerKey[left2] == 'T') {
                count2--;
            }
            left2++;
        }
        len2 = right - left2 + 1;
        maxcount2 = maxcount2 > len2 ? maxcount2 : len2;
        maxcount = maxcount1 > maxcount2 ? maxcount1 : maxcount2;
    }
    return maxcount;
}
//
int longestOnes(int* nums, int numsSize, int k) {
    int count = 0;
    int maxlength = 0;
    int length = 0;
    int left = 0;
    for (int right = 0; right < numsSize; right++) {
        if (nums[right] == 0) {
            count++;
        }
        while (count > k) {
            if (nums[left] == 0) {
                count--;
            }
            left++;
        }
        length = right - left + 1;
        maxlength = maxlength > length ? maxlength : length;
    }
    return maxlength;
}
//
int longestSemiRepetitiveSubstring(char* s) {
    int length = 0;
    int maxlength = 0;
    int left = 0;
    int count = 0;
    int a = strlen(s);
    if (a == 1) {
        return 1;
    }
    for (int right = 1; right < a; right++) {
        if (s[right] == s[right - 1]) {
            count++;
        }
        while (count > 1) {
            if (s[left] == s[left + 1]) {
                count--;
            }
            left++;
        }
        length = right - left + 1;
        maxlength = maxlength > length ? maxlength : length;
    }
    return maxlength;
}
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
int balancedString(char* s) {
    int length = 0;
    int minlength = 100001;
    int left = 0;
    int a = strlen(s);
    int b = a / 4;
    int* arr = (int*)calloc(101, sizeof(int));
    for (int i = 0; i < a; i++) {
        arr[s[i]]++;
    }
    while (arr['Q'] == b && arr['W'] == b && arr['E'] == b && arr['R'] == b) {
        return 0;
    }
    for (int right = 0; right < a; right++) {
        arr[s[right]]--;
        while (arr['Q'] <= b && arr['W'] <= b && arr['E'] <= b &&
               arr['R'] <= b) {
            length = right - left + 1;
            minlength = minlength < length ? minlength : length;
            arr[s[left]]++;
            left++;
        }
    }
    free(arr);
    return minlength;
}