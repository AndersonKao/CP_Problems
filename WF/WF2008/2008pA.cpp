#include <bits/stdc++.h>
using namespace std;
#define debug(x) cout << #x << ":= " << x << endl;
struct cuber{
	int x, y, z;
	int face; // 0 +x, 1 -x, 2 +y, 3 -y, 4 +z, 5 -z
	bool operator==(cuber& cub){
		return this->x == cub.x && this->y == cub.y && this->z == cub.z && this->face == cub.face;
	}
	friend ostream& operator<<(ostream&os, cuber& cube);
};
ostream& operator<<(ostream&os, cuber& cube){
	return (os << cube.x << ", " << cube.y << ", " << cube.z << ", f = " << cube.face);
}
inline int deface(string&str){
	if(str == "+x")
		return 0;
	else if(str == "-x")
		return 1;
	else if(str == "+y")
		return 2;
	else if(str == "-y")
		return 3;
	else if(str == "+z")
		return 4;
	return 5;
}  
cuber st, ed;                                         
/*       |                                            |       -|
type 0 --|   type 1 --| type 2 --X type 3 --O type 4  | type 5 | type 6 -X^2 type 7 -O^2
                      |                              -|        |
*/
int Xlen, Ylen, Zlen;
vector<vector<int>> direc = {
	{1, 0, 0},
	{-1, 0, 0},
	{0, 1, 0},
	{0, -1, 0},
	{0, 0, 1},
	{0, 0, -1} 
};
vector<vector<int>> dimove= {
	{0, 0, 0, 2},		
	{0, 0, 0, 3},		
	{0, 0, 0, 4},		
	{0, 0, 0, 5},		
	{0, 0, 2, 2},
	{0, 0, 3, 3},		
	{0, 0, 4, 4},		
	{0, 0, 5, 5}	
};
vector<vector<vector<int>>> visited;
bool validblock(int x, int y, int z){
	if(x <= 0 || x > Xlen || y <= 0 || y > Ylen || z <= 0 || z > Zlen || visited[x][y][z])
		return false;
	return true;	
}
int ANS;
void DFS(cuber cur, int depth){
	if(cur == ed){
		ANS = min(depth, ANS);	
		return;
	}
	if(depth == 6)
		return;
	cuber nxt = cur;
	int *fx, *fy, *fz;
	vector<int> nface(4);
	switch(cur.face){
		case 0:
		case 1:
			fx = &nxt.x;	
			fy = &nxt.y;	
			fz = &nxt.z;	
			nface = {2, 3, 4, 5};
			break;
		case 2:
		case 3:
			fx = &nxt.y;
			fy = &nxt.z;
			fz = &nxt.x;
			nface = {4, 5, 0, 1};
			break;
		case 4:
		case 5:
			fx = &nxt.z;
			fy = &nxt.x;
			fz = &nxt.y;
			nface = {0, 1, 2, 3};
			break;
	}	
	int neg = (cur.face & 1) ? -1 : 1; 
	for(int k = 0; k < 8; k++){
		nxt = cur;
		bool moveit = true;
		int step = 0;
		for(step = 0; step < 4; step++){
			int mid = dimove[k][step];
			(*fx)+=direc[mid][0] * neg;
			(*fy)+=direc[mid][1] * neg;
			(*fz)+=direc[mid][2] * neg;
			if(validblock(nxt.x, nxt.y, nxt.z) == false){
				moveit = false;
			}
			visited[nxt.x][nxt.y][nxt.z] = true;
			if(moveit == false)
				break;
		}
		nxt.face = nface[((k & 0b11) ^ (neg == -1 ? 0b01 : 0b00))];
		if(moveit)
			DFS(nxt, depth+1);
		for(step = (step == 4 ? step-1 : step);step >= 0; step--){
			visited[nxt.x][nxt.y][nxt.z] = false;
			int mid = dimove[k][step];
			(*fx)-=direc[mid][0] * neg;
			(*fy)-=direc[mid][1] * neg;
			(*fz)-=direc[mid][2] * neg;
		}
	}
}
int main(){
	int caseN = 1;
	while(cin >> Xlen){
		if(Xlen == 0)
			break;
		cin >> Ylen >> Zlen;
		visited.clear();
		visited.resize(Xlen + 2, vector<vector<int>>(Ylen + 2, vector<int>(Zlen + 2, 0)));
		string str;
		cin >> st.x >> st.y >> st.z >> str;
		st.face = deface(str);
		if(st.face == 0){
				st.x--;
		}else if(st.face == 1){
				st.x++;
		}else if(st.face == 2){
				st.y--;
		}else if(st.face == 3){
				st.y++;
		}else if(st.face == 4){
				st.z--;
		}else if(st.face == 5){
				st.z++;
		}
		cin >> ed.x >> ed.y >> ed.z >> str;
		ed.face = deface(str);
		ANS = numeric_limits<int>::max();
		DFS(st, 0);		
		cout << "Case " << caseN++ << ": ";	
		if(ANS == numeric_limits<int>::max())
			cout << "Impossible\n";
		else
			cout << ANS << endl;
	} 
	return 0;
}

