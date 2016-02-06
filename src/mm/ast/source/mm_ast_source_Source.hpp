/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Source.hpp                                 */
/* Description:     metamath source                                          */
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
namespace source {

class Source :
	public mm :: source :: Source,
	public Scalar<Source> {
public :
	Source
	(
		const mm :: source :: Include* const,
		mm :: source :: Block* const = NULL
	);
	virtual ~ Source();

	// source :: Source interface
	virtual void setBlock (const mm :: source :: Block* const);

	// object :: Verifiable interface
	virtual void check() const;

	// object :: Translatable interface
	virtual const object :: Targetive* translate() const;
	virtual bool isBlock() const;
	virtual bool isDisjoined() const;
	virtual bool isFloating() const;
	virtual bool isEssential() const;

	// object :: Writable interface
	virtual void write (String&) const;
	virtual void write() const;
	virtual bool nothingToWrite() const;

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const bool isTop_;
	const mm :: source :: Include* const include_;
	const mm :: source :: Block* block_;

	mutable mm :: target :: Target* target_;
	Output* output_;
};

}
}
}


