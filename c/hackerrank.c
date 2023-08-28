#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct triangle
{
	int a;
	int b;
	int c;
};

typedef struct triangle triangle;

typedef struct lt {
	double **size;
	triangle **tr;
}lt;

void print_lt(lt *l, int sz) {
	int i = -1;
	double *size = *l->size;
	while (++i < sz) {
		printf("%d\n", size[i]);
	}
}

void swap_tr(lt* list, int pos, int dest) {
	double *size = *list->size;
	int tmp = size[pos];
	size[pos] = size[dest];
	size[dest] = tmp;

	triangle* tr = *list->tr;
	triangle t_tmp = tr[pos];
	tr[pos] = tr[dest];
	tr[dest] = t_tmp;
}

static void	selection_sort(lt *arr, int sz)
{
	int	i;
	int	j;
	int	min;
	double *size = *arr->size;

	i = 0;
	while (i < sz - 1)
	{
		min = i;
		j = i + 1;
		while (j < sz)
		{
			if (size[j] < size[min])
				min = j;
			j++;
		}
		swap_tr(arr, min, i);
		//swap(&arr[min], &arr[i]);
		i++;
	}
}

void sort_by_area(triangle* tr, int n) {
	lt *indexes = malloc(n * sizeof(lt));
	double *size = malloc(n * sizeof(double));
	indexes->tr = &tr;
	indexes->size = &size;
	int i = 0;

	while (i < n)
	{
		triangle t = tr[i];
		int p = (t.a + t.b + t.c) / 2;
		double r = sqrt(p * (p - t.a) * (p - t.b) * (p - t.c));
		size[i] = r;
		i++;
	}
	swap_tr(indexes, 0, 2);
	free(indexes);
	free(size);
}


int main()
{
	int n;
	scanf("%d", &n);
	triangle *tr = malloc(n * sizeof(triangle));
	for (int i = 0; i < n; i++) {
		scanf("%d%d%d", &tr[i].a, &tr[i].b, &tr[i].c);
	}
	sort_by_area(tr, n);
	for (int i = 0; i < n; i++) {
		printf("%d %d %d\n", tr[i].a, tr[i].b, tr[i].c);
	}
	return 0;
}
