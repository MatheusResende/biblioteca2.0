// counter-clockwise order
// to allow colinear points change:
//1: not cw  ---> ccw
//2: not cww ---> cw
template<typename T> vector<complex<T>> convex_hull(vector<complex<T>> pts) {
    sort(begin(pts), end(pts), lex_cmp<T>), pts.erase(unique(begin(pts), end(pts)), end(pts));
    if (size(pts) <= 1) return pts;
    vector<complex<T>> upper(size(pts)), lower(size(pts));
    int k = 0, l = 0;
    for (auto p : pts) {
        while (k > 1 && not cw(upper[k - 2], upper[k - 1], p)) --k;
        while (l > 1 && not ccw(lower[l - 2], lower[l - 1], p)) --l;
        upper[k++] = lower[l++] = p;
    }
    upper.resize(k - 1), lower.resize(l);
    reverse(begin(upper), end(upper));
    lower.insert(end(lower), begin(upper), end(upper) - 1);
    return lower;
}

template<typename T> long double area(vector<complex<T>> pts){
	int n = pts.size();
	pts.push_back(pts[0]);
	long double ret = 0;
	for(int i = 0; i < n; i++) ret += cross(pts[i], pts[i+1]);
	return abs(ret/2.0);
}

template<typename T> bool isInside(vector<complex<T>> pts, complex<T> p){
	int n = pts.size(), cnt = 0;
	pts.push_back(pts[0]);
	uniform_real_distribution<long double> uniform(0, 2*acos(-1));
	segment s(p, p + polar((long double)5e9, uniform(rng)));
	for(int i = 0; i < n; i++){
		segment t(pts[i], pts[i+1]);
		if(onSegment(t, p))return true;
		cnt += intersects(s, t);
	}
	return cnt % 2;
}