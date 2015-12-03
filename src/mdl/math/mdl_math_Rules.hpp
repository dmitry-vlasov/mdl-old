/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Rules.hpp                                       */
/* Description:     global container for syntactic grammar rules             */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_MATH_RULES_HPP_
#define MDL_MATH_RULES_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/math/mdl_math_Container.hpp"

namespace mdl {
namespace math {

class Rules :
	public Container<Rule, index :: Rule>,
	public Scalar<Rules> {
public :
	Rules ();
	virtual ~ Rules();
	
	mdl :: Rule* get (const index :: Rule);
	index :: Rule add (mdl :: Rule*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef 
		Container<mdl :: Rule, index :: Rule>
		Ancestor_;
	enum { 
		INITIAL_RULE_VECTOR_CAPACITY = size :: KILOBYTE
	};
	pthread_mutex_t mutex_;
};

}
}

#endif /*MDL_MATH_RULES_HPP_*/
