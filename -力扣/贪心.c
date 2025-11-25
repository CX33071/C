int compare(const void* a, const void* b) {
    return *(int*)b - *(int*)a;
}
int minimumBoxes(int* apple, int appleSize, int* capacity, int capacitySize) {
    qsort(capacity, capacitySize, sizeof(int), compare);
    int sum = 0;
    for (int i = 0; i < appleSize; i++) {
        sum += apple[i];
    }
    int count = 0;
    int i = 0;
    while (sum > 0) {
        sum -= capacity[i];
        count++;
        i++;
    }

    return count;
}
//
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
int minDeletion(char* s, int k) {
    int len = strlen(s);
    int arr[26];
    memset(arr, 0, sizeof(int));
    for (int i = 0; i < len; i++) {
        int idx = s[i] - 'a';
        arr[idx]++;
    }
    int count = 0;
    for (int i = 0; i < 26; i++) {
        if (arr[i] != 0) {
            count++;
        }
    }
    qsort(arr, 26, sizeof(int), compare);
    int mincount = 0;
    int i = 0;
    int deletecount = 0;
    while (deletecount < count - k && i < 26) {
        if (arr[i] != 0) {
            deletecount++;
            mincount += arr[i];
        }
        i++;
    }
    return mincount;
}
//
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
int maximumBags(int* capacity,
                int capacitySize,
                int* rocks,
                int rocksSize,
                int additionalRocks) {
    int* rest = (int*)malloc(capacitySize * sizeof(int));
    for (int i = 0; i < capacitySize; i++) {
        rest[i] = capacity[i] - rocks[i];
    }
    int count = 0;
    int i = 0;
    qsort(rest, capacitySize, sizeof(int), compare);
    for (int i = 0; i < capacitySize; i++) {
        if (additionalRocks < rest[i]) {
            break;
        }
        additionalRocks -= rest[i];
        count++;
        if (additionalRocks == 0) {
            break;
        }
    }
    free(rest);
    return count;
}
//
int compare(const void* a, const void* b) {
    return *(int*)a - *(int*)b;
}
int maxIceCream(int* costs, int costsSize, int coins) {
    int count = 0;
    qsort(costs, costsSize, sizeof(int), compare);
    for (int i = 0; i < costsSize; i++) {
        if (coins < costs[i]) {
            break;
        }
        coins -= costs[i];
        count++;
        if (coins == 0) {
            break;
        }
    }
    return count;
}