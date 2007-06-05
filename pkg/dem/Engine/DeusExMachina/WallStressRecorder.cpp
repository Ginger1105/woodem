/*************************************************************************
*  Copyright (C) 2006 by luc scholtes                                    *
*  luc.scholtes@hmg.inpg.fr                                              *
*                                                                        *
*  This program is free software; it is licensed under the terms of the  *
*  GNU General Public License v2 or later. See file LICENSE for details. *
*************************************************************************/

#include "WallStressRecorder.hpp"
#include <yade/pkg-common/RigidBodyParameters.hpp>
#include <yade/pkg-common/ParticleParameters.hpp>
#include <yade/pkg-dem/BodyMacroParameters.hpp>
#include <yade/pkg-common/Force.hpp>
#include <yade/pkg-dem/ElasticContactLaw.hpp>

#include <yade/pkg-dem/SpheresContactGeometry.hpp>
#include <yade/pkg-dem/ElasticContactInteraction.hpp>

#include <yade/core/Omega.hpp>
#include <yade/core/MetaBody.hpp>
#include <boost/lexical_cast.hpp>


WallStressRecorder::WallStressRecorder () : DataRecorder(), actionForce(new Force)

{
	outputFile = "";
	interval = 1;
	
	height = 0;
	width = 0;
	depth = 0;
	thickness = 0;
}


void WallStressRecorder::postProcessAttributes(bool deserializing)
{
	if(deserializing)
	{
		ofile.open(outputFile.c_str());
	}
}


void WallStressRecorder::registerAttributes()
{
	DataRecorder::registerAttributes();
	REGISTER_ATTRIBUTE(outputFile);
	REGISTER_ATTRIBUTE(interval);
	
	REGISTER_ATTRIBUTE(wall_bottom_id);
 	REGISTER_ATTRIBUTE(wall_top_id);
 	REGISTER_ATTRIBUTE(wall_left_id);
 	REGISTER_ATTRIBUTE(wall_right_id);
 	REGISTER_ATTRIBUTE(wall_front_id);
 	REGISTER_ATTRIBUTE(wall_back_id);
 	
 	REGISTER_ATTRIBUTE(height);
	REGISTER_ATTRIBUTE(width);
	REGISTER_ATTRIBUTE(depth);
	REGISTER_ATTRIBUTE(thickness);

}


bool WallStressRecorder::isActivated()
{
	return ((Omega::instance().getCurrentIteration() % interval == 0) && (ofile));
}


void WallStressRecorder::action(Body * body)
{
	MetaBody * ncb = static_cast<MetaBody*>(body);
	shared_ptr<BodyContainer>& bodies = ncb->bodies;
		
	/// dimensions de l'echantillon
	
	PhysicalParameters* p_bottom = static_cast<PhysicalParameters*>((*bodies)[wall_bottom_id]->physicalParameters.get());
	PhysicalParameters* p_top   =	 static_cast<PhysicalParameters*>((*bodies)[wall_top_id]->physicalParameters.get());
	PhysicalParameters* p_left 	= static_cast<PhysicalParameters*>((*bodies)[wall_left_id]->physicalParameters.get());
	PhysicalParameters* p_right = static_cast<PhysicalParameters*>((*bodies)[wall_right_id]->physicalParameters.get());
	PhysicalParameters* p_front = static_cast<PhysicalParameters*>((*bodies)[wall_front_id]->physicalParameters.get());
	PhysicalParameters* p_back 	= static_cast<PhysicalParameters*>((*bodies)[wall_back_id]->physicalParameters.get());
	
	
	height = p_top->se3.position.Y() - p_bottom->se3.position.Y() - thickness;
	width = p_right->se3.position.X() - p_left->se3.position.X() - thickness;
	depth = p_front->se3.position.Z() - p_back->se3.position.Z() - thickness;
	
	/// calcul des contraintes via forces resultantes sur murs
	
	Real SIG_wall_11 = 0, SIG_wall_22 = 0, SIG_wall_33 = 0;
	
	Vector3r F_wall_11 = static_cast<Force*>( ncb->physicalActions->find(wall_left_id, actionForce->getClassIndex() ). get() )->force;
	
	SIG_wall_11 = F_wall_11[0]/(depth*height);
	
	Vector3r F_wall_22 = static_cast<Force*>( ncb->physicalActions->find(wall_top_id, actionForce->getClassIndex() ). get() )->force;
	
	SIG_wall_22 = F_wall_22[1]/(depth*width);
	
	Vector3r F_wall_33 = static_cast<Force*>( ncb->physicalActions->find(wall_front_id, actionForce->getClassIndex() ). get() )->force;
	
	SIG_wall_33 = F_wall_33[2]/(width*height);
	
	ofile << lexical_cast<string>(Omega::instance().getSimulationTime()) << " " 
		<< lexical_cast<string>(SIG_wall_11) << " "
		<< lexical_cast<string>(p_left->se3.position.X()) << " "
 		<< lexical_cast<string>(SIG_wall_22) << " "
 		<< lexical_cast<string>(p_top->se3.position.Y()) << " "
		<< lexical_cast<string>(SIG_wall_33) << " "
		<< lexical_cast<string>(p_front->se3.position.Z()) << " "
		<< endl;
	
}

