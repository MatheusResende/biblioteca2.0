template<typename T>
ii floyd(const auto &f, T x0){
	int pos = 0, period = 1;
	T a = f(x0), b = f(f(x0));
	for(;a != b; a = f(a), b = f(f(b)));
	for(a = x0; a != b; a = f(a), b = f(b), pos++);
	for(b = f(a); a != b; b = f(b), period += 1);
	return ii(period, pos);
}