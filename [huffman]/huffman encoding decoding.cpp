// ==============  [ ����#2 : ������ ���ڵ� & ���ڵ� ]  ==============
//                 
// �������� : 2021-11-12                          �ۼ��� : 2020039004 �ֹ���
// ����ȯ�� : vscode���� gcc(version : 6.3.0) �����Ϸ� ȯ�濡�� �ڵ带 ®���ϴ�.
//
//
// ���� �䱸 ���� :
//   ������ �ڵ� ����� ����ؼ� ���ڿ��� ���ڵ�, ���ڵ� �ϴ� ���α׷��� ����ÿ�. 
//      - �Է°��� ���ĺ��̴�. (Ư������, ���ڴ� ������� ����)
//      - ��/�ҹ��ڴ� ����
//      - �Էµ� ���ĺ� ���ڿ��� ���� ��Ʈ��(binary string)���� encoding
//      - ���ڵ��� ���� ��Ʈ���� �ٽ� ���ĺ� ���ڿ��� decoding
//      - C �Ǵ� C++  GCC �����Ϸ��� ����
// ===========================================================================


#include <iostream>
#include <string>

#define MAXALPHA 52

using namespace std;

typedef struct _TreeNode {    // tree�� ���� ������
    char data;                // huffman tree���� ������尡 ������ ���ĺ�
    struct _TreeNode* left;   // huffman tree���� ���� �ڽ��� �����ϱ� ���� ������
    struct _TreeNode* right;  // huffman tree���� ������ �ڽ��� �����ϱ� ���� ������
} TreeNode;

typedef struct _PqNode { // �켱���� ť�� ���� ������
    int cnt; // frequency ����� ����
    TreeNode* tree; // huffman tree�� �����ϱ� ���� ����
} PqNode;


// ����� ���� �Լ� ���
// encoding
void swap(PqNode& a, PqNode& b);  // �켱���� ť���� �� ��带 �������ֱ� ���� �Լ�
void push(PqNode(&pq)[MAXALPHA + 1], int& top, int cnt, char data); // �켱���� ť���� ���������� push���ֱ� ���� �Լ�
void push(PqNode(&pq)[MAXALPHA + 1], int& top, int cnt, TreeNode* tree); // �켱���� ť���� �� ��带 ��ģ subtree�� push���ֱ� ���� �Լ�
TreeNode* pop(PqNode(&pq)[MAXALPHA + 1], int& top); // �켱���� ť���� priority�� ���� ū ���� pop ���ֱ� ���� �Լ�
void makeBinaryTable(TreeNode* root, string* table, string binary); // encoding�� ���Ͽ� Codeword table�� ������ִ� �Լ�
string encoding(string& input, TreeNode** rootNode); // ����ڷκ��� �Է¹��� string�� encoding ���ֱ� ���� �Լ�

// decoding
char decodetrave(const string& binaryStr, int& top, TreeNode* search); // huffman tree�� �̿��Ͽ� binary code�� �ٽ� decoding���ִ� �Լ�
string decoding(string& binaryStr, TreeNode* root); // decoding�� ���ֱ� ���� �Լ�


int main(void)
{
    TreeNode* rootNode = NULL;
    string input, binaryStr;

    // ����ڷκ��� ���ڿ� �Է¹ޱ�
    cout << "Put the string to encode: ";
    //cin >> input; // ����ڷκ��� string�� �Է¹޴´�.
    getline(cin, input);

    cout << "encoding...\n\n";

    binaryStr = encoding(input, &rootNode);
    cout << "Encoded result:" << binaryStr << "\n";
    cout << "decoding...\n\n";

    cout << "Decoded result: " << decoding(binaryStr, rootNode);

    return 0;
}


// �켱���� ť���� �� ��带 �������ֱ� ���� �Լ�
void swap(PqNode& a, PqNode& b)
{
    PqNode temp = a;
    a = b;
    b = temp;
}

// �켱���� ť���� ���������� push���ֱ� ���� �Լ�
void push(PqNode(&pq)[MAXALPHA + 1], int& top, int cnt, int data)
{
    pq[++top].cnt = cnt;

    pq[top].tree = (TreeNode*)malloc(sizeof(TreeNode));
    pq[top].tree->right = NULL; // ���⼭ ��������� ������ ��������̹Ƿ� ���� �ڽİ� ������ �ڽ��� NULL ������ �������ش�.
    pq[top].tree->left = NULL;

    if (data < 26) // �ҹ����� ���,
        pq[top].tree->data = (char)('a' + data);
    else // �빮���� ���
        pq[top].tree->data = (char)('A' + (data - 26));

    // �켱���� ť�� �ּ������� �����Ǿ�� ��.
    int topTmp = top;
    while (topTmp != 1) // topTmp�� root�� �� ������ �ݺ�
    {
        if (pq[topTmp].cnt < pq[topTmp / 2].cnt) // �θ��庸�� �ش� ���ĺ��� frequency�� �۴ٸ� ����
            swap(pq[topTmp], pq[topTmp / 2]);
        else
            break;

        topTmp /= 2;
    }
}

// �켱���� ť���� �� ��带 ��ģ subtree�� push���ֱ� ���� �Լ�
void push(PqNode(&pq)[MAXALPHA + 1], int& top, int cnt, TreeNode* tree)
{
    pq[++top] = { cnt, tree };

    // �켱���� ť�� �ּ������� �����Ǿ�� ��.
    int topTmp = top;
    while (topTmp != 1) // topTmp�� root�� �� ������ �ݺ�
    {
        if (pq[topTmp].cnt < pq[topTmp / 2].cnt) // �θ��庸�� �ش� ���ĺ��� frequency�� �۴ٸ� ����
            swap(pq[topTmp], pq[topTmp / 2]);
        else
            break;

        topTmp /= 2; // ���� Ž������ ���� ����� �θ��带 �������� Ž���ϵ��� �ε����� ������.
    }
}

// �켱���� ť���� priority�� ���� ū ���� pop ���ֱ� ���� �Լ�
TreeNode* pop(PqNode(&pq)[MAXALPHA + 1], int& top)
{
    // ���⿡�� TreeNode�� data�� �־���� ��.
    TreeNode* popNode = pq[1].tree;
    swap(pq[1], pq[top--]);

    int topTmp = 1;
    while (topTmp < top)
    {
        // �� �ڽĳ�� ���� �켱���� ��
        if ((topTmp * 2) + 1 <= top) // �ϴ��� ������ �ڽ��� �ִ������� Ȯ���ϱ�
        {
            if (pq[topTmp * 2].cnt < pq[(topTmp * 2) + 1].cnt) // ���� �ڽ��� �켱������ �� ũ�ٸ�
            {
                if (pq[topTmp * 2].cnt < pq[topTmp].cnt) // ��Ʈ�� ���� �ڽ��̶� ��
                {
                    swap(pq[topTmp * 2], pq[topTmp]);
                    topTmp *= 2;
                }

                else
                    break;
            }

            else // ������ �ڽ��� �켱������ �� Ŭ ���
            {
                if (pq[(topTmp * 2) + 1].cnt < pq[topTmp].cnt) // ������ �ڽ��̶� ���ϱ�
                {
                    swap(pq[(topTmp * 2) + 1], pq[topTmp]);
                    topTmp = (topTmp * 2) + 1;
                }

                else
                    break;
            }
        }

        // �����ڽĹۿ� ���� ���
        else if (topTmp * 2 <= top && pq[topTmp * 2].cnt < pq[topTmp].cnt) // ���� �ڽ��̶� ���ϱ�       
        {
            swap(pq[topTmp * 2], pq[topTmp]);
            topTmp *= 2;
        }

        else
            break;
    }

    return popNode;
}

// encoding�� ���Ͽ� Codeword table�� ������ִ� �Լ�
void makeBinaryTable(TreeNode* root, string* table, string binary)
{
    // ���������� �����Դٸ�, table ����
    if (root->left == NULL && root->right == NULL)
    {
        // cout << root->data << " : " << binary << "\n";  // Binary Code�� �� ����������� Ȯ���ϱ�

        // �ش� ���ĺ��� ���Ͽ� binary code�� �����ϱ�
        if ('a' <= root->data && root->data <= 'z')
            table[root->data - 'a'] = binary;
        else
            table[root->data - 'A' + 26] = binary;

        return; // �Լ� ����
    }

    makeBinaryTable(root->left, table, binary + '0');  // huffman tree���� ���� �ڽ����� �̵��ߴٸ� ���� string�� '0'�� �߰�
    makeBinaryTable(root->right, table, binary + '1'); // huffman tree���� ������ �ڽ����� �̵��ߴٸ� ���� string�� '1'�� �߰�
}

// ����ڷκ��� �Է¹��� string�� encoding ���ֱ� ���� �Լ�
string encoding(string& input, TreeNode** rootNode)
{
    // get Frequency table
    int table[MAXALPHA] = { 0, }; // frequency table ����
    for (int i = 0; i < input.length(); i++)
    {
        // �ش� ���ĺ��� �� �� ���Դ����� �����.
        if ('a' <= input[i] && input[i] <= 'z')
            table[input[i] - 'a']++;
        else
            table[input[i] - 'A' + 26]++;
    }
    // frequency table ���� �Ϸ�


    // pq.push();
    PqNode pq[MAXALPHA + 1]; // frequency �Ի��� �������Ƿ� �� table�� ���� �켱���� ť ����
    int top = 0;
    for (int i = 0; i < MAXALPHA; i++) // table�� �������� �켱����ť�� �ֱ�
        if (table[i] != 0) // �ش� ���ĺ��� 1�� �̻� ���Դٸ� �켱���� ť�� ����
        {
            // cout << table[i] << " ";  // frequency table�� �� ����� ������ Ȯ���ϱ�
            push(pq, top, table[i], i);
        }
    // �ʱ� �켱���� ť ���� �Ϸ�


    // �켱���� ť Ȯ��
    // cout << "\n";
    // for (int i = 1; i <= top; i++)
    //     cout << pq[i].tree->data << " " << pq[i].cnt << "\n";


    // ���ĺ��� �ϳ��� �־��� ���, �� ��쿡���� rootNode�� ������ �� -> ����ó��
    if (top == 1) // �켱���� ť�� ����� 1�̶��, ���ĺ��� �ϳ��θ� �Է����� �־��� �����
    {
        (*rootNode) = pq[1].tree;
        string binaryStr = "";

        for (int i = 0; i < input.length(); i++)
            binaryStr += "1";

        return binaryStr;
    }


    // �켱���� ť�κ��� frequency�� ���� ���� ������ subtree ����
    int cntSum;
    TreeNode* left, * right;
    while (top != 1) // top�� 1�� ���, tree ���� �Ϸ�
    {
        // pq[1] = rootNode
        cntSum = pq[1].cnt;   // �켱���� ť���� frequency�� ���� ���� alphabet �����Ͽ� cutSum�� ����
        left = pop(pq, top); // �׸��� ���ο� subtree�� ����� ���� �켱���� ť���� pop�� ��, �����ڽ����� ����

        cntSum += pq[1].cnt;  // �� �켱���� ť���� frequency�� ���� ���� alphabet �����Ͽ� cntSum�� ���� frequency ���ϱ�
        right = pop(pq, top); // �׸��� ���ο� subtree�� ����� ���� �켱���� ť���� pop�� ��, �������ڽ����� ����

        // �̷��� �ؼ� ������� ���ο� ��带 tree�� �����ؾ���.
        TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
        newNode->data = ' ';
        newNode->left = left;
        newNode->right = right;

        push(pq, top, cntSum, newNode); // �� alphabet�� ��ģ ���ο� alphabet�� ���� ��, �ٽ� �켱���� ť�� ����
    }
    (*rootNode) = pq[1].tree;
    // Huffman tree �����Ϸ�


    // Binary code table �����
    string binaryTable[MAXALPHA]; // binary table�� ���� string �迭 ����
    makeBinaryTable(*rootNode, binaryTable, ""); // Huffman tree�� �̿��Ͽ� binary table �����
    // Binary code table �����Ϸ�


    // encoding �ϱ�
    string binaryStr = ""; // encoding�� ������� �����ϱ� ���� string ���� ����
    for (int i = 0; i < input.length(); i++) // ����ڰ� �Է��� string�� ũ�⸸ŭ �ݺ�
    {
        if ('a' <= input[i] && input[i] <= 'z') // �ҹ����� ���,
            binaryStr += binaryTable[input[i] - 'a']; // ���� alphabet�� �ش��ϴ� table�� ���� binary ���·� ��ȯ�Ѵ�. ( �� ���� binaryStr�� ���� )
        else // �빮���� ���
            binaryStr += binaryTable[input[i] - 'A' + 26]; // ���� alphabet�� �ش��ϴ� table�� ���� binary ���·� ��ȯ�Ѵ�. ( �� ���� binaryStr�� ���� )
    }
    // encoding �Ϸ�

    return binaryStr;
}

// huffman tree�� �̿��Ͽ� binary code�� �ٽ� decoding���ִ� �Լ�
char decodetrave(const string& binaryStr, int& top, TreeNode* search)
{
    while (true)
    {
        // ���������� �����Դٸ�, �ش� ���� ��ȯ
        if (search->left == NULL && search->right == NULL)
            return search->data;

        // ���� binary ���� 0�� ���, ���� �ڽ����� �̵�
        if (binaryStr[top] == '0')
            search = search->left;
        // ���� binary ���� 1�� ���, ������ �ڽ����� �̵�
        else if (binaryStr[top] == '1')
            search = search->right;

        top++; // ���� binary code�� Ȯ���ϵ��� top�� ����������.
    }
}

// decoding�� ���ֱ� ���� �Լ�
string decoding(string& binaryStr, TreeNode* root)
{
    int top = 0; // binary code�� ��ȸ�ϱ� ���� index ������ ���� ����
    string decodeStr = ""; // decode�� ���ڿ��� �����ϱ� ���� string ���� ����

    // �Է����� ���ĺ� �ϳ��� �־��� ���, �� ��쿡���� rootNode�� ������ �� -> ����ó��
    if (root->left == NULL && root->right == NULL)
    {
        for (int i = 0; i < binaryStr.length(); i++)
            decodeStr += root->data;

        return decodeStr;
    }

    while (top < binaryStr.length()) // top�� ��� binary code�� �ؼ��� ������ �ݺ�
        decodeStr += decodetrave(binaryStr, top, root); // �� ���� alphabet�� decode �ǵ��� �ϴ� �Լ� ���� (�� �Լ��� ������� decodeStr�� �����ش�.)

    return decodeStr; // decode �� ���ڿ��� ��ȯ�Ѵ�.
}