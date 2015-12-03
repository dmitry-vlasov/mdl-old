/*****************************************************************************/
/* Project name:    del - mathematics development language                   */
/* File Name:       del_interface_Symbol.hpp                                 */
/* Description:     signature class                                          */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef DEL_INTERFACE_SYMBOL_HPP_
#define DEL_INTERFACE_SYMBOL_HPP_

#include "del/interface/del_interface.hpp"
#include "del/lexer/del_lexer_Token.hpp"
#include "del/source/term/del_source_term.dpp"

namespace del {
namespace interface {

class Symbol {
public :
	Symbol();
	Symbol
	(
		const value :: Symbol,
		const bool isRelation,
		const bool isAsterisk = false,
		const bool isTemporary = false
	);
	Symbol (const Symbol&);
	virtual ~ Symbol();

	void operator = (const Symbol&);

	const String& getString() const;

	// del :: Symbol interface
	value :: Variable getVariable() const;
	value :: Relation getRelation() const;
	value :: Symbol getValue() const;
	bool isVariable() const;
	bool isRelation() const;
	bool isAsterisk() const;
	bool isTemporary() const;
	bool isTop() const;
	bool isUndefined() const;
	bool isDefined() const;

	void undefine();
	void setAsterisk (const bool);

	// Writable interface
	void translate (String&) const;
	void replicate (String&) const;

	// Object interface
	void show (String&) const;
	void show (std :: ostream&) const;
	Size_t getVolume() const;
	Size_t getSizeOf() const;

private :
	friend class del :: source :: term :: Variable;

	void writeFuncFormat (String&) const;
	void writeFuncSymbolString (String&, const String&) const;

	enum {
		ENCLOSE_SYMBOL_IN_FUNC_FORMAT = false
	};

	value :: Symbol value_;
	bool isRelation_;
	bool isAsterisk_;
	bool isTemporary_;
};

	bool operator == (const Symbol&, const Symbol&);
	bool operator != (const Symbol&, const Symbol&);
	bool operator < (const Symbol&, const Symbol&);
	bool operator > (const Symbol&, const Symbol&);
	bool operator <= (const Symbol&, const Symbol&);
	bool operator >= (const Symbol&, const Symbol&);

	String& operator << (String&, const Symbol&);
	std :: ostream& operator << (std :: ostream&, const Symbol&);
}
}

#endif /*DEL_INTERFACE_SYMBOL_HPP_*/
