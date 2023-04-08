// ==============  [ 과제#2 : 허프만 인코딩 & 디코딩 ]  ==============
//                 
// 제출일자 : 2021-11-12                          작성자 : 2020039004 최문형
// 개발환경 : vscode에서 gcc(version : 6.3.0) 컴파일러 환경에서 코드를 짰습니다.
//
//
// 과제 요구 사항 :
//   허프만 코드 방법을 사용해서 문자열을 인코딩, 디코딩 하는 프로그램을 만드시오. 
//      - 입력값은 알파벳이다. (특수문자, 숫자는 허용하지 않음)
//      - 대/소문자는 구별
//      - 입력된 알파벳 문자열을 이진 스트링(binary string)으로 encoding
//      - 인코딩된 이진 스트링을 다시 알파벳 문자열로 decoding
//      - C 또는 C++  GCC 컴파일러로 구현
// ===========================================================================


#include <iostream>
#include <string>

#define MAXALPHA 52

using namespace std;

typedef struct _TreeNode {    // tree에 들어가는 정보들
    char data;                // huffman tree에서 리프노드가 가지는 알파벳
    struct _TreeNode* left;   // huffman tree에서 왼쪽 자식을 관리하기 위한 포인터
    struct _TreeNode* right;  // huffman tree에서 오른쪽 자식을 관리하기 위한 포인터
} TreeNode;

typedef struct _PqNode { // 우선순위 큐에 들어가는 정보들
    int cnt; // frequency 저장용 변수
    TreeNode* tree; // huffman tree를 저장하기 위한 변수
} PqNode;


// 사용자 정의 함수 목록
// encoding
void swap(PqNode& a, PqNode& b);  // 우선순위 큐에서 두 노드를 스왑해주기 위한 함수
void push(PqNode(&pq)[MAXALPHA + 1], int& top, int cnt, char data); // 우선순위 큐에서 리프노드들을 push해주기 위한 함수
void push(PqNode(&pq)[MAXALPHA + 1], int& top, int cnt, TreeNode* tree); // 우선순위 큐에서 두 노드를 합친 subtree를 push해주기 위한 함수
TreeNode* pop(PqNode(&pq)[MAXALPHA + 1], int& top); // 우선순위 큐에서 priority가 가장 큰 값을 pop 해주기 위한 함수
void makeBinaryTable(TreeNode* root, string* table, string binary); // encoding을 위하여 Codeword table을 만들어주는 함수
string encoding(string& input, TreeNode** rootNode); // 사용자로부터 입력받은 string을 encoding 해주기 위한 함수

// decoding
char decodetrave(const string& binaryStr, int& top, TreeNode* search); // huffman tree를 이용하여 binary code를 다시 decoding해주는 함수
string decoding(string& binaryStr, TreeNode* root); // decoding을 해주기 위한 함수


int main(void)
{
    TreeNode* rootNode = NULL;
    string input, binaryStr;

    // 사용자로부터 문자열 입력받기
    cout << "Put the string to encode: ";
    //cin >> input; // 사용자로부터 string을 입력받는다.
    getline(cin, input);

    cout << "encoding...\n\n";

    binaryStr = encoding(input, &rootNode);
    cout << "Encoded result:" << binaryStr << "\n";
    cout << "decoding...\n\n";

    cout << "Decoded result: " << decoding(binaryStr, rootNode);

    return 0;
}


// 우선순위 큐에서 두 노드를 스왑해주기 위한 함수
void swap(PqNode& a, PqNode& b)
{
    PqNode temp = a;
    a = b;
    b = temp;
}

// 우선순위 큐에서 리프노드들을 push해주기 위한 함수
void push(PqNode(&pq)[MAXALPHA + 1], int& top, int cnt, int data)
{
    pq[++top].cnt = cnt;

    pq[top].tree = (TreeNode*)malloc(sizeof(TreeNode));
    pq[top].tree->right = NULL; // 여기서 만들어지는 노드들은 리프노드이므로 왼쪽 자식과 오른쪽 자식을 NULL 값으로 선언해준다.
    pq[top].tree->left = NULL;

    if (data < 26) // 소문자일 경우,
        pq[top].tree->data = (char)('a' + data);
    else // 대문자일 경우
        pq[top].tree->data = (char)('A' + (data - 26));

    // 우선순위 큐는 최소힙으로 구현되어야 함.
    int topTmp = top;
    while (topTmp != 1) // topTmp가 root가 될 때까지 반복
    {
        if (pq[topTmp].cnt < pq[topTmp / 2].cnt) // 부모노드보다 해당 알파벳의 frequency가 작다면 스왑
            swap(pq[topTmp], pq[topTmp / 2]);
        else
            break;

        topTmp /= 2;
    }
}

// 우선순위 큐에서 두 노드를 합친 subtree를 push해주기 위한 함수
void push(PqNode(&pq)[MAXALPHA + 1], int& top, int cnt, TreeNode* tree)
{
    pq[++top] = { cnt, tree };

    // 우선순위 큐는 최소힙으로 구현되어야 함.
    int topTmp = top;
    while (topTmp != 1) // topTmp가 root가 될 때까지 반복
    {
        if (pq[topTmp].cnt < pq[topTmp / 2].cnt) // 부모노드보다 해당 알파벳의 frequency가 작다면 스왑
            swap(pq[topTmp], pq[topTmp / 2]);
        else
            break;

        topTmp /= 2; // 다음 탐색에선 현재 노드의 부모노드를 기준으로 탐색하도록 인덱스를 설정함.
    }
}

// 우선순위 큐에서 priority가 가장 큰 값을 pop 해주기 위한 함수
TreeNode* pop(PqNode(&pq)[MAXALPHA + 1], int& top)
{
    // 여기에서 TreeNode에 data를 넣어줘야 함.
    TreeNode* popNode = pq[1].tree;
    swap(pq[1], pq[top--]);

    int topTmp = 1;
    while (topTmp < top)
    {
        // 두 자식노드 간의 우선순위 비교
        if ((topTmp * 2) + 1 <= top) // 일단은 오른쪽 자식이 있는지부터 확인하기
        {
            if (pq[topTmp * 2].cnt < pq[(topTmp * 2) + 1].cnt) // 왼쪽 자식의 우선순위가 더 크다면
            {
                if (pq[topTmp * 2].cnt < pq[topTmp].cnt) // 루트랑 왼쪽 자식이랑 비교
                {
                    swap(pq[topTmp * 2], pq[topTmp]);
                    topTmp *= 2;
                }

                else
                    break;
            }

            else // 오른쪽 자식의 우선순위가 더 클 경우
            {
                if (pq[(topTmp * 2) + 1].cnt < pq[topTmp].cnt) // 오른쪽 자식이랑 비교하기
                {
                    swap(pq[(topTmp * 2) + 1], pq[topTmp]);
                    topTmp = (topTmp * 2) + 1;
                }

                else
                    break;
            }
        }

        // 왼쪽자식밖에 없을 경우
        else if (topTmp * 2 <= top && pq[topTmp * 2].cnt < pq[topTmp].cnt) // 왼쪽 자식이랑 비교하기       
        {
            swap(pq[topTmp * 2], pq[topTmp]);
            topTmp *= 2;
        }

        else
            break;
    }

    return popNode;
}

// encoding을 위하여 Codeword table을 만들어주는 함수
void makeBinaryTable(TreeNode* root, string* table, string binary)
{
    // 리프노드까지 내려왔다면, table 갱신
    if (root->left == NULL && root->right == NULL)
    {
        // cout << root->data << " : " << binary << "\n";  // Binary Code가 잘 만들어졌는지 확인하기

        // 해당 알파벳에 대하여 binary code를 저장하기
        if ('a' <= root->data && root->data <= 'z')
            table[root->data - 'a'] = binary;
        else
            table[root->data - 'A' + 26] = binary;

        return; // 함수 종료
    }

    makeBinaryTable(root->left, table, binary + '0');  // huffman tree에서 왼쪽 자식으로 이동했다면 현재 string에 '0'을 추가
    makeBinaryTable(root->right, table, binary + '1'); // huffman tree에서 오른쪽 자식으로 이동했다면 현재 string에 '1'을 추가
}

// 사용자로부터 입력받은 string을 encoding 해주기 위한 함수
string encoding(string& input, TreeNode** rootNode)
{
    // get Frequency table
    int table[MAXALPHA] = { 0, }; // frequency table 생성
    for (int i = 0; i < input.length(); i++)
    {
        // 해당 알파벳이 몇 번 들어왔는지를 계산함.
        if ('a' <= input[i] && input[i] <= 'z')
            table[input[i] - 'a']++;
        else
            table[input[i] - 'A' + 26]++;
    }
    // frequency table 생성 완료


    // pq.push();
    PqNode pq[MAXALPHA + 1]; // frequency 게산이 끝났으므로 이 table에 대한 우선순위 큐 생성
    int top = 0;
    for (int i = 0; i < MAXALPHA; i++) // table의 정보들을 우선순위큐에 넣기
        if (table[i] != 0) // 해당 알파벳이 1개 이상 들어왔다면 우선순위 큐에 삽입
        {
            // cout << table[i] << " ";  // frequency table이 잘 만들어 졌는지 확인하기
            push(pq, top, table[i], i);
        }
    // 초기 우선순위 큐 생성 완료


    // 우선순위 큐 확인
    // cout << "\n";
    // for (int i = 1; i <= top; i++)
    //     cout << pq[i].tree->data << " " << pq[i].cnt << "\n";


    // 알파벳이 하나만 주어진 경우, 이 경우에서는 rootNode만 생성이 됨 -> 예외처리
    if (top == 1) // 우선순위 큐의 사이즈가 1이라면, 알파벳이 하나로만 입력으로 주어진 경우임
    {
        (*rootNode) = pq[1].tree;
        string binaryStr = "";

        for (int i = 0; i < input.length(); i++)
            binaryStr += "1";

        return binaryStr;
    }


    // 우선순위 큐로부터 frequency가 적은 것을 가져와 subtree 생성
    int cntSum;
    TreeNode* left, * right;
    while (top != 1) // top이 1일 경우, tree 생성 완료
    {
        // pq[1] = rootNode
        cntSum = pq[1].cnt;   // 우선순위 큐에서 frequency가 제일 작은 alphabet 선택하여 cutSum에 대입
        left = pop(pq, top); // 그리고 새로운 subtree를 만들기 위해 우선순위 큐에서 pop한 후, 왼쪽자식으로 설정

        cntSum += pq[1].cnt;  // 또 우선순위 큐에서 frequency가 제일 작은 alphabet 선택하여 cntSum에 현재 frequency 더하기
        right = pop(pq, top); // 그리고 새로운 subtree를 만들기 위해 우선순위 큐에서 pop한 후, 오른쪽자식으로 설정

        // 이렇게 해서 만들어진 새로운 노드를 tree에 저장해야함.
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = ' ';
        newNode->left = left;
        newNode->right = right;

        push(pq, top, cntSum, newNode); // 두 alphabet을 합친 새로운 alphabet을 생성 후, 다시 우선순위 큐에 저장
    }
    (*rootNode) = pq[1].tree;
    // Huffman tree 생성완료


    // Binary code table 만들기
    string binaryTable[MAXALPHA]; // binary table을 위한 string 배열 선언
    makeBinaryTable(*rootNode, binaryTable, ""); // Huffman tree를 이용하여 binary table 만들기
    // Binary code table 생성완료


    // encoding 하기
    string binaryStr = ""; // encoding의 결과값을 저장하기 위한 string 변수 선언
    for (int i = 0; i < input.length(); i++) // 사용자가 입력한 string의 크기만큼 반복
    {
        if ('a' <= input[i] && input[i] <= 'z') // 소문자일 경우,
            binaryStr += binaryTable[input[i] - 'a']; // 현재 alphabet에 해당하는 table로 가서 binary 형태로 변환한다. ( 이 값을 binaryStr에 대입 )
        else // 대문자일 경우
            binaryStr += binaryTable[input[i] - 'A' + 26]; // 현재 alphabet에 해당하는 table로 가서 binary 형태로 변환한다. ( 이 값을 binaryStr에 대입 )
    }
    // encoding 완료

    return binaryStr;
}

// huffman tree를 이용하여 binary code를 다시 decoding해주는 함수
char decodetrave(const string& binaryStr, int& top, TreeNode* search)
{
    while (true)
    {
        // 리프노드까지 내려왔다면, 해당 문자 반환
        if (search->left == NULL && search->right == NULL)
            return search->data;

        // 현재 binary 값이 0일 경우, 왼쪽 자식으로 이동
        if (binaryStr[top] == '0')
            search = search->left;
        // 현재 binary 값이 1일 경우, 오른쪽 자식으로 이동
        else if (binaryStr[top] == '1')
            search = search->right;

        top++; // 다음 binary code를 확인하도록 top을 증가시켜줌.
    }
}

// decoding을 해주기 위한 함수
string decoding(string& binaryStr, TreeNode* root)
{
    int top = 0; // binary code를 순회하기 위한 index 관리용 변수 선언
    string decodeStr = ""; // decode된 문자열을 저장하기 위한 string 변수 선언

    // 입력으로 알파벳 하나만 주어진 경우, 이 경우에서는 rootNode만 생성이 됨 -> 예외처리
    if (root->left == NULL && root->right == NULL)
    {
        for (int i = 0; i < binaryStr.length(); i++)
            decodeStr += root->data;

        return decodeStr;
    }

    while (top < binaryStr.length()) // top이 모든 binary code를 해석할 때까지 반복
        decodeStr += decodetrave(binaryStr, top, root); // 한 개의 alphabet이 decode 되도록 하는 함수 실행 (이 함수의 결과값을 decodeStr에 더해준다.)

    return decodeStr; // decode 된 문자열을 반환한다.
}