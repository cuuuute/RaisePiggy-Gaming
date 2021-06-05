#include<iostream>
#include<fstream>
#include<string>
#include<set>
#include<time.h>
#include<stdlib.h>
using namespace std;

double money;
int day;
int cnt,idx=0;

typedef struct Pig{ //�� 
	int id;//��� 
	int ty;//���� 
	int growday;//�������� 
	double weight;//���� 
	int pen;//�ڼ�����Ȧ 
	struct Pig *next;
}Pig,*PigList;

struct PigPen{//��Ȧ 
	int sum;//�ж���ͷ��
	int a,b,c;//С��������׻��������������� 
	bool flag;//�Ƿ��к��� 
	int pigid[11];//ÿͷ����id 
}pigpen[111];


//���ұ��Ϊid���� 
void find(PigList L,int id){
    Pig *p=L->next;
    int i=0;
    while(p){
    	if(p->id==id) {//�ҵ��������Ϣ 
    		cout<<"����Ϊ ";	
			if(p->ty==1)cout<<"С������";
			if(p->ty==2)cout<<"��׻�����";
			if(p->ty==3) cout<<"������";
			cout<<"����Ϊ "<<p->weight<<"kg,";
			cout<<"����ʱ��Ϊ "<<p->growday/30<<"��"<<p->growday%30<<"��";
   		
    		return;
    	}
        p=p->next;
    } 
} 
 
//Ϊ����С��������Ȧ 
int getpen(int k)//kΪƷ�ֱ�� 
{
	int x=-1;
	//С����,��׻���
	if(k==1||k==2){
		for(int i=0;i<100;i++)
		{
			//��û�к�������Ȧ�������������ٵ�Ȧ 
			if(!pigpen[i].flag && (x==-1||pigpen[i].sum<pigpen[x].sum))
				x=i;
		}
		//û���ҵ��޺����Ļ���ȫ������ 
		if(x==-1||pigpen[x].sum==10)
			return -1; 
	}
	else {//���� 
		for(int i=0;i<100;i++)
		{
			//���ȷ����Ѿ��к�������û��������Ȧ 
			if(pigpen[i].flag && pigpen[i].sum<10)
			{
				return i;
			}	
		}
		//���û���ҵ�,�Ҹ��յķ������ 
		for(int i=0;i<100;i++){
			if(pigpen[i].sum == 0)
				return i;
		}
	}
	
	return x;
}

//����С���� 
PigList PigListInsert(PigList L) {
    Pig *pre;                     
    pre = L;
    while( pre->next!=NULL )  
	  pre = pre->next;     //�������һ������ǰ���ڵ� 
	
    Pig *p;    //Ҫ����Ľ��Ϊp
    p = (Pig *)malloc(sizeof(Pig));
    p->id = ++idx;//��� 
	p->ty = rand()%3+1;//����1-3���������� 
	p->growday = 0;//��ʼ��������Ϊ0 
	p->weight = rand()%50+20; //����������� 
	p->pen = getpen(p->ty); //ΪС��������Ȧ 
//	cout<<p->id<<' '<<p->ty<<' '<<p->growday<<' '<<p->weight<<' '<<p->pen<<endl; 
	if(p->pen==-1) {
		cout<<"��Ȧ����/������,�޷����룡����"<<endl; 
		return L;
	}
	else 
	{
		//С��������Ȧ 
		pigpen[p->pen].pigid[pigpen[p->pen].sum]=idx;//////////////////////////
		
		if(p->ty == 1) pigpen[p->pen].a++;
		else if(p->ty == 2) pigpen[p->pen].b++;
		else pigpen[p->pen].c++,pigpen[p->pen].flag=true;
		
		pigpen[p->pen].sum++;//����Ȧ�����ĸ�������1 
	}
    p->next = pre->next;
    pre->next = p;
 	
    return L;
}


//������ʼ��
PigList PigListInit() {
    Pig *L;
    L = (Pig *)malloc(sizeof(Pig));   //������ռ�			//////////////////////////
    if(L==NULL){    //�ж�����ռ��Ƿ�ʧ��						//////////////////////////
    	cout<<"����ռ�ʧ��!"<<endl; 							//////////////////////////
        exit(0);    //���ʧ�����˳�����						//////////////////////////
    }															//////////////////////////
    L->next = NULL;          //��next����ΪNULL,��ʼ����Ϊ0�ĵ�����
    return L;
}
 //С����������kǧ�� 
PigList grow(PigList L,double k) {
    Pig *p=L->next;
    int i=0;
    while(p){
        p->growday ++;
		p->weight = p->weight + k; 
        p=p->next;
    }
    return L;
}

//�ѱ��Ϊk��С����x����Ȧ��ɾ�� 
void pendel(int x,int k,int t)
{
	int n=pigpen[x].sum;//��ǰ��Ȧ���������� 
	for(int i=1;i<=n;i++)
	{
		if(pigpen[x].pigid[i]==k)//���ҵ��� 
		{
			for(int j=i;j<=n;j++)//����ı�Ŷ�ǰ��һλ 
				pigpen[x].pigid[j]=pigpen[x].pigid[j+1];
			break;
		}
	}
	pigpen[x].sum--;//��ǰ��Ȧ������������һ 
	if(t==1) pigpen[x].a--;
	if(t==2) pigpen[x].b--;
	if(t==3) pigpen[x].c--;
	if(pigpen[x].c<=0) pigpen[x].flag=0;//û�к����� 
} 
 
//ɾ�����Գ�Ȧ���� 
PigList del(PigList L) {
   
    double money=0;//���γ�Ȧ������������Ǯ 
    int f=1;
    while(f)
	{       
	 	Pig *p,*pre;   //preΪǰ����㣬pΪ���ҵĽ�㡣
    	p = L;
    	f=0;
	    while(p->next) 
        {
	        pre = p;
	        p = p->next;
	        //��������,���Գ�Ȧ 
	        if(p->weight>150||p->growday>365)
			{
				double x;//���� 
				
				if(p->ty==1) x=7;
				else if(p->ty==2) x=6;
				else x=15;
				
				money+=x*(p->weight);
				
				pendel(p->pen,p->id,p->ty);//����Ȧ��ɾ�� 
				
				f=1;//�ҵ���һ�����Գ�Ȧ��,���û�ҵ�,f=0,ѭ��ֹͣ 
				break;
			}		
		}
		pre->next = p->next;          //ɾ������������ǰ��nextָ�����̡�
  		free(p);
    }
   
    cout<<"���γ�Ȧ�������ۼ�Ϊ��"<<money<<endl; 
    return L;
}

//ͳ�Ƶ�k���������������ء�����ʱ��ֲ����
void cla(PigList L,int k)
{
	int s=0;//����
	double w=0;//����
	int mint=10000,maxt=0;//ʱ��
	set<int> st;//��Ȧ�ֲ� /////////////////////////////////////// 
	Pig *p=L->next;
	if(p==NULL) {
		cout<<"��Ȧ��û�д�����!!!"<<endl; 
		return;
	}
    int i=0;
    while(p){
    	//�ҵ���һ�� 
    	if(p->ty==k) {
    		s++;//������һ 
    		w+=p->weight;//���������� 
    		st.insert(p->pen);//����������Ȧ�ı�ŷ������ 
    		mint=min(mint,p->growday);//��С���� 
    		maxt=max(maxt,p->growday);//������ 
    	} 
        p=p->next;
    } 
    if(k==1)cout<<"С����";
	if(k==2)cout<<"��׻���";
	if(k==3) cout<<"����";
	cout<<"������Ϊ"<<s;
	if(s==0) {
		cout<<endl<<endl;
		return;
	}
	cout<<",������Ϊ"<<w<<"\n������С��������ʱ��Ϊ"<<mint<<"��,��������"
	<<maxt<<"��\n�ֲ�����Ȧ�� ";
	set<int>::iterator it=st.begin();
	for(;it!=st.end();it++)
		cout<<*(it)<<' ';
	cout<<endl<<endl; 
}
int main(){
	time_t t;
	srand((unsigned) time(&t));
	
	//����һ����������ʼ�� 
    PigList list;
    list = PigListInit();
 	//�������cntͷС�� 
	cnt=rand()%10+1;
	//cout<<cnt<<endl;
	for(int i=1;i<=cnt;i++)
    PigListInsert(list);
    	
	cout<<"\n\n\n\n\n\n\n";
	cout<<"            ======================================================\n";
	cout<<'\n';
	cout<<"                       ��ѡ�������\n";
	cout<<'\n';
	cout<<"                            1.��һ��\n";		
	cout<<"                            2.��ѯĳ��Ȧ��������������\n";
	cout<<"                            3.��ѯĳ��Ȧĳͷ����״̬��Ϣ\n";
	cout<<"                            4.ͳ��ÿ���������������ء�����ʱ��ֲ����\n";
	cout<<"                            5.�˳�\n";
	cout<<'\n';
	cout<<"            ======================================================\n";

	while(1)
	{				
		int op;
		cin>>op;
		switch(op){
       		case 1:{
       			day++;
       			int x=rand()%12;
			    list = grow(list,0.1*x);	
				if(day%90==0) //��������,��Ȧ
				{
					del(list);
					//�����µ�С�� 
					cnt=rand()%5+1;
					for(int i=1;i<=cnt;i++)
				     	PigListInsert(list);
					
				}    	  	
				break;
			}
			case 2:{
				int x;
				cout<<"��������Ȧ��ţ�";
   		      	cin>>x;
   		      	cout<<"����Ȧ��"<<pigpen[x].sum<<"ͷ���������к���"<<pigpen[x].c<<"ͷ��С����"<<pigpen[x].a<<"ͷ����׻���"<<pigpen[x].b<<"ͷ\n\n";

				break;
			}
			case 3:{
				int x;
				cout<<"��������Ȧ��ţ�";
   		      	cin>>x;
   		      	cout<<"����Ȧ��"<<pigpen[x].sum<<"ͷ��,���������ı��: ";
				
				int y;
				cin>>y;
				while(y<0||y>=pigpen[x].sum)  
				{
					cout<<"��Ų��Ϸ�,����������: ";
					cin>>y;
				}
				//cout<<pigpen[x].pigid[y]<<endl;
				find(list,pigpen[x].pigid[y]);
				break;
			}
			case 4:{
				cla(list,1);
				cla(list,2);
				cla(list,3);
				break;
			} 
			case 5:{
				return 0;
			}
			default:break;
		}
		
	}
	
	return 0;
} 



