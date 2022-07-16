/*1065 - Raising the Roof _ Slicing */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define DBUGM1
#define LargeINT 1000000000
#define MaxVertex 3000
#define MaxSlice 10000
#define errorT 0.000001
#define GetCase 500000
#define M_PI 3.14159265358979323846
/*Struct*/
typedef struct {
    double x, y, z;
} Vec;
typedef struct Vertex {
    double x, y, z;
    int triangle;
    int hasNext;
    double nx, ny, nz;
}Vertex;
typedef struct {
    double x1, x2;
    double y1, y2;
    double z1, z2;
} Segment;
typedef struct {
    int vIndex[3];
    Segment lines[3];
    /*ax + by + cz + d = 0*/
    double a, b, c, d;
    double cos;
} Triangle;
typedef struct {
    double x;
    Segment line;
    Vertex v[MaxVertex];
} Slice;
/*Global variable*/
int vertexNumber = 0, triangleNumber = 0;
Vertex vArray[305];
Triangle tArray[1005];

double sliceX[MaxVertex*MaxVertex];
int sliceNumber = 0;
Slice slices[MaxSlice];
int svNumber[MaxSlice];

/*Function*/
double VecLen(Vec v)
{
    return sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}
void Cross(Vec a, Vec b, Vec *c)
{
    c->x = a.y*b.z - a.z*b.y;
    c->y = a.z*b.x - a.x*b.z;
    c->z = a.x*b.y - a.y*b.x;
    if(c->z < 0-errorT){
        c->x *= -1;
        c->y *= -1;
        c->z *= -1;
    }
}
void GetVec(Vertex a, Vertex b, Vec *v)
{
    v->x = b.x - a.x;
    v->y = b.y - a.y;
    v->z = b.z - a.z;
}
void FindPlane(Triangle* t)
{
    Vec a, b, c;
    GetVec(vArray[t->vIndex[0]], vArray[t->vIndex[1]], &a);
    GetVec(vArray[t->vIndex[0]], vArray[t->vIndex[2]], &b);
    Cross(a, b, &c);
    double d = -(c.x*vArray[t->vIndex[0]].x + c.y*vArray[t->vIndex[0]].y + c.z*vArray[t->vIndex[0]].z);
    t->a = c.x;
    t->b = c.y;
    t->c = c.z;
    t->d = d;
    if(fabs(t->c - 0) < errorT ) t->cos = -1;
    if(fabs(VecLen(c) - 0) < errorT) while(1);
    t->cos = fabs((t->c)/VecLen(c));
}
void FindLine2(Vertex a, Segment* line)
{
    line->x1 = a.x;
    line->y1 = a.y;
    line->z1 = a.z;
    line->x2 = a.nx;
    line->y2 = a.ny;
    line->z2 = a.nz;
}
void FindLine(Vertex a, Vertex b, Segment* line)
{
    if(a.x - b.x < 0+errorT){
        line->x1 = a.x;
        line->y1 = a.y;
        line->z1 = a.z;
        line->x2 = b.x;
        line->y2 = b.y;
        line->z2 = b.z;
    }
    else {
        line->x1 = b.x;
        line->y1 = b.y;
        line->z1 = b.z;
        line->x2 = a.x;
        line->y2 = a.y;
        line->z2 = a.z;
    }

}
void Read(int caseNumber)
{
    #ifdef DBUGM
        printf("----------- Read-----------\n");
    #endif
    int i, j, k;
    sliceNumber = 0;
    for(i = 0; i < vertexNumber; i++){
        scanf("%lf%lf%lf", &vArray[i].x, &vArray[i].y, &vArray[i].z);
    }
    int tmpCount = 0;
    for(i = 0; i < triangleNumber; i++){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        tArray[tmpCount].vIndex[0] = a-1;
        tArray[tmpCount].vIndex[1] = b-1;
        tArray[tmpCount].vIndex[2] = c-1;
        FindLine(vArray[tArray[tmpCount].vIndex[0]], vArray[tArray[tmpCount].vIndex[1]], &tArray[tmpCount].lines[0]);
        FindLine(vArray[tArray[tmpCount].vIndex[1]], vArray[tArray[tmpCount].vIndex[2]], &tArray[tmpCount].lines[1]);
        FindLine(vArray[tArray[tmpCount].vIndex[2]], vArray[tArray[tmpCount].vIndex[0]], &tArray[tmpCount].lines[2]);
        FindPlane(&tArray[tmpCount]);
        if( fabs(tArray[tmpCount].c - 0) < errorT ) continue;
        tmpCount++;
    }
    triangleNumber = tmpCount;
}
void ShowLine(Segment edgeA)
{
    printf("Line: (%2.2lf, %2.2lf %2.2lf) -> (%2.2lf, %2.2lf %2.2lf)\n", edgeA.x1, edgeA.y1, edgeA.z1, edgeA.x2, edgeA.y2, edgeA.z2);
}
void ShowVertex(Vertex v)
{
    if( v.hasNext != 0)
        printf("   (%2.2lf %2.2lf %2.2lf) Triangle: %d next: -> (%2.2lf %2.2lf %2.2lf)  \n", v.x, v.y, v.z, v.triangle, v.nx, v.ny, v.nz);
    else
        printf("   (%2.2lf %2.2lf %2.2lf) Triangle: %d next: -> NULL  \n", v.x, v.y, v.z, v.triangle);

}
int FindIntersection(Segment edgeA, Segment edgeB, Vertex *v)
{
    #ifdef DBUGM
        printf("\n---FindIntersection %2.2lf\n", fabs(((edgeA.y2 - edgeA.y1)*(edgeB.x2 - edgeB.x1) - (edgeA.x2 - edgeA.x1)*(edgeB.y2 - edgeB.y1))));
        ShowLine(edgeA);
        ShowLine(edgeB);
    #endif

     if( fabs((edgeA.y2 - edgeA.y1)*(edgeB.x2 - edgeB.x1) - (edgeA.x2 - edgeA.x1)*(edgeB.y2 - edgeB.y1)) < errorT ){
        return 0;
    }

    /*Compute the proportion from edgeA->P1 to the intersection*/
    /*ua = ((x4 - x3)(y1 - y3) - (y4-y3)(x1-x3)) / ((y4 - y3)(x2 - x1) - (x4 - x3)(y2 - y1))*/
    double ppB = ((edgeA.x2 - edgeA.x1)*(edgeB.y1 - edgeA.y1) - (edgeA.y2 - edgeA.y1)*(edgeB.x1 - edgeA.x1)) / ((edgeA.y2 - edgeA.y1)*(edgeB.x2 - edgeB.x1) - (edgeA.x2 - edgeA.x1)*(edgeB.y2 - edgeB.y1));
    double ppA = ((edgeB.x2 - edgeB.x1)*(edgeA.y1 - edgeB.y1) - (edgeB.y2 - edgeB.y1)*(edgeA.x1 - edgeB.x1)) / ((edgeB.y2 - edgeB.y1)*(edgeA.x2 - edgeA.x1) - (edgeB.x2 - edgeB.x1)*(edgeA.y2 - edgeA.y1));
    #ifdef DBUGM
        printf("ppA, ppB: %2.2lf %2.2lf\n", ppA, ppB);
    #endif
    if(ppB > 1+errorT || ppB < 0-errorT || ppA > 1+errorT || ppA < 0-errorT) return 0;
    else {
        v->x = (edgeA.x2 - edgeA.x1)*ppA + edgeA.x1;
        v->y = (edgeA.y2 - edgeA.y1)*ppA + edgeA.y1;
        v->z = (edgeA.z2 - edgeA.z1)*ppA + edgeA.z1;
        #ifdef DBUGM
        printf("Intersection: (%2.2lf, %2.2lf %2.2lf)\n", v->x, v->y, v->z);
        #endif
        return 1;
    }
}
int cmp(const void *a, const void *b)
{
    if( fabs(*(double*)a - *(double*)b) < errorT) return 0;
    else if(*(double*)a - *(double*)b > 0) return 1;
    else return -1;
}
int cmpVertex(const void *a, const void *b)
{
    Vertex *ap = (Vertex*)a, *bp = (Vertex*)b;
    if(bp->hasNext - ap->hasNext != 0) return bp->hasNext - ap->hasNext;
    if(fabs(bp->y - ap->y) < errorT && bp->hasNext == 1 && ap->hasNext == 1){
        if(fabs(bp->ny - ap->ny) < errorT) return 0;
        else if((bp->ny - ap->ny) > 0) return 1;
        else return -1;
    }
    else if(bp->y - ap->y > 0) return 1;
    else return -1;
}

void ShowTriangle()
{
    int i, j;
    for(i = 0; i < triangleNumber; i++){
        printf("T: %d\n", i);
        printf("%2.2lfx + %2.2lfy + %2.2lfz + %2.2lf = 0\n",tArray[i].a, tArray[i].b, tArray[i].c, tArray[i].d);
        printf("cos: %2.2lf\n", tArray[i].cos);
        for(j = 0; j < 3; j++) printf("%d: (%2.2lf %2.2lf %2.2lf)\n", tArray[i].vIndex[j], vArray[tArray[i].vIndex[j]].x, vArray[tArray[i].vIndex[j]].y, vArray[tArray[i].vIndex[j]].z);
        ShowLine(tArray[i].lines[0]);
        ShowLine(tArray[i].lines[1]);
        ShowLine(tArray[i].lines[2]);
    }
}
const int roundT = 72;
double CalculateOriginalArea(Segment s1, Segment s2, double height, int triN, int round)
{
    if(round == roundT){
        printf("      ---- Valid Area:\n");
        printf("      height: %2.2lf, Triangle: %d\n      ", height, triN);
        ShowLine(s1);
        printf("      ");
        ShowLine(s2);
        if(triN == 40){
            for(int i = 0; i < 3; i++)
                ShowLine(tArray[triN].lines[i]);
        }
    }
    if( fabs(tArray[triN].cos+1) < errorT) return 0;
    double f = sqrt( (s1.x1 - s2.x1)*(s1.x1 - s2.x1) + (s1.y1 - s2.y1)*(s1.y1 - s2.y1) + (s1.z1 - s2.z1)*(s1.z1 - s2.z1));
    double c = sqrt( (s1.x2 - s2.x2)*(s1.x2 - s2.x2) + (s1.y2 - s2.y2)*(s1.y2 - s2.y2) + (s1.z2 - s2.z2)*(s1.z2 - s2.z2));
    #ifdef DBUGM
        printf("      Area: (%2.2lf + %2.2lf)*%2.2lf /2/%2.2lf: %2.2lf\n", f, c, height, tArray[triN].cos, fabs( (f + c) * height/tArray[triN].cos/2));
    #endif
    return fabs( ((f + c) * height/2)/tArray[triN].cos);
}
int GetAbove(int t1, int t2, Vertex v)
{
    double z1 = (-tArray[t1].a*v.x - tArray[t1].b*v.y - tArray[t1].d)/tArray[t1].c;
    double z2 = (-tArray[t2].a*v.x - tArray[t2].b*v.y - tArray[t2].d)/tArray[t2].c;
    if(z1 - z2 > 0-errorT) return t1;
    else return t2;
}
int GetTop(Segment s1, Vertex v, int valid[triangleNumber])
{
    int i;
    int tmp = -1;
    Vertex tmpV ;
    tmpV.x = ((v.x + v.nx)/2 + (s1.x1 + s1.x2)/2)/2;
    tmpV.y = ((v.y + v.ny)/2 + (s1.y1 + s1.y2)/2)/2;
    tmpV.z = ((v.z + v.nz)/2 + (s1.z1 + s1.z2)/2)/2;
    for(i = 0; i < triangleNumber; i++){
        #ifdef DBUGM
            printf("%d ", valid[i]);
        #endif
        if(valid[i] == 0) continue;
        if(tmp == -1) {
            tmp = i;
            continue;
        }
        else {
            tmp = GetAbove(tmp, i, tmpV);
        }
    }
    #ifdef DBUGM
        printf("\n");
    #endif
    return tmp;
}
int main()
{
    /*
    #ifndef ONLINE_JUDGE
		freopen("input.in", "r", stdin);
		freopen("output.out", "w", stdout);
	#endif
    */
    int i, j, k;
    int caseNumber = 1;

    while(1){
        scanf("%d%d", &vertexNumber, &triangleNumber);
        if(vertexNumber == 0) break;
        #ifdef DBUGM
            printf("----------- Debug Message %d-----------\n", caseNumber);
        #endif
        Read(caseNumber);
        #ifdef DBUGM
            printf("Triangles:\n");
            ShowTriangle();
            printf("Start Slice:\n");
        #endif
        /*Find SliceX*/
        for(i = 0; i < triangleNumber; i++){
            /*3 vertex*/
            for(j = 0; j < 3; j++){
                sliceX[sliceNumber++] = vArray[tArray[i].vIndex[j]].x;
            }
            /*The intersection with other edge*/
            for(j = 0; j < triangleNumber; j++){
                if(i == j) continue;
                for(k = 0; k < 3; k++){
                    Vertex tmp;
                    if(FindIntersection(tArray[i].lines[0], tArray[j].lines[k], &tmp) )sliceX[sliceNumber++] = tmp.x;
                    if(FindIntersection(tArray[i].lines[1], tArray[j].lines[k], &tmp) )sliceX[sliceNumber++] = tmp.x;
                    if(FindIntersection(tArray[i].lines[2], tArray[j].lines[k], &tmp) )sliceX[sliceNumber++] = tmp.x;
                }
            }
        }
        if(sliceNumber >= MaxVertex*MaxVertex)while(1);
        qsort(sliceX, sliceNumber, sizeof(double), cmp);

		/*
        int cur = 0;
        for(int i = 1; i < sliceNumber; i++){
            if(cmp(sliceX + cur, sliceX + i) != 0){
                cur++;
                *(sliceX + cur) = *(sliceX + i);
            }
        }
        sliceNumber = cur;
        */
        #ifdef DDBUGM
            printf("\n---Slice X:\n");
            for(i = 0; i < sliceNumber; i++) printf("%2.6lf \n", sliceX[i]);
            printf("\n");
        #endif
        /*Remove duplicate X*/
        int tmpn = sliceNumber;
        sliceNumber = 0;
        double now = -1;
        for(i = 0; i < tmpn; i++){
            if(fabs(sliceX[i] - now) < errorT ) continue;
            else {
                now = sliceX[i];
                if(now < 0-errorT) while(1);
                svNumber[sliceNumber] = 0;
                slices[sliceNumber].x = now;
                slices[sliceNumber].line.x1 = now;
                slices[sliceNumber].line.y1 = -1000;
                slices[sliceNumber].line.x2 = now;
                slices[sliceNumber].line.y2 = 1000;
                slices[sliceNumber].line.z1 = 0, slices[sliceNumber].line.z2 = 0;
                sliceNumber++;
            }
        }
        #ifdef DSLICEX
            printf("\n---Slice X:\n");
            for(i = 0; i < sliceNumber; i++) printf("%2.6lf \n", slices[i].x);
            printf("\n");
        #endif
        if(sliceNumber >= MaxSlice) while(1);
        /*For each slice , sort vertexes on it*/
        for(i = 0; i < triangleNumber; i++){
            for(j = 0; j < 3; j++){
                Vertex *tmpp = NULL;
                for(k = 0; k < sliceNumber; k++){
                    if(tArray[i].lines[j].x1 > slices[k].x + errorT) continue;
                    if(tArray[i].lines[j].x2 < slices[k].x - errorT) {
                        if(tmpp != NULL)
                            tmpp->hasNext = 0;
                        break;
                    }
                    if(FindIntersection(slices[k].line, tArray[i].lines[j], &slices[k].v[svNumber[k]])){
                        slices[k].v[svNumber[k]].triangle = i;
                        if(tmpp != NULL) {
                            tmpp->hasNext = 1;
                            tmpp->nx = slices[k].v[svNumber[k]].x;
                            tmpp->ny = slices[k].v[svNumber[k]].y;
                            tmpp->nz = slices[k].v[svNumber[k]].z;
                        }
                        tmpp = &(slices[k].v[svNumber[k]]);
                        svNumber[k]++;
                        if(svNumber[k] >= MaxVertex)while(1);
                    }
                }
            }
        }
        for(i = 0; i < sliceNumber; i++) qsort(slices[i].v, svNumber[i], sizeof(Vertex), cmpVertex);
        #ifdef DBUGM
        printf("\n------ Slice Vertex ------\n");
        for(i = 0; i < sliceNumber; i++){
            printf("Slice %d: x = %lf\n", i, slices[i].x);
            for(j = 0; j < svNumber[i]; j++){
                ShowVertex(slices[i].v[j]);
            }
        }
        #endif
        /*For each slice.*/
            /*When a new vertex(triangle) coming , compare it to the top triangle. only calculate the top one's area*/
            /*When a vertex leave, if it is the top one, extract max to find another top one*/
        double area = 0;
        for(i = 0; i < sliceNumber-1; i++){
            #ifdef DBUGM
            printf("\n------ Slice %d -> %d : %2.2lf %2.2lf ------\n", i, i+1, slices[i].x, slices[i+1].x);
            #endif
            int valid[triangleNumber];
            for(j = 0; j < triangleNumber; j++) valid[j] = 0;
            int top = -1;
            Segment tmps1, tmps2;;
            double area2 = area;
            for(j = 0; j < svNumber[i]; j++){
                #ifdef DBUGM
                    printf("  line: %d/%d - Top: %d\n", j, svNumber[i], top);
                    printf("  Vertex: ");
                    ShowVertex(slices[i].v[j]);
                #endif

                if( slices[i].v[j].hasNext == 0)continue;
                if(top == -1) {
                    top = 1;
                    valid[slices[i].v[j].triangle] = 1;
                    FindLine2(slices[i].v[j], &tmps1);
                    continue;
                }
                int tmpTop = GetTop(tmps1, slices[i].v[j], valid);
                #ifdef DBUGM
                    printf("    Temp Top: %d\n", tmpTop);
                #endif
                if(tmpTop == -1){
                    valid[slices[i].v[j].triangle] = 1;
                    FindLine2(slices[i].v[j], &tmps1);
                    continue;
                }
                FindLine2(slices[i].v[j], &tmps2);
                double res = CalculateOriginalArea(tmps1, tmps2, slices[i+1].x - slices[i].x, tmpTop, i);
                area += res;
                if(i == roundT)
                    printf("res: %.7f\n", res);
                FindLine2(slices[i].v[j], &tmps1);
                valid[slices[i].v[j].triangle] = !valid[slices[i].v[j].triangle];
            }
            printf("%.10lf\n", area - area2);
        }
        printf("Case %d: %.2lf\n\n", caseNumber, area);
        caseNumber++;
    }
    return 0;
}
