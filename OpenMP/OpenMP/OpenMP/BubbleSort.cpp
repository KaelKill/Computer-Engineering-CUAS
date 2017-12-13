////sort data Bubble Sort sequential
//
//#include <stdio.h>
//#include <Windows.h>
//#include <omp.h>
//
//#define maxData 50000
//
//void sort_data(int[]);
//
//void main() {
//	int data[maxData];
//	DWORD start, end;
//	for (int index = 0; index < maxData; index++) {
//		data[index] = rand();
//	}
//	
//	//for (int index = 0; index < maxData; index++)
//	//	printf("%d ", data[index]);
//	printf("\n");
//	start = GetTickCount();
//	sort_data(data);
//	end = GetTickCount();
//
//	//for (int index = 0; index < maxData; index++)
//	//	printf("%d ", data[index]);
//
//	printf("\nElapsed time: %d\n", end - start);
//	system("pause");
//}
//
//
//void sort_data(int data[]) {
//
//#pragma omp parallel for schedule(guided), shared(data)
//	for (int i = 0; i < maxData; i++) {
//		for (int j = 0; j < maxData - 1; j++) {
//			if (data[j] > data[j + 1]) {
//				int help = data[j];
//				data[j] = data[j + 1];
//				data[j + 1] = help;
//			}
//		}
//	}
//}
//
///* 
//Without multhreading = ~9250
//Parallel for schedule(guided), shared(data) on i  2640 
//Parallel for schedule(guided), shared(data) on j  3547
//Parallel for on for( i ) = 2531~2609
//Parallel For on for( j ) = 3938~4016 
//*/