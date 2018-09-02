#include<bits/stdc++.h>
#define min_sup 2
#define pb push_back
using namespace std;

void generate_transdb()
{
	int tt=rand()%99+1;
	ofstream fout("trans.txt");
	for(int i=1;i<=tt;i++)
	{
		fout<<i<<"\t";
		int ti=rand()%9+1;
		set<int> s;
		set<int>::iterator sit;
		for(int i=1;i<=ti;i++)
		{
			int u=rand()%49+1;
			s.insert(u);
		}
		for(sit=s.begin();sit!=s.end();sit++)
		{
			fout<<(*sit)<<" ";
		}
		fout<<-123<<endl;
	}
	fout.close();
}

void getcount(map<vector<int> ,int> &m)
{
	ifstream fin("trans.txt");
	int x=0,n;
	while(fin>>n)
	{
		if(x==0)
		{
			x=1;
			continue;
		}
		else if(n==-123)
		{
			x=0;
			continue;
		}
		else
		{
			vector<int> v;
			v.pb(n);
			m[v]++;
		}
	}
	fin.close();
}

string itoa(int n)
{
	string u="";
	while(n)
	{
		int r=n%10;
		char ch=r+'0';
		u+=ch;
		n/=10;
	}
	reverse(u.begin(),u.end());
	return u;
}

void putinfile(map<vector<int> ,int> &m)
{
	map<vector<int> ,int> mp;
	int fileno;
	if(m.begin()->first.size()>0)
	{
		fileno=m.begin()->first.size();
	}
	else
	{
		return ;
	}
	string cfile="c",lfile="l";
	string cat=itoa(fileno);
	cfile+=cat;lfile+=cat;
	string ext=".txt";
	cfile+=ext;lfile+=ext;
	ofstream fcout(cfile.c_str()),flout(lfile.c_str());
	map<vector<int> ,int>::iterator mit;
	for(mit=m.begin();mit!=m.end();mit++)
	{
		int f=0;
		if(mit->second>=min_sup)
			f=1;
		vector<int> vtemp;
		for(int i=0;i<mit->first.size();i++)
		{
			fcout<<mit->first[i]<<" ";
			if(f)
			{
				flout<<mit->first[i]<<" ";
				vtemp.pb(mit->first[i]);
			}
		}
		fcout<<"\t"<<mit->second<<endl;
		if(f)
		{
			flout<<"\t"<<mit->second<<endl;
			mp.insert({vtemp,mit->second});
		}
	}
	fcout.close();flout.close();
	m=mp;
}

void modifytemp(map<vector<int> ,int> &temp)
{
	int sz=temp.begin()->first.size();
	map<vector<int> ,int>::iterator mit;
	for(mit=temp.begin();mit!=temp.end();mit++)
	{
		int cnt=0;
		bool flag[sz];
		for(int i=0;i<sz;i++)
			flag[i]=false;
		ifstream fin("trans.txt");
		int n,x=0,k=0;
		while(fin>>n)
		{
			if(x==0)
			{
				x=1;
				continue;
			}
			else if(n==-123)
			{
				int q=0;
				for(int j=0;j<sz;j++)
				{
					if(flag[j]==false)
					{
						q=1;
						break;
					}
				}
				if(!q)
					cnt++;
				for(int i=0;i<sz;i++)
					flag[i]=false;
				x=0;k=0;
				continue;
			}
			else
			{
				if(k<sz)
				{
					if(n==mit->first[k])
					{
						flag[k]=true;
						k++;
					}
				}
			}
		}
		mit->second=cnt;
	}
}
void printmap(map<vector<int> ,int> m)
{
	cout<<endl;
	map<vector<int> ,int>::iterator mit;
	for(mit=m.begin();mit!=m.end();mit++)
	{
		for(int i=0;i<mit->first.size();i++)
		{
			cout<<mit->first[i]<<" ";
		}
		cout<<"\t"<<mit->second<<endl;
	}
	cout<<endl;
}

bool prune(vector<int> v,map<vector<int> ,int> m)
{
	map<vector<int> ,int>::iterator mit;
	for(int i=0;i<v.size();i++)
	{
		vector<int> vec=v;
		vec.erase(vec.begin()+i);
		mit=m.find(vec);
		if(mit==m.end())
			return false;
	}
	return true;
}

int main()
{
	srand(time(NULL));
	//generate_transdb();
	map<vector<int> ,int> m;
	map<vector<int> ,int>::iterator mit,it,tit;
	getcount(m);
	putinfile(m);
	int lastfileno=0;
	while(1)
	{
		lastfileno++;
		if(m.size()==0)
			break;
		//printmap(m);
		//system("pause");
		map<vector<int> ,int> temp;
		for(mit=m.begin();mit!=m.end();mit++)
		{
			mit++;
			tit=mit;
			mit--;
			for(it=tit;it!=m.end();it++)
			{
				int q=0;
				for(int i=0;i<mit->first.size()-1;i++)
				{
					if(mit->first[i]!=it->first[i])
					{
						q=1;
						break;
					}
				}
				if(!q)
				{
					vector<int> vec=mit->first;
					vec.pb(it->first[it->first.size()-1]);
					if(prune(vec,m))
						temp.insert({vec,0});
				}
			}
		}
		modifytemp(temp);
		m=temp;
		if(m.size()>0)
			putinfile(m);
	}
	cout<<"\nSee upto file --> "<<lastfileno<<endl;
}
