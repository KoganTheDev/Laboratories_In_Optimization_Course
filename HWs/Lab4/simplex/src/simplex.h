// simplex.h


#include <stdio.h>

// Global Variables


#define N 128
#define M 64


extern  double  A[N][N];
extern  double B[N][N];
extern  double C[N];
extern  double D[N][N];
extern  double c[N];
extern  double b[N];
extern  double b_aux[N];
extern  double cb[N];
extern  double cbBI[N];
extern  double cbBID[M];
extern  double cd[N];
extern  double rd[N];
extern  double BID[N][N];
extern  double W[N][N];
extern  double BI[N][N];
extern  double BIA_aux[N][N];

extern double A_aux[N][N];
extern double BIb[N];

extern double epsilon;
  
extern  int d[N];
extern  int d_aux[N];
extern  int basis[N];
extern  int n;
extern  int m;
extern  FILE *fp;


extern   int Initial_n;
extern    double Initial_W[N][N];
extern   double Initial_cb[N];
extern  double Initial_cd[N];
extern  double Initial_A[N][N];
extern  double Initial_A_aux[N][N];
extern  double Initial_c[N];
extern   double Initial_c_aux[N];
extern  int Initial_basis[N];
extern  double Initial_D[N][N];
extern  int Initial_d[N];
extern   double Initial_B[N][N];
extern  double Initial_BIb[N];

extern   double Initial_C[N][N];
extern   double Initial_b[N];
extern   double Initial_b_aux[N];
extern   double Initial_rd[N];
extern   double Initial_BID[N][N];
extern   double Initial_BI[N][N];
extern   double Initial_cbBI[N];
extern   double Initial_cbBID[N];
extern   double Initial_BIA_aux[N][N];





// Global functions

extern void copy_matrix(double Dest[][N], double Source[][N], int n, 
int m);

extern void copy_vector(double Dest[], double Source[], int n);

extern void bublesort(int array[],  int n);

extern void print_result();


extern void Initial_simplex_algorithm();

extern void simplex_algorithm();


extern int find_exiting_id(double y[][N], double x[], int enter_id,
int n, int m);

extern int find_most_negative();

extern int find_Initial_most_negative();

extern void inv_gaussian(double B[][N], double A[][N],  
   int n);

extern  void matrix_mult(double C[][N], double A[][N], double B[][N],  
int 
n, 
int m, int p);

extern void matrix_vector_mult(double c[], 
double A[][N], double b[], int n, int m); 

extern void vector_matrix_mult(double c[], double b[], double A[][N],   
  int n, int m);

extern void print_no_solution();

extern void print_original_system();

extern void print_result();

extern void read_file();

extern void swap_colums(double A[][N], int i, int j, int m, int n);

extern void swap_rows(double W[][N], int n, int m1, int m2);


extern void vector_subtract(double result_v[], double v1[], double v2[],  
int n);


extern void 
copy_submatrix(double Dest[][N], double Source[][N],  int istart,
   int depth, int jstart, int length);


extern void copy_initial_matrix();

extern double find_min_value(double rd[], int n);


extern void compute_cb_cd();

extern void compute_Initial_cb_Initial_cd();
 
extern void print_initial_solution(); 

extern void print_solution();

extern void Initial_swap_colums(int i, int j);

extern void stage2_swap_colums(int i, int j);

extern void Initial_set_d();
extern void set_d();

extern void set_Initial_A_aux();
extern void set_A_aux();

extern void bublesort_d(int array[], double darr[],  int n);

extern void erase_epsilons_matrix(double darray[][N], int m, int n);
extern void erase_epsilons_vector(double darray[], int n);

extern int find_Initial_exiting_id(double y[][N], double x[], int 
enter_id, int n, int m);

extern void copy_to_initial_matrix();
