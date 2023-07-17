#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int weight;
    int value;
} Item;

double upperBound(int capacity, Item items[], int n, int level, int currentWeight, int currentValue) {
    if (currentWeight >= capacity)
        return 0;

    double remainingCapacity = capacity - currentWeight;
    double upperValue = currentValue;

    int i = level;
    while (i < n && items[i].weight <= remainingCapacity) {
        remainingCapacity -= items[i].weight;
        upperValue += items[i].value;
        i++;
    }

    if (i < n)
        upperValue += (items[i].value / (double)items[i].weight) * remainingCapacity;

    return upperValue;
}

void knapsackBranchBound(int capacity, Item items[], int n, int level, int currentWeight, int currentValue, int *maxValue, int *solution) {
    if (currentWeight > capacity)
        return;

    if (level == n) {
        if (currentValue > *maxValue) {
            *maxValue = currentValue;
            for (int i = 0; i < n; i++)
                solution[i] = items[i].weight;
        }
        return;
    }

    double ub = upperBound(capacity, items, n, level, currentWeight, currentValue);

    if (ub <= *maxValue)
        return;

    knapsackBranchBound(capacity, items, n, level + 1, currentWeight + items[level].weight,
                        currentValue + items[level].value, maxValue, solution);

    knapsackBranchBound(capacity, items, n, level + 1, currentWeight, currentValue, maxValue, solution);
}

int main() {
    int capacity = 50;
    Item items[] = {{10, 60}, {20, 100}, {30, 120}};
    int n = sizeof(items) / sizeof(items[0]);

    int maxValue = 0;
    int solution[n];

    knapsackBranchBound(capacity, items, n, 0, 0, 0, &maxValue, solution);

    printf("Maximum value: %d\n", maxValue);
    printf("Selected items: ");
    for (int i = 0; i < n; i++) {
        if (solution[i] > 0)
            printf("%d ", solution[i]);
    }

    return 0;
}
