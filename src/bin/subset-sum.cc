import std;

using namespace std;

template<typename T>
bool SubsetSum(unordered_set<T>& x, T t) {
    if (t == 0)
    {
        return true;
    }
    else if (t < 0 || x.empty())
    {
        return false;
    }
    else
    {
        int i = *x.begin();
        x.erase(x.begin());
        return SubsetSum(x, t - i)
            || SubsetSum(x, t);
    }
}

int main() {
    unordered_set<int> x{1, 2, 3, 4};
    println("{}", SubsetSum(x, 11));
    return 0;
}
