#include <stdio.h>
#include<string.h>
int count=1;
int sugCount=0;
int number=3;
int reqCount=0;
struct friendNode{
	char usr[10];
	struct friendNode* next;
};
struct Graph{
	char name[10];
	struct friendNode* Head;
};
struct Graph* adjList[10]={NULL};
//initialiseGraph(usr);
void initialiseGraph(char* usr){
		adjList[number]=(struct Graph*)malloc(sizeof(struct Graph));
		adjList[number]->Head=NULL;
		strcpy(adjList[number]->name,usr);
		number++;
}
//justCheckingFunctions////////////////////////////////
void print(int i){
	struct friendNode* q=adjList[i]->Head;
	printf("%s:",adjList[i]->name);
	while(q!=NULL){
		printf("%s->",q->usr);
		q=q->next;
	}
	printf("\n");
}
void printHeads(){
	int i;
	for(i=0;i<number;i++){
		printf("Name:%s Address:%d\n",adjList[i]->name,adjList[i]->Head);
	}
}
/////////////////////////////////////////////////////
//RegardingMessagesAndRequests
struct node{
	char from[10],to[10],msg[50];
	struct node* next;
};
struct node* head=NULL;
//RegardingMessages
void toBeSent(char* from,char* to,char* msg){
	struct node* temp=(struct node*)malloc(sizeof(struct node));
	strcpy(temp->from,from);
	strcpy(temp->to,to);
	strcpy(temp->msg,msg);
	if(head==NULL){
		temp->next=head;
		head=temp;
		return;
	}
	else{
		struct node* q=head;
		while(q->next!=NULL){
			q=q->next;
		}
		temp->next=q->next;
		q->next=temp;
		return;
	}
}
void FriendRequests(char* from,char* to){
	toBeSent(from,to,"Request");
}
void setGraph(){
		adjList[0]=(struct Graph*)malloc(sizeof(struct Graph));
		adjList[0]->Head=NULL;
		strcpy(adjList[0]->name,"Robin");
		adjList[1]=(struct Graph*)malloc(sizeof(struct Graph));
		adjList[1]->Head=NULL;
		strcpy(adjList[1]->name,"Missandei");
		adjList[2]=(struct Graph*)malloc(sizeof(struct Graph));
		adjList[2]->Head=NULL;
		strcpy(adjList[2]->name,"Harshad");
}
//RegardingMessages
void del(char *usr){
	if(strcmp(head->to,usr)==0){
		struct node* temp=head;
		head=head->next;
		free(temp);
		return;
	}
	struct node* q=head,*temp;
	while(strcmp(q->next->to,usr)!=0){
		q=q->next;
	}
	temp=q->next;
	q->next=q->next->next;
	free(temp);
	return;
}
//UtilFunctionToCheckMessageList
void msgList(){
	struct node* temp=head;
	if(temp==NULL){
		printf("No elements in the list\n");
		return;
	}
	while(temp!=NULL){
			printf("\t\tTo: %s\n",temp->to);
			printf("\t\tFrom: %s\n",temp->from);
			printf("\t\tMessage: %s\n",temp->msg);
		temp=temp->next;
	}
	return;
}
//RegardingMessages
void showChats(char* usr){
	struct node* q=head;
	int flag=0;
	int i=0,j;
	char toBeDeleted[10][10];
	while(q!=NULL){
		if(strcmp(q->to,usr)==0&&strcmp(q->msg,"Request")!=0){
			flag=1;
			printf("\t\tFrom: %s\n",q->from);
			printf("\t\tMessage: %s\n",q->msg);
			strcpy(toBeDeleted[i],q->to);
			i++;
		}
		q=q->next;
	}
	for(j=0;j<i;j++){
		del(toBeDeleted[j]);
	}
	if(!flag){
		printf("\t\tNo New Messages\n");
	}
	return;
}
//BulidingBondProcess
void addFriendNode(char* usr,char* newFriend){
	int i;
	struct friendNode* temp=(struct friendNode*)malloc(sizeof(struct friendNode));
	strcpy(temp->usr,newFriend);
	for(i=0;i<number;i++){
		if(strcmp(adjList[i]->name,usr)==0){
			break;
		}
	}
	if(adjList[i]->Head==NULL){
		temp->next=adjList[i]->Head;
		adjList[i]->Head=temp;
		return;
	}
	struct friendNode* q=adjList[i]->Head;
	while(q->next!=NULL){
		q=q->next;
	}
	temp->next=q->next;
	q->next=temp;
	
	return;
	
}
//askingAndBodingFriends with their permission
void BuildABond(char* usr,char* addUsr){
	addFriendNode(usr,addUsr);
	addFriendNode(addUsr,usr);
}
//showingFriendReqeusts
void showRequests(char* usr){
	struct node* q=head;
	int flag=0;
	int i=0,j;
	char choice;
	char toBeDeleted[10][10];
	while(q!=NULL){
		if(strcmp(q->to,usr)==0&&strcmp(q->msg,"Request")==0){
			flag=1;
			reqCount++;
			printf("\t\tRequest From: %s\n",q->from);
			printf("\t\tDo you want to accept his friend Request?(y/n):");
			scanf(" %c",&choice);
			if(choice=='y'||choice=='Y'){
				BuildABond(usr,q->from);
				printf("\t\tHurray!You and %s are friends Now!\n",q->from);
			}
			strcpy(toBeDeleted[i],q->to);
			i++;
		}
		q=q->next;
	}
	for(j=0;j<i;j++){
		del(toBeDeleted[j]);
	}
	if(!flag){
		printf("\t\tNo New Friend Requests\n");
	}
}
int getReqCount(char *usr){
	reqCount=0;
	struct node* q=head;
	while(q!=NULL){
		if(strcmp(q->to,usr)==0&&strcmp(q->msg,"Request")==0){
			reqCount++;
		}
		q=q->next;
	}
	return reqCount;
}
//RegardingMessages
void sendMessage(char *from,char* to){
	int i,flag=0;
	char msg[50];
	for(i=0;i<number;i++){
		if(strcmp(adjList[i]->name,from)==0){
			break;
		}
	}
	struct friendNode* q=adjList[i]->Head;
	while(q!=NULL){
		if(strcmp(q->usr,to)==0){
			flag=1;
			break;
		}
		q=q->next;
	}
	if(flag){
		printf("\t\tEnter your message:");
		scanf("%s",msg);
	toBeSent(from,to,msg);
	}
	else{
		printf("\t\tNo friend with that name. Please enter correctly\n");
	}
}
int checkIfAlreadyFriends(char* usr,char* frnd){
	int i;
	for(i=0;i<number;i++){
		if(strcmp(usr,adjList[i]->name)==0){
			break;
		}
	}
	struct friendNode* q=adjList[i]->Head;
	while(q!=NULL){
		if(strcmp(q->usr,frnd)==0){
			return 1;
		}
		q=q->next;
	}
	return 0;
}
int checkIfRequestAlreadySent(char* usr,char* addUsr,char* req){
	struct node* q=head;
	while(q!=NULL){
		if(strcmp(q->from,usr)==0&&strcmp(q->to,addUsr)==0&&strcmp(q->msg,req)==0){
			return 1;
		}
		q=q->next;
	}
	return 0;
}
int checkIfOppPersonAlreadySentRequest(char* usr,char* addUsr,char *req){
	struct node* q=head;
	while(q!=NULL){
			if(strcmp(q->from,addUsr)==0&&strcmp(q->to,usr)==0&&strcmp(q->msg,req)==0){
				return 1;
			}
			q=q->next;
	}
	return 0;
}
int IfInDataBase(char* addUsr){
	int i=0;
	for(i=0;i<number;i++){
		if(strcmp(addUsr,adjList[i]->name)==0){
			return 1;
		}
	}
	return 0;
}
void AddFriends(char* usr){
	int i,option,flag=0;
	char choice;
	char addUsr[10];
	for(i=0;i<number;i++){
		if(strcmp(usr,adjList[i]->name)){
			//below code is to check is adjList[i]->name is already friend with usr
			if(!checkIfAlreadyFriends(usr,adjList[i]->name)){
				flag=1;
			printf("\t\t%s\n",adjList[i]->name);}
		}
	}
	if(flag){
		printf("\t\tDo want to add any of them above?(y/n):");
		scanf(" %c",&choice);
		if(choice=='y'|| choice=='Y'){
	printf("\t\tEnter the username to Add:");
	scanf("%s",addUsr);
	if(IfInDataBase(addUsr)==0){
		printf("\t\tNo user with that name in this application. Please Enter correctly\n");
	}
	else if(checkIfOppPersonAlreadySentRequest(usr,addUsr,"Request")==1){
		printf("\t\t%s has already sent you the friendRequest. Please check in Friend Requests section.\n",addUsr);
	}
	else if(checkIfRequestAlreadySent(usr,addUsr,"Request")!=1){
	toBeSent(usr,addUsr,"Request");
	printf("\t\tFriend Request sent Successfully\n");
	}
	else{
		printf("\t\tFriend Request Already Sent\n");
	}
	}
	}
	else{
		printf("\t\tNo friends to add\n");
	}
}

int showFriends(char* usr){
	int i,flag=0;
	for(i=0;i<number;i++){
		if(strcmp(adjList[i]->name,usr)==0){
			break;
		}
	}
	struct friendNode* q=adjList[i]->Head;
	while(q!=NULL){
		flag=1;
		printf("\t\t%s\n",q->usr);
		q=q->next;
	}
	if(!flag){
		printf("\t\tNo new Friends. Go add them now! :D\n");
		return 0;
	}
	return 1;
}
void showFriendsThroughSuggestions(char* usr,char* acUsr){
	int i;
	int flag=0;
	for(i=0;i<number;i++){
		if(strcmp(adjList[i]->name,usr)==0){
			break;
		}
	}
	struct friendNode* q=adjList[i]->Head;
	while(q!=NULL){
		if(checkIfAlreadyFriends(q->usr,acUsr)!=1 && strcmp(q->usr,acUsr)!=0){
		printf("\t\t%s\n",q->usr);
		sugCount++;
		}
		q=q->next;
	}
	return;
	
}
void Suggestions(char* usr){
	int i;
	for(i=0;i<number;i++){
		if(strcmp(adjList[i]->name,usr)==0){
			break;
		}
	}
	struct friendNode* temp=adjList[i]->Head; 
	struct friendNode *InfriendList,*q,*head=temp;
	while(temp!=NULL){
		for(i=0;i<number;i++){
			if(strcmp(adjList[i]->name,temp->usr)==0){
				break;
			}
		}
		InfriendList=adjList[i]->Head;
		while(InfriendList!=NULL){
			q=head;
			while(q!=NULL){
				if(strcmp(InfriendList->usr,q->usr)==0){
				showFriendsThroughSuggestions(q->usr,usr);
				}
				q=q->next;
			}
			InfriendList=InfriendList->next;
		}
		temp=temp->next;
	}
	if(sugCount==0){
		printf("\t\tNo friend suggestions\n");
	}
}
void Unfriend(char* usr,char* delFrnd){
	int i;
	struct friendNode* temp;
	for(i=0;i<number;i++){
		if(strcmp(usr,adjList[i]->name)==0){
			break;
		}
	}
	struct friendNode* q=adjList[i]->Head;
	struct friendNode* temp2=q;
	while(temp2!=NULL){
		if(strcmp(temp2->usr,delFrnd)==0){
			break;
		}
		temp2=temp2->next;
	}
	if(temp2==NULL){
		printf("\t\tNo friend with that name. Please enter correctly.\n");
		return;
	}
	if(q==NULL){
		printf("\t\tNo friends to Unfriend\n");
		return;
	}
	else if(q->next==NULL){
		temp=adjList[i]->Head;
		adjList[i]->Head=NULL;
		free(temp);
		printf("\t\tUnfriended Successfully\n");
		return;
	}
	else if(strcmp(q->usr,delFrnd)==0){
		temp=q;
		q=q->next;
		adjList[i]->Head=q;
		free(temp);
		return;
		printf("\t\tUnfriended Successfully\n");
	}
	while(strcmp(q->next->usr,delFrnd)!=0){
		q=q->next;
	}
	temp=q->next;
	q->next=q->next->next;
	free(temp);
	printf("\t\tUnfriended Successfully\n");
}
int getMsgsCount(char* usr){
	reqCount=0;
	struct node* q=head;
	while(q!=NULL){
		if(strcmp(q->to,usr)==0&&strcmp(q->msg,"Request")!=0){
			reqCount++;
		}
		q=q->next;
	}
	return reqCount;
}
void IntoTheApp(char* usr){
	char cmd='n';
	int option;
	char to[10];
	char delFrnd[15];
	while(cmd=='n'||cmd=='N'){ 
//	msgList();
	printf("\n\t\tWelcome to ChatBox\n\n");
	printf("\t\t1)View Chats(%d)\n",getMsgsCount(usr));
	printf("\t\t2)Send a message\n");
	printf("\t\t3)View Suggestions\n");
	printf("\t\t4)Friends\n");
	printf("\t\t5)Add Friends\n");
	printf("\t\t6)Friend Requests(%d)\n",getReqCount(usr));
	printf("\t\t7)Unfriend\n");
	printf("\t\t8)LogOut\n\n");
	printf("\t\tChoose any one of above:");
	scanf("%d",&option);
	switch(option){
		case 1:showChats(usr);
				break;
		case 2:printf("\t\tTo:");
				scanf("%s",to);
				sendMessage(usr,to);
				break;
		case 3:Suggestions(usr);
				sugCount=0;
				break;
		case 4:showFriends(usr);
				break;
		case 5:AddFriends(usr);
				break;
		case 6:showRequests(usr);
				break;
		case 7:if(showFriends(usr)){
					printf("\t\tEnter the username:");
					scanf("%s",delFrnd);
					Unfriend(usr,delFrnd);
				}
				break;
		case 8:return;
		default:printf("\t\tSelect valid option\n");
	}
	printf("\t\tDo you want to log out?(y/n)");
	scanf(" %c",&cmd);
	}
}
int checkDetails(char *c,char* usr){
	int i=0;
	char temp[10];
	while(c[i]!=','){
		temp[i]=c[i];
		i++;
	}
	temp[i]='\0';
	if(strcmp(temp,usr)==0){
		return i;
	}
	return 0;
}
void createAccount(char* usr,char* pass){
	FILE *fp;
	int i=0;
	char un[10];
	char c[100];
	fp=fopen("D://CDataBase.txt","r"); 
	while(fgets(c,100,fp)!=NULL){
		if(checkDetails(c,usr)){
			printf("\t\tUsername already exists. Try a different one.\n");
			return;
		}
	}
	fclose(fp);
	fp=fopen("D://CDataBase.txt","a+");
	fprintf(fp,"%s",usr);
	fprintf(fp,",");
	fprintf(fp,"%s",pass);
	fprintf(fp,",");
	fprintf(fp,"%d\n",count);
	count++;
	printf("\t\tAccount created successfully.\n\n");
	fclose(fp);
	initialiseGraph(usr);
	IntoTheApp(usr);
}
int login(char *usr,char *pass){
	char c[100];
	int t,i=0;
	char pas[10];
	FILE *fp=fopen("D://CDataBase.txt","r"); 
	while(fgets(c,100,fp)!=NULL){
		t=checkDetails(c,usr);
		if(t){
			t+=1;
			while(c[t]!=','){
				pas[i]=c[t];
				i++;
				t++;
			}
			pas[i]='\0';
			if(strcmp(pass,pas)==0){
				printf("\t\tLogged in sucessfully\n");
				IntoTheApp(usr);
				return 1;
			}
			else{
				printf("\t\t!!Wrong password. Try again\n");
				return -1;
			}
		}
	}
	printf("\t\t!!Invalid username\n");
	return 0;
}
void cleanDB(){
	FILE* fp=fopen("D://CDataBase.txt","w");
	fprintf(fp,"");
	fclose(fp);
	return;
}
int main(int argc, char** argv) {
	//login and signup
	cleanDB();
	setGraph();
	FILE* fptr;
	int i;
	char str[100],cmd='y';
	int choice;
	char usr[10],pass[10];
	i=3;
	while(cmd=='Y'||cmd=='y'){
			printf("\t\t1)Login\n");
	printf("\t\t2)SignUp\n");
	printf("\t\tSelect Option: ");
	scanf("\t%d",&choice);
	switch(choice){
		case 1:printf("\n\t\tLOGIN\n");
				printf("\t\t------------------------------------\n");
				printf("\t\t\tUsername:");
				scanf("\t\t\t%s",usr);
				printf("\t\t\tPassword:");
				scanf("\t\t\t%s",pass);
				login(usr,pass);
				break;
		case 2:printf("\n\t\tSIGNUP\n");
				printf("\t\t------------------------------------\n");
				printf("\t\t\tUsername:");
				scanf("%s",usr);
				printf("\t\t\tSet your password:");
				scanf("%s",pass);
				createAccount(usr,pass);
				break;
	}
	printf("\t\tDo you want to continue?(y/n):");
	scanf(" %c",&cmd);
	}
//	printHeads();
	cleanDB();
	printf("\t\tSee you soon! :)");
	fclose(fptr);
	return 0;
}

