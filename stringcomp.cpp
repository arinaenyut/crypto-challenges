#include <iostream>
#include <string>
#include <time.h> 
using namespace std;

bool StringComparison(string str1, string str2)
{
	int diff = str1.length() ^ str2.length();
	for (int i = 0; i < str1.length() && i < str2.length(); i++)
	{
		diff |= (int) (str1[i] ^ str2[i]);
	}	
	return diff == 0;
	
}

int main()
{
	string a = "Implement a string comparisons algorithm on your own and then implement secure one comparing strings in constant time. To understand why it is necessary and where it is used see this";
	string b = "Security policy is a definition of what it means to be secure for a system, organization or other entity. For an organization, it addresses the constraints on behavior of its members as well as constraints imposed on adversaries by mechanisms such as doors, locks, keys and walls. For systems, the security policy addresses constraints on functions and flow among them, constraints on access by external systems and adversaries including programs and access to data by people.";
	clock_t time;
	time = clock();
	if (StringComparison(a,b)) cout<<" equal\n";
	else cout<<"not equal\n";
	cout<<"runtime "<<(double)(clock() - time) / CLOCKS_PER_SEC<<"sec"<<endl;


return 0;
}
