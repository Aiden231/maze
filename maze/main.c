#include <stdio.h>
#define MAX_STACK_SIZE 100
#define MAZE_SIZE 10

typedef struct {
	short r;
	short c;
}element;

typedef struct {
	element data[MAX_STACK_SIZE];
	int top;
}StackType;

// ���� �ʱ�ȭ
void init_stack(StackType* s)
{
	s->top = -1;
}

// ���� ���� �˻�
int is_empty(StackType* s)
{
	return (s->top == -1);
}

// ��ȭ ���� �˻�
int is_full(StackType* s)
{
	return(s->top == (MAX_STACK_SIZE - 1));
}

// �����Լ�
void push(StackType* s, element item)
{
	if (is_full(s)) {
		fprintf(stderr, "���� ��ȭ ����\n");
		return;
	}
	else {
		s->top++;
		s->data[s->top] = item;
		return;
	}
}

//�����Լ�
element pop(StackType* s)
{
	if (is_empty(s)) {
		fprintf(stderr, "���� ���� ����\n");
		return;
	}

	else return s->data[(s->top--)];
}

// ��ũ�Լ�
element peek(StackType* s)
{
	return s->data[s->top];
}

// ���� ��ġ �� ������ ����
element here = { 1,0 }, entry = { 1,0 };

char maze[MAZE_SIZE][MAZE_SIZE] = {

		{'1','1','1','1','1','1','1','1','1','1'},

		{'e','1','0','1','0','0','0','1','0','1'},

		{'0','0','0','1','0','0','0','1','0','1'},

		{'0','1','0','0','0','1','1','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','1','0','0','0','0','1'},

		{'1','0','0','0','0','0','1','0','1','1'},

		{'1','0','1','1','1','0','1','1','0','1'},

		{'1','1','0','0','0','0','0','0','0','x'},

		{'1','1','1','1','1','1','1','1','1','1'}
};

// �̷� ��ã�� �Լ�
void push_loc(StackType* s, int r, int c)
{
	if (r < 0 || c < 0)	return;

	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element tmp;
		tmp.r = r;
		tmp.c = c;
		push(s, tmp);
	}
}

// �̷� ��� �Լ�
void maze_print(char maze[MAZE_SIZE][MAZE_SIZE])
{
	printf("\n");
	for (int r = 0; r < MAZE_SIZE; r++) {
		for (int c = 0; c < MAZE_SIZE; c++) {
			printf("%c", maze[r][c]);
		}
		printf("\n");
	}
}

int main()
{
	int r, c;
	int count = 0;
	StackType s;

	init_stack(&s);
	here = entry;

	while (maze[here.r][here.c] != 'x') {
		r = here.r;
		c = here.c;

		maze[r][c] = '.';
		maze_print(maze);

		push_loc(&s, r, c - 1); // left
		push_loc(&s, r - 1, c); // up
		push_loc(&s, r + 1, c); // down
		push_loc(&s, r, c + 1); // right

		if (is_empty(&s)) {
			printf("Fail\n");
			return;
		}
		else
			here = pop(&s);

		// ���ƿ� Ƚ�� ����
		if ((maze[r - 1][c] == '1' || maze[r - 1][c] == '.') &&
			(maze[r + 1][c] == '1' || maze[r + 1][c] == '.') &&
			(maze[r][c - 1] == '1' || maze[r][c - 1] == '.') &&
			(maze[r][c + 1] == '1' || maze[r][c + 1] == '.'))
		{
			count++;
		}
	}

	printf("Success\n");
	printf("���ư� Ƚ�� : %d\n", count);

	return;
}