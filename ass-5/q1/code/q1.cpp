#include <stdio.h>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

using namespace std;

int main()
{
    double time = 0.0;
    clock_t starting = clock();

    map<int, int> poly1;
    vector<int> a;
    cout << "Enter no. of terms in expression 1 : ";
    int n1;
    cin >> n1;
    cout << "Coefficient\tExponent " << endl;
    while (n1--)
    {
        int expo, coeff;
        cin >> coeff >> expo;
        poly1.insert(pair<int, int>(expo, coeff));
        a.push_back(coeff);
    }
    int n2;
    cout << "Enter no. of terms in expression 2 : ";
    cin >> n2;

    map<int, int> poly2;
    vector<int> b;
    cout << "Coefficient\tExponent " << endl;
    while (n2--)
    {
        int expo, coeff;
        cin >> coeff >> expo;
        poly2.insert(pair<int, int>(expo, coeff));
        b.push_back(coeff);
    }

    int m = 1;
    while (m == 1 || m == 2)
    {
        cout << "Enter 1 to add or 2 for multiply , else any other integer to exit.\n";
        cin >> m;
        if (m == 1)
        {
            map<int, int>::iterator itr;
            map<int, int> poly3;
            poly3 = poly1;
            for (auto const &item : poly2)
            {
                poly3[item.first] += item.second;
            }

            cout << "\tCOEFF\tEXPO\n";
            itr = poly3.end();
            itr = --itr;

            for (itr; itr != poly3.begin(); --itr)
            {
                cout << '\t' << itr->second;
                cout << '\t' << itr->first << '\n';
            }
            itr = itr++;
            cout << '\t' << itr->second;
            cout << '\t' << itr->first << '\n';
            cout << endl;
        }

        // make polynomial coefs vector
        if (m == 2)
        {
            int A = 1;
            const int as = a.size();
            int ap = 1;
            for (int ai = 0; ai < as; ++ai)
            {
                a[ai] *= ap;
                ap *= A;
            }

            //vector<int> b = {1,1,5,2};
            const int bs = b.size();

            // result vector
            vector<int> c(as + bs - 1, 0);

            // multiply vectors
            for (int ai = 0; ai < as; ++ai)
                for (int bi = 0; bi < bs; ++bi)
                {
                    c[ai + bi] += a[ai] * b[bi];
                }
            cout << "\tCOEFF\tEXPO\n";
            for (int i = 0; i < c.size(); i++)
            {
                cout << "\t" << c[i] << ' ';
                cout << "\t" << c.size() - 1 - i << " " << endl;
            }
        }
    }

    clock_t ending = clock();
    time += (double)(ending - starting) / CLOCKS_PER_SEC;
    printf("\nTotal Execution time is : %f (sec)\n", time);

    return 0;
}
