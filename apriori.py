from copy import deepcopy
import random

def generate_transdb():
	random.seed()
	fout=open("transdb.txt","w+")
	tt=random.randint(1,101)+1
	for i in range(1,tt):
		fout.write("%d\t" %(i))
		ti=random.randint(1,10)+1
		s=set()
		for j in range(1,ti):
			u=random.randint(1,49)+1
			s.add(u)
		s=sorted(s)
		for n in s:
			fout.write("%d " %(n))
		fout.write("-123\n")
	fout.close()


def atoi(strg):
	h=0
	for u in strg:
		h*=10
		y=ord('0')
		r=ord(u)
		r-=y
		h+=r
	return h


def itoa(n):
	temp=""
	while(n!=0):
		r=n%10
		p=ord('0')
		p+=r
		e=chr(p)
		temp+=e
		n//=10
	gone="".join(reversed(temp))
	return gone


def getcount(m):
	f=open("transdb.txt","r")
	fl=f.readlines()
	for x in fl:
		strg=""
		tab='\t'
		space=' '
		q=0
		for i in x:
			if(i==tab or i==space):
				if(strg!=""):
					if(q==0):
						q=1
						strg=""
						continue
					if(strg[0]=='-'):
						strg=""
						continue
					y=atoi(strg)
					l=[]
					l.append(y)
					t=tuple(l)
					if(t in m):
						m[t]+=1
					else:
						m[t]=1;
					strg=""
			else:
				strg+=i
	f.close()


def putinfile(m):
	mp={}
	for key,value in m.items():
		y=len(key)
		break
	if(y==0):
		return
	cfile="cpy"
	lfile="lpy"
	ext=".txt"
	cat=itoa(y)
	cfile+=cat
	lfile+=cat
	cfile+=ext
	lfile+=ext
	cfout=open("%s" %cfile,"w+")
	lfout=open("%s" %lfile,"w+")
	for key,value in m.items():
		f=0
		if(value>=min_sup):
			f=1
		l=[]
		for i in key:
			cfout.write(itoa(i))
			cfout.write(" ")
			if(f==1):
				lfout.write(itoa(i))
				lfout.write(" ")
				l.append(i)
		cfout.write("	")
		cfout.write(itoa(value))
		cfout.write("\n")
		if(f==1):
			lfout.write("	")
			lfout.write(itoa(value))
			lfout.write("\n")
			t=tuple(l)
			mp[t]=value
	return mp


def modifytemp(temp):
	back={}
	sz=0
	for key in temp.keys():
		sz=len(key)
		break
	for key,value in temp.items():
		cnt=0
		f=open("transdb.txt","r")
		fl=f.readlines()
		for x in fl:
			l=[]
			strg=""
			tab='\t'
			space=' '
			q=0
			for i in x:
				if(i==tab or i==space):
					if(strg!=""):
						if(q==0):
							q=1
							strg=""
							continue
						y=atoi(strg)
						l.append(y)
						strg=""
				else:
					strg+=i
			keyl=list(key)
			setk=set(keyl)
			setl=set(l)
			s=setk & setl
			if(s==setk):
				cnt+=1
		f.close()
		if(cnt>0):
			lr=list(key)
			lr=sorted(lr)
			pkey=tuple(lr)
			back[pkey]=cnt
		else:
			lr=list(key)
			lr=sorted(lr)
			pkey=tuple(lr)
			back[pkey]=0
	return back



generate_transdb()
min_sup=2
m={}
getcount(m)
m=putinfile(m)
lastfileno=0
while True:
	lastfileno+=1
	if(len(m)==0):
		break
	temp={}
	for index,mkey in enumerate(m):
		q=0
		u=index+1
		utr={}
		for key,value in m.items():
			if(q<u):
				q+=1
				continue
			else:
				t=key
				utr[t]=value
		# print(utr)
		for ukey,uval in utr.items():
			flag=0
			for ind in range(0,len(ukey)-1):
				if(mkey[ind]!=ukey[ind]):
					flag=1
					break
			if(flag==0):
				ykey=deepcopy(mkey)
				dum=list(ykey)
				dum.append(ukey[len(ukey)-1])
				fkey=tuple(dum)
				temp[fkey]=0
	m=modifytemp(temp)
	if(len(m)>0):
		m=putinfile(m)

print("See files upto --> ",lastfileno)

