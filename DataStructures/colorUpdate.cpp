template<typename T> struct Color{
	set<tuple<int, int, T>> se; 
	vector<tuple<int, int, T>> update(int l, int r, T c) {
		auto ret = query(l, r);
		se.erase(se.lower_bound({l, -INF, c}), se.upper_bound({r, INF, c}));
		se.emplace(l, r, c);
		return ret;
	}
	auto cut(int x){
		auto it = se.lower_bound({x, -INF, T()});
		if (it != se.begin() and get<1>(*prev(it)) >= x) {
			auto [L, R, C] = *--it;
			se.erase(it);
			se.emplace(L, x-1, C), it = se.emplace(x, R, C).first;
		}
		return it;
	}
	vector<tuple<int, int, T>> query(int l, int r){
		cut(r+1);
		vector<tuple<int, int, T>> ret;
		for(auto it = cut(l); it != se.end() and get<0>(*it) <= r; ++it)
			ret.push_back(*it);
		return ret;
	}
	T query(int i){
		if (auto it = se.upper_bound({i, INF, T()}); it == se.begin() or get<1>(*--it) < i) return -1;
		else return get<2>(*it);
	}
	ii getInterval(int i){//Ainda precisa fazer a união com os intervalos adjacentes
		auto it = se.upper_bound({i, INF, T()});
		it--;
		return {get<0>(*it), get<1>(*it)};
	}
};