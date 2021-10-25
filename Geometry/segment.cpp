template<typename T> struct segment{
	complex<T> p, q;
	segment(complex<T> p, complex<T> q): p(p), q(q){}
};
template<typename T> bool onSegment(segment<T> s, complex<T> p1){
	if(p1.x() < min(s.p.x(), s.q.x()) - EPS || max(s.p.x(), s.q.x()) + EPS < p1.x())return false;
	if(p1.y() < min(s.p.y(), s.q.y()) - EPS || max(s.p.y(), s.q.y()) + EPS < p1.y())return false;
	return not cw(s.p, s.q, p1) && not ccw(s.p, s.q, p1);
}
template<typename T> tuple<T, T, T> getLineEquation(complex<T> p, complex<T> q){
	T a = q.y() - p.y(), b = p.x() - q.x(), c = a * p.x() + b * p.y();
	return make_tuple(a, b, c);
}
template<typename T> bool intersects(segment<T> s, segment<T> t){
	if(onSegment(s, t.p) || onSegment(s, t.q) ||
	   onSegment(t, s.p) || onSegment(t, s.q)) return true;
	for(auto _: {0, 1}){
		if((not cw(s.p, s.q, t.p) == not cw(s.p, s.q, t.q)) &&
		   (not cw(s.q, s.p, t.p) == not cw(s.q, s.p, t.q))) return false;
		swap(s, t);
	}
	return true;
}
template<typename T> complex<double> findIntersection(segment<T> s, segment<T> t){
	auto [a1, b1, c1] = getLineEquation(s.p, s.q);
	auto [a2, b2, c2] = getLineEquation(t.p, t.q);
	double det = a1 * b2 - a2 * b1;
	return complex<T>((b2 * c1 - b1 * c2) / det, (a1 * c2 - a2 * c1) / det);
}

template<typename T> long double segmentPointDist(segment<T> s, complex<T> p){
	long double dist = min(abs(p-s.p), abs(p-s.q));
	if(dot(s.p-s.q, p-s.q) > 0 && dot(s.q-s.p, p-s.p) > 0)
		dist = min(dist, abs(cross(s.p-s.q, p - s.q))/abs(s.p-s.q));
	return dist;
}