#include "TRandom.h"
#include "TGraphErrors.h"
#include "TF1.h"
#include "TCanvas.h"
#include "TLegend.h"

/*
Follows example of fitLinearRobust.C in the CERN ROOT tutorials. This implements
only the essentials for a least-squares fit to decent data.
*/

// Generate a dataset
void generateTestData(Int_t npoints, Double_t x[], Double_t y[], Double_t e[]) {
	TRandom r;
	Int_t i;

	for(i = 0; i < npoints; i++){
		x[i] = r.Uniform(-1,1);
		e[i] = 1;
		y[i] = 1 + 2*x[i] + 3*x[i]*x[i] + 4*x[i]*x[i]*x[i] + e[i]*r.Gaus();
	}
}

// Implements a least squares fit to a polynomial. In actual dataset, it
// would be preferable to perform a least trimmed squares regression.
void fitLeastSquaresCubic() {
	Int_t npoints = 250;

	Double_t *x = new Double_t[npoints];
	Double_t *y = new Double_t[npoints];
	Double_t *e = new Double_t[npoints];
	generateTestData(npoints, x, y, e);

	TGraphErrors *grr = new TGraphErrors(npoints, x, y, 0, e);
	grr->SetMinimum(-30);
	grr->SetMaximum(80);

	TF1 *fit = new TF1("fit", "pol3", -5, 5);
	TCanvas *canvas = new TCanvas("canvas", "Least squares fit");
	canvas->SetGrid();
	grr->Draw("ap");
	printf("Least squares fit:\n");
	grr->Fit(fit);

	delete [] x;
	delete [] y;
	delete [] e;
}