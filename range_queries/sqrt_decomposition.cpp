#include<bits/stdc++.h>
using namespace std;
#define ll long long

class SqrtDecomposition {
public:
    ll size, blockSize;
    vector<ll> elements, blockSums;

    SqrtDecomposition(vector<ll>& elements, ll size) {
        this->size = size;
        this->elements = elements;
        blockSize = ceil(sqrt(size));
        blockSums = vector<ll>(blockSize);
        build();
    }

    void build() {
        for (ll i = 0; i < size; i++) {
            blockSums[i / blockSize] += elements[i];
        }
    }

    ll querySum(ll left, ll right) {
        ll leftBlock = left / blockSize;
        ll rightBlock = right / blockSize;
        ll sumResult = 0;

        if (leftBlock == rightBlock) {
            return accumulate(elements.begin() + left, elements.begin() + right + 1, 0ll);
        }

        ll leftSum = 0;
        ll rightSum = 0;

        for (ll i = left; (i / blockSize) == leftBlock; i++) {
            leftSum += elements[i];
        }

        for (ll i = leftBlock + 1; i < rightBlock; i++) {
            sumResult += blockSums[i];
        }

        for (ll i = rightBlock * blockSize; i <= right; i++) {
            rightSum += elements[i];
        }

        return sumResult + leftSum + rightSum;
    }

    void update(ll index, ll newValue) {
        blockSums[index / blockSize] += (newValue - elements[index]);
        elements[index] = newValue;
    }
};

int main() {
    ll size, queries;
    cin >> size >> queries;
    vector<ll> elements(size);
    for (auto &element : elements) cin >> element;

    SqrtDecomposition* sqrtDecomp = new SqrtDecomposition(elements, size);

    while (queries--) {
        ll queryType, left, right;
        cin >> queryType;
        if (queryType == 2) {
            cin >> left >> right;
            cout << sqrtDecomp->querySum(left - 1, right - 1) << endl;
        } else {
            cin >> left >> right;
            sqrtDecomp->update(left - 1, right);
        }
    }
}
