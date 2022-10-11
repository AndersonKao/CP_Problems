#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for(int i = 0; i < (int)n; i++)
#define REP1(i, n) for(int i = 1; i <= (int)n; i++)
#define debug(x) cout << #x << ": " << x << endl;
#define depii(x) cout << "(" << x.first << ", " << x.second << ")";
#define devec(x) for(auto v: x) cout << v << endl;
#define eb emplace_back
#define F first
#define S second
#define al(x) x.begin(), x.end()
using ll = long long;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
template<typename T>
using p = pair<T, T>;

template<typename T>
using vec = vector<T>;
struct node{
	node* next;	
	node* prev;
	int v;
	bool ishead = false;
	bool isend = false;
	int id = -1;
	node(){prev = next = nullptr;}
	node(int v):v(v){prev = next = nullptr;}
};
void remove(node * cur){
	if(cur->prev){
		cur->prev->next = cur->next;
	}
	if(cur->next){
		cur->next->prev = cur->prev;
	}
}
void append(node* a, node *b){
	b->next = a->next;	
	b->prev = a;
	if(a->next){
		a->next->prev = b;
	}
	a->next = b;
}
node itV[1000001];
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(false);
	int n, m;	
	cin >> n >> m;
	vec<node*> Vbegin(n+1, nullptr);
	vec<node*> Vend(n+1, nullptr);
	for(int i = 1; i <= n; i++){
		itV[i].v = i;
		itV[i].ishead = itV[i].isend = true;
		itV[i].id = i;
		Vbegin[i] = Vend[i] = itV + i;
	}
	REP1(t, m){
		int op, a, b;
		if(t <= m)
			cin >> op >> a >> b;
		else{
			op = rand() & 1;
			a = rand() % n + 1;
			b = rand() % n + 1;
		}
#ifdef DEBUG
		cout << " op : " << op << ", " << a << ", " << b << endl;
#endif
		if(a == b){
			continue;
		}
		if(op == 0){
			if(itV[a].prev == &itV[b]){
#ifdef DEBUG
				cout << "no need\n";
#endif
				continue;
			}
			if(itV[a].ishead){
				Vbegin[itV[a].id] = itV[a].next;
				if(Vbegin[itV[a].id]){
					Vbegin[itV[a].id]->ishead = true;
					Vbegin[itV[a].id]->id = itV[a].id;
				}
				itV[a].ishead = false;
			}
			if(itV[a].isend){
				Vend[itV[a].id] = itV[a].prev;
				if(Vend[itV[a].id]){
					Vend[itV[a].id]->isend = true;
					Vend[itV[a].id]->id = itV[a].id;
				}
				itV[a].isend = false;
			}
			remove(&itV[a]);
			if(itV[b].isend){
				itV[b].isend = false;
				itV[a].isend = true;
				Vend[itV[b].id] = &itV[a];
				itV[a].id = itV[b].id;
			}
			append(&itV[b], &itV[a]);
		}
		else{
			if(Vbegin[a] == nullptr) {
#ifdef DEBUG
				cout << "empty a\n";
#endif
				continue;
			}
			if(Vend[b] == nullptr){
				Vbegin[b] = Vbegin[a];
				Vend[b] = Vend[a];
				Vbegin[b]->id = Vend[b]->id = b;
			}
			else{
				Vend[b]->isend = false;
				Vbegin[a]->ishead = false;
				Vend[b]->next = Vbegin[a]; 
				Vbegin[a]->prev = Vend[b];
				Vend[b] = Vend[a];
				Vend[a]->id = b;
			}
			Vbegin[a] = Vend[a] = nullptr;
		}
#ifdef DEBUG
		for(int i = 1; i <= n; i++){
			cout << i << ": ";
			if(itV[i].prev)
				cout << "prev: " <<  itV[i].prev->v;
			if(itV[i].next)
				cout << " next: " << itV[i].next->v;
			cout << endl;
			cout << itV[i].ishead  << ", " << itV[i].isend << ", " << itV[i].id << endl;
		}
		for(int i = 1; i <= n; i++){
			cout << "#" << i << ": begin= " << (Vbegin[i] ? Vbegin[i]->v : -1) << ", end= " << (Vend[i] ? Vend[i]->v : -1) << endl;
		}
		for(int i = 1; i <= n; i++){
			cout << "#" << i << ":";
			node* ptr= Vbegin[i];
			while(ptr){
				cout << " " << ptr->v;
				ptr = ptr->next;
			}
			cout << '\n';
		}
		cout << "--------------------\n";
#endif
	}
	for(int i = 1; i <= n; i++){
		cout << "#" << i << ":";
		node* ptr= Vbegin[i];
		while(ptr){
			cout << " " << ptr->v;
			ptr = ptr->next;
		}
		cout << '\n';
	}
	return 0;
}

