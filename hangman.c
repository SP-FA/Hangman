#pragma warning(disable : 4996)
#pragma warning(disable : 6031)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const int MAX_SIZE = 100;

/******************************************************************\
STRUCT: Account
DESCRIPTION: �����˻���Ϣ
\******************************************************************/
struct Account {
	char accountNumber[MAX_SIZE];
	char password[MAX_SIZE];
	int winNumber;
	int totalNumber;
};

/******************************************************************\
STRUCT: Node
DESCRIPTION: ���˻���Ϣ�浽һ��������
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
DESCRIPTION: ����ջ������е�\n���ٶ���һ���ַ���
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
DESCRIPTION: ���ļ��ж�ȡ�˻���Ϣ
RETURN VALUE: Node * ����һ���ṹ��ָ�룬��ʾ�����ͷ�ڵ�
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
DESCRIPTION: ���˻���Ϣд���ļ�
PARAMETER:
@ accountList: һ���ṹ��ָ�룬��ʾ�����ͷ�ڵ�
RETURN VALUE: bool ������ֵΪ�٣���˵�����������
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
DESCRIPTION: ����һ���˻�
PARAMETER:
@ Account *cur: һ���ṹ��ָ�룬��������˻���������
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
DESCRIPTION: ��������Ѱ�Ҵ�����˻������ҵ��򷵻�
PARAMETER:
@ Account *cur: һ���ṹ��ָ�룬������˻�
RETURN VALUE: Account * �����ҵ����˻���û�ҵ����� NULL
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
DESCRIPTION: ��������Ѱ�Ҵ�����˻�
PARAMETER:
@ Account *cur: һ���ṹ��ָ�룬������˻�
RETURN VALUE: bool ������û���ҵ����˻�
\******************************************************************/
bool HaveAccount(Account* cur) {
	if (FindAccount(cur) == NULL) return 0;
	return 1;
}

/******************************************************************\
FUNCTION: CheckPassword
DESCRIPTION: �ж�����Բ���
PARAMETER:
@ Account *cur: һ���ṹ��ָ�룬�ж�����˻�
RETURN VALUE: bool ��������Բ���
\******************************************************************/
bool CheckPassword(Account* cur) {
	Account* chkcur = FindAccount(cur);
	if (!strcmp(chkcur->password, cur->password)) return 1;
	return 0;
}

/******************************************************************\
FUNCTION: SignIn
DESCRIPTION: ע��
RETURN VALUE: Account * ����ע����˺�
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
DESCRIPTION: ��¼
RETURN VALUE: Account * ���ص�¼���˺�
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
DESCRIPTION: ���ļ������ѡȡһ������
RETURN VALUE: char * ���ص��ʣ����޷����ļ��������ض��ַ�����û���
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
DESCRIPTION: �ֶ�����һ������
RETURN VALUE: char * ���ص���
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
DESCRIPTION: �����û�ж�Ӧ����ĸ�����Ҹ��� vis ��ֵ
PARAMETER:
@ c : �ַ�����ʾ��Ҳµ���ĸ
@ vis: �������͵����飬������¼��Щλ���Ѿ����³�����
@ word: �ַ�����secret word
RETURN VALUE: bool ����µ���ĳ����ĸ���򷵻� 1�����򷵻� 0
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
DESCRIPTION: �ж��Ƿ�Ӯ������Ϸ
PARAMETER:
@ vis: �������͵����飬������¼��Щλ���Ѿ����³�����
@ word: �ַ�����secret word
RETURN VALUE: bool ������ֵΪ�٣���˵����ʱ��ûӮ����Ϸ������������
\******************************************************************/
bool isWin(bool* vis, char* word) {
	for (int i = 0; i < (int)strlen(word); i++) {
		if (!vis[i]) return 0;
	}
	return 1;
}

/******************************************************************\
FUNCTION: Start
DESCRIPTION: ��ʼ��Ϸ
PARAMETER:
@ Account *player: �˻���Ϣ
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
DESCRIPTION: �鿴��ʷս��
PARAMETER:
@ Account *player: �˻���Ϣ
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
DESCRIPTION: �����ʷս��
PARAMETER:
@ Account *player: �˻���Ϣ
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
DESCRIPTION: �˳���¼״̬
PARAMETER:
@ Account *player: �˻���Ϣ
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
DESCRIPTION: ��¼��ɺ���û�ѡ�����
PARAMETER:
@ Account *player: �˻���Ϣ
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