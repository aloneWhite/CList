#include <stdio.h>
#include <stdlib.h>
#include "clist.h"

static void free_val(void* val)
{
	free(val);
}

static void dump(clist_t* list)
{
	int count, i;
	int* p = NULL;

	count = clist_count(list);
	for(i = 0; i < count; i++) {
		p = clist_find(list, i);
		if(p) {
			printf("%d  ", *p);
		}
	}

	printf("\n");
}

int main(int argc, const char** argv)
{
	int* a[10] = {0};
	int i, ret = 0;
	clist_t* list = NULL;
	int* p = NULL;

	for(i = 0; i < 10; i++) {
		a[i] = calloc(1, sizeof(int));
		*(a[i]) = i;
	}

	// lpush
	list = clist_new(free_val);
	for(i = 0; i < sizeof(a) / sizeof(int*); i++) {
		ret = clist_rpush(list, a[i]);
		if(ret) {
			printf("lpush error : %d\n", ret);
			break;
		}
		dump(list);
	}

	// rpop
	for(i = 0; i < sizeof(a) / sizeof(int*); i++) {
		//printf("lpop : %d\n", *((int*)clist_lpop(list)));
		p = clist_rpop(list);
		free_val(p);
		dump(list);
	}

	clist_free(list);

	return 0;
}
