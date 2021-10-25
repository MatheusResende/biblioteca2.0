struct node{
	ll sum = 0;
	node(): sum(0){}
	node(ll sum): sum(sum){}
	friend node operator+(const node& lhs, const node& rhs){
		return node(lhs.sum + rhs.sum);
	}
	node& operator+=(const node& rhs){
		sum += rhs.sum;
		return *this;
	}
};

template<typename T> struct segmentTree{
	int n;
	vector<T> t;
	segmentTree(int n): n(n), t(2*n){};
	segmentTree(vector<T> a): n(a.size()), t(2*n){
		for(int i = 0; i < n; i++) t[i+n] = a[i];
		for(int i = n-1; i; i--) t[i] = t[i<<1] + t[i<<1|1];
	};
	void update(int p, T val){
		for(t[p += n] += val; p>>=1;) t[p] = t[p<<1] + t[p<<1|1]; 
	}
	T query(int l, int r){
		T lhs, rhs;
		for(l += n, r+=n+1; l < r; l>>=1, r>>=1){
			if(l&1)lhs = lhs + t[l++];
			if(r&1)rhs = t[--r] + rhs;
		}
		return lhs + rhs;
	}
};