#ifndef GLM_H
#define GLM_H 1

#include <RcppArmadillo.h>
#include <list>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include "crossprodmat.h"
#include "covariancemat.h"
#include "cstat.h"
#include "modelSel.h"
#include "modselFunction.h"
using namespace std;




//Function to evaluate the marginal likelihood
double marginal_glm(int *sel, int *nsel, struct marginalPars *pars);


//*************************************************************************************
//  Generic function returning a pointer to logprior, gradient and hessians for a given priorcode
//*************************************************************************************

void set_logjoint_glm(pt2fun *fjoint, pt2funupdate *fjoint_update, pt2gradUniv *fjoint_grad, pt2gradhessUniv *fjoint_gradhess, pt2hess *fjoint_hess, pt2fun *fjoint0, pt2gradhessUniv *fjoint_gradhess0, pt2hess *fjoint_hess0, bool *orthoapprox, bool *nonlocal, bool *momsingle, bool *momgroup, int *family, int *priorcode, int *method);

void set_logl_glm(pt2fun *logl, pt2funupdate *logl_update, pt2gradUniv *logl_grad, pt2gradhessUniv *logl_gradhess, pt2hess *logl_hess, pt2fun *logl0, pt2gradhessUniv *logl_gradhess0, pt2hess *logl_hess0, int *family);



//*************************************************************************************
// LOGISTIC REGRESSION
//*************************************************************************************


//MAIN FUNCTIONS

//Function to evaluate the negative loglikelihood, and initialize funargs. It has type pt2fun (defined in modselFunction.h)
void neglogl_logreg(double *f, double *th, int *sel, int *thlength, struct marginalPars *pars,  std::map<string, double *> *funargs);

//Evaluate the negative loglikelihood at th=0. Do not initialize funargs
void neglogl0_logreg(double *f, double *th, int *sel, int *thlength, struct marginalPars *pars,  std::map<string, double *> *funargs);

//Update the negative loglikelihood due to changing th[j] into thjnew, and update funargs. It has type pt2funupdate (defined in modselFunction.h)
void negloglupdate_logreg(double *fnew, double *thjnew, int j, double *f, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double *> *funargs);

//Gradient and hessian wrt j. It has type pt2gradhessUniv (defined in modselFunction.h)
void negloglgradhess_logreg(double *grad, double *hess, int j, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);
void negloglgrad_logreg(double *grad, int j, double *th, int *sel, int *thlength, struct marginalPars *, std::map<string, double*> *funargs);
void negloglgradhess0_logreg(double *grad, double *hess, int j, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);

//Obtain hessian. It has type pt2hess (defined in modselFunction.h)
void negloglhess_logreg(double **hess, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);
void negloglhess0_logreg(double **hess, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);


//AUXILIARY FUNCTIONS TO EVALUATE LOG-JOINT AND DERIVATIVES. THESE CAN BE COPY/PASTED WITH MINIMAL ADAPTATION, IF ONE WISHES TO IMPLEMENT OTHER LIKELIHOODS (SEE POISSON EXAMPLE BELOW)

//Log joint under pMOM - gZellner prior
void fjoint_logreg_pmomgzell(double *f, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double *> *funargs);
void fjointu_logreg_pmomgzell(double *fnew, double *thjnew, int j, double *f, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double *> *funargs);
void fjointg_logreg_pmomgzell(double *grad, int j, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);
void fjointgh_logreg_pmomgzell(double *grad, double *hess, int j, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);
void fjointh_logreg_pmomgzell(double **hess, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);

//Log joint under peMOM - gZellner prior
void fjoint_logreg_pemomgzell(double *f, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double *> *funargs);
void fjointu_logreg_pemomgzell(double *fnew, double *thjnew, int j, double *f, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double *> *funargs);
void fjointg_logreg_pemomgzell(double *grad, int j, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);
void fjointgh_logreg_pemomgzell(double *grad, double *hess, int j, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);
void fjointh_logreg_pemomgzell(double **hess, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);

//Log joint under gZellner - gZellner prior
void fjoint_logreg_gzellgzell(double *f, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double *> *funargs);
void fjointu_logreg_gzellgzell(double *fnew, double *thjnew, int j, double *f, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double *> *funargs);
void fjointg_logreg_gzellgzell(double *grad, int j, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);
void fjointgh_logreg_gzellgzell(double *grad, double *hess, int j, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);
void fjointh_logreg_gzellgzell(double **hess, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);

void fjoint0_logreg_gzellgzell(double *f, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double *> *funargs);
void fjointgh0_logreg_gzellgzell(double *grad, double *hess, int j, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);
void fjointh0_logreg_gzellgzell(double **hess, double *th, int *sel, int *thlength, struct marginalPars *pars, std::map<string, double*> *funargs);




//*************************************************************************************
// POISSON REGRESSION
//*************************************************************************************





#endif /* GLM_H */