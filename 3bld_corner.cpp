#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <functional>
#include <numeric>
#include <algorithm>
#include <set>
using namespace std;

struct Cube
{
    static bool initialized;
    static map<string, vector<int>> moves;

    string C;

    Cube();
    void move(string m);
    void move(vector<string> m);
    string format(bool color=false) const;
};

bool Cube::initialized;
map<string, vector<int>> Cube::moves;

Cube::Cube()
{
    if (!initialized)
    {
        initialized = true;

        moves["R"] = vector<int>{ 0,  1, 20,  3,  4, 23,  6,  7, 26, 15, 12,  9, 16, 13, 10, 17, 14, 11, 18, 19, 29, 21, 22, 32, 24, 25, 35, 27, 28, 51, 30, 31, 48, 33, 34, 45, 36, 37, 38, 39, 40, 41, 42, 43, 44,  8, 46, 47,  5, 49, 50,  2, 52, 53};
        moves["L"] = vector<int>{53,  1,  2, 50,  4,  5, 47,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17,  0, 19, 20,  3, 22, 23,  6, 25, 26, 18, 28, 29, 21, 31, 32, 24, 34, 35, 42, 39, 36, 43, 40, 37, 44, 41, 38, 45, 46, 33, 48, 49, 30, 51, 52, 27};
        moves["U"] = vector<int>{ 6,  3,  0,  7,  4,  1,  8,  5,  2, 45, 46, 47, 12, 13, 14, 15, 16, 17,  9, 10, 11, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 18, 19, 20, 39, 40, 41, 42, 43, 44, 36, 37, 38, 48, 49, 50, 51, 52, 53};
        moves["D"] = vector<int>{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 24, 25, 26, 18, 19, 20, 21, 22, 23, 42, 43, 44, 33, 30, 27, 34, 31, 28, 35, 32, 29, 36, 37, 38, 39, 40, 41, 51, 52, 53, 45, 46, 47, 48, 49, 50, 15, 16, 17};
        moves["F"] = vector<int>{ 0,  1,  2,  3,  4,  5, 44, 41, 38,  6, 10, 11,  7, 13, 14,  8, 16, 17, 24, 21, 18, 25, 22, 19, 26, 23, 20, 15, 12,  9, 30, 31, 32, 33, 34, 35, 36, 37, 27, 39, 40, 28, 42, 43, 29, 45, 46, 47, 48, 49, 50, 51, 52, 53};
        moves["B"] = vector<int>{11, 14, 17,  3,  4,  5,  6,  7,  8,  9, 10, 35, 12, 13, 34, 15, 16, 33, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 36, 39, 42,  2, 37, 38,  1, 40, 41,  0, 43, 44, 51, 48, 45, 52, 49, 46, 53, 50, 47};
        moves["M"] = vector<int>{ 0, 52,  2,  3, 49,  5,  6, 46,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18,  1, 20, 21,  4, 23, 24,  7, 26, 27, 19, 29, 30, 22, 32, 33, 25, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 34, 47, 48, 31, 50, 51, 28, 53};
        moves["S"] = vector<int>{ 0,  1,  2, 43, 40, 37,  6,  7,  8,  9,  3, 11, 12,  4, 14, 15,  5, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 16, 13, 10, 33, 34, 35, 36, 30, 38, 39, 31, 41, 42, 32, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53};
        moves["E"] = vector<int>{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 21, 22, 23, 15, 16, 17, 18, 19, 20, 39, 40, 41, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 48, 49, 50, 42, 43, 44, 45, 46, 47, 12, 13, 14, 51, 52, 53};
         //moves["?"] = vector<int>{ 0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53};

        auto composite = [&](vector<string> M)
        {
            vector<int> V(54);
            for (int i=0; i<54; i++)
                V[i] = i;
            for (string m: M)
            {
                vector<int> T(54);
                T.swap(V);
                for (int i=0; i<54; i++)
                    V[i] = T[moves[m][i]];
            }
            return V;
        };

        moves["r"] = composite({"R", "M", "M", "M"});
        moves["l"] = composite({"L", "M"});
        moves["u"] = composite({"U", "E", "E", "E"});
        moves["d"] = composite({"D", "E"});
        moves["f"] = composite({"F", "S"});
        moves["b"] = composite({"B", "S", "S", "S"});
        moves["x"] = composite({"L", "L", "L", "r"});
        moves["y"] = composite({"U", "d", "d", "d"});
        moves["z"] = composite({"F", "b", "b", "b"});

        for (string m: vector<string>{"R", "L", "U", "D", "F", "B", "M", "S", "E", "r", "l", "u", "d", "f", "b", "x", "y", "z"})
        {
            moves[m+"2"] = composite({m, m});
            moves[m+"'"] = composite({m, m, m});
        }
    }

    C = "UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB";
}

void Cube::move(string m)
{
    string tmp(54, '.');
    for (int i=0; i<(int)m.size();)
    {
        bool found = false;
        for (int l=3; l>=1; l--)
            if (i+l<=(int)m.size() && moves.count(m.substr(i, l))>0)
            {
                vector<int> &M = moves[m.substr(i, l)];
                tmp.swap(C);
                for (int i=0; i<54; i++)
                    C[i] = tmp[M[i]];
                i += l;
                found = true;
                break;
            }
        if (!found)
            i++;
    }
}

void Cube::move(vector<string> m)
{
    move(accumulate(m.begin(), m.end(), string()));
}

string Cube::format(bool color/*=false*/) const
{
    const static int T[9][12] = {
        {-1, -1, -1,  0,  1,  2, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1,  3,  4,  5, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1,  6,  7,  8, -1, -1, -1, -1, -1, -1},
        {36, 37, 38, 18, 19, 20,  9, 10, 11, 45, 46, 47},
        {39, 40, 41, 21, 22, 23, 12, 13, 14, 48, 49, 50},
        {42, 43, 44, 24, 25, 26, 15, 16, 17, 51, 52, 53},
        {-1, -1, -1, 27, 28, 29, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, 30, 31, 32, -1, -1, -1, -1, -1, -1},
        {-1, -1, -1, 33, 34, 35, -1, -1, -1, -1, -1, -1},
    };

    string r;
    for (int y=0; y<9; y++)
    {
        for (int x=0; x<12; x++)
            if (T[y][x]>=0)
                r += C[T[y][x]];
            else
                r += " ";
        r += "\n";
    }

    if (color)
    {
        string t = r;
        r = "";
        for (char c: t)
            if (false);
            else if (c=='U') r += "\x1b[47m  \x1b[0m";
            else if (c=='R') r += "\x1b[41m  \x1b[0m";
            else if (c=='F') r += "\x1b[42m  \x1b[0m";
            else if (c=='D') r += "\x1b[43m  \x1b[0m";
            else if (c=='L') r += "\x1b[45m  \x1b[0m";
            else if (c=='B') r += "\x1b[44m  \x1b[0m";
            else if (c=='\n') r+= '\n';
            else r += c, r += c;
    }

    return r;
}

int main()
{
    /*
    Cube c;
    vector<string> M = {"R", "L", "U", "D", "F", "B", "M", "S", "E", "r", "l", "u", "d", "f", "b", "x", "y", "z"};
    M.insert(M.end(), M.begin(), M.end());
    random_shuffle(M.begin(), M.end());
    for (auto m: M)
    {
        cout<<m<<endl;
        c.move(m);
        cout<<c.format(true)<<endl;
    }
    */

    vector<string> cands = {
        "R", "R2", "R'",
        "L", "L2", "L'",
        "U", "U2", "U'",
        "D", "D2", "D'",
        "F", "F2", "F'",
        "B", "B2", "B'",
    };

    //                          0,  1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53
    const static int EI[54] = {-1,  0, -1,  1, -1,  2, -1,  3, -1, -1,  2, -1,  5, -1,  6, -1, 10, -1, -1,  3, -1,  4, -1,  5, -1,  8, -1, -1,  8, -1,  9, -1, 10, -1, 11, -1, -1,  1, -1,  7, -1,  4, -1,  9, -1, -1,  0, -1,  6, -1,  7, -1, 11, -1};
    const static int CI[54] = { 0, -1,  1, -1, -1, -1,  2, -1,  3,  3, -1,  1, -1, -1, -1,  5, -1,  7,  2, -1,  3, -1, -1, -1,  4, -1,  5,  4, -1,  5, -1, -1, -1,  6, -1,  7,  0, -1,  2, -1, -1, -1,  6, -1,  4,  1, -1,  0, -1, -1, -1,  7, -1,  6};
    const static char * const EN[12] = {"UB", "UL", "UR", "UF", "FL", "FR", "BR", "BL", "DF", "DL", "DR", "DB"};
    const static char * const CN[8] = {"ULB", "UBR", "UFL", "URF", "DLF", "DFR", "DBL", "DRB"};

    for (int len=1; ; len++)
    {
        cout<<"len: "<<len<<endl;

        bool found = false;
        vector<string> moves;
        Cube init;
        Cube cube;
        vector<set<string>> visit(len);

        function<void()> f = [&]()
        {
            if ((int)moves.size()==len)
            {
                // UBエッジ、ULエッジ、LBエッジのうち2個と、UBLコーナーともう1個のコーナーが揃っていなければ良い。
                bool E[12] = {};
                bool C[8] = {};

                for (int i=0; i<54; i++)
                    if (cube.C[i]!=init.C[i])
                    {
                        if (EI[i]>=0)
                            E[EI[i]] = true;
                        if (CI[i]>=0)
                            C[CI[i]] = true;
                    }

                int en = 0;
                for (bool e: E)
                    if (e)
                        en++;
                int cn = 0;
                for (bool c: C)
                    if (c)
                        cn++;
                if (en==2 && cn==2 && C[0] && (E[0]&& E[1] || E[1]&&E[7] || E[7]&&E[0]))
                //if (cn==2 && C[0])
                {
                    // 2回繰り返して初期状態に戻ることを確認する。
                    // 最初の判定だと、2個のエッジが位置を変えずに回転しているものも通してしまうが、これで弾けるはず。
                    Cube tmp;
                    tmp.move(moves);
                    tmp.move(moves);
                    if (tmp.C == init.C)
                    {
                        found = true;

                        for (int i=0; i<8; i++)
                            if (C[i])
                            {
                                cout<<" "<<CN[i];
                                if (i==0)
                                    cout<<"("<<cube.C[0]<<cube.C[36]<<cube.C[47]<<")";
                            }
                        for (int i=0; i<12; i++)
                            if (E[i])
                                cout<<" "<<EN[i];
                        cout<<":";
                        //cout<<cube.format(true)<<endl;
                        for (string m: moves)
                            cout<<" "<<m;
                        cout<<endl;
                    }
                }

                return;
            }

            // 枝刈り。
            // 1手で揃うピースは、エッジもコーナーも最大4個なので、残り手数的に足りなければ不可。
            // 判定時にエッジを無制限にするときはここも修正が必要。
            int rest = len-(int)moves.size();
            if (rest<=3)
            {
                bool E[12] = {};
                bool C[8] = {};

                for (int i=0; i<54; i++)
                    if (cube.C[i]!=init.C[i])
                    {
                        if (EI[i]>=0)
                            E[EI[i]] = true;
                        if (CI[i]>=0)
                            C[CI[i]] = true;
                    }
                int en = 0;
                for (bool e: E)
                    if (e)
                        en++;
                int cn = 0;
                for (bool c: C)
                    if (c)
                        cn++;
                if (en>2+rest*4 ||
                    cn>2+rest*4)
                    return;
            }

            for (int i=0; i<(int)cands.size(); i++)
            {
                //if (moves.size()==0 && cands[i]!="R" ||
                //    moves.size()==1 && cands[i]!="U" ||
                //    moves.size()==2 && cands[i]!="R'")
                //    continue;

                if (moves.size()>0 && (
                    moves[moves.size()-1][0]==cands[i][0] ||
                    moves[moves.size()-1][0]=='R' && cands[i][0]=='L' ||
                    moves[moves.size()-1][0]=='D' && cands[i][0]=='U' ||
                    moves[moves.size()-1][0]=='B' && cands[i][0]=='F'))
                    continue;

                moves.push_back(cands[i]);
                string old = cube.C;
                cube.move(cands[i]);
                
                f();

                moves.pop_back();
                //cube.move(cands[i/3*3+2-i%3]);
                cube.C = old;
            }
        };
        f();

        //cout<<(double)clock()/CLOCKS_PER_SEC<<endl;

        if (found)
            break;
    }
}
