/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Constants.hpp                                   */
/* Description:     global container for constants                           */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/math/mdl_math_Container.hpp"

namespace mdl {
namespace math {

class Constants :
	public Container<mdl :: Constant, index :: Constant>,
	public Scalar<Constants> {
public :
	Constants ();
	virtual ~ Constants();
	
	mdl :: Constant* get (const index :: Constant);
	index :: Constant add (mdl :: Constant*);
	bool contain (const value :: Literal);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef 
		Container<mdl :: Constant, index :: Constant>
		Ancestor_;

	set :: value :: Literal constantSet_;

	enum { 
			INITIAL_CONSTANT_VECTOR_CAPACITY = 1024 
	};

	pthread_mutex_t mutex_;
};

}
}


