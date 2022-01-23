template <typename T>
class KDTree
{
    struct KDNode
    {
        Point<T> v;
        KDNode *ch[2];
        KDNode(const Point<T> &v, KDNode *l, KDNode *r) : v{v}, ch{l, r} {}
        ~KDNode()
        {
            for (size_t i : {0, 1})
                if (ch[i])
                    ch[i]->~KDNode();
        }
        T dfs(const Point<T> q,

              T dis = numeric_limits<T>::max(),
              bool parity = 0)
        {
            dis = min(dis, (v - q).norm());
            bool isRight = parity ? v.x < q.x : v.y < q.y;
            if (ch[isRight])
                dis = min(dis, ch[isRight]->dfs(q, dis, parity ^ 1));
            if (ch[isRight ^ 1] and [](T x) {
                    return x * x;
                }(parity ? v.x - q.x : v.y - q.y) < dis)
                dis = min(dis, ch[isRight ^ 1]->dfs(q, dis, parity ^ 1));
            return dis;
        }
    } * root;
    KDNode *buildKDTree(typename vector<Point<T>>::iterator l,
                        typename vector<Point<T>>::iterator r,
                        bool parity = 0)
    {
        if (r == l)
            return nullptr;
        auto m = l + (r - l >> 1);
        nth_element(l, m, r, [=](Point<T> a, Point<T> b) {
            return parity ? a.x < b.x : a.y < b.y;
        });
        return new KDNode(*m,
                          buildKDTree(l, m, parity ^ 1),
                          buildKDTree(m + 1, r, parity ^ 1));
    }

public:
    KDTree(vector<Point<T>> A) : root{buildKDTree(A.begin(), A.end())} {}
    T nearestNeighborSquareDistance(Point<T> q)
    {
        return root->dfs(q);
    }
};
