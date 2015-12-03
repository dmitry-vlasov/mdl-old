/*****************************************************************************/
/* Project name:    mm - decompiler from metamath to mdl                     */
/* File Name:       mm_ast_source_Include.hpp                                */
/* Description:     metamath file inclusion                                  */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MM_AST_SOURCE_INCLUDE_HPP_
#define MM_AST_SOURCE_INCLUDE_HPP_

#include "interface/mm_interface.hpp"

namespace mm {
namespace ast {
namespace source {

class Include :
	public mm :: source :: Include,
	public Scalar<Include> {
public :
	Include (const Path* const);
	Include (const Location& location, const String&);
	virtual ~ Include();

	// source :: Include interface
	virtual const Path& getPath() const;

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

	// object :: Object interface
	virtual void commitSuicide();
	virtual Size_t getVolume() const;
	virtual Size_t getSizeOf() const;

private :
	const Location location_;
	const Path path_;
};

}
}
}

#endif /* MM_AST_SOURCE_INCLUDE_HPP_ */
