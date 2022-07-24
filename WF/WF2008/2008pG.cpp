#include <bits/stdc++.h>
using namespace std;
#define REP(i, n) for (int i = 0; i < (int)n; i++)
template <typename T>
using vec = vector<T>;
#define eb emplace_back
#define debug(x) cout << #x << ":= " << x << endl;
#define al(x) x.begin(), x.end()
const int Len = 4;
const int R = 3;
double eps = 1e-9;
using uint = unsigned int;
inline int fcmp(double a, double b){
    if(fabs(a- b) < eps)
        return 0;
    return (a > b) * 2 - 1;
}
struct coeff{
	vector<double>p; // for contant, coff of {a1, k, a1c, a1^2, k^2, a1^c, ka1c}
	coeff(){
		p.resize(6);
		fill(al(p), 0.0);
	}
	coeff(vector<double> v){
		p = v;
	}
	void operator=(vector<double> v){
		p = v;
	}
	coeff(const coeff& rhs){
		p = rhs.p;
	}
	void operator+=(const coeff& rhs){
		for(unsigned int i = 0; i < p.size(); i++)
			p[i] += rhs.p[i];	
	}
	coeff operator+(const coeff& rhs){
		coeff res = (*this);
		for(unsigned int i = 0; i < p.size(); i++){
			res.p[i] += rhs.p[i];	
		}
		return res;
	}
	void operator*=(double r){
		for(unsigned int i = 0; i < p.size(); i++){
			p[i]*= r;	
		}
	}
	coeff operator*(double r){
		coeff res = (*this);
		for(unsigned int i = 0; i < p.size(); i++){
			res.p[i]*= r;	
		}
		return res;
	}

	void operator*=(const coeff& rhs){
		const vector<double>& p2 = rhs.p;	
		p = {
			p[0] * p2[0], 
			p[0] * p2[1] + p[1] * p2[0],
		 	p[2] * p2[0] + p[0] * p2[2],
			p[1] * p2[1],
			p[2] * p2[1] + p[1] * p2[2],
			p[2] * p2[2],
		};		
	}
	coeff operator*(const coeff& rhs){
		const vector<double>& p2 = rhs.p;
		coeff newC;
		newC.p = {
			p[0] * p2[0], 
			p[0] * p2[1] + p[1] * p2[0],
		 	p[2] * p2[0] + p[0] * p2[2],
			p[1] * p2[1],
			p[2] * p2[1] + p[1] * p2[2],
			p[2] * p2[2],
		};		
		return newC;
	}
};

using coeffpoly = vector<coeff>;
using polynomial = vector<double>;
coeffpoly mul(coeffpoly &p1, coeffpoly&p2){
	coeffpoly p3((p1.size() - 1) + (p2.size()-1) + 1);
	
	for(uint i = 0; i < p1.size(); i++){
		for(uint j = 0; j < p2.size(); j++){
			p3[i+j] += p1[i] * p2[j];	
		}
	}
	return p3;
}
void partialAB(polynomial& poly, vector<coeff>& fpoly, double xC, bool doB){
	double res1 = 1.0, res2 = 1.0;
	double res ;

	for(int i = 0; i < fpoly.size(); i++){
		vector<double>&p = fpoly[i].p;
		if(doB)
			res1 = -res1;
		res2 *= xC;
		if(doB == false){
			res = res1 - res2;
			poly[0] += 2 * p[3] * res;
		}
		else{
			res = res2 - res1;
			poly[1] += 2 * p[3] * res;
		}
		poly[2] += p[4] * res;	
		poly[3] -= p[1] * res;
	}
}

void partialK(polynomial& poly, vector<coeff>& fpoly, double xC){
	double res1 = 1.0, res2 = 1.0;
	double res ;

	for(int i = 0; i < fpoly.size(); i++){
		vector<double>&p = fpoly[i].p;
		res1 = -res1;
		res2 *= xC;
		res = 1.0 - res2;
		poly[0] += p[4] * res;
		poly[2] += 2 * p[5] * res;
		poly[3] -= p[2] * res;
		res = res2 - res1;
		poly[1] += p[4] * res;
		poly[2] += 2 * p[5] * res;
		poly[3] -= p[2] * res;
	}
}
void pG(vec<vec<double>> &polynomials){
    cout << "polynomials now -----------------:\n";
    for (int i = 0; i < Len; i++)
    {
        cout <<setw(3) << i << ": ";
        for (int j = 0; j <= R; j++)
        {
            cout << setw(5) << polynomials[j][i] << " ";
        }
        cout << endl;
    }
}
bool eliminate(int r, int c, vec<vec<double>> &polynomials)
{
    vec<double> rate(R, 0.0);
    double base = polynomials[r][c];
    if(fcmp(base, 0.0) == 0){
        int found = -1;
        for (int i = r + 1; i < R; i++){
            if(fcmp(polynomials[i][c], 0.0) != 0){
                found = i;
                break;
            }
        }
        if(found == -1){
            return false;
        }
        for (int i = c; i < Len; i++){
            swap(polynomials[r][i], polynomials[found][i]);
        }
        base = polynomials[r][c];
    }
    for (int i = r+1; i < R; i++){
        rate[i] = polynomials[i][c] / base;
        polynomials[i][c] = 0.0;
    }
    for (int i = r + 1; i < R; i++)
    {
        for (int j = c + 1; j < Len; j++)
        {
            polynomials[i][j] -= polynomials[r][j] * rate[i];
        }
    }
    return true;
}
// 0 for no solution, 1 for one solution, 2 for inf solution
void gauss(vec<vec<double>>&polynomials, vector<double>& ans){
	ans.resize(Len-1, 0.0);
    int curr = 0;
//    pG(polynomials);
    REP(c, Len-1) 
    {
        if(eliminate(curr, c, polynomials))
            curr++;
//        pG(polynomials);
    }
    for (int i = R-1; i >= 0; i--) {
		double rhs = polynomials[i][Len-1];
		for(int j = R-1; j > i; j--){
			rhs -= polynomials[i][j] * ans[j];
		}
		ans[i] = rhs / polynomials[i][i];
    }
}
int N;
int main()
{
    int caseN = 1;
    while (cin >> N)
    {
		if(N == 0)
            break;
		vector<coeff> fpoly(N+1);
		for(int i = N; i >= 0; i--){
			cin >> fpoly[i].p[0];
		}
		double xC;
		cin >> xC;
		fpoly[1].p[1] -= 1.0; // -a1X
		fpoly[0].p[1] += xC; // +a1C
		fpoly[0].p[2] -= 1.0;// -k 
		
		fpoly = mul(fpoly, fpoly);
		// Integral
		for(int i = 0; i < fpoly.size(); i++){
			fpoly[i] *= (1 / (i+1.0));
		}
		vector<polynomial> polys(R, polynomial(Len, 0.0));		
		partialAB(polys[0], fpoly, xC, false);
		partialAB(polys[1], fpoly, xC, true);
		partialK(polys[2], fpoly, xC);
/*
		for(polynomial&e : polys){
			for(double &e2: e){
				cout << e2 << " ";
			}
			cout << endl;
		}
*/
		vector<double> ans;
		gauss(polys, ans); 
/*
		cout << "a1 b1 k\n";
		for(double &e: ans){
			cout << e << endl;
		}
*/
		cout << fixed << setprecision(3);
		cout << "Case " << caseN++ <<": " << ans[1] << " " << ans[2] - ans[1] * xC<< " " << ans[0] << " " << ans[2] - ans[0] * xC  << endl;	
    }
    return 0;
}
