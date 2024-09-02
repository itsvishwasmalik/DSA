#include<bits/stdc++.h>
using namespace std;
#define ll long long

class SegmentTree {
    public:
    ll size, blockSize;
    vector<ll> arr, segmentTree;

    void buildTree(int nodeIndex, int left, int right) {
        if (left == right) {
            segmentTree[nodeIndex] = arr[left];
            return;
        } 
        int mid = left + (right - left) / 2;
        buildTree(2 * nodeIndex + 1, left, mid);
        buildTree(2 * nodeIndex + 2, mid + 1, right);
        segmentTree[nodeIndex] = segmentTree[2 * nodeIndex + 1] + segmentTree[2 * nodeIndex + 2];
    }

    ll querySum(int nodeIndex, int left, int right, ll queryLeft, ll queryRight) {
        if (queryRight < left || right < queryLeft) return 0ll;
        if (queryLeft <= left && right <= queryRight) return segmentTree[nodeIndex];
        int mid = left + (right - left) / 2;
        return querySum(2 * nodeIndex + 1, left, mid, queryLeft, queryRight) + 
               querySum(2 * nodeIndex + 2, mid + 1, right, queryLeft, queryRight);
    }

    ll rangeSum(ll left, ll right) {
        return querySum(0, 0, size - 1, left, right);
    }

    void updateValue(int nodeIndex, int left, int right, int index, ll newValue) {
        if (left == right && right == index) {
            segmentTree[nodeIndex] = newValue;
            arr[index] = newValue;
            return;
        }
        int mid = left + (right - left) / 2;
        if (mid >= index) updateValue(2 * nodeIndex + 1, left, mid, index, newValue);
        else updateValue(2 * nodeIndex + 2, mid + 1, right, index, newValue);
        segmentTree[nodeIndex] = segmentTree[2 * nodeIndex + 1] + segmentTree[2 * nodeIndex + 2];
    }

    void update(ll index, ll newValue) {
        updateValue(0, 0, size - 1, index, newValue);
    }

    SegmentTree(vector<ll>& arr, ll size) {
        this->size = size;
        this->arr = arr;
        segmentTree = vector<ll>(4 * size, 0);
        buildTree(0, 0, size - 1);
    }
};

int main() {
    ll n, q;
    cin >> n >> q;
    vector<ll> arr(n);
    for (auto &element : arr) cin >> element;
    SegmentTree *root = new SegmentTree(arr, n);
    while (q--) {
        ll type, left, right;
        cin >> type;
        if (type == 2) {
            cin >> left >> right;
            cout << root->rangeSum(left - 1, right - 1) << endl;
        } else {
            cin >> left >> right;
            root->update(left - 1, right);
        }
    }
}
