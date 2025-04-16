#include <iostream>
using namespace std;
int main(void)
{
    int n;
    cin >> n;
    for (int i{0}; i < n; ++i)
    {
        double d;
        int a;
        cin >> d >> a;

        switch (a)
        {
        case 1:
            printf("%.1f\n", d);
            break;
        case 2:
            printf("%.2f\n", d);
            break;
        case 3:
            printf("%.3f\n", d);
            break;
        case 4:
            printf("%.4f\n", d);
            break;
        }
    }

    return 0;
}