/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Theories.hpp                                    */
/* Description:     global container for theories                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_MATH_THEORIES_HPP_
#define MDL_MATH_THEORIES_HPP_

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/math/mdl_math_Container.hpp"

namespace mdl {
namespace math {

class Theories :
	public Container<mdl :: Theory, index :: Theory>,
	public Scalar<Theories> {
public :
	Theories ();
	virtual ~ Theories();
	
	mdl :: Theory* get (const index :: Theory);
	index :: Theory add (mdl :: Theory*);
	mdl :: Theory* getRoot();

	void mine() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	typedef 
		Container<mdl :: Theory, index :: Theory>
		Ancestor_;

	mdl :: Theory* root_;
	enum { 
		INITIAL_THEORY_VECTOR_CAPACITY = size :: KILOBYTE,
		INITIAL_MINE_OUTPUT_CAPACITY   = size :: KILOBYTE
	};
	pthread_mutex_t mutex_;
};

}
}

#endif /*MDL_MATH_THEORIES_HPP_*/
