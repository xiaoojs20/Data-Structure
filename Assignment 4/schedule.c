#pragma warning(disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define DOUBLE(n) (n<<1)
#define HALF(n) (n>>1)
#define TOP(heap) heap[1]

const long long MAX_PRIORITY = 1LL << 32;

typedef struct Task {
	long long priority;
	char name[8];
} Task;

typedef struct Task* PTask;

typedef struct Heap {
	PTask *tasks;   //position 0 is useless, start from 1
	int size;
	int capacity;
} Heap;

inline void swap_task(PTask *t1, PTask *t2) {
	PTask t = *t1;
	*t1 = *t2;
	*t2 = t;
}

Heap* new_heap(int capacity) {
	Heap *heap = malloc(sizeof(Heap));
	heap->size = 0;
	heap->capacity = capacity + 1;
	heap->tasks = malloc(sizeof(PTask) * heap->capacity);
	return heap;
}

void delete_heap(Heap* heap) {
	free(heap->tasks);
	free(heap);
}

inline int compare_task(PTask task1, PTask task2) {
	if (task1->priority != task2->priority) {
		return (task1->priority > task2->priority)?1:-1;
	}   else {
		return strcmp(task1->name, task2->name);
	}
}

void build_heap(Heap *heap) {
	PTask *tasks = heap->tasks;
	for (int i = HALF(heap->size); i >= 1; --i) {
		int min = DOUBLE(i);  //left child
		if (min < heap->size && compare_task(tasks[min + 1], tasks[min]) < 0) {
			++min;
		}
		if (compare_task(tasks[min], tasks[i]) < 0) {
			swap_task(&tasks[min], &tasks[i]);
		}
	}
}

PTask extract_min(Heap *heap) {
	if (heap->size == 0) return NULL;
	PTask *tasks = heap->tasks;
	PTask min = tasks[1];
	if (DOUBLE(min->priority) < MAX_PRIORITY) {
		min->priority = DOUBLE(min->priority);
	}
	else {
		tasks[1] = tasks[heap->size];
		heap->size--;
	}

	int cur = 1, child = DOUBLE(cur);
	PTask t = tasks[1];
	while (child <= heap->size) {
		if (child < heap->size && compare_task(tasks[child + 1], tasks[child]) < 0) {
			++child;
		}
		if (compare_task(tasks[child], t) >= 0) {
			break;
		}
		tasks[cur] = tasks[child];
		cur = child;
		child = DOUBLE(cur);
	}
	tasks[cur] = t;
	return min;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	Task* gtasks = malloc(sizeof(Task) * n);
	Heap*  gheap = new_heap(n);

	int i;
	for (i = 0; i < n; i++) {
		scanf("%lld %s", &gtasks[i].priority, gtasks[i].name);
		if (gtasks[i].priority < MAX_PRIORITY) {
			gheap->tasks[++gheap->size] = &gtasks[i];
		}
	}
	build_heap(gheap);

	for (i = 1; i <= m; i++) {
		PTask task = extract_min(gheap);
		if (!task) break;
		printf("%s\n", task->name);
	}
	return 0;
}