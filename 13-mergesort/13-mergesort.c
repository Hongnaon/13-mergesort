#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100  // 배열 크기 설정

int sortPass = 0;  // mergeSort 실행 횟수 기록
int compareCount = 0;  // 비교 횟수 기록
int dataMoves = 0;  // 데이터 이동 횟수 기록
int totalCompares = 0;  // 총 비교 횟수
int totalDataMoves = 0;  // 총 데이터 이동 횟수
int isFirstRun = 0;  // 첫 실행 여부 확인

// 랜덤 배열 생성
void generateRandomArray(int arr[]) {
    for (int i = 0; i < SIZE; i++) {
        arr[i] = rand() % 1000;  // 0부터 999 사이의 랜덤 값 생성
    }
}

// 배열 출력
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n\n");
}

// 반복적 합병 정렬
void doMergeSort(int arr[]) {
    int temp[SIZE];  // 임시 배열

    for (int width = 1; width < SIZE; width *= 2) {  // 부분 배열의 크기(폭)를 1부터 시작해 2배씩 증가
        for (int i = 0; i < SIZE; i += 2 * width) {  // 배열을 폭 단위로 나누어 정렬
            int left = i;  // 왼쪽 부분 배열의 시작 인덱스
            int mid = i + width < SIZE ? i + width : SIZE;  // 중간 인덱스
            int right = i + 2 * width < SIZE ? i + 2 * width : SIZE;  // 오른쪽 부분 배열의 끝 인덱스

            int l = left, r = mid, k = left;  // 왼쪽, 오른쪽, 임시 배열 인덱스 초기화

            // 두 부분 배열을 비교하며 병합
            while (l < mid && r < right) {
                compareCount++;  // 비교 횟수 증가
                if (arr[l] <= arr[r]) {
                    temp[k++] = arr[l++];  // 왼쪽 값을 임시 배열에 복사
                    dataMoves++;  // 이동 횟수 증가
                }
                else {
                    temp[k++] = arr[r++];  // 오른쪽 값을 임시 배열에 복사
                    dataMoves++;  // 이동 횟수 증가
                }
            }

            // 왼쪽 배열에 남은 요소 복사
            while (l < mid) {
                temp[k++] = arr[l++];
                dataMoves++;
            }

            // 오른쪽 배열에 남은 요소 복사
            while (r < right) {
                temp[k++] = arr[r++];
                dataMoves++;
            }

            // 임시 배열의 정렬된 값을 원래 배열에 복사
            for (int j = left; j < right; j++) {
                arr[j] = temp[j];
                dataMoves++;  // 이동 횟수 증가
            }

            // 중간 상태를 10번마다 출력
            if (sortPass % 10 == 0 && isFirstRun == 0) {
                for (int j = 0; j < 10; j++) {  // 처음 10개의 요소 출력
                    printf("%3d ", arr[j]);
                }
                printf("! ");
                for (int j = SIZE / 2 - 1; j < SIZE / 2 + 10; j++) {  // 중간 10개의 요소 출력
                    printf("%3d ", arr[j]);
                }
                printf("\n\n");
            }
            sortPass++;  // 패스 수 증가
        }
    }
}

int main() {
    int arr[SIZE];  // 정렬할 배열
    srand((unsigned int)time(NULL));  // 랜덤 시드 초기화

    for (int i = 0; i < 20; i++) {  // 20번 반복 실행
        generateRandomArray(arr);  // 무작위 배열 생성
        compareCount = 0;  // 비교 횟수 초기화
        dataMoves = 0;  // 데이터 이동 횟수 초기화

        if (i == 0) {  // 첫 번째 실행일 경우
            printf("Merge Sort Run\n");
            doMergeSort(arr);  // 정렬 실행

            printf("Result\n");
            printArray(arr, SIZE);  // 정렬 결과 출력
            isFirstRun++;  // 첫 실행 여부 업데이트
        }
        else {
            doMergeSort(arr);  // 이후 실행에서는 정렬만 수행
        }

        totalCompares += compareCount;  // 총 비교 횟수 누적
        totalDataMoves += dataMoves;  // 총 이동 횟수 누적
    }

    // 평균 비교 횟수와 평균 이동 횟수 출력
    printf("\nAverage Comparisons: %.2f\n", totalCompares / 20.0);
    printf("Average Moves: %.2f\n", totalDataMoves / 20.0);

    return 0;
}
