#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Point
struct Point
{
    int x, y;
};


// Quad Limits in a Box
struct Box
{
    float x, y, w, h;
    float left, right, top , bottom;

    void setLimits ();
    bool containsPoint(Point* p);
    bool intersects(Box* range);
    Box* subdivide(int quadrant);
};

void Box::setLimits ()
{
    this->left      = this->x - this->w / 2;
    this->right     = this->x + this->w / 2;
    this->top       = this->y - this->h / 2;
    this->bottom    = this->y + this->h / 2;
}
bool Box::containsPoint(Point* p)
{
    setLimits();
    /* cout << "-- p.x = " << p->x << ", p.y = " << p->y << "\n";
    cout << "-- L = " <<this->left << ", R = " <<this->right 
        << ", T = " <<this->top << ", B = " <<this->bottom << "\n";
 */

    if (this->left <= p->x && p->x <= this->right
        && this->top <= p->y && p->y <= this->bottom)
        return true;
    else 
        return false;
}

bool Box::intersects(Box* range)
{
    setLimits();
    if (this->right < range->left || range->right < this->left
        || this->bottom < range->top || range->bottom < this->top)
        return false;
    else
        return true;
}

Box* Box::subdivide(int quadrant)
{
    Box* newBox = new Box;
    switch (quadrant)
    {
    case 1:
        cout << "---- nw "; 
        newBox->x = this->x - this->w/4;
        newBox->y = this->y - this->h/4;
        newBox->w = this->w/2;
        newBox->h = this->h/2;
        cout << "--- "<< newBox->x << ", " << newBox->y << "\n";
        break;
    
    case 2:
        cout << "---- ne ";
        newBox->x = this->x + this->w/4;
        newBox->y = this->y - this->h/4;
        newBox->w = this->w/2;
        newBox->h = this->h/2;
        cout << "--- "<< newBox->x << ", " << newBox->y << "\n";       
        break;
    
    case 3:
        cout << "---- sw ";
        newBox->x = this->x - this->w/4;
        newBox->y = this->y + this->h/4;
        newBox->w = this->w/2;
        newBox->h = this->h/2;
        cout << "--- "<< newBox->x << ", " << newBox->y << "\n";
        break;

    case 4:
        cout << "---- se ";
        newBox->x = this->x + this->w/4;
        newBox->y = this->y + this->h/4;
        newBox->w = this->w/2;
        newBox->h = this->h/2;
        cout << "--- "<< newBox->x << ", " << newBox->y << "\n";
        break;
    }
        
    return newBox;
}

// QuadTreeNode
class QuadTreeNode
{
    public:
        // Data
        int capacity = 1;
        int level;
        Box* boundary = nullptr;
        vector<Point*> points;
        
        // children
        QuadTreeNode* nw = nullptr;
        QuadTreeNode* ne = nullptr;
        QuadTreeNode* sw = nullptr;
        QuadTreeNode* se = nullptr;

        // Methods
        QuadTreeNode(Box* _boundary, int capacity, int level);
        bool isLeaf();
        void subdivide();
        bool insert(Point* p);
        vector<Point*> queryRange(Box* range, vector<Point*> &pointsInRange);
        // vector<int> queryRange(Box* range, vector<int> &pointsInRange);

        void childrenQuad();
};

QuadTreeNode::QuadTreeNode(Box* _boundary, int _capacity, int _level)
{
    this->boundary = _boundary;
    this->capacity = _capacity;
    this->level = _level;
    // points.resize(_capacity);
    // cout <<"-- Points size quadTreeNode = "<< points.size() << "\n";
}

bool QuadTreeNode::isLeaf()
{
    if (this->nw == nullptr)
        return true;
    return false;
}

void QuadTreeNode::subdivide()
{
    this->nw = new QuadTreeNode(this->boundary->subdivide(1), this->capacity, this->level + 1);
    this->ne = new QuadTreeNode(this->boundary->subdivide(2), this->capacity, this->level + 1);
    this->sw = new QuadTreeNode(this->boundary->subdivide(3), this->capacity, this->level + 1);
    this->se = new QuadTreeNode(this->boundary->subdivide(4), this->capacity, this->level + 1);
}

bool QuadTreeNode::insert(Point* p)
{
    cout <<"\n";
    // Ignore objects that do not belong in this quad tree
    if(!this->boundary->containsPoint(p))
    {
        cout <<"-- "<< p << " object cannot be added ";
        cout << " - point size = " << points.size() << "\n";
        return false;                       
    }
    
    // If there is space in this quad tree and if doesn't have subdivisions, 
    // add the object here
    if(points.size() < this->capacity && this->isLeaf())
    {
        points.push_back(p);
        cout << "-- point inserted = " << points[0]  << " - point size = " << points.size() << "\n";
        return true;
    }

    // Otherwise, subdivide 
    // and then add the point to whichever node will accept it
    if(this->isLeaf())
    {
        cout << "--- is Leaf -> subdivide\n";
        subdivide();

        // re insert points of parent node on child
        for (auto point : this->points)
        {
            insert(point);
            point = nullptr;
        }

    }
    
    // We have to add the points/data contained in this quad array to the new quads if we only want
    // the last node to hold the data
    if(this->nw->insert(p)) 
    {
        cout <<"-- inserting on NW"<< "\n";
        return true;
    }
    if(this->ne->insert(p)) 
    {
        cout <<"-- inserting on NE"<< "\n";
        return true;
    }
    if(this->sw->insert(p)) 
    {
        cout <<"-- inserting on SW"<< "\n";
        return true;
    }
    if(this->se->insert(p)) 
    {
        cout <<"-- inserting on SE"<< "\n";
        return true;
    }

    // Otherwise, the point cannot be inserted for some unknown reason (this should never happen)
    return false;
}

/* vector<Point*> QuadTreeNode::queryRange(Box* range, vector<Point*> &pointsInRange)
{   
    if(!(range->intersects(this->boundary)))
    {
        return pointsInRange;
    }
    
    // Check objects at this quad level
    for (auto p : this->points)
    {
        if (range->containsPoint(p))
        {
            cout << p->x << ", " << p->y << "\n";
            pointsInRange.push_back(p);
        }
    }

    // Terminate here, if there are no children
    if (this->isLeaf())
        return pointsInRange;
    else 
    {
        // Otherwise, add the points from the children
        this->nw->queryRange(range, pointsInRange);
        this->ne->queryRange(range, pointsInRange);
        this->sw->queryRange(range, pointsInRange);
        this->se->queryRange(range, pointsInRange);

    }
    return pointsInRange;
} */

vector<Point*> QuadTreeNode::queryRange(Box* range, vector<Point*> &pointsInRange)
 {
    if(!(range->intersects(this->boundary)))
    {
        return pointsInRange;
    }

    // If quad is divided
    if (!(this->isLeaf()))
    {
        this->nw->queryRange(range, pointsInRange);
        this->ne->queryRange(range, pointsInRange);
        this->sw->queryRange(range, pointsInRange);
        this->se->queryRange(range, pointsInRange);
        return pointsInRange;
    }

    
    for (auto p : this->points)
    {
        if(range->containsPoint(p))
        {
            pointsInRange.push_back(p);
        }
    }
    return pointsInRange;
 }

void QuadTreeNode::childrenQuad ()
{
    if(this->isLeaf())
    {
        for(auto point :this->points)
            cout << point->x <<", " << point->y << " ";
    }
    else 
    {
        cout << "NW -> [";
        this->nw->childrenQuad();
        cout << "] ";

        cout << " NE -> [";
        this->ne->childrenQuad();
        cout << "]";
        
        cout << " SW -> [";
        this->sw->childrenQuad();
        cout << "]";
        
        cout << " SE -> [";
        this->se->childrenQuad();
        cout << "]";
        cout << "*";
    }
}