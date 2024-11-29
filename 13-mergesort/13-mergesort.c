#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100  // �迭 ũ�� ����

int sortPass = 0;  // mergeSort ���� Ƚ�� ���
int compareCount = 0;  // �� Ƚ�� ���
int dataMoves = 0;  // ������ �̵� Ƚ�� ���
int totalCompares = 0;  // �� �� Ƚ��
int totalDataMoves = 0;  // �� ������ �̵� Ƚ��
int isFirstRun = 0;  // ù ���� ���� Ȯ��

// ���� �迭 ����
void generateRandomArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000;  // 0���� 999 ������ ���� �� ����
    }
}

// �迭 ���
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

// �ݺ��� �պ� ����
void doMergeSort(int arr[]) {
    int temp[SIZE];  // �ӽ� �迭

    for (int width = 1; width < SIZE; width *= 2) {  // �κ� �迭�� ũ��(��)�� 1���� ������ 2�辿 ����
        for (int i = 0; i < SIZE; i += 2 * width) {  // �迭�� �� ������ ������ ����
            int left = i;  // ���� �κ� �迭�� ���� �ε���
            int mid = i + width < SIZE ? i + width : SIZE;  // �߰� �ε���
            int right = i + 2 * width < SIZE ? i + 2 * width : SIZE;  // ������ �κ� �迭�� �� �ε���

            int l = left, r = mid, k = left;  // ����, ������, �ӽ� �迭 �ε��� �ʱ�ȭ

            // �� �κ� �迭�� ���ϸ� ����
            while (l < mid && r < right) {
                compareCount++;  // �� Ƚ�� ����
                if (arr[l] <= arr[r]) {
                    temp[k++] = arr[l++];  // ���� ���� �ӽ� �迭�� ����
                    dataMoves++;  // �̵� Ƚ�� ����
                }
                else {
                    temp[k++] = arr[r++];  // ������ ���� �ӽ� �迭�� ����
                    dataMoves++;  // �̵� Ƚ�� ����
                }
            }

            // ���� �迭�� ���� ��� ����
            while (l < mid) {
                temp[k++] = arr[l++];
                dataMoves++;
            }

            // ������ �迭�� ���� ��� ����
            while (r < right) {
                temp[k++] = arr[r++];
                dataMoves++;
            }

            // �ӽ� �迭�� ���ĵ� ���� ���� �迭�� ����
            for (int j = left; j < right; j++) {
                arr[j] = temp[j];
                dataMoves++;  // �̵� Ƚ�� ����
            }

            // �߰� ���¸� 10������ ���
            if (sortPass % 10 == 0 && isFirstRun == 0) {
                for (int j = 0; j < 10; j++) {  // ó�� 10���� ��� ���
                    printf("%3d ", arr[j]);
                }
                printf("! ");
                for (int j = SIZE / 2 - 1; j < SIZE / 2 + 10; j++) {  // �߰� 10���� ��� ���
                    printf("%3d ", arr[j]);
                }
                printf("\n\n");
            }
            sortPass++;  // �н� �� ����
        }
    }
}

int main() {
    int arr[SIZE];  // ������ �迭
    srand((unsigned int)time(NULL));  // ���� �õ� �ʱ�ȭ

    for (int i = 0; i < 20; i++) {  // 20�� �ݺ� ����
        generateRandomArray(arr);  // ������ �迭 ����
        compareCount = 0;  // �� Ƚ�� �ʱ�ȭ
        dataMoves = 0;  // ������ �̵� Ƚ�� �ʱ�ȭ

        if (i == 0) {  // ù ��° ������ ���
            printf("Merge Sort Run\n");
            doMergeSort(arr);  // ���� ����

            printf("Result\n");
            printArray(arr, SIZE);  // ���� ��� ���
            isFirstRun++;  // ù ���� ���� ������Ʈ
        }
        else {
            doMergeSort(arr);  // ���� ���࿡���� ���ĸ� ����
        }

        totalCompares += compareCount;  // �� �� Ƚ�� ����
        totalDataMoves += dataMoves;  // �� �̵� Ƚ�� ����
    }

    // ��� �� Ƚ���� ��� �̵� Ƚ�� ���
    printf("\nAverage Comparisons: %.2f\n", totalCompares / 20.0);
    printf("Average Moves: %.2f\n", totalDataMoves / 20.0);

    return 0;
}
