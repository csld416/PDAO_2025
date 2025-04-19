#include <bits/stdc++.h>
using namespace std;

static const int ROWS = 10;
static const int COLS = 9;

struct Move { int r1, c1, r2, c2; };

inline bool in_bounds(int r, int c) {
    return r>=0 && r<ROWS && c>=0 && c<COLS;
}
inline bool inside_palace(int r, int c, bool isBlack){
    if (isBlack)  return r<=2 && c>=3 && c<=5;
    else          return r>=7 && c<=9 && c>=3 && c<=5;
}
inline bool crossed_river(int r, bool isBlack){
    return isBlack ? (r>=5) : (r<=4);
}

// Generate all legal moves (including captures) for the side `isBlack`
vector<Move> genMoves(const vector<string>& B, bool isBlack){
    vector<Move> M;
    auto opp = [&](int r,int c)->bool{
        char p = B[r][c];
        if (p == '.') return false;
        // uppercase = Black, lowercase = Red
        return (isupper(p)!=0) ^ isBlack;
    };
    for(int r=0; r<ROWS; r++){
        for(int c=0; c<COLS; c++){
            char p = B[r][c];
            if (p=='.') continue;
            bool pIsBlack = isupper(p);
            if (pIsBlack != isBlack) continue;
            char pt = tolower(p);

            // ---- GENERAL ----
            if (pt=='g'){
                static int dr[4]={1,-1,0,0}, dc[4]={0,0,1,-1};
                // one step in palace
                for(int d=0; d<4; d++){
                    int nr=r+dr[d], nc=c+dc[d];
                    if(!in_bounds(nr,nc)) continue;
                    if(!inside_palace(nr,nc,isBlack)) continue;
                    if (B[nr][nc]=='.' || opp(nr,nc))
                        M.push_back({r,c,nr,nc});
                }
                // flying general
                for(int rr=0; rr<ROWS; rr++){
                    if (B[rr][c] == (isBlack?'g':'G')){
                        int step = (rr>r?1:-1);
                        bool block=false;
                        for(int tr=r+step; tr!=rr; tr+=step){
                            if (B[tr][c] != '.') { block=true; break; }
                        }
                        if (!block) M.push_back({r,c,rr,c});
                    }
                }
            }
            // ---- ADVISOR ----
            else if (pt=='s'){
                static int dr[4]={1,1,-1,-1}, dc[4]={1,-1,1,-1};
                for(int d=0; d<4; d++){
                    int nr=r+dr[d], nc=c+dc[d];
                    if(!in_bounds(nr,nc)) continue;
                    if(!inside_palace(nr,nc,isBlack)) continue;
                    if (B[nr][nc]=='.' || opp(nr,nc))
                        M.push_back({r,c,nr,nc});
                }
            }
            // ---- ELEPHANT ----
            else if (pt=='e'){
                static int dr[4]={2,2,-2,-2}, dc[4]={2,-2,2,-2};
                for(int d=0; d<4; d++){
                    int nr=r+dr[d], nc=c+dc[d];
                    if(!in_bounds(nr,nc)) continue;
                    // river
                    if(isBlack? nr>4 : nr<5) continue;
                    // eye
                    if (B[r+dr[d]/2][c+dc[d]/2] != '.') continue;
                    if (B[nr][nc]=='.' || opp(nr,nc))
                        M.push_back({r,c,nr,nc});
                }
            }
            // ---- ROOK/CHARIOT ----
            else if (pt=='r'){
                static int dr[4]={1,-1,0,0}, dc[4]={0,0,1,-1};
                for(int d=0; d<4; d++){
                    for(int k=1;;k++){
                        int nr=r+dr[d]*k, nc=c+dc[d]*k;
                        if(!in_bounds(nr,nc)) break;
                        if (B[nr][nc]=='.'){
                            M.push_back({r,c,nr,nc});
                        } else {
                            if (opp(nr,nc))
                                M.push_back({r,c,nr,nc});
                            break;
                        }
                    }
                }
            }
            // ---- CANNON ----
            else if (pt=='c'){
                static int dr[4]={1,-1,0,0}, dc[4]={0,0,1,-1};
                for(int d=0; d<4; d++){
                    // flat move
                    for(int k=1;;k++){
                        int nr=r+dr[d]*k, nc=c+dc[d]*k;
                        if(!in_bounds(nr,nc)) break;
                        if (B[nr][nc]=='.')
                            M.push_back({r,c,nr,nc});
                        else break;
                    }
                    // capture over exactly one screen
                    bool jumped=false;
                    for(int k=1;;k++){
                        int nr=r+dr[d]*k, nc=c+dc[d]*k;
                        if(!in_bounds(nr,nc)) break;
                        if(!jumped){
                            if (B[nr][nc] != '.') jumped=true;
                        } else {
                            if (B[nr][nc] != '.'){
                                if (opp(nr,nc))
                                    M.push_back({r,c,nr,nc});
                                break;
                            }
                        }
                    }
                }
            }
            // ---- HORSE ----
            else if (pt=='h'){
                static int dr[8]={-2,-2,2,2,-1,1,-1,1}, dc[8]={-1,1,-1,1,-2,-2,2,2};
                for(int d=0; d<8; d++){
                    int nr=r+dr[d], nc=c+dc[d];
                    if(!in_bounds(nr,nc)) continue;
                    int lr = (abs(dr[d])==2 ? r+dr[d]/2 : r);
                    int lc = (abs(dc[d])==2 ? c+dc[d]/2 : c);
                    if (B[lr][lc] != '.') continue;
                    if (B[nr][nc]=='.' || opp(nr,nc))
                        M.push_back({r,c,nr,nc});
                }
            }
            // ---- SOLDIER ----
            else if (pt=='p'){
                int fdr = isBlack? +1 : -1;
                int nr=r+fdr, nc=c;
                if (in_bounds(nr,nc) && (B[nr][nc]=='.' || opp(nr,nc)))
                    M.push_back({r,c,nr,nc});
                if (crossed_river(r,isBlack)){
                    for(int dd : {-1,+1}){
                        nr=r; nc=c+dd;
                        if(in_bounds(nr,nc) && (B[nr][nc]=='.' || opp(nr,nc)))
                            M.push_back({r,c,nr,nc});
                    }
                }
            }
        }
    }
    return M;
}

// can 'side' capture opponent's general in one move?
bool canCaptureGeneral(const vector<string>& B, bool side){
    char T = side?'g':'G';
    for(auto &m: genMoves(B, side)){
        if (B[m.r2][m.c2] == T) return true;
    }
    return false;
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> board(ROWS);
    for(int i=0;i<ROWS;i++) cin >> board[i];

    // Black-to-move: simulate every Black move
    for(auto &bm: genMoves(board, true)){
        // build new position
        auto nb = board;
        char pc = nb[bm.r1][bm.c1];
        nb[bm.r1][bm.c1] = '.';
        nb[bm.r2][bm.c2] = pc;

        // a) Black actually captured Red's general?
        if (board[bm.r2][bm.c2] == 'g') {
            cout << "No\n";
            return 0;
        }
        // b) Red must be able to capture Black's general immediately
        if (!canCaptureGeneral(nb, false)) {
            cout << "No\n";
            return 0;
        }
    }

    // If every Black reply loses the general next move, answer is Yes
    cout << "Yes\n";
    return 0;
}