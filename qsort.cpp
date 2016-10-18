#include <cstdio>

// Returns pivot index
void qsort(int A[], int left, int right)
{
    int l = left;
    int r = right;
    int m = (right+left)/2;

    while (l <= r)
    {
        while (A[l] < A[m])
            l++;

        while (A[r] > A[m])
            r--;

        if (l <= r)
        {
            int tmp = A[l];
            A[l] = A[r];
            A[r] = tmp;
            ++l;
            --r;
        }
    }

    if (left < r)
        qsort(A, left, r);

    if (l < right)
        qsort(A, l, right);
}

int main()
{
    int A[] {11, 2, 9, 2, 8, 3, 7, 4, 6, 5};

    int n = sizeof A / sizeof *A;

    qsort(A, 0, n);

    for (int i = 0; i < n; i++)
        ::printf("%d ", A[i]);
}
