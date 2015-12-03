/*****************************************************************************/
/* Project name:    mdl - mathematics development language                   */
/* File name:       mdl_expression_Symbol.hpp                                */
/* Description:     expression symbol                                        */
/* Copyright:       (c) 2006-2009 Dmitri Vlasov                              */
/* Author:          Dmitri Yurievich Vlasov, Novosibirsk, Russia             */
/* Email:           vlasov at academ.org                                     */
/* URL:             http://mathdevlanguage.sourceforge.net                   */
/* Modified by:                                                              */
/* License:         GNU General Public License Version 3                     */
/*****************************************************************************/

#ifndef MDL_EXPRESSION_SYMBOL_HPP_
#define MDL_EXPRESSION_SYMBOL_HPP_

#include "mdl/types/mdl_types.hpp"
#include "mdl/interface/mdl_interface.dpp"

namespace mdl {
namespace expression {

class Symbol {
public :
	Symbol ();
	Symbol (const value :: Literal);
	Symbol (const Symbol&);
	~ Symbol();

	const String& getString() const;
	value :: Literal getLiteral() const;
	static value :: Literal getLambda();
	const mdl :: Type* getType() const;

	bool isLambda() const;
	bool isUndefined() const;
	bool isReplaceable() const;
	bool isFixed() const;
	bool isConstant() const;
	bool isVariable() const;
	bool isEqualLiteraly (const char*) const;
	bool isEqualLiteraly (const value :: Literal) const;
	bool isEqualLiteraly (const Symbol&) const;

	bool operator == (const Symbol&) const;
	bool operator != (const Symbol&) const;
	void operator = (const Symbol&);

	void setLambda();
	void setLiteral (const value :: Literal);
	void setType (mdl :: Type*);
	void setReplaceable (const bool = true);

	void build (const object :: Typing*, bool = false);
	void write (String&) const;
	void writeReversed (String&) const;

	// object :: Object interface
	void commitSuicide();
	Size_t getVolume() const;
	Size_t getSizeOf() const;
	void show (String&) const;
	void dump() const;

private :
	friend bool operator < (const Symbol&, const Symbol&);
	friend bool operator <= (const Symbol&, const Symbol&);
	friend bool operator > (const Symbol&, const Symbol&);
	friend bool operator >= (const Symbol&, const Symbol&);

	value :: Literal literal_;
	bool isReplaceable_;
	const mdl :: Type* type_;
	static const value :: Literal lambda_;
};

	String&
	operator << (String&, const Symbol&);
	std  :: ostream&
	operator << (std :: ostream&, const Symbol&);

	bool operator < (const Symbol&, const Symbol&);
	bool operator <= (const Symbol&, const Symbol&);
	bool operator > (const Symbol&, const Symbol&);
	bool operator >= (const Symbol&, const Symbol&);
}
}

#endif /*MDL_EXPRESSION_SYMBOL_HPP_*/
