#include<iostream>
#include<stdlib.h>
#include<queue>
#include<stdio.h>
#include<algorithm>
#include<iomanip>

using namespace std;

typedef struct ProcessInfo
{
    int id,
        td_XuatHien,
        tg_ThucHien,
        td_KetThuc;
    double tg_Cho, tong_tgThucHien;
} ProcessInfo;


ProcessInfo *arrProcess, *arrTienTrinh;
queue<int> queueTienTrinh;

int NhapProcess();
void InProcess(int numberOfProcess);
void sodo_Gantt(int numberOfProcess);
void Tg_DoiTB(int numberOfProcess);
int main()
{
    int numberOfProcess;
    numberOfProcess = NhapProcess();
    if (numberOfProcess > 0){
        InProcess(numberOfProcess);
        sodo_Gantt(numberOfProcess);
        Tg_DoiTB(numberOfProcess);
    }
    return 0;
}


int NhapProcess()
{
    int numberOfProcess;
    cout <<"\n\t So chuong trinh can lap lich = ";
    cin >> numberOfProcess;
    if(numberOfProcess <= 0)
    {
        cout << "\n So tien trinh <= 0. Ket thuc chuong trinh";
    }
    else
    {
        arrProcess = new ProcessInfo[numberOfProcess];
        arrTienTrinh = new ProcessInfo[numberOfProcess];
        cout << "\nThoi diem xuat hien cac tien trinh";
        for(int i = 0; i<numberOfProcess; i++)
        {
            cout <<"\n\tNhap thoi diem xuat hien P"<< i+1<< " = ";
            cin>>arrProcess[i].td_XuatHien;
            arrProcess[i].id = i;
        }
        cout << "\nThoi gian thuc hien cac tien trinh";
        for(int i = 0; i<numberOfProcess; i++)
        {
            cout <<"\n\tNhap thoi gian thuc hien P"<< i+1<< " = ";
            cin>>arrProcess[i].tg_ThucHien;
        }

        //
        for(int i = 0; i<numberOfProcess; i++)
            arrTienTrinh[i] = arrProcess[i];
    }
    return numberOfProcess;
}

void InProcess(int numberOfProcess)
{
    cout<<"\n\n=================Process=======================" << endl;
    cout << setw(5) << "ID Process" << setw(15) << "tg_Xuat Hien" << setw(20) << "tg_Thuc Hien" << endl;
    for(int i = 0; i<numberOfProcess; i++)
    {
        cout << setw(5)  << arrProcess[i].id+1;
        cout << setw(15) << arrProcess[i].td_XuatHien;
        cout << setw(25) << arrProcess[i].tg_ThucHien << endl;
    }
}

void sodo_Gantt(int numberOfProcess)
{
    int i,m,nextTime, nextProc;
    int qTime;

    nextTime = arrProcess[0].td_XuatHien;

    cout << "\n\n Nhap gia tri q = ";
    cin >> qTime;

    nextTime = arrTienTrinh[0].td_XuatHien;
    cout << "\n\n\t\t\t\t\t\t======= So Do Gantt ========\n";
    cout << arrTienTrinh[0].td_XuatHien;

    for(i=0; i < numberOfProcess, arrTienTrinh[i].td_XuatHien <= nextTime; i++)
        queueTienTrinh.push(arrTienTrinh[i].id);
    nextProc = arrTienTrinh[i].td_XuatHien;

    while(!queueTienTrinh.empty())
    {
        m = queueTienTrinh.front();
        queueTienTrinh.pop();

        if(arrTienTrinh[m].tg_ThucHien >= qTime) nextTime = nextTime + qTime;
        else nextTime = nextTime + arrTienTrinh[m].tg_ThucHien;

        cout << " -> P"<<arrTienTrinh[m].id + 1 <<" -> "<< nextTime;

        arrTienTrinh[m].tg_ThucHien = arrTienTrinh[m].tg_ThucHien - qTime;

        if(nextTime < nextProc)
        {
            if(arrTienTrinh[m].tg_ThucHien>0)
                queueTienTrinh.push(m);
            if(arrTienTrinh[m].tg_ThucHien<=0)
                arrProcess[m].td_KetThuc = nextTime;
        }
        else
        {
            while(i<=numberOfProcess-1&&arrTienTrinh[i].td_XuatHien<nextTime)
            {
                queueTienTrinh.push(arrTienTrinh[i].id);
                i++;
            }
            if(i<= numberOfProcess-1)
                nextProc = arrTienTrinh[i].td_XuatHien;
            if(arrTienTrinh[m].tg_ThucHien>0)
                queueTienTrinh.push(m);
            if(arrTienTrinh[m].tg_ThucHien<=0)
                arrProcess[m].td_KetThuc = nextTime;
        }
    }
}
void Tg_DoiTB(int numberOfProcess)
{
    int i;
    double ta = 0, wt = 0;
    cout << "\n=============================================";
    for(i=0; i<numberOfProcess; i++)
    {
        arrProcess[i].tong_tgThucHien= arrProcess[i].td_KetThuc-arrProcess[i].td_XuatHien;
        arrProcess[i].tg_Cho = arrProcess[i].tong_tgThucHien-arrProcess[i].tg_ThucHien;

        cout  << "\n Thoi gian doi p"  << i+1 << " \t" << arrProcess[i].tg_Cho;
        ta= ta+arrProcess[i].tong_tgThucHien;
        wt= wt+arrProcess[i].tg_Cho;

    }
    cout << "\n=============================================";
    ta = ta/numberOfProcess;
    wt = wt/numberOfProcess;

    cout << "\n\n\t\t Thoi gian doi trung binh = \t" << wt;
}//