#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <math.h>
#include <map>
//#include <openssl/aes.h>

using namespace std;
#define INT_MAX 1000000

using namespace std;

map <char, string> gen_hex_table()
{
    map <char, string> map;
    map['0'] = "0000";
    map['1'] = "0001";
    map['2'] = "0010";
    map['3'] = "0011";
    map['4'] = "0100";
    map['5'] = "0101";
    map['6'] = "0110";
    map['7'] = "0111";
    map['8'] = "1000";
    map['9'] = "1001";
    map['a'] = "1010";
    map['b'] = "1011";
    map['c'] = "1100";
    map['d'] = "1101";
    map['e'] = "1110";
    map['f'] = "1111";
    return map;   
}

string hex2bin(string hexstr)
{
    map<char, string> m = gen_hex_table();
    string newstr = "";
    for (int i = 0; i<hexstr.size(); i++)
    {
        if (isdigit(hexstr[i])!= 0)
        {
            newstr += m.find(hexstr[i])->second;
        }
        else
        {
            newstr += m.find(hexstr[i])->second;
        }

        
    }
//  cout << newstr<<endl;
    return newstr;

}

string add_zero(string str, int zero)//zero = 6(bit)
{
    string newstr = "";
    int count = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if (count == zero)
        {
            newstr += " ";
            i--;
            count = 0;
        }
        else
        {
            newstr += str[i];
            count++;
        }  
    }
  //  cout<<newstr<<endl;
    return newstr;
}

vector <int> bin2dec(string str, double power)
{
    vector<int> v;
    string newstr = "";
    istringstream iss(str);
    string x;

    while (iss >> x)
    {
        double p = power;
        double dec = 0.0;

        for (int i = 0; i<x.size(); i++)
        {
            if (x[i] == '1')
            {
                dec +=pow(2.0, p);
            }
            p--;
        }
        v.push_back((int)dec);
    }    
    return v;
}

string hex2base64(string str)
{
    string b64 = "";
    string ref = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    string newstr = add_zero(hex2bin(str), 6);

    vector <int> v = bin2dec(newstr, 5.0);

    for(int i = 0; i<v.size(); i++)
    {
        b64 +=ref[v[i]];
    }
//    cout<<"base "<<b64<<"\n\n\nend\n\n";
    return b64;
}

string a2h(string str)
{
    stringstream ss;
    for (int i = 0; i<str.size(); i++)
    {
        ss << std::hex << (int)str[i];
    }
    return ss.str();
}

string fixedXOR (string str1, string str2)
{
    if (str1.size() != str2.size()) {cout<<"error";exit(0);}

    string result = "";
    str1 = add_zero(hex2bin(str1), 8);
    str2 = add_zero(hex2bin(str2), 8);

    vector<int> v1 = bin2dec(str1, 7.0);
    vector<int> v2 = bin2dec(str2, 7.0);

    for (int i = 0; i<v1.size(); i++)
    {
        unsigned char a = v1[i];
        unsigned char b = v2[i];
        unsigned char c = a ^ b;

        result += c;
    }
    return a2h(result);
}

map <char, int> freq_table(string str)
{
    map <char, int> m;
    map <char, int>:: iterator itr;
    for (int i = 0; i<str.size(); i++)
    {
        char ch = str[i];
        itr = m.find(ch);
        if (itr == m.end())
        {
            m.insert(make_pair(ch, 1));
        }
        else
        {
            itr->second++;
        }        
    }
     return m;
}

char retHighFreqChar(map<char,int> m)
{
    int max_count = 0;
    char max_ch;
    for (auto p: m)
    {
        if (isalpha(p.first)){
            if(p.second > max_count)
            {
                max_ch = p.first;
                max_count = p.second;
            }
        }
    }
    return max_ch;
}

string d2a(vector<int> v)
{
	string newStr = "";
	for(int i=0; i<v.size(); i++)
	{
		newStr += (char)v[i];
	}
	return newStr;
}

string singleByteXOR(string str)
{
    string newstr = "";
    str = add_zero(hex2bin(str), 8);
    
    vector<int> v = bin2dec(str, 7.0);

    unsigned char a = toupper(retHighFreqChar(freq_table(d2a(v))));
    
    for (int i = 0; i<v.size(); i++)
    {
        unsigned char b = v[i]; 
        unsigned char c = b ^ a;
        newstr += c;
    }

    return newstr;

}

int HighFreqCount(map <char, int> m)
{
    int count =0; 
    for (auto p:m)
    {
        if (isalpha(p.first))
        {
            count += p.second;
        }
    }
    return count;
}

string DetectSingleCharacterXOR(vector<int> maxV)
{
    string result = "";
    int max_count = 0;

    for (int i = 0; i<256; i++)
    {
        string tmp = "";
        unsigned char a = i;
        for (int j = 0; j<maxV.size(); j++)
        {
            unsigned char b = maxV[j];
            unsigned char c = b ^ a;
            tmp += tolower(c);
           // cout<<tmp<<endl;
        }
        
        int count = HighFreqCount(freq_table(tmp));
        if (count > max_count)
        {
            max_count = count;
            result = tmp;
        }
    }
    return result;
}

string RepeatingKeyXOR(string str, string key)
{
    string newstr = "";
    int count = 0;

    for (int i = 0; i<str.size(); i++)
    {
        unsigned char a = key[count];
        unsigned char b = str[i];
        unsigned char c = b ^ a;

        newstr += c;
        if (count == key.size()-1)
        {
            count = 0;
        }
        else count ++;
    }
    string result = "0";
   // cout<<"ascii\n"<<newstr<<endl<<endl;
    result += a2h(newstr);
    return result;
}

int hamming_distance(string str1, string str2)
{
    int dist = 0;
    for(int i = 0; i<str1.size(); i++)
    {
        int p = (str1[i] & 0xFF) ^ (str2[i] & 0xFF);
        while (p)
        {
            dist += p & 1;
            p = p >> 1;
        }
    }
    return dist;
}

int find_keysize(string text)
{
    int KEYSIZE = -1;
    double leastnorm = INT_MAX;
    for(int i = 2; i < 40; i++)
    {
        double normalize = 0.0f;
        int bytes = text.size()/i;

        for(int j = 0; j < bytes; j++)
        {
            string A = text.substr((i*j), i);
            string B = text.substr(((j+1)*i), i);

            int h_dist = hamming_distance(A, B);
            normalize += (((double)h_dist)/(double)A.size());
        }
        normalize /= bytes;

        if (normalize > 0 && normalize < leastnorm)
        {
            leastnorm = normalize;
            KEYSIZE = i;
        }
    
    }
    return KEYSIZE;
}

string singleByteXOR(string str, char key)
{
    string newStr(str.size(),'\0'); 
    for(int i = 0; i < str.size(); ++i){
        newStr[i] = str[i] ^ key;
    }
    return newStr;
}

char singleByteXOR_blocks(string cipherBlock)
{
    char key = 0;
    int maxCount = 0;
    string decodedMessage;

    for(int i = 0; i <= 256; i++)
    {
        char ch = (char) i;
        string attempt = singleByteXOR(cipherBlock, ch);

        cout << "Message: " << attempt << endl;

        int count = 0;
        for(int j = 0; j < attempt.size(); j++)
        {
            if((attempt[j] >= 65 && attempt[j] <= 122) || attempt[j] == ' ')
            {
                count++;
            }
        }

        if(count > maxCount)
        {
            maxCount = count;
            key = ch;
        }
    }
    cout << "KEY: " << key << endl;
    return key;
}

string h2a(string str)
{
	string newStr = "";
	str = add_zero(hex2bin(str), 8);
    cout<<str<<endl;
	vector <int> v = bin2dec(str, 7.0);

	for(int i = 0; i < v.size(); i++)
	{
		newStr += (char)v[i];
	}
	return newStr;
}

//Detect ECB Mode in AES Cipher
bool DetectAESinECBmode(string str, int keylen)
 {
    int blocks = str.size() / keylen;
    for(int i = 0; i < blocks; i++)
    {
        string strA = str.substr(i*keylen, keylen);
        for(int j = i + 1; j < blocks; j++)
        {
            string strB = str.substr(j*keylen, keylen);
            if(strA == strB)
            {
                //Found
                return true;
            }
        }
    }
        return false;
}

string b64_2_a(string str)
{
	for(int i=0; i<str.size(); i++)
	{
		char c = str[i];

		if(str[i] >= 'A' && str[i] <= 'Z')
		{
			c = c - 65;
		}
		else if(str[i] >= 'a' && str[i] <= 'z')
		{
			c += -97 + 26;
		}
		else if(str[i] >= '0' && str[i] <= '9')
		{
			c += -48 + 52;
		}
		else if(str[i] == '+')
		{
			c = 62;
		}
		else if(str[i] == '/')
		{
			c = 63;
		}

		str[i] = c;
	}
}


int main()
{
    int challenge; 
    cout<<"What? ";
    cin>>challenge;
    string hexStr, str1, str2, str, key, text, block, message;
    string maxstr = "";
    ifstream FILE, FILE6;
    ifstream FILE1;
    int x = 0, count, blocks, keylen;
    vector<int> maxV, v1;
    char indexkey;
    switch (challenge)
    {
    case 1:
        /*
        1)Перевести шестнадцатеричную строку в двоичную
        2)Разделить двоичную строку по 6 бит
        3)Полученные биты преобразовать в десятичную форму
        4)Каждому числу соответствует символ 
        */
        // string hexStr;
        hexStr = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
        if(hex2base64(hexStr) == "SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t")
            cout<<"correct\n";
        else 
            cout<<"wrong\n";
    break;

    case 2:
        /*
        Длины строк должны быть равны
        1)Перевести шестнадцатеричную строку в двоичную
        2)Разделить двоичную строку по 8 бит
        3)Полученные биты преобразовать в десятичную форму
        4)В цикле последовательно брать по символу и применять ^
        5)Записать результат в шестнадцатеричном виде
        */
        str1 = "1c0111001f010100061a024b53535009181c";
        str2 = "686974207468652062756c6c277320657965";
        if (fixedXOR(str1, str2) == "746865206b696420646f6e277420706c6179")
            cout<<"correct\n";
        break;

    case 3:
        /*
        1)Перевести шестнадцатеричную строку в двоичную 
        2)Разделить двоичную строку по 8 бит
        3)Полученные биты преобразовать в десятичную форму
        4)Найти самый часто встречающийся символ строки ASCII вида
        5)Найденый символ - ключ. Применяем ^ посимвольно к каждому символу строки
        */
        str1 = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
        cout<<singleByteXOR(str1)<<endl;
        break;

    case 4:
        /*
        1)Каждую шестнадцатеричную строку переводим в двоичную
        2)Десятичную переводим в ASCII
        3)Ищем строку с наибольшим числом английских букв
        4)С найденой строкой проделать то же, что и в 3 задании  
        */
        FILE.open("challenge4.txt");
        if (!FILE) {cout<<"error\n"; exit(0);}
        while (FILE >> str)
        {
            if (str.size()== 60)
            {
                str = add_zero(hex2bin(str), 8);
                v1 = bin2dec(str, 7.0);
                str1 = d2a(v1);
               // cout<<"str1: "<<str1<<endl;

                count = HighFreqCount(freq_table(str1));
                if (count > x)
                {
                    x = count;
                    maxstr = str1;
                    maxV = v1;            
                }
                
            } 
        }
        cout<<" "<<DetectSingleCharacterXOR(maxV)<<endl;
        FILE.close();
        break;

    case 5:
        /*
        1)К каждому символу строки применяем поочередно ^ c символами ключа
        2)Результат записать в шестнадцатеричном виде
        */
        str = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal";
        str1 = "ICE";
        cout<<RepeatingKeyXOR(str,str1)<<endl;
        //0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272
        //a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f
        break;

    case 6:
        /*
        1)Пусть KEYSIZE будет от 2 до 40
        2)Написать функцию для вычисления расстояния расстояния Хэмминга между двумя строками
        3)Для каждого KEYSIZE взять первое значение KEYSIZE в байтах и второе значение KEYSIZE в байтах и ​​найдите расстояние между ними. Нормализовать этот результат, разделив на KEYSIZE.
        4)KEYSIZE с наименьшим нормализованным расстоянием, вероятно, является ключевым
        5)Разбить зашифрованный текст на блоки длиной KEYSIZE.
        6)Теперь переставить блоки
        7)Расшифровать каждый блок, как в задании 3
        8)Для каждого блока ключ XOR является байтом ключа XOR с повторяющимся ключом для этого блока. Соединить их-ключ.
        */

        /*  
        str1 = "this is a test";
        str2 = "wokka wokka!!!";
        cout<<"dist = "<<hamming_distance(str1, str2)<<endl; = 37
        */
       
        FILE6.open("challenge6.txt");
        if (!FILE6) {cout<<"error\n"; exit(0);}
        getline(FILE6, message, '\0');
        FILE6.close();
        //cout<<message<<endl;
        text = h2a(message);
        keylen = find_keysize(text);
        
        blocks = text.size()/keylen;
        for(int i = 0; i < keylen; ++i)
        {
            for(int j = 0; j < blocks; j++)
            {
                block += text.substr((j*keylen) + i, 1);
            }

            key += singleByteXOR_blocks(block);


        }
        cout<<"key "<<key<<endl;
        cout<<"message:\n"<<h2a(RepeatingKeyXOR(text, key))<<endl;

        break;

    case 7:
        /*
        openssl enc -aes-128-ecb -d -in challenge7.txt -out message.txt -K YELLOW SUBMARINE
        
        AES_KEY decryptKey;
        int bits = 128; //AES-128

        string key = "YELLOW SUBMARINE";
        
        FILE.open("challenge7.txt");
        getline(FILE, text, '\0');
        FILE.close();

        text = b64_2_a(text);

        AES_set_decrypt_key((const unsigned char*)key.c_str(), bits, &decryptKey);

        unsigned char* decrypted = new unsigned char[message.size()+2];
        decrypted[message.size()] = '\0';

        int blocks = bitMode / 8;

        for(int i = 0; i * blocks < message.size(); i++)
        
            AES_ecb_encrypt((const unsigned char*)&(message.c_str()[i*blocks]), &decrypted[i*blocks], &decryptKey, AES_DECRYPT);
        
        cout << decrypted << endl; */
    break;

    case 8:
        /*
        1)Разделяем строку на блоки по 16
        2)Берем две подстроки 
        3)Сравниваем их, если одинаковые, то мы их нашли
        */
        FILE1.open("challenge8.txt");
        if (!FILE1) {cout<<"error\n"; exit(0);}

        while (!FILE1.eof())
        {
            getline(FILE1, str);
            if (DetectAESinECBmode(str, 16) == true)
            {
                cout<<"Line "<<x<<"\n"<< str <<endl;
               // break;
            }
            x++;
        }
        break;

   // default:
   //     break;
    }
   
    return 0;


}