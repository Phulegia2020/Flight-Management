#pragma once
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <string>
#include <cstring>
#include <fstream>
#include <math.h>

#define MAXLIST 300
#define MAXVE 200
#define MAX_INPUT 255
#define HUYCHUYEN 0
#define CONVE 1
#define HETVE 2
#define HOANTAT 3
#define NAM 0
#define NU 1
#define MAX_PAGE 35
#define MAX_PAGE_SMALL 15

using namespace std;
// 1800 <  NAM < 9999
const int MAX_NAM = 9999;
const int MIN_NAM = 1800;
const int MAX_DAY = 10;
const int MAX_DONG = 20;
const int KC_GIO = 5;
const int KC_GIOAM = 19;
// cau truc thoi gian
struct ThoiGian
{
	int gio;
	int phut;

	int ngay;
	int thang;
	int nam;
};
typedef struct ThoiGian THOI_GIAN;

// cau truc may bay
struct maybay {
	char soHieuMayBay[20];
	char loaiMayBay[45];
	int soDay;
	int soDong;
};
typedef struct maybay mayBay;

struct NodeMayBay {
	mayBay data;
};
typedef struct NodeMayBay nodeMB;
typedef struct NodeMayBay* NODEMAYBAY;

struct ListMayBay {
	int n = 0;
	NODEMAYBAY MB[MAXLIST];
};
typedef struct ListMayBay LIST_MB;


// cau truc ve
struct VeMayBay{
	char soVe[5];
	char CMND[12];
};
typedef struct VeMayBay VeMB;
struct nodeVeMayBay {
	VeMB data;
};
typedef struct nodeVeMayBay nodeVeMB;
typedef struct nodeVeMayBay* NODEVEMB;
struct ListVe {
	int n = 0;
	int soDay;
	int soDong;
	NODEVEMB Ve[MAXVE];
};
typedef struct ListVe LIST_VE;


// cau truc chuyen bay
struct ChuyenBay {
	char maChuyenBay[20];
	THOI_GIAN tgKhoiHanh;
	char sanBayDen[50];
	int trangThai;
	char soHieuMayBay[20];
	LIST_VE dsVe;
};
typedef struct ChuyenBay CHUYENBAY;

typedef struct NodeChuyenBay {
	CHUYENBAY data;
	struct NodeChuyenBay* next;
};
typedef struct NodeChuyenBay* PTRChuyenBay;


// cau truc hanh khach
struct HanhKhach {
	char CMND[12];
	char ho[50];
	char ten[50];
	int phai;
};
typedef struct HanhKhach HANHKHACH;

struct nodeHanhKhach {
	HANHKHACH data;
	struct nodeHanhKhach* Left;
	struct nodeHanhKhach* Right;
};
typedef struct nodeHanhKhach NodeHanhKhach;
typedef struct nodeHanhKhach* TREEHanhKhach;


struct NhapChuoi {
	int n = 0;
	char* data[MAX_INPUT];
};

struct thongKe
{
	int soLuot = 0;
	int index;
};

//============= CAC HAM XU LY ===============//
//========== cac ham xu ly ds may bay =========
int emptyMB(LIST_MB lstMB);
int fullMB(LIST_MB lstMB);
mayBay createMB(LIST_MB& lstMB);
int insert_MB(LIST_MB& lstMB, mayBay mb);
int delete_MB(LIST_MB& lstMB, int i, PTRChuyenBay lstCB);
void show_MB(LIST_MB lstMB);
int search_MB(LIST_MB lstMB, char ma[]);
mayBay getMB(LIST_MB lstMB, char ma[]);
int hieuChinh_MB(LIST_MB& lstMB, int i);
void show_1_MB(LIST_MB lstMB, int chon, bool type, int dem);
void show_MB(LIST_MB lstMB);


//======= ham xu ly ve =====
int emptyVe(LIST_VE lstVe);
int fullVe(LIST_VE lstVe, mayBay mb);
int getSLVe(mayBay mb);
void insertVe(LIST_VE& lstVe, int vitri, char cmnd[]);
int createDsVe(mayBay mb, LIST_VE& lstVe);
int demSoVe(LIST_VE lstVe);
int cancelVe(LIST_VE& lstVe, int vitri);
void themSLVe(LIST_VE& lstVe, maybay mb, LIST_VE lstVeCu);


//============ cac ham xu ly chuyen bay ===============//
void initCB(PTRChuyenBay& lstCB);
int empty_CB(PTRChuyenBay lstCB);
CHUYENBAY createCB(PTRChuyenBay lstCB, LIST_MB lstMB);
void insert_OrderNodeCB(PTRChuyenBay& lstCB, CHUYENBAY cb);
int insertNodeCB(PTRChuyenBay& lstCB, CHUYENBAY cb);
PTRChuyenBay searchBin_CB(PTRChuyenBay lstCB, char ma[]);
int hieuChinh_CB(PTRChuyenBay& lstCB, PTRChuyenBay p, LIST_MB lstMB);
int xoa_CB(PTRChuyenBay& lstCB, char ma[]);
int huy_CB(PTRChuyenBay& lstCB, PTRChuyenBay p);

void showCB(PTRChuyenBay lstCB);
void showCB_DatVe(PTRChuyenBay lstCB);
void show_1_CB_DatVe(CHUYENBAY* cb, int chon);
void showCB_ConVe(CHUYENBAY* p, int& i);
void show_1_CB(CHUYENBAY* cb, int chon);
void chuyenMang(PTRChuyenBay lstCB, CHUYENBAY* cb[], int& n, LIST_MB lstMB, int trangThai);


//============= cac ham xu ly hanh khach ===================//
void init_HK(TREEHanhKhach& lstHK);
int empty_HK(TREEHanhKhach lstHK);
int timTrung_HK(TREEHanhKhach lstHK, char soCMND[]);
TREEHanhKhach timKiem_HK(TREEHanhKhach lstHK, char cmnd[]);
void insertNode_HK(TREEHanhKhach& lstHK, HANHKHACH p);
HANHKHACH create_HK(TREEHanhKhach& lstHK, PTRChuyenBay& lstCB);
int hieuChinh_HK(TREEHanhKhach& lstHK, TREEHanhKhach t, PTRChuyenBay& lstCB);
void xuat_HK(TREEHanhKhach lstHK, int& stt); // theo thu tu NLR
void timNodeTheMang(TREEHanhKhach& lstHK, TREEHanhKhach& r);
void remove_HK(TREEHanhKhach& lstHK, char soCMND[]);
void showHK(TREEHanhKhach lstHK);
void quickSortTK(int* soLuot, NODEMAYBAY tempMB, int q, int r);
void quickSortTK1(thongKe *thucHien, int q, int r);

//======= cac ham kiem tra ============//
int checkMB_DaBay(mayBay mb, PTRChuyenBay lstCB);
int checkTime_LapCB(CHUYENBAY cb, PTRChuyenBay lstCB);
int toTime(THOI_GIAN tg);
int checkKC_5Gio(THOI_GIAN tg1, THOI_GIAN tg2);
int checkStatus_CB(CHUYENBAY cb);
int checkBooked(LIST_VE lstVe);
int checkTime_HoanTat(THOI_GIAN tg1, THOI_GIAN tg2);
int checkHoanTat_CB(PTRChuyenBay& lstCB);
int checkTimeHienTai(THOI_GIAN tg);
int checkSoDay_SoDong(mayBay mbCu, mayBay mbMoi);
int checkHK_HuyVe(PTRChuyenBay p, HANHKHACH& hk);
int checkVeCung_CB(PTRChuyenBay p, HANHKHACH hk);
PTRChuyenBay checkVeCungTime(PTRChuyenBay lstCB, PTRChuyenBay p, HANHKHACH hk);


//============= doc xuat file ================//
int loadMB(LIST_MB &mb);
int saveMB(LIST_MB mb);
int loadCB(PTRChuyenBay& lstCB, LIST_MB mb);
int saveCB(PTRChuyenBay lstCB);
int loadHK(TREEHanhKhach& lstHK);
void duyetCay(TREEHanhKhach lstHK, fstream& file);
int saveHK(TREEHanhKhach lstHK);

//========= cac ham xu ly nhap chuoi ==========//
void NhapMA(char var[], int len);
void NhapCHUOI(char var[], int len);
void NhapCHUOI_SO(char var[], int len);
void Nhap_SO(int &var, int len);
void NhapNGAY(int&var, int len);
void NhapTHANG(int& var, int len);
void NhapNAM(int& var, int len);
void NhapGIO(int& var, int len);
void NhapPHUT(int& var, int len);
char* CheckInputStr(bool nhapMa, int DongInfo);
char* CheckInputCMND(int DongInfo);
int CheckInputNum(int DongInfo);
THOI_GIAN CheckInputDate(THOI_GIAN& tg, int DongInfo);
THOI_GIAN CheckInputTime(THOI_GIAN& tg, int DongInfo);
int rangBuocThoiGian(THOI_GIAN tg, int loai);
int rangBuocGio(THOI_GIAN h);
void catChuoi(string chuoi, char splitChar, int &vtri, char cmnd[]);
char* stringToChar(string chuoi);

//============= Xu ly Giao dien ==============//
const int soItem_MenuChinh = 7;
const int soItem_MenuMB = 4;
const int soItem_MenuCB = 5;
const int soItem_MenuDV = 3;

//=== ve khung giao dien ======
char* gdTimMa(int type, string title);
void khungGiaoDien();
void veKhungNhap(int dai, int rong, int posx, int posy, string source = "");
void khungNhapThongTin(int type, string title = "", string s1 = "", string s2 = "", string s3 = "", string s4 = "",
	string s5 = "", string s6 = "", string s7 = "", string s8 = "", string s9 = "");

void khungXuatDS(int type, int rong, int dai, int colump1 = 0, int colump2 = 0, int colump3 = 0, int colump4 = 0, 
	int colump5 = 0, int posx = 0, int posy = 0);
void xoaKhungDS();
void xoaThongTin(int type);

void khungThongBao();
void hienThongBao(string notif, string notif2 = "", string notif3 = "", string NoiDen = "");
void hienHuongDan(int type);

//=== to mau ====
void Normal();
void Highlight();
void Red_Highlight();
void Green_Highlight();

//======= giao dien menu chon ================
int menuDong_Prim(char td[soItem_MenuChinh][100]);

mayBay ChonMB_LapCB(LIST_MB lstMB);
mayBay ChonMB_Edit(LIST_MB lstMB, int& chonMB);
PTRChuyenBay ChonCB_Edit(PTRChuyenBay lstCB, LIST_MB lstMB, int& chonCB);
PTRChuyenBay ChonCB_DatVe_HuyVe(PTRChuyenBay lstCB, int& chonCB, LIST_MB lstMB);
void show_1_Ve(LIST_VE lstVe, int cot, int dong, int chon, int kc);
int chonVe(PTRChuyenBay& lstCB);
int chonVe_HUY(PTRChuyenBay& lstCB, HANHKHACH hk);
void show_VeTrong(PTRChuyenBay p);
void xuatHK_1_CB(CHUYENBAY* cb, TREEHanhKhach lstHK, int page);
void xuatALL_HK_1_CB(CHUYENBAY* cb, TREEHanhKhach lstHK);
PTRChuyenBay ChonCB_Xuat_DSHK(PTRChuyenBay lstCB, int& chonCB, LIST_MB lstMB, TREEHanhKhach lstHK);
PTRChuyenBay ChonCB_Loc_NoiDen(PTRChuyenBay lstCB, int& chonCB, LIST_MB lstMB);
PTRChuyenBay ChonCB_XemVeTrong(PTRChuyenBay lstCB, LIST_MB lstMB, int& chonCB);

//====== ham xu ly cac chuc nang cua danh sach ===========
void QLMB(LIST_MB& lstMB, PTRChuyenBay lstCB);
void QLCB(PTRChuyenBay& lstCB, LIST_MB& lstMB);
void DatHuyVe(PTRChuyenBay& lstCB, LIST_MB lstMB, TREEHanhKhach& lstHK);
void dsHK_1_CB(PTRChuyenBay lstCB, TREEHanhKhach lstHK, LIST_MB lstMB);
void locCB_CoNoiDen(PTRChuyenBay lstCB, LIST_MB lstMB);
void dsVeTrong_1_CB(PTRChuyenBay lstCB, LIST_MB lstMB);
void thongKeCB(PTRChuyenBay lstCB, LIST_MB lstMB);

int confirm(string chose1, string chose2, bool huyCB);
