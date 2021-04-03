#include "ThuVien.h"

char tdChinh[soItem_MenuChinh][100] = { "1. Quan ly may bay                                     ",
										 "2. Quan ly chuyen bay                                 ",
										 "3. Dat ve/Huy ve                                      ",
										 "4. Danh sach hanh khach thuoc 1 chuyen bay            " ,
										 "5. Danh sach cac chuyen bay khoi hanh trong dd/mm/yyyy",
										 "6. Danh sach ve con trong cua chuyen bay X            ",
										 "7. Thong ke so luot thuc hien chuyen bay"
};

int main() {
	LIST_MB lstMB;
	PTRChuyenBay lstCB;
	TREEHanhKhach lstHK;
	init_HK(lstHK);
	initCB(lstCB);

	int loadmb = loadMB(lstMB);
	int loadcb = loadCB(lstCB, lstMB);
	int loadhk = loadHK(lstHK);
	int chon;
	int exit = 1;
	while (exit) {
		Normal();
		system("cls");
		chon = menuDong_Prim(tdChinh);
		switch (chon) {
		case 1:
		{
			QLMB(lstMB, lstCB);
			break;
		}
		case 2:
		{
			int check = checkHoanTat_CB(lstCB);
			QLCB(lstCB, lstMB);
			int save = saveCB(lstCB);
			break;
		}
		case 3:
		{
			DatHuyVe(lstCB, lstMB, lstHK);
			break;
		}
		case 4:
		{
			
			dsHK_1_CB(lstCB, lstHK, lstMB);
			break;
		}
		case 5:
		{
			locCB_CoNoiDen(lstCB, lstMB);
			break;
		}
		case 6:
		{
			dsVeTrong_1_CB(lstCB, lstMB);
			break;
		}
		case 7:
		{
			thongKeCB(lstCB, lstMB);
			break;
			
		}
		case 0:
			return 0;
		}
	}
	return 0;
}
