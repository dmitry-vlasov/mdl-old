/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File Name:       mdl_prover_interface_Tree.hpp                            */
/* Description:     main prover tree interface                               */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_PROVER_INTERFACE_TREE_HPP_
#define MDL_PROVER_INTERFACE_TREE_HPP_

#include "mdl/interface/object/mdl_interface_object.hpp"

namespace mdl {
namespace prover {
namespace interface {

class Tree : public object :: Object {
public :
	Tree();
	virtual ~ Tree();

	// Prove automatically
	virtual bool prove (const Time) = 0;

	// Prove interactively
	virtual void start (String&) = 0;
	virtual void grow  () = 0;
	virtual void stop  () = 0;
	virtual void info  (String&) = 0;

	// Confirm found proof
	virtual void confirm() = 0;
	virtual bool isProved() = 0;

	virtual void showVolume (String&) const = 0;
	virtual void showTiming (String&) const = 0;
	virtual Data* getData() const = 0;

	static Tree* get();

private :
	static Tree* tree_;
};

}
}
}

#endif /*MDL_PROVER_INTERFACE_TREE_HPP_*/
