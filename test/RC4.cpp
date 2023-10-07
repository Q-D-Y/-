#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

string RC4(vector<unsigned char>&S,string key,string plaintext)
{
    string ciphertext;
    int i = 0, j = 0, k = 0, t = 0;
    for (k = 0; k < plaintext.size(); ++k)
    {
        i = (i + 1) % 256;
        j = (j + S[i]) % 256;
        auto tmp = S[i];
        S[i] = S[j];
        S[j] = tmp;
        t = (S[i] + S[j]) % 256;
        ciphertext += plaintext[k] ^ S[t];
    }
    return ciphertext;
}

void encrypt() {
    string key;
    string ciphertext;
    string plaintext;
    cout << "Input Key \n";
    cin >> key;
    cout << "Input Plaintext \n";
    cin >> plaintext; //输入密钥和明文
    vector<unsigned char>S1(256);
    for (int i = 0; i < 256; ++i)
    {
        S1[i] = i;
    }
    for (int i = 0, j = 0; i < 256; ++i)
    {
        j = (j + S1[i] + key[i % key.size()]) % 256;
        auto tmp = S1[i];
        S1[i] = S1[j];
        S1[j] = tmp;
    }//line32-43：初始化S表
    vector<unsigned char>S2 = S1;//备份S表
    ciphertext = RC4(S1, key, plaintext);//加密
    cout << "密文" << endl << ciphertext << endl;
    cout << RC4(S2, key, ciphertext);//输出解密结果
    return ;
}
