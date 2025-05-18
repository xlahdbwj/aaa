/*
//1. 표현 가능한 이진트리
#include <string>
#include <vector>
#include <iostream>
using namespace std;

bool is_val(const string& binStr, int left, int right) { //이진탐색 트리
    if (left >= right) return true;
    int mid = (left + right) / 2;
    char root = binStr[mid];

    bool left_val = is_val(binStr, left, mid - 1);
    bool right_val = is_val(binStr, mid + 1, right);
    if (root == '0') {
        for (int i = left; i <= right; i++) {
            if (binStr[i] == '1') return false;
        }
    }
    return left_val && right_val;
}
vector<int> solution(vector<long long> numbers) {
    vector<int> answer;
    string binStr;
    int h, treeNode;
    long long tmp;
    for (long long n : numbers) {
        binStr = "";
        h = 0;
        tmp = n;
        while (tmp > 0) { //number을 이진수 문자열 형태로 바꿈
            binStr = to_string(tmp % 2) + binStr;
            tmp /= 2;
        }
        while ((1 << h) - 1 < binStr.length()) h++; //높이 구하기
        treeNode = (1 << h) - 1; //노드 개수 세기
        binStr = string(treeNode - binStr.length(), '0') + binStr; //노드개수-이진수문자열길이 만큼 0 채우기(0-padding)
        if (is_val(binStr, 0, binStr.length() - 1)) answer.push_back(1);
        else answer.push_back(0);
    }
    return answer;
}
int main() {
    vector<long long> answer = { 7,42,5 };
    vector<int> res=solution(answer);
    for (int i : res) {
        cout << i << ' ';
    }
    return 0;
}
*/
/*
//2. 길 찾기 게임

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct Node {
    int id, x, y;
    Node* left = nullptr;
    Node* right = nullptr;
    Node(int id, int x, int y) : id(id), x(x), y(y) {}
};

// 정렬 기준 함수
bool compareNodes(Node* a, Node* b) {
    if (a->y != b->y) return a->y > b->y;
    return a->x < b->x;
}

// 트리 추가 함수
Node* addNode(Node* current, Node* newNode) {
    if (current == nullptr) return newNode;

    if (newNode->x < current->x)
        current->left = addNode(current->left, newNode);
    else
        current->right = addNode(current->right, newNode);

    return current;
}

// 전위 순회
void preOrder(Node* node, vector<int>& traversal) {
    if (node == nullptr) return;
    traversal.push_back(node->id);
    preOrder(node->left, traversal);
    preOrder(node->right, traversal);
}

// 후위 순회
void postOrder(Node* node, vector<int>& traversal) {
    if (node == nullptr) return;
    postOrder(node->left, traversal);
    postOrder(node->right, traversal);
    traversal.push_back(node->id);
}

vector<vector<int>> solution(vector<vector<int>> nodeinfo) {
    vector<Node*> nodes;
    for (int i = 0; i < nodeinfo.size(); ++i) {
        nodes.push_back(new Node(i + 1, nodeinfo[i][0], nodeinfo[i][1]));
    }

    // y 큰 순 → x 작은 순 정렬
    sort(nodes.begin(), nodes.end(), compareNodes);

    Node* root = nullptr;
    for (Node* node : nodes) {
        root = addNode(root, node);
    }

    vector<int> pre;
    vector<int> post;
    preOrder(root, pre);
    postOrder(root, post);

    return { pre, post };
}
int main() {
    vector<vector<int>> nodeinfo = {
        {5,3},{11,5},{13,3},{3,5},{6,1},{1,3},{8,6},{7,2},{2,2}
    };

    vector<vector<int>> result = solution(nodeinfo);

    for (const auto& order : result) {
        for (int n : order) cout << n << " ";
        cout << "\n";
    }

    return 0;
}
*/
/*
//3. 예상 대진표 
#include <iostream>

using namespace std;

int solution(int n, int a, int b)
{
    int answer = 0;//2 3 만약 3번이 2라운드에 진출하게된다면 2번이 되야하므로 1을 더해야됨
    while (a != b) {
        a = (a + 1) / 2;
        b = (b + 1) / 2;
        answer++;
    }


    return answer;
}
*/
/*
//4. 다단계 칫솔 판매 
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

vector<int> solution(vector<string> enroll, vector<string> referral, vector<string> seller, vector<int> amount) {
    vector<int> answer;
    unordered_map<string, string>m; //이름,추천인
    unordered_map<string, int>total; //이름,금액
    for (int i = 0; i < enroll.size(); i++) {
        m[enroll[i]] = referral[i];
        total[enroll[i]] = 0;
    }
    for (int i = 0; i < seller.size(); i++) {
        int money = amount[i] * 100;
        string cur_name = seller[i];
        while (money > 0 && cur_name != "-") {
            int div = money / 10;
            total[cur_name] += money - div;
            if (m.find(cur_name) != m.end())
                cur_name = m[cur_name];
            else break;
            money = div;
        }

    }
    for (string s : enroll) {
        answer.push_back(total[s]);
    }

    return answer;
}
*/
//5. 미로 탈출
/*
#include <string>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int,int> par;
struct Node{
  int x,y,dist;  //dist: 거리
};
int dx[]={-1,1,0,0};
int dy[]={0,0,-1,1}; //상하좌우
//BFS 탐색
int BFS(par start,char a,vector<string> maps){
    queue<Node> q;
    vector<vector<bool>>visited(maps.size(),vector<bool>(maps[0].size(),false));
    q.push({start.first,start.second,0});
    visited[start.first][start.second]=true;
    while(!q.empty()){
        Node cur=q.front();
        q.pop();
        if(maps[cur.x][cur.y]==a) return cur.dist;

        for(int i=0;i<4;i++){
            int nx=cur.x+dx[i];
            int ny=cur.y+dy[i];

            if(nx>=0 && ny>=0 && nx<maps.size() && ny<maps[0].size() && visited[nx][ny]!=true && maps[nx][ny]!='X'){
                visited[nx][ny]=true;
                q.push({nx,ny,cur.dist+1});
            }
        }

    }
    return -1;
}
int solution(vector<string> maps) {
    int answer = 0,tmp;
    par start,l,exit;

    for(int i=0;i<maps.size();i++){
        for(int j=0;j<maps[0].size();j++){
            if(maps[i][j]=='S'){
                start={i,j};
            }
            else if(maps[i][j]=='L'){
                l={i,j};
            }
            else if(maps[i][j]=='E'){
                exit={i,j};
            }
        }
    }

    tmp=BFS(start,'L',maps);//시작점에서 레버로
    if(tmp==-1) return -1;
    answer=BFS(l,'E',maps); //레버에서 끝으로
    if(answer==-1) return -1;
    answer+=tmp;
    return answer;
}
*/

//6. 양과 늑대
//dfs ㄱㄱ
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

vector<vector<int>> tree;
int answer = 0;

void dfs(int node, int sheep, int wolf, vector<int> next, const vector<int>& info) {
    if (info[node] == 0) sheep++;
    else wolf++;

    if (wolf >= sheep) return;

    answer = max(answer, sheep);

    // 현재 방문한 노드를 next 목록에서 제거
    vector<int> newNext;
    for (int i : next) {
        if (i != node) newNext.push_back(i);
    }

    // 현재 노드의 자식들을 탐색 가능 노드에 추가
    for (int child : tree[node]) {
        newNext.push_back(child);
    }

    for (int i : newNext) {
        dfs(i, sheep, wolf, newNext, info);
    }
}

int solution(vector<int> info, vector<vector<int>> edges) {
    tree = vector<vector<int>>(info.size());

    for (auto& e : edges) {
        tree[e[0]].push_back(e[1]);
    }

    vector<int> next = { 0 }; // 루트 노드부터 시작
    dfs(0, 0, 0, next, info);

    return answer;
}
int main() {
    vector<int> info = { 0,0,1,1,1,0,1,0,1,0,1,1 };
    vector<vector<int>> edges = {
        {0,1},{1,2},{1,4},{0,8},{8,7},{9,10},{9,11},
        {4,3},{6,5},{4,6},{8,9}
    };

    cout << solution(info, edges) << endl; // 결과: 5
    return 0;
}
