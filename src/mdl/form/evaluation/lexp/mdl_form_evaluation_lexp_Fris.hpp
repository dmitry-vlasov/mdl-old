/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_form_evaluation_lexp_Fris.hpp                        */
/* Description:     FRiS function                                            */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.hpp"
#include "mdl/form/evaluation/lexp/mdl_form_evaluation_lexp_Vector.hpp"
#include "mdl/form/evaluation/lexp/mdl_form_evaluation_lexp_Factors.hpp"

namespace mdl {
namespace form {
namespace evaluation {
namespace lexp {

template<class A>
class Fris :
	public object :: Object,
	public Scalar<Fris<A> > {
public :
	typedef A Allocator_;
	typedef prover :: Types<Allocator_> Types_;
	typedef Point<Allocator_> Point_;
	typedef
		typename Types_ :: Node_
		Node_;
	typedef
		typename Types_ :: Expression_
		Expression_;
	typedef
		Vector<Allocator_>
		Vector_;

	Fris (const value :: Integer);
	Fris (const bool);  // constant FRiS constructor
	Fris (const mdl :: evaluation :: vector :: Case&);
	Fris
	(
		const mdl :: evaluation :: vector :: Case&,
		const Factors& factors
	);
	virtual ~ Fris();

	void addPoint (const Point_*);
	value :: Real classify (const Node_*) const;
	bool isConst() const;
	bool getSign() const;
	const Vector_* getVector() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;
	virtual void show (String&) const;

private :
	const bool sign_;
	Factors    factors_;
	Vector_*   vector_;
};

}
}
}
}


