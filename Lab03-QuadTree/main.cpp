#include <iostream>
#include "quadTreeNode.h"
using namespace std;

int main()
{
    Point p1 = {10,10};
    Point p2 = {200, 150};
    cout << p2.x << ", " << p2.y << "\n";
   
    Box b0 = {400, 300, 800, 600};
    // cout << b0.x << ", " << b0.y << ", "
    //     << b0.w << ", " << b0.h << "\n";

    QuadTreeNode qt(&b0, 1, 0);
    // cout << &b0 << " == " << qt.boundary << "\n";

    qt.insert(&p1);
    qt.insert(&p2);
    
    qt.childrenQuad();
    cout <<"\n";

    Box range = {200, 150, 400, 300};
    vector<Point*> result;
    qt.queryRange(&range, result);

    // for(auto r : result)
    //     cout << r->x << ", " << r->y;
    cout<<"\n";

    return 0;
}