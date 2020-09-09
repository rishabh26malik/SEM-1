#include<bits/stdc++.h>
using namespace std;

struct EXP{
	string data;
	struct EXP *next;
};
typedef EXP EXP;

struct PostFix{
	string str;
	float num;
	bool isNum;
	char opn;
	struct PostFix *next;
};
typedef PostFix PostFix;

template <class T >
struct node{
	T data;
	node<T> *next;
};

template <class T >
class Stack{
	public :
	node<T> *Top;
	void push(T x){
		node<T> *tmp;
		tmp=new node<T>;
		tmp->data=x;
		tmp->next==NULL;
		if(Top==NULL){
			Top=tmp;
		}	
		else{
			tmp->next=Top;
			Top=tmp;
		}
	}

	T pop(){
		T res;
		node<T> *tmp;
		if(Top){
			tmp=Top;
			res=Top->data;
			if(Top->next){
				Top=Top->next;
			}
			else{
				Top=NULL;
			}
			delete(tmp);
			return res;
		}
		return -1;
	}
	bool empty(){
		if(Top==NULL)
			return true;
		return false;
	}
	T top(){
		if(Top)
			return Top->data;
		else
			return -1;
	}
};



bool isOperator(char op){
	if( op=='-' || op=='+' || op=='*' || op=='/' || op=='%' || op=='(' || op==')' )
		return true;
	return false;
}

void PostFixInsert(string val, bool isOpr, PostFix **head, PostFix **last){
	PostFix *nd=(PostFix*)malloc(sizeof(PostFix));
	nd->next=NULL;
	
	if( !isOpr ){
		nd->isNum=true;
		nd->num=stof(val);
		//cout<<"stof done"<<endl;
	}
	else{
		nd->isNum=false;
		//string opn(1,val);
		nd->opn=val[0];
	}
	
	nd->str=val;
	if(*head==NULL){
		*head=nd;
		*last=nd;
	}
	else{
		(*last)->next=nd;
		*last=nd;
	}
}


void ExpInsert(string val, EXP **head, EXP **last){
	EXP *nd=(EXP*)malloc(sizeof(EXP));
	nd->next=NULL;
	nd->data=val;
	if(*head==NULL){
		*head=nd;
		*last=nd;
	}
	else{
		(*last)->next=nd;
		*last=nd;
	}
}

int precedence(char ch){
	if(ch=='/' || ch=='%' || ch=='*')
		return 2;
	else if(ch=='+' || ch=='-')
		return 1;
	return -1;
}

string removeSpaces(string exp){
	string newExp="";
	int i,len=exp.length();
	for(i=0;i<len;i++)
		if(exp[i]!=' ')
			newExp+=exp[i];
	return newExp;
}

void separateExp(string exp, EXP **head){
	//exp="-11+22*(-33/44-55)*(66+77*88)-99";	//−8391823
	//exp="111*88/65+432+5-5/15*89";			//557.61025641
	//exp="11+22*33/44-55";						//−27.5
	//exp="((11.1*8.8)/65)+43.2+(5-(5/15)*.9)";	//49.402769231
	//exp="(-11*-22)*-33/44-55";				//−236.5
	//exp="75*854/7953/6490*1641-100";			//−97.963651824
	//exp="87*16+(87/50)*28-60-(41-73)/69+30";	//1411.183768116

	//exp="84-27*(26+29)*55-65-(3*2)*5/80";		//−81656.375
	//exp="75*854/7953/6490*1641-100";			//−97.963651824
	//exp="87*16+(87/50)*28-60-(41-73)/69+30";	//1411.18
	//exp="20/76-(65*46)+80*94*(55*68)-73*16";	//2.81206e+07
	//exp="86/41/(73/2)/25*4042/7696+43";		//43.0012
	//exp="84-27*(26+29)*55-65-(3*2)*5/80";		//-81656.4
	//exp="66-7333/5082-4999-2127/87";			//-4958.89
	//exp="86/6686-4479+24*(43/1)/45+71";		//-4385.05
	//exp="45-50*(83*78)*82/48-(1-66)*39*63";	//-393238
	//exp="5*23+56%45*123+95-56";				//1507
	//exp="54/6524*5644652%(51+2326)*89";		// math error
	//exp="3*2+45*39/13*5%3-(33-123)*2";			//186
	cout<<exp<<endl;
	int i=0,len=exp.length(),neg=0;
	cout<<len<<endl;
	EXP *nd,*last=NULL;
	string num="";
	//	11+22*(33/(44-55))+1
	for(i=0;i<len;i++){
		cout<<"aa"<<endl;
		cout<<exp[i]<<" ";
		cout<<"bb"<<endl;
		if(isOperator(char(exp[i]))){
			cout<<"cc\n";
			cout<<exp[i]<<" ";
			if(exp[i]=='-' && exp[i+1]>='0' && exp[i+1]<='9'){
				neg=1;
				if(i==0)
					continue;
				//if(isOperator(char(exp[i-1])) && exp[i-1]!=')' && exp[i-1]!='(' ){
				if(isOperator(char(exp[i-1])) && exp[i-1]=='(' ){
					continue;
				}
				else if( isOperator(char(exp[i-1])) && exp[i-1]==')' ) {
					exp[i]='+';	
				}
				else if( isOperator(char(exp[i-1])) ) {
					continue;
					//exp[i]='+';	
				}
				else if( !isOperator(char(exp[i-1])) ) {	
					exp[i]='+';	
				}
				//string sign="+";
				//string opn(1,sign);
				//exp[i]='+';
			}
			//else
			string opn(1,exp[i]);
			nd=(EXP*)malloc(sizeof(EXP));
			nd->next=NULL;
			nd->data=opn;
			if(*head==NULL){
				*head=nd;
				last=nd;
			}
			else{
				last->next=nd;
				last=nd;
			}
			num="";
		}
		else{
			cout<<"dd\n";
			cout<<exp[i]<<" ";
			//cout<<"ee\n";
			num+=exp[i];
			cout<<"num = "<<num<<endl;
			if(i+1==len || (i+1 < len && isOperator(exp[i+1]))){
				nd=(EXP*)malloc(sizeof(EXP));
				nd->next=NULL;
				if(neg){
					num="-"+num;
					neg=0;
				}
				cout<<"num = "<<num<<endl;
				nd->data=num;
				cout<<"----num = "<<nd->data<<endl;
				if(*head==NULL){
					*head=nd;
					last=nd;
				}
				else{
					last->next=nd;
					last=nd;
				}	
				num="";
			}
		}
	}
}

void toPostfix(EXP *exp, PostFix **postfix){
	Stack <char> S;
	string operand, opn;
	char operatr;
	bool isOperand;
	PostFix *nd,*last=NULL;
	//cout<<"aa"<<endl;
	while(exp!=NULL){
		//cout<<"bb"<<endl;
		operand=exp->data;
		if( operand.length()==1 ){
			if( !isOperator(operand[0]) )
				isOperand=true;
			else
				isOperand=false;	
		}
		else{
			isOperand=true;
		}
		//isOperand=!isOperator(operand[0]) || ( isOperator(operand[0]) && !isOperator(operand[1]) );
		//cout<<operand;
		if( isOperand ){
			//cout<<operand<<endl;
			PostFixInsert(operand,false,postfix,&last);
		}
		else {
			//cout<<'a'<<" ";
			operatr=operand[0];
			if(S.empty() || operatr=='(' ){
				//cout<<operatr<<endl;
				S.push(operatr);
			}
			else if ( operatr== ')'){
				while( S.top() != '(' ){
					//cout<<S.top()<<" ";
					string opn(1,S.top());
					//opn=S.top();
					PostFixInsert(opn,true,postfix,&last);
					S.pop();	
				}

				//cout<<endl;
				S.pop();
			}
			else {
				while( !S.empty() && precedence(S.top()) >= precedence(operatr) ){
					string opn(1,S.top());
					//opn=S.top();
					//cout<<S.top()<<" ";
					PostFixInsert(opn,true,postfix,&last);			
					S.pop();
					if(!S.empty() && S.top()=='(')
						break;
				}
				//cout<<endl;
				S.push(operatr);	
			}
		}
		exp=exp->next;
		//isOperand=1-isOperand;
	}
	while(!S.empty()){
		//cout<<S.top()<<" ";
		string opn(1,S.top());
		PostFixInsert(opn,true,postfix,&last);			
		S.pop();
	}
}

float evaluateExp(PostFix *postfix){
	Stack <float> S;
	float num1, num2;
	while(postfix!=NULL){
		if(postfix->isNum){
			S.push(postfix->num);
		}
		else{
			num1=S.top();
			S.pop();
			num2=S.top();
			S.pop();
			switch(postfix->opn){
				case '*':
					S.push(num2 * num1);
					break;
				case '+':
					S.push(num2 + num1);
					break;
				case '-':
					S.push(num2 - num1);
					break;
				case '/':
					if(num1==0){
						cout<<"div by 0 math error\n";
						exit(0);
					}
					S.push(num2 / num1);
					break;
				case '%':
					if(num2==int(num2) && num1==int(num1) )
						S.push(int(num2) % int(num1));
					else{
						cout<<"mod math error\n";
						exit(0);
					}
					break;
			}
		}
		postfix=postfix->next;
	}
	return S.top();
}

int main(){
	string exp;
	//exp="3*2+45*39/13*5%3-(33-123)*2";	
	getline(cin,exp);
	//exp=removeSpaces(exp);
	EXP *sepExp=NULL,*tmp;
	PostFix *postfix=NULL,*tmp2;
	separateExp(exp,&sepExp);
	tmp=sepExp;
	while(tmp!=NULL){
		cout<<tmp->data<<" ";
		tmp=tmp->next;
	}
	cout<<endl;
	toPostfix(sepExp, &postfix);
	//cout<<endl;
	tmp2=postfix;
	while(tmp2!=NULL){
		if( tmp2->isNum )
			cout<<tmp2->num<<" ";
		else
			cout<<tmp2->opn<<" ";
		//cout<<tmp2->str<<" ";
		tmp2=tmp2->next;
	}
	cout<<endl;
	cout<<evaluateExp(postfix)<<endl;
	return 0;
}

