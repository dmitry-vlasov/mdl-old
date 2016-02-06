/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Evidences.hpp                       */
/* Description:     interface for a collection of evidences                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "mdl/interface/mdl_interface.dpp"

namespace mdl {
namespace prover {
namespace interface {

template<class A>
class Evidences : public object :: Object {
public :
	typedef A Allocator_;
	typedef Base<Allocator_> Base_;
	typedef Node<Allocator_> Node_;
	typedef Proof<Allocator_> Proof_;
	typedef Evidence<Allocator_> Evidence_;
	typedef
		typename Base_ :: Expression_
		Expression_;
	typedef
		typename Base_ :: Substitution_
		Substitution_;

	virtual void checkForDuplicateProofs() = 0;
	virtual void add (const stack :: Substitution*, Evidence_* up) = 0;
	virtual void verifyIntegrity() const = 0;
	virtual value :: Integer getSize() const = 0;
	virtual void add (Evidence_*) = 0;
	virtual Evidence_* getValue (const value :: Integer) = 0;
	virtual Node_* getNode() = 0;
	virtual const Evidence_* getValue (const value :: Integer) const = 0;
	virtual void show (String&, const int indent = 0) const = 0;

	void showInfo (String&, const int indent = 0) const;
};

}
}
}


