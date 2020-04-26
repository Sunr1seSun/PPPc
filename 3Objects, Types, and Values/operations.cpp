#include "std_lib_facilities.h"

int main()
{
    int count;
    cin >> count;
    string name;
    cin >> name;
    int c2 = count + 2;
    string s2 = name + " Jr.";
    int c3 = count -2;
    // error: - isn't defined for strings
    // string s3 = s2 - " Jr.";

    cout << "Please enter a floating-point value: ";
    int n;
    cin >> n;
    cout << "n == " << n << "\nn+1 == " << n + 1 \
    << "\nthree times n == " << 3 * n \
    << "\ntwice n ==" << n + n \
    << "\nn squard == " << n * n \
    << "\nhalf of n == " << n / 2 \
    << "\nsquare root of n ==" << sqrt(n) << endl;
}