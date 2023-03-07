#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int dice[10], ret, val[40], player[4];
vector<int> adj[40];

void set_map(){
    //set graph value
    val[0] = 0; val[21] = 0;
    for(int i = 1; i <= 20; i++) val[i] = i * 2;
    val[22] = 13; val[23] = 16; val[24] = 19; val[25] = 25;
    val[26] = 22; val[27] = 24; 
    val[28] = 28; val[29] = 27; val[30] = 26;
    val[31] = 30; val[32] = 35;
    //set graph
    for(int i = 0; i < 21; i++) adj[i].push_back(i + 1);
    adj[5].push_back(22); adj[10].push_back(26); adj[15].push_back(28);
    for(int i = 22; i < 25; i++) adj[i].push_back(i + 1);
    adj[26].push_back(27); adj[27].push_back(25);
    for(int i = 28; i < 30; i++) adj[i].push_back(i + 1);
    adj[30].push_back(25);
    adj[25].push_back(31); adj[31].push_back(32); adj[32].push_back(20);
    int index = 0;
}

int move(int who, int howmany){
    if(adj[player[who]].size() > 1){//파란색 칸에서 시작이면
        player[who] = adj[player[who]][1];//플레이어 위치 파란색 루트로 이동
        howmany--;
    }
    while(howmany > 0 && player[who] != 21){
        player[who] = adj[player[who]][0];//플레이어 위치 이동
        howmany--;
    }
    //이동이 끝났으면
    return val[player[who]];
}

int move_sim(int who, int howmany){//move 시뮬레이션
    int player_loc = player[who];
    if(adj[player[who]].size() > 1){//파란색 칸에서 시작이면
        player_loc = adj[player_loc][1];//플레이어 위치 파란색 루트로 이동
        howmany--;
    }
    while(howmany > 0 && player_loc != 21){
        player_loc = adj[player_loc][0];//플레이어 위치 이동
        howmany--;
    }
    //이동이 끝났으면
    return player_loc;
}

bool is_valid(int who, int dice_idx){
    if(player[who] == 21) return false;//현재 위치가 도착점이면
    int arrive = move_sim(who, dice[dice_idx]);//이동 후 위치
    if(arrive == 21) return true;//이동이 끝나는 점이 도착점이면
    else{//아니면 이동이 끝나는점에 다른 player가 있는지 확인
        for(int i = 0; i < 4; i++){
            if(i == who) continue;
            if(player[i] == arrive) return false;
        }
    }
    return true;
}

void game(int dice_idx, int sum){
    //기저조건
    if(dice_idx == 10){
        ret = max(ret, sum);
        return;
    } 
    //logic
    for(int i = 0; i < 4; i++){//말 선택
        if(is_valid(i, dice_idx)){ //가능한 말이면
            int temp_loc = player[i];
            game(dice_idx + 1, sum + move(i, dice[dice_idx]));
            player[i] = temp_loc;//독립 시행
        }
        else continue;
    }
    return;
}
int main(){
    for(int i = 0; i < 10; i++){
        cin >> dice[i];
    }
    set_map();
    game(0, 0);
    cout << ret << "\n";
    return 0;
}