/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_study_Expreience.hpp                                 */
/* Description:     collecting experience of proposition usage               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_STUDY_EXPERIENCE_HPP_
#define MDL_STUDY_EXPERIENCE_HPP_

#include "mdl/interface/mdl_interface.hpp"

namespace mdl {
namespace study {

class Experience :
	public object :: Object,
	public Scalar<Experience> {
public :
	Experience (Format&, Sample*);
	virtual ~ Experience();

	bool collect();

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	void processMath();
	void processProof (const Proof*) const;
	void showExperience();

	enum {
		INITIAL_MESSAGE_CAPACITY = 64
	};

	Format  format_;
	Format  subFormat_;
	String  message_;
	Sample* sample_;
};

}
}

#endif /*MDL_STUDY_EXPERIENCE_HPP_*/
