#pragma once
#include "ThuVien.h"
#include "mylib.h"

//using namespace std;

//============ ham xu ly danh sach may bay ===============//
int emptyMB(LIST_MB lstMB) {
	return lstMB.n == 0;
}

int fullMB(LIST_MB lstMB) {
	return lstMB.n == MAXLIST;
}

maybay createMB(LIST_MB& lstMB) {
	khungNhapThongTin(THEM_MB, "THEM MAY BAY", "So hieu may bay:", "Loai may bay:", "So day:", "So dong:");
	mayBay mb;
	do {
		strcpy(mb.soHieuMayBay, CheckInputStr(true, DONGNHAP1));
		// kiem tra so hieu may bay da co chua
		int tontai = search_MB(lstMB, mb.soHieuMayBay);
		if (tontai != -1) {
			Red_Highlight();
			hienThongBao("So hieu may bay da ton tai, nhap lai!");
		}
		else {
			if (mb.soHieuMayBay[0] == ESC) {
				return mb;
			}
			else break;
		}
	} while (true);

	do {
		strcpy(mb.loaiMayBay, CheckInputStr(false, DONGNHAP2));
		
		if (mb.loaiMayBay[0] == ESC) {
			mb.soHieuMayBay[0] = ESC;
			return mb;
		}		
		else break;
	} while (true);

	do
	{
		mb.soDay = CheckInputNum(DONGNHAP3);
		if (mb.soDay == -1) {
			mb.soHieuMayBay[0] = ESC;
			return mb;
		}
		else if (mb.soDay > MAX_DAY || mb.soDay < 0) {
			Red_Highlight();
			hienThongBao("So day phai < 11 va > 0");
		}
		else break;
	} while (true);

	do
	{
		mb.soDong = CheckInputNum(DONGNHAP4);
		if (mb.soDong == -1) {
			mb.soHieuMayBay[0] = ESC;
			return mb;
		}
		else if (mb.soDong > MAX_DONG || mb.soDong < 0) {
			Red_Highlight();
			hienThongBao("So dong phai < 21 va > 0");
		}
		else break;
	} while (true);

	return mb;
}

int insert_MB(LIST_MB& lstMB, mayBay mb) {
	NODEMAYBAY p = new nodeMB;
	p->data = mb;
	if (fullMB(lstMB)){
		return 0;
	}
	lstMB.MB[lstMB.n++] = p;
	return 1;
}

int search_MB(LIST_MB lstMB, char ma[]) {
	for (int i = 0; i < lstMB.n; i++) {
		if (stricmp(lstMB.MB[i]->data.soHieuMayBay, ma) == 0) {
			return i;
		}
	}
	return -1;
}

mayBay getMB(LIST_MB lstMB, char ma[]) {
	for (int i = 0; i < lstMB.n; i++) {
		if (stricmp(lstMB.MB[i]->data.soHieuMayBay, ma) == 0) {
			return lstMB.MB[i]->data;
		}
	}
	maybay m;
	m.soHieuMayBay[0] = '\0';
	return m;
}

int delete_MB(LIST_MB& lstMB, int i, PTRChuyenBay lstCB){
	int j;
	if (emptyMB(lstMB)) {
		return 0;
	}
	if (i == -1)
		return 0;
	if (checkMB_DaBay(lstMB.MB[i]->data, lstCB) == 1) {
		return 0;
	}
	for (j = i + 1; j < lstMB.n; j++){
		lstMB.MB[j - 1] = lstMB.MB[j];
	}
	lstMB.n--;
	return 1;
}

char* gdTimMa(int type, string title) {
	khungNhapThongTin(type, title);

	char temp[20] = { '\0' };
	gotoxy(COT + 1, DONGNHAP1 + 2);
	cout << "                          ";
	gotoxy(COT + 1, DONGNHAP1 + 2);
	rewind(stdin);
	NhapMA(temp, 20);
	return temp;
}

int hieuChinh_MB(LIST_MB& lstMB, int i) {
	khungNhapThongTin(HIEUCHINH_MB, "HIEU CHINH MAY BAY", "So hieu may bay:", "Sua loai may bay:", "Sua so day:", "Sua so dong:");
	mayBay mb;
	if (i == -1)
		return 0;

	gotoxy(COT + 1, DONGNHAP1 + 2);
	rewind(stdin);
	cout << lstMB.MB[i]->data.soHieuMayBay;
	strcpy(mb.soHieuMayBay, lstMB.MB[i]->data.soHieuMayBay);
	gotoxy(COT + 1, DONGNHAP2 + 2);
	cout << lstMB.MB[i]->data.loaiMayBay;
	strcpy(mb.loaiMayBay, lstMB.MB[i]->data.loaiMayBay);

	do
	{
		mb.soDay = CheckInputNum(DONGNHAP3);
		if (mb.soDay == -1) {
			return CANCEL;
		}
		else if (mb.soDay > MAX_DAY || mb.soDay < 0) {
			Red_Highlight();
			hienThongBao("So day phai < 9 va > 0");
		}
		else break;

	} while (true);

	do
	{
		mb.soDong = CheckInputNum(DONGNHAP4);
		if (mb.soDong == -1) {
			mb.soHieuMayBay[0] = ESC;
			return CANCEL;
		}
		else if (mb.soDong > MAX_DONG || mb.soDay < 0) {
			Red_Highlight();
			hienThongBao("So dong phai < 20 va > 0");
		}
		else break;
	} while (true);

	lstMB.MB[i]->data = mb;
	return 1;
}

void show_1_MB(LIST_MB lstMB, int chon, bool type, int dem) {
	gotoxy(COTDS_L + 1, DONGDS_U + 3 + dem);
	cout << "                                                                                                                 ";
	gotoxy(COTDS_L + 1, DONGDS_U + 3 + dem);
	cout << chon + 1;

	gotoxy(COTDS_L + 6, DONGDS_U + 3 + dem);
	cout << lstMB.MB[chon]->data.soHieuMayBay;
	gotoxy(COTDS_L + 5, DONGDS_U + 3 + dem);
	cout << char(DOC);

	gotoxy(COTDS_L + 26, DONGDS_U + 3 + dem);
	cout << lstMB.MB[chon]->data.loaiMayBay;
	gotoxy(COTDS_L + 25, DONGDS_U + 3 + dem);
	cout << char(DOC);

	gotoxy(COTDS_L + 71, DONGDS_U + 3 + dem);
	cout << lstMB.MB[chon]->data.soDay;
	gotoxy(COTDS_L + 70, DONGDS_U + 3 + dem);
	cout << char(DOC);

	gotoxy(COTDS_L + 94, DONGDS_U + 3 + dem);
	cout << lstMB.MB[chon]->data.soDong;
	gotoxy(COTDS_L + 93, DONGDS_U + 3 + dem);
	cout << char(DOC);

	Normal();
	if (type == true) {
		gotoxy(COT + 1, DONGNHAP1 + 2);
		cout << "                      ";
		gotoxy(COT + 1, DONGNHAP1 + 2);
		cout << lstMB.MB[chon]->data.soHieuMayBay;
		gotoxy(COT + 1, DONGNHAP2 + 2);
		cout << "                      ";
		gotoxy(COT + 1, DONGNHAP2 + 2);
		cout << lstMB.MB[chon]->data.loaiMayBay;
		gotoxy(COT + 1, DONGNHAP3 + 2);
		cout << "                      ";
		gotoxy(COT + 1, DONGNHAP3 + 2);
		cout << "                      ";
		gotoxy(COT + 1, DONGNHAP3 + 2);
		cout << lstMB.MB[chon]->data.soDay;
		gotoxy(COT + 1, DONGNHAP4 + 2);
		cout << "                      ";
		gotoxy(COT + 1, DONGNHAP4 + 2);
		cout << lstMB.MB[chon]->data.soDong;
	}
	
}

void show_MB(LIST_MB lstMB) {
	khungXuatDS(XUAT_MB, DONGDS_D - DONGDS_U, COTDS_R - COTDS_L, 5, 25, 70, 93);

	for (int i = 0; i < MAX_PAGE; i++) {
		//5, 25, 70, 93
		gotoxy(COTDS_L + 1, DONGDS_U + 3 + i);
		cout << i + 1;
		gotoxy(COTDS_L + 6, DONGDS_U + 3 + i);
		cout << lstMB.MB[i]->data.soHieuMayBay;
		gotoxy(COTDS_L + 26, DONGDS_U + 3 + i);
		cout << lstMB.MB[i]->data.loaiMayBay;
		gotoxy(COTDS_L + 71, DONGDS_U + 3 + i);
		cout << lstMB.MB[i]->data.soDay;
		gotoxy(COTDS_L + 94, DONGDS_U + 3 + i);
		cout << lstMB.MB[i]->data.soDong;
	}
	
}

int checkMB_DaBay(mayBay mb, PTRChuyenBay lstCB) {
	for (PTRChuyenBay p = lstCB; p != NULL; p = p->next) {
		if (stricmp(mb.soHieuMayBay, p->data.soHieuMayBay) == 0) {
			return 1;
		}
	}
}

int checkTime_LapCB(CHUYENBAY cb, PTRChuyenBay lstCB) {
	for (PTRChuyenBay p = lstCB; p != NULL; p = p->next) {
		if (stricmp(p->data.soHieuMayBay, cb.soHieuMayBay) == 0) {
			if (!checkKC_5Gio(cb.tgKhoiHanh, p->data.tgKhoiHanh)) {
				return 1;
			}
		}
	}
	return 0;
}

int toTime(THOI_GIAN tg) {
	int sumyear = 0;
	int summonth = 0;
	for (int i = 1999; i < tg.nam; i++)
	{
		if ((i % 4 == 0 && i % 100 != 0) || i % 400 == 0)
		{
			sumyear = sumyear + 366;
		}
		else
		{
			sumyear = sumyear + 365;
		}
	}
	for (int j = 1; j < tg.thang; j++)
	{
		if (j == 2)
		{
			if ((tg.nam % 4 == 0 && tg.nam % 100 != 0) || tg.nam % 400 == 0)
			{
				summonth = summonth + 29;
			}
			else
			{
				summonth = summonth + 28;
			}
		}
		if (j == 1 || j == 3 || j == 5 || j == 7 || j == 8 || j == 10 || j == 12)
		{
			summonth = summonth + 31;
		}
		if (j == 4 || j == 6 || j == 9 || j == 11)
		{
			summonth = summonth + 30;
		}
	}
	return sumyear + summonth + tg.ngay;
}

int checkKC_5Gio(THOI_GIAN tg1, THOI_GIAN tg2) {
	// truong hop trong cung 1 ngay
	if (toTime(tg1) - toTime(tg2) == 0) {
		if (abs(tg1.gio - tg2.gio) >= KC_GIO) {
			if (abs(tg1.gio - tg2.gio) == KC_GIO) {
				if (tg1.phut - tg2.phut >= 0)
					return 1;
				else
					return 0;
			}
			return 1;
		}
		return 0;
	}

	// truong hop cach nhau 1 ngay (0h==24h)
	if (abs(toTime(tg1) - toTime(tg2)) == 1) {
		
		// truong hop chuyen bay cach nhau giua moc 0h
		if (0 + tg1.gio <= KC_GIO && 24 - tg2.gio <= KC_GIO) {
			if (abs(tg1.gio - tg2.gio) <= KC_GIOAM) {
				if (abs(tg1.gio - tg2.gio) == KC_GIOAM) {
					if (tg1.phut - tg2.phut >= 0)
						return 1;
					else
						return 0;
				}
				return 1;
			}
			return 0;
		}
		if (24 - tg1.gio <= KC_GIO && 0 + tg2.gio <= KC_GIO) {
			if (abs(tg1.gio - tg2.gio) >= KC_GIO) {
				if (abs(tg1.gio - tg2.gio) == KC_GIO) {
					if (tg1.phut - tg2.phut >= 0)
						return 1;
					else
						return 0;
				}
				return 1;
			}
			return 0;
		}
		return 1;
	}
	// truong hop cach nhau nhieu ngay
	if (abs(toTime(tg1) - toTime(tg2)) > 1) {
		
		return 1;
	}
	
	return 0;
}

int checkTime_HoanTat(THOI_GIAN tg1, THOI_GIAN tg2) {
	if (toTime(tg1) - toTime(tg2) == 0) {
		
		if (abs(tg1.gio - tg2.gio) >= KC_GIO) {
			if (abs(tg1.gio - tg2.gio) == KC_GIO) {
				if (tg1.phut - tg2.phut >= 0)
					return 1;
				else
					return 0;
			}
			return 1;
		}
		return 0;
	}

	// truong hop cach nhau 1 ngay (0h==24h)
	if (toTime(tg1) - toTime(tg2) == -1) {
		
		// truong hop chuyen bay cach nhau giua moc 0h
		if (0 + tg1.gio <= KC_GIO && 24 - tg2.gio <= KC_GIO) {
			if (abs(tg1.gio - tg2.gio) <= KC_GIOAM) {
				if (abs(tg1.gio - tg2.gio) == KC_GIOAM) {
					if (tg1.phut - tg2.phut >= 0)
						return 1;
					else
						return 0;
				}
				return 1;
			}
			return 0;
		}
		if (24 - tg1.gio <= KC_GIO && 0 + tg2.gio <= KC_GIO) {
			if (abs(tg1.gio - tg2.gio) <= KC_GIOAM) {
				if (abs(tg1.gio - tg2.gio) == KC_GIOAM) {
					if (tg1.phut - tg2.phut >= 0)
						return 1;
					else
						return 0;
				}
				return 1;
			}
			return 0;
		}
		return 1;
	}
	if (toTime(tg1) - toTime(tg2) < -1) {
		//hienThongBao("Xet dieu kien 3");
		return 1;
	}
}

//============= ham xu ly danh sach ve ================//
int emptyVe(LIST_VE lstVe) {
	return lstVe.n == 0;
}

int fullVe(LIST_VE lstVe, mayBay mb) {
	int tmpSoDay = mb.soDay;
	int tmpSoDong = mb.soDong;
	int soVe = tmpSoDay * tmpSoDong;
	return lstVe.n == soVe;
}

int getSLVe(mayBay mb) {
	int tmpSoDay = mb.soDay;
	int tmpSoDong = mb.soDong;
	return tmpSoDay * tmpSoDong;
}

void insertVe(LIST_VE& lstVe, int vitri, char cmnd[]) {
	strcpy(lstVe.Ve[vitri]->data.CMND, cmnd);
}

int createDsVe(mayBay mb, LIST_VE &lstVe) {
	if (fullVe(lstVe, mb)) {
		return 0;
	}
	char day[] = "ABCDEFGHIJKLMNO";
	char temp[5] = "";
	char tmpCMND[12] = "";
	
	lstVe.soDay = mb.soDay;
	lstVe.soDong = mb.soDong;

	for (int i = 0; i < mb.soDay; i++) {
		temp[0] = '\0';
		temp[0] = day[i];
		for (int j = 1; j <= mb.soDong; j++) {
			if (j < 10) {
				
				char array[3];
				temp[1] = '\0';
				strcat(temp, "0");
				itoa(j, array, 10);
				strcat(temp, array);
			}
			else {

				char array[3];
				temp[1] = '\0';
				itoa(j, array, 10);
				strcat(temp, array);
			}
			lstVe.Ve[lstVe.n] = new nodeVeMayBay;
			strcpy(lstVe.Ve[lstVe.n]->data.soVe, temp);
			insertVe(lstVe, lstVe.n, tmpCMND);
			lstVe.n++;
		}
	}
	return 1;
}

int demSoVe(LIST_VE lstVe) {
	int dem = 0;
	for (int i = 0; i < lstVe.n; i++) {
		if (stricmp(lstVe.Ve[i]->data.CMND, "") != 0)
			dem++;
	}
	return dem;
}

int cancelVe(LIST_VE& lstVe, int vitri) {
	if (emptyVe(lstVe))
		return 0;
	strcpy(lstVe.Ve[vitri]->data.CMND, "");
	return 1;
}

void themSLVe(LIST_VE& lstVe, maybay mb, LIST_VE lstVeCu) {

	char day[] = "ABCDEFGHIJKLMNO";
	char temp[5] = ""; // de luu so ve vd A01, A02,..
	char tmpCMND[12] = ""; // khoi tao cmnd rong khi tao ds ve

	int slVeCu = lstVeCu.soDay * lstVeCu.soDong;
	int dem = 0;
	bool daThem = false;
	char soVeCu[MAXLIST][4];
	char cmndCu[MAXLIST][12];
	for (int i = 0; i < lstVeCu.n; i++) {
		if (stricmp(lstVeCu.Ve[i]->data.CMND, "") != 0) {
			strcpy(soVeCu[dem], lstVeCu.Ve[i]->data.soVe);
			strcpy(cmndCu[dem], lstVeCu.Ve[i]->data.CMND);
			
			dem++;
		}
	}
	lstVe.n = 0;
	lstVe.soDay = mb.soDay;
	lstVe.soDong = mb.soDong;
	for (int i = 0; i < mb.soDay; i++) {
		temp[0] = '\0';
		temp[0] = day[i];
		for (int j = 1; j <= mb.soDong; j++) {
			if (j < 10) {

				char array[3];
				temp[1] = '\0';
				strcat(temp, "0");
				itoa(j, array, 10);
				strcat(temp, array);
			}
			else {

				char array[3];
				temp[1] = '\0';
				itoa(j, array, 10);
				strcat(temp, array);
			}
			lstVe.Ve[lstVe.n] = new nodeVeMayBay;
			strcpy(lstVe.Ve[lstVe.n]->data.soVe, temp);
			daThem = false;
			for (int k = 0; k < dem; k++) {
				if (stricmp(lstVe.Ve[lstVe.n]->data.soVe, soVeCu[k]) == 0) {
					insertVe(lstVe, lstVe.n, cmndCu[k]);
					daThem = true;
					break;
				}
			}
			if(!daThem)
				insertVe(lstVe, lstVe.n, tmpCMND);
			lstVe.n++;
		}
	}
	
}


// ============== ham xu ly danh sach chuyen bay ============//
void initCB(PTRChuyenBay& lstCB) {
	lstCB = NULL;
}

int empty_CB(PTRChuyenBay lstCB) {
	return (lstCB == NULL);
}

PTRChuyenBay searchBin_CB(PTRChuyenBay lstCB, char ma[]) {
	PTRChuyenBay p;
	for (p = lstCB; p != NULL; p = p->next) {
		if (stricmp(p->data.maChuyenBay, ma) == 0)
			return p;
	}
	return NULL;

}

CHUYENBAY createCB(PTRChuyenBay lstCB, LIST_MB lstMB) {
	khungNhapThongTin(GDTHEM_CB, "THEM CHUYEN BAY", "Ma chuyen bay:", "So hieu may bay:", "San bay den:", "Ngay khoi hanh:", "Gio khoi hanh:");
	CHUYENBAY cb;
	PTRChuyenBay p;

	do
	{
		strcpy(cb.maChuyenBay, CheckInputStr(true, DONGNHAP1));
		p = searchBin_CB(lstCB, cb.maChuyenBay);
		if (p != NULL) {
			Red_Highlight();
			hienThongBao("Ma chuyen bay da ton tai!");
		}
		else {
			if (cb.maChuyenBay[0] == ESC) {
				return cb;
			}
			else break;
		}
	} while (true);

	ChonMayBay:
		mayBay chonMB;
		do
		{
			// chon may bay tren giao dien
			chonMB = ChonMB_LapCB(lstMB);
			strcpy(cb.soHieuMayBay, chonMB.soHieuMayBay);
			// tim may bay bang cach nhap
			if (chonMB.soHieuMayBay[0] == '\0') {
				strcpy(cb.soHieuMayBay, CheckInputStr(true, DONGNHAP2));
				if (cb.soHieuMayBay[0] == ESC) {
					cb.maChuyenBay[0] = ESC;
					return cb;
				}
				int tontai = search_MB(lstMB, cb.soHieuMayBay);
				if (tontai == -1) {
					Red_Highlight();
					hienThongBao("Khong co may bay nao mang so hieu nay!");
					continue;
				}
				else 
					break;
			
			}
			else {
				gotoxy(COT + 1, DONGNHAP2 + 2);
				cout << cb.soHieuMayBay;
				break;
			}
		
		} while (true);
	
	do
	{
		strcpy(cb.sanBayDen, CheckInputStr(false, DONGNHAP3));
		if (cb.sanBayDen[0] == ESC) {
			cb.maChuyenBay[0] = ESC;
			return cb;
		}
		else
			break;
	} while (true);
	
	do
	{
		
		cb.tgKhoiHanh = CheckInputDate(cb.tgKhoiHanh, DONGNHAP4);
	
		if (cb.tgKhoiHanh.ngay == -1 || cb.tgKhoiHanh.thang == -1 || cb.tgKhoiHanh.nam == -1) {
			cb.maChuyenBay[0] = ESC;
			return cb;
		}
		if (rangBuocThoiGian(cb.tgKhoiHanh, THEM_CB) == -1)
		{
			break;
		}
		else
		{
			gotoxy(COT + 1, DONGNHAP4 + 2);
			cout << "  ";
			gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP4 + 2);
			cout << "  ";
			gotoxy(COT + DAIKHUNGNHO * 2 + 1, DONGNHAP4 + 2);
			cout << "    ";
		}
	} while (true);

	do
	{
		cb.tgKhoiHanh = CheckInputTime(cb.tgKhoiHanh, DONGNHAP5);
		if (cb.tgKhoiHanh.gio == -1 || cb.tgKhoiHanh.phut == -1) {
			cb.maChuyenBay[0] = ESC;
			return cb;
		}
		if (rangBuocGio(cb.tgKhoiHanh) == -1)
		{
			break;
		}
		else
		{
			gotoxy(COT + 1, DONGNHAP5 + 2);
			cout << "  ";
			gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP5 + 2);
			cout << "  ";
		}
	} while (true);
	// xet gio lap chuyen bay 
	if (checkTime_LapCB(cb, lstCB)) {
		Red_Highlight();
		hienThongBao("May bay nay phai cat canh sau 5h nua! Hay chon may bay khac");
		goto ChonMayBay;
	}
		
	int taoDSVe = createDsVe(chonMB, cb.dsVe);
	if (taoDSVe == 1)
		cb.trangThai = CONVE;

	return cb;
}

void insert_OrderNodeCB(PTRChuyenBay& lstCB, CHUYENBAY cb) {
	PTRChuyenBay p, t, s;
	p = new NodeChuyenBay;
	p->data = cb;
	t = new NodeChuyenBay;
	for (s = lstCB; s != NULL && stricmp(s->data.maChuyenBay, cb.maChuyenBay) < 0; t = s, s = s->next);
	if (s == lstCB) {
		p->next = lstCB;
		lstCB = p;
	}
	else {
		p->next = s;
		t->next = p;
	}
}

int insertNodeCB(PTRChuyenBay& lstCB, CHUYENBAY cb) {
	PTRChuyenBay p = new NodeChuyenBay;
	p->data = cb;
	p->next = NULL;
	if (lstCB == NULL)
		lstCB = p;
	else {
		PTRChuyenBay last;
		for (last = lstCB; last->next != NULL; last = last->next);
		last->next = p;
	}
	return 1;
}

int hieuChinh_CB(PTRChuyenBay& lstCB, PTRChuyenBay p, LIST_MB lstMB) {
	khungNhapThongTin(GDTHEM_CB, "HIEU CHINH CHUYEN BAY", "Ma chuyen bay:", "So hieu may bay:", "San bay den:", "Ngay khoi hanh:", "Gio khoi hanh:");
	ChuyenBay cb;
	if (p == NULL)
	{
		return 0;
	}
	mayBay mbCu = getMB(lstMB, p->data.soHieuMayBay);
	gotoxy(COT + 1, DONGNHAP1 + 2);
	
	rewind(stdin);
	cout << p->data.maChuyenBay;
	strcpy(cb.maChuyenBay, p->data.maChuyenBay);
	gotoxy(COT + 1, DONGNHAP3 + 2);
	cout << p->data.sanBayDen;
	strcpy(cb.sanBayDen, p->data.sanBayDen);
	cb.trangThai = p->data.trangThai;
	
	//ChonMayBay:
	do {
		do
		{
			// chon may bay tren giao dien
			mayBay chonMB;
			chonMB = ChonMB_LapCB(lstMB);
			strcpy(cb.soHieuMayBay, chonMB.soHieuMayBay);
			// tim may bay bang cach nhap
			if (chonMB.soHieuMayBay[0] == '\0') {
				strcpy(cb.soHieuMayBay, CheckInputStr(true, DONGNHAP2));

				chonMB = getMB(lstMB, cb.soHieuMayBay);
				if (chonMB.soHieuMayBay[0] == '\0') {
					Red_Highlight();
					hienThongBao("Khong co may bay nao mang so hieu nay!");
					continue;
				}
				else if (cb.soHieuMayBay[0] == ESC) {
					cb.maChuyenBay[0] = ESC;
					return 0;
				}
				else {
					if (!checkSoDay_SoDong(mbCu, chonMB)) {
						themSLVe(cb.dsVe, chonMB, p->data.dsVe);
						break;
					}

				}

			}
			else {
				if (!checkSoDay_SoDong(mbCu, chonMB)) {
					gotoxy(COT + 1, DONGNHAP2 + 2);
					cout << cb.soHieuMayBay;

					themSLVe(cb.dsVe, chonMB, p->data.dsVe);
					break;
				}
			}

		} while (true);

		if (!checkBooked(p->data.dsVe)) {
			do
			{
				strcpy(cb.sanBayDen, CheckInputStr(false, DONGNHAP3));
				if (cb.sanBayDen[0] == ESC) {
					return 0;
				}
				else
					break;
			} while (true);
		}

		do
		{
			cb.tgKhoiHanh = CheckInputDate(cb.tgKhoiHanh, DONGNHAP4);
			if (cb.tgKhoiHanh.ngay == -1 || cb.tgKhoiHanh.thang == -1 || cb.tgKhoiHanh.nam == -1) {

				return 0;
			}
			if (rangBuocThoiGian(cb.tgKhoiHanh, THEM_CB) == -1)
			{
				break;
			}
			else
			{
				gotoxy(COT + 1, DONGNHAP4 + 2);
				cout << "  ";
				gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP4 + 2);
				cout << "  ";
				gotoxy(COT + DAIKHUNGNHO * 2 + 1, DONGNHAP4 + 2);
				cout << "    ";
			}
		} while (true);

		do
		{
			cb.tgKhoiHanh = CheckInputTime(cb.tgKhoiHanh, DONGNHAP5);
			if (cb.tgKhoiHanh.gio == -1 || cb.tgKhoiHanh.phut == -1) {

				return 0;
			}
			if (rangBuocGio(cb.tgKhoiHanh) == -1)
			{
				break;
			}
			else
			{
				gotoxy(COT + 1, DONGNHAP5 + 2);
				cout << "  ";
				gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP5 + 2);
				cout << "  ";
			}
		} while (true);

		// xet gio lap chuyen bay 
		if (checkTime_LapCB(cb, lstCB)) {
			Red_Highlight();
			hienThongBao("May bay nay phai cat canh sau 5h nua! Hay chon may bay khac");
			//goto ChonMayBay;

		}
		else break;
	}while (true);

	p->data = cb;
	
	return 1;
}

int xoa_CB(PTRChuyenBay& lstCB, char ma[]) {
	PTRChuyenBay p = lstCB;
	if (empty_CB(lstCB))
		return 0;
	if (stricmp(lstCB->data.maChuyenBay, ma) == 0) {
		p = lstCB;
		p = p->next;
		delete p;
		return 1;
	}
	else {
		for (p = p; p->next != NULL && stricmp(p->next->data.maChuyenBay, ma) != 0; p = p->next);
		if (p->next != NULL) {
			PTRChuyenBay q = p->next;
			p->next = q->next;
			delete q;
			return 1;
		}
		else return 0;
	}
	
}

int huy_CB(PTRChuyenBay& lstCB, PTRChuyenBay p) {
	
	if (empty_CB(lstCB))
		return 0;
	else {
		if (p->data.trangThai == HOANTAT
			|| p->data.trangThai == HUYCHUYEN) {
			return 0;
		}
		else {
			p->data.trangThai = HUYCHUYEN;
			return 1;
		}
	}
}

int checkStatus_CB(CHUYENBAY cb) {
	if (cb.trangThai == HOANTAT) {
		Red_Highlight();
		hienThongBao("Chuyen bay da hoan tat khong the thao tac!");
		return 1;
	}
	if (cb.trangThai == HUYCHUYEN) {
		Red_Highlight();
		hienThongBao("Chuyen bay da bi huy khong the thao tac!");
		return 1;
	}
	if (cb.trangThai == HETVE) {
		Red_Highlight();
		hienThongBao("Chuyen bay da het ve!");
		return 1;
	}
	return 0;
}

int checkBooked(LIST_VE lstVe) {
	for (int i = 0; i < lstVe.n; i++) {
		if (stricmp(lstVe.Ve[i]->data.CMND, "") != 0) {
			return 1;
		}
	}
	return 0;
}

int checkHoanTat_CB(PTRChuyenBay& lstCB) {
	time_t baygio = time(0);
	tm* ltm = localtime(&baygio);
	THOI_GIAN tg;
	tg.ngay = ltm->tm_mday;
	tg.thang = ltm->tm_mon + 1;
	tg.nam = ltm->tm_year + 1900;
	tg.gio = ltm->tm_hour;
	tg.phut = ltm->tm_min;
	
	for (PTRChuyenBay p = lstCB; p != NULL; p = p->next) {
		
		if (toTime(p->data.tgKhoiHanh) - toTime(tg) <= 0) {
			if (checkTime_HoanTat(p->data.tgKhoiHanh, tg)) {
				p->data.trangThai = HOANTAT;
			}
		}
	}
	
	return 1;
}

int checkTimeHienTai(THOI_GIAN tg) {
	time_t baygio = time(0);
	tm* ltm = localtime(&baygio);
	THOI_GIAN t;
	t.ngay = ltm->tm_mday;
	t.thang = ltm->tm_mon + 1;
	t.nam = ltm->tm_year + 1900;
	t.gio = ltm->tm_hour;
	t.phut = ltm->tm_min;

	if (toTime(tg) - toTime(t) == 0)
		return 1;
	return 0;
}

int checkSoDay_SoDong(mayBay mbCu, mayBay mbMoi) {
	if (mbMoi.soDay < mbCu.soDay || mbMoi.soDong < mbCu.soDong) {
		Red_Highlight();
		hienThongBao("So day, so dong phai >= so day, so dong may bay cu");
		return 1;
	}
	return 0;
}

void showCB(PTRChuyenBay lstCB) {
	khungXuatDS(XUAT_CB, DONGDS_D - DONGDS_U, COTDS_R - COTDS_L, 5, 25, 45, 80, 100);

	int i = 0;
	for (PTRChuyenBay p = lstCB; p != NULL; p = p->next) {
		gotoxy(COTDS_L + 1, DONGDS_U + 3 + i);
		cout << i + 1;
		gotoxy(COTDS_L + 6, DONGDS_U + 3 + i);
		cout << p->data.maChuyenBay;
		gotoxy(COTDS_L + 26, DONGDS_U + 3 + i);
		cout << p->data.soHieuMayBay;
		gotoxy(COTDS_L + 46, DONGDS_U + 3 + i);
		cout << p->data.sanBayDen;
		gotoxy(COTDS_L + 81, DONGDS_U + 3 + i);
		cout << p->data.tgKhoiHanh.ngay << "/" << p->data.tgKhoiHanh.thang << "/" << p->data.tgKhoiHanh.nam
			<< " " << p->data.tgKhoiHanh.gio << ":" << p->data.tgKhoiHanh.phut;
		gotoxy(COTDS_L + 101, DONGDS_U + 3 + i);
		if(p->data.trangThai == 0)
			cout << "Da huy";
		else if (p->data.trangThai == 1)
			cout << "Con ve";
		else if (p->data.trangThai == 2)
			cout << "Het ve";
		else if (p->data.trangThai == 3)
			cout << "Hoan tat";
		i++;
		if (i == MAX_PAGE)
			break;
	}
	
}

void showCB_DatVe(PTRChuyenBay lstCB) {
	khungXuatDS(XUAT_CB, DONGDS_D - DONGDS_U, COTDS_R - COTDS_L, 5, 25, 45, 80, 100);

	int i = 0;
	for (PTRChuyenBay p = lstCB; p != NULL; p = p->next) {
		if (p->data.trangThai == CONVE) {
			gotoxy(COTDS_L + 1, DONGDS_U + 3 + i);
			cout << i + 1;
			gotoxy(COTDS_L + 6, DONGDS_U + 3 + i);
			cout << p->data.maChuyenBay;
			gotoxy(COTDS_L + 26, DONGDS_U + 3 + i);
			cout << p->data.soHieuMayBay;
			gotoxy(COTDS_L + 46, DONGDS_U + 3 + i);
			cout << p->data.sanBayDen;
			gotoxy(COTDS_L + 81, DONGDS_U + 3 + i);
			cout << p->data.tgKhoiHanh.ngay << "/" << p->data.tgKhoiHanh.thang << "/" << p->data.tgKhoiHanh.nam
				<< " " << p->data.tgKhoiHanh.gio << ":" << p->data.tgKhoiHanh.phut;
			
			int veTrong = p->data.dsVe.n - demSoVe(p->data.dsVe);
			gotoxy(COTDS_L + 101, DONGDS_U + 3 + i);
			cout << "Con " << veTrong << " ve";
			i++;
		}
		
	}

}

void show_1_CB_DatVe(CHUYENBAY* cb, int chon) {
	gotoxy(COTDS_L + 1, DONGDS_U + 3 + chon);
	cout << "                                                                                                                 ";
	gotoxy(COTDS_L + 1, DONGDS_U + 3 + chon);
	cout << chon + 1;
	gotoxy(COTDS_L + 5, DONGDS_U + 3 + chon);
	cout << char(DOC);
	gotoxy(COTDS_L + 6, DONGDS_U + 3 + chon);
	cout << cb->maChuyenBay;
	gotoxy(COTDS_L + 25, DONGDS_U + 3 + chon);
	cout << char(DOC);
	gotoxy(COTDS_L + 26, DONGDS_U + 3 + chon);
	cout << cb->soHieuMayBay;
	gotoxy(COTDS_L + 45, DONGDS_U + 3 + chon);
	cout << char(DOC);
	gotoxy(COTDS_L + 46, DONGDS_U + 3 + chon);
	cout << cb->sanBayDen;
	gotoxy(COTDS_L + 80, DONGDS_U + 3 + chon);
	cout << char(DOC);
	gotoxy(COTDS_L + 81, DONGDS_U + 3 + chon);
	cout << cb->tgKhoiHanh.ngay << "/" << cb->tgKhoiHanh.thang << "/" << cb->tgKhoiHanh.nam
		<< " " << cb->tgKhoiHanh.gio << ":" << cb->tgKhoiHanh.phut;
	gotoxy(COTDS_L + 100, DONGDS_U + 3 + chon);
	cout << char(DOC);
	int veTrong = cb->dsVe.n - demSoVe(cb->dsVe);
	gotoxy(COTDS_L + 101, DONGDS_U + 3 + chon);
	cout << "Con " << veTrong << " ve";

	Normal();

	gotoxy(COT + 1, DONGNHAP1 + 2);
	cout << "                                     ";
	gotoxy(COT + 1, DONGNHAP1 + 2);
	cout << cb->maChuyenBay;
	gotoxy(COT + 1, DONGNHAP2 + 2);
	cout << "                                     ";
	gotoxy(COT + 1, DONGNHAP2 + 2);
	cout << cb->soHieuMayBay;
	gotoxy(COT + 1, DONGNHAP3 + 2);
	cout << "                                     ";
	gotoxy(COT + 1, DONGNHAP3 + 2);
	cout << cb->sanBayDen;
	gotoxy(COT + 1, DONGNHAP4 + 2);
	cout << "    ";
	gotoxy(COT + 1, DONGNHAP4 + 2);
	cout << cb->tgKhoiHanh.ngay;
	gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP4 + 2);
	cout << "    ";
	gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP4 + 2);
	cout << cb->tgKhoiHanh.thang;
	gotoxy(COT + DAIKHUNGNHO * 2 + 1, DONGNHAP4 + 2);
	cout << "    ";
	gotoxy(COT + DAIKHUNGNHO * 2 + 1, DONGNHAP4 + 2);
	cout << cb->tgKhoiHanh.nam;
	gotoxy(COT + 1, DONGNHAP5 + 2);
	cout << "    ";
	gotoxy(COT + 1, DONGNHAP5 + 2);
	cout << cb->tgKhoiHanh.gio;
	gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP5 + 2);
	cout << "    ";
	gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP5 + 2);
	cout << cb->tgKhoiHanh.phut;
}

void showCB_ConVe(CHUYENBAY* p, int &i) {
	khungXuatDS(LOC_CB, DONGDS_D - DONGDS_U, COTDS_R - COTDS_L, 5, 25, 45, 80, 100);

	gotoxy(COTDS_L + 1, DONGDS_U + 3 + i);
	cout << i + 1;
	gotoxy(COTDS_L + 6, DONGDS_U + 3 + i);
	cout << p->maChuyenBay;
	gotoxy(COTDS_L + 26, DONGDS_U + 3 + i);
	cout << p->soHieuMayBay;
	gotoxy(COTDS_L + 46, DONGDS_U + 3 + i);
	cout << p->sanBayDen;
	gotoxy(COTDS_L + 81, DONGDS_U + 3 + i);
	cout << p->tgKhoiHanh.ngay << "/" << p->tgKhoiHanh.thang << "/" << p->tgKhoiHanh.nam
		<< " " << p->tgKhoiHanh.gio << ":" << p->tgKhoiHanh.phut;
		
	int veTrong = p->dsVe.n - demSoVe(p->dsVe);
	gotoxy(COTDS_L + 101, DONGDS_U + 3 + i);
	cout << "Con " << veTrong << " ve";
	
	
}

void show_1_CB(CHUYENBAY *cb, int chon) {
	gotoxy(COTDS_L + 1, DONGDS_U + 3 + chon);
	cout << "                                                                                                                 ";
	gotoxy(COTDS_L + 1, DONGDS_U + 3 + chon);
	cout << chon + 1;
	gotoxy(COTDS_L + 5, DONGDS_U + 3 + chon);
	cout << char(DOC);
	gotoxy(COTDS_L + 6, DONGDS_U + 3 + chon);
	cout << cb->maChuyenBay;
	gotoxy(COTDS_L + 25, DONGDS_U + 3 + chon);
	cout << char(DOC);
	gotoxy(COTDS_L + 26, DONGDS_U + 3 + chon);
	cout << cb->soHieuMayBay;
	gotoxy(COTDS_L + 45, DONGDS_U + 3 + chon);
	cout << char(DOC);
	gotoxy(COTDS_L + 46, DONGDS_U + 3 + chon);
	cout << cb->sanBayDen;
	gotoxy(COTDS_L + 80, DONGDS_U + 3 + chon);
	cout << char(DOC);
	gotoxy(COTDS_L + 81, DONGDS_U + 3 + chon);
	cout << cb->tgKhoiHanh.ngay << "/" << cb->tgKhoiHanh.thang << "/" << cb->tgKhoiHanh.nam
		<< " " << cb->tgKhoiHanh.gio << ":" << cb->tgKhoiHanh.phut;
	gotoxy(COTDS_L + 100, DONGDS_U + 3 + chon);
	cout << char(DOC);
	gotoxy(COTDS_L + 101, DONGDS_U + 3 + chon);
	if (cb->trangThai == 0)
		cout << "Da huy";
	else if (cb->trangThai == 1)
		cout << "Con ve";
	else if (cb->trangThai == 2)
		cout << "Het ve";
	else if (cb->trangThai == 3)
		cout << "Hoan tat";
	
	Normal();

	gotoxy(COT + 1, DONGNHAP1 + 2);
	cout << "                                     ";
	gotoxy(COT + 1, DONGNHAP1 + 2);
	cout << cb->maChuyenBay;
	gotoxy(COT + 1, DONGNHAP2 + 2);
	cout << "                                     ";
	gotoxy(COT + 1, DONGNHAP2 + 2);
	cout << cb->soHieuMayBay;
	gotoxy(COT + 1, DONGNHAP3 + 2);
	cout << "                                     ";
	gotoxy(COT + 1, DONGNHAP3 + 2);
	cout << cb->sanBayDen;
	gotoxy(COT + 1, DONGNHAP4 + 2);
	cout << "    ";
	gotoxy(COT + 1, DONGNHAP4 + 2);
	cout << cb->tgKhoiHanh.ngay;
	gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP4 + 2);
	cout << "    ";
	gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP4 + 2);
	cout << cb->tgKhoiHanh.thang;
	gotoxy(COT + DAIKHUNGNHO * 2 + 1, DONGNHAP4 + 2);
	cout << "    ";
	gotoxy(COT + DAIKHUNGNHO * 2 + 1, DONGNHAP4 + 2);
	cout << cb->tgKhoiHanh.nam;
	gotoxy(COT + 1, DONGNHAP5 + 2);
	cout << "    ";
	gotoxy(COT + 1, DONGNHAP5 + 2);
	cout << cb->tgKhoiHanh.gio;
	gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP5 + 2);
	cout << "    ";
	gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP5 + 2);
	cout << cb->tgKhoiHanh.phut;
}

//============== cac ham xu ly hanh khach ===================//
void init_HK(TREEHanhKhach& lstHK) {
	lstHK = NULL;
}

int empty_HK(TREEHanhKhach lstHK) {
	return lstHK == NULL;
}

int timTrung_HK(TREEHanhKhach lstHK, char soCMND[]) {
	if (lstHK == NULL)
		return 0;
	if (lstHK != NULL)
	{
		if (stricmp(lstHK->data.CMND, soCMND) == 0) // neu so CMND ton tai trong cay
		{
			return 1;
		}
		else if (stricmp(lstHK->data.CMND, soCMND) > 0)
		{
			timTrung_HK(lstHK->Left, soCMND);
		}
		else if (stricmp(lstHK->data.CMND, soCMND) < 0)
		{
			timTrung_HK(lstHK->Right, soCMND);
		}
	}
}

TREEHanhKhach timKiem_HK(TREEHanhKhach lstHK, char cmnd[]) {
	TREEHanhKhach p;
	p = lstHK;
	
	while (p != NULL && stricmp(p->data.CMND, cmnd) != 0)
	{
		if (stricmp(p->data.CMND, cmnd) > 0)
		{
			p = p->Left;
		}
		else if (stricmp(p->data.CMND, cmnd) < 0)
		{
			p = p->Right;
		}
	}
	return p;
}

void insertNode_HK(TREEHanhKhach& lstHK, HANHKHACH p) {
	if (lstHK == NULL)
	{
		lstHK = new NodeHanhKhach;
		lstHK->data = p;
		lstHK->Left = NULL;
		lstHK->Right = NULL;
	}
	else
	{
		if (stricmp(lstHK->data.CMND, p.CMND) > 0)
		{
			insertNode_HK(lstHK->Left, p);
		}
		else if (stricmp(lstHK->data.CMND, p.CMND) < 0)
		{
			insertNode_HK(lstHK->Right, p);
		}
	}
}

HANHKHACH create_HK(TREEHanhKhach& lstHK, PTRChuyenBay& lstCB) {
	khungNhapThongTin(GDTHEM_HK, "NHAP THONG TIN HANH KHACH", "Nhap CMND", "Nhap ho", "Nhap ten", "Chon phai");
	HANHKHACH hk;

	do
	{
		strcpy(hk.CMND, CheckInputCMND(DONGNHAP1));
		/* kiem tra hanh khach da co hay chua */
		TREEHanhKhach tmp = timKiem_HK(lstHK, hk.CMND);
		if (tmp != NULL) {
			showHK(tmp);
			DatVe:
				int sua = confirm("SUA THONG TIN", "DAT VE", false);
			if (sua == YES) {
				int hieuChinh = hieuChinh_HK(lstHK, tmp, lstCB);
				if (hieuChinh) {
					Green_Highlight();
					hienThongBao("Sua thong tin thanh cong!");
					int savehk = saveHK(lstHK);
					int savecb = saveCB(lstCB);
					int datVe = confirm("DAT VE", "TRO VE", false);
					if (datVe == YES) {
						return tmp->data;
					}
					else {
						tmp->data.CMND[0] = ESC;
						return tmp->data;
					}
				}
				else
					goto DatVe;
			}
			else if (sua == NO){
				int datVe = confirm("DONG Y", "TRO VE", false);
				if (datVe == YES) {
					
					return tmp->data;
				}
				else {
					tmp->data.CMND[0] = ESC;
					return tmp->data;
				}
			}
			
		}
		else {
			if (hk.CMND[0] == ESC) {
				return hk;
			}
			else break;
		}
	} while (true);

	do
	{
		strcpy(hk.ho, CheckInputStr(false, DONGNHAP2));

		if (hk.ho[0] == ESC) {
			hk.CMND[0] = ESC;
			return hk;
		}
		else
			break;
	} while (true);

	do
	{
		strcpy(hk.ten, CheckInputStr(false, DONGNHAP3));

		if (hk.ten[0] == ESC) {
			hk.CMND[0] = ESC;
			return hk;
		}
		else
			break;
	} while (true);

	int chon = confirm("NAM", "NU", false);
	if (chon == YES)
		hk.phai = NAM; // nam
	if (chon == NO)
		hk.phai = NU; // nam
	return hk;
}

int hieuChinh_HK(TREEHanhKhach& lstHK, TREEHanhKhach t, PTRChuyenBay &lstCB) {
	HANHKHACH hk;
	
	do
	{
		strcpy(hk.CMND, CheckInputCMND(DONGNHAP1));

		if (timTrung_HK(lstHK, hk.CMND)) {
			/* ham kiem tra dat ve tren cung 1 chuyen bay hay khong */
			Red_Highlight();
			hienThongBao("CMND nay da co!");
		}
		else {
			if (hk.CMND[0] == ESC) {
				return 0;
			}
			else break;
		}
	} while (true);

	do
	{
		strcpy(hk.ho, CheckInputStr(false, DONGNHAP2));

		if (hk.ho[0] == ESC) {
			hk.CMND[0] = ESC;
			return 0;
		}
		else
			break;
	} while (true);

	do
	{
		strcpy(hk.ten, CheckInputStr(false, DONGNHAP3));

		if (hk.ten[0] == ESC) {
			hk.CMND[0] = ESC;
			return 0;
		}
		else
			break;
	} while (true);

	int chon = confirm("NAM", "NU", false);
	if (chon == YES)
		hk.phai = NAM; // nam
	if (chon == NO)
		hk.phai = NU; // nam

	// doi lai CMND moi trong ds ve cua chuyen bay
	for (PTRChuyenBay p = lstCB; p != NULL; p = p->next) {
		for (int i = 0; i < p->data.dsVe.n; i++) {
			if (stricmp(t->data.CMND, p->data.dsVe.Ve[i]->data.CMND) == 0) {
				strcpy(p->data.dsVe.Ve[i]->data.CMND, hk.CMND);
				break;
			}
		}
	}
	t->data = hk;
	
	return 1;
}

void xuat_HK(TREEHanhKhach lstHK, int& stt) {
}

void timNodeTheMang(TREEHanhKhach& lstHK, TREEHanhKhach& r) {
	if (r->Left != NULL)
	{
		timNodeTheMang(lstHK, r->Left);
	}
	else
	{
		lstHK->data = r->data;
		lstHK = r;
		r = r->Right;
	}
}

void remove_HK(TREEHanhKhach& lstHK, char soCMND[]) {
	if (lstHK != NULL)
	{
		if (stricmp(lstHK->data.CMND, soCMND) > 0)
		{
			remove_HK(lstHK->Left, soCMND);
		}
		else if (stricmp(lstHK->data.CMND, soCMND) < 0)
		{
			remove_HK(lstHK->Right, soCMND);
		}
		else if (stricmp(lstHK->data.CMND, soCMND) == 0)
		{
			TREEHanhKhach q;
			q = lstHK;
			if (lstHK->Left == NULL) // truong hop khong co cay con ben trai
			{
				lstHK = lstHK->Right;
			}
			else if (lstHK->Right == NULL) // truong hop khong co cay con ben phai
			{
				lstHK = lstHK->Left;
			}
			else // truong hop co cay con 2 ben
			{
				timNodeTheMang(q, lstHK->Right);
			}
			delete q;
		}
	}
}

void showHK(TREEHanhKhach lstHK) {
	gotoxy(COT + 1, DONGNHAP1 + 2);
	cout << lstHK->data.CMND;
	gotoxy(COT + 1, DONGNHAP2 + 2);
	cout << lstHK->data.ho;
	gotoxy(COT + 1, DONGNHAP3 + 2);
	cout << lstHK->data.ten;
	gotoxy(COT + 1, DONGNHAP4 + 2);
	cout << (lstHK->data.phai == NAM ? "Nam" : "Nu");
}

void xuatHK_1_CB(CHUYENBAY *cb, TREEHanhKhach lstHK, int page) {
	int j = page, pageHK = page, dem = 0;
	for (j, pageHK; pageHK < cb->dsVe.n; pageHK++, j++) {
		if (stricmp(cb->dsVe.Ve[j]->data.CMND, "") != 0) {
			TREEHanhKhach t = timKiem_HK(lstHK, cb->dsVe.Ve[j]->data.CMND);

			gotoxy(COTDS_L + 1, DONGDS_U + 27 + dem);
			cout << dem + 1;
			gotoxy(COTDS_L + 6, DONGDS_U + 27 + dem);
			cout << cb->dsVe.Ve[j]->data.soVe;
			gotoxy(COTDS_L + 26, DONGDS_U + 27 + dem);
			cout << t->data.CMND;
			gotoxy(COTDS_L + 46, DONGDS_U + 27 + dem);
			cout << t->data.ho << " " << t->data.ten;
			gotoxy(COTDS_L + 94, DONGDS_U + 27 + dem);
			cout << (t->data.phai == NAM ? "Nam" : "Nu");
			dem++;
		}

		if (dem == MAX_PAGE_SMALL) {
			break;
		}

	}
}

void count_HK(TREEHanhKhach lstHK, int& dem) {
	if (lstHK != NULL)
	{
		dem++;
		count_HK(lstHK->Left, dem);
		count_HK(lstHK->Right, dem);
	}
}

//========== doc xuat file ===============
int loadMB(LIST_MB& mb) {
	fstream inFile;
	inFile.open("MayBay.txt", ios::in);
	string temp;
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			mb.MB[mb.n] = new nodeMB;
			getline(inFile, temp);
			inFile.getline(mb.MB[mb.n]->data.soHieuMayBay, 20);
			inFile.getline(mb.MB[mb.n]->data.loaiMayBay, 45);
			inFile >> mb.MB[mb.n]->data.soDay;
			inFile >> mb.MB[mb.n]->data.soDong;
			mb.n++;
		}
	}
	else {
		return 0;
	}
	//mb.n--;
	inFile.close();
	return 1;
}
int saveMB(LIST_MB mb) {
	fstream outFile;
	outFile.open("MayBay.txt", ios::out);
	int i = 0;
	if (outFile.is_open()) {
		while (i < mb.n) {
			outFile << endl << mb.MB[i]->data.soHieuMayBay;
			outFile << endl << mb.MB[i]->data.loaiMayBay;
			outFile << endl << mb.MB[i]->data.soDay;
			outFile << endl << mb.MB[i]->data.soDong;
			i++;
		}
	}
	else {
		return 0;
	}
	outFile.close();
	return 1;
}
int loadCB(PTRChuyenBay& lstCB, LIST_MB lstMB) {
	
	fstream inFile;
	inFile.open("ChuyenBay.txt", ios::in);
	string temp;
	string temp1 = "";
	string ve;
	int slCB;
	if (inFile.is_open()) {
		while (!inFile.eof()) {
			

			getline(inFile, temp);
			if (temp == "") {
				CHUYENBAY cb;
				inFile.getline(cb.maChuyenBay, 20);
				inFile.getline(cb.soHieuMayBay, 20);
				inFile.getline(cb.sanBayDen, 50);
				inFile >> cb.tgKhoiHanh.ngay;
				inFile >> cb.tgKhoiHanh.thang;
				inFile >> cb.tgKhoiHanh.nam;
				inFile >> cb.tgKhoiHanh.gio;
				inFile >> cb.tgKhoiHanh.phut;
				inFile >> cb.trangThai;

				mayBay mb = getMB(lstMB, cb.soHieuMayBay);
				int dsve = createDsVe(mb, cb.dsVe);
			
				getline(inFile, temp1);
				getline(inFile, temp1);
				while (temp1 != "") {
					
					int vitri = 0;
					char cmnd[12] = "";
					

					catChuoi(temp1, '-', vitri, cmnd);
					insertVe(cb.dsVe, vitri, cmnd);
					
					getline(inFile, temp1);
				}
		
				insertNodeCB(lstCB, cb);
			}
		}
	}
	else {
		return 0;
	}
	
	inFile.close();
	return 1;
}
int saveCB(PTRChuyenBay lstCB) {
	ChuyenBay cb;
	fstream outFile;
	outFile.open("ChuyenBay.txt", ios::out);
	
	if (outFile.is_open()) {
		for (PTRChuyenBay p = lstCB; p != NULL; p = p->next) {
			outFile << endl << p->data.maChuyenBay;
			outFile << endl << p->data.soHieuMayBay;
			outFile << endl << p->data.sanBayDen;
			outFile << endl << p->data.tgKhoiHanh.ngay;
			outFile << endl << p->data.tgKhoiHanh.thang;
			outFile << endl << p->data.tgKhoiHanh.nam;
			outFile << endl << p->data.tgKhoiHanh.gio;
			outFile << endl << p->data.tgKhoiHanh.phut;
			outFile << endl << p->data.trangThai;
			for (int i = 0; i < p->data.dsVe.n; i++) {
				if(stricmp(p->data.dsVe.Ve[i]->data.CMND, "") != 0)
					outFile << endl << p->data.dsVe.Ve[i]->data.soVe << "," << i << "-" << p->data.dsVe.Ve[i]->data.CMND;
			}
			if (p->next == NULL)
				outFile << endl;
			if (p->next != NULL) {
				outFile << endl;
				outFile << endl;
			}
			
		}
	}
	else
		return 0;
	outFile.close();
	return 1;
}

int loadHK(TREEHanhKhach& lstHK) {
	fstream inFile;
	inFile.open("D:/CauTrucDuLieu&GiaiThuat/CTDL/HanhKhach.txt", ios::in);
	HANHKHACH hk;
	string temp;
	char phai[4];
	if (!inFile.fail()) {
		while (!inFile.eof())
		{
			getline(inFile, temp);
			inFile.getline(hk.CMND, 12);
			inFile.getline(hk.ho, 50);
			inFile.getline(hk.ten, 10);
			inFile.getline(phai, 4);
			if (stricmp(phai, "Nam") == 0) {
				hk.phai = NAM;
			}
			else if (stricmp(phai, "Nu") == 0) {
				hk.phai = NU;
			}
			insertNode_HK(lstHK, hk);
		}
	}
	else {
		return 0;
	}
	inFile.close();
	return 1;
}
void duyetCay(TREEHanhKhach lstHK, fstream& file) {
	if (lstHK != NULL) {
		file << endl << lstHK->data.CMND;
		file << endl << lstHK->data.ho;
		file << endl << lstHK->data.ten;
		if (lstHK->data.phai == NAM)
			file << endl << "Nam";
		else if (lstHK->data.phai == NU)
			file << endl << "Nu";
		file << endl;
		duyetCay(lstHK->Left, file);
		duyetCay(lstHK->Right, file);
	}
}
int saveHK(TREEHanhKhach lstHK) {
	fstream outFile;
	outFile.open("D:/CauTrucDuLieu&GiaiThuat/CTDL/HanhKhach.txt", ios::out);
	if (!outFile.fail()) {
		duyetCay(lstHK, outFile);
	}
	else
		return 0;
	outFile.close();
	return 1;
}
//========== xu ly nhap chuoi ===========
void NhapMA(char var[], int len) {
	int maxInput = len;
	if (maxInput == 0)
		maxInput = MAX_INPUT;
	rewind(stdin);
	NhapChuoi nhap;
	
	nhap.n = 0;
	
	while (true) {
		if (kbhit()) {
			char c = getch();
			if (!(!((int)c >= A && (int)c <= Z) && !((int)c >= a && (int)c <= z)
				&& !((int)c >= So0 && (int)c <= So9)) && nhap.n < maxInput) {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ' && c == ' ')
					continue;
				if (!(nhap.n == 0 && (int)c >= So0 && (int)c <= So9)) {
					c = toupper(c);
					nhap.data[nhap.n] = new char;
					cout << c;
					*nhap.data[nhap.n] = c;
					nhap.n++;
				}
			}
			if (c == '\r') {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ') {
					gotoxy(wherex() - 1, wherey());
					cout << " ";
					gotoxy(wherex() - 1, wherey());
					if (nhap.n > 0)
						nhap.n--;
				}
				
				break;
			}
			if (c == BACKSPACE && nhap.n > 0) {
				gotoxy(wherex() - 1, wherey());
				cout << " ";
				gotoxy(wherex() - 1, wherey());
				nhap.n--;
			}
			if (c == ESC) {
				var[0] = ESC;
				return;
			}
		}
	}
	for (int i = 0; i < nhap.n; i++) {
		var[i] = *nhap.data[i];
	}
	var[nhap.n] = '\0';
}

void NhapCHUOI(char var[], int len) {
	int maxInput = len;
	if (maxInput == 0)
		maxInput = MAX_INPUT;
	rewind(stdin);
	NhapChuoi nhap;
	
	nhap.n = 0;

	while (true) {
		if (kbhit()) {
			char c = getch();
			
			if (!(!((int)c >= A && (int)c <= Z) && !((int)c >= a && (int)c <= z)
				&& c != ' ') && nhap.n < maxInput) {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ' && c == ' ')
					continue;
				if (!(nhap.n == 0 && c == ' ')) {
					if (nhap.n == 0)
						c = toupper(c);
					else {
						if (*nhap.data[nhap.n - 1] == ' ')
							c = toupper(c);
						else
							c = tolower(c);
					}
					nhap.data[nhap.n] = new char;
					cout << c;
					*nhap.data[nhap.n] = c;
					nhap.n++;
				}
			}
			if (c == '\r') {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ') {
					gotoxy(wherex() - 1, wherey());
					cout << " ";
					gotoxy(wherex() - 1, wherey());
					if (nhap.n > 0)
						nhap.n--;
				}

				break;
			}
			if (c == BACKSPACE && nhap.n > 0) {
				gotoxy(wherex() - 1, wherey());
				cout << " ";
				gotoxy(wherex() - 1, wherey());
				nhap.n--;
			}
			if (c == ESC) {
				var[0] = ESC;
				return;
			}
		}
	}
	for (int i = 0; i < nhap.n; i++) {
		var[i] = *nhap.data[i];
	}
	var[nhap.n] = '\0';
}

void NhapCHUOI_SO(char var[], int len) {
	
	int maxInput = len;
	if (maxInput == 0)
		maxInput = MAX_INPUT;
	rewind(stdin);
	NhapChuoi nhap;

	nhap.n = 0;

	while (true) {
		if (kbhit()) {
			char c = getch();
			if (!(!((int)c >= 65 && (int)c <= 90) && !((int)c >= 97 && (int)c <= 122)
				&& !((int)c >= 48 && (int)c <= 57) && c != ' ') && nhap.n < maxInput) {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ' && c == ' ')
					continue;
				if (!(nhap.n == 0 && c == ' ')) {
					if (nhap.n == 0)
						c = toupper(c);
					else {
						if (*nhap.data[nhap.n - 1] == ' ')
							c = toupper(c);
						else
							c = tolower(c);
					}
					nhap.data[nhap.n] = new char;
					cout << c;
					*nhap.data[nhap.n] = c;
					nhap.n++;
				}
			}
			if (c == '\r') {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ') {
					gotoxy(wherex() - 1, wherey());
					cout << " ";
					gotoxy(wherex() - 1, wherey());
					if (nhap.n > 0)
						nhap.n--;
				}
				
				break;
			}
			if (c == BACKSPACE && nhap.n > 0) {
				gotoxy(wherex() - 1, wherey());
				cout << " ";
				gotoxy(wherex() - 1, wherey());
				nhap.n--;
			}
			if (c == ESC) {
				var[0] = ESC;
				return;
			}
		}
	}
	for (int i = 0; i < nhap.n; i++) {
		var[i] = *nhap.data[i];
	}
	var[nhap.n] = '\0';
}

void Nhap_SO(int &var, int len) {
	char num[12] = { '\0' };
	int maxInput = len;
	if (maxInput == 0)
		maxInput = MAX_INPUT;
	
	rewind(stdin);
	NhapChuoi nhap;
	nhap.n = strlen(num);

	while (true) {
		if (kbhit()) {
			char c = getch();
			if (nhap.n < 11) {
				if ((int)c >= So0 && (int)c <= So9 && nhap.n < maxInput) {

					nhap.data[nhap.n] = new char;
					cout << c;
					*nhap.data[nhap.n] = c;
					nhap.n++;
				}
			}
			if (c == '\r') {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ') {
					gotoxy(wherex() - 1, wherey());
					cout << " ";
					gotoxy(wherex() - 1, wherey());
					if (nhap.n > 0)
						nhap.n--;
				}
					
				break;
			}
			if (c == BACKSPACE && nhap.n > 0) {
				gotoxy(wherex() - 1, wherey());
				cout << " ";
				gotoxy(wherex() - 1, wherey());
				nhap.n--;
			}
			if (c == ESC) {
				var = -1;
				return;
			}
			
		}
	}
	for (int i = 0; i < nhap.n; i++) {
		num[i] = *nhap.data[i];
	}
	num[nhap.n] = '\0';
	var = atoi(num);
}

void NhapNGAY(int& var, int len) {
	char num[12] = { '\0' };
	int maxInput = len;
	if (maxInput == 0)
		maxInput = MAX_INPUT;

	rewind(stdin);
	NhapChuoi nhap;
	nhap.n = strlen(num);

	while (true) {
		if (kbhit()) {
			char c = getch();
			if (nhap.n < 2) {
				if ((int)c >= So0 && (int)c <= So9 && nhap.n < maxInput) {
					if ((nhap.n > 0 && (int)*nhap.data[nhap.n - 1] == So3 && (int)c >= So2)
						|| (nhap.n > 0 && (int)*nhap.data[nhap.n - 1] >= 52 && c >= So0)
						|| (nhap.n == 0 && (int)c == So0)) {
						continue;
					}
					nhap.data[nhap.n] = new char;
					cout << c;
					*nhap.data[nhap.n] = c;
					nhap.n++;
				}
			}
			if (c == '\r') {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ') {
					gotoxy(wherex() - 1, wherey());
					cout << " ";
					gotoxy(wherex() - 1, wherey());
					if (nhap.n > 0)
						nhap.n--;
				}

				break;
			}
			if (c == BACKSPACE && nhap.n > 0) {
				gotoxy(wherex() - 1, wherey());
				cout << " ";
				gotoxy(wherex() - 1, wherey());
				nhap.n--;
			}
			if (c == ESC) {
				var = -1;
				return;
			}
			
		}
	}
	for (int i = 0; i < nhap.n; i++) {
		num[i] = *nhap.data[i];
	}
	num[nhap.n] = '\0';
	var = atoi(num);
}

void NhapTHANG(int& var, int len) {
	char num[12] = { '\0' };
	int maxInput = len;
	if (maxInput == 0)
		maxInput = MAX_INPUT;

	rewind(stdin);
	NhapChuoi nhap;
	nhap.n = strlen(num);

	while (true) {
		if (kbhit()) {
			char c = getch();
			if (nhap.n < 2) {
				if ((int)c >= So0 && (int)c <= So9 && nhap.n < maxInput) {
					if ((nhap.n > 0 && (int)*nhap.data[nhap.n - 1] == So1 && (int)c >= So3)
						|| (nhap.n > 0 && (int)*nhap.data[nhap.n - 1] >= So2 && c >= So0)
						|| (nhap.n == 0 && (int)c == So0)) {
						continue;
					}
					nhap.data[nhap.n] = new char;
					cout << c;
					*nhap.data[nhap.n] = c;
					nhap.n++;
				}
			}
			if (c == '\r') {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ') {
					gotoxy(wherex() - 1, wherey());
					cout << " ";
					gotoxy(wherex() - 1, wherey());
					if (nhap.n > 0)
						nhap.n--;
				}

				break;
			}
			if (c == BACKSPACE && nhap.n > 0) {
				gotoxy(wherex() - 1, wherey());
				cout << " ";
				gotoxy(wherex() - 1, wherey());
				nhap.n--;
			}
			if (c == ESC) {
				var = -1;
				return;
			}
			
		}
	}
	for (int i = 0; i < nhap.n; i++) {
		num[i] = *nhap.data[i];
	}
	num[nhap.n] = '\0';
	var = atoi(num);
}

void NhapNAM(int& var, int len) {
	char num[12] = { '\0' };
	int maxInput = len;
	if (maxInput == 0)
		maxInput = MAX_INPUT;

	rewind(stdin);
	NhapChuoi nhap;
	nhap.n = strlen(num);

	while (true) {
		if (kbhit()) {
			char c = getch();
			if (nhap.n < 4) {
				if ((int)c >= So0 && (int)c <= So9 && nhap.n < maxInput) {
					if ((nhap.n == 0 && (int)c == So0)) {
						continue;
					}
					nhap.data[nhap.n] = new char;
					cout << c;
					*nhap.data[nhap.n] = c;
					nhap.n++;
				}
			}
			if (c == '\r') {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ') {
					gotoxy(wherex() - 1, wherey());
					cout << " ";
					gotoxy(wherex() - 1, wherey());
					if (nhap.n > 0)
						nhap.n--;
				}

				break;
			}
			if (c == BACKSPACE && nhap.n > 0) {
				gotoxy(wherex() - 1, wherey());
				cout << " ";
				gotoxy(wherex() - 1, wherey());
				nhap.n--;
			}
			if (c == ESC) {
				var = -1;
				return;
			}
		}
	}
	for (int i = 0; i < nhap.n; i++) {
		num[i] = *nhap.data[i];
	}
	num[nhap.n] = '\0';
	var = atoi(num);

}

void NhapGIO(int& var, int len) {
	char num[12] = { '\0' };
	int maxInput = len;
	if (maxInput == 0)
		maxInput = MAX_INPUT;

	rewind(stdin);
	NhapChuoi nhap;
	nhap.n = strlen(num);

	while (true) {
		if (kbhit()) {
			char c = getch();
			if (nhap.n < 2) {
				if ((int)c >= So0 && (int)c <= So9 && nhap.n < maxInput) {
					if ((nhap.n > 0 && (int)*nhap.data[nhap.n - 1] >= So2 && (int)c >= So4)) {
						continue;
					}
					nhap.data[nhap.n] = new char;
					cout << c;
					*nhap.data[nhap.n] = c;
					nhap.n++;
				}
			}
			if (c == '\r') {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ') {
					gotoxy(wherex() - 1, wherey());
					cout << " ";
					gotoxy(wherex() - 1, wherey());
					if (nhap.n > 0)
						nhap.n--;
				}

				break;
			}
			if (c == BACKSPACE && nhap.n > 0) {
				gotoxy(wherex() - 1, wherey());
				cout << " ";
				gotoxy(wherex() - 1, wherey());
				nhap.n--;
			}
			if (c == ESC) {
				var = -1;
				return;
			}

		}
	}
	for (int i = 0; i < nhap.n; i++) {
		num[i] = *nhap.data[i];
	}
	num[nhap.n] = '\0';
	var = atoi(num);
}

void NhapPHUT(int& var, int len) {
	char num[12] = { '\0' };
	int maxInput = len;
	if (maxInput == 0)
		maxInput = MAX_INPUT;

	rewind(stdin);
	NhapChuoi nhap;
	nhap.n = strlen(num);

	while (true) {
		if (kbhit()) {
			char c = getch();
			if (nhap.n < 2) {
				if ((int)c >= So0 && (int)c <= So9 && nhap.n < maxInput) {
					if ((nhap.n > 0 && (int)*nhap.data[nhap.n - 1] >= So6 && (int)c >= So0)) {
						continue;
					}
					nhap.data[nhap.n] = new char;
					cout << c;
					*nhap.data[nhap.n] = c;
					nhap.n++;
				}
			}
			if (c == '\r') {
				if (nhap.n > 0 && *nhap.data[nhap.n - 1] == ' ') {
					gotoxy(wherex() - 1, wherey());
					cout << " ";
					gotoxy(wherex() - 1, wherey());
					if (nhap.n > 0)
						nhap.n--;
				}

				break;
			}
			if (c == BACKSPACE && nhap.n > 0) {
				gotoxy(wherex() - 1, wherey());
				cout << " ";
				gotoxy(wherex() - 1, wherey());
				nhap.n--;
			}
			if (c == ESC) {
				var = -1;
				return;
			}

		}
	}
	for (int i = 0; i < nhap.n; i++) {
		num[i] = *nhap.data[i];
	}
	num[nhap.n] = '\0';
	var = atoi(num);
}

char* CheckInputStr(bool nhapMa, int DongInfo) {
	char info[50] = { '\0' };
	do
	{
		rewind(stdin);
		gotoxy(COT + 1, DongInfo + 2);
		cout << "                                ";
		gotoxy(COT + 1, DongInfo + 2);
		if (nhapMa == true) 
			NhapMA(info, 20);
		else
			NhapCHUOI(info, 45);
		if (info[0] == '\0') {
			Red_Highlight();
			hienThongBao("Chua nhap thong tin!");
		}
		// kiem tra nguoi nhap co nhan phim ESC de huy hay khong
		else if (info[0] == ESC) {
			int exit = confirm("HUY", "NHAP TIEP", false);
			if (exit == YES) {
				return info;
			}
			else
				continue;
		}
		else {
			return info;
		}

	} while (true);
}

char* CheckInputCMND(int DongInfo) {
	char info[50] = { '\0' };
	do
	{
		rewind(stdin);
		gotoxy(COT + 1, DongInfo + 2);
		cout << "                                ";
		gotoxy(COT + 1, DongInfo + 2);
		NhapCHUOI_SO(info, 10);
		if (info[0] == '\0') {
			Red_Highlight();
			hienThongBao("Chua nhap thong tin!");
		}
		// kiem tra nguoi nhap co nhan phim ESC de huy hay khong
		else if (info[0] == ESC) {
			int exit = confirm("HUY", "NHAP TIEP", false);
			if (exit == YES) {
				return info;
			}
			else
				continue;
		}
		else {
			return info;
		}

	} while (true);
}

int CheckInputNum(int DongInfo) {
	int var;
	do
	{
		rewind(stdin);
		gotoxy(COT + 1, DongInfo + 2);
		cout << "                                ";
		gotoxy(COT + 1, DongInfo + 2);
		Nhap_SO(var, 50);
		if (var == 0) {
			Red_Highlight();
			hienThongBao("Chua nhap thong tin!");
		}
		else if (var == -1) {
			int exit = confirm("HUY", "NHAP TIEP", false);
			if (exit == YES) {
				return var;
			}
			else
				continue;
		}	
		else {
			return var;
		}

	} while (true);
}


THOI_GIAN CheckInputDate(THOI_GIAN &tg, int DongInfo) {
	
	do
	{
		Ngay:
			gotoxy(COT + 1, DongInfo + 2);
			cout << "    ";
			gotoxy(COT + 1, DongInfo + 2);
			NhapNGAY(tg.ngay, 3);
			if (tg.ngay == 0 || tg.ngay == -1)
				goto Check;
		Thang:
			gotoxy(COT + DAIKHUNGNHO + 1, DongInfo + 2);
			cout << "   ";
			gotoxy(COT + DAIKHUNGNHO + 1, DongInfo + 2);
			NhapTHANG(tg.thang, 3);
			if (tg.thang == 0 || tg.thang == -1)
				goto Check;
		Nam:
			gotoxy(COT + DAIKHUNGNHO * 2 + 1, DongInfo + 2);
			cout << "    ";
			gotoxy(COT + DAIKHUNGNHO * 2 + 1, DongInfo + 2);
			NhapNAM(tg.nam, 5);
			if (tg.nam == 0 || tg.nam == -1)
				goto Check;

		Check:
			if (tg.ngay == 0 /*|| tg.thang == 0 || tg.nam == 0*/) {
				Red_Highlight();
				hienThongBao("Chua nhap thong tin!");
				if (tg.ngay == 0)
					goto Ngay;
				if (tg.thang == 0)
					goto Thang;
				if (tg.nam == 0)
					goto Nam;
				}
			if (tg.ngay == -1 || tg.thang == -1 || tg.nam == -1) {
				int exit = confirm("HUY", "NHAP TIEP", false);
				if (exit == YES) {
					return tg;
				}
				else {
					if (tg.ngay == -1)
						goto Ngay;
					if (tg.thang == -1)
						goto Thang;
					if (tg.nam == -1)
						goto Nam;
				}
			}
		return tg;
	} while (true);
}

THOI_GIAN CheckInputTime(THOI_GIAN& tg, int DongInfo) {
	
	do
	{
		Gio:
			gotoxy(COT + 1, DongInfo + 2);
			cout << "    ";
			gotoxy(COT + 1, DongInfo + 2);
			NhapGIO(tg.gio, 3);
			if (tg.gio == -1)
				goto Check;
		Phut:
			gotoxy(COT + DAIKHUNGNHO + 1, DongInfo + 2);
			cout << "   ";
			gotoxy(COT + DAIKHUNGNHO + 1, DongInfo + 2);
			NhapPHUT(tg.phut, 3);
			if (tg.phut == -1)
				goto Check;

		Check:
			if (tg.gio == -1 || tg.phut == -1) {
				int exit = confirm("HUY", "NHAP TIEP", false);
				if (exit == YES) {
					return tg;
				}
				else {
					if (tg.gio == -1)
						goto Gio;
					if (tg.phut == -1)
						goto Phut;
				}
					
			}
		return tg;

	} while (true);
}

int rangBuocThoiGian(THOI_GIAN tg, int loai) {
	
	time_t baygio = time(0);
	tm *ltm = localtime(&baygio);
	
	if (tg.ngay == 0 || tg.thang == 0 || tg.nam == 0)
	{
		hienThongBao("Khong co ngay thang nam la 0!");
		return 1;
	}
	
	if (loai != LOC_CB)
	{
		if(tg.ngay < ltm->tm_mday || tg.thang < 1 + ltm->tm_mon || tg.nam < 1900 + ltm->tm_year)
		{
			if(tg.thang <= 1 + ltm->tm_mon || tg.nam < 1900 + ltm->tm_year)
			{
				if(tg.nam <= 1900 + ltm->tm_year)
				{
					char nam[4];
					itoa(1900 + ltm->tm_year, nam, 10);
					char thang[2];
					itoa(ltm->tm_mon + 1, thang, 10);
					char ngay[2];
					itoa(ltm->tm_mday, ngay, 10);
					char thongbao[15] = "Hom nay la ";
					strcat(ngay, "/");
					strcat(ngay, thang);
					strcat(ngay, "/");
					strcat(ngay, nam);
					strcat(ngay, ". Lap chuyen bay sau ngay hien tai!");
					strcat(thongbao, ngay);
					hienThongBao(thongbao);
					return 1;
				}
			}
		}
	} 
	
	if (tg.ngay >= 31 && (tg.thang == 4 || tg.thang == 6 || tg.thang == 9 || tg.thang == 11))
	{
		char month[2];
		itoa(tg.thang, month, 10);
		char thongbao[7] = "Thang ";
		strcat(month, " chi co 30 ngay!");
		strcat(thongbao, month);
		hienThongBao(thongbao);
		return 1;
	}
	if(tg.ngay > 29 && tg.thang == 2)
	{
		char month[2];
		itoa(tg.thang, month, 10);
		char thongbao[7] = "Thang ";
		strcat(month, " co toi da 29 ngay!");
		strcat(thongbao, month);
		hienThongBao(thongbao);
		return 1;
	}
	if(!((tg.nam % 4 == 0 && tg.nam % 100 != 0) || tg.nam % 400 == 0) && tg.ngay == 29 && tg.thang == 2) // kiem tra nam nhuan
	{		
		char year[4];
		itoa(tg.nam, year, 10);
		strcat(year, " la nam khong nhuan nen thang 2 chi co 28 ngay!");	
		hienThongBao(year);		
		return 1;
	}
	if (tg.ngay > 31)
	{
		char month[2];
		itoa(tg.thang, month, 10);
		char thongbao[7] = "Thang ";
		strcat(month, " chi co 31 ngay!");
		strcat(thongbao, month);
		hienThongBao(thongbao);
		return 1;
	}
	return -1;
}

int rangBuocGio(THOI_GIAN h)
{
	time_t baygio = time(0);
	tm* ltm = localtime(&baygio);
	THOI_GIAN t;
	t.ngay = ltm->tm_mday;
	t.thang = ltm->tm_mon + 1;
	t.nam = ltm->tm_year + 1900;
	t.gio = ltm->tm_hour;
	t.phut = ltm->tm_min;
	char thongbao[70] = "Bay gio la ";
	char gio[4];
	char phut[4];
	if (checkTimeHienTai(h) && h.gio < t.gio) {
		itoa(t.gio, gio, 10);
		strcat(gio, ":");
		itoa(t.phut, phut, 10);
		strcat(thongbao, gio);
		strcat(thongbao, phut);
		Red_Highlight();
		hienThongBao(thongbao);
		return 1;
	}
	if (checkTimeHienTai(h) && h.gio == t.gio) {
		if (h.phut < t.phut) {
			itoa(t.gio, gio, 10);
			strcat(gio, ":");
			itoa(t.phut, phut, 10);
			strcat(thongbao, gio);
			strcat(thongbao, phut);
			Red_Highlight();
			hienThongBao(thongbao);
			return 1;
		}
	}
	if (h.gio > 23 || h.gio < 0)
	{
		Red_Highlight();
		hienThongBao("Gio bat dau tu 0h den 23h. Vui long nhap gio hop le!");
		return 1;
	}
	if (h.phut > 59 || h.phut < 0)
	{
		Red_Highlight();
		hienThongBao("Phut bat dau tu 0 den 59 phut. Vui long nhap phut hop le!");
		return 1;
	}
	return -1;
}

void catChuoi(string chuoi, char splitChar, int &vtri, char cmnd[]) {
	int len = chuoi.length();
	int k = 0;
	for (int i = 0; i < len; i++) {
		if (chuoi.at(i) == splitChar) {
			vtri = atoi(chuoi.substr(4, i).c_str());
			for (int j = i + 1; j < len; j++) {
				cmnd[k] = chuoi[j];
				k++;
			}
			cmnd[k + 1] = '\0';
			break;
		}
	}
}


char* stringToChar(string chuoi) {
	char *tmp;
	int len = chuoi.length();
	tmp = new char[len];
	for (int i = 0; i < len; i++) {
		tmp[i] = chuoi[i];
	}
	tmp[len] = '\0';
	return tmp;
}
//========== giao dien =============

void khungGiaoDien() {
	for (int i = 0; i < WIDTH; i++)	{
		gotoxy(i + 2, 0);
		cout << char(NGANG);
	}
	gotoxy(2, 0);
	cout << char(UPLEFT);
	for (int i = 0; i < HEIGHT; i++) {
		gotoxy(2, i + 1);
		cout << char(DOC);
	}
	gotoxy(WIDTH + 1, 0);
	cout << char(UPRIGHT);
	for (int i = 0; i < HEIGHT; i++) {
		gotoxy(WIDTH + 1, i + 1);
		cout << char(DOC);
	}
	for (int i = 0; i < WIDTH; i++) {
		gotoxy(i + 2, HEIGHT + 1);
		cout << char(NGANG);
	}
	gotoxy(2, HEIGHT + 1);
	cout << char(DOWNLEFT);
	gotoxy(WIDTH + 1, HEIGHT + 1);
	cout << char(DOWNRIGHT);

	gotoxy(2, 8);
	cout << char(BELEFT);
	for (int i = 0; i < MIDDLE_DOC; i++) {
		gotoxy(i + 3, 8);
		cout << char(NGANG);
	}
	gotoxy(MIDDLE_DOC + 3, 0);
	cout << char(BEUP);
	gotoxy(MIDDLE_DOC + 3, MIDDLE_NGANG + 1);
	cout << char(BERIGHT);
	for (int i = 0; i < MIDDLE_NGANG; i++) {
		gotoxy(MIDDLE_DOC + 3, i + 1);
		cout << char(DOC);
	}
	for (int i = 0; i < (HEIGHT - MIDDLE_NGANG) - 1; i++) {
		gotoxy(MIDDLE_DOC + 3, i + MIDDLE_NGANG + 2);
		cout << char(DOC);
	}
	gotoxy(MIDDLE_DOC + 3, HEIGHT + 1);
	cout << char(BEDOWN);
	khungThongBao();
}

void veKhungNhap(int dai, int rong, int posx, int posy, string source)
{
	int len = source.length();
	if (dai == 0)
		dai = len + 2;
	for (int i = 0; i < dai; i++) // top
	{
		gotoxy(posx + i, posy);
		cout << char(196);
	}
	gotoxy(posx, posy);
	cout << char(218); // top-left
	gotoxy(posx + dai, posy);
	cout << char(191); // top-right
	for (int i = 1; i <= rong; i++) // right
	{
		gotoxy(posx + dai, posy + i);
		cout << char(179);
	}
	for (int i = 0; i < dai; i++) // bot
	{
		gotoxy(posx + i, posy + rong);
		cout << char(196);
	}
	gotoxy(posx + dai, posy + rong);
	cout << char(217);	// bot-right	
	for (int i = 1; i <= rong; i++) // left
	{
		gotoxy(posx, posy + i);
		cout << char(179);
	}
	gotoxy(posx, posy + rong);
	cout << char(192); // bot-left
	gotoxy(posx - len / 2 + dai / 2, posy + round(rong / 2));
	cout << source;
}

void khungXuatDS(int type, int rong, int dai, int colump1, int colump2, int colump3, int colump4,
	int colump5, int posx, int posy) {
	if (posx == 0 || posy == 0)
	{
		posx = COTDS_L;
		posy = DONGDS_U;
	}
	veKhungNhap(dai, rong, posx, posy);
	for (int v = 0; v < dai - 1; v++)
	{
		gotoxy(posx + 1 + v, posy + 2);
		cout << char(196);
	}

	for (int v = 0; v < rong - 1; v++) // colump 1 
	{
		gotoxy(posx + colump1, posy + v + 1);
		cout << char(179);
	}
	gotoxy(posx + colump1, posy + 2);
	cout << char(197);
	for (int v = 0; v < rong - 1; v++) // colump 2 
	{
		gotoxy(posx + colump2, posy + v + 1);
		cout << char(179);
	}
	gotoxy(posx + colump2, posy + 2);
	cout << char(197);
	for (int v = 0; v < rong - 1; v++) // colump 3
	{
		gotoxy(posx + colump3, posy + v + 1);
		cout << char(179);
	}
	gotoxy(posx + colump3, posy + 2);
	cout << char(197);
	for (int v = 0; v < rong - 1; v++) // colump 4
	{
		gotoxy(posx + colump4, posy + v + 1);
		cout << char(179);
	}
	gotoxy(posx + colump4, posy + 2);
	cout << char(197);
	if (colump5 != 0)
	{
		for (int v = 0; v < rong - 1; v++) // colump 5
		{
			gotoxy(posx + colump5, posy + v + 1);
			cout << char(179);
		}
		gotoxy(posx + colump5, posy + 2);
		cout << char(197);
	}
	if (type == XUAT_MB) {
		//5, 25, 70, 93
		gotoxy(COTDS_L + 1, DONGDS_U + 1);
		cout << "STT";
		gotoxy(COTDS_L + 6, DONGDS_U + 1);
		cout << "SO HIEU MAY BAY";
		gotoxy(COTDS_L + 26, DONGDS_U + 1);
		cout << "LOAI MAY BAY";
		gotoxy(COTDS_L + 71, DONGDS_U + 1);
		cout << "SO DAY";
		gotoxy(COTDS_L + 94, DONGDS_U + 1);
		cout << "SO DONG";
	}
	else if (type == XUAT_CB) {
		// 5, 25, 45, 80, 100
		gotoxy(COTDS_L + 1, DONGDS_U + 1);
		cout << "STT";
		gotoxy(COTDS_L + 6, DONGDS_U + 1);
		cout << "MA CHUYEN BAY";
		gotoxy(COTDS_L + 26, DONGDS_U + 1);
		cout << "SO HIEU MAY BAY";
		gotoxy(COTDS_L + 46, DONGDS_U + 1);
		cout << "SAN BAY DEN";
		gotoxy(COTDS_L + 81, DONGDS_U + 1);
		cout << "NGAY GIO KHOI HANH";
		gotoxy(COTDS_L + 101, DONGDS_U + 1);
		cout << "TRANG THAI";
	}
	else if (type == XUAT_HK) {
		//5, 25, 45, 93
		gotoxy(COTDS_L + 1, DONGDS_U + 25);
		cout << "STT";
		gotoxy(COTDS_L + 6, DONGDS_U + 25);
		cout << "SO VE";
		gotoxy(COTDS_L + 26, DONGDS_U + 25);
		cout << "SO CMND";
		gotoxy(COTDS_L + 46, DONGDS_U + 25);
		cout << "HO TEN";
		gotoxy(COTDS_L + 94, DONGDS_U + 25);
		cout << "GIOI TINH";
	}
	else if (type == THONG_KE)
	{
		//5, 25, 70, 93
		gotoxy(COTDS_L + 1, DONGDS_U + 1);
		cout << "STT";
		gotoxy(COTDS_L + 6, DONGDS_U + 1);
		cout << "SO HIEU MAY BAY";
		gotoxy(COTDS_L + 26, DONGDS_U + 1);
		cout << "LOAI MAY BAY";
		gotoxy(COTDS_L + 71, DONGDS_U + 1);
		cout << "SO LUOT THUC HIEN BAY";
	}
	else if (type == LOC_CB) {
		// 5, 25, 45, 80, 100
		gotoxy(COTDS_L + 1, DONGDS_U + 1);
		cout << "STT";
		gotoxy(COTDS_L + 6, DONGDS_U + 1);
		cout << "MA CHUYEN BAY";
		gotoxy(COTDS_L + 26, DONGDS_U + 1);
		cout << "SO HIEU MAY BAY";
		gotoxy(COTDS_L + 46, DONGDS_U + 1);
		cout << "SAN BAY DEN";
		gotoxy(COTDS_L + 81, DONGDS_U + 1);
		cout << "NGAY GIO KHOI HANH";
		gotoxy(COTDS_L + 101, DONGDS_U + 1);
		cout << "SO VE CON LAI";
	}
}
void Normal() {
	SetColor(15);
	SetBGColor(0);
}
void Highlight() {
	SetColor(8);
	SetBGColor(7);
}
void Red_Highlight() {
	SetColor(7);
	SetBGColor(12);
}
void Green_Highlight() {
	SetColor(7);
	SetBGColor(10);
}

void khungNhapThongTin(int type, string title, string s1, string s2, string s3, string s4,
	string s5, string s6, string s7, string s8, string s9) {
	Normal();
	//========xoa thong tin cu============
	gotoxy(COT, DONGNHAP1);
	cout << "                                    ";
	gotoxy(COT, DONGNHAP2);
	cout << "                                    ";
	gotoxy(COT, DONGNHAP3);
	cout << "                                    ";
	gotoxy(COT, DONGNHAP4);
	cout << "                                    ";
	gotoxy(COT, DONGNHAP5);
	cout << "                                    ";
	gotoxy(COT + 1, DONGNHAP1 + 2);
	cout << "                                    ";
	gotoxy(COT + 1, DONGNHAP1 + 2);
	cout << "                                    ";
	gotoxy(COT + 1, DONGNHAP2 + 2);
	cout << "                                    ";
	gotoxy(COT + 1, DONGNHAP3 + 2);
	cout << "                                    ";
	gotoxy(COT + 1, DONGNHAP4 + 2);
	cout << "  ";
	gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP4 + 2);
	cout << "  ";
	gotoxy(COT + DAIKHUNGNHO * 2 + 1, DONGNHAP4 + 2);
	cout << "    ";
	gotoxy(COT + 1, DONGNHAP5 + 2);
	cout << "  ";
	gotoxy(COT + DAIKHUNGNHO + 1, DONGNHAP5 + 2);
	cout << "  ";
	//==========================
	if (type == TIM_MA) {
		gotoxy(COT + 25, DONGTD);
		cout << "                                    ";
		gotoxy(COT + 25, DONGTD);
		cout << title;
		gotoxy(COT, DONGNHAP1);
		cout << "Nhap so hieu can tim:";
		veKhungNhap(DAIKHUNG, RONGKHUNG, COT, DONGNHAP1 + 1);
		return;
	}
	else if (type == LOC_CB) {
		gotoxy(COT + 25, DONGTD);
		cout << "                                    ";
		gotoxy(COT + 25, DONGTD);
		cout << title;
		// khung nhap ngay
		gotoxy(COT, DONGNHAP1);
		cout << s1;
		veKhungNhap(DAIKHUNGNHO, RONGKHUNG, COT, DONGNHAP1 + 1);

		gotoxy(COT + DAIKHUNGNHO, DONGNHAP1);
		veKhungNhap(DAIKHUNGNHO + DAIKHUNGNHO, RONGKHUNG, COT, DONGNHAP1 + 1);

		gotoxy(COT + DAIKHUNGNHO + DAIKHUNGNHO, DONGNHAP1);
		veKhungNhap(DAIKHUNGNHO + DAIKHUNGNHO * 2, RONGKHUNG, COT, DONGNHAP1 + 1);
		
		gotoxy(COT, DONGNHAP2);
		cout << s2;
		veKhungNhap(DAIKHUNG, RONGKHUNG, COT, DONGNHAP2 + 1);
		return;
	}
	else {

		gotoxy(COT + 25, DONGTD);
		cout << title;
		gotoxy(COT, DONGNHAP1);
		cout << "                      ";
		gotoxy(COT, DONGNHAP1);
		cout << s1;
		veKhungNhap(DAIKHUNG, RONGKHUNG, COT, DONGNHAP1 + 1);

		gotoxy(COT, DONGNHAP2);
		cout << s2;
		veKhungNhap(DAIKHUNG, RONGKHUNG, COT, DONGNHAP2 + 1);

		gotoxy(COT, DONGNHAP3);
		cout << s3;
		veKhungNhap(DAIKHUNG, RONGKHUNG, COT, DONGNHAP3 + 1);

		if (type == GDTHEM_CB) {
			// khung nhap ngay
			gotoxy(COT, DONGNHAP4);
			cout << s4;
			veKhungNhap(DAIKHUNGNHO, RONGKHUNG, COT, DONGNHAP4 + 1);

			gotoxy(COT + DAIKHUNGNHO, DONGNHAP4);
			veKhungNhap(DAIKHUNGNHO + DAIKHUNGNHO, RONGKHUNG, COT, DONGNHAP4 + 1);

			gotoxy(COT + DAIKHUNGNHO + DAIKHUNGNHO, DONGNHAP4);
			veKhungNhap(DAIKHUNGNHO + DAIKHUNGNHO * 2, RONGKHUNG, COT, DONGNHAP4 + 1);

			// khung nhap gio
			gotoxy(COT, DONGNHAP5);
			cout << s5;
			veKhungNhap(DAIKHUNGNHO, RONGKHUNG, COT, DONGNHAP5 + 1);

			gotoxy(COT + DAIKHUNGNHO, DONGNHAP5);
			veKhungNhap(DAIKHUNGNHO + DAIKHUNGNHO, RONGKHUNG, COT, DONGNHAP5 + 1);
		}
		else if (type == GDTHEM_HK) {
			
			// khung nhap ngay
			gotoxy(COT, DONGNHAP4 + 1);
			cout << "                                    ";
			gotoxy(COT, DONGNHAP4 + 2);
			cout << "                                    ";
			gotoxy(COT, DONGNHAP4 + 3);
			cout << "                                    ";

			// khung nhap gio
			gotoxy(COT, DONGNHAP5 + 1);
			cout << "                                    ";
			gotoxy(COT, DONGNHAP5 + 2);
			cout << "                                    ";
			gotoxy(COT, DONGNHAP5 + 3);
			cout << "                                    ";

			gotoxy(COT, DONGNHAP4);
			cout << s4;
		}
		else {
			gotoxy(COT, DONGNHAP4);
			cout << s4;
			veKhungNhap(DAIKHUNG, RONGKHUNG, COT, DONGNHAP4 + 1);
		}

	}

}

void khungThongBao() {
	gotoxy(COT, DONGDS_D - 5);
	cout << "Thong bao";
	veKhungNhap(DAIKHUNG, RONGKHUNG + 2, COT, DONGDS_D - 4);

}

void hienThongBao(string notif, string notif2, string notif3, string NoiDen) {
	gotoxy(COT + 1, DONGDS_D - 3);
	cout << notif;
	
	if (notif2 != "") {
		gotoxy(COT + 1, DONGDS_D - 2);
		cout << notif2;
	}
	if (NoiDen != "") {
		gotoxy(COT + 1, DONGDS_D - 1);
		cout << NoiDen;
	}
	if (notif3 != "") {
		gotoxy(COT + 10, DONGDS_D - 1);
		cout << notif3;
	}
	Sleep(1000);
	Normal();
	gotoxy(COT + 1, DONGDS_D - 3);
	cout << "                                                           ";
	gotoxy(COT + 1, DONGDS_D - 2);
	cout << "                                                           ";
	gotoxy(COT + 1, DONGDS_D - 1);
	cout << "                                                           ";
}

void hienHuongDan(int type) {
	if (type == DATVE) {
		gotoxy(COT, DONG);
		cout << "ENTER: Chon";
		gotoxy(COT, DONG + 1);
		cout << "ESC: Tro ve/Thoat";
		gotoxy(COT, DONG + 2);
		cout << "<-: Trang truoc";
		gotoxy(COT, DONG + 3);
		cout << "->: Trang sau";
	}
	else {
		gotoxy(COT, DONG);
		cout << "F2: Them";
		gotoxy(COT, DONG + 1);
		cout << "F3: Tim";
		gotoxy(COT, DONG + 2);
		cout << "ENTER: Chon";
		gotoxy(COT, DONG + 3);
		cout << "DELETE: Xoa";
		gotoxy(COT, DONG + 4);
		cout << "ESC: Huy/Tro ve";
	}
	
}

void xoaKhungDS() {
	for (int i = 0; i < DONGDS_D - 2; i++) {
		gotoxy(COTDS_L, DONGDS_U + i);
		cout << "                                                                                                                   ";
	}
}

void xoaThongTin(int type) {
	if (type == XOA_MB) {
		for (int i = 0; i < MAX_PAGE; i++) {
			//5, 25, 70, 93
			gotoxy(COTDS_L + 1, DONGDS_U + 3 + i);
			cout << "    ";
			gotoxy(COTDS_L + 5, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 6, DONGDS_U + 3 + i);
			cout << "                   ";
			gotoxy(COTDS_L + 25, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 26, DONGDS_U + 3 + i);
			cout << "                                            ";
			gotoxy(COTDS_L + 70, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 71, DONGDS_U + 3 + i);
			cout << "                      ";
			gotoxy(COTDS_L + 93, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 94, DONGDS_U + 3 + i);
			cout << "                    ";
		}
	}
	else if (type == XOA_CB_L) {
		for (int i = 0; i < MAX_PAGE; i++) {
			// 5, 25, 45, 80, 100
			gotoxy(COTDS_L + 1, DONGDS_U + 3 + i);
			cout << "    ";
			gotoxy(COTDS_L + 5, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 6, DONGDS_U + 3 + i);
			cout << "                   ";
			gotoxy(COTDS_L + 25, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 26, DONGDS_U + 3 + i);
			cout << "                   ";
			gotoxy(COTDS_L + 45, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 46, DONGDS_U + 3 + i);
			cout << "                                  ";
			gotoxy(COTDS_L + 80, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 81, DONGDS_U + 3 + i);
			cout << "                   ";
			gotoxy(COTDS_L + 100, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 101, DONGDS_U + 3 + i);
			cout << "             ";
		}
	}
	else if (type == XOA_CB) {
		for (int i = 0; i < MAX_PAGE_SMALL; i++) {
			// 5, 25, 45, 80, 100
			gotoxy(COTDS_L + 1, DONGDS_U + 3 + i);
			cout << "    ";
			gotoxy(COTDS_L + 5, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 6, DONGDS_U + 3 + i);
			cout << "                   ";
			gotoxy(COTDS_L + 25, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 26, DONGDS_U + 3 + i);
			cout << "                   ";
			gotoxy(COTDS_L + 45, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 46, DONGDS_U + 3 + i);
			cout << "                                  ";
			gotoxy(COTDS_L + 80, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 81, DONGDS_U + 3 + i);
			cout << "                   ";
			gotoxy(COTDS_L + 100, DONGDS_U + 3 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 101, DONGDS_U + 3 + i);
			cout << "             ";
		}
		
	}
	else if (type == XOA_HK) {
		for (int i = 0; i < MAX_PAGE_SMALL; i++) {
			gotoxy(COTDS_L + 1, DONGDS_U + 27 + i);
			cout << "    ";
			gotoxy(COTDS_L + 5, DONGDS_U + 27 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 6, DONGDS_U + 27 + i);
			cout << "                   ";
			gotoxy(COTDS_L + 25, DONGDS_U + 27 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 26, DONGDS_U + 27 + i);
			cout << "                   ";
			gotoxy(COTDS_L + 45, DONGDS_U + 27 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 46, DONGDS_U + 27 + i);
			cout << "                                   ";
			gotoxy(COTDS_L + 93, DONGDS_U + 27 + i);
			cout << char(DOC);
			gotoxy(COTDS_L + 94, DONGDS_U + 27 + i);
			cout << "   ";
		}
	}
}

int menuDong_Prim(char td[soItem_MenuChinh][100]) {
	Normal();
	//system("cls");
	khungGiaoDien();
	int chon = 0;
	int i;
	for (int i = 0; i < soItem_MenuChinh; i++) {
		gotoxy(COT, DONG + i);
		cout << td[i];
	}
	Highlight();
	gotoxy(COT, DONG + chon);
	cout << td[chon];
	char kytu;
	do {
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		switch (kytu){
		case UP:
			if (chon > 0) {
				Normal();
				gotoxy(COT, DONG + chon); cout << td[chon];
				chon--;
				Highlight();
				gotoxy(COT, DONG + chon); 	cout << td[chon];
			}
			break;
		case DOWN:
			if (chon + 1 < soItem_MenuChinh) {
				Normal();
				gotoxy(COT, DONG + chon);	cout << td[chon];
				chon++;
				Highlight();
				gotoxy(COT, DONG + chon); 	cout << td[chon];
			}
			break;
		case ENTER:
			return chon + 1;
		case ESC:
			return 0;
		}
	} while (TRUE);
}

mayBay ChonMB_LapCB(LIST_MB lstMB) {
	xoaKhungDS();
	mayBay tmp;
	Normal();
	int page = MAX_PAGE - 1;
	if (lstMB.n < MAX_PAGE)
		page = lstMB.n;
	int dem = 0;
	int chon = 0;
	int i;
	show_MB(lstMB);
	Highlight();
	show_1_MB(lstMB, chon, false, dem);
	char kytu;
	do
	{
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		switch (kytu)
		{
		case UP:
			if (chon > 0 && dem > 0) {
				Normal();
				show_1_MB(lstMB, chon, false, dem);

				chon--;
				dem--;
				Highlight();
				show_1_MB(lstMB, chon, false, dem);
			}
			break;
		case DOWN:
			if (chon + 1 < lstMB.n && dem + 1 < MAX_PAGE) {
				Normal();
				show_1_MB(lstMB, chon, false, dem);
				chon++;
				dem++;
				Highlight();
				show_1_MB(lstMB, chon, false, dem);
			}
			break;
		case LEFT:
			if (page > MAX_PAGE) {
				Normal();
				page -= MAX_PAGE * 2;
				chon = page;
				dem = 0;
				xoaThongTin(XOA_MB);
				for (page; page < lstMB.n; page++) {
					show_1_MB(lstMB, page, true, dem);
					if (dem == MAX_PAGE - 1) {
						break;
					}
					dem++;
				}
				dem = 0;
				Highlight();
				show_1_MB(lstMB, chon, true, dem);
			}

			break;
		case RIGHT:
			if (page < lstMB.n) {
				Normal();
				xoaThongTin(XOA_MB);
				page++;
				chon = page;
				dem = 0;
				for (page; page < lstMB.n; page++) {
					show_1_MB(lstMB, page, true, dem);
					if (dem == MAX_PAGE - 1) {
						break;
					}
					dem++;
				}
				page += MAX_PAGE - dem;
				dem = 0;
				Highlight();
				show_1_MB(lstMB, chon, true, dem);
			}
			break;
		case ESC:
		{
			Normal();
			tmp.soHieuMayBay[0] = '\0';
			return tmp;
		}

		case ENTER:
			Normal();
			return lstMB.MB[chon]->data;
		}
	} while (true);
}

int menuDong_MayBay(char td[soItem_MenuMB][100]) {
	Normal();
	//system("cls");
	khungGiaoDien();
	int chon = 0;
	int i;
	for (int i = 0; i < soItem_MenuMB; i++) {
		gotoxy(COT, DONG + i);
		cout << td[i];
	}
	Highlight();
	gotoxy(COT, DONG + chon);
	cout << td[chon];
	char kytu;
	do {
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		switch (kytu) {
		case UP:
			if (chon > 0) {
				Normal();
				gotoxy(COT, DONG + chon); cout << td[chon];
				chon--;
				Highlight();
				gotoxy(COT, DONG + chon); 	cout << td[chon];
			}
			break;
		case DOWN:
			if (chon + 1 < soItem_MenuMB) {
				Normal();
				gotoxy(COT, DONG + chon);	cout << td[chon];
				chon++;
				Highlight();
				gotoxy(COT, DONG + chon); 	cout << td[chon];
			}
			break;
		case ENTER:
			return chon + 1;
		}
	} while (TRUE);
}

int menuDong_ChuyenBay(char td[soItem_MenuCB][100]) {
	Normal();
	//system("cls");
	khungGiaoDien();
	int chon = 0;
	int i;
	for (int i = 0; i < soItem_MenuCB; i++) {
		gotoxy(COT, DONG + i);
		cout << td[i];
	}
	Highlight();
	gotoxy(COT, DONG + chon);
	cout << td[chon];
	char kytu;
	do {
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		switch (kytu) {
		case UP:
			if (chon > 0) {
				Normal();
				gotoxy(COT, DONG + chon); cout << td[chon];
				chon--;
				Highlight();
				gotoxy(COT, DONG + chon); 	cout << td[chon];
			}
			break;
		case DOWN:
			if (chon + 1 < soItem_MenuCB) {
				Normal();
				gotoxy(COT, DONG + chon);	cout << td[chon];
				chon++;
				Highlight();
				gotoxy(COT, DONG + chon); 	cout << td[chon];
			}
			break;
		case ENTER:
			return chon + 1;
		}
	} while (TRUE);
}

mayBay ChonMB_Edit(LIST_MB lstMB, int& chonMB) {
	xoaKhungDS();
	mayBay tmp;
	Normal();
	khungGiaoDien();
	khungNhapThongTin(THEM_MB, "THEM MAY BAY", "So hieu may bay:", "Loai may bay:", "So day:", "So dong:");
	hienHuongDan(1);
	int page = MAX_PAGE - 1;
	int dem = 0;
	int chon = 0;
	int i;
	show_MB(lstMB);
	Highlight();
	show_1_MB(lstMB, chon, true, dem);
	char kytu;
	do
	{
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		if (kytu == 0)
			kytu = getch();
		switch (kytu)
		{
		case UP:
			if (chon > 0 && dem > 0) {
				Normal();
				show_1_MB(lstMB, chon, true, dem);

				chon--;
				dem--;
				Highlight();
				show_1_MB(lstMB, chon, true, dem);
			}
			break;
		case DOWN:
			if (chon + 1 < lstMB.n && dem + 1 < MAX_PAGE) {
				Normal();
				show_1_MB(lstMB, chon, true, dem);

				chon++;
				dem++;
				Highlight();
				show_1_MB(lstMB, chon, true, dem);
			}
			break;
		case LEFT:
			if (page > MAX_PAGE) {
				Normal();
				page -= MAX_PAGE * 2;
				chon = page;
				dem = 0;
				xoaThongTin(XOA_MB);
				for (page; page < lstMB.n; page++) {
					show_1_MB(lstMB, page, true, dem);
					if (dem == MAX_PAGE - 1) {
						break;
					}
					dem++;
				}
				dem = 0;
				Highlight();
				show_1_MB(lstMB, chon, true, dem);
			}
			break;
		case RIGHT:
			if (page < lstMB.n) {
				Normal();
				xoaThongTin(XOA_MB);
				page++;
				chon = page;
				dem = 0;
				for (page; page < lstMB.n; page++) {
					show_1_MB(lstMB, page, true, dem);
					if (dem == MAX_PAGE - 1) {
						break;
					}
					dem++;
				}
				page += MAX_PAGE - dem;
				dem = 0;
				Highlight();
				show_1_MB(lstMB, chon, true, dem);
			}
			break;
		case F2:
			chonMB = THEM_MB;
			tmp.soHieuMayBay[0] = '\0';
			return tmp;
		case DELETE:
		{
			int xacNhan = confirm("DONG Y", "HUY", false);
			if (xacNhan == YES) {
				chonMB = XOA_MB;
				return lstMB.MB[chon]->data;
			}
			else
				break;
		}
		case F3:
		{
			tmp.soHieuMayBay[0] =  '\0';
			int tontai = -1;
			do
			{
				strcpy(tmp.soHieuMayBay, gdTimMa(0, "TIM MAY BAY"));
				if (tmp.soHieuMayBay[0] == ESC)
				{
					return tmp;
				}
				tontai = search_MB(lstMB, tmp.soHieuMayBay);
				if (tontai == -1) {
					Red_Highlight();
					hienThongBao("Khong tim thay so hieu nay!");
					
				}
				else break;
			} while (true);
			chonMB = confirm("HIEU CHINH", "XOA", false);
			if (chonMB == XOA_MB) {
				int xacNhan = confirm("DONG Y", "HUY", false);
				if (xacNhan == YES) {
					chonMB = XOA_MB;
					return tmp;
				}
				else
					break;
			}
			else if (chonMB == CANCEL)
				break;
			Normal();
			return tmp;
		}
		case ESC:
		{
			Normal();
			tmp.soHieuMayBay[0] = '\0';
			chonMB = soItem_MenuMB;
			return tmp;
		}	
		case ENTER:  
		{
			Normal();
			chonMB = confirm("HIEU CHINH", "XOA", false);
			if (chonMB == NO) {
				int xacNhan = confirm("DONG Y", "HUY", false);
				if (xacNhan == YES) {
					chonMB = XOA_MB;
					return lstMB.MB[chon]->data;
				}
				else
					break;
			}
			else if (chonMB == CANCEL)
				break;
			return lstMB.MB[chon]->data;
		}
		}
	} while (true);
}

void chuyenMang(PTRChuyenBay lstCB, CHUYENBAY* cb[], int &n, LIST_MB lstMB, int trangThai) {
	PTRChuyenBay p = lstCB;
	if (trangThai == 0) {
		for (p; p != NULL; p = p->next) {
			cb[n] = new CHUYENBAY;
			strcpy(cb[n]->maChuyenBay, p->data.maChuyenBay);
			strcpy(cb[n]->soHieuMayBay, p->data.soHieuMayBay);
			strcpy(cb[n]->sanBayDen, p->data.sanBayDen);
			cb[n]->tgKhoiHanh.ngay = p->data.tgKhoiHanh.ngay;
			cb[n]->tgKhoiHanh.thang = p->data.tgKhoiHanh.thang;
			cb[n]->tgKhoiHanh.nam = p->data.tgKhoiHanh.nam;
			cb[n]->tgKhoiHanh.gio = p->data.tgKhoiHanh.gio;
			cb[n]->tgKhoiHanh.phut = p->data.tgKhoiHanh.phut;
			cb[n]->trangThai = p->data.trangThai;
			
			mayBay mb = getMB(lstMB, cb[n]->soHieuMayBay);
			int dsve = createDsVe(mb, cb[n]->dsVe);
			for (int k = 0; k < cb[n]->dsVe.n; k++) {
			//	hienThongBao(string(cb[n]->dsVe.nodeVe[k].data.CMND));
				if (stricmp(p->data.dsVe.Ve[k]->data.CMND, "") != 0) {
					strcpy(cb[n]->dsVe.Ve[k]->data.CMND, p->data.dsVe.Ve[k]->data.CMND);
					insertVe(cb[n]->dsVe, k, cb[n]->dsVe.Ve[k]->data.CMND);
				}
				
			}

			n++;
		}
	}
	else if (trangThai == CONVE) {
		for (p; p != NULL; p = p->next) {
			if (p->data.trangThai == CONVE) {
				cb[n] = new CHUYENBAY;
				strcpy(cb[n]->maChuyenBay, p->data.maChuyenBay);
				strcpy(cb[n]->soHieuMayBay, p->data.soHieuMayBay);
				strcpy(cb[n]->sanBayDen, p->data.sanBayDen);
				cb[n]->tgKhoiHanh.ngay = p->data.tgKhoiHanh.ngay;
				cb[n]->tgKhoiHanh.thang = p->data.tgKhoiHanh.thang;
				cb[n]->tgKhoiHanh.nam = p->data.tgKhoiHanh.nam;
				cb[n]->tgKhoiHanh.gio = p->data.tgKhoiHanh.gio;
				cb[n]->tgKhoiHanh.phut = p->data.tgKhoiHanh.phut;
				cb[n]->trangThai = p->data.trangThai;
				mayBay mb = getMB(lstMB, cb[n]->soHieuMayBay);
				int dsve = createDsVe(mb, cb[n]->dsVe);
				for (int k = 0; k < cb[n]->dsVe.n; k++) {
					//	hienThongBao(string(cb[n]->dsVe.nodeVe[k].data.CMND));
					if (stricmp(p->data.dsVe.Ve[k]->data.CMND, "") != 0) {
						strcpy(cb[n]->dsVe.Ve[k]->data.CMND, p->data.dsVe.Ve[k]->data.CMND);
						insertVe(cb[n]->dsVe, k, cb[n]->dsVe.Ve[k]->data.CMND);
					}

				}
				n++;
			}
		}
	}
}

PTRChuyenBay ChonCB_Edit(PTRChuyenBay lstCB, LIST_MB lstMB, int& chonCB) {
	
	Normal();
	khungGiaoDien();
	khungNhapThongTin(GDTHEM_CB, "THEM CHUYEN BAY", "Ma chuyen bay:", "So hieu may bay:", "San bay den:", "Ngay khoi hanh:", "Gio khoi hanh:");
	hienHuongDan(1);
	int chon = 0;
	int page = MAX_PAGE - 1;
	int dem = 0;
	showCB(lstCB);

	CHUYENBAY* tmpCB[300];
	int i = 0; // so phan tu cua mang tam
	chuyenMang(lstCB, tmpCB, i, lstMB, 0);
	
	PTRChuyenBay q = new NodeChuyenBay;
	Highlight();
	show_1_CB(tmpCB[chon], chon);
	char tmp[20];
	char kytu;
	do
	{
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		if (kytu == 0)
			kytu = getch();
		switch (kytu)
		{
		case UP:
			if (chon > 0 && dem > 0) {
				Normal();
				show_1_CB(tmpCB[chon], dem);

				chon--;
				dem--;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
			}
			break;
		case DOWN:
			if (chon + 1 < i && dem + 1 < MAX_PAGE) {
				Normal();
				show_1_CB(tmpCB[chon], dem);

				chon++;
				dem++;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
			}
			break;
		case LEFT:
			if (page > MAX_PAGE) {
				Normal();
				page -= MAX_PAGE * 2;
				chon = page;
				dem = 0;
				xoaThongTin(XOA_CB_L);
				for (page; page < i; page++) {
					show_1_CB(tmpCB[page], dem);
					if (dem == MAX_PAGE - 1) {
						break;
					}
					dem++;
				}
				dem = 0;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
			}
			break;
		case RIGHT:
			if (page < i) {
				Normal();
				xoaThongTin(XOA_CB_L);
				page++;
				chon = page;
				dem = 0;
				for (page; page < i; page++) {
					show_1_CB(tmpCB[page], dem);
					if (dem == MAX_PAGE - 1) {
						break;
					}
					dem++;
				}
				page += MAX_PAGE - dem;
				dem = 0;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
			}
			break;
		case F2:
			chonCB = THEM_CB;
			tmp[0] = '\0';
			strcpy(q->data.maChuyenBay, tmp);
			return q;
		case F3:
		{
			tmp[0] = '\0';
			do
			{
				strcpy(tmp, gdTimMa(0, "TIM CHUYEN BAY"));
				q = searchBin_CB(lstCB, tmp);
				if (q == NULL) {
					Red_Highlight();
					hienThongBao("Khong tim thay chuyen bay nay!");
				}
				else break;
			} while (true);
			chonCB = confirm("HIEU CHINH", "HUY CHUYEN", true);
			if (chonCB == CANCEL)
				break;
			Normal();
			return q;
		}
		case DELETE:
		{
			q = searchBin_CB(lstCB, tmpCB[chon]->maChuyenBay);
			if (q != NULL) {
				int chon = confirm("CO", "KHONG", false);
				if (chon == YES) {
					chonCB = XOA_CB;
					Normal();
					return q;
				}
				else
					break;
			}
		}
		case ESC:
		{
			Normal();
			chonCB = soItem_MenuCB;
			return NULL;
		}

		case ENTER:
			chonCB = confirm("HIEU CHINH", "HUY CHUYEN", true);
			if (chonCB == CANCEL) {
				Normal();
				break;
			}
				
			q = searchBin_CB(lstCB, tmpCB[chon]->maChuyenBay);
			Normal();
			return q;
		}
	} while (true);
}

PTRChuyenBay ChonCB_DatVe_HuyVe(PTRChuyenBay lstCB, int &chonCB, LIST_MB lstMB) {

	Normal();
	khungGiaoDien();
	khungNhapThongTin(GDTHEM_CB, "", "Ma chuyen bay:", "So hieu may bay:", "San bay den:", "Ngay khoi hanh:", "Gio khoi hanh:");
	hienHuongDan(DATVE);
	int chon = 0;
	int page = MAX_PAGE - 1;
	int dem = 0;
	
	showCB_DatVe(lstCB);
	CHUYENBAY* tmpCB[300];
	int i = 0; // so phan tu mang tam
	chuyenMang(lstCB, tmpCB, i, lstMB, CONVE);
	PTRChuyenBay q = new NodeChuyenBay;
	
	Highlight();
	show_1_CB_DatVe(tmpCB[chon], chon);
	char tmp[20];
	char kytu;
	do
	{
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		if (kytu == 0)
			kytu = getch();
		switch (kytu)
		{
		case UP:
			if (chon > 0 && dem > 0) {
				Normal();
				show_1_CB_DatVe(tmpCB[chon], dem);

				chon--;
				dem--;
				Highlight();
				show_1_CB_DatVe(tmpCB[chon], dem);
			}
			break;
		case DOWN:
			if (chon + 1 < i && dem + 1 < MAX_PAGE) {
				Normal();
				show_1_CB_DatVe(tmpCB[chon], dem);

				chon++;
				dem++;
				Highlight();
				show_1_CB_DatVe(tmpCB[chon], dem);
			}
			break;
		case LEFT:
			if (page > MAX_PAGE) {
				Normal();
				page -= MAX_PAGE * 2;
				chon = page;
				dem = 0;
				xoaThongTin(XOA_CB_L);
				for (page; page < i; page++) {
					show_1_CB(tmpCB[page], dem);
					if (dem == MAX_PAGE - 1) {
						break;
					}
					dem++;
				}
				dem = 0;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
			}
			break;
		case RIGHT:
			if (page < i) {
				Normal();
				xoaThongTin(XOA_CB_L);
				page++;
				chon = page;
				dem = 0;
				for (page; page < i; page++) {
					show_1_CB(tmpCB[page], dem);
					if (dem == MAX_PAGE - 1) {
						break;
					}
					dem++;
				}
				page += MAX_PAGE - dem;
				dem = 0;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
			}
			break;
		case F3:
		{
			tmp[0] = '\0';
			do
			{
				strcpy(tmp, gdTimMa(0, "TIM CHUYEN BAY"));
				q = searchBin_CB(lstCB, tmp);
				if (q == NULL) {
					Red_Highlight();
					hienThongBao("Khong tim thay chuyen bay nay!");
				}
				else break;
			} while (true);
			chonCB = confirm("DAT VE", "TRO VE", false);
			if (chonCB == CANCEL)
				break;
			Normal();
			return q;
		}
		case ESC:
		{
			Normal();
			chonCB = soItem_MenuCB;
			return NULL;
		}

		case ENTER:
			Normal();
			int luachon = confirm("DAT VE", "HUY VE", false);
			if (luachon == YES)
				chonCB = DATVE;
			else if (luachon == NO)
				chonCB = HUYVE;
			else if (luachon == CANCEL)
				break;
			q = searchBin_CB(lstCB, tmpCB[chon]->maChuyenBay);
			Normal();
			return q;
		}
	} while (true);
}

void xuatALL_HK_1_CB(CHUYENBAY* cb, TREEHanhKhach lstHK) {
	Normal();
	int page = 0;
	if (cb->dsVe.n < MAX_PAGE_SMALL)
		page = cb->dsVe.n;
	int max_HK = demSoVe(cb->dsVe);
	char kytu;
	bool max = false;
	xuatHK_1_CB(cb, lstHK, page);
	do
	{
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		if (kytu == 0)
			kytu = getch();
		switch (kytu)
		{
		case LEFT:
			if (page >= MAX_PAGE_SMALL) {

				page -= MAX_PAGE_SMALL;

				xoaThongTin(XOA_HK);
				xuatHK_1_CB(cb, lstHK, page);
			}
			break;
		case RIGHT:
			if (page < max_HK) {
				
				page += MAX_PAGE_SMALL;
				if (page >= max_HK) {
					page -= MAX_PAGE_SMALL;
					break;
				}

				xoaThongTin(XOA_HK);
				xuatHK_1_CB(cb, lstHK, page);
				
			}
			break;
		case ESC:
			return;
		}
		
	} while (true);
}

int checkHK_HuyVe(PTRChuyenBay p, HANHKHACH& hk) {
	khungNhapThongTin(GDTHEM_HK, "HUY VE", "CMND", "Ho", "Ten", "Phai");

	//HANHKHACH hk;
	do
	{
		strcpy(hk.CMND, CheckInputCMND(DONGNHAP1));
		if (hk.CMND[0] != ESC) {
			if (checkVeCung_CB(p, hk)) {
				return 1;
			}
			else return 0;
		}
		else
			return 0;
	} while (true);
}

int checkVeCung_CB(PTRChuyenBay p, HANHKHACH hk) {
	for (int i = 0; i < p->data.dsVe.n; i++) {
		if (stricmp(hk.CMND, p->data.dsVe.Ve[i]->data.CMND) == 0) {
			return 1;
		}
	}
	return 0;
}

PTRChuyenBay checkVeCungTime(PTRChuyenBay lstCB, PTRChuyenBay p, HANHKHACH hk) {
	PTRChuyenBay q = lstCB;
	bool check = false;
	for (q; q != NULL; q = q->next) {
		/*kiem tra co khac chuyen bay, bay cung ngay va co cach nhau
		5 tieng hay khong*/
		if (stricmp(p->data.maChuyenBay, q->data.maChuyenBay) != 0
			&& toTime(p->data.tgKhoiHanh) - toTime(q->data.tgKhoiHanh) == 0
			&& !checkKC_5Gio(p->data.tgKhoiHanh, q->data.tgKhoiHanh)) {
			if (!checkVeCung_CB(q, hk))
				return NULL;
			else return q;
		}
	}
	if (q == NULL)
		return NULL;	
}

PTRChuyenBay ChonCB_Xuat_DSHK(PTRChuyenBay lstCB, int& chonCB, LIST_MB lstMB, TREEHanhKhach lstHK) {

	Normal();
	khungGiaoDien();
	khungXuatDS(XUAT_CB, DONGDS_D - DONGDS_U - 24, COTDS_R - COTDS_L, 5, 25, 45, 80, 100);
	khungXuatDS(XUAT_HK, DONGDS_D - DONGDS_U - 24, COTDS_R - COTDS_L, 5, 25, 45, 93, 0, COTDS_L, DONGDS_U + 24);
	khungNhapThongTin(GDTHEM_CB, "", "Ma chuyen bay:", "So hieu may bay:", "San bay den:", "Ngay khoi hanh:", "Gio khoi hanh:");
	hienHuongDan(DATVE);
	int chon = 0;
	
	int pageCB = 0;
	int pageHK = 0;
	int dem = 0;
	CHUYENBAY* tmpCB[300];
	int i = 0; // so phan tu cua mang tmpCB
	chuyenMang(lstCB, tmpCB, i, lstMB, 0);
	PTRChuyenBay q = new NodeChuyenBay;
	for (pageCB; pageCB < i; pageCB++) {
		show_1_CB(tmpCB[pageCB], pageCB);
		
		if (dem == MAX_PAGE_SMALL - 1) {
			break;
		}
		dem++;
	}
	dem = 0;

	xuatHK_1_CB(tmpCB[chon], lstHK, 0);
	Highlight();
	show_1_CB(tmpCB[chon], chon);
	
	dem = 0;
	char tmp[20];
	char kytu;
	do
	{
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		if (kytu == 0)
			kytu = getch();
		switch (kytu)
		{
		case UP:
			if (chon > 0 && dem > 0) {
				Normal();
				show_1_CB(tmpCB[chon], dem);
				xoaThongTin(XOA_HK);
				chon--;
				dem--;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
				xuatHK_1_CB(tmpCB[chon], lstHK, 0);
			}
			break;
		case DOWN:
			if (chon + 1 < i && dem + 1 < MAX_PAGE_SMALL) {
				Normal();
				show_1_CB(tmpCB[chon], dem);
				xoaThongTin(XOA_HK);
				chon++;
				dem++;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
				xuatHK_1_CB(tmpCB[chon], lstHK, 0);
			}
			break;
		case LEFT:
			
			if (pageCB > MAX_PAGE_SMALL) {
				Normal();
				xoaThongTin(XOA_CB);
				xoaThongTin(XOA_HK);
				pageCB -= MAX_PAGE_SMALL*2;
				chon = pageCB;
				dem = 0;
				
				for (pageCB; pageCB < i; pageCB++) {
					show_1_CB(tmpCB[pageCB], dem);
					
					if (dem == MAX_PAGE_SMALL - 1) {
						break;
					}
					dem++;
				}
				dem = 0;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
				xuatHK_1_CB(tmpCB[chon], lstHK, 0);
			}
			break;
		case RIGHT:
			if (pageCB < i) {
				Normal();
				xoaThongTin(XOA_CB);
				xoaThongTin(XOA_HK);
				pageCB ++;
				chon = pageCB;
				dem = 0;
				
				for (pageCB; pageCB < i; pageCB++) {
					show_1_CB(tmpCB[pageCB], dem);
					
					if (dem == MAX_PAGE_SMALL - 1) {
						
						break;
					}
					dem++;
				}
				pageCB += MAX_PAGE_SMALL - dem;
				dem = 0;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
				xuatHK_1_CB(tmpCB[chon], lstHK, 0);
			}
			break;
		case F3:
		{
			tmp[0] = '\0';
			do
			{
				strcpy(tmp, gdTimMa(0, "TIM CHUYEN BAY"));
				q = searchBin_CB(lstCB, tmp);
				if (q == NULL) {
					Red_Highlight();
					hienThongBao("Khong tim thay chuyen bay nay!");
				}	
				else break;
			} while (true);
			xoaThongTin(XOA_HK);
			xuatALL_HK_1_CB(&q->data, lstHK);
			Normal();
			return q;
		}
		case ESC:
		{
			Normal();
			tmp[0] = '\0';
			strcpy(q->data.maChuyenBay, tmp);
			chonCB = soItem_MenuCB;
			return q;
		}

		case ENTER:
			Normal();
			xuatALL_HK_1_CB(tmpCB[chon], lstHK);
			break;
		}
	} while (true);
}

PTRChuyenBay ChonCB_Loc_NoiDen(PTRChuyenBay lstCB, int& chonCB, LIST_MB lstMB) {
	Normal();
	system("cls");

	khungGiaoDien();
	khungNhapThongTin(LOC_CB, "NHAP THONG TIN CAN TIM", "Ngay khoi hanh:", "Noi den:");
	hienHuongDan(DATVE);
	int dem = 0;
	Nhap:
		THOI_GIAN tg = CheckInputDate(tg, DONGNHAP1);
		if (tg.ngay == -1 || tg.thang == -1 || tg.nam == -1) {
			chonCB = ENTER;
			return NULL;
		}
		if (rangBuocThoiGian(tg, LOC_CB) == 1)
		{
			goto Nhap;
		}
		char *noiDen = new char[50];
		strcpy(noiDen, CheckInputStr(false, DONGNHAP2));
		if (noiDen[0] == ESC) {
			chonCB = ENTER;
			return NULL;
		}
	
	PTRChuyenBay p; // dang sach tam luu cac chuyen bay co noi den X
	initCB(p);
	for (PTRChuyenBay q = lstCB; q != NULL; q = q->next) {
		
		if (q->data.tgKhoiHanh.ngay == tg.ngay && q->data.tgKhoiHanh.thang == tg.thang
			&& q->data.tgKhoiHanh.nam == tg.nam && stricmp(q->data.sanBayDen, noiDen) == 0 && q->data.trangThai == CONVE) {
			insert_OrderNodeCB(p, q->data);
		}
	}
	
	if (p == NULL)
	{
		hienThongBao("Chuyen bay nay da hoan tat hoac khong co trong danh sach!");
		chonCB = soItem_MenuCB;
		return p;
	}
	
	CHUYENBAY* tmpCB[300];
	int i = 0; // so phan tu cua mang tmpCB
	chuyenMang(p, tmpCB, i, lstMB, 0);
	int pageCB = 0;
	for (pageCB; pageCB < i; pageCB++) {
		showCB_ConVe(tmpCB[pageCB], pageCB);

		if (dem == MAX_PAGE - 1) {
			break;
		}
		dem++;
	}
	dem = 0;
	int chon = 0;
	char kytu;
	char tmp[20];
	do
	{
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		if (kytu == 0)
			kytu = getch();
		switch (kytu)
		{
		case LEFT:
			if (pageCB > MAX_PAGE) {
				xoaThongTin(XOA_CB_L);
				pageCB -= MAX_PAGE * 2;
				dem = 0;
				for (pageCB; pageCB < i; pageCB++) {
					showCB_ConVe(tmpCB[pageCB], dem);

					if (dem == MAX_PAGE - 1) {
						break;
					}
					dem++;
				}
				dem = 0;
			}
			break;
		case RIGHT:
			if (pageCB < i) {
				xoaThongTin(XOA_CB_L);
				pageCB++;
				dem = 0;
				for (pageCB; pageCB < i; pageCB++) {
					showCB_ConVe(tmpCB[pageCB], dem);

					if (dem == MAX_PAGE - 1) {

						break;
					}
					dem++;
				}
				pageCB += MAX_PAGE - dem;
				dem = 0;
			}
			break;
		case ESC:
		{
			Normal();
			chonCB = soItem_MenuCB;
			return NULL;
		}
			
		case ENTER:
			Normal();
			goto Nhap;
			chonCB = 1;
			break;
		}
	} while (true);
	
}

PTRChuyenBay ChonCB_XemVeTrong(PTRChuyenBay lstCB, LIST_MB lstMB, int &chonCB) {

	Normal();
	khungGiaoDien();
	khungNhapThongTin(GDTHEM_CB, "", "Ma chuyen bay:", "So hieu may bay:", "San bay den:", "Ngay khoi hanh:", "Gio khoi hanh:");
	hienHuongDan(DATVE);
	int page = MAX_PAGE - 1;
	int dem = 0;
	int chon = 0;
	

	showCB_DatVe(lstCB);
	CHUYENBAY* tmpCB[300];
	int i = 0; // so phan tu mang tam
	chuyenMang(lstCB, tmpCB, i, lstMB, CONVE);
	PTRChuyenBay q = new NodeChuyenBay;

	Highlight();
	show_1_CB_DatVe(tmpCB[chon], chon);
	char tmp[20];
	char kytu;

	do
	{
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		if (kytu == 0)
			kytu = getch();
		switch (kytu)
		{
		case UP:
			if (chon > 0 && dem > 0) {
				Normal();
				show_1_CB_DatVe(tmpCB[chon], dem);

				chon--;
				dem--;
				Highlight();
				show_1_CB_DatVe(tmpCB[chon], dem);
			}
			break;
		case DOWN:
			if (chon + 1 < i && dem + 1 < MAX_PAGE) {
				Normal();
				show_1_CB_DatVe(tmpCB[chon], dem);

				chon++;
				dem++;
				Highlight();
				show_1_CB_DatVe(tmpCB[chon], dem);
			}
			break;
		case LEFT:
			if (page > MAX_PAGE) {
				page -= MAX_PAGE * 2;
				chon = page;
				dem = 0;
				Normal();
				xoaThongTin(XOA_CB_L);
				for (page; page < i; page++) {
					show_1_CB(tmpCB[page], dem);
					if (dem == MAX_PAGE - 1) {
						break;
					}
					dem++;
				}
				dem = 0;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
			}
			break;
		case RIGHT:
			if (page < i) {
				Normal();
				xoaThongTin(XOA_CB_L);
				page++;
				chon = page;
				dem = 0;
				for (page; page < i; page++) {
					show_1_CB(tmpCB[page], dem);
					if (dem == MAX_PAGE - 1) {
						break;
					}
					dem++;
				}
				page += MAX_PAGE - dem;
				dem = 0;
				Highlight();
				show_1_CB(tmpCB[chon], dem);
			}
			break;
		case F3:
		{
			tmp[0] = '\0';
			do
			{
				strcpy(tmp, gdTimMa(0, "TIM CHUYEN BAY"));
				q = searchBin_CB(lstCB, tmp);
				if (q == NULL) {
					Red_Highlight();
					hienThongBao("Khong tim thay chuyen bay nay!");
				}
				else break;
			} while (true);
			
			Normal();
			return q;
		}
		case ESC:
		{
			Normal();
			strcpy(q->data.maChuyenBay, {""});
			chonCB = soItem_MenuCB;
			return q;
		}
		case ENTER:
			Normal();
			q = searchBin_CB(lstCB, tmpCB[chon]->maChuyenBay);
			chonCB = 1;
			return q;
		}
	} while (true);
}

void quickSortTK(int* soLuot, NODEMAYBAY tempMB, int q, int r) {
	int i, j;
	i = q;
	j = r;
	int x = soLuot[(q + r) / 2];
	int tam;
	mayBay temp;

	do
	{
		while (soLuot[i] > x)
		{
			i++;
		}
		while (soLuot[j] < x)
		{
			j--;
		}
		if (i <= j)
		{
			tam = soLuot[i];
			soLuot[i] = soLuot[j];
			soLuot[j] = tam;

			temp = tempMB[i].data;
			tempMB[i].data = tempMB[j].data;
			tempMB[j].data = temp;

			i++;
			j--;
		}
	} while (i <= j);

	if (q < j)
	{
		quickSortTK(soLuot, tempMB, q, j);
	}

	if (i < r)
	{
		quickSortTK(soLuot, tempMB, i, r);
	}
}

void show_1_Ve(LIST_VE lstVe, int cot, int dong, int chon, int kc) {
	//int kc = 3;
	gotoxy(COTDS_L + cot + kc, DONGDS_U + dong);
	cout << lstVe.Ve[chon]->data.soVe;
}

int chonVe(PTRChuyenBay& lstCB) {
	int chon = 0;
	int kc = 3;
	int n = 0;
	for (int i = 0; i < lstCB->data.dsVe.soDay; i++) {
		for (int j = 0; j < lstCB->data.dsVe.soDong; j++) {
			if (stricmp(lstCB->data.dsVe.Ve[n]->data.CMND, "") != 0)
				Red_Highlight();
			show_1_Ve(lstCB->data.dsVe, i, j, n, kc);
			Normal();
			n++;
		}
		kc += 3;
	}
	int cot = 0;
	int dong = 0;
	kc = 3;
	if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") != 0)
		Red_Highlight();
	Highlight();
	show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
	char kytu;
	do
	{
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		if (kytu == 0)
			kytu = getch();
		switch (kytu)
		{
		case UP:
		{
			if (dong > 0) {
				Normal();
				if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") != 0)
					Red_Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
				chon--;
				dong--;
				
				Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
			}
			break;
		}
		case DOWN:
		{
			if (dong + 1 < lstCB->data.dsVe.soDong) {
				Normal();
				if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") != 0)
					Red_Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
				chon++;
				dong++;
				Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
			}
			break;
		}
		case LEFT:
		{
			if (cot > 0) {
				Normal();
				if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") != 0)
					Red_Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
				chon -= lstCB->data.dsVe.soDong;
				cot--;
				kc -= 3;
				Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
			}
			break;
		}
		case RIGHT:
		{
			if (cot + 1 < lstCB->data.dsVe.soDay) {
				Normal();
				if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") != 0)
					Red_Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
				chon += lstCB->data.dsVe.soDong;
				cot++;
				kc += 3;
				Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
			}
			break;
		}
		case ESC:
			Normal();
			xoaKhungDS();
			return -1;
		case ENTER:
			Normal();
			if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") != 0) {
				Red_Highlight();
				hienThongBao("Ve nay da co nguoi dat!");
				break;
			}
			xoaKhungDS();
			return chon;
		}
	} while (true);
	return -1;
}

int chonVe_HUY(PTRChuyenBay& lstCB, HANHKHACH hk) {
	int chon = 0;
	int kc = 3;
	int n = 0;
	for (int i = 0; i < lstCB->data.dsVe.soDay; i++) {
		for (int j = 0; j < lstCB->data.dsVe.soDong; j++) {
			if (stricmp(lstCB->data.dsVe.Ve[n]->data.CMND, "") != 0)
				Red_Highlight();
			show_1_Ve(lstCB->data.dsVe, i, j, n, kc);
			Normal();
			n++;
		}
		kc += 3;
	}
	int cot = 0;
	int dong = 0;
	kc = 3;
	if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") != 0)
		Red_Highlight();
	Highlight();
	show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
	char kytu;
	do
	{
		kytu = getch();
		if (kytu == -32)
			kytu = getch();
		if (kytu == 0)
			kytu = getch();
		switch (kytu)
		{
		case UP:
		{
			if (dong > 0) {
				Normal();
				if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") != 0)
					Red_Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
				chon--;
				dong--;

				Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
			}
			break;
		}
		case DOWN:
		{
			if (dong + 1 < lstCB->data.dsVe.soDong) {
				Normal();
				if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") != 0)
					Red_Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
				chon++;
				dong++;
				Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
			}
			break;
		}
		case LEFT:
		{
			if (cot > 0) {
				Normal();
				if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") != 0)
					Red_Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
				chon -= lstCB->data.dsVe.soDong;
				cot--;
				kc -= 3;
				Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
			}
			break;
		}
		case RIGHT:
		{
			if (cot + 1 < lstCB->data.dsVe.soDay) {
				Normal();
				if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") != 0)
					Red_Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
				chon += lstCB->data.dsVe.soDong;
				cot++;
				kc += 3;
				Highlight();
				show_1_Ve(lstCB->data.dsVe, cot, dong, chon, kc);
			}
			break;
		}
		case ESC:
		{
			Normal();
			xoaKhungDS();
			return -1;
		}
		case ENTER:
			Normal();
			if (stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, "") == 0
				|| stricmp(lstCB->data.dsVe.Ve[chon]->data.CMND, hk.CMND) != 0) {
				Red_Highlight();
				hienThongBao("Chua dat ve nay, khong the huy!");
				break;
			}
			int xacNhan = confirm("DONG Y", "TRO VE", false);
			if (xacNhan == 2 || xacNhan == 0)
				break;
			xoaKhungDS();
			return chon;
		}
	} while (true);
	return -1;
}

void show_VeTrong(PTRChuyenBay p) {
	int chon = 0;
	int kc = 3;
	int n = 0;
	for (int i = 0; i < p->data.dsVe.soDay; i++) {
		for (int j = 0; j < p->data.dsVe.soDong; j++) {
			if (stricmp(p->data.dsVe.Ve[n]->data.CMND, "") != 0)
				Red_Highlight();
			show_1_Ve(p->data.dsVe, i, j, n, kc);
			Normal();
			n++;
		}
		kc += 3;
	}
	char kytu;
	do
	{
		kytu = getch();
		if (kytu == ESC) {
			return;
		}
	} while (true);
	
}

void dsHK_1_CB(PTRChuyenBay lstCB, TREEHanhKhach lstHK, LIST_MB lstMB) {
	Normal();
	system("cls");
	
	int chon;
	int exit = 1;
	

	while (exit)
	{
		chon = 0;
		PTRChuyenBay p = ChonCB_Xuat_DSHK(lstCB, chon, lstMB, lstHK);
		
		switch (chon)
		{
		case 1:
			break;
		case soItem_MenuCB:
			exit = 0;
			break;
		}
	}
}

void QLMB(LIST_MB &lstMB, PTRChuyenBay lstCB) {
	int chonMB;
	int exit1 = 1;
	Normal();
	system("cls");
	mayBay tmp;
	while (exit1) {
		show_MB(lstMB);
		chonMB = 0;
		tmp = ChonMB_Edit(lstMB, chonMB);
		switch (chonMB)
		{
		case THEM_MB:
		{
			mayBay mb = createMB(lstMB);
			if (mb.soHieuMayBay[0] == ESC) {
				break;
			}
			int themMB = insert_MB(lstMB, mb);
			if (themMB == 1) {
				Green_Highlight();
				hienThongBao("Them thanh cong!");
				int save = saveMB(lstMB);
			}
			else {
				Red_Highlight();
				hienThongBao("Them that bai!");
			}
			Normal();
			system("cls");
			break;

		}
		case HIEUCHINH_MB:
		{
			int tontai = -1;
			tontai = search_MB(lstMB, tmp.soHieuMayBay);

			int sua = hieuChinh_MB(lstMB, tontai);
			if (sua == 1) {
				Green_Highlight();
				hienThongBao("Hieu chinh thanh cong!");
				int save = saveMB(lstMB);
			}
			else {
				Red_Highlight();
				hienThongBao("Da huy!");
			}
			Normal();
			system("cls");
			break;

		}
		case XOA_MB:
		{
			int tontai = -1;
			tontai = search_MB(lstMB, tmp.soHieuMayBay);
			int xoa = delete_MB(lstMB, tontai, lstCB);
			if (xoa == 1) {
				Green_Highlight();
				hienThongBao("Xoa thanh cong!");
				int save = saveMB(lstMB);
			}
			else {
				Red_Highlight();
				hienThongBao("May bay da lap chuyen bay khong the xoa!");
			}
			Normal();
			system("cls");
			break;

		}
		case soItem_MenuMB:
		{
			exit1 = 0;
			break;
		}
		}
	}
}

void QLCB(PTRChuyenBay& lstCB, LIST_MB& lstMB) {
	int chonCB;
	int exit2 = 1;
	Normal();
	system("cls");
	PTRChuyenBay p = lstCB;
	while (exit2)
	{
		chonCB = THEM_CB;
		if(!empty_CB(lstCB))
			p = ChonCB_Edit(lstCB, lstMB, chonCB);
		switch (chonCB)
		{
		case THEM_CB:
		{
			CHUYENBAY cb;
			cb = createCB(lstCB, lstMB);
			if (cb.maChuyenBay[0] != ESC) {
				insert_OrderNodeCB(lstCB, cb);
				hienThongBao("Them thanh cong!");
				int save = saveCB(lstCB);
			}
			else {
				Green_Highlight();
				hienThongBao("Da huy!");
			}
			Normal();
			system("cls");

			break;
		}
		case HIEUCHINH_CB:
		{
			// khong hieu chinh chuyen bay da huy hay hoan tat
			if (checkStatus_CB(p->data)) {
				Normal();
				system("cls");
				break;
			}
			int fix = hieuChinh_CB(lstCB, p, lstMB);
			
			if (fix == 1)
			{
				Green_Highlight();
				hienThongBao("Hieu chinh thanh cong!");
				int save = saveCB(lstCB);
			}
			else
			{
				Green_Highlight();
				hienThongBao("Da huy!");
			}
			Normal();
			system("cls");
			break;
		}
		case XOA_CB:
		{
			// khong xoa chuyen bay da huy hay hoan tat
			if (checkStatus_CB(p->data)) {
				Normal();
				system("cls");
				break;
			}
			/*Chuy?n tr?ng thái v? h?y chuy?n khi có ít nh?t 1 vé
			du?c dang kí và không xóa chuy?n bay kh?i danh sách.*/ 
			if (demSoVe(p->data.dsVe) != 0) {
				int huy = huy_CB(lstCB, p);
				if (huy) {
					int save = saveCB(lstCB);
					Green_Highlight();
					hienThongBao("Da huy chuyen bay!");
				}
				Normal();
				system("cls");
				break;
			}
			int xoa = xoa_CB(lstCB, p->data.maChuyenBay);
			if (xoa == 1) {
				Green_Highlight();
				hienThongBao("Xoa thanh cong!");
				int save = saveCB(lstCB);
			}
			else {
				Red_Highlight();
				hienThongBao("Xoa that bai!");
			}	
			Normal();
			system("cls");
			break;
		}
		case HUY_CB:
		{
			int xacNhan = confirm("CO", "KHONG", false);
			if (xacNhan == YES)
			{
				int huy = huy_CB(lstCB, p);
				if (huy) {
					int save = saveCB(lstCB);
					Green_Highlight();
					hienThongBao("Huy chuyen thanh cong!");
				}
				else {
					Red_Highlight();
					hienThongBao("Khong the huy chuyen bay nay hoac da bi huy truoc do!");
				}
			}
			else
			{
				Red_Highlight();
				hienThongBao("Khong thuc hien thao tac huy chuyen!");
			}
			Normal();
			system("cls");
			break;
		}
		case soItem_MenuCB:
		{
			exit2 = 0;
			break;
		}
		}
	}
}

void DatHuyVe(PTRChuyenBay& lstCB, LIST_MB lstMB, TREEHanhKhach& lstHK) {
	int chon;
	int exit = 1;
	int vitri;
	Normal();
	system("cls");
	
	while (exit)
	{
		chon = 0;
		PTRChuyenBay p = ChonCB_DatVe_HuyVe(lstCB, chon, lstMB);
		
		switch (chon)
		{
		case DATVE:
		{
			xoaKhungDS();
			vitri = chonVe(p);
			if (vitri == -1)
				break;
			HANHKHACH hk = create_HK(lstHK, lstCB);
			// sau khi sua thong tin hanh khach thi phai cap nhat lai vao file
			
			if (hk.CMND[0] == ESC) {
				Red_Highlight();
				hienThongBao("Da huy dat ve!");
				Normal();
				break;
			}

			// truong hop dat ve tren cung 1 chuyen bay
			if (checkVeCung_CB(p, hk)) {
				Red_Highlight();
				hienThongBao("Quy khach da dat ve chuyen bay nay roi!");
				break;
			}

			// truong hop dat ve cung thoi diem tren 2 chuyen khac nhau
			PTRChuyenBay tmp = checkVeCungTime(lstCB, p, hk);
			if (tmp != NULL) {
				Red_Highlight();
				hienThongBao("Quy khach da dat ve tren chuyen bay: ", string(tmp->data.maChuyenBay), string(tmp->data.sanBayDen), "Den noi:");
				
				break;
			}

			// them ve vao ds ve
			insertNode_HK(lstHK, hk);
			insertVe(p->data.dsVe, vitri, hk.CMND);
			if (demSoVe(p->data.dsVe) == p->data.dsVe.n) {
				p->data.trangThai = HETVE;
			}
			Green_Highlight();
			hienThongBao("Dat ve thanh cong!");
			int savehk = saveHK(lstHK);
			int savecb = saveCB(lstCB);
			break;
		}
		case HUYVE:
		{
			xoaKhungDS();
			HANHKHACH hk;
			if (checkHK_HuyVe(p, hk)) {
				vitri = chonVe_HUY(p, hk);
				if (vitri == -1)
					break;
				int cancle = cancelVe(p->data.dsVe, vitri);
				if (cancle == 1) {
					if (demSoVe(p->data.dsVe) == p->data.dsVe.n) {
						p->data.trangThai = HETVE;
					}
					Green_Highlight();
					hienThongBao("Huy ve thanh cong!");
					int save = saveCB(lstCB);
				}
				
			}
			else {
				Red_Highlight();
				hienThongBao("Quy khach chua dat ve chuyen bay nay!");
			}
			break;
		}
		case soItem_MenuCB:
			exit = 0;
			break;
		}
	}
}

void locCB_CoNoiDen(PTRChuyenBay lstCB, LIST_MB lstMB) {
	Normal();
	system("cls");

	int chon;
	int exit = 1;
	while (exit)
	{
		chon = 0;
		PTRChuyenBay p = ChonCB_Loc_NoiDen(lstCB, chon, lstMB);
		switch (chon)
		{
		case ENTER: {
			exit = 0;
			break;
		}
			
		case soItem_MenuCB:
			exit = 0;
			break;
		}
	}
}

void dsVeTrong_1_CB(PTRChuyenBay lstCB, LIST_MB lstMB) {
	Normal();
	system("cls");

	int chon;
	int exit = 1;
	
	while (exit)
	{
		chon = 0;
		PTRChuyenBay p = ChonCB_XemVeTrong(lstCB, lstMB, chon);
		switch (chon)
		{
		case 1:
		{
			xoaKhungDS();
			show_VeTrong(p);
			xoaKhungDS();
			break;
		}
		case soItem_MenuCB:
			exit = 0;
			break;
		}
	}
}

void thongKeCB(PTRChuyenBay lstCB, LIST_MB lstMB) {
	/*int* soLuot = new int[lstMB.n]; // mang luu so luot thuc hien
	NODEMAYBAY tempMB = new NodeMayBay[lstMB.n]; // mang luu thong tin cua may bay
	int dem;
	for (int i = 0; i < lstMB.n; i++)
	{
		dem = 0;
		for (PTRChuyenBay p = lstCB; p != NULL; p = p->next)
		{
			if (stricmp(p->data.soHieuMayBay, lstMB.MB[i]->data.soHieuMayBay) == 0)
			{
				dem++;//so luong thuc hien cua may bay
			}
		}
		soLuot[i] = dem;
		tempMB[i].data = lstMB.MB[i]->data;
	}
	quickSortTK(soLuot, tempMB, 0, lstMB.n - 1);
	Normal();
	xoaKhungDS();
	khungXuatDS(THONG_KE, DONGDS_D - DONGDS_U, COTDS_R - COTDS_L, 5, 25, 70);

	for (int i = 0; i < lstMB.n; i++) {
		//5, 25, 70, 93
		gotoxy(COTDS_L + 1, DONGDS_U + 3 + i);
		cout << i + 1;
		gotoxy(COTDS_L + 6, DONGDS_U + 3 + i);
		cout << tempMB[i].data.soHieuMayBay;
		gotoxy(COTDS_L + 26, DONGDS_U + 3 + i);
		cout << tempMB[i].data.loaiMayBay;
		gotoxy(COTDS_L + 71, DONGDS_U + 3 + i);
		cout << soLuot[i];
	}
	char key;
	do
	{
		key = getch();
		if (key == ESC)
			return;
	} while (true);*/
	
	thongKe *thucHien = new thongKe[lstMB.n];
	int k = 0;
	for (int i = 0; i < lstMB.n; i++)
	{
		for (PTRChuyenBay p = lstCB; p != NULL; p = p->next)
		{
			if (stricmp(lstMB.MB[i]->data.soHieuMayBay, p->data.soHieuMayBay) == 0 && p->data.trangThai == HOANTAT)
			{
				thucHien[k].soLuot++;
			}
		}
		thucHien[k].index = i;
		k++;
	}
	
	quickSortTK1(thucHien, 0, lstMB.n - 1);
	
	Normal();
	xoaKhungDS();
	khungXuatDS(THONG_KE, DONGDS_D - DONGDS_U, COTDS_R - COTDS_L, 5, 25, 70);
	
	int j = 0;
	for (int i = 0; i < lstMB.n; i++) {
		//5, 25, 70, 93
		gotoxy(COTDS_L + 1, DONGDS_U + 3 + i);
		cout << i + 1;
		gotoxy(COTDS_L + 6, DONGDS_U + 3 + i);
		cout << lstMB.MB[thucHien[j].index]->data.soHieuMayBay;
		gotoxy(COTDS_L + 26, DONGDS_U + 3 + i);
		cout << lstMB.MB[thucHien[j].index]->data.loaiMayBay;
		gotoxy(COTDS_L + 71, DONGDS_U + 3 + i);
		cout << thucHien[j].soLuot;
		j++;
	}
	char key;
	do
	{
		key = getch();
		if (key == ESC)
			return;
	} while (true);
}

void quickSortTK1(thongKe *thucHien, int q, int r)
{
	int i, j;
	i = q;
	j = r;
	int x = thucHien[(q + r) / 2].soLuot;
	thongKe temp;

	do
	{
		while (thucHien[i].soLuot > x)
		{
			i++;
		}
		while (thucHien[j].soLuot < x)
		{
			j--;
		}
		if (i <= j)
		{
			temp = thucHien[i];
			thucHien[i] = thucHien[j];
			thucHien[j] = temp;

			i++;
			j--;
		}
	} while (i <= j);

	if (q < j)
	{
		quickSortTK1(thucHien, q, j);
	}

	if (i < r)
	{
		quickSortTK1(thucHien, i, r);
	}
}

int confirm(string chose1, string chose2, bool huyCB) {
	char key;
	int chon = 3;
	
	Highlight();
	gotoxy(COT + 10, DONGNHAP7);
	cout << chose1;
	Normal();
	gotoxy(COT + DAIKHUNGNHO + 28, DONGNHAP7);
	cout << chose2;
	do
	{
		key = getch();
		if (key == -32)
			key = getch();
		switch (key)
		{
		case LEFT:
			Normal();
			gotoxy(COT + DAIKHUNGNHO + 28, DONGNHAP7);
			cout << chose2;
			Highlight();
			gotoxy(COT + 10, DONGNHAP7);
			cout << chose1;
			chon = YES;
			break;
		case RIGHT:
			Normal();
			gotoxy(COT + 10, DONGNHAP7);
			cout << chose1;
			Highlight();
			gotoxy(COT + DAIKHUNGNHO + 28, DONGNHAP7);
			cout << chose2;
			if (huyCB == true)
				chon = HUY_CB;
			else 
				chon = NO;
			break;
		case ENTER:
			Normal();
			gotoxy(COT + 10, DONGNHAP7);
			cout << "                                       ";
			return chon;
		case ESC:
			Normal();
			gotoxy(COT + 10, DONGNHAP7);
			cout << "                                       ";
			return CANCEL;
		}
		
	} while (true);
}
