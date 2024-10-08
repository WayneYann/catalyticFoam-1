/*------------------------------------------------------------------------\
|   catalyticFOAM                                                         |
|   http://www.catalyticfoam.polimi.it/                                   |
|                                                                         |
|   Authors:                                                              |
|                                                                         |
|   Alberto Cuoci <alberto.cuoci@polimi.it>                               |
|   Department of Chemistry, Materials and Chemical Engineering           |
|   Politecnico di Milano                                                 |
|   P.zza Leonardo da Vinci 32, 20133 Milano                              |
|                                                                         |
|   Matteo Maestri <matteo.maestri@polimi.it>                             |
|   Department of Energy                                                  |
|   Politecnico di Milano                                                 |
|   P.zza Leonardo da Vinci 32, 20133 Milano                              |
|                                                                         |
|   Mauro Bracconi <mauro.bracconi@polimi.it>                             |
|   Department of Energy                                                  |
|   Politecnico di Milano                                                 |
|   P.zza Leonardo da Vinci 32, 20133 Milano                              |
|                                                                         |
|-------------------------------------------------------------------------|
|                                                                         |
|   This file is part of catalyticFOAM framework.                         |
|                                                                         |
|   Copyright(C) 2020-2011, A.Cuoci, M.Maestri,                           |
|                2020-2014, M. Bracconi                                   |
|                2015-2013, S.Rebughini                                   |
|                     2013, T.Maffei                                      |
|                     2013, G.Gentile, F.Manelli                          |
|                     2012, M.Calonaci, F.Furnari                         |
|                     2011, S.Goisis, A.Osio                              |
|                                                                         |
|   catalyticFOAM is distributed in the hope that it will be useful,      |
|   but WITHOUT ANY WARRANTY; without even the implied warranty of        |
|   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
|   GNU General Public License for more details.                          |
|                                                                         |
|   OpenSMOKE++ is distributed in the hope that it will be useful,        |
|   but WITHOUT ANY WARRANTY; without even the implied warranty of        |
|   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         |
|   GNU General Public License for more details.                          |
|                                                                         |
|   You should have received a copy of the GNU General Public License     |
|   along with catalyticFOAM. If not, see <http://www.gnu.org/licenses/>. |
|                                                                         |
\*-----------------------------------------------------------------------*/

{
/*	OpenSMOKE::OpenSMOKEVectorDouble MWi = gas_mixture->M();

	forAll(T.boundaryField(), patchi)
	{
		for(int j=0; j<indexCatalyst.size(); j++)
            	{
                	if (patchi == indexCatalyst[j])
			{
				fvPatchScalarField& pp = p.boundaryFieldRef()[patchi];
				fvPatchScalarField& pT = T.boundaryFieldRef()[patchi];
				fvPatchScalarField& ppsi  = psi.boundaryFieldRef()[patchi];
				fvPatchScalarField& plambda = lambda.boundaryFieldRef()[patchi];

				forAll(pT, facei)
				{
                    			for(label i=0; i<Ygrad.size(); i++)
						Ygrad[i].boundaryFieldRef()[patchi][facei] *=  
                          	  		MWi(i+1)*AlfaCatalyst/Dmix[i].boundaryFieldRef()[patchi][facei]/(pp[facei]*ppsi[facei]); 
			
                    			if(energyEquation == true)
                     	  			grad_T.boundaryFieldRef()[patchi][facei] *= AlfaCatalyst/plambda[facei];
				}
			}
                }
	}
*/
}
