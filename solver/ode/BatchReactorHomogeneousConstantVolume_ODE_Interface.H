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
|-------------------------------------------------------------------------|
|                                                                         |
|   This file is part of catalyticFOAM framework.                         |
|                                                                         |
|	License                                                           |
|                                                                         |
|   Copyright(C) 2014-2011, A.Cuoci, M.Maestri,                           |
|                2014-2013, S.Rebughini                                   |
|                     2013, T.Maffei                                      |
|                     2013, G.Gentile, F.Manelli                          |
|                     2012, M.Calonaci, F.Furnari                         |
|                     2011, S.Goisis, A.Osio                              |
|                                                                         |
|   catalyticFOAM is free software: you can redistribute it and/or modify |
|   it under the terms of the GNU General Public License as published by  |
|   the Free Software Foundation, either version 3 of the License, or     |
|   (at your option) any later version.                                   |
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

#ifndef BatchReactorHomogeneousConstantVolume_ODE_Interface_H
#define	BatchReactorHomogeneousConstantVolume_ODE_Interface_H

#include "math/OpenSMOKEVector.h"
#include "math/external-ode-solvers/OpenSMOKE_OdeSystemObject.h"

#if OPENSMOKE_USE_DVODE == 1
#include "math/external-ode-solvers/OpenSMOKE_DVODE_Interface.h"
#include "math/external-ode-solvers/OpenSMOKE_DVODE.h"
#endif

#if OPENSMOKE_USE_ODEPACK == 1
#include "math/external-ode-solvers/OpenSMOKE_DLSODE_Interface.h"
#include "math/external-ode-solvers/OpenSMOKE_DLSODE.h"
#include "math/external-ode-solvers/OpenSMOKE_DLSODA_Interface.h"
#include "math/external-ode-solvers/OpenSMOKE_DLSODA.h"
#endif

#if OPENSMOKE_USE_DASPK == 1
#include "math/external-ode-solvers/OpenSMOKE_DASPK_Interface.h"
#include "math/external-ode-solvers/OpenSMOKE_DASPK.h"
#endif

#if OPENSMOKE_USE_RADAU == 1
#include "math/external-ode-solvers/OpenSMOKE_RADAU_Interface.h"
#include "math/external-ode-solvers/OpenSMOKE_RADAU.h"
#endif

#if OPENSMOKE_USE_SUNDIALS == 1
#include "math/external-ode-solvers/OpenSMOKE_CVODE_Sundials_Interface.h"
#include "math/external-ode-solvers/OpenSMOKE_CVODE_Sundials.h"
#endif

#if OPENSMOKE_USE_MEBDF == 1
#include "math/external-ode-solvers/OpenSMOKE_MEBDF_Interface.h"
#include "math/external-ode-solvers/OpenSMOKE_MEBDF.h"
#endif

#include "math/external-ode-solvers/OpenSMOKE_OdeSystemObject.h"
#include "ODESystemVirtualClassWithOpenSMOKEVectors.H"
#include "BatchReactorHomogeneousConstantVolume.H"

namespace OpenSMOKE
{
	//!  A class to solve the constant volume batch reactors with homogeneous reactions
	/*!
		This class solves the ordinary differential equations governing a batch reactor
                with homogeneous reactions
	*/

	class BatchReactorHomogeneousConstantVolume_ODE_OpenSMOKE : public ODESystemVirtualClassWithOpenSMOKEVectors
	{
	public:

		BatchReactorHomogeneousConstantVolume_ODE_OpenSMOKE() {};

		void SetReactor(BatchReactorHomogeneousConstantVolume* reactor) { reactor_ = reactor; }

		virtual void GetEquations(const OpenSMOKE::OpenSMOKEVectorDouble& y, const double t, OpenSMOKE::OpenSMOKEVectorDouble& dy)
		{
			reactor_->Equations(t, y, dy);
		}
		virtual void PrintResults(const OpenSMOKE::OpenSMOKEVectorDouble& y, const double t)
		{
			reactor_->Print(t, y);
		}

	private:

		BatchReactorHomogeneousConstantVolume* reactor_;
	};
	
	#if OPENSMOKE_USE_DVODE == 1
	class BatchReactorHomogeneousConstantVolume_ODE_DVODE : public OpenSMOKE::OpenSMOKE_OdeSystemObject
	{
		DEFINE_ODESOLVERINTERFACE_DVODE(BatchReactorHomogeneousConstantVolume_ODE_DVODE)

		BatchReactorHomogeneousConstantVolume* batch_;
		OpenSMOKE::OpenSMOKEVectorDouble y_;
		OpenSMOKE::OpenSMOKEVectorDouble dy_;
	
	public:

		void SetBatchReactorHomogeneousConstantVolume(BatchReactorHomogeneousConstantVolume* batch)
		{
			batch_ = batch;
			ChangeDimensions(batch_->NumberOfEquations(), &y_, true);
			ChangeDimensions(batch_->NumberOfEquations(), &dy_, false);
		}
	 
		int GetSystemFunctions(const double t, double* y,  double* dy)
		{
			y_.CopyFrom(y);
			int flag = batch_->Equations(t, y_, dy_);
			dy_.CopyTo(dy);
			return(flag);
		}
	
		int GetAnalyticalJacobian(const double t,  double* y,  double* J)
		{
			return(0);
		}
	 
		int GetWriteFunction(const double t, double *y)
		{
			y_.CopyFrom(y);
			int flag = batch_->Print(t, y_);
			return 0;
 		}
	}; 
	COMPLETE_ODESOLVERINTERFACE_DVODE(BatchReactorHomogeneousConstantVolume_ODE_DVODE)
	#endif

	#if OPENSMOKE_USE_ODEPACK == 1
	class BatchReactorHomogeneousConstantVolume_ODE_DLSODE : public OpenSMOKE::OpenSMOKE_OdeSystemObject
	{
		DEFINE_ODESOLVERINTERFACE_DLSODE(BatchReactorHomogeneousConstantVolume_ODE_DLSODE)

		BatchReactorHomogeneousConstantVolume* batch_;
		OpenSMOKE::OpenSMOKEVectorDouble y_;
		OpenSMOKE::OpenSMOKEVectorDouble dy_;
	
	public:

		void SetBatchReactorHomogeneousConstantVolume(BatchReactorHomogeneousConstantVolume* batch)
		{
			batch_ = batch;
			ChangeDimensions(batch_->NumberOfEquations(), &y_, true);
			ChangeDimensions(batch_->NumberOfEquations(), &dy_, false);
		}
	 
		int GetSystemFunctions(const double t, double* y,  double* dy)
		{
			y_.CopyFrom(y);
			int flag = batch_->Equations(t, y_, dy_);
			dy_.CopyTo(dy);
			return(flag);
		}
	
		int GetAnalyticalJacobian(const double t,  double* y,  double* J)
		{
			return(0);
		}
	 
		int GetWriteFunction(const double t, double *y)
		{
			y_.CopyFrom(y);
			int flag = batch_->Print(t, y_);
			return 0;
 		}
	}; 
	COMPLETE_ODESOLVERINTERFACE_DLSODE(BatchReactorHomogeneousConstantVolume_ODE_DLSODE)

	class BatchReactorHomogeneousConstantVolume_ODE_DLSODA : public OpenSMOKE::OpenSMOKE_OdeSystemObject
	{
		DEFINE_ODESOLVERINTERFACE_DLSODA(BatchReactorHomogeneousConstantVolume_ODE_DLSODA)

		BatchReactorHomogeneousConstantVolume* batch_;
		OpenSMOKE::OpenSMOKEVectorDouble y_;
		OpenSMOKE::OpenSMOKEVectorDouble dy_;
	
	public:

		void SetBatchReactorHomogeneousConstantVolume(BatchReactorHomogeneousConstantVolume* batch)
		{
			batch_ = batch;
			ChangeDimensions(batch_->NumberOfEquations(), &y_, true);
			ChangeDimensions(batch_->NumberOfEquations(), &dy_, false);
		}
	 
		int GetSystemFunctions(const double t, double* y,  double* dy)
		{
			y_.CopyFrom(y);
			int flag = batch_->Equations(t, y_, dy_);
			dy_.CopyTo(dy);
			return(flag);
		}
	
		int GetAnalyticalJacobian(const double t,  double* y,  double* J)
		{
			return(0);
		}
	 
		int GetWriteFunction(const double t, double *y)
		{
			y_.CopyFrom(y);
			int flag = batch_->Print(t, y_);
			return 0;
 		}
	}; 
	COMPLETE_ODESOLVERINTERFACE_DLSODA(BatchReactorHomogeneousConstantVolume_ODE_DLSODA)
	#endif

	#if OPENSMOKE_USE_DASPK == 1
	class BatchReactorHomogeneousConstantVolume_ODE_DASPK : public OpenSMOKE::OpenSMOKE_OdeSystemObject
	{
		BatchReactorHomogeneousConstantVolume* batch_;

		DEFINE_ODESOLVERINTERFACE_DASPK(BatchReactorHomogeneousConstantVolume_ODE_DASPK)

		OpenSMOKE::OpenSMOKEVectorDouble y_;
		OpenSMOKE::OpenSMOKEVectorDouble dy_;
	
	public:

		void SetBatchReactorHomogeneousConstantVolume(BatchReactorHomogeneousConstantVolume* batch)
		{
			batch_ = batch;
			ChangeDimensions(batch_->NumberOfEquations(), &y_, true);
			ChangeDimensions(batch_->NumberOfEquations(), &dy_, false);
		}
	 
		int GetSystemFunctions(const double t, double* y,  double* dy)
		{
			y_.CopyFrom(y);
			int flag = batch_->Equations(t, y_, dy_);
			dy_.CopyTo(dy);
			return(flag);
		}
	
		int GetAnalyticalJacobian(const double t,  double* y,  double* J)
		{
			return(0);
		}
	 
		int GetWriteFunction(const double t, double *y)
		{
			y_.CopyFrom(y);
			int flag = batch_->Print(t, y_);
			return 0;
 		}
	}; 
	COMPLETE_ODESOLVERINTERFACE_DASPK(BatchReactorHomogeneousConstantVolume_ODE_DASPK)
	#endif

	#if OPENSMOKE_USE_RADAU == 1
	class BatchReactorHomogeneousConstantVolume_ODE_RADAU5 : public OpenSMOKE::OpenSMOKE_OdeSystemObject
	{
		DEFINE_ODESOLVERINTERFACE_RADAU(BatchReactorHomogeneousConstantVolume_ODE_RADAU5)

		BatchReactorHomogeneousConstantVolume* batch_;
		OpenSMOKE::OpenSMOKEVectorDouble y_;
		OpenSMOKE::OpenSMOKEVectorDouble dy_;
	
	public:

		void SetBatchReactorHomogeneousConstantVolume(BatchReactorHomogeneousConstantVolume* batch)
		{
			batch_ = batch;
			ChangeDimensions(batch_->NumberOfEquations(), &y_, true);
			ChangeDimensions(batch_->NumberOfEquations(), &dy_, false);
		}
	 
		int GetSystemFunctions(const double t, double* y,  double* dy)
		{
			y_.CopyFrom(y);
			int flag = batch_->Equations(t, y_, dy_);
			dy_.CopyTo(dy);
			return(flag);
		}
	
		int GetAnalyticalJacobian(const double t,  double* y,  double* J)
		{
			return(0);
		}
	 
		int GetWriteFunction(const double t, double *y)
		{
			y_.CopyFrom(y);
			int flag = batch_->Print(t, y_);
			return 0;
 		}
	}; 
	COMPLETE_ODESOLVERINTERFACE_RADAU(BatchReactorHomogeneousConstantVolume_ODE_RADAU5)
	#endif

	#if OPENSMOKE_USE_SUNDIALS == 1
	class BatchReactorHomogeneousConstantVolume_ODE_CVODE : public OpenSMOKE::OpenSMOKE_OdeSystemObject
	{
		DEFINE_ODESOLVERINTERFACE_CVODE_Sundials(BatchReactorHomogeneousConstantVolume_ODE_CVODE)

		BatchReactorHomogeneousConstantVolume* batch_;
		OpenSMOKE::OpenSMOKEVectorDouble y_;
		OpenSMOKE::OpenSMOKEVectorDouble dy_;
	
	public:

		void SetBatchReactorHomogeneousConstantVolume(BatchReactorHomogeneousConstantVolume* batch)
		{
			batch_ = batch;
			ChangeDimensions(batch_->NumberOfEquations(), &y_, true);
			ChangeDimensions(batch_->NumberOfEquations(), &dy_, false);
		}
	 
		int GetSystemFunctions(const double t, double* y,  double* dy)
		{
			y_.CopyFrom(y);
			int flag = batch_->Equations(t, y_, dy_);
			dy_.CopyTo(dy);
			return(flag);
		}
	
		int GetAnalyticalJacobian(const double t,  double* y,  double* J)
		{
			return(0);
		}
	 
		int GetWriteFunction(const double t, double *y)
		{
			y_.CopyFrom(y);
			int flag = batch_->Print(t, y_);
			return 0;
 		}
	}; 
	COMPLETE_ODESOLVERINTERFACE_CVODE_Sundials(BatchReactorHomogeneousConstantVolume_ODE_CVODE)
	#endif

	#if OPENSMOKE_USE_MEBDF == 1
	class BatchReactorHomogeneousConstantVolume_ODE_MEBDF : public OpenSMOKE::OpenSMOKE_OdeSystemObject
	{
		DEFINE_ODESOLVERINTERFACE_MEBDF(BatchReactorHomogeneousConstantVolume_ODE_MEBDF)

		BatchReactorHomogeneousConstantVolume* batch_;
		OpenSMOKE::OpenSMOKEVectorDouble y_;
		OpenSMOKE::OpenSMOKEVectorDouble dy_;
	
	public:

		void SetBatchReactorHomogeneousConstantVolume(BatchReactorHomogeneousConstantVolume* batch)
		{
			batch_ = batch;
			ChangeDimensions(batch_->NumberOfEquations(), &y_, true);
			ChangeDimensions(batch_->NumberOfEquations(), &dy_, false);
		}
	 
		int GetSystemFunctions(const double t, double* y,  double* dy)
		{
			y_.CopyFrom(y);
			int flag = batch_->Equations(t, y_, dy_);
			dy_.CopyTo(dy);
			return(flag);
		}
	
		int GetAnalyticalJacobian(const double t,  double* y,  double* J)
		{
			return(0);
		}
	 
		int GetWriteFunction(const double t, double *y)
		{
			y_.CopyFrom(y);
			int flag = batch_->Print(t, y_);
			return 0;
 		}
	}; 
	COMPLETE_ODESOLVERINTERFACE_MEBDF(BatchReactorHomogeneousConstantVolume_ODE_MEBDF)
	#endif
}

#endif	// BatchReactorHomogeneousConstantVolume_ODE_Interface_H
