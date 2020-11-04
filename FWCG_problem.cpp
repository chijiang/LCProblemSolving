#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Action
{
    public:
    Action(string direction, string carrage)
    {
        this -> direction = direction;
        this -> carrage = carrage;
    }

    public:
    string direction;
    string carrage;
    Action *next;
    bool isLeaf{false};

    public:
    string to_string()
    {
        string str {"F "};
        if (carrage.size() != 0)
            str += "+ " + carrage + " ";
        str += direction;
        return str;
    }
}; // Action

struct ShoreState
{ // 1 : left shore, 0 : right shore.
    bool F {1};
    bool G {1};
    bool W {1};
    bool C {1};
};

bool findMethod(Action &root, ShoreState s)
{
    s.F = !s.F; // Farmer moves.
    switch (root.carrage[0])
    {
    case 'G': // Move goat
        s.G = !s.G;
        break;
    case 'W': // Move wolf
        s.W = !s.W;
        break;
    case 'C': // Move cabbage
        s.C = !s.C;
        break;
    }
    // Check end state
    if ((s.W && s.G && !s.F) || (!s.W && !s.G && s.F)
        || (s.G && s.C && !s.F) || (!s.G && !s.C && s.F))
    {
        root.next = nullptr;
        return false;
    }
    // Found solution
    if (!s.C && !s.G && !s.W)
    {
        root.isLeaf = true;
        return true;
    }
    bool flag {0};
    string dir = root.direction[0] == 'r' ? "left" : "right";
    if (s.F == s.C && root.carrage[0] != 'C' && !flag)
    {
        Action a(dir, "C");
        root.next = &a;
        flag = findMethod(a, s);
    }
    else if (s.F == s.G && root.carrage[0] != 'G' && !flag)
    {
        Action a(dir, "G");
        root.next = &a;
        flag = findMethod(a, s);
    }
    else if (s.F == s.W && root.carrage[0] != 'W' && !flag)
    {
        Action a(dir, "W");
        root.next = &a;
        flag = findMethod(a, s);
    }
    else
    {
        Action a(dir, "");
        root.next = &a;
        flag = findMethod(a, s);
    }
}

int main(int argc, char ** argv)
{
    Action a("right", "G");
    ShoreState s;
    bool found {0};
    found = findMethod(a, s);

    cout << found;
    return 0;
}