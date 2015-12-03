/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_math_Defiendums.hpp                                  */
/* Description:     global container for defiendum terms                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_MATH_DEFIENDUMS_HPP_
#define MDL_MATH_DEFIENDUMS_HPP_

#include "mdl/math/mdl_math_Container.hpp"

namespace mdl {
namespace math {

class Defiendums :
	public object :: Object,
	public Scalar<Defiendums> {
public :
	Defiendums ();
	virtual ~ Defiendums();
	
	void add (mdl :: term :: Definition*);
	mdl :: Term* unifiesWith (const mdl :: term :: Definition*);

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;
	
private :
	typedef
		tree :: Term :: Unify_<array :: Expression>
		Unify_;

	tree :: Term* tree_;
	value :: Integer count_;
	pthread_mutex_t mutex_;
};

}
}

#endif /*MDL_MATH_DEFIENDUMS_HPP_*/
