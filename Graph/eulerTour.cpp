//Do not forget to check if there exists an eulerian path/cycle before calling dfs
struct EulerianPath{
	vector<vector<tuple<int, int, bool>>> E;
	vector<int> tour;
	EulerianPath(int n): E(n){}
	void addEdge(int u, int v){
		int p1 = E[u].size(), p2 = E[v].size();
		E[u].emplace_back(v, p2, 0);
		E[v].emplace_back(u, p1, 0);
	}	
	void dfs(int u){
		while(!E[u].empty()){
			auto [v, rev, used] = E[u].back();
			E[u].pop_back();
			if(!used){
				get<2>(E[v][rev]) = 1;
				dfs(v);
			}
		}
		tour.push_back(u);
	}
};