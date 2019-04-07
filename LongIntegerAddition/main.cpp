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
//声明一些控件的名字
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

int InitList(DuLinkList &L)//初始化双向链表
{
    L = (DuLinkList)malloc(sizeof(DulNode));
    if(!L){//如果未分配空间成功则返回溢出
        return OVERFLOW;
    }
    L->Prior = L;
    L->Next = L;
    return OK;//否则头结点的前域和后域都赋为L 返回初始化成功
}
int DestroyList(DuLinkList &L)//销毁双向链表
{
    DulNode *p, *q;
    q = p = L->Next;
    while(p != L){//如果p指针不指向L头结点（L->next!=L）则执行
        p = p->Next;//p = p->next找到p的后一个节点，然后下一步释放q
        free(q);
        q = p;
    }
    free(L);//最后释放L头结点
    L = NULL;
    return OK;//返回成功销毁
}

int ListEmpty(DuLinkList &L)//链表为空
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
        return TRUE;//如果L的下一个节点和上一个节点都为L，则返回成功
    }
    else return FALSE;//否则返回失败
}

int ClearList(DuLinkList &L)//清空链表，原理如销毁链表
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
            return TRUE;//找到当前数值的前一个值(prior_e)
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
            return TRUE;//找到当前数值的前一个值(prior_e)
        }
        p = p->Next;//if not equal, p = p->next;
    }
    return FALSE;
}

int ListLength(DuLinkList L)//返回表长
{
    int i = 0;
    DulNode *p = L;
    while(p->Next != L){
        p = p->Next;
        ++i;
    }
    return i;
}

DulNode *GetElemP(DuLinkList L, int i)//找到某个位置的节点
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
    q->Next = p->Next;//把q插入p的后面，q的next与p的next连接
    p->Next->Prior = q;//p的next的前域与q连接
    p->Next = q;
    q->Prior = p;
    q->data = e;
    return OK;
}

void PrintList(DuLinkList L)
{
  if(L->Next->data < 0 && L->Next->Next != 0)//符号为为负数，且保证不会出现-0
  {
    printf("-");
  }
  int mark = (ListLength(L)-1) % 4;
  if(mark == 0){
    mark = 4;//防止输出第一位有逗号
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



void ProcStr(DuLinkList &L, char *s)//把字符串输入L链表
{
    InitList(L);//初始化链表
    int acc = 0;
    if(s[0] == '-'){
        ListInsert(L, 1, -233);
        acc = 1;//标志为负数
    }//如果为负数L首位数值赋值-233
    else{
        ListInsert(L, 1, 233);
    }//如果正数则首位赋值233
    int len = strlen(s);

    if(acc==1){
        for(int i = len; i > 1; i--){
            if(s[len-i+1] != ','){
                ListInsert(L, ++acc, s[len-i+1]-'0');//负数则从第二位插入数值
            }

        }
    }
    else{
        acc = 1;
        for(int i = len; i >= 1; i--){
            if(s[len-i] != ','){
                ListInsert(L, ++acc, s[len-i]-'0');
            }//正数也从第二位开始插入数值，比负数多插入一位，因为负数有符号位
        }
    }

}

void Add(DuLinkList L1, DuLinkList L2, DuLinkList &L)//两号相同的加法
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
    }//前面两步是为了把两个数位数统一为较长位数加一，如123456和123  统一为0123456和0000123，前面加0方便进位

    int ca = 0;//进位
    DulNode *p, *q;
    p = L1->Prior;
    q = L2->Prior;
    for(int i = 1; i < len_L2; i++)
    {
        mark++;//中间测试用，无实际意义
        p->data = p->data + ca;//有进位则加1，无进位则加0
        ca = 0;
        if(p->data + q->data > 9){
            ca = 1;
        }
        p->data = (p->data + q->data) % 10;//无论是否进位，相加后本位都只保留个位数
        p = p->Prior;
        q = q->Prior;
    }
    L = L1;//把结果取给L
    if(L->Next->Next->data == 0)
    {
      ListDelete(L, 2);//首位有0则删除（即第一位无进位时）
    }
}


int comp(DuLinkList L1, DuLinkList L2)//判断两个字符串绝对值的长短
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
void Sub(DuLinkList L1, DuLinkList L2, DuLinkList &L)//两号不相同则为减法
{

    int cmp = comp(L1, L2);//先排列大小顺序，用大数减小数
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
      int ex = 0;//借位，从低位到高位减法
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
    //L前有大量0的情况
    while(1){
      if(L->Next->Next->data == 0 && L->Next->Next->Next != L){//至少保留符号为和一个0
        ListDelete(L, 2);
      }
      else break;
    }
}

void Method(DuLinkList L1, DuLinkList L2, DuLinkList &L, char *str, char *str2)
{
  ProcStr(L1, str);//处理字符串
  printf("长整数1为：");
  PrintList(L1);//打印
  printf("\n");
  ProcStr(L2, str2);
  printf("长整数2为：");
  PrintList(L2);
  printf("\n");
  if(L1->Next->data * L2->Next->data < 0){
    Sub(L1, L2, L);//符号相反
  }
  else{
    Add(L1, L2, L);//符号相同
  }
  printf("运算结果为：");
  PrintList(L);
  printf("**************************\n");
}

//以下为工程自动生成
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
        //标识要控制窗口控件的句柄

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
            SetWindowText(ans_text, "“计算”则输出两个长整数求和运算结果；“重置”则重置输入");//设置text控件的文本内容
            SetWindowText(text1, "");
            SetWindowText(text2, "");
            break;
        case IDC_BUTTON3:
            MessageBeep(1);
            MessageBox(NULL,TEXT("输入格式：每四位一组，组间用逗号隔开。如：1,0000,0000,0000,0000\n\t或直接输入数字不添加分割符号。如：10000000000\n（其中\",\"为英文逗号，输入只有为数字或“,”才可以有效计算）\n可以输入最大不超过154位正整数或者负整数\n按钮介绍：\n\t重置：将输入输出文本框重置为空。\n\t计算：将“长整数1”与“长整数2”做求和运算，并在“结果”中显示求和结果。"),TEXT("帮助"),MB_OK);
            break;
        case IDC_BUTTON1://BUTTON1被点击触发事件

            char str[200], str2[200];
            //SetWindowText(ans_text, TEXT("点击了按钮"));
            GetWindowText(text1, str, 195);//把text1控件内容取出到str字符串数组，最大长度195
            GetWindowText(text2, str2, 195);
            if(strcmp(str, "") == 0 || strcmp(str2, "") == 0){
                MessageBeep(1);
                MessageBox(NULL,TEXT("长整数不能为空！"),TEXT("错误"),MB_OK);
                break;
            }
            DuLinkList L1, L2, L;
            InitList(L1);
            InitList(L2);
            InitList(L);

            Method(L1, L2, L, str, str2);
            char ans[195];
//          把L的内容传入数组
            int i = 0;
            if(L->Next->data < 0 && L->Next->Next != 0)//符号为为负数，且保证不会出现-0
            {
            ans[i] = '-';
            i++;
            }
            int mark = (ListLength(L)-1) % 4;
            if(mark == 0){
            mark = 4;//防止输出第一位有逗号
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
////////////////不带,的输出
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
            SetWindowText(ans_text, TEXT(ans));//ans调入到ans_text内显示

            DestroyList(L);
            DestroyList(L1);
            DestroyList(L2);
            break;

        }


    }
    return TRUE;
    }
    return FALSE;
    WinExec("cmd /c dir", SW_HIDE);//隐藏控制台程序
}


int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    hInst=hInstance;
    InitCommonControls();
    return DialogBox(hInst, MAKEINTRESOURCE(DLG_MAIN), NULL, (DLGPROC)DlgMain);
}
