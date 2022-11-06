#include <iostream>
#include "quadTreeNode.h"
using namespace std;

int main()
{
    Point t = {4, 6};
    Point b = {6, 5};
    Point d = {0, 3};
    Point ch = {2, 3};
    Point o = {2, 2};
    Point mo = {4, 0};
    Point a = {6, 1};
    Point mi = {7, 0};
   
    Box initBox = {4, 4, 8, 8};
    // cout << initBox.x << ", " << initBox.y << ", "
    //     << initBox.w << ", " << initBox.h << "\n";

    QuadTreeNode qt(&initBox, 1, 0);
    // cout << &initBox << " == " << qt.boundary << "\n";

    qt.insert(&t);
    qt.insert(&b);
    qt.insert(&d);
    qt.insert(&ch);
    qt.insert(&o);
    qt.insert(&mo);
    qt.insert(&a);
    qt.insert(&mi);
    
    qt.childrenQuad();
    cout <<"\n";

    Box range = {3, 2, 6, 4};
    vector<Point*> result;

    qt.queryRange(&range, result);

    // imprimiendo resultaodo
    if(result.size() > 0)
    {
        for(auto r : result)
            cout << r->x << ","<< r->y << " - ";
        cout<<"\n";

    }

    return 0;
}