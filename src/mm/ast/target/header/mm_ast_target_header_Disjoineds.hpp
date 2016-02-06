/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File name:       mm_ast_target_header_Disjoineds.hpp                      */
/* Description:     mdl disjoined variables restrictions                     */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#pragma once

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace target {
namespace header {

class Disjoineds :
	public mm :: target :: Disjoineds,
	public Scalar<Disjoineds> {
public :
	Disjoineds (const bool);
	virtual ~ Disjoineds();

	// target :: Disjointeds interface
	virtual void addDisjoined (const mm :: target :: Disjoined* const);

	// object :: Targetive interface
	virtual void complete (mm :: target :: Block* const) const;

	// object :: Writable interface
	virtual void write (String&) const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	typedef
		list :: target :: Disjoined
		Disjoineds_;
	typedef
		Disjoineds_ :: Node_
		Node_;
	bool isEmpty() const;
	bool isLast (const Node_*) const;

	Disjoineds_ disjoineds_;
	const bool axiomatic_;
};

}
}
}
}


