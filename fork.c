#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	int	arr[] = {1, 9, 2};
	int	arrs;
	int	fd1[2];
	int	fd2[2];
	int	start;
	int	end;

	arrs = sizeof(arr) / sizeof(int);
	printf("%d\n", arrs);
	pipe(fd1);
	
	int	id1;

	id1 = fork();
	if (id1 == 0)
	{
		pipe(fd2);
		int	id2;
		id2 = fork();
		if (id2 == 0)
		{
			close(fd2[0]);
			int sum_child_child;
			sum_child_child = 0;
			start = 0;
			end = arrs / 3;
			while (start < end)
			{
				sum_child_child += arr[start];
				start++;
			}
			printf("Sum in child_child : %d\n", sum_child_child);
			write(fd2[1], &sum_child_child, sizeof(int));
			close(fd2[1]);
		}
		else
		{
			close(fd2[1]);
			close(fd1[0]);
			int	tmp_sum;
			int	sum_child;
			sum_child = 0;
			start = arrs / 3;
			end = start * 2;
			while (start < end)
			{
				sum_child += arr[start];
				start++;
			}
			printf("Sum in parent-child : %d\n", sum_child);
			read(fd2[0], &tmp_sum, sizeof(int));
			close(fd2[0]);
			sum_child += tmp_sum;
			write(fd1[1], &sum_child, sizeof(int));
			close(fd1[1]);
			wait(0);
		}
	}
	else
	{
		close(fd1[1]);
		int	sum;
		int	sum_of_child;
		sum = 0;
		start = (arrs / 3) * 2;
		end = arrs;
		while (start < end)
		{
			sum += arr[start];
			start++;
		}
		printf("Sum in parent : %d\n", sum);
		read(fd1[0], &sum_of_child, sizeof(int));
		close(fd1[0]);
		sum += sum_of_child;
		printf("Sum is : %d\n", sum);
		wait(0);
	}
	return (0);
}
