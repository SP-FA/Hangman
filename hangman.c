#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const int MAX_SIZE = 100;

/******************************************************************\
STRUCT: Account
DESCRIPTION: 保存账户信息
\******************************************************************/
struct Account {
	char accountNumber[MAX_SIZE];
	char password[MAX_SIZE];
	int winNumber;
	int totalNumber;
};

/******************************************************************\
STRUCT: Node
DESCRIPTION: 把账户信息存到一个链表里
\******************************************************************/
struct Node {
	Account* data;
	Node* next;
};

void PrintTitle() {
	printf("===========================\n");
	printf("=   -- H A N G M A N --   =\n"); //hangman
	printf("===========================\n");
	printf("\n");
}

void PrintHangman(int i) {
	char s1[2] = { ' ', '-' };
	char s2[2] = { ' ', '|' };
	char s3[2] = { ' ', '-' };
	char s4[2] = { ' ', '|' };
	char s5[2] = { ' ', 'O' };
	char s6[2] = { ' ', '|' };
	char s7[2] = { ' ', '/' };
	char s8[2] = { ' ', '\\' };

	/*    printf("--------\n");
	printf(" |  |   \n");
	printf(" |  O   \n");
	printf(" |  |   \n");
	printf(" | / \\ \n");
	printf(" |      \n");
	printf("--------\n");*/
	printf("===========================\n");
	printf("=                         =\n");
	printf("=        %c%c%c%c%c%c%c%c         =\n", s3[i < 3], s3[i < 3], s3[i < 3], s3[i < 3], s3[i < 3], s3[i < 3], s3[i < 3], s3[i < 3]);
	printf("=         %c  %c            =\n", s2[i < 2], s4[i < 4]);
	printf("=         %c  %c            =\n", s2[i < 2], s5[i < 5]);
	printf("=         %c  %c            =\n", s2[i < 2], s6[i < 6]);
	printf("=         %c %c %c           =\n", s2[i < 2], s7[i < 7], s8[i < 8]);
	printf("=         %c               =\n", s2[i < 2]);
	printf("=        %c%c%c%c%c%c%c%c         =\n", s1[i < 1], s1[i < 1], s1[i < 1], s1[i < 1], s1[i < 1], s1[i < 1], s1[i < 1], s1[i < 1]);
	printf("=                         =\n");
	printf("===========================\n");
}

void PrintWord(bool* vis, char* word) {
	int i;
	for (i = 0; i < (int)strlen(word); i++) {
		if (vis[i]) printf("%c", word[i]);
		else printf("?");
	}
	printf("\n");
}

/******************************************************************\
FUNCTION: readin
DESCRIPTION: 先清空缓存区中的\n，再读入一个字符串
\******************************************************************/
void readin(char* str) {
	while (1) {
		str[0] = getchar();
		if (str[0] != '\n' && str[0] != EOF) {
			gets(str + 1);
			return;
		}
	}
}

/******************************************************************\
FUNCTION: LoadList
DESCRIPTION: 从文件中读取账户信息
RETURN VALUE: Node * 返回一个结构体指针，表示链表的头节点
\******************************************************************/
Node* LoadList() {
	FILE* fp;
	Node* accountList = (Node*)malloc(sizeof(Node));
	Node* head = accountList;
	fp = fopen("account.txt", "rb");
	if (fgetc(fp) == EOF) return NULL;
	fseek(fp, 0, SEEK_SET);
	while (fgetc(fp) != EOF) {
		fseek(fp, -1, SEEK_CUR);
		Node* newP = (Node*)malloc(sizeof(Node));
		newP->data = (Account*)malloc(sizeof(Account));
		fread(newP->data, sizeof(Account), 1, fp);
		accountList->next = newP;
		newP->next = NULL;
		accountList = newP;
	}
	accountList->next = NULL;
	fclose(fp);
	return head->next;
}

/******************************************************************\
FUNCTION: SaveList
DESCRIPTION: 将账户信息写入文件
PARAMETER:
@ accountList: 一个结构体指针，表示链表的头节点
RETURN VALUE: bool 若返回值为假，则说明程序出错了
\******************************************************************/
bool SaveList(Node* accountList) {
	FILE* fp;
	fp = fopen("account.txt", "wb");
	while (accountList != NULL) {
		fwrite(accountList->data, sizeof(Account), 1, fp);
		accountList = accountList->next;
	}
	fclose(fp);
	return 1;
}

/******************************************************************\
FUNCTION: ScanAccount
DESCRIPTION: 读入一个账户
PARAMETER:
@ Account *cur: 一个结构体指针，将读入的账户存入这里
\******************************************************************/
void ScanAccount(Account* cur) {
	while (1) {
		char* buffer = (char*)malloc(10 * MAX_SIZE * sizeof(char));
		printf("Please enter your account number: (between 1 and 100 letters)");
		readin(buffer);
		if (strlen(buffer) > MAX_SIZE) {
			printf("Too long for the account number, please enter angain");
			system("pause");
			continue;
		}
		else {
			strcpy(cur->accountNumber, buffer);
		}
		strcpy(buffer, "");
		printf("Please enter your account pass word: (between 1 and 100 letters)");
		readin(buffer);
		if (strlen(buffer) > MAX_SIZE) {
			printf("Too long for the password, please enter angain");
			system("pause");
			continue;
		}
		else {
			strcpy(cur->password, buffer);
			return;
		}
	}
}

/******************************************************************\
FUNCTION: FindAccount
DESCRIPTION: 在链表中寻找传入的账户，若找到则返回
PARAMETER:
@ Account *cur: 一个结构体指针，找这个账户
RETURN VALUE: Account * 返回找到的账户，没找到返回 NULL
\******************************************************************/
Account* FindAccount(Account* cur) {
	Node* head = LoadList();
	while (head != NULL) {
		if (!strcmp(head->data->accountNumber, cur->accountNumber)) {
			return head->data;
		}
		head = head->next;
	}
	return NULL;
}

/******************************************************************\
FUNCTION: HaveAccount
DESCRIPTION: 在链表中寻找传入的账户
PARAMETER:
@ Account *cur: 一个结构体指针，找这个账户
RETURN VALUE: bool 返回有没有找到的账户
\******************************************************************/
bool HaveAccount(Account* cur) {
	if (FindAccount(cur) == NULL) return 0;
	return 1;
}

/******************************************************************\
FUNCTION: CheckPassword
DESCRIPTION: 判断密码对不对
PARAMETER:
@ Account *cur: 一个结构体指针，判断这个账户
RETURN VALUE: bool 返回密码对不对
\******************************************************************/
bool CheckPassword(Account* cur) {
	Account* chkcur = FindAccount(cur);
	if (!strcmp(chkcur->password, cur->password)) return 1;
	return 0;
}

/******************************************************************\
FUNCTION: SignIn
DESCRIPTION: 注册
RETURN VALUE: Account * 返回注册的账号
\******************************************************************/
Account* SignIn() {
	Account* cur = (Account*)malloc(sizeof(Account));
	ScanAccount(cur);
	if (!HaveAccount(cur)) {
		cur->winNumber = 0;
		cur->totalNumber = 0;
		printf("You have successfully created an account!\n");
		system("pause");
	}
	else {
		printf("It is already have an account, please enter angain.\n");
		system("pause");
		cur = SignIn();
	}
	return cur;
}

/******************************************************************\
FUNCTION: Login
DESCRIPTION: 登录
RETURN VALUE: Account * 返回登录的账号
\******************************************************************/
Account* Login() {
	int selection = 0;
	Account* cur = (Account*)malloc(sizeof(Account));
	ScanAccount(cur);
	if (HaveAccount(cur)) {
		if (CheckPassword(cur)) {
			printf("Welcome back, dear %s\n", cur->accountNumber);
			system("pause");
			return FindAccount(cur);
		}
		else {
			printf("Incorrect password, please 1)try again 2)sign in\n");
			scanf("%d", &selection);
			if (selection == 1)
				cur = Login();
			else cur = SignIn();
		}
	}
	else {
		printf("The account does not exist, please 1)try again 2)sign in\n");
		scanf("%d", &selection);
		if (selection == 1)
			cur = Login();
		else cur = SignIn();
	}
	return cur;
}

/******************************************************************\
FUNCTION: RandomSecretWord
DESCRIPTION: 从文件中随机选取一个单词
RETURN VALUE: char * 返回单词，若无法打开文件，返回特定字符（还没想好
\******************************************************************/
char* RandomSecretWord() {
	FILE* fp;
	char* buffer = (char*)malloc(MAX_SIZE * sizeof(char));
	int len = 0;
	srand(time(NULL));
	int tot = 0;
	int num = 0;
	fp = fopen("data.txt", "rb");
	while (fgetc(fp) != EOF) {
		fseek(fp, -1, SEEK_CUR);
		fgets(buffer, MAX_SIZE, fp);
		tot++;
	}
	num = rand() % tot + 1;
	fseek(fp, 0, SEEK_SET);
	for (int i = 1; i <= num; i++) {
		fgets(buffer, MAX_SIZE, fp);
	}
	len = strlen(buffer);
	buffer[len - 2] = '\0';
	printf("The secret word is: %s", buffer);
	system("pause");
	return buffer;
}

/******************************************************************\
FUNCTION: EnterSecretWord
DESCRIPTION: 手动输入一个单词
RETURN VALUE: char * 返回单词
\******************************************************************/
char* EnterSecretWord() {
	char* buffer;
	while (1) {
		buffer = (char*)malloc(10 * MAX_SIZE * sizeof(char));
		printf("Please enter a word: (between 1 to 100 letters)");
		readin(buffer);
		if (strlen(buffer) > MAX_SIZE) {
			printf("Too long for the secret word, please enter angain");
			system("pause");
			continue;
		}
		else {
			printf("The secret word is: %s", buffer);
			break;
		}
	}
	return buffer;
}

/******************************************************************\
FUNCTION: isWin
DESCRIPTION: 检查有没有对应的字母，并且更新 vis 的值
PARAMETER:
@ c : 字符，表示玩家猜的字母
@ vis: 布尔类型的数组，用来记录哪些位置已经被猜出来了
@ word: 字符串，secret word
RETURN VALUE: bool 如果猜到了某个字母，则返回 1，否则返回 0
\******************************************************************/
bool CheckWord(char c, bool* vis, char* word) {
	bool flag = 0;
	for (int i = 0; i < (int)strlen(word); i++) {
		if (word[i] == c) {
			vis[i] = 1;
			flag = 1;
		}
	}
	return flag;
}

/******************************************************************\
FUNCTION: isWin
DESCRIPTION: 判断是否赢得了游戏
PARAMETER:
@ vis: 布尔类型的数组，用来记录哪些位置已经被猜出来了
@ word: 字符串，secret word
RETURN VALUE: bool 若返回值为假，则说明暂时还没赢得游戏，而不是输了
\******************************************************************/
bool isWin(bool* vis, char* word) {
	for (int i = 0; i < (int)strlen(word); i++) {
		if (!vis[i]) return 0;
	}
	return 1;
}

/******************************************************************\
FUNCTION: Start
DESCRIPTION: 开始游戏
PARAMETER:
@ Account *player: 账户信息
\******************************************************************/
void Start(Account* player) {
	int selection = 0;
	char* word;
	bool vis[MAX_SIZE];
	char c[MAX_SIZE];
	system("cls");
	PrintTitle();
	printf("***************************\n");
	printf("* 1. Random secret word   *\n");
	printf("* 2. enter a secret word  *\n");
	printf("***************************\n");
	scanf("%d", &selection);
	while (1) {
		if (selection == 1) {
			word = RandomSecretWord();
			break;
		}
		else if (selection == 2) {
			word = EnterSecretWord();
			break;
		}
		else {
			printf("Invalid selection, please try again.\n");
		}
	}
	for (int i = 0; i < (int)strlen(word); i++) {
		vis[i] = 0;
	}
	selection = 0;
	for (int i = 0; i <= 8; i++) {
		system("cls");
		PrintTitle();
		PrintHangman(i);
		PrintWord(vis, word);
		if (i == 8) break;
		printf("Please guess a letter: ");
		while (1) {
			readin(c);
			if (strlen(c) != 1) {
				printf("you only can enter one letter at a time, please enter angain: ");
			}
			else {
				break;
			}
		}
		if (CheckWord(c[0], vis, word)) i--;
		if (isWin(vis, word)) {
			player->winNumber++;
			player->totalNumber++;
			selection = 1;
			printf("Congratulations on your victory!\n");
			break;
		}
	}
	if (selection == 0) {
		player->totalNumber++;
		printf("you lost\n");
	}
	system("pause");
}

/******************************************************************\
FUNCTION: ReviewHistory
DESCRIPTION: 查看历史战绩
PARAMETER:
@ Account *player: 账户信息
\******************************************************************/
void ReviewHistory(Account* player) {
	system("cls");
	PrintTitle();
	printf("***************************\n");
	printf("* %s\n", player->accountNumber);
	printf("* Win number: %d\n", player->winNumber);
	printf("* Total number: %d\n", player->totalNumber);
	printf("***************************\n");
	system("pause");
}

/******************************************************************\
FUNCTION: ClearHistory
DESCRIPTION: 清空历史战绩
PARAMETER:
@ Account *player: 账户信息
\******************************************************************/
void ClearHistory(Account* player) {
	int flag = 0;
	printf("Are you sure to clear your history? 1) clear 2) do not clear\n");
	scanf("%d", &flag);
	if (flag == 1) {
		player->winNumber = 0;
		player->totalNumber = 0;
		printf("Your history has already cleared.\n");
	}
	else {
		printf("Operation cancelled.\n");
	}
	system("pause");
}

/******************************************************************\
FUNCTION: Logout
DESCRIPTION: 退出登录状态
PARAMETER:
@ Account *player: 账户信息
\******************************************************************/
void Logout(Account* player) {
	Node* head = LoadList();
	Node* temp = head;
	if (!HaveAccount(player)) {
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->data = player;
		newNode->next = head;
		head = newNode;
	}
	else {
		while (temp != NULL) {
			if (!strcmp(temp->data->accountNumber, player->accountNumber)) {
				temp->data->winNumber = player->winNumber;
				temp->data->totalNumber = player->totalNumber;
			}
			temp = temp->next;
		}
	}
	SaveList(head);
}

/******************************************************************\
FUNCTION: UserSelect
DESCRIPTION: 登录完成后的用户选择界面
PARAMETER:
@ Account *player: 账户信息
\******************************************************************/
void UserSelect(Account* player) {
	int flag = 1;
	int selection = 0;
	while (1) {
		flag = 1;
		system("cls");
		PrintTitle();
		printf("***************************\n");
		printf("* 1. Start a new game     *\n");
		printf("* 2. Review game history  *\n");
		printf("* 3. Clear game history   *\n");
		printf("* 4. Logout               *\n");
		printf("***************************\n");
		while (flag) {
			scanf("%d", &selection);
			switch (selection) {
			case 1:
				Start(player);
				flag = 0;
				break;
			case 2:
				ReviewHistory(player);
				flag = 0;
				break;
			case 3:
				ClearHistory(player);
				flag = 0;
				break;
			case 4:
				Logout(player);
				return;
			default:
				printf("Invalid selection, please try again.\n");
				flag = 1;
			}
		}
	}
}

int main(void) {
	int flag = 1;
	int selection = 0;
	Account* player = NULL;
	while (1) {
		flag = 1;
		system("cls");
		PrintTitle();
		printf("***************************\n");
		printf("* 1. login                *\n");
		printf("* 2. sign in              *\n");
		printf("* 3. exist game           *\n");
		printf("***************************\n");
		while (flag) {
			scanf("%d", &selection);
			switch (selection) {
			case 1:
				player = Login();
				flag = 0;
				break;
			case 2:
				player = SignIn();
				flag = 0;
				break;
			case 3:
				return 0;
			default:
				printf("Invalid selection, please try again.\n");
				flag = 1;
			}
		}
		UserSelect(player);
	}
	return 0;
}