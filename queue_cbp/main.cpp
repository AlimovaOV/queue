#include <iostream>
#include <stdlib.h>
#include <ctime>
/*
* �� ���� �������:
* �������� "-1" ��������, ��� � ������ ������ ��� �������� �� ������������
* ������� ��������� ������� ����� ������ � ������� q*
*                  const double T*1 = -1; //
*                  const double T*2 = -1; //
* ������� ��������� ������� ��������� ������ � ��*
*                  const double W*1 = 0;
*                  const double W*2 = 0.02;
* ����������:
*   q* �������
*   ptr - ��������� �� ��������� ������(�����)
*   tmp* - ��������� �� ������, ����������� �� ������� q*
* 	n(n1, n2) - ����� ������, � ������ ������� ���� ������ �������������
* 	tw* ����� ������ ��*
* 	ts* ����� ������� ��*
* 	ti* ����� ����� ��������� ������ � ��*
* 	cc1* ���������� ������ ������� ���� ��������� ����� ��*
* 	cc2* ���������� ������ ������� ���� ��������� ����� ��*
* 	m* ������������ ����� �������� � ������� q*
*  	s* ����� ����� �������� ���� ������ � ������� q*
* 	x* ����� ������ � ������������ �������� �������� � ������� q*
* 	tx* ��� ������ � ������������ �������� �������� � ������� q*
*/

using namespace std;
using std::cout;

typedef struct link
{
	int id;
	int type, // ��� �������, �����������, ������� � ����������� �� �������
		from; // ���� �������� ������� � ������� ����� ��, ����� ������� �� ����� ��������
	double time_in, time_work, time_out;
	link* next,
		* prev;
} list;

struct queue
{
	list* head = NULL;
	list* tail = NULL;
	int countin = 0;
	int countout = 0;
	double tec_time = 0;
};
//                         task1:
//const double T11 = 0;
//const double T12 = 10;
//const double W11 = 0;
//const double W12 = 2;
//const double T21 = -1;//
//const double T22 = -1;//
//const double W21 = -1;//
//const double W22 = -1;//

//                         task2:
//const double T11 = 0;
//const double T12 = 5;
//const double W11 = 0;
//const double W12 = 4;
//const double T21 = -1;//
//const double T22 = -1;//
//const double W21 = 0;
//const double W22 = 4;

////                         task3:
//const double T11 = -1;//
//const double T12 = -1;//
//const double W11 = 0;
//const double W12 = 6;
//const double T21 = -1;//
//const double T22 = -1;//
//const double W21 = 1;
//const double W22 = 8;

//                         task4:
//const double T11 = 0;
//const double T12 = 6;
//const double W11 = 0;
//const double W12 = 1;
//const double T21 = -1;//
//const double T22 = -1;//
//const double W21 = -1;//
//const double W22 = -1;//

//                         task5:
//const double T11 = 1;
//const double T12 = 5;
//const double W11 = 0;
//const double W12 = 4;
//const double T21 = 0;
//const double T22 = 3;
//const double W21 = 0;
//const double W22 = 1;

//                         task6:
const double T11 = 1;
const double T12 = 3;
const double W11 = 3;
const double W12 = 5;
const double T21 = -1;//
const double T22 = -1;//
const double W21 = 0;
const double W22 = 2;

//                         task7:
//const double T11 = 1;
//const double T12 = 3;
//const double W11 = 0;
//const double W12 = 2;
//const double T21 = 1;
//const double T22 = 5;
//const double W21 = 1;
//const double W22 = 3;

//                         task8:
//const double T11 = -1; //
//const double T12 = -1; //
//const double W11 = 0;
//const double W12 = 0.02;
//const double T21 = -1; //
//const double T22 = -1; //
//const double W21 = 1;
//const double W22 = 5;
const double W31 = 3;
const double W32 = 9;

const int nn = 1000; // ���-�� ������ ��� ���������

list* create(int a, int x) //�������� �������� ������� ��� ������� ����
{
	double t1, t2, w1, w2;
	if (x == 1)
	{
		t1 = T11;
		t2 = T12;
		w1 = W11;
		w2 = W12;
	}
	else
	{
		t1 = T21;
		t2 = T22;
		w1 = W21;
		w2 = W22;
	}
	list* tmp = new list;
	tmp->id = a;
	tmp->type = x;
	tmp->from = 1;
	tmp->time_work = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
	tmp->time_in = t1 + (t2 - t1) * (double)rand() / RAND_MAX;
	tmp->time_out = 0;
	tmp->next = NULL;
	tmp->prev = NULL;
	return tmp;
}
void change_in(list* ptr, double t1, double t2) //��������� ������� �����
{
	ptr->time_in = t1 + (t2 - t1) * (double)rand() / RAND_MAX;
}
void change_from(list* ptr, int a) //��������� ������� �����
{
	ptr->from = a;
}
void change_work(list* ptr, double w1, double w2) //��������� ������� ������
{
	ptr->time_work = w1 + (w2 - w1) * (double)rand() / RAND_MAX;
}
void set_out(list* ptr, double t1) //��������� ������� ������
{
	ptr->time_out = t1;
}
void set_in(list* ptr, double t1) //��������� ������� �����
{
	ptr->time_in = t1;
}
void set_type(list* ptr, int t1) //��������� type
{
	ptr->type = t1;
}
void set_work(list* ptr, double t1) //��������� ������� ������
{
	ptr->time_work = t1;
}
void push(queue& q, list* tmp) //�������� � ����� �������
{
	//    cout<<tmp->id;
	tmp->next = q.tail;
	if (q.tail)
		q.tail->prev = tmp;
	else
		q.head = tmp;
	q.countin++;
	if (tmp->from) q.tec_time += tmp->time_in;
	tmp->time_in = q.tec_time;
	q.tail = tmp;
}
void print(queue q) //����� �� ������ � ������
{
	cout << " -> ";
	list* last = q.tail;
	while (last)
	{
		//cout << last->id << '(' << last->type << ", " << last->time_in << ')' << " -> ";
		cout << last->id << '(' << last->type << ", " << last->time_in << ", " << last->time_work << ", " << last->time_out << ')' << " -> ";
		last = last->next;
	}
}
void print_reverse(queue q) //����� �� ������ � ������
{
	list* first = q.head;
	while (first)
	{
		cout << " <- " << first->id << '(' << first->time_in << ", " << first->time_work << ')';
		first = first->prev;
	}
	cout << " <- ";
}
list* pop(queue& q) //������� ������� �� ������ �������
{
	list* tmp = q.head;
	if (q.head)
	{
		if (q.tec_time) tmp->time_out = max(q.tec_time, tmp->time_in);
		//if (q.tec_time) tmp->time_out = q.tec_time;
		q.head = q.head->prev;
		if (q.head)
			q.head->next = NULL;
		else
			q.tail = NULL;
	}
	else q.tail = NULL;
	if (tmp)
	{
		q.countout++;
		tmp->next = NULL;
		tmp->prev = NULL;
	}
	//    if (tmp) cout<<endl<<"pop = "<<tmp->id;
	//    else cout<<endl<<"pop = NULL";
	return tmp;
}
list* top(queue& q)
{
	list* tmp = q.head;
	return tmp;
}
void add(int k, queue& q, list* elm) // �������� �� ����� �-��� �����, ������ � ������
{
	if (k > 0)
	{
		list* tmp = q.head;
		int i = 0;
		if (tmp)
		{
			while (i < k - 1 && tmp->prev)
			{
				tmp = tmp->prev;
				i++;
			}
			if (tmp->prev)
				tmp->prev->next = elm;
			else
				q.tail = elm;
			elm->prev = tmp->prev;
			elm->next = tmp;
			tmp->prev = elm;
		}
		else
		{
			q.head = elm;
			q.tail = elm;
		}
	}
	else
	{
		elm->prev = q.head;
		if (q.head)
			q.head->next = elm;
		else
			q.tail = elm;
		q.head = elm;
	}
	q.countin++;
}
list* oa(queue& q, double& t_work, double& t_stop, double& t_in, int& t1, int& t2) //������������� ������ ��
{
	list* ptr = pop(q);
	if (ptr)
	{
		if (ptr->type % 2 == 1)
			t1++;
		else t2++;
		if (t_work == 0)
		{
			t_stop = ptr->time_in;
			//cout << endl << "+++++++++++++++++++++" << ptr->id << " + " << ptr->type << "(" << ptr->time_in << ", " << t_work << ")" << endl;
			t_work = ptr->time_in + ptr->time_work;
			t_in = ptr->time_in;
		}
		else
		{
			if (ptr->time_out < t_work)
			{
				t_in = t_work;
				ptr->time_out = t_in;
				t_work += ptr->time_work;
			}
			else
			{
				t_stop += ptr->time_out - t_work;
				//cout << endl << "********************" << ptr->id << " + " << ptr->type << "(" << ptr->time_out << ", " << t_work << ")" << endl;
				t_in = ptr->time_out;
				t_work = t_in + ptr->time_work;
			}
		}
	}
	//if (ptr != NULL) {
	//	cout << endl << " pop = ";
	//	cout << ptr->id << '(' << ptr->type << ", " << ptr->time_in << ", " << ptr->time_work << ", " << ptr->time_out << ')' << endl;
	//}
	return ptr;
}
void statistic(list* ptr, int& id, int& ch, double& mx, double& sum)
{
	if (ptr->time_out - ptr->time_in > mx || (ptr->time_out - ptr->time_in == 0 && mx == 0))
	{
		mx = ptr->time_out - ptr->time_in;
		id = ptr->id;
		ch = ptr->type;
	}
	sum += ptr->time_out - ptr->time_in != 0 ? ptr->time_out - ptr->time_in : ptr->time_work;
}
void task1() // ��
{
	queue q;
	int n = 0;
	list* ptr = create(n, 1);
	n++;
	push(q, ptr);
	//cout<<endl<<"lst = ";
	//print(q);
	ptr = NULL;
	double tw = 0, ts = 0, ti = 0;
	double m = 0, s = 0;
	int cc1 = 0, cc2 = 0, x, tx;
	list* tmp = oa(q, tw, ts, ti, cc1, cc2);
	if (tmp)
	{
		statistic(tmp, x, tx, m, s);
	}
	while (tmp)
	{
		//cout << endl << "lst = ";
		//print(q);
		if (n < nn)
		{
			if (ptr == NULL)  //���� ��������� � �������, �� ���� ������� �����
			{
				ptr = create(n, 1);
				n++;
			}
			if (q.tec_time + ptr->time_in < tw)  //����� ����� ������ ������� ������ ������� ������ ��
			{
				push(q, ptr);    //������� ������
				ptr = NULL;
				/*  cout << endl << " push new q.tec_time + ptr->time_in < tw lst = ";
				  print(q);  */
			}
			else if (tmp->type < 4) //����� ����� ������ ������� ������ ������� ������ ��
			{
				tmp->type++;
				change_from(tmp, 0);//������������ ������� ������������ � �������
				push(q, tmp);
				set_in(tmp, tmp->time_out + tmp->time_work);
				/* cout << endl << " push old tmp->type < 4 lst = ";
				 print(q);*/
				tmp = oa(q, tw, ts, ti, cc1, cc2); //����. ������� ���� �� ���������
				if (tmp)
				{
					statistic(tmp, x, tx, m, s);
				}
			}
		}
		else                    //�� ���� ��������� �������
		{
			if (tmp->type < 4)          //������������ ������� ����� nn
			{
				tmp->type++;
				change_from(tmp, 0);
				push(q, tmp);
				set_in(tmp, tmp->time_out + tmp->time_work);
				/* cout << endl << " push old n >= nn lst = ";
				 print(q);*/
				tmp = oa(q, tw, ts, ti, cc1, cc2);
				if (tmp)
				{
					statistic(tmp, x, tx, m, s);
				}
			}
		}
		if (tmp->type >= 4)      //������� ������ 4 ����� ���������
		{
			delete (tmp);
			tmp = oa(q, tw, ts, ti, cc1, cc2); //����� ����. �������
			if (tmp)
			{
				statistic(tmp, x, tx, m, s);
			}
			else if (ptr)             //��������� ���� �� ����� �� nn � ������� ������
			{
				push(q, ptr);
				ptr = NULL;
				/* cout << endl << " push new tmp = NULL lst = ";
				 print(q);*/
				tmp = oa(q, tw, ts, ti, cc1, cc2); //����� ����. �������
				if (tmp)
				{
					statistic(tmp, x, tx, m, s);
				}
			}

		}
		if ((cc1 + cc2) % (nn / 10) == 0)  // ����� ���������� ������ 100 �����
		{
			cout << endl << "task " << x << " (" << tx << ")  max = " << m << " aver = " << s / (cc1 + cc2) << endl;
			cout << "queue in = " << q.countin << " queue length = " << q.countin - q.countout << endl;
		}
	}
	cout << endl << endl;
	cout << "queue in = " << q.countin << " queue out = " << q.countout << endl;
	cout << "task count = " << (cc1 + cc2) << " time_work = " << tw << " time_stop = " << ts << endl;
}
void task2() // ��
{
	queue q;
	list* ptr = create(-1, 2); //������� ������� ����
	set_in(ptr, 0);
	push(q, ptr);
	ptr = NULL;
	int n = 0;
	double tw = 0, ts = 0, ti = 0;
	double m = 0, s = 0;
	int cc1 = 0, cc2 = 0, x, tx;
	list* tmp = oa(q, tw, ts, ti, cc1, cc2); //����� �� ���������
	if (tmp)
	{
		statistic(tmp, x, tx, m, s);
	}
	while (tmp)
	{

		if (n < nn)
		{
			if (ptr == NULL)  //���� ��������� � �������, �� ���� ������� �����
			{
				ptr = create(n, 1);
				n++;
			}
			if (q.tec_time + ptr->time_in < tw)  // ����� ����� ������ ������� ������ ������� ������ tw
			{
				push(q, ptr);    //������� ������
				ptr = NULL;
			}
			else
			{
				if (tmp->type == 2)  //������� 2 ���� ���������� � �������
				{
					tmp->time_in = tw;
					add(4, q, tmp);
				}
				else delete tmp;  //����� �������
				tmp = oa(q, tw, ts, ti, cc1, cc2); //����. ������� ���� �� ���������
				if (tmp)
				{
					statistic(tmp, x, tx, m, s);
				}
			}
		}
		else                                //�� ���� ��������� ����� �������
		{
			if (ptr)
			{
				push(q, ptr);    //��������� �������
				ptr = NULL;
			}
			if (tmp->type == 2 && q.head)          //������������ ������� ����� nn
			{
				tmp->time_in = tw;
				add(4, q, tmp);
			}
			else   delete (tmp);
			tmp = oa(q, tw, ts, ti, cc1, cc2);
			if (tmp)
			{
				statistic(tmp, x, tx, m, s);
			}
		}
		if ((cc1 + cc2) % (nn / 10) == 0)  // ����� ���������� ������ 100 �����
		{
			cout << endl << "task " << x << " (" << tx << ")  max = " << m << " aver = " << s / (cc1 + cc2) << endl;
			cout << "queue in = " << q.countin << " queue length = " << q.countin - q.countout << endl;
		}
	}
	cout << endl << endl;
	cout << "queue in = " << q.countin << " queue out = " << q.countout << endl;
	cout << "task count = " << (cc1 + cc2) << " time_work = " << tw << " time_stop = " << ts << endl;
}
void task3() //��
{
	queue q1;
	queue q2;
	for (int i = 0; i < nn; i++)      //��������� ����� �������
	{
		list* ptr = create(i, 1);
		set_in(ptr, 0);
		push(q1, ptr);
	}
	double tw1 = 0, ts1 = 0, ti1 = 0;
	double m1 = 0, s1 = 0;
	int cc11 = 0, cc21 = 0, x1 = -1, tx1 = -1;
	double tw2 = 0, ts2 = 0, ti2 = 0;
	double m2 = 0, s2 = 0;
	int cc12 = 0, cc22 = 0, x2 = -1, tx2 = -1;
	int p = 7;
	list* tmp1 = oa(q1, tw1, ts1, ti1, cc11, cc21); //����� �� ���������
	if (tmp1)
	{
		statistic(tmp1, x1, tx1, m1, s1);
	}
	list* tmp2 = NULL;
	while (q1.head || q2.head || tmp1 || tmp2)
	{
		if (tmp1)
		{
			set_type(tmp1, rand() % 10);
			set_in(tmp1, tmp1->time_work);
			if (tmp1->type < p)
			{
				push(q1, tmp1);
				set_in(tmp1, tmp1->time_out + tmp1->time_work); // ����� ����� ��� ��������� ���������
				q2.tec_time = q1.tec_time;  // ����� ���� �����������
			}
			else
			{
				push(q2, tmp1);
				change_work(tmp1, W21, W22);
				q1.tec_time = q2.tec_time; // ����� ���� �����������
			}

			tmp1 = NULL;
		}
				//cout << endl << "lst1 = " << q1.tec_time;
				//print(q1);
				//cout << endl << "lst2 = " << q2.tec_time;
				//print(q2);
		tmp1 = oa(q1, tw1, ts1, ti1, cc11, cc21); //����� �� ���������
		if (tmp1)
		{
			statistic(tmp1, x1, tx1, m1, s1);
		}

		if (tmp2 == NULL) {
			tmp2 = oa(q2, tw2, ts2, ti2, cc12, cc22); //����� �� ���������
			if (tmp2)
			{
				statistic(tmp2, x2, tx2, m2, s2);
			}
		}
		if (q2.head && top(q2)->time_in < q2.tec_time || q1.head == NULL) {
				delete tmp2;		// ������� �� 2 ������� ���� ����� ������ ��� ����� ������ ��� �� �����
				tmp2 = NULL;

			}

		if ((cc11 + cc21 + cc12 + cc22) % (nn / 10) == 0)  // ����� ���������� ������ 100 �����
		{
			cout << endl << cc11 + cc21 << endl << " 1 task " << x1 << " (" << tx1 << ")  max = " << m1 << " aver = " << s1 / (cc11 + cc21) << endl;
			cout << "queue1 in = " << q1.countin << " queue1 length = " << q1.countin - q1.countout << endl;
			cout << endl << cc12 + cc22 << endl << " 2 task " << x2 << " (" << tx2 << ")  max = " << m2 << " aver = " << s2 / (cc12 + cc22) << endl;
			cout << "queue2 in = " << q2.countin << " queue2 length = " << q2.countin - q2.countout << endl;
		}
	}
	cout << endl << endl;
	cout << "queue 1 in = " << q1.countin << " queue 1 out = " << q1.countout << endl;
	cout << "task 1 count = " << (cc11 + cc21) << " 1 time_work = " << tw1 << " 1 time_stop = " << ts1 << endl;
	cout << "queue 2 in = " << q2.countin << " queue 2 out = " << q2.countout << endl;
	cout << "task 2 count = " << (cc12 + cc22) << " 2 time_work = " << tw2 << " 2 time_stop = " << ts2 << endl;
}
void task4() // ��
{
	queue q;
	int p = 8;
	int n = 0;
	list* ptr = create(n, 1);               //������� ������� ����
	n++;
	push(q, ptr);
	ptr = NULL;
	double tw = 0, ts = 0, ti = 0;
	double m = 0, s = 0;
	int cc1 = 0, cc2 = 0, x, tx;
	list* tmp = oa(q, tw, ts, ti, cc1, cc2); //����� �� ���������
	if (tmp)
	{
		statistic(tmp, x, tx, m, s);
	}
	while (tmp || n < nn)  //tmp ����� ����� ������ �� ��������� n �������
	{
		if (n < nn)
		{
			if (ptr == NULL)  //���� ��������� � �������, �� ���� ������� �����
			{
				ptr = create(n, 1);
				n++;
			}
			if (tmp == NULL)
			{
				push(q, ptr);    //������� ������
				ptr = NULL;
				tmp = oa(q, tw, ts, ti, cc1, cc2); //����. ������� ���� �� ���������
				if (tmp)
				{
					statistic(tmp, x, tx, m, s);
				}
			}
			else
			{
				if (q.tec_time + ptr->time_in < tw) //����� ����� ������ ������� ������ ������� ������ tw
				{
					push(q, ptr);    //������� ������
					ptr = NULL;
				}
				else
				{
					set_type(tmp, rand() % 10);
					if (tmp->type < p)  //�������  ���������� � �������
					{
						set_in(tmp, 0);
						push(q, tmp);
					}
					else
					{
						delete tmp;    //����� �������
						tmp = NULL;
					}
					tmp = oa(q, tw, ts, ti, cc1, cc2); //����. ������� ���� �� ���������
					if (tmp)
					{
						statistic(tmp, x, tx, m, s);
					}
				}
			}
		}
		else                                //�� ���� ��������� ����� �������
		{
			set_type(tmp, rand() % 10);
			if (tmp->type < p)  //�������  ���������� � �������
			{
				set_in(tmp, 0);
				push(q, tmp);
			}
			else   delete (tmp);
			tmp = oa(q, tw, ts, ti, cc1, cc2);
			if (tmp)
			{
				statistic(tmp, x, tx, m, s);
			}
		}
		if ((cc1 + cc2) % (nn / 10) == 0)  // ����� ���������� ������ 100 �����
		{
			cout << endl << "task " << x << " (" << tx << ")  max = " << m << " aver = " << s / (cc1 + cc2) << endl;
			cout << "queue in = " << q.countin << " queue length = " << q.countin - q.countout << endl;
		}
	}
	cout << endl << endl;
	cout << "queue in = " << q.countin << " queue out = " << q.countout << endl;
	cout << "task count = " << (cc1 + cc2) << " time_work = " << tw << " time_stop = " << ts << endl;
}
void task5() // ��
{
	queue q1;
	queue q2;
	int n1 = 0, n2 = 0;
	list* ptr1 = create(n1, 1);
	n1++;
	push(q1, ptr1);
	ptr1 = NULL;
	list* ptr2 = create((-1) * n2, 2);
	n2++;
	push(q2, ptr2);
	ptr2 = NULL;
	double tw = 0, ts = 0, ti = 0;
	double m1 = 0, s1 = 0;
	double m2 = 0, s2 = 0;
	int cc1 = 0, cc2 = 0, x1, tx1, x2, tx2;
	list* tmp1 = top(q1);
	list* tmp2 = top(q2);
	while (tmp1)
	{
		if (q1.tec_time < q2.tec_time || q1.tec_time < tw)
		{
			tmp1 = oa(q1, tw, ts, ti, cc1, cc2); //����� �� ��������� �� ������ �������
			if (tmp1)
			{
				statistic(tmp1, x1, tx1, m1, s1);
			}
			delete tmp1;
			tmp1 = NULL;
			if (n1 < nn)
			{
				if (ptr1 == NULL)  //���� ��������� � �������, �� ���� ������� �����
				{
					ptr1 = create(n1, 1);
					n1++;
					push(q1, ptr1);    //������� ������
					ptr1 = NULL;
				}
			}
		}
		else
		{
			tmp2 = oa(q2, tw, ts, ti, cc1, cc2); //����� �� ��������� �� ������ �������
			if (tmp2)
			{
				statistic(tmp2, x2, tx2, m2, s2);
			}
			delete tmp2;
			tmp2 = NULL;
			if (ptr2 == NULL)  //���� ��������� � �������, �� ���� ������� �����
			{
				ptr2 = create((-1) * n2, 2);
				n2++;
				push(q2, ptr2);    //������� ������
				ptr2 = NULL;
			}
		}
		if (!tmp1)tmp1 = top(q1);
		if (!tmp2)tmp2 = top(q2);
		if ((cc1 + cc2) % (nn / 10) == 0)  // ����� ���������� ������ 100 �����
		{
			cout << endl << "tasks 1 = " << cc1 << " tasks 2 = " << cc2 << endl << " max task 1 " << x1 << " (" << tx1 << ")  max = " << m1 << " aver = " << s1 / (cc1 + cc2) << endl;
			cout << "queue1 in = " << q1.countin << " queue1 length = " << q1.countin - q1.countout << endl;
			cout << endl << " max task 2 " << x2 << " (" << tx2 << ")  max = " << m2 << " aver = " << s2 / (cc1 + cc2) << endl;
			cout << "queue2 in = " << q2.countin << " queue2 length = " << q2.countin - q2.countout << endl;
		}
	}
	cout << endl << endl;
	cout << "queue 1 in = " << q1.countin << " queue 1 out = " << q1.countout << endl;
	cout << "queue 2 in = " << q2.countin << " queue 2 out = " << q2.countout << endl;
	cout << "task count = " << (cc1 + cc2) << " time_work = " << tw << " time_stop = " << ts << endl;
}
void task6() // ok
{
	queue q1;
	queue q2;
	int n = 0;
	double tw1 = 0, ts1 = 0, ti1 = 0;
	double m1 = 0, s1 = 0;
	int cc11 = 0, cc21 = 0, x1 = -1, tx1 = -1;
	double tw2 = 0, ts2 = 0, ti2 = 0;
	double m2 = 0, s2 = 0;
	int cc12 = 0, cc22 = 0, x2 = -1, tx2 = -1;
	int p = 4;
	list* ptr = create(n, 1);// ������ ������
	n++;
	set_type(ptr, rand() % 10);
	if (ptr->type >= p) // ���������� �������
	{
		q2.tec_time += ptr->time_in;  //����� �������� � ����� ��������
		push(q1, ptr);
	}
	else
	{
		change_work(ptr, W21, W22);
		q1.tec_time += ptr->time_in;
		push(q2, ptr);
	}
	ptr = NULL;
	//cout << endl << "lst1 = ";
	//print(q1);
	//cout << endl << "lst2 = ";
	//print(q2);
	list* tmp1 = oa(q1, tw1, ts1, ti1, cc11, cc21); //����� �� ���������
	if (tmp1)
	{
		statistic(tmp1, x1, tx1, m1, s1);
	}
	list* tmp2 = oa(q2, tw2, ts2, ti2, cc12, cc22); //����� �� ���������
	if (tmp2)
	{
		statistic(tmp2, x2, tx2, m2, s2);
	}
	while (tmp1 || q2.head || n < nn)
	{
		if (n < nn)
		{
			if (ptr == NULL)   //���� ��������� � �������, �� ���� ������� �����
			{
				ptr = create(n, 1);
				set_type(ptr, rand() % 10);
				n++;
				if (ptr->type < p)   //�������� ����� ���� ���������� ��1
					change_work(ptr, W21, W22);
			}
		}
		if (ptr) {
			if (tmp1)
			{
				if (tmp1->time_out + tmp1->time_work < q2.tec_time + ptr->time_in)   // ����� ������� ptr ������ ��� ����� ����������� �� ��1
				{
					change_from(tmp1, 0);
					push(q2, tmp1);
					set_in(tmp1, tmp1->time_out + tmp1->time_work);
					change_work(tmp1, W21, W22);
					tmp1 = oa(q1, tw1, ts1, ti1, cc11, cc21); //����� �� ��������� �� q1 ���� ���������� � q2
					if (tmp1)
					{
						statistic(tmp1, x1, tx1, m1, s1);
					}
				}
			}
			if (ptr->type >= p) // ������ � ������ �������
			{
				q2.tec_time += ptr->time_in;
				push(q1, ptr);
				ptr = NULL;
			}
			else // ���������� ������ �������
			{
				q1.tec_time += ptr->time_in;
				push(q2, ptr);
				ptr = NULL;
			}
		}
		else          //����� ������ ���, ������������ ����� q1
			if (tmp1)
			{
				change_from(tmp1, 0);
				push(q2, tmp1);
				set_in(tmp1, tmp1->time_out + tmp1->time_work);
				change_work(tmp1, W21, W22);
				tmp1 = oa(q1, tw1, ts1, ti1, cc11, cc21); //����� �� ��������� �� q1 ���� ���������� � q2
				if (tmp1)
				{
					statistic(tmp1, x1, tx1, m1, s1);
				}
			}
		//cout << endl << "lst1 = " << q1.tec_time;
		//print(q1);
		//cout << endl << "lst2 = " << q2.tec_time;
		//print(q2);
		if (tmp1 == NULL)
		{
			tmp1 = oa(q1, tw1, ts1, ti1, cc11, cc21); //����� �� ��������� �� q1 ���� ���������� � q2
			if (tmp1)
			{
				statistic(tmp1, x1, tx1, m1, s1);
			}
		}
		tmp2 = oa(q2, tw2, ts2, ti2, cc12, cc22); //����� �� ���������
		if (tmp2)
		{
			statistic(tmp2, x2, tx2, m2, s2);
		}
		delete tmp2;
		tmp2 = NULL;
		if ((cc12 + cc22) % (nn / 10) == 0)  // ����� ���������� ������ 100 �����
		{
			cout << endl << cc11 + cc21 << endl << " 1 task " << x1 << " (" << tx1 << ")  max = " << m1 << " aver = " << s1 / (cc11 + cc21) << endl;
			cout << "queue1 in = " << q1.countin << " queue1 length = " << q1.countin - q1.countout << endl;
			cout << endl << cc12 + cc22 << endl << " 2 task " << x2 << " (" << tx2 << ")  max = " << m2 << " aver = " << s2 / (cc12 + cc22) << endl;
			cout << "queue2 in = " << q2.countin << " queue2 length = " << q2.countin - q2.countout << endl;
		}
	}
	cout << endl << endl;
	cout << "queue 1 in = " << q1.countin << " queue 1 out = " << q1.countout << endl;
	cout << "task 1 count = " << (cc11 + cc21) << " 1 time_work = " << tw1 << " 1 time_stop = " << ts1 << endl;
	cout << "queue 2 in = " << q2.countin << " queue 2 out = " << q2.countout << endl;
	cout << "task 2 count = " << (cc12 + cc22) << " 2 time_work = " << tw2 << " 2 time_stop = " << ts2 << endl;
}
void task7() // ok
{
	queue q;
	int n1 = 0, n2 = 1;
	int a = rand() % 2;
	list* ptr = NULL;
	double tw = 0, ts = 0, ti = 0;
	double m1 = 0, s1 = 0;
	int cc1 = 0, cc2 = 0, x1, tx1;
	if (a % 2)
	{
		ptr = create(n1, 1);
		n1++;
	}
	else
	{
		ptr = create((-1) * n2, 2);
		n2++;
	}
	push(q, ptr);
	ptr = NULL;
	list* tmp1 = oa(q, tw, ts, ti, cc1, cc2); //����� �� ��������� �� ������ �������
	if (tmp1)
	{
		statistic(tmp1, x1, tx1, m1, s1);
	}
	while (tmp1 || n1 < nn || cc1 < nn)
	{
		//        cout<<endl<<endl<<"lst = ";
		//        print(q);
		if (n1 < nn)
		{
			if (ptr == NULL)
			{
				a = rand() % 2;
				if (a % 2)
				{
					ptr = create(n1, 1);
					n1++;
				}
				else
				{
					ptr = create((-1) * n2, 2);
					n2++;
				}
			}
			if (tmp1 && tmp1->type == 2)
			{
				if (tmp1->time_out + tmp1->time_work < q.tec_time + ptr->time_in)
				{
					change_from(tmp1, 0);
					push(q, tmp1);
					tmp1 = NULL;
				}
				else
				{
					push(q, ptr);
					ptr = NULL;
				}
			}
			else
			{
				if (tmp1)
				{
					delete tmp1;
					tmp1 = NULL;
				}
				else
				{
					push(q, ptr);
					ptr = NULL;
				}
			}
		}
		else
		{
			if (ptr)
			{
				push(q, ptr);
				ptr = NULL;
			}
			if (tmp1 && tmp1->type == 2)
			{
				change_from(tmp1, 0);
				push(q, tmp1);
				tmp1 = NULL;

			}
			else
			{
				delete tmp1;
				tmp1 = NULL;
			}
		}
		if (!tmp1)
		{
			tmp1 = oa(q, tw, ts, ti, cc1, cc2); //����� �� ��������� �� ������ �������
			if (tmp1)
			{
				statistic(tmp1, x1, tx1, m1, s1);
			}
		}
		if (cc1 >= nn) tmp1 = NULL;
		if ((cc1 + cc2) % (nn / 10) == 0)  // ����� ���������� ������ 100 �����
		{
			cout << endl << "create tasks 1 = " << n1 << " create tasks 2 = " << n2;
			cout << endl << "tasks 1 = " << cc1 << " tasks 2 = " << cc2 << endl << " max task " << x1 << " (" << tx1 << ")  max = " << m1 << " aver = " << s1 / (cc1 + cc2) << endl;
			cout << "queue1 in = " << q.countin << " queue1 length = " << q.countin - q.countout << endl;

		}
	}
	cout << endl << endl;
	cout << "queue1 time = " << q.tec_time << " queue  in = " << q.countin << " queue 1 out = " << q.countout << endl;
	cout << endl << "tasks 1 = " << cc1 << " tasks 2 = " << cc2 << endl;
	cout << "task count = " << (cc1 + cc2) << " time_work = " << tw << " time_stop = " << ts << endl;
}
void task8() //��
{
	queue q1;
	queue q2;
	queue q3;
	cout.precision(9);
	for (int i = 0; i < nn; i++)      //��������� ����� �������
	{
		list* ptr = create(i, 1);
		set_in(ptr, 0);
		push(q1, ptr);
	}
	double tw1 = 0, ts1 = 0, ti1 = 0;
	double m1 = 0, s1 = 0;
	int cc11 = 0, cc21 = 0, x1 = -1, tx1 = -1;
	double tw2 = 0, ts2 = 0, ti2 = 0;
	double m2 = 0, s2 = 0;
	int cc12 = 0, cc22 = 0, x2 = -1, tx2 = -1;
	double tw3 = 0, ts3 = 0, ti3 = 0;
	double m3 = 0, s3 = 0;
	int cc13 = 0, cc23 = 0, x3 = -1, tx3 = -1;

	int p = 7, a = rand() % 10;
	list* tmp1 = oa(q1, tw1, ts1, ti1, cc11, cc21); //����� �� ���������
	if (tmp1)
	{
		statistic(tmp1, x1, tx1, m1, s1);
		set_in(tmp1, tmp1->time_work);
	}
	list* tmp2 = NULL;
	list* tmp3 = NULL;
	while (tmp1 || tmp2 || tmp3)
	{
		if (tmp1)
		{
			set_in(tmp1, tmp1->time_out + tmp1->time_work);
			if (a < p)
			{
				change_work(tmp1, W21, W22);
				push(q2, tmp1);
			}
			else
			{
				change_work(tmp1, W31, W32);
				push(q3, tmp1);
			}
			tmp1 = NULL;
			a = rand() % 10;
		}
		//cout << endl << "lst1 = ";
		//print(q1);
		//cout << endl << "lst2 = ";
		//print(q2);
		//cout << endl << "lst3 = ";
		//print(q3);
		tmp1 = oa(q1, tw1, ts1, ti1, cc11, cc21); //����� �� ���������
		if (tmp1)
		{
			statistic(tmp1, x1, tx1, m1, s1);
			set_in(tmp1, tw1);
		}
		tmp2 = oa(q2, tw2, ts2, ti2, cc12, cc22); //����� �� ���������
		if (tmp2)
		{
			statistic(tmp2, x2, tx2, m2, s2);
		}
		tmp3 = oa(q3, tw3, ts3, ti3, cc13, cc23); //����� �� ���������
		if (tmp3)
		{
			statistic(tmp3, x3, tx3, m3, s3);
		}

		if ((cc12 + cc22 + cc13 + cc23) % (nn / 10) == 0)  // ����� ���������� ������ 100 �����
		{
			cout << endl << cc11 + cc21 << endl << " 1 task " << x1 << " (" << tx1 << ")  max = " << m1 << " aver = " << s1 / (cc11 + cc21) << endl;
			cout << "queue1 in = " << q1.countin << " queue1 length = " << q1.countin - q1.countout << endl;
			cout << endl << cc12 + cc22 << endl << " 2 task " << x2 << " (" << tx2 << ")  max = " << m2 << " aver = " << s2 / (cc12 + cc22) << endl;
			cout << "queue2 in = " << q2.countin << " queue2 length = " << q2.countin - q2.countout << endl;
			cout << endl << cc13 + cc23 << endl << " 3 task " << x3 << " (" << tx3 << ")  max = " << m3 << " aver = " << s3 / (cc13 + cc23) << endl;
			cout << "queue3 in = " << q3.countin << " queue3 length = " << q3.countin - q3.countout << endl;
		}
	}
	cout << endl << endl;
	cout << "queue1 time = " << q1.tec_time << " queue 1 in = " << q1.countin << " queue 1 out = " << q1.countout << endl;
	cout << "task 1 count = " << (cc11 + cc21) << " 1 time_work = " << tw1 << " 1 time_stop = " << ts1 << endl;
	cout << "queue2 time = " << q2.tec_time << " queue 2 in = " << q2.countin << " queue 2 out = " << q2.countout << endl;
	cout << "task 2 count = " << (cc12 + cc22) << " 2 time_work = " << tw2 << " 2 time_stop = " << ts2 << endl;
	cout << "queue3 time = " << q3.tec_time << " queue 3 in = " << q3.countin << " queue 3 out = " << q3.countout << endl;
	cout << "task 3 count = " << (cc13 + cc23) << " 3 time_work = " << tw3 << " 3 time_stop = " << ts3 << endl;
}

int main()
{
	srand(time(0));
	task6();
	//   cout<<endl<<"lst = ";
	//  print(q);
	return 0;
}
