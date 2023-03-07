#include <iostream>
using namespace std;

const int INF = 987654321;
int a[104][104], ret = INF, n = 10, paper[6];

bool check(int y, int x, int cnt){//색종이를 붙일 수 있는지 check
    if(y + cnt > n || x + cnt > n) return false;
    for(int i = y; i < y + cnt; i++){
        for(int j = x; j < x + cnt; j++){
            if(a[i][j] == 0) return false;
        }
    }
    return true;
}

void draw(int y, int x, int cnt, int value){//value 0 : 색종이 붙이기, value 1 : 색종이 떼기
    for(int i = y; i < y + cnt; i++){
        for(int j = x; j < x + cnt; j++){
            a[i][j] = value;
        }
    }    
}

void dfs(int y, int x, int cnt){
    if(cnt >= ret) return;//중요!! 이 문제는 '최솟값' 찾는거임(최솟값 : 최대 -> 최소, 최댓값 : 최소 - >최대)
    if(x == n){//x축 우선 탐색
        dfs(y + 1, 0, cnt);
        return;
    }
    if(y == n){
        ret = min(cnt, ret);
        return;
    }
    if(a[y][x] == 0){
        dfs(y, x + 1, cnt);
        return;
    }

    for(int size_ = 5; size_ >= 1; size_--){
        if(paper[size_] == 5) continue;//종이 수 초과
        if(!check(y, x, size_)) continue;//붙일 수 없는 영역
        paper[size_]++;
        draw(y, x, size_, 0);//색종이 붙이기
        dfs(y, x + size_, cnt + 1);
        draw(y, x, size_, 1);//색종이 떼기(각 가지마다 독립 시행을 위해!)
        paper[size_]--;
    }
    return;
}
int main(){
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            cin >> a[i][j];
        }
    } 
    dfs(0, 0, 0);
    cout << (ret == INF ? -1 : ret) << "\n";
    return 0;
}