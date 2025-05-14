import std.algorithm : max, cmp;
import std.functional : binaryFun;

struct Node(T)
{   
    T data;
    Node!T* leftChild;
    Node!T* rightChild;
}

Node!T* empty(T)()
    => null;

Node!T* node(T)(T data)
    => node(data, null, null);

Node!T* node(T, U, V)(T data, U leftChild, V rightChild)
{
    static if (is(U == T) && is(V == T))
    {
        return node(data, node(leftChild), node(rightChild));
    }
    else static if (is(U == T))
    {
        return node(data, node(leftChild), rightChild);
    }
    else static if (is(V == T))
    {
        return node(data, leftChild, node(rightChild));
    }
    else
    {
        return new Node!T(data, leftChild, rightChild);
    }
}

bool equal(T)(const(Node!T*) a, const(Node!T*) b)
    => (a.isEmpty() && b.isEmpty())
    || !a.isEmpty() && !b.isEmpty()
    && a.data == b.data
    && a.leftChild.equal(b.leftChild)
    && a.rightChild.equal(b.rightChild);

Node!T* copy(T)(Node!T* n)
{
    if (n.isEmpty()) return empty!T();
    return node(n.data, copy(n.leftChild), copy(n.rightChild));
}

bool isLeaf(T)(const(Node!T*) x)
    => !x.isEmpty() && (x.leftChild.isEmpty() && x.rightChild.isEmpty());

bool isEmpty(T)(const(Node!T*) x)
    => x == null;

bool isSearch(alias less = "a < b", T)(const(Node!T*) root)
if (is(typeof(binaryFun!less(T.init, T.init))))
    => (root.isEmpty())
    || (root.leftChild.isEmpty() || isSearch!less(root.leftChild, null, root))
    && (root.rightChild.isEmpty() || isSearch!less(root.rightChild, root, null));

bool isSearch(alias less = "a < b", T)(const(Node!T*) root, const(Node!T*) min, const(Node!T*) max)
if (is(typeof(binaryFun!less(T.init, T.init))))
    => (min.isEmpty() || binaryFun!less(min.data , root.data))
    && (max.isEmpty() || binaryFun!less(root.data, max.data))
    && (root.leftChild.isEmpty() || isSearch!less(root.leftChild, min, root))
    && (root.rightChild.isEmpty() || isSearch!less(root.rightChild, root, max));

void makeEmpty(T)(ref Node!T* n)
out (; n.isEmpty())
{
    n = null;
}

size_t height(T)(const(Node!T*) n)
    => n.isEmpty() ? 0 : 1 + max(height(n.leftChild), height(n.rightChild));

inout(Node!T*) binarySearch(alias less = "a < b", T)(inout(Node!T*) n, const(T) v)
if (is(typeof(binaryFun!less(T.init, T.init))))
in (n.isSearch!less(), "should be binary search tree")
{
    if (n.isEmpty()) return null;
    bool lt = binaryFun!less(v, n.data);
    bool gt = binaryFun!less(n.data, v);
    if (!lt && !gt) return n;
    if (lt) return n.leftChild.binarySearch!less(v);
    if (gt) return n.rightChild.binarySearch!less(v);
    return null;
}

void traversePreorder(T)(Node!T* n, void delegate(Node!T*) v)
{
    if (n.isEmpty()) return;
    v(n);
    traversePreorder(n.leftChild, v);
    traversePreorder(n.rightChild, v);
}

void traverseInorder(T)(Node!T* n, void delegate(Node!T*) v)
{
    if (n.isEmpty()) return;
    traverseInorder(n.leftChild, v);
    v(n);
    traverseInorder(n.rightChild, v);
}

void traversePostorder(T)(Node!T* n, void delegate(Node!T*) v)
{
    if (n.isEmpty()) return;
    traversePostorder(n.leftChild, v);
    traversePostorder(n.rightChild, v);
    v(n);
}

void traverseBreadthFirst(T)(Node!T* n, void delegate(Node!T*) v)
{
    import std.container.dlist : DList;
    if (n.isEmpty()) return;
    auto q = DList!(Node!T*)(n);
    while (!q.empty)
    {
        n = q.front();
        q.removeFront();
        v(n);
        if (!n.leftChild.isEmpty()) q.insertBack(n.leftChild);
        if (!n.rightChild.isEmpty()) q.insertBack(n.rightChild);
    }
}

void insert(alias less = "a < b", T)(ref Node!T* n, Node!T*other)
if (is(typeof(binaryFun!less(T.init, T.init))))
in (n.isSearch!less(), "should be binary search tree")
out (; n.isSearch!less())
{
    Node!T*t = n, p = null;
    while (!t.isEmpty())
    {
        p = t;
        if (binaryFun!less(other.data, t.data)) t = t.leftChild;
        else t = t.rightChild;
    }
    if (p.isEmpty())
    {
        n = other;
        return;
    }
    if (binaryFun!less(other.data, p.data))
    {
        p.leftChild = other;
        return;
    }
    p.rightChild = other;
}

void insert(alias less = "a < b", T)(ref Node!T* n, T d)
    => n.insert!less(node(d));

void remove(alias less = "a < b", T)(ref Node!T* n)
in (n.isSearch!less(), "should be binary search tree")
out (; n.isSearch!less())
{
    if (n.isEmpty())
    {
        return;
    }
    if (n.isLeaf())
    {
        n.makeEmpty();
        return;
    }
    if (n.leftChild.isEmpty())
    {
        n = n.rightChild;
        return;
    }
    if (n.rightChild.isEmpty())
    {
        n = n.leftChild;
        return;
    }
    Node!T* t = n.leftChild, p = n;
    while (!t.rightChild.isEmpty())
    {
        p = t;
        t = t.rightChild;
    }
    n.data = t.data;
    if (p == n) n.leftChild = t.leftChild;
    else p.rightChild = t.leftChild;
}

void rightRotate(alias less = "a < b", T)(ref Node!T* n)
in (n.isSearch!less(), "should be binary search tree")
out (; n.isSearch!less())
{
    Node!T* m = n.leftChild;
    n.leftChild = m.rightChild;
    m.rightChild = n;
    n = m;
}

void leftRotate(alias less = "a < b", T)(ref Node!T* n)
in (n.isSearch!less(), "should be binary search tree")
out (; n.isSearch!less())
{
    Node!T* m = n.rightChild;
    n.rightChild = m.leftChild;
    m.leftChild = n;
    n = m;
}

void main()
{
    import std.stdio;
    auto t = node(5, node(3, null, 4), null);
    auto tt = () { write("["); t.traverseBreadthFirst((Node!int *x) { write(x.data, ","); }); writeln("]"); };
    tt();
    writeln(t.leftChild.height, " ", t.rightChild.height);
    t.leftChild.leftRotate();
    t.rightRotate();
    writeln(t.leftChild.height, " ", t.rightChild.height);
    tt();
}
