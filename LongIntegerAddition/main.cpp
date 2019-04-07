#include <windows.h>
#include <commctrl.h>
#include <stdio.h>
#include "resource.h"

HINSTANCE hInst;
HWND button1;
HWND text1;//4
HWND text2;//5
HWND ans_text;//3
HWND b_reset;
//����һЩ�ؼ�������
#include<malloc.h>
#include<string.h>

#define OK         1
#define ERROR      0
#define OVERFLOW  -1
#define TRUE       1
#define FALSE      0
#define L1_BIG     1
#define L2_BIG     2
#define EQUAL      0

#define ElemType int

typedef struct DulNode
{
    ElemType data;
    struct DulNode *Prior;
    struct DulNode *Next;
}DulNode, *DuLinkList;

int InitList(DuLinkList &L)//��ʼ��˫������
{
    L = (DuLinkList)malloc(sizeof(DulNode));
    if(!L){//���δ����ռ�ɹ��򷵻����
        return OVERFLOW;
    }
    L->Prior = L;
    L->Next = L;
    return OK;//����ͷ����ǰ��ͺ��򶼸�ΪL ���س�ʼ���ɹ�
}
int DestroyList(DuLinkList &L)//����˫������
{
    DulNode *p, *q;
    q = p = L->Next;
    while(p != L){//���pָ�벻ָ��Lͷ��㣨L->next!=L����ִ��
        p = p->Next;//p = p->next�ҵ�p�ĺ�һ���ڵ㣬Ȼ����һ���ͷ�q
        free(q);
        q = p;
    }
    free(L);//����ͷ�Lͷ���
    L = NULL;
    return OK;//���سɹ�����
}

int ListEmpty(DuLinkList &L)//����Ϊ��
{
    if(L->Next == L && L->Prior == L)
    {DulNode *p, *q;
    q = p = L->Next;
    while(p != L){
        p = p->Next;
        free(q);
        q = p;
    }
    free(L);
    L = NULL;
    return OK;
        return TRUE;//���L����һ���ڵ����һ���ڵ㶼ΪL���򷵻سɹ�
    }
    else return FALSE;//���򷵻�ʧ��
}

int ClearList(DuLinkList &L)//�������ԭ������������
{
    DulNode *p, *q;
    q = p = L->Next;
    while(p != L){
        p = p->Next;
        free(q);
        q = p;
    }
    L->Next = L->Prior = L;
    return OK;
}

int GetPriorElem(DuLinkList L, ElemType current_e, ElemType &prior_e)//input current element and return prior element
{
    DulNode *p;
    p = L->Next->Next;//current element must has its prior element
    while(p != L)
    {
        if(p->data == current_e){
            prior_e = p->Prior->data;//save p->prior->data into &prior_e
            return TRUE;//�ҵ���ǰ��ֵ��ǰһ��ֵ(prior_e)
        }
        p = p->Next;//if not equal, p = p->next;
    }
    return FALSE;
}

int GetNextElem(DuLinkList L, ElemType current_e, ElemType &next_e)
{
    DulNode *p;
    p = L->Next->Next;//current element must has its prior element
    while(p != L)
    {
        if(p->Prior->data == current_e){
            next_e = p->data;//save p->data into &next_e
            return TRUE;//�ҵ���ǰ��ֵ��ǰһ��ֵ(prior_e)
        }
        p = p->Next;//if not equal, p = p->next;
    }
    return FALSE;
}

int ListLength(DuLinkList L)//���ر�
{
    int i = 0;
    DulNode *p = L;
    while(p->Next != L){
        p = p->Next;
        ++i;
    }
    return i;
}

DulNode *GetElemP(DuLinkList L, int i)//�ҵ�ĳ��λ�õĽڵ�
{
    DulNode *p = L;
    int j;
    for(j = 0; j < i; ++j)
    {
        p = p->Next;
    }
    return p;
}

int ListDelete(DuLinkList &L, int i)
{
	DulNode *p;
	p = L->Next;
	if(i < 0 || i > ListLength(L)){
        return ERROR;
	}
	p = GetElemP(L,i);
	p->Prior->Next = p->Next;
	p->Next->Prior = p->Prior;
	free(p);
	return OK;
}


int ListInsert(DuLinkList &L, int i, ElemType e)
{
    DulNode *p, *q;
    if(i<1 || i>ListLength(L)+1){
        return ERROR;
    }
    p = GetElemP(L, i-1);
    q = (DuLinkList)malloc(sizeof(DulNode));
    if(!q) return OVERFLOW;
    q->Next = p->Next;//��q����p�ĺ��棬q��next��p��next����
    p->Next->Prior = q;//p��next��ǰ����q����
    p->Next = q;
    q->Prior = p;
    q->data = e;
    return OK;
}

void PrintList(DuLinkList L)
{
  if(L->Next->data < 0 && L->Next->Next != 0)//����ΪΪ�������ұ�֤�������-0
  {
    printf("-");
  }
  int mark = (ListLength(L)-1) % 4;
  if(mark == 0){
    mark = 4;//��ֹ�����һλ�ж���
  }
	DulNode *p = L->Next->Next;
	while(p != L)
	{
    if(mark == 0)
    {
      printf(",");
      mark = 4;
    }
    mark--;
		printf("%d", p->data);
		p = p->Next;
	}
	printf("\n");
}



void ProcStr(DuLinkList &L, char *s)//���ַ�������L����
{
    InitList(L);//��ʼ������
    int acc = 0;
    if(s[0] == '-'){
        ListInsert(L, 1, -233);
        acc = 1;//��־Ϊ����
    }//���Ϊ����L��λ��ֵ��ֵ-233
    else{
        ListInsert(L, 1, 233);
    }//�����������λ��ֵ233
    int len = strlen(s);

    if(acc==1){
        for(int i = len; i > 1; i--){
            if(s[len-i+1] != ','){
                ListInsert(L, ++acc, s[len-i+1]-'0');//������ӵڶ�λ������ֵ
            }

        }
    }
    else{
        acc = 1;
        for(int i = len; i >= 1; i--){
            if(s[len-i] != ','){
                ListInsert(L, ++acc, s[len-i]-'0');
            }//����Ҳ�ӵڶ�λ��ʼ������ֵ���ȸ��������һλ����Ϊ�����з���λ
        }
    }

}

void Add(DuLinkList L1, DuLinkList L2, DuLinkList &L)//������ͬ�ļӷ�
{
    ///L1>L2
    int len_L1 = ListLength(L1), len_L2 = ListLength(L2);
    int mark = 0;
    if(len_L1 >= len_L2){
        ListInsert(L1, 2, 0);
        len_L1++;
        for(int i = 0; i < len_L1 - len_L2; i++)
        {
            ListInsert(L2, 2, 0);
        }
        len_L2 = len_L1;
    }
    else{
        ListInsert(L2, 2, 0);
        len_L2++;
        for(int i = 0; i < len_L2 - len_L1; i++)
        {
            ListInsert(L1, 2, 0);
        }
        len_L1 = len_L2;
    }//ǰ��������Ϊ�˰�������λ��ͳһΪ�ϳ�λ����һ����123456��123  ͳһΪ0123456��0000123��ǰ���0�����λ

    int ca = 0;//��λ
    DulNode *p, *q;
    p = L1->Prior;
    q = L2->Prior;
    for(int i = 1; i < len_L2; i++)
    {
        mark++;//�м�����ã���ʵ������
        p->data = p->data + ca;//�н�λ���1���޽�λ���0
        ca = 0;
        if(p->data + q->data > 9){
            ca = 1;
        }
        p->data = (p->data + q->data) % 10;//�����Ƿ��λ����Ӻ�λ��ֻ������λ��
        p = p->Prior;
        q = q->Prior;
    }
    L = L1;//�ѽ��ȡ��L
    if(L->Next->Next->data == 0)
    {
      ListDelete(L, 2);//��λ��0��ɾ��������һλ�޽�λʱ��
    }
}


int comp(DuLinkList L1, DuLinkList L2)//�ж������ַ�������ֵ�ĳ���
{
  int len_L1 = ListLength(L1), len_L2 = ListLength(L2);
  int mark = 0;
  if(len_L1 > len_L2){
      len_L1++;
      for(int i = 0; i < len_L1 - len_L2; i++)
      {
          ListInsert(L2, 2, 0);
      }
      len_L2 = len_L1;
  }
  else if(len_L1 < len_L2){
      len_L2++;
      for(int i = 0; i < len_L2 - len_L1; i++)
      {
          ListInsert(L1, 2, 0);
      }
      len_L1 = len_L2;
  }
  else{
      ListInsert(L1, 2, 0);
      ListInsert(L2, 2, 0);
  }

  DulNode *p = L1->Next->Next;
  DulNode *q = L2->Next->Next;
  int jud = 0;
	while(p != L1)
	{
		if(p->data > q->data){
            return L1_BIG;
        }
        else if(p->data < q->data){
            return L2_BIG;
        }
		p = p->Next;
        q = q->Next;
	}

    return EQUAL;
}
void Sub(DuLinkList L1, DuLinkList L2, DuLinkList &L)//���Ų���ͬ��Ϊ����
{

    int cmp = comp(L1, L2);//�����д�С˳���ô�����С��
    if(cmp == EQUAL){
        ListInsert(L, 1, 233);
        ListInsert(L, 2, 0);
        PrintList(L);
    }
    else if(cmp == L1_BIG){
      int len_L2 = ListLength(L2);
      DulNode *p, *q;
      p = L1->Prior;
      q = L2->Prior;
      int ex = 0;//��λ���ӵ�λ����λ����
      for(int i = 1; i < len_L2; i++)
      {
          p->data = p->data - ex;
          ex = 0;
          if(p->data - q->data < 0){
              ex = 1;
              p->data = (p->data - q->data) + 10;
          }
          else{
            p->data = p->data - q->data;
          }

          p = p->Prior;
          q = q->Prior;
      }

      L = L1;
    }
    else if(cmp == L2_BIG){
      int len_L1 = ListLength(L1);
      DulNode *p, *q;
      q = L1->Prior;
      p = L2->Prior;
      int ex = 0;
      for(int i = 1; i < len_L1; i++)
      {
          p->data = p->data - ex;
          ex = 0;
          if(p->data - q->data < 0){
              ex = 1;
              p->data = (p->data - q->data) + 10;
          }
          else{
            p->data = p->data - q->data;
          }

          p = p->Prior;
          q = q->Prior;

      }

      L = L2;
    }
    //Lǰ�д���0�����
    while(1){
      if(L->Next->Next->data == 0 && L->Next->Next->Next != L){//���ٱ�������Ϊ��һ��0
        ListDelete(L, 2);
      }
      else break;
    }
}

void Method(DuLinkList L1, DuLinkList L2, DuLinkList &L, char *str, char *str2)
{
  ProcStr(L1, str);//�����ַ���
  printf("������1Ϊ��");
  PrintList(L1);//��ӡ
  printf("\n");
  ProcStr(L2, str2);
  printf("������2Ϊ��");
  PrintList(L2);
  printf("\n");
  if(L1->Next->data * L2->Next->data < 0){
    Sub(L1, L2, L);//�����෴
  }
  else{
    Add(L1, L2, L);//������ͬ
  }
  printf("������Ϊ��");
  PrintList(L);
  printf("**************************\n");
}

//����Ϊ�����Զ�����
BOOL CALLBACK DlgMain(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{

    switch(uMsg)
    {
    case WM_INITDIALOG:
    {
        button1 = GetDlgItem(hwndDlg, IDC_BUTTON1);
        b_reset = GetDlgItem(hwndDlg, IDC_BUTTON2);
        text1 = GetDlgItem(hwndDlg, IDC_EDIT4);
        text2 = GetDlgItem(hwndDlg, IDC_EDIT5);
        ans_text = GetDlgItem(hwndDlg, IDC_EDIT3);
        //��ʶҪ���ƴ��ڿؼ��ľ��

    }
    return TRUE;

    case WM_CLOSE:
    {
        EndDialog(hwndDlg, 0);
    }
    return TRUE;

    case WM_COMMAND:
    {
        switch(LOWORD(wParam))
        {
        case IDC_BUTTON2:
            SetWindowText(ans_text, "�����㡱�������������������������������á�����������");//����text�ؼ����ı�����
            SetWindowText(text1, "");
            SetWindowText(text2, "");
            break;
        case IDC_BUTTON3:
            MessageBeep(1);
            MessageBox(NULL,TEXT("�����ʽ��ÿ��λһ�飬����ö��Ÿ������磺1,0000,0000,0000,0000\n\t��ֱ���������ֲ���ӷָ���š��磺10000000000\n������\",\"ΪӢ�Ķ��ţ�����ֻ��Ϊ���ֻ�,���ſ�����Ч���㣩\n����������󲻳���154λ���������߸�����\n��ť���ܣ�\n\t���ã�����������ı�������Ϊ�ա�\n\t���㣺����������1���롰������2����������㣬���ڡ����������ʾ��ͽ����"),TEXT("����"),MB_OK);
            break;
        case IDC_BUTTON1://BUTTON1����������¼�

            char str[200], str2[200];
            //SetWindowText(ans_text, TEXT("����˰�ť"));
            GetWindowText(text1, str, 195);//��text1�ؼ�����ȡ����str�ַ������飬��󳤶�195
            GetWindowText(text2, str2, 195);
            if(strcmp(str, "") == 0 || strcmp(str2, "") == 0){
                MessageBeep(1);
                MessageBox(NULL,TEXT("����������Ϊ�գ�"),TEXT("����"),MB_OK);
                break;
            }
            DuLinkList L1, L2, L;
            InitList(L1);
            InitList(L2);
            InitList(L);

            Method(L1, L2, L, str, str2);
            char ans[195];
//          ��L�����ݴ�������
            int i = 0;
            if(L->Next->data < 0 && L->Next->Next != 0)//����ΪΪ�������ұ�֤�������-0
            {
            ans[i] = '-';
            i++;
            }
            int mark = (ListLength(L)-1) % 4;
            if(mark == 0){
            mark = 4;//��ֹ�����һλ�ж���
            }
            DulNode *p = L->Next->Next;
            while(p != L)
            {
            if(mark == 0)
            {
                ans[i] = ',';
                i++;
                mark = 4;
            }
            mark--;
            ans[i] = p->data + '0';
            i++;
                p = p->Next;
            }
            ans[i] = '\0';
//////////////////////////////////////////////////////////
////////////////����,�����
//            DulNode *p;
//            p = L->Next->Next;
//            if(L->Next->data < 0){
//                ans[0] = '-';
//            for(int i = 1; i < ListLength(L); i++)
//            {
//                ans[i] = p->data + '0';
//                p = p->Next;
//            }
//            }
//            else{
//            for(int i = 0; i < ListLength(L)-1; i++)
//            {
//                ans[i] = p->data + '0';
//                p = p->Next;
//            }
//
//            }
//////////////////////////////////////////////////////////
            SetWindowText(ans_text, TEXT(ans));//ans���뵽ans_text����ʾ

            DestroyList(L);
            DestroyList(L1);
            DestroyList(L2);
            break;

        }


    }
    return TRUE;
    }
    return FALSE;
    WinExec("cmd /c dir", SW_HIDE);//���ؿ���̨����
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
