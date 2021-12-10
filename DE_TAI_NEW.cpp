// Khai bao thu vien trong do fstream dung de doc ghi file, iosmanip dung de dinh dang nhap xuat
#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

using namespace std;
// Khai bao cac kieu du lieu tu dinh nghia
struct info
{
	string HTHV;
	string MMH1;
	int DiemMH1;
	string MMH2;
	int DiemMH2;
};
struct SV
{
	string key;
	info data;
	SV *left, *right, *parent;
};
struct node {
    string ID;
    info dulieu;
};
// Nhom ham khoi tao du lieu
info INPUT_DATA()
{
	info temp;
	cout << "Nhap ho ten hoc vien:";
	getline(cin, temp.HTHV);
	cout << "Nhap ma mon hoc:";
	getline(cin, temp.MMH1);
	cout << "Nhap diem mon hoc 1:";
	cin >> temp.DiemMH1;
	cin.ignore();
	cout << "Nhap ma mon hoc 2:";
	getline(cin, temp.MMH2);
	cout << "Nhap diem mon hoc thu 2:";
	cin >> temp.DiemMH2;
	cin.ignore();
	return temp;
}
void INIT_BST(SV *&Root)
{
	Root = NULL;
}
void SV_INSERT(SV *&T, string v, info thongtin)
{
	SV *z, *y, *x;
	z = new SV;
	z->key = v;
	z->data = thongtin;
	z->left = NULL;
	z->right = NULL;
	y = NULL;
	x = T;
	while (x != NULL)
	{
		y = x;
		if (z->key.compare(x->key) < 0)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == NULL)
		T = z;
	else if (z->key.compare(y->key) < 0)
		y->left = z;
	else
		y->right = z;
}
void CLASS_INSERT(SV *&tree)
{
	int n;
	string key;
	cout << "Vui long nhap so luong hoc vien:";
	cin >> n;
	cin.ignore();
	cout << "Nhap vao MSHV - HTHV - MMH1 - DiemM1 - MHH2 - DiemM2\n";
	for (int i = 0; i < n; i++)
	{
		cout << "Nhap vao thong tin hoc vien thu " << i << endl;
		getline(cin, key);
		info thongtin = INPUT_DATA();
		SV_INSERT(tree, key, thongtin);
	}
	cout << "Them thanh cong " << n << " hoc vien !\n";
}
int CLASS_NULL(SV *tree)
{
	if (tree == NULL)
	{
		cout << "Chua co du lieu !!!\n";
		return 0;
	}
	return 1;
}
// Nhom ham duyet-tim kiem tren cay
void OUT_ST_CONSOLE(SV *tree)
{
	cout << setw(10) << left << tree->key;
	cout << setw(32) << left << tree->data.HTHV;
}
void DUYET_CAY_TRUOC(SV *tree, string key_goc)
{
	if (tree != NULL)
	{
		if (tree->key == key_goc)
		{
			OUT_ST_CONSOLE(tree);
			cout << " la nut goc cua cay\n";
		}
		else if ((tree->parent)->left == tree)
		{
			OUT_ST_CONSOLE(tree);
			cout << " la nut con trai cua\t";
			OUT_ST_CONSOLE((tree->parent));
			cout << endl;
		}
		else
		{
			OUT_ST_CONSOLE(tree);
			cout << " la nut con phai cua\t";
			OUT_ST_CONSOLE((tree->parent));
			cout << endl;
		}
		DUYET_CAY_TRUOC(tree->left, key_goc);
		DUYET_CAY_TRUOC(tree->right, key_goc);
	}
}
SV *SEARCH_SV_MSHV(SV *tree, string MSSV)
{
	while (tree != NULL && tree->key != MSSV)
	{
		if (tree->key.compare(MSSV) > 0)
			tree = tree->left;
		else
			tree = tree->right;
	}
	return tree;
}
void TIM_SINH_VIEN_THEO_MH(SV *tree, int check)
{
	if (tree != NULL)
	{
		TIM_SINH_VIEN_THEO_MH(tree->left, check);
		if (check == 1)
		{
			cout << setw(32) << left << tree->data.HTHV << "Co diem MH1: " << tree->data.DiemMH1 << "\n";
		}
		else
			cout << setw(32) << left << tree->data.HTHV << "Co diem MH2: " << tree->data.DiemMH2 << "\n";
		TIM_SINH_VIEN_THEO_MH(tree->right, check);
	}
}
void IN_DU_LIEU_TRONG_CAY(SV *tree)
{
	if (tree != NULL)
	{

		OUT_ST_CONSOLE(tree);
		cout << "\n";
		IN_DU_LIEU_TRONG_CAY(tree->left);
		IN_DU_LIEU_TRONG_CAY(tree->right);
	}
}
// Xoa nut
SV *TREE_MINIMUM(SV *x)
{
	while (x->left != NULL)
		x = x->left;
	return x;
}
SV *TREE_SUCCESSOR(SV *x)
{
	SV *y;
	if (x->right != NULL)
		return TREE_MINIMUM(x->right);
	y = x->parent;
	while ((y != NULL) && (x == y->right))
	{
		x = y;
		y = y->parent;
	}
	return y;
}
SV *TREE_DELETE(SV *&tree, SV *z)
{
	SV *x, *y;
	if ((z->left == NULL) || (z->right == NULL))
		y = z;
	else
		y = TREE_SUCCESSOR(z);
	if (y->left != NULL)
		x = y->left;
	else
		x = y->right;
	if (x != NULL)
		x->parent = y->parent;
	if (y->parent == NULL)
		tree = x;
	else if (y == (y->parent)->left)
		(y->parent)->left = x;
	else
		(y->parent)->right = x;
	if (y != z)
	{
		z->key = y->key;
		z->data = y->data;
	}
	return y;
}
// In du lieu sap xep
node A[100];
int i = 0;

// In du lieu sap xep
void diemmon(SV *tree)
{
	if (tree != NULL)
	{
		diemmon(tree->left);
		A[i].ID = tree->key;
		A[i].dulieu.HTHV += tree->data.HTHV;
		A[i].dulieu.DiemMH1 = tree->data.DiemMH1;
		A[i].dulieu.DiemMH2 = tree->data.DiemMH2;
		i++;
		diemmon(tree->right);
	}
}
int select(int a,int b)
{
	if(b==5)
		return A[a].dulieu.DiemMH1;
	if(b==6)
		return A[a].dulieu.DiemMH2;	
}
void tangdan(node A[],int n,int x)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if (select(j,x) < select(j-1,x))
			{
				node temp = A[j];
				A[j] = A[j - 1];
				A[j - 1] = temp;
			}
		}
	}
}
void tangdan1(node A[],int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = n - 1; j > i; j--)
		{
			if(A[j].dulieu.DiemMH1==A[j-1].dulieu.DiemMH1)
			{
				if (A[j].dulieu.DiemMH2 < A[j-1].dulieu.DiemMH2)
				{
					node temp = A[j];
					A[j] = A[j - 1];
					A[j - 1] = temp;
				}
			}
			
		}
	}
}
// Doc ghi du lieu
void DOC_FILE(SV *&tree)
{
	int n = 0, check;
	string t_key, src;
	info temp;
	fstream fi;
	cout << "1.Doc dia chi mac dinh\n";
	cout << "2.Doc dia chi theo yeu cau\n";
	cout << "Lua chon:";
	cin >> check;
	cin.ignore();
	if (check == 1)
	{
		fi.open("D:\\DATACTDL\\hocvien.txt");
	}
	else
	{
		cout << "Nhap vao duong dan:";
		getline(cin, src);
		fi.open(src.c_str(), ios::in);
	}
	if (fi.fail())
		cout << "Khong doc duoc file!\n";
	else
	{
		cout << "Da truy cap vao duong dan: " << src << endl;
		fi >> n;
		fi.ignore();
		for (int i = 0; i < n; i++)
		{
			getline(fi, t_key);
			getline(fi, temp.HTHV);
			getline(fi, temp.MMH1);
			fi >> temp.DiemMH1;
			fi.ignore();
			getline(fi, temp.MMH2);
			fi >> temp.DiemMH2;
			fi.ignore();
			SV_INSERT(tree, t_key, temp);
		}
	}
	if (tree == NULL)
	{
		cout << "Doc du lieu that bai !\n";
	}
	else
	{
		cout << "Doc file thanh cong !\n";
	}
	fi.close();
}
void GHI_CAY_SV(SV *tree, fstream &fo)
{

	if (tree != NULL)
	{

		fo << setw(9) << left << tree->key;
		fo << setw(31) << left << tree->data.HTHV;
		fo << setw(8) << left << tree->data.MMH1;
		fo << setw(8) << left << tree->data.DiemMH1;
		fo << setw(8) << left << tree->data.MMH2;
		fo << setw(8) << left << tree->data.DiemMH2 << "\n";
		GHI_CAY_SV(tree->left, fo);
		GHI_CAY_SV(tree->right, fo);
	}
}
void GHI_FILE(SV *tree)
{
	// Khoi tao bien duong dan va nhap duong dan
	string src = "";
	cout << "Nhap vao duong dan file:";
	getline(cin, src);
	// Khoi tao bien fo thuoc vao lop fstream co duong dan src da ep kieu ve chuoi kieu con tro,
	fstream fo(src.c_str(), ios::out);
	// Ghi tieu de vao file
	fo << setw(9) << left << "MSHV";
	fo << setw(30) << left << "Ho va ten";
	fo << setw(8) << left << "MaMH-1";
	fo << setw(8) << left << "Diem";
	fo << setw(8) << left << "MaMH-2";
	fo << setw(8) << left << "Diem"
	   << "\n";
	// Ghi thong tin cua cay Sinh Vien vao file
	GHI_CAY_SV(tree, fo);
	fo.close();
	cout << "Ghi file thanh cong !\n";
}
// Phan giao dien
int menu_1()
{
	int check = 0;
	cout << "=========================MENU=======================\n";
	cout << "1.Them 1 lop n sinh vien.\n";
	cout << "2.Them 1 hoc vien moi.\n";
	cout << "4.Xoa 1 hoc vien co MSHV can xoa.\n";
	cout << "____________________________________________________\n";
	cout << "Nhap vao yeu cau:";
	cin >> check;
	if (check != 1 && check != 2 && check != 4)
		return -1;
	return check;
}
int menu_2()
{
	int check;
	cout << "=========================MENU=======================\n";
	cout << "3.In ra HV co MSHV can tim.\n";
	cout << "5.In ra thu tu tang dan cua theo diem mon 1 (DH1).\n";
	cout << "6.In ra thu tu tang dan cua theo diem mon 2(DH2).\n";
	cout << "7.In ra thong tin theo thu tu tang dan DM1 \n	(neu DM1 bang nhau thi tang dan DM2)\n";
	cout << "8.In ra HTHV,DM cua cac hoc vien theo MMH\n";
	cout << "9.Viet ra MSHV. HTHV theo dang cay.\n";
	cout << "Nhap vao yeu cau:";
	cin >> check;
	if (check != 3 && check != 5 && check != 6 && check != 7 && check != 8 && check != 9)
		return -1;
	return check;
}
int menu_3()
{
	int check;
	cout << "=========================MENU=======================\n";
	cout << "10.Ghi thong tin vao file\n";
	cout << "11.Mo file\n";
	cout << "Nhap vao yeu cau:";
	cin >> check;
	if (check != 10 && check != 11)
		return -1;
	return check;
}
int menu(SV *tree)
{
	system("cls");
	int choice = 0;

	cout << "=========================MENU=======================\n";
	cout << "1.Thao tac them - xoa du lieu\n";
	cout << "2.In ra cac thong tin theo yeu cau\n";
	cout << "3.Thao tac tren FILE\n";
	cout << "0.Thoat chuong trinh\n";
	cout << "_________________________DATA_______________________\n";
	if (tree == NULL)

		cout << "\nChua co du lieu !!!\n";

	else
		IN_DU_LIEU_TRONG_CAY(tree);
	cout << "____________________________________________________\n";
	cout << "Nhap vao yeu cau:";
	cin >> choice;
	switch (choice)
	{
	case 1:
	{
		system("cls");
		return menu_1();
	}
	break;
	case 2:
	{
		system("cls");
		return menu_2();
	}
	break;
	case 3:
	{
		system("cls");
		return menu_3();
	}
	case 0:
	{
		return 0;
		break;
	}
	default:
		cout << "Nhap lai yeu cau !!;";
		break;
	}
}
// Phan than va xu li cua chuong trinh
int main()
{
	SV *root;
	INIT_BST(root);
	int chon = 0;

	while (1)
	{
		chon = menu(root);
		cin.ignore();
		cout << "====================================================\n";
		cout << setw(32) << right << "-+-Thong Bao-+-\n";
		switch (chon)
		{
		case 1:
		{
			CLASS_INSERT(root);
			break;
		}
		case 2:
		{
			// Nhap thong tin cua SV de them vao cay
			string v;
			cout << "Nhap vao MSSV:";
			getline(cin, v);
			info thongtin = INPUT_DATA();
			// Them SV
			SV_INSERT(root, v, thongtin);
			cout << "Them thanh cong hoc vien !\n";
			break;
		}
		case 3:
		{
			if (CLASS_NULL(root) == 1)
			{
				string MSSV;
				cout << "Nhap vao MSHV can tim kiem:";
				getline(cin, MSSV);
				SV *p = SEARCH_SV_MSHV(root, MSSV);
				if (p != NULL)
				{
					cout << "Tim thanh cong hoc vien !" << endl;
					cout << "MSSV " << p->key << "|| Ten hoc vien:" << p->data.HTHV;
					cout << " || MMH 1: " << p->data.MMH1 << " || Diem MH 1: " << p->data.DiemMH1 << endl;
				}
				else
					cout << "Tim that bai khong co MSHV trung khop!\n";
			}
			break;
		}
		case 4:
		{
			if (CLASS_NULL(root) == 1)
			{
				// Khoi tao MSSV de tim kiem va nhap du lieu
				string MSSV_X;
				cout << "Nhap vao MSSV can xoa:";
				getline(cin, MSSV_X);
				// Tim nut SV thoa gia tri can tim
				SV *n = SEARCH_SV_MSHV(root, MSSV_X);
				if (n == NULL)
				{
					cout << "Khong tim thay hoc vien !\n";
				}
				else
				{
					// Tien hanh xoa va kiem tra xem da xoa thanh cong chua
					SV *m = TREE_DELETE(root, n);
					if (m != NULL)
						cout << "Da xoa hoc vien !\n";
				}
			}
			break;
		}
		case 5:
		{
			diemmon(root);
			tangdan(A,i,chon);
			for(int a = 0;a < i;a++)
			{
				cout<<setw(10) << left <<A[a].ID;
				A[a].ID="";
				cout<<setw(30) << left <<A[a].dulieu.HTHV;
				A[a].dulieu.HTHV="";
				cout<<setw(8) << left <<A[a].dulieu.DiemMH1<<endl;
				A[a].dulieu.DiemMH1=0;
			}
			i=0;
			break;
		}
		case 6:
		{
			diemmon(root);
			tangdan(A,i,chon);
			for(int a = 0;a < i;a++)
			{
				cout<<setw(10) << left <<A[a].ID;
				A[a].ID="";
				cout<<setw(30) << left <<A[a].dulieu.HTHV;
				A[a].dulieu.HTHV="";
				cout<<setw(8) << left <<A[a].dulieu.DiemMH2<<endl;
				A[a].dulieu.DiemMH2=0;
			}
			i=0;
			break;
		}
		case 7:
		{
			diemmon(root);
			tangdan(A,i,5);
			tangdan1(A,i);
			for(int a = 0;a < i;a++)
			{
				cout<<setw(10) << left <<A[a].ID;
				A[a].ID="";
				cout<<setw(30) << left <<A[a].dulieu.HTHV;
				A[a].dulieu.HTHV="";
				cout<<setw(8) << left <<A[a].dulieu.DiemMH1;
				A[a].dulieu.DiemMH1=0;
				cout<<setw(8) << left <<A[a].dulieu.DiemMH2<<endl;
				A[a].dulieu.DiemMH2=0;
			}
			i=0;
			break;
		}

		case 8:
		{
			if (CLASS_NULL(root) == 1)
			{
				int check = 0;
				cout << "Nhap vao mon hoc can in ra [(MMH1):1 - (MMH2):2]:";
				cin >> check;
				cin.ignore();
				TIM_SINH_VIEN_THEO_MH(root, check);
			}
			break;
		}
		case 9:
		{
			if (CLASS_NULL(root) == 1)
				DUYET_CAY_TRUOC(root, root->key);
			break;
		}
		case 10:
		{
			GHI_FILE(root);
			break;
		}
		case 11:
		{
			DOC_FILE(root);
			break;
		}
		case 0:
		{
			cout << "Tam biet !\n";
			return 0;
			break;
		}
		default:
			cout << "Vui long nhap dung yeu cau!\n";
			break;
		}
		cout << "Nhap phim bat ki de tiep tuc !\n";
		cin.get();
	}

	return 0;
}

