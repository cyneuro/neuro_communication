/* Created by Language version: 7.7.0 */
/* VECTORIZED */
#define NRN_VECTORIZED 1
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "mech_api.h"
#undef PI
#define nil 0
#include "md1redef.h"
#include "section.h"
#include "nrniv_mf.h"
#include "md2redef.h"
 
#if METHOD3
extern int _method3;
#endif

#if !NRNGPU
#undef exp
#define exp hoc_Exp
extern double hoc_Exp(double);
#endif
 
#define nrn_init _nrn_init__na_wb
#define _nrn_initial _nrn_initial__na_wb
#define nrn_cur _nrn_cur__na_wb
#define _nrn_current _nrn_current__na_wb
#define nrn_jacob _nrn_jacob__na_wb
#define nrn_state _nrn_state__na_wb
#define _net_receive _net_receive__na_wb 
#define rate rate__na_wb 
#define states states__na_wb 
 
#define _threadargscomma_ _p, _ppvar, _thread, _nt,
#define _threadargsprotocomma_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt,
#define _threadargs_ _p, _ppvar, _thread, _nt
#define _threadargsproto_ double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt
 	/*SUPPRESS 761*/
	/*SUPPRESS 762*/
	/*SUPPRESS 763*/
	/*SUPPRESS 765*/
	 extern double *getarg();
 /* Thread safe. No static _p or _ppvar. */
 
#define t _nt->_t
#define dt _nt->_dt
#define gbar _p[0]
#define gbar_columnindex 0
#define minfvhalf _p[1]
#define minfvhalf_columnindex 1
#define minfk _p[2]
#define minfk_columnindex 2
#define hinfvhalf _p[3]
#define hinfvhalf_columnindex 3
#define hinfk _p[4]
#define hinfk_columnindex 4
#define htauphi _p[5]
#define htauphi_columnindex 5
#define ina _p[6]
#define ina_columnindex 6
#define minf _p[7]
#define minf_columnindex 7
#define hinf _p[8]
#define hinf_columnindex 8
#define mtau _p[9]
#define mtau_columnindex 9
#define htau _p[10]
#define htau_columnindex 10
#define g _p[11]
#define g_columnindex 11
#define m _p[12]
#define m_columnindex 12
#define h _p[13]
#define h_columnindex 13
#define ena _p[14]
#define ena_columnindex 14
#define Dm _p[15]
#define Dm_columnindex 15
#define Dh _p[16]
#define Dh_columnindex 16
#define v _p[17]
#define v_columnindex 17
#define _g _p[18]
#define _g_columnindex 18
#define _ion_ena	*_ppvar[0]._pval
#define _ion_ina	*_ppvar[1]._pval
#define _ion_dinadv	*_ppvar[2]._pval
 
#if MAC
#if !defined(v)
#define v _mlhv
#endif
#if !defined(h)
#define h _mlhh
#endif
#endif
 
#if defined(__cplusplus)
extern "C" {
#endif
 static int hoc_nrnpointerindex =  -1;
 static Datum* _extcall_thread;
 static Prop* _extcall_prop;
 /* external NEURON variables */
 /* declaration of user functions */
 static void _hoc_rate(void);
 static int _mechtype;
extern void _nrn_cacheloop_reg(int, int);
extern void hoc_register_prop_size(int, int, int);
extern void hoc_register_limits(int, HocParmLimits*);
extern void hoc_register_units(int, HocParmUnits*);
extern void nrn_promote(Prop*, int, int);
extern Memb_func* memb_func;
 
#define NMODL_TEXT 1
#if NMODL_TEXT
static const char* nmodl_file_text;
static const char* nmodl_filename;
extern void hoc_reg_nmodl_text(int, const char*);
extern void hoc_reg_nmodl_filename(int, const char*);
#endif

 extern void _nrn_setdata_reg(int, void(*)(Prop*));
 static void _setdata(Prop* _prop) {
 _extcall_prop = _prop;
 }
 static void _hoc_setdata() {
 Prop *_prop, *hoc_getdata_range(int);
 _prop = hoc_getdata_range(_mechtype);
   _setdata(_prop);
 hoc_retpushx(1.);
}
 /* connect user functions to hoc names */
 static VoidFunc hoc_intfunc[] = {
 "setdata_na_wb", _hoc_setdata,
 "rate_na_wb", _hoc_rate,
 0, 0
};
 /* declare global and static user variables */
 /* some parameters have upper and lower limits */
 static HocParmLimits _hoc_parm_limits[] = {
 0,0,0
};
 static HocParmUnits _hoc_parm_units[] = {
 "gbar_na_wb", "siemens/cm2",
 "ina_na_wb", "mA/cm2",
 "mtau_na_wb", "ms",
 "htau_na_wb", "ms",
 "g_na_wb", "siemens/cm2",
 0,0
};
 static double delta_t = 0.01;
 static double h0 = 0;
 static double m0 = 0;
 /* connect global user variables to hoc */
 static DoubScal hoc_scdoub[] = {
 0,0
};
 static DoubVec hoc_vdoub[] = {
 0,0,0
};
 static double _sav_indep;
 static void nrn_alloc(Prop*);
static void  nrn_init(NrnThread*, _Memb_list*, int);
static void nrn_state(NrnThread*, _Memb_list*, int);
 static void nrn_cur(NrnThread*, _Memb_list*, int);
static void  nrn_jacob(NrnThread*, _Memb_list*, int);
 
static int _ode_count(int);
static void _ode_map(int, double**, double**, double*, Datum*, double*, int);
static void _ode_spec(NrnThread*, _Memb_list*, int);
static void _ode_matsol(NrnThread*, _Memb_list*, int);
 
#define _cvode_ieq _ppvar[3]._i
 static void _ode_matsol_instance1(_threadargsproto_);
 /* connect range variables in _p that hoc is supposed to know about */
 static const char *_mechanism[] = {
 "7.7.0",
"na_wb",
 "gbar_na_wb",
 "minfvhalf_na_wb",
 "minfk_na_wb",
 "hinfvhalf_na_wb",
 "hinfk_na_wb",
 "htauphi_na_wb",
 0,
 "ina_na_wb",
 "minf_na_wb",
 "hinf_na_wb",
 "mtau_na_wb",
 "htau_na_wb",
 "g_na_wb",
 0,
 "m_na_wb",
 "h_na_wb",
 0,
 0};
 static Symbol* _na_sym;
 
extern Prop* need_memb(Symbol*);

static void nrn_alloc(Prop* _prop) {
	Prop *prop_ion;
	double *_p; Datum *_ppvar;
 	_p = nrn_prop_data_alloc(_mechtype, 19, _prop);
 	/*initialize range parameters*/
 	gbar = 0;
 	minfvhalf = 34.57;
 	minfk = -9.25;
 	hinfvhalf = 55.16;
 	hinfk = 7.07;
 	htauphi = 5;
 	_prop->param = _p;
 	_prop->param_size = 19;
 	_ppvar = nrn_prop_datum_alloc(_mechtype, 4, _prop);
 	_prop->dparam = _ppvar;
 	/*connect ionic variables to this model*/
 prop_ion = need_memb(_na_sym);
 nrn_promote(prop_ion, 0, 1);
 	_ppvar[0]._pval = &prop_ion->param[0]; /* ena */
 	_ppvar[1]._pval = &prop_ion->param[3]; /* ina */
 	_ppvar[2]._pval = &prop_ion->param[4]; /* _ion_dinadv */
 
}
 static void _initlists();
  /* some states have an absolute tolerance */
 static Symbol** _atollist;
 static HocStateTolerance _hoc_state_tol[] = {
 0,0
};
 static void _update_ion_pointer(Datum*);
 extern Symbol* hoc_lookup(const char*);
extern void _nrn_thread_reg(int, int, void(*)(Datum*));
extern void _nrn_thread_table_reg(int, void(*)(double*, Datum*, Datum*, NrnThread*, int));
extern void hoc_register_tolerance(int, HocStateTolerance*, Symbol***);
extern void _cvode_abstol( Symbol**, double*, int);

 void _na_wb_reg() {
	int _vectorized = 1;
  _initlists();
 	ion_reg("na", -10000.);
 	_na_sym = hoc_lookup("na_ion");
 	register_mech(_mechanism, nrn_alloc,nrn_cur, nrn_jacob, nrn_state, nrn_init, hoc_nrnpointerindex, 1);
 _mechtype = nrn_get_mechtype(_mechanism[1]);
     _nrn_setdata_reg(_mechtype, _setdata);
     _nrn_thread_reg(_mechtype, 2, _update_ion_pointer);
 #if NMODL_TEXT
  hoc_reg_nmodl_text(_mechtype, nmodl_file_text);
  hoc_reg_nmodl_filename(_mechtype, nmodl_filename);
#endif
  hoc_register_prop_size(_mechtype, 19, 4);
  hoc_register_dparam_semantics(_mechtype, 0, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 1, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 2, "na_ion");
  hoc_register_dparam_semantics(_mechtype, 3, "cvodeieq");
 	hoc_register_cvode(_mechtype, _ode_count, _ode_map, _ode_spec, _ode_matsol);
 	hoc_register_tolerance(_mechtype, _hoc_state_tol, &_atollist);
 	hoc_register_var(hoc_scdoub, hoc_vdoub, hoc_intfunc);
 	ivoc_help("help ?1 na_wb /home/tyler/git_stage/Borgers-Examples-in-BMTK/31-ING_Entrainment/components/mechanisms/na_wb.mod\n");
 hoc_register_limits(_mechtype, _hoc_parm_limits);
 hoc_register_units(_mechtype, _hoc_parm_units);
 }
static int _reset;
static char *modelname = "";

static int error;
static int _ninits = 0;
static int _match_recurse=1;
static void _modl_cleanup(){ _match_recurse=1;}
static int rate(_threadargsprotocomma_ double);
 
static int _ode_spec1(_threadargsproto_);
/*static int _ode_matsol1(_threadargsproto_);*/
 static int _slist1[1], _dlist1[1];
 static int states(_threadargsproto_);
 
/*CVODE*/
 static int _ode_spec1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {int _reset = 0; {
   rate ( _threadargscomma_ v ) ;
   Dh = ( hinf - h ) / htau ;
   }
 return _reset;
}
 static int _ode_matsol1 (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
 rate ( _threadargscomma_ v ) ;
 Dh = Dh  / (1. - dt*( ( ( ( - 1.0 ) ) ) / htau )) ;
  return 0;
}
 /*END CVODE*/
 static int states (double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) { {
   rate ( _threadargscomma_ v ) ;
    h = h + (1. - exp(dt*(( ( ( - 1.0 ) ) ) / htau)))*(- ( ( ( hinf ) ) / htau ) / ( ( ( ( - 1.0 ) ) ) / htau ) - h) ;
   }
  return 0;
}
 
static int  rate ( _threadargsprotocomma_ double _lv ) {
    minf = 1.0 / ( 1.0 + ( exp ( ( _lv + minfvhalf ) / ( minfk ) ) ) ) ;
   mtau = ( 1.0 - exp ( - _lv / 10.0 - 7.0 / 2.0 ) ) / ( 0.1 * _lv + 4.0 * ( 1.0 - exp ( - _lv / 10.0 - 7.0 / 2.0 ) ) * exp ( - _lv / 18.0 - 10.0 / 3.0 ) + 3.5 ) ;
   hinf = 1.0 / ( 1.0 + ( exp ( ( _lv + hinfvhalf ) / ( hinfk ) ) ) ) ;
   htau = ( exp ( 0.1 * _lv ) + 0.0608 ) / ( 0.07 * ( exp ( 0.1 * _lv ) + 0.0608 ) * exp ( - _lv / 20.0 - 29.0 / 10.0 ) + exp ( 0.1 * _lv ) ) ;
   htau = htau / htauphi ;
     return 0; }
 
static void _hoc_rate(void) {
  double _r;
   double* _p; Datum* _ppvar; Datum* _thread; NrnThread* _nt;
   if (_extcall_prop) {_p = _extcall_prop->param; _ppvar = _extcall_prop->dparam;}else{ _p = (double*)0; _ppvar = (Datum*)0; }
  _thread = _extcall_thread;
  _nt = nrn_threads;
 _r = 1.;
 rate ( _p, _ppvar, _thread, _nt, *getarg(1) );
 hoc_retpushx(_r);
}
 
static int _ode_count(int _type){ return 1;}
 
static void _ode_spec(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ena = _ion_ena;
     _ode_spec1 (_p, _ppvar, _thread, _nt);
  }}
 
static void _ode_map(int _ieq, double** _pv, double** _pvdot, double* _pp, Datum* _ppd, double* _atol, int _type) { 
	double* _p; Datum* _ppvar;
 	int _i; _p = _pp; _ppvar = _ppd;
	_cvode_ieq = _ieq;
	for (_i=0; _i < 1; ++_i) {
		_pv[_i] = _pp + _slist1[_i];  _pvdot[_i] = _pp + _dlist1[_i];
		_cvode_abstol(_atollist, _atol, _i);
	}
 }
 
static void _ode_matsol_instance1(_threadargsproto_) {
 _ode_matsol1 (_p, _ppvar, _thread, _nt);
 }
 
static void _ode_matsol(NrnThread* _nt, _Memb_list* _ml, int _type) {
   double* _p; Datum* _ppvar; Datum* _thread;
   Node* _nd; double _v; int _iml, _cntml;
  _cntml = _ml->_nodecount;
  _thread = _ml->_thread;
  for (_iml = 0; _iml < _cntml; ++_iml) {
    _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
    _nd = _ml->_nodelist[_iml];
    v = NODEV(_nd);
  ena = _ion_ena;
 _ode_matsol_instance1(_threadargs_);
 }}
 extern void nrn_update_ion_pointer(Symbol*, Datum*, int, int);
 static void _update_ion_pointer(Datum* _ppvar) {
   nrn_update_ion_pointer(_na_sym, _ppvar, 0, 0);
   nrn_update_ion_pointer(_na_sym, _ppvar, 1, 3);
   nrn_update_ion_pointer(_na_sym, _ppvar, 2, 4);
 }

static void initmodel(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt) {
  int _i; double _save;{
  h = h0;
  m = m0;
 {
   rate ( _threadargscomma_ v ) ;
   m = minf ;
   h = hinf ;
   }
 
}
}

static void nrn_init(NrnThread* _nt, _Memb_list* _ml, int _type){
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v = _v;
  ena = _ion_ena;
 initmodel(_p, _ppvar, _thread, _nt);
 }
}

static double _nrn_current(double* _p, Datum* _ppvar, Datum* _thread, NrnThread* _nt, double _v){double _current=0.;v=_v;{ {
   m = minf ;
   g = gbar * m * m * m * h ;
   ina = g * ( v - ena ) ;
   }
 _current += ina;

} return _current;
}

static void nrn_cur(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; double _rhs, _v; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
  ena = _ion_ena;
 _g = _nrn_current(_p, _ppvar, _thread, _nt, _v + .001);
 	{ double _dina;
  _dina = ina;
 _rhs = _nrn_current(_p, _ppvar, _thread, _nt, _v);
  _ion_dinadv += (_dina - ina)/.001 ;
 	}
 _g = (_g - _rhs)/.001;
  _ion_ina += ina ;
#if CACHEVEC
  if (use_cachevec) {
	VEC_RHS(_ni[_iml]) -= _rhs;
  }else
#endif
  {
	NODERHS(_nd) -= _rhs;
  }
 
}
 
}

static void nrn_jacob(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml];
#if CACHEVEC
  if (use_cachevec) {
	VEC_D(_ni[_iml]) += _g;
  }else
#endif
  {
     _nd = _ml->_nodelist[_iml];
	NODED(_nd) += _g;
  }
 
}
 
}

static void nrn_state(NrnThread* _nt, _Memb_list* _ml, int _type) {
double* _p; Datum* _ppvar; Datum* _thread;
Node *_nd; double _v = 0.0; int* _ni; int _iml, _cntml;
#if CACHEVEC
    _ni = _ml->_nodeindices;
#endif
_cntml = _ml->_nodecount;
_thread = _ml->_thread;
for (_iml = 0; _iml < _cntml; ++_iml) {
 _p = _ml->_data[_iml]; _ppvar = _ml->_pdata[_iml];
 _nd = _ml->_nodelist[_iml];
#if CACHEVEC
  if (use_cachevec) {
    _v = VEC_V(_ni[_iml]);
  }else
#endif
  {
    _nd = _ml->_nodelist[_iml];
    _v = NODEV(_nd);
  }
 v=_v;
{
  ena = _ion_ena;
 {   states(_p, _ppvar, _thread, _nt);
  } }}

}

static void terminal(){}

static void _initlists(){
 double _x; double* _p = &_x;
 int _i; static int _first = 1;
  if (!_first) return;
 _slist1[0] = h_columnindex;  _dlist1[0] = Dh_columnindex;
_first = 0;
}

#if defined(__cplusplus)
} /* extern "C" */
#endif

#if NMODL_TEXT
static const char* nmodl_filename = "/home/tyler/git_stage/Borgers-Examples-in-BMTK/31-ING_Entrainment/components/mechanisms/na_wb.mod";
static const char* nmodl_file_text = 
  "COMMENT\n"
  "Wang-Buzsaki Model of an Inhibitory\n"
  "Interneuron in Rat Hippocampus\n"
  "\n"
  "Sodium Channel\n"
  "\n"
  "Reference: Borgers - An Introduction to Modeling Neuronal Dynamics Chapter 5\n"
  ".mod by Tyler Banks\n"
  "ENDCOMMENT\n"
  "\n"
  "NEURON {\n"
  "	SUFFIX na_wb\n"
  "	USEION na READ ena WRITE ina\n"
  "	RANGE gbar, g\n"
  "	RANGE minf, hinf, mtau, htau\n"
  "	RANGE ina\n"
  "	RANGE minfvhalf,minfk,hinfvhalf,hinfk\n"
  "	RANGE htauphi\n"
  "}\n"
  "\n"
  "UNITS {\n"
  "	(mA) = (milliamp)\n"
  "	(mV) = (millivolt)\n"
  "}\n"
  "\n"
  "PARAMETER {\n"
  "	gbar (siemens/cm2)\n"
  "	minfvhalf = 34.57\n"
  "    minfk = -9.25 :-9.55\n"
  "    hinfvhalf = 55.16\n"
  "    hinfk = 7.07\n"
  "	htauphi = 5\n"
  "}\n"
  "\n"
  "ASSIGNED {\n"
  "	v (mV)\n"
  "	ena (mV)\n"
  "	ina (mA/cm2)\n"
  "	minf\n"
  "	hinf\n"
  "	mtau (ms)\n"
  "	htau (ms)\n"
  "	g (siemens/cm2)\n"
  "}\n"
  "\n"
  "STATE {\n"
  "	m h\n"
  "}\n"
  "\n"
  "BREAKPOINT {\n"
  "	SOLVE states METHOD cnexp\n"
  "	m = minf : See Borgers Page 32 Figure 5.1 for explaination\n"
  "	g = gbar*m*m*m*h\n"
  "	ina = g*(v-ena)\n"
  "}\n"
  "\n"
  "INITIAL {\n"
  "	rate(v)\n"
  "	m = minf\n"
  "	h = hinf\n"
  "}\n"
  "\n"
  "DERIVATIVE states {\n"
  "	rate(v)\n"
  "	:m' = (minf-m)/mtau\n"
  "	h' = (hinf-h)/htau\n"
  "}\n"
  "\n"
  "COMMENT\n"
  "Matlab code\n"
  "function m_i_inf=m_i_inf(v)\n"
  "alpha_m=0.1*(v+35)./(1-exp(-(v+35)/10));\n"
  "beta_m=4*exp(-(v+60)/18);\n"
  "m_i_inf=alpha_m./(alpha_m+beta_m);\n"
  ":minf = 0.1*(v+35)/(1-exp(-(v+35)/10))/(0.1*(v+35)/(1-exp(-(v+35)/10))+4*exp(-(v+60)/18))\n"
  ":mtau = 1/(0.1*(v+35)/(1-exp(-(v+35)/10))+4*exp(-(v+60)/18))\n"
  "\n"
  "function h_i_inf=h_i_inf(v)\n"
  "alpha_h=0.07*exp(-(v+58)/20);\n"
  "beta_h=1./(exp(-0.1*(v+28))+1);\n"
  "h_i_inf=alpha_h./(alpha_h+beta_h);\n"
  ":hinf = 0.07*exp(-(v+58)/20)/(0.07*exp(-(v+58)/20)+1/(exp(-0.1*(v+28))+1))\n"
  ":htau = 1/(0.07*exp(-(v+58)/20)+1/(exp(-0.1*(v+28))+1))\n"
  "\n"
  "Regression fit INF\n"
  "minf = 1.0/(1.0+(exp((v+34.57)/(-9.55))))\n"
  "hinf = 1.0/(1.0+(exp((v+55.16)/(7.07))))\n"
  "\n"
  "Calculated TAU\n"
  "mtau = (1 - exp(-v/10 - 7/2))/(0.1*v + 4*(1 - exp(-v/10 - 7/2))*exp(-v/18 - 10/3) + 3.5)\n"
  "htau = (exp(0.1*v) + 0.0608)/(0.07*(exp(0.1*v) + 0.0608)*exp(-v/20 - 29/10) + exp(0.1*v))\n"
  "\n"
  "ENDCOMMENT\n"
  "\n"
  "PROCEDURE rate(v (mV)) {\n"
  "	UNITSOFF\n"
  "	minf = 1.0/(1.0+(exp((v+minfvhalf)/(minfk))))\n"
  "	mtau = (1 - exp(-v/10 - 7/2))/(0.1*v + 4*(1 - exp(-v/10 - 7/2))*exp(-v/18 - 10/3) + 3.5)   \n"
  "	:minf = 0.1*(v+35)/(1-exp(-(v+35)/10))/(0.1*(v+35)/(1-exp(-(v+35)/10))+4*exp(-(v+60)/18))\n"
  "	:mtau = 1/(0.1*(v+35)/(1-exp(-(v+35)/10))+4*exp(-(v+60)/18))\n"
  "\n"
  "	hinf = 1.0/(1.0+(exp((v+hinfvhalf)/(hinfk))))\n"
  "	htau = (exp(0.1*v) + 0.0608)/(0.07*(exp(0.1*v) + 0.0608)*exp(-v/20 - 29/10) + exp(0.1*v))\n"
  "	:hinf = 0.07*exp(-(v+58)/20)/(0.07*exp(-(v+58)/20)+1/(exp(-0.1*(v+28))+1))\n"
  "	:htau = 1/(0.07*exp(-(v+58)/20)+1/(exp(-0.1*(v+28))+1))\n"
  "\n"
  "	htau = htau/htauphi\n"
  "	UNITSON\n"
  "}\n"
  ;
#endif
