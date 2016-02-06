/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_teach_Teacher_Estimating.hpp                   */
/* Description:     a class for a complex time estimation                    */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {
namespace teach {

class Teacher :: Estimating :
	public object :: Object,
	public Scalar<Teacher :: Estimating> {
public :
	Estimating
	(
		Format&,
		const value :: Integer precision,
		const value :: Integer grouping
	);
	virtual ~ Estimating();

	bool estimateSize (const Time timeLimit);
	value :: Integer getSampleSize() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	Format format_;
	value :: Integer sampleSize_;
	const value :: Integer precision_;
	const value :: Integer grouping_;
};

}
}
}


