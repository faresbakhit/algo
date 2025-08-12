import std;

using namespace std;

void search(
    int& count,
    const int n,
    vector<bool>& col,
    vector<bool>& pos_diag,
    vector<bool>& neg_diag,
    int y = 0
) {
    if (y == n) {
        count++;
        return;
    }
    for (int x = 0; x < n; x++) {
      if (col[x] || pos_diag[x-y+n-1] || neg_diag[x+y]) continue;
      col[x] = pos_diag[x-y+n-1] = neg_diag[x+y] = true;
      search(count, n, col, pos_diag, neg_diag, y + 1);
      col[x] = pos_diag[x-y+n-1] = neg_diag[x+y] = false;
    }
}

int q(int n) {
    vector<bool>
      col(n),
      pos_diag(n+2),
      neg_diag(n+2);
    int count = 0;
    search(
        count,
        n,
        col,
        pos_diag,
        neg_diag
    );
    return count;
}

int main() {
    int n;
    cin >> n;
    println("{}", q(n));
}
